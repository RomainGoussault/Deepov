/*
	Deepov, a UCI chess playing engine.

	Copyright (c) 20014-2016 Romain Goussault, Navid Hedjazian

    Deepov is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Deepov is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Deepov.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "MoveGen.hpp"
#include "BitBoardUtils.hpp"
#include "MagicMoves.hpp"
#include "Tables.hpp"

#include <algorithm>
#include <memory>


/* Constructor */
MoveGen::MoveGen(Board board) : myBoard(std::make_shared<Board>(board) )
{
}

MoveGen::MoveGen(std::shared_ptr<Board> boardPtr)
{
	myBoard = boardPtr;
}

/* Moves private methods */

void MoveGen::addQuietMoves(U64 quietDestinations, Square pieceIndex, std::vector<Move>& moves, Piece::PieceType pieceType) const
{
	while (quietDestinations)
	{
		//Getting the index of the MSB
		Square positionMsb = pop_lsb(&quietDestinations);

		Move move = Move(pieceIndex, positionMsb, 0, pieceType);
		moves.push_back(move);
	}
}

void MoveGen::addDoublePawnPushMoves(U64 pawnDestinations, Square pieceIndex, std::vector<Move>& moves) const
{
	while (pawnDestinations)
	{
		//Getting the index of the MSB
		Square positionMsb = pop_lsb(&pawnDestinations);

		Move move = Move(pieceIndex, positionMsb, Move::DOUBLE_PAWN_PUSH_FLAG, Piece::PAWN);
		moves.push_back(move);
	}
}

void MoveGen::addCaptureMoves(U64 captureDestinations, Square pieceIndex, std::vector<Move>& moves, Piece::PieceType pieceType) const
{
	while (captureDestinations)
	{
		//Getting the index of the MSB
		Square positionMsb = pop_lsb(&captureDestinations);
		Move move = Move(pieceIndex, positionMsb, Move::CAPTURE_FLAG, pieceType);
		Piece::PieceType capturedType(myBoard->findPieceType(positionMsb,Utils::getOppositeColor(myBoard->getColorToPlay())));
		move.setCapturedPieceType(capturedType);
		moves.push_back(move);

	}
}

void MoveGen::addPromotionMoves(U64 promotionDestinations, Square pieceIndex, std::vector<Move>& moves) const
{
	while (promotionDestinations)
	{
		//Getting the index of the MSB
		Square positionMsb = pop_lsb(&promotionDestinations);
		Move move = Move(pieceIndex, positionMsb, Move::PROMOTION_FLAG, Piece::PAWN);
		moves.push_back(move);
		move.setFlags(Move::PROMOTION_FLAG+1);
		moves.push_back(move);
		move.setFlags(Move::PROMOTION_FLAG+2);
		moves.push_back(move);
		move.setFlags(Move::PROMOTION_FLAG+3);
		moves.push_back(move);

		//Removing the MSB
	}
}

void MoveGen::addPromotionCaptureMoves(U64 promotionDestinations, Square pieceIndex, std::vector<Move>& moves) const
{
	while (promotionDestinations)
	{
		//Getting the index of the MSB
		Square positionMsb = pop_lsb(&promotionDestinations);
		unsigned int flag = Move::PROMOTION_FLAG+Move::CAPTURE_FLAG;
		Move move = Move(pieceIndex, positionMsb, flag, Piece::PAWN);
		Piece::PieceType capturedType(myBoard->findPieceType(positionMsb, Utils::getOppositeColor(myBoard->getColorToPlay())));
		move.setCapturedPieceType(capturedType);

		moves.push_back(move);
		move.setFlags(flag+1);
		moves.push_back(move);
		move.setFlags(flag+2);
		moves.push_back(move);
		move.setFlags(flag+3);
		moves.push_back(move);
	}
}

/* Get moves methods */
void MoveGen::appendKingPseudoLegalMoves(const Color color, std::vector<Move>& moves) const
{
	U64 kingPos = myBoard->getKing(color);
	Square kingIndex = msb(kingPos);
	U64 kingValidDestinations = myBoard->getKingAttacks(kingIndex, color);

	Color ennemyColor = Utils::getOppositeColor(color);
	U64 kingCaptureDestinations = kingValidDestinations & myBoard->getPieces(ennemyColor);
	U64 kingQuietDestinations = kingValidDestinations ^ kingCaptureDestinations;

	addQuietMoves(kingQuietDestinations, kingIndex, moves, Piece::KING);
	addCaptureMoves(kingCaptureDestinations, kingIndex, moves, Piece::KING);
	addKingSideCastlingMove(color, kingIndex, moves);
	addQueenSideCastlingMove(color, kingIndex, moves);
}

