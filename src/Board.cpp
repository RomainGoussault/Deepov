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

#include "Board.hpp"
#include "Utils.hpp"
#include "BitBoardUtils.hpp"
#include "MagicMoves.hpp"
#include "MoveGen.hpp"
#include "Eval.hpp"

#include <algorithm>


std::mt19937_64 ZK::rdGen;

Zkey ZK::psq[COLOR_NB][Piece::PIECE_TYPE_NB][SQUARE_NB];
Zkey ZK::enPassant[FILE_NB];
Zkey ZK::castling[4];
Zkey ZK::side;

void ZK::initZobristKeys()
{
	rdGen.seed(1);

	for (Color c = WHITE; c <= BLACK; ++c)
	{
		for (Piece::PieceType pt = Piece::PAWN; pt <= Piece::KING; ++pt)
		{
			for (Square s = SQ_A1; s <= SQ_H8; ++s)
			{
				psq[c][pt][s] = rdGen();
			}
		}
	}

	for (int i = 0; i<3; i++)
	{
		castling[i] = rdGen();
	}

	for (File f = FILE_A; f <= FILE_H; ++f)
	{
		enPassant[f] = rdGen();
	}

	side = rdGen();
}


Board::Board() : Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -"){}

Board::Board(const std::string fen) : 
myBitboards(), myAllPieces(), myPinnedPieces(), myCastling(), myHasWhiteCastled(false), myHasBlackCastled(false), myAtkTo(), myKingAttackers()
{
	std::vector<std::string> spaceSplit;
	std::vector<std::string> piecesByRank;

	//Split string
	std::stringstream ss(fen);
	std::string item;
	while (std::getline(ss, item, ' ')) {
		spaceSplit.push_back(item);
	}

	ss = std::stringstream(spaceSplit[0]);
	while (std::getline(ss, item, '/')) {
		piecesByRank.push_back(item);
	}

	unsigned int rank = 7;
	for (unsigned int i=0; i<8; i++)
	{
		setBitBoards(piecesByRank[i], rank);
		rank--;
	}

	updateConvenienceBitboards();

	if (spaceSplit[1][0] == 'w')
	{
		myColorToPlay = WHITE;
	}
	else if (spaceSplit[1][0] == 'b')
	{
		myColorToPlay = BLACK;
	}

	Utils::getCastling(spaceSplit[2], myCastling);

	if ((spaceSplit[3][0] != '-') && (getMovesHistory().size() == 0))
	{
		unsigned int epIndex = getIndexFromChar(spaceSplit[3]);
		Square origin = static_cast<Square>(epIndex + 8 - 16*myColorToPlay);
		Square destination = static_cast<Square>(epIndex - 8 + 16*myColorToPlay);
		Move lastMove(origin, destination, Move::DOUBLE_PAWN_PUSH_FLAG, Piece::PAWN);
		myMoves.push_back(lastMove);
	}

	if (spaceSplit[3][0] != '-')
    {
        unsigned int epIndex = getIndexFromChar(spaceSplit[3]);
        Square epsquare = static_cast<Square>(epIndex);
        myEpSquares.push_back(epsquare);
    }
    else
    {
        myEpSquares.push_back(SQ_NONE);
    }

	// I put a condition in case the FEN format doesn't include the move counters
	if (spaceSplit.size() >= 5)
	{
		myMovesCounter = Utils::convertStringToInt(spaceSplit[4]);
		//  Waiting for a fix for windows! Ahaha a link to the error maybe?
		//	myMovesCounter = std::stoi(spaceSplit[4]);
	}
	else
	{
		myMovesCounter = 0;
	}

	if (spaceSplit.size() >= 6)
	{
		myHalfMovesCounter = Utils::convertStringToInt(spaceSplit[5]);
		//	myHalfMovesCounter = std::stoi(spaceSplit[5]);
	}
	else
	{
		myHalfMovesCounter = 0;
	}

    // pawnsKey = 0;
    // key = 0;
}