void MoveGen::addKingSideCastlingMove(Color color, Square kingIndex, std::vector<Move>& moves) const
{
	if(isKingSideCastlingPossible(color))
	{
		Square destination = static_cast<Square>(color == WHITE ? 6 : 62);
		Move move = Move(kingIndex, destination, Move::KING_SIDE_CASTLING, Piece::KING);
		moves.push_back(move);
	}
}

void MoveGen::addQueenSideCastlingMove(Color color, Square kingIndex, std::vector<Move>& moves) const
{
	if(isQueenSideCastlingPossible(color))
	{
		Square destination = static_cast<Square>(color == WHITE ? 2 : 58);
		Move move = Move(kingIndex, destination, Move::QUEEN_SIDE_CASTLING, Piece::KING);
		moves.push_back(move);
	}
}

void MoveGen::appendQueenPseudoLegalMoves(const Color color, std::vector<Move>& moves, U64 target) const
{
	U64 queenPositions = myBoard->getQueens(color);

	//loop through the queens:
	while(queenPositions)
	{
		Square queenIndex = pop_lsb(&queenPositions);

		Color ennemyColor = Utils::getOppositeColor(color);

		U64 bishopDestinations = MagicMoves::Bmagic(queenIndex, myBoard->getAllPieces()) & ~myBoard->getPieces(color);
		U64 rookDestinations = MagicMoves::Rmagic(queenIndex, myBoard->getAllPieces()) & ~myBoard->getPieces(color);
		U64 queenDestinations = (bishopDestinations ^ rookDestinations) & target ;

		U64 queenCaptureDestinations = queenDestinations & myBoard->getPieces(ennemyColor);
		U64 queenQuietDestinations = queenDestinations ^ queenCaptureDestinations;

		addQuietMoves(queenQuietDestinations, queenIndex, moves, Piece::QUEEN);
		addCaptureMoves(queenCaptureDestinations, queenIndex, moves, Piece::QUEEN);
	}
}

void MoveGen::appendBishopPseudoLegalMoves(const Color color, std::vector<Move>& moves, U64 target) const
{
	U64 bishopPositions = myBoard->getBishops(color);

	//loop through the bishops:
	while(bishopPositions)
	{
		Square bishopIndex = pop_lsb(&bishopPositions);

		Color ennemyColor = Utils::getOppositeColor(color);

		U64 bishopDestinations = MagicMoves::Bmagic(bishopIndex, myBoard->getAllPieces()) & ~myBoard->getPieces(color) & target;

		U64 bishopCaptureDestinations = bishopDestinations & myBoard->getPieces(ennemyColor);
		U64 bishopQuietDestinations = bishopDestinations ^ bishopCaptureDestinations;

		addQuietMoves(bishopQuietDestinations, bishopIndex, moves, Piece::BISHOP);
		addCaptureMoves(bishopCaptureDestinations, bishopIndex, moves, Piece::BISHOP);
	}
}

void MoveGen::appendRookPseudoLegalMoves(const Color color, std::vector<Move>& moves, U64 target) const
{
	U64 rookPositions = myBoard->getRooks(color);

	//loop through the rooks:
	while(rookPositions)
	{
		Square rookIndex = pop_lsb(&rookPositions);

		Color ennemyColor = Utils::getOppositeColor(color);

		U64 rookDestinations = MagicMoves::Rmagic(rookIndex, myBoard->getAllPieces()) & ~myBoard->getPieces(color) & target;

		U64 rookCaptureDestinations = rookDestinations & myBoard->getPieces(ennemyColor);
		U64 rookQuietDestinations = rookDestinations ^ rookCaptureDestinations;

		addQuietMoves(rookQuietDestinations, rookIndex, moves, Piece::ROOK);
		addCaptureMoves(rookCaptureDestinations, rookIndex, moves, Piece::ROOK);
	}
}

void MoveGen::appendPawnPseudoLegalMoves(const Color color, std::vector<Move>& moves, U64 target) const
{
	if(color == WHITE)
	{
		appendWhitePawnPseudoLegalMoves(moves, target);
	}
	else
	{
		appendBlackPawnPseudoLegalMoves(moves, target);
	}
}

void MoveGen::appendKnightPseudoLegalMoves(const Color color, std::vector<Move>& moves, U64 target) const
{
	U64 knightPositions = myBoard->getKnights(color) & ~myBoard->getPinnedPieces();

	//loop through the knights:
	while(knightPositions)
	{
		const Square knightIndex = pop_lsb(&knightPositions);
		U64 knightValidDestinations = myBoard->getKnightAttacks(knightIndex, color) & target;

		Color ennemyColor = Utils::getOppositeColor(color);

		U64 knightCaptureDestinations = knightValidDestinations & myBoard->getPieces(ennemyColor);
		U64 knightQuietDestinations = knightValidDestinations ^ knightCaptureDestinations;

		addQuietMoves(knightQuietDestinations, knightIndex, moves, Piece::KNIGHT);
		addCaptureMoves(knightCaptureDestinations, knightIndex, moves, Piece::KNIGHT);
	}
}

void MoveGen::appendWhitePawnPseudoLegalMoves(std::vector<Move>& moves, U64 target) const
{
	appendWhiteEnPassantMoves(moves, Tables::ALL); //Note: The 2nd argument can be refined.
	//But this can't be set to "target" in case of evasion moves. There is a test for this.
	U64 pawnPositions = myBoard->getWhitePawns();

	while(pawnPositions)
	{
		Square pawnIndex = pop_lsb(&pawnPositions);
		U64 pawnPos = 0 | 1LL << pawnIndex;

		/* check the single space in front of the white pawn */
		U64 firstStep = (pawnPos << 8) & ~myBoard->getAllPieces() ;

		/* for all moves that came from rank 2 (home row), and passed the above
		filter, thereby being on rank 3, ie. on MASK_RANK[2], check and see if I can move forward
		one more */
		U64 twoSteps = ((firstStep & Tables::MASK_RANK[2]) << 8) & ~myBoard->getAllPieces() & target;

		/* next we calculate the pawn attacks */
		U64 validAttacks = Tables::PAWN_ATTACK_TABLE[WHITE][pawnIndex] & myBoard->getBlackPieces() & target;

		/* then we combine the two situations in which a white pawn can legally
		attack/move. */
		// whitePawnValid = (firstStep | twoSteps) | validAttacks; // not needed for now

		addQuietMoves(firstStep & target & Tables::CLEAR_RANK[7], pawnIndex, moves, Piece::PAWN);
		addDoublePawnPushMoves(twoSteps & Tables::CLEAR_RANK[7], pawnIndex, moves);
		addPromotionMoves(firstStep & Tables::MASK_RANK[7], pawnIndex, moves);
		addCaptureMoves(validAttacks & Tables::CLEAR_RANK[7], pawnIndex, moves, Piece::PAWN);
		addPromotionCaptureMoves(validAttacks & Tables::MASK_RANK[7], pawnIndex, moves);
	}
}

void MoveGen::appendBlackPawnPseudoLegalMoves(std::vector<Move>& moves, U64 target) const
{
	appendBlackEnPassantMoves(moves, Tables::ALL);//Note: The 2nd argument can be refined.
	//But this can't be set to "target" in case of evasion moves. There is a test for this.
	U64 pawnPositions = myBoard->getBlackPawns();

	while(pawnPositions)
	{
		Square pawnIndex = pop_lsb(&pawnPositions);
		U64 pawnPos = 0 | 1LL << pawnIndex;

		/* check the single space in front of the white pawn */
		U64 firstStep = (pawnPos >> 8) & ~myBoard->getAllPieces();

		/* for all moves that came from rank 7 (home row), and passed the above
		filter, thereby being on rank 6, ie. on MASK_RANK[5], check and see if I can move forward
		one more */
		U64 twoSteps = ((firstStep & Tables::MASK_RANK[5]) >> 8) & ~myBoard->getAllPieces() & target;

		/* next we calculate the pawn attacks */
		U64 validAttacks = Tables::PAWN_ATTACK_TABLE[BLACK][pawnIndex] & myBoard->getWhitePieces() & target;

		/* then we combine the two situations in which a white pawn can legally
		attack/move. */
		// blackPawnValid = (firstStep | twoSteps) | validAttacks; // not needed for now

		addQuietMoves(firstStep  & target & Tables::CLEAR_RANK[0], pawnIndex, moves, Piece::PAWN);
		addDoublePawnPushMoves(twoSteps & Tables::CLEAR_RANK[0], pawnIndex, moves);
		addPromotionMoves(firstStep & Tables::MASK_RANK[0], pawnIndex, moves);
		addCaptureMoves(validAttacks & Tables::CLEAR_RANK[0], pawnIndex, moves, Piece::PAWN);
		addPromotionCaptureMoves(validAttacks & Tables::MASK_RANK[0], pawnIndex, moves);
	}
}