Piece::PieceType Board::findBlackPieceType(const Square position) const
{
	if (myBitboards[6]&(1LL << position))
	{
		return Piece::PAWN;
	}
	else if (myBitboards[7]&(1LL << position))
	{
		return Piece::KNIGHT;
	}
	else if (myBitboards[8]&(1LL << position))
	{
		return Piece::BISHOP;
	}
	else if (myBitboards[9]&(1LL << position))
	{
		return Piece::ROOK;
	}
	else if (myBitboards[10]&(1LL << position))
	{
		return Piece::QUEEN;
	}
	else if (myBitboards[11]&(1LL << position))
	{
		return Piece::KING;
	}
	else
	{
		return Piece::NO_PIECE_TYPE;
	}
}

Piece::PieceType Board::findWhitePieceType(const Square position) const
{
	if (myBitboards[0]&(1LL << position))
	{
		return Piece::PAWN;
	}
	else if (myBitboards[1]&(1LL << position))
	{
		return Piece::KNIGHT;
	}
	else if (myBitboards[2]&(1LL << position))
	{
		return Piece::BISHOP;
	}
	else if (myBitboards[3]&(1LL << position))
	{
		return Piece::ROOK;
	}
	else if (myBitboards[4]&(1LL << position))
	{
		return Piece::QUEEN;
	}
	else if (myBitboards[5]&(1LL << position))
	{
		return Piece::KING;
	}
	else
	{
		return Piece::NO_PIECE_TYPE;
	}
}

/**
 * This method returns an unsigned int between 0 and 5 representing the type
 *  of the piece at the given position (MSB index) and for the given
 *  color.
 */
Piece::PieceType Board::findPieceType(const Square position, const Color color) const
{
	if(color == WHITE)
	{
		return findWhitePieceType(position);
	}
	else
	{
		return findBlackPieceType(position);
	}
}

Piece::Piece Board::findPieceType(const Square position) const
{
	Piece::PieceType whiteType = findWhitePieceType(position);
	Piece::PieceType blackType = findBlackPieceType(position);

	return static_cast<Piece::Piece>(whiteType + blackType*(whiteType == 6));
	//  = whiteType if piece is white, = 6+blackType if piece is black
}

bool Board::isMoveLegal(Move &move, bool isCheckb)
{
	bool isLegalMove = true;
	bool isEnPassant = move.getFlags() == Move::EP_CAPTURE_FLAG;
	Color color = myColorToPlay;

	Square origin = move.getOrigin();
	U64 oribb = 1LL << origin;
	bool isPinned = oribb & getPinnedPieces();
	bool isKingMove = move.getPieceType() == Piece::KING;

	if(isPinned)
	{
		//If piece is pinned it can only move on the line defined by him and the king
		Square destination = move.getDestination();
		Square ksq = getKingSquare(myColorToPlay);

		return  BitBoardUtils::areAligned(origin, destination, ksq);
	}
	else if(isKingMove)
	{
		return !isSquareAttacked(move.getDestination(), myColorToPlay);
	}
	if (isCheckb || isEnPassant)
	{
		executeMove(move);
		updateKingAttackers(color);
		if(isCheck())
		{
			isLegalMove = false;
		}

		undoMove(move);
	}

	return isLegalMove;
}

void Board::updateKingAttackers(const Color color)
{
	U64 kingPosition = getKing(color);
	Square kingSquare = msb(kingPosition);

	//update myKingAttackers field;
	myKingAttackers = getAttackersTo(kingSquare, color);
}

bool Board::isSquareAttacked(Square square, Color color) const
{
	Color enemyColor = Utils::getOppositeColor(color);
	if (Tables::PAWN_ATTACK_TABLE[color][square] & getPawns(enemyColor))
	{
		return true;
	}
	else if (Tables::ATTACK_TABLE[Piece::KNIGHT][square] & getKnights(enemyColor))
	{
		return true;
	}
	else if (Tables::ATTACK_TABLE[Piece::KING][square] & getKing(enemyColor))
	{
		return true;
	}

	U64 potentialAttackers = MagicMoves::Bmagic(square, getAllPieces());
	if (potentialAttackers & (getBishops(enemyColor) | getQueens(enemyColor)))
	{
		return true;
	}

	potentialAttackers = MagicMoves::Rmagic(square, getAllPieces());
	if (potentialAttackers & (getRooks(enemyColor) | getQueens(enemyColor)))
	{
		return true;
	}

	return false;
}

U64 Board::getAttackersTo(Square sq, Color color) const
{
	U64 atkTo = 0;

	Color enemyColor = Utils::getOppositeColor(color);
	atkTo |= (Tables::PAWN_ATTACK_TABLE[color][sq] & getPawns(enemyColor));
	atkTo |= (Tables::ATTACK_TABLE[Piece::KNIGHT][sq] & getKnights(enemyColor));
	atkTo |= (Tables::ATTACK_TABLE[Piece::KING][sq] & getKing(enemyColor));

	U64 potentialAttackers = MagicMoves::Bmagic(sq, getAllPieces()) & ~getPieces(color);
	atkTo |= (potentialAttackers & (getBishops(enemyColor) | getQueens(enemyColor)));

	potentialAttackers = MagicMoves::Rmagic(sq, getAllPieces()) & ~getPieces(color);
	atkTo |= (potentialAttackers & (getRooks(enemyColor) | getQueens(enemyColor)));

	return atkTo;
}

U64 Board::getAttackersTo(Square sq, Color color, U64 occ) const
{
	U64 atkTo = 0;

	Color enemyColor = Utils::getOppositeColor(color);
	atkTo |= (Tables::PAWN_ATTACK_TABLE[color][sq] & getPawns(enemyColor));
	atkTo |= (Tables::ATTACK_TABLE[Piece::KNIGHT][sq] & getKnights(enemyColor));
	atkTo |= (Tables::ATTACK_TABLE[Piece::KING][sq] & getKing(enemyColor));

	U64 potentialAttackers = MagicMoves::Bmagic(sq, occ) & ~getPieces(color);
	atkTo |= (potentialAttackers & (getBishops(enemyColor) | getQueens(enemyColor)));

	potentialAttackers = MagicMoves::Rmagic(sq, occ) & ~getPieces(color);
	atkTo |= (potentialAttackers & (getRooks(enemyColor) | getQueens(enemyColor)));

	return atkTo;
}

void Board::executeMove(Move &move)
{
	Square origin = move.getOrigin();
	Square destination = move.getDestination();
	unsigned int pieceType = move.getPieceType();
	Color oppositeColor = Utils::getOppositeColor(myColorToPlay);

	if(move.isQuiet())
	{
		movePiece(origin, destination, pieceType, myColorToPlay);
	}
	else //Castling or Promotion or Capture
	{
		if(move.isCastling())
		{
			//move King
			movePiece(origin, destination, pieceType, myColorToPlay);

			Square rookOrigin = SQ_NONE;
			Square rookDestination = SQ_NONE;

			if(move.isKingSideCastling())
			{
				if(myColorToPlay == WHITE)
				{
					myHasWhiteCastled = true;
					rookOrigin = SQ_H1;
					rookDestination = SQ_F1;
				}
				else
				{
					myHasBlackCastled = true;
					rookOrigin = SQ_H8;
					rookDestination = SQ_F8;
				}
			}
			else // QueenSideCastling
			{
				if(myColorToPlay == WHITE)
				{
					myHasWhiteCastled = true;
					rookOrigin = SQ_A1;
					rookDestination = SQ_D1;
				}
				else
				{
					myHasBlackCastled = true;
					rookOrigin = SQ_A8;
					rookDestination = SQ_D8;
				}
			}

			//move rook
			movePiece(rookOrigin, rookDestination, Piece::ROOK, myColorToPlay);
		}
		else if (move.isPromotion())
		{
			unsigned int promotedType = move.getPromotedPieceType();

			if(move.isCapture())
			{
				//remove the captured piece
				unsigned int capturedPieceType = move.getCapturedPieceType();
				removePiece(destination, capturedPieceType, oppositeColor);
			}

			removePiece(origin, Piece::PAWN, myColorToPlay);
			addPiece(destination, promotedType, myColorToPlay);
		}
		else
		{
			if (move.isEnPassant()) // watch out ep capture is a capture
			{
				Square capturedPawnIndex = static_cast<Square>(move.getDestination() - 8 + 16*myColorToPlay);
				removePiece(capturedPawnIndex, Piece::PAWN, oppositeColor);
			}
			else //Move is capture
			{
				//remove the captured piece
				unsigned int type(move.getCapturedPieceType());
				removePiece(destination, type, oppositeColor);
			}

			movePiece(origin, destination, pieceType, myColorToPlay);
		}
	}

    /*    Update EP square  */
    Square lastEpSquare = getLastEpSquare();
    // Cancel the ep square in the hash if there was one
    if (lastEpSquare != SQ_NONE)
    {
        key ^= ZK::enPassant[Utils::getFile(lastEpSquare)];
    }

    if (move.isDoublePawnPush())
    {
        myEpSquares.push_back(static_cast<Square>(destination-8+16*myColorToPlay));
        key ^= ZK::enPassant[Utils::getFile(destination)];
    }
    else
    {
        myEpSquares.push_back(SQ_NONE) ;
    }

	updateCastlingRights(move);

	myMovesCounter += myColorToPlay;

	myHalfMovesCounter++;

    // Change the color to play
	myColorToPlay = oppositeColor;
    key ^= ZK::side;
    pawnsKey ^= ZK::side;

	myMoves.push_back(move);
	myKeys.push_back(key);

	updateConvenienceBitboards();
}

void Board::executeNullMove()
{
	Color oppositeColor = Utils::getOppositeColor(myColorToPlay);
	myMovesCounter += myColorToPlay;
	myHalfMovesCounter++;
	myColorToPlay = oppositeColor;
	key ^= ZK::side;
	pawnsKey ^= ZK::side;
	myMoves.push_back(Move());//TODO create constructor for null move?	
	myKeys.push_back(key);
}

void Board::undoNullMove()
{
	Color oppositeColor = Utils::getOppositeColor(myColorToPlay);
	myMovesCounter += myColorToPlay - 1;
	myHalfMovesCounter--;
	myColorToPlay = oppositeColor;
	key ^= ZK::side;
	pawnsKey ^= ZK::side;
	myMoves.pop_back();
	myKeys.pop_back();
}

void Board::undoMove(Move &move)
{
	Square origin = move.getOrigin();
	Square destination = move.getDestination();
	unsigned int pieceType = move.getPieceType();
	Color oppositeColor = Utils::getOppositeColor(myColorToPlay);

	/* Be careful to get the valid move color  */
	rewindCastlingRights(move);

	if(move.isQuiet())
	{
		movePiece(destination, origin, pieceType, oppositeColor);
	}
	else //Castling or Promotion or Capture
	{
		if(move.isCastling())
		{
			//move King
			movePiece(destination, origin, pieceType, oppositeColor);

			Square rookOrigin = SQ_NONE;
			Square rookDestination = SQ_NONE;

			if(move.isKingSideCastling())
			{
				if(oppositeColor == WHITE)
				{
					myHasWhiteCastled = false;
					rookOrigin = SQ_H1;
					rookDestination = SQ_F1;
				}
				else
				{
					myHasBlackCastled = false;
					rookOrigin = SQ_H8;
					rookDestination = SQ_F8;
				}
			}
			else // QueenSideCastling
			{
				if(oppositeColor == WHITE)
				{
					myHasWhiteCastled = false;
					rookOrigin = SQ_A1;
					rookDestination = SQ_D1;
				}
				else
				{
					myHasBlackCastled = false;
					rookOrigin = SQ_A8;
					rookDestination = SQ_D8;
				}
			}

			//move rook
			movePiece(rookDestination, rookOrigin, Piece::ROOK, oppositeColor);
		}
		else if(move.isPromotion())
		{
			unsigned int promotedType = move.getFlags() - Move::PROMOTION_FLAG +1;

			if(move.isCapture())
			{
				promotedType -= Move::CAPTURE_FLAG;
				//add the captured piece
				unsigned int type(move.getCapturedPieceType());
				addPiece(destination, type, myColorToPlay);
			}

			removePiece(destination, promotedType, oppositeColor);
			addPiece(origin, Piece::PAWN, oppositeColor);
		}
		else
		{
			movePiece(destination, origin, pieceType, oppositeColor);

			if (move.isEnPassant()) // watch out ep capture is a capture
			{
				Square capturedPawnIndex = static_cast<Square>(move.getDestination() - 8 + 16*oppositeColor);
				addPiece(capturedPawnIndex, Piece::PAWN, myColorToPlay);
			}
			else //Move is capture
			{
				//add the captured piece
				unsigned int type(move.getCapturedPieceType());
				addPiece(destination, type, myColorToPlay);
			}
		}
	}

    // Update EP square
    if (move.isDoublePawnPush())
    {
        key ^= ZK::enPassant[Utils::getFile(destination)];
    }
    myEpSquares.pop_back();

    Square lastEpSquare = getLastEpSquare();
    // Put the ep square in the hash again if there was one
    if (lastEpSquare != SQ_NONE)
    {
        key ^= ZK::enPassant[Utils::getFile(lastEpSquare)];
    }

	myMovesCounter += myColorToPlay - 1; //-1 only when it's white to play

	myHalfMovesCounter--;

    // Change the color to play
	myColorToPlay = Utils::getOppositeColor(myColorToPlay);
    key ^= ZK::side;
    pawnsKey ^= ZK::side;

	//Remove the last move from the myMoves list.
	myMoves.pop_back();
	myKeys.pop_back();

	updateConvenienceBitboards();
}

void Board::updateConvenienceBitboards()
{
	// White Pieces bitboard
	myBitboards[12] = myBitboards[0] ^ myBitboards[1] ^ myBitboards[2] ^ myBitboards[3] ^ myBitboards[4] ^ myBitboards[5];

	// Black Pieces bitboard
	myBitboards[13] = myBitboards[6] ^ myBitboards[7] ^ myBitboards[8] ^ myBitboards[9] ^ myBitboards[10] ^ myBitboards[11];

	// All Pawns bitboard
	myBitboards[14] = myBitboards[0] ^ myBitboards[6];
	// All Knights bitboard
	myBitboards[15] = myBitboards[1] ^ myBitboards[7];
	// All Bishops bitboard
	myBitboards[16] = myBitboards[2] ^ myBitboards[8];
	// All Rooks bitboard
	myBitboards[17] = myBitboards[3] ^ myBitboards[9];
	// All Queens bitboard
	myBitboards[18] = myBitboards[4] ^ myBitboards[10];
	// All Kings bitboard
	myBitboards[19] = myBitboards[5] ^ myBitboards[11];

	myAllPieces = myBitboards[12] ^ myBitboards[13];
}

//This methods returns the char representing the piece at the given position (file,rank)
char Board::getChar(const unsigned int file, const unsigned int rank) const
{
	char c;

	if (BitBoardUtils::isBitSet(getWhitePawns(), file, rank))
	{
		c = 'P';
	}
	else if (BitBoardUtils::isBitSet(getWhiteKnights(), file, rank))
	{
		c = 'N';
	}
	else if (BitBoardUtils::isBitSet(getWhiteBishops(), file, rank))
	{
		c = 'B';
	}
	else if (BitBoardUtils::isBitSet(getWhiteRooks(), file, rank))
	{
		c = 'R';
	}
	else if (BitBoardUtils::isBitSet(getWhiteQueens(), file, rank))
	{
		c = 'Q';
	}
	else if (BitBoardUtils::isBitSet(getWhiteKing(), file, rank))
	{
		c = 'K';
	}
	else if (BitBoardUtils::isBitSet(getBlackPawns(), file, rank))
	{
		c = 'p';
	}
	else if (BitBoardUtils::isBitSet(getBlackKnights(), file, rank))
	{
		c = 'n';
	}
	else if (BitBoardUtils::isBitSet(getBlackBishops(), file, rank))
	{
		c = 'b';
	}
	else if (BitBoardUtils::isBitSet(getBlackRooks(), file, rank))
	{
		c = 'r';
	}
	else if (BitBoardUtils::isBitSet(getBlackQueens(), file, rank))
	{
		c = 'q';
	}
	else if (BitBoardUtils::isBitSet(getBlackKing(), file, rank))
	{
		c = 'k';
	}
	else {
		c = '*';
	}

	return c;
}

//This methods adds pieces to the board at the given rank and based on the give piecesString
void Board::setBitBoards(const std::string piecesString, const unsigned int rank)
{
	unsigned int x = -1;
	for (const char& pieceChar : piecesString) {

		if(isdigit(pieceChar))
		{
			x += pieceChar - '0';
		}
		else
		{
			x++;

			if (pieceChar == 'K')
			{
				myBitboards[5] |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'R')
			{
				myBitboards[3] |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'B')
			{
				myBitboards[2] |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'Q')
			{
				myBitboards[4] |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'N')
			{
				myBitboards[1] |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'P')
			{
				myBitboards[0] |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'k')
			{
				myBitboards[11] |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'r')
			{
				myBitboards[9] |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'b')
			{
				myBitboards[8] |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'q')
			{
				myBitboards[10] |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'n')
			{
				myBitboards[7] |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'p')
			{
				myBitboards[6]|= 1LL << (8*rank + x);
			}
		}
	}
}

unsigned int Board::perft(unsigned int depth)
{
	unsigned int nodes = 0;

	if (depth == 0)
	{
		return 1;
	}

	MoveGen movegen(*this);
	std::vector<Move> moves(movegen.generateMoves());

	if (moves.empty())
	{
		// std::cout << "Position is mate" <<std::endl;
	}

	for (auto &move : moves)
	{
		executeMove(move);

		nodes += perft(depth - 1);
		undoMove(move);
	}

	return nodes;
}

unsigned int Board::divide(unsigned int depth)
{
	unsigned int nMoves;
	unsigned int nodes = 0;
	unsigned int nodeTotal = 0;

	if (depth == 0)
	{
		return 1;
	}

	MoveGen movegen(*this);
	std::vector<Move> moves(movegen.generateMoves());
	nMoves = moves.size();

	for (auto &move : moves)
	{
		executeMove(move);
		nodes = perft(depth - 1);
		std::cout <<  move.toShortString() <<  " " << nodes << std::endl;
		nodeTotal += nodes;
		undoMove(move);
	}

	std::cout << std::endl;
	std::cout << "Total nodes: " << nodeTotal << std::endl;
	std::cout << "Total moves: " << nMoves << std::endl;
	return nodes;
}

const Move* Board::getEnemyLastMove() const
{
	if (myMoves.size()>0)
	{
		const Move* lastMovePtr = &myMoves.back();
		return lastMovePtr;
	}
	else
	{
		return nullptr;
	}
}

void Board::updateCastlingRights(Move &move)
{
	move.setPreviousCastlingRights(myCastling); // store for undoMove

	/* Update Castling rights for king move */
	unsigned int isKingMove(move.getPieceType() == Piece::KING);
	myCastling &= ~((isKingMove*3) << (myColorToPlay*2));
	/* 0011 = 3 and i shift it by 0 or by 2 , then take the ~ to get the mask*/

	/* Update Castling Rights for rook moves */
	Square origin = move.getOrigin();
	if (((1LL << origin)&Tables::ROOK_INITIAL_POS)!=0)
	{
		// King side produces bit 0, queen side produces bit 1
		unsigned int shift(((~origin)&0b0001) + 2*((origin&0b1000)>>3));
		unsigned int mask = ~(0b0001 << shift);
		myCastling &= mask;
		/* 0001 if this is a rook Move and i shift it by the right amount to mask the bit*/
	}

	Square destination = move.getDestination();
	if (((1LL << destination)&Tables::ROOK_INITIAL_POS)!=0)
	{
		/* Update Castling Rights for rook capture */
		unsigned int shift(((~destination)&0b0001) + 2*((destination&0b1000)>>3));
		unsigned int mask = ~(0b0001 << shift);
		myCastling &= mask;
	}

    // TODO : create a separate function, optimize and test
    /* Did the castling rights change ? If yes, update the zkey */
    unsigned int hasChanged = (myCastling^move.getPreviousCastlingRights()) & 0b1111; 
    // hasChanged bits are 1 if corresponding castling right has changed
    if (hasChanged & 0b0001) key^=(ZK::castling[0]);
    if (hasChanged & 0b0010) key^=(ZK::castling[1]);
    if (hasChanged & 0b0100) key^=(ZK::castling[2]);
    if (hasChanged & 0b1000) key^=(ZK::castling[3]);

}

void Board::rewindCastlingRights(const Move &move)
{

    /* Did the castling rights change ? If yes, update the zkey */
    unsigned int hasChanged = (myCastling^move.getPreviousCastlingRights()) & 0b1111; 
    // hasChanged bits are 1 if corresponding castling right has changed
    if (hasChanged & 0b0001) key^=(ZK::castling[0]);
    if (hasChanged & 0b0010) key^=(ZK::castling[1]);
    if (hasChanged & 0b0100) key^=(ZK::castling[2]);
    if (hasChanged & 0b1000) key^=(ZK::castling[3]);

	myCastling = move.getPreviousCastlingRights();
}

void Board::updatePinnedPieces()
{
	myPinnedPieces = 0LL;
	Color color = getColorToPlay();
	Color oppositeColor = Utils::getOppositeColor(color);
	U64 occ = getAllPieces();
	U64 kiSq = getKingSquare(color);

	U64 rookWise = MagicMoves::Rmagic(kiSq, occ);
	U64 potPinned = rookWise & getPieces(color);
	U64 xrays = rookWise ^ MagicMoves::Rmagic(kiSq, occ ^ potPinned);
	U64 possiblePinners = getRooks(oppositeColor) | getQueens(oppositeColor);
	U64 pinners = xrays & possiblePinners;

	while ( pinners )
	{
		unsigned int pinnerSq = pop_lsb(&pinners);
		myPinnedPieces  |= potPinned & Tables::IN_BETWEEN[pinnerSq][kiSq];
	}

	U64 bishopWise = MagicMoves::Bmagic(kiSq, occ);
	potPinned = bishopWise & getPieces(color);
	xrays = rookWise ^ MagicMoves::Bmagic(kiSq, occ ^ potPinned);
	possiblePinners = getBishops(oppositeColor) | getQueens(oppositeColor);
	pinners = xrays & possiblePinners;

	while ( pinners )
	{
		unsigned int pinnerSq = pop_lsb(&pinners);
		myPinnedPieces  |= potPinned & Tables::IN_BETWEEN[pinnerSq][kiSq];
	}
}

int Board::see(const Square square, Color color)
{
	int score = 0;
	U64 attackers;
	Piece::PieceType pieceType = getSmallestAttacker(square, color, attackers);

	/* skip if the square isn't attacked anymore by this side */
	if (pieceType != Piece::PieceType::NO_PIECE_TYPE)
	{
		Square origin = msb(attackers);
		Move captureMove = Move(origin, square, Move::CAPTURE_FLAG, pieceType);
		Piece::PieceType capturedType = findPieceType(square, color);

		captureMove.setCapturedPieceType(capturedType);

		executeMove(captureMove);

		// Do not consider captures if they lose material, therefore max zero
		//=> We are not forced to do a capture, there should be other moves available
		score = Eval::pieceTypeToValue(captureMove.getCapturedPieceType()) - see(square, Utils::getOppositeColor(color));
		score = std::max(0, score);

		undoMove(captureMove);
	}

	return score;
}

//To statically evaluate a capture, that particular capture should be forced, because it might not be the lowest attacker that makes the capture,
//and must not allow the option of standing pat
int Board::seeCapture(Move captureMove, Color color)
{
	executeMove(captureMove);

	int score = Eval::pieceTypeToValue(captureMove.getCapturedPieceType()) - see(captureMove.getDestination(), Utils::getOppositeColor(color));
	undoMove(captureMove);

   return score;
}

//To statically evaluate a capture, that particular capture should be forced, because it might not be the lowest attacker that makes the capture,
//and must not allow the option of standing pat
int Board::seeCapture2(Move captureMove, Color color)
{
	Square toSq = captureMove.getDestination();
	int gain[32], d = 0;
	U64 mayXray =  getAllPawns() | getAllKnights() | getAllRooks() | getAllQueens();
	U64 fromSet = 1ULL << captureMove.getOrigin();
	U64 occ     = getAllPieces();
	U64 attadef = getAttackersTo(toSq, color, occ) | getAttackersTo(toSq, Utils::getOppositeColor(color), occ); 
	gain[d]     = Eval::pieceTypeToValue(captureMove.getCapturedPieceType());
	
	do {
		d++; // next depth and side
		gain[d]  = Eval::pieceTypeToValue(captureMove.getPieceType()) - gain[d-1]; // speculative store, if defended
		if (std::max(-gain[d-1], gain[d]) < 0) break; // pruning does not influence the result
		attadef ^= fromSet; // reset bit in set to traverse
		occ     ^= fromSet; // reset bit in temporary occupancy (for x-Rays)
		
		if (fromSet & mayXray)
		{
			attadef = getAttackersTo(toSq, color, occ) | getAttackersTo(toSq, Utils::getOppositeColor(color), occ); 
		}

		U64 attackers = attadef;
		color = Utils::getOppositeColor(color);

		//TODO: getSmallestAttacker should :
		// locate the least valuable attacker for the side to move
		//remove the attacker we just found from the bitboards
		// and scan for new X-ray attacks behind it.
		getSmallestAttacker(toSq, Utils::getOppositeColor(color), attackers);


		fromSet = attackers ? 1ULL << attackers : 0;
		std::cout << d << std::endl;

	} while (fromSet);

	while (--d)
	{
	  gain[d-1]= -std::max (-gain[d-1], gain[d]);
	}

	return gain[0];
}

Piece::PieceType Board::getSmallestAttacker(const Square square, Color color, U64 &attackers)
{
	attackers = 0;
	Color enemyColor = Utils::getOppositeColor(color);
	attackers = Tables::PAWN_ATTACK_TABLE[color][square] & getPawns(enemyColor);
	if (attackers)
	{
		return Piece::PieceType::PAWN;
	}

	attackers = Tables::ATTACK_TABLE[Piece::KNIGHT][square] & getKnights(enemyColor);
	if (attackers)
	{
		return Piece::PieceType::KNIGHT;
	}

	U64 potentialBishopAttackers = MagicMoves::Bmagic(square, getAllPieces());
	attackers = potentialBishopAttackers & getBishops(enemyColor);
	if (attackers)
	{
		return Piece::PieceType::BISHOP;
	}

	U64 potentialRookAttackers = MagicMoves::Rmagic(square, getAllPieces());
	attackers = potentialRookAttackers & getRooks(enemyColor);
	if (attackers)
	{
		return Piece::PieceType::ROOK;
	}

	attackers = potentialRookAttackers & getQueens(enemyColor);
	if (attackers)
	{
		return Piece::PieceType::QUEEN;
	}

	attackers = potentialBishopAttackers & getQueens(enemyColor);
	if (attackers)
	{
		return Piece::PieceType::QUEEN;
	}

	attackers = Tables::ATTACK_TABLE[Piece::KING][square] & getKing(enemyColor);
	if (attackers)
	{
		return Piece::PieceType::KING;
	}

	return Piece::PieceType::NO_PIECE_TYPE;
}