std::vector<Move> MoveGen::generatePseudoLegalMoves()
{
	return generateLegalMoves(myBoard->getColorToPlay());
}

std::vector<Move> MoveGen::generatePseudoLegalMoves(const Color color)
{
	std::vector<Move> legalMoves;
	legalMoves.reserve(218);

	appendPawnPseudoLegalMoves(color, legalMoves);
	appendKingPseudoLegalMoves(color, legalMoves);
	appendQueenPseudoLegalMoves(color, legalMoves);
	appendRookPseudoLegalMoves(color, legalMoves);
	appendBishopPseudoLegalMoves(color, legalMoves);
	appendKnightPseudoLegalMoves(color, legalMoves);

	return legalMoves;
}

//based on https://github.com/mcostalba/Stockfish/blob/master/src/movegen.cpp#L365
std::vector<Move> MoveGen::generateEvasionMoves(const Color color)
{
	std::vector<Move> evasionMoves;

	Color ennemyColor = Utils::getOppositeColor(color);
	U64 sliderAttacks = 0;
	U64 kbb = myBoard->getKing(color);
	Square ksq = msb(kbb);

	U64 kingAttackers = myBoard->getKingAttackers();
	U64 sliderAttackers = kingAttackers & ~myBoard->getPawns(ennemyColor) & ~myBoard->getKnights(ennemyColor);

	//Generate sliders attack of piece(s) that gives checks
	while (sliderAttackers)
	{
		Square checksq = pop_lsb(&sliderAttackers);
		auto line = Tables::LINE_BB[checksq][ksq];
		auto removeKing = line ^ checksq;
		sliderAttacks |= removeKing;
	}

	//Generate evasion move for king
	U64 kingAttacks = myBoard->getKingAttacks(ksq, color);
	U64 kingEvasions = kingAttacks & ~sliderAttacks;

	U64 kingCaptureDestinations = kingEvasions & myBoard->getPieces(ennemyColor);
	U64 kingQuietDestinations = kingEvasions ^ kingCaptureDestinations;

	addQuietMoves(kingQuietDestinations, ksq, evasionMoves, Piece::KING);
	addCaptureMoves(kingCaptureDestinations, ksq, evasionMoves, Piece::KING);

	if(moreThanOne(kingAttackers))
	{
		return evasionMoves;
	}

	//We know there is only one piece that gives check
	//Lets try to generate a moves that capture or blocks the checker piece
	Square checkerSq = msb(kingAttackers);
	U64 target = Tables::IN_BETWEEN[checkerSq][ksq] ^ kingAttackers;

	appendPawnPseudoLegalMoves(color, evasionMoves, target);
	appendKnightPseudoLegalMoves(color, evasionMoves, target);
	appendBishopPseudoLegalMoves(color, evasionMoves, target);
	appendRookPseudoLegalMoves(color, evasionMoves, target);
	appendQueenPseudoLegalMoves(color, evasionMoves, target);

	return evasionMoves;
}

std::vector<Move> MoveGen::generateLegalMoves()
{
	return generateLegalMoves(myBoard->getColorToPlay());
}

std::vector<Move> MoveGen::generateLegalMoves(const Color color)
{
	myBoard->updatePinnedPieces();
	myBoard->updateKingAttackers(myBoard->getColorToPlay());
	bool isCheck = myBoard->isCheck();

	std::vector<Move> moves;

	if(isCheck)
	{
		moves = generateEvasionMoves(color);
	}
	else
	{
		moves = generatePseudoLegalMoves(color);

	}
	moves.erase(std::remove_if(moves.begin(), moves.end(),
			[&](Move move) mutable { return !myBoard->isMoveLegal(move, isCheck); }), moves.end());
	//TODO make this easier to understand..

	return moves;
}

/* Special Moves */
void MoveGen::appendWhiteEnPassantMoves(std::vector<Move>& moves, U64 target) const
{
	U64 validPawns = (myBoard->getWhitePawns() & Tables::MASK_RANK[4]);

	/* Easiest test first */
	if (validPawns == 0) {return;}

	const Move* enemyLastMove(myBoard->getEnemyLastMove());

	if (!enemyLastMove)
	{
		return;
	}
	else if (enemyLastMove->getFlags() == Move::DOUBLE_PAWN_PUSH_FLAG)
	{
		while (validPawns)
		{
			Square enemyDestination = enemyLastMove->getDestination();
			Square validPawnIndex = pop_lsb(&validPawns);

			if (abs(validPawnIndex - enemyDestination) == 1)
			{
				Square destination = static_cast<Square>(enemyDestination+8);
				U64 destinationbb = 0 | 1LL << destination;
				if(destinationbb & target)
				{
					Move epMove(validPawnIndex,destination,Move::EP_CAPTURE_FLAG,Piece::PAWN);
					epMove.setCapturedPieceType(Piece::PAWN);
					moves.push_back(epMove);
				}
			}
		}
	}

	return;
}

void MoveGen::appendBlackEnPassantMoves(std::vector<Move>& moves, U64 target) const
{
	U64 validPawns = (myBoard->getBlackPawns() & Tables::MASK_RANK[3]);

	/* Easiest test first */
	if (validPawns == 0) {return;}

	const Move* enemyLastMove(myBoard->getEnemyLastMove());

	if (!enemyLastMove)
	{
		return;
	}
	else if (enemyLastMove->getFlags() == Move::DOUBLE_PAWN_PUSH_FLAG)
	{
		while (validPawns)
		{
			Square enemyDestination = enemyLastMove->getDestination();
			Square validPawnIndex = pop_lsb(&validPawns);

			if (abs(validPawnIndex - enemyDestination) == 1)
			{
				Square destination = static_cast<Square>(enemyDestination-8);

				U64 destinationbb = 0 | 1LL << destination;
				if(destinationbb & target)
				{
					Move epMove(validPawnIndex, destination, Move::EP_CAPTURE_FLAG, Piece::PAWN);
					epMove.setCapturedPieceType(Piece::PAWN);
					moves.push_back(epMove);
				}
			}
		}

		return;
	}

	return;
}

bool MoveGen::isQueenSideCastlingPossible(const Color color) const
{
	//This return false if the queen side rook or the king has already moved
	bool iQSCP = myBoard->isQueenSideCastlingAllowed(color); //TODO

	if(!iQSCP) return false;

	//check if positions between the rook and the king are free
	const U64 bitBoardToBeFree = color == WHITE ? 14 : 1008806316530991104LL;
	iQSCP &= !(bitBoardToBeFree & myBoard->getAllPieces());

	//check if positions between the rook and the king are not attacked
	Square squareNotTobeAttacked = color == WHITE ? SQ_E1 : SQ_E8;
	iQSCP &= !myBoard->isSquareAttacked(squareNotTobeAttacked, color);

	squareNotTobeAttacked = color == WHITE ? SQ_D1 : SQ_D8;
	iQSCP &= !myBoard->isSquareAttacked(squareNotTobeAttacked, color);

	squareNotTobeAttacked = color == WHITE ? SQ_C1 : SQ_C8;
	iQSCP &= !myBoard->isSquareAttacked(squareNotTobeAttacked, color);

	return iQSCP;
}

bool MoveGen::isKingSideCastlingPossible(const Color color) const
{
	//This return false if the king side rook or the king has already moved
	bool iKSCP = myBoard->isKingSideCastlingAllowed(color);

	if(!iKSCP) return false;

	//check if positions between the rook and the king are free
	const U64 bitBoardToBeFree = color == WHITE ? 96 : 6917529027641081856LL;
	iKSCP &= !(bitBoardToBeFree & myBoard->getAllPieces());

	//check if positions between the rook and the king are not attacked
	Square squareNotTobeAttacked = color == WHITE ? SQ_E1 : SQ_E8;
	iKSCP &= !myBoard->isSquareAttacked(squareNotTobeAttacked, color);

	squareNotTobeAttacked = color == WHITE ? SQ_F1 : SQ_F8;
	iKSCP &= !myBoard->isSquareAttacked(squareNotTobeAttacked, color);

	squareNotTobeAttacked = color == WHITE ? SQ_G1 : SQ_G8;
	iKSCP &= !myBoard->isSquareAttacked(squareNotTobeAttacked, color);

	return iKSCP;
}