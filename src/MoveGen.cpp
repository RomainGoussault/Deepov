#include "MoveGen.hpp"
#include "BitBoardUtils.hpp"
#include "MagicMoves.hpp"
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

void MoveGen::addQuietMoves(U64 quietDestinations, int pieceIndex, std::vector<Move>& moves, int pieceType) const
{
	while (quietDestinations)
	{
		//Getting the index of the MSB
		int positionMsb = BitBoardUtils::getMsbIndex(quietDestinations);

		Move move = Move(pieceIndex, positionMsb, 0, pieceType);
		moves.push_back(move);

		//Removing the MSB
		quietDestinations = quietDestinations ^ (0 | 1LL << positionMsb);
	}
}

void MoveGen::addDoublePawnPushMoves(U64 pawnDestinations, int pieceIndex, std::vector<Move>& moves) const
{
    while (pawnDestinations)
    {
        //Getting the index of the MSB
		int positionMsb = BitBoardUtils::getMsbIndex(pawnDestinations);

        Move move = Move(pieceIndex, positionMsb, Move::DOUBLE_PAWN_PUSH_FLAG, Move::PAWN_TYPE);
		moves.push_back(move);

        //Removing the MSB
		pawnDestinations = pawnDestinations ^ (0 | 1LL << positionMsb);
    }
}

void MoveGen::addCaptureMoves(U64 captureDestinations, int pieceIndex, std::vector<Move>& moves, int pieceType) const
{
	while (captureDestinations)
	{
		//Getting the index of the MSB
		int positionMsb = BitBoardUtils::getMsbIndex(captureDestinations);
		Move move = Move(pieceIndex, positionMsb, Move::CAPTURE_FLAG, pieceType);
        int capturedType(myBoard->findPieceType(positionMsb,Utils::getOppositeColor(myBoard->getColorToPlay())));
		move.setCapturedPieceType(capturedType);
		moves.push_back(move);

		//Removing the MSB
		captureDestinations = captureDestinations ^ (0 | 1LL << positionMsb);
	}
}

void MoveGen::addPromotionMoves(U64 promotionDestinations, int pieceIndex, std::vector<Move>& moves) const
{
	while (promotionDestinations)
	{
		//Getting the index of the MSB
		int positionMsb = BitBoardUtils::getMsbIndex(promotionDestinations);
		Move move = Move(pieceIndex, positionMsb, Move::PROMOTION_FLAG, Move::PAWN_TYPE);
		moves.push_back(move);
		move.setFlags(Move::PROMOTION_FLAG+1);
		moves.push_back(move);
		move.setFlags(Move::PROMOTION_FLAG+2);
		moves.push_back(move);
		move.setFlags(Move::PROMOTION_FLAG+3);
		moves.push_back(move);

		//Removing the MSB
		promotionDestinations = promotionDestinations ^ (0 | 1LL << positionMsb);
	}
}

void MoveGen::addPromotionCaptureMoves(U64 promotionDestinations, int pieceIndex, std::vector<Move>& moves) const
{
	while (promotionDestinations)
	{
		//Getting the index of the MSB
		int positionMsb = BitBoardUtils::getMsbIndex(promotionDestinations);
		unsigned int flag = Move::PROMOTION_FLAG+Move::CAPTURE_FLAG;
		Move move = Move(pieceIndex, positionMsb, flag, Move::PAWN_TYPE);
        int capturedType(myBoard->findPieceType(positionMsb,Utils::getOppositeColor(myBoard->getColorToPlay())));
		move.setCapturedPieceType(capturedType);

		moves.push_back(move);
		move.setFlags(flag+1);
		moves.push_back(move);
		move.setFlags(flag+2);
		moves.push_back(move);
		move.setFlags(flag+3);
		moves.push_back(move);

		//Removing the MSB
		promotionDestinations = promotionDestinations ^ (0 | 1LL << positionMsb);
	}
}

    /* Get moves methods */
void MoveGen::appendKingPseudoLegalMoves(const int& color, std::vector<Move>& moves) const
{
	U64 kingPos = color == WHITE ? myBoard->getWhiteKing() : myBoard->getBlackKing();

	U64 kingValidDestinations = myBoard->getKingDestinations(kingPos, color);

	int ennemyColor = Utils::getOppositeColor(color);
	int kingIndex = BitBoardUtils::getMsbIndex(kingPos);

	U64 kingCaptureDestinations = kingValidDestinations & myBoard->getPieces(ennemyColor);
	U64 kingQuietDestinations = kingValidDestinations ^ kingCaptureDestinations;

	addQuietMoves(kingQuietDestinations, kingIndex, moves, Move::KING_TYPE);
	addCaptureMoves(kingCaptureDestinations, kingIndex, moves, Move::KING_TYPE);
	addKingSideCastlingMove(color, kingIndex, moves);
	addQueenSideCastlingMove(color, kingIndex, moves);
}

void MoveGen::addKingSideCastlingMove(int color, int kingIndex, std::vector<Move>& moves) const
{
	if(isKingSideCastlingPossible(color))
	{
		int destination = color == WHITE ? 6 : 62;
		Move move = Move(kingIndex, destination, Move::KING_SIDE_CASTLING, Move::KING_TYPE);
		moves.push_back(move);
	}
}

void MoveGen::addQueenSideCastlingMove(int color, int kingIndex, std::vector<Move>& moves) const
{
	if(isQueenSideCastlingPossible(color))
	{
		int destination = color == WHITE ? 2 : 58;
		Move move = Move(kingIndex, destination, Move::QUEEN_SIDE_CASTLING, Move::KING_TYPE);
		moves.push_back(move);
	}
}

void MoveGen::appendQueenPseudoLegalMoves(const int& color, std::vector<Move>& moves) const
{
	U64 queenPositions = color == WHITE ? myBoard->getWhiteQueens() : myBoard->getBlackQueens();

	//loop through the queens:
	while(queenPositions)
	{
		int queenIndex = BitBoardUtils::getMsbIndex(queenPositions);
		queenPositions = queenPositions ^ ( 0 | 1LL << queenIndex);

		int ennemyColor = Utils::getOppositeColor(color);

		U64 bishopDestinations = MagicMoves::Bmagic(queenIndex, myBoard->getAllPieces()) & ~myBoard->getPieces(color);
		U64 rookDestinations = MagicMoves::Rmagic(queenIndex, myBoard->getAllPieces()) & ~myBoard->getPieces(color);
		U64 queenDestinations = bishopDestinations ^ rookDestinations ;

		U64 queenCaptureDestinations = queenDestinations & myBoard->getPieces(ennemyColor);
		U64 queenQuietDestinations = queenDestinations ^ queenCaptureDestinations;

		addQuietMoves(queenQuietDestinations, queenIndex, moves, Move::QUEEN_TYPE);
		addCaptureMoves(queenCaptureDestinations, queenIndex, moves, Move::QUEEN_TYPE);
	}
}

void MoveGen::appendBishopPseudoLegalMoves(const int& color, std::vector<Move>& moves) const
{
	U64 bishopPositions = color == WHITE ? myBoard->getWhiteBishops() : myBoard->getBlackBishops();

	//loop through the bishops:
	while(bishopPositions)
	{
		int bishopIndex = BitBoardUtils::getMsbIndex(bishopPositions);
		bishopPositions = bishopPositions ^ ( 0 | 1LL << bishopIndex);

		int ennemyColor = Utils::getOppositeColor(color);

		U64 bishopDestinations = MagicMoves::Bmagic(bishopIndex, myBoard->getAllPieces()) & ~myBoard->getPieces(color);

		U64 bishopCaptureDestinations = bishopDestinations & myBoard->getPieces(ennemyColor);
		U64 bishopQuietDestinations = bishopDestinations ^ bishopCaptureDestinations;

		addQuietMoves(bishopQuietDestinations, bishopIndex, moves, Move::BISHOP_TYPE);
		addCaptureMoves(bishopCaptureDestinations, bishopIndex, moves, Move::BISHOP_TYPE);
	}
}

void MoveGen::appendRookPseudoLegalMoves(const int& color, std::vector<Move>& moves) const
{
	U64 rookPositions = color == WHITE ? myBoard->getWhiteRooks() : myBoard->getBlackRooks();

	//loop through the rooks:
	while(rookPositions)
	{
		int rookIndex = BitBoardUtils::getMsbIndex(rookPositions);
		rookPositions = rookPositions ^ ( 0 | 1LL << rookIndex);

		int ennemyColor = Utils::getOppositeColor(color);

		U64 rookDestinations = MagicMoves::Rmagic(rookIndex, myBoard->getAllPieces()) & ~myBoard->getPieces(color);

		U64 rookCaptureDestinations = rookDestinations & myBoard->getPieces(ennemyColor);
		U64 rookQuietDestinations = rookDestinations ^ rookCaptureDestinations;

		addQuietMoves(rookQuietDestinations, rookIndex, moves, Move::ROOK_TYPE);
		addCaptureMoves(rookCaptureDestinations, rookIndex, moves, Move::ROOK_TYPE);
	}
}
/*
std::vector<Move> MoveGen::getPawnPseudoLegalMoves(const int& color) const
{
	if(color == WHITE)
	{
		return getWhitePawnPseudoLegalMoves();
	}
	else
	{
		return getBlackPawnPseudoLegalMoves();
	}
}*/

void MoveGen::appendPawnPseudoLegalMoves(const int& color, std::vector<Move>& moves) const
{
	if(color == WHITE)
	{
		appendWhitePawnPseudoLegalMoves(moves);
	}
	else
	{
		appendBlackPawnPseudoLegalMoves(moves);
	}
}
void MoveGen::appendKnightPseudoLegalMoves(const int& color, std::vector<Move>& moves) const
{
	U64 knightPositions = color == WHITE ? myBoard->getWhiteKnights() : myBoard->getBlackKnights();

	//loop through the knights:
	while(knightPositions)
	{
		const int knightIndex = BitBoardUtils::getMsbIndex(knightPositions);
		U64 knightValidDestinations = myBoard->getKnightDestinations(knightIndex, color);
		/* compute only the places where the knight can move and attack. The caller
		will interpret this as a white or black knight. */

		int ennemyColor = Utils::getOppositeColor(color);

		U64 knightCaptureDestinations = knightValidDestinations & myBoard->getPieces(ennemyColor);
		U64 knightQuietDestinations = knightValidDestinations ^ knightCaptureDestinations;

		addQuietMoves(knightQuietDestinations, knightIndex, moves, Move::KNIGHT_TYPE);
		addCaptureMoves(knightCaptureDestinations, knightIndex, moves, Move::KNIGHT_TYPE);

		knightPositions = knightPositions ^ ( 0 | 1LL << knightIndex);
	}
}

void MoveGen::appendWhitePawnPseudoLegalMoves(std::vector<Move>& moves) const
{
	moves = getWhiteEnPassantMoves();
	U64 pawnPositions = myBoard->getWhitePawns();

	while(pawnPositions)
	{
		int pawnIndex = BitBoardUtils::getMsbIndex(pawnPositions);
		U64 pawnPos = 0 | 1LL << pawnIndex;
		pawnPositions = pawnPositions ^ ( 0 | 1LL << pawnIndex);

		/* check the single space in front of the white pawn */
		U64 firstStep = (pawnPos << 8) & ~myBoard->getAllPieces();

		/* for all moves that came from rank 2 (home row), and passed the above
		filter, thereby being on rank 3, ie. on MASK_RANK[2], check and see if I can move forward
		one more */
		U64 twoSteps = ((firstStep & LookUpTables::MASK_RANK[2]) << 8) & ~myBoard->getAllPieces();

		/* next we calculate the pawn attacks */

		/* check the left side of the pawn, minding the underflow File A */
		U64 leftAttack = (pawnPos & LookUpTables::CLEAR_FILE[0]) << 7;

		/* then check the right side of the pawn, minding the overflow File H */
		U64 rightAttack = (pawnPos & LookUpTables::CLEAR_FILE[7]) << 9;

		/* the union of the left and right attacks together make up all the
        possible attacks
	   Calculate where I can _actually_ attack something */

		U64 validAttacks = (leftAttack | rightAttack) & myBoard->getBlackPieces();

		/* then we combine the two situations in which a white pawn can legally
		attack/move. */
		// whitePawnValid = (firstStep | twoSteps) | validAttacks; // not needed for now

		addQuietMoves(firstStep & LookUpTables::CLEAR_RANK[7], pawnIndex, moves, Move::PAWN_TYPE);
		addDoublePawnPushMoves(twoSteps & LookUpTables::CLEAR_RANK[7], pawnIndex, moves);
		addPromotionMoves(firstStep & LookUpTables::MASK_RANK[7], pawnIndex, moves);
		addCaptureMoves(validAttacks & LookUpTables::CLEAR_RANK[7], pawnIndex, moves, Move::PAWN_TYPE);
		addPromotionCaptureMoves(validAttacks & LookUpTables::MASK_RANK[7], pawnIndex, moves);
	}
}

void MoveGen::appendBlackPawnPseudoLegalMoves(std::vector<Move>& moves) const
{
	moves = getBlackEnPassantMoves();
	U64 pawnPositions = myBoard->getBlackPawns();

	while(pawnPositions)
	{
		int pawnIndex = BitBoardUtils::getMsbIndex(pawnPositions);
		U64 pawnPos = 0 | 1LL << pawnIndex;
		pawnPositions = pawnPositions ^ ( 0 | 1LL << pawnIndex);

		/* check the single space in front of the white pawn */
		U64 firstStep = (pawnPos >> 8) & ~myBoard->getAllPieces();

		/* for all moves that came from rank 7 (home row), and passed the above
		filter, thereby being on rank 6, ie. on MASK_RANK[5], check and see if I can move forward
		one more */
		U64 twoSteps = ((firstStep & LookUpTables::MASK_RANK[5]) >> 8) & ~myBoard->getAllPieces();

		/* next we calculate the pawn attacks */

		/* check the left side of the pawn, minding the underflow File A */
		U64 leftAttack = (pawnPos & LookUpTables::CLEAR_FILE[7]) >> 7;

		/* then check the right side of the pawn, minding the overflow File H */
		U64 rightAttack = (pawnPos & LookUpTables::CLEAR_FILE[0]) >> 9;

		/* the union of the left and right attacks together make up all the
        possible attacks
	   Calculate where I can _actually_ attack something */

		U64 validAttacks = (leftAttack | rightAttack) & myBoard->getWhitePieces();

		/* then we combine the two situations in which a white pawn can legally
		attack/move. */
		// blackPawnValid = (firstStep | twoSteps) | validAttacks; // not needed for now

		addQuietMoves(firstStep & LookUpTables::CLEAR_RANK[0], pawnIndex, moves, Move::PAWN_TYPE);
		addDoublePawnPushMoves(twoSteps & LookUpTables::CLEAR_RANK[0], pawnIndex, moves);
		addPromotionMoves(firstStep & LookUpTables::MASK_RANK[0], pawnIndex, moves);
		addCaptureMoves(validAttacks & LookUpTables::CLEAR_RANK[0], pawnIndex, moves, Move::PAWN_TYPE);
		addPromotionCaptureMoves(validAttacks & LookUpTables::MASK_RANK[0], pawnIndex, moves);
	}
}

std::vector<Move> MoveGen::getPseudoLegalMoves()
{
	return getLegalMoves(myBoard->getColorToPlay());
}

std::vector<Move> MoveGen::getPseudoLegalMoves(const int color)
{
	std::vector<Move> legalMoves;
	legalMoves.reserve(218);

	//Pawn need to be first
	appendPawnPseudoLegalMoves(color, legalMoves);
	appendKingPseudoLegalMoves(color, legalMoves);
	appendQueenPseudoLegalMoves(color, legalMoves);
	appendRookPseudoLegalMoves(color, legalMoves);
	appendBishopPseudoLegalMoves(color, legalMoves);
	appendKnightPseudoLegalMoves(color, legalMoves);

	return legalMoves;
}

std::vector<Move> MoveGen::getLegalMoves()
{
	return getLegalMoves(myBoard->getColorToPlay());
}

std::vector<Move> MoveGen::getLegalMoves(const int color)
{
	std::vector<Move> moves = getPseudoLegalMoves(color);

	myBoard->updatePinnedPieces();
	bool isCheck = myBoard->isCheck(myBoard->getColorToPlay());

	moves.erase(std::remove_if(moves.begin(), moves.end(),
			[&](Move move) mutable { return !myBoard->isMoveLegal(move, isCheck); }), moves.end());
	//TODO make this easier to understand..

	return moves;
}

  /* Special Moves */
std::vector<Move> MoveGen::getWhiteEnPassantMoves() const
{
	std::vector<Move> enPassantMoves;
	U64 validPawns = (myBoard->getWhitePawns() & LookUpTables::MASK_RANK[4]);

	/* Easiest test first */
	if (validPawns == 0) {return enPassantMoves;}

    boost::optional<Move> enemyLastMove(myBoard->getEnemyLastMove());

    if (!enemyLastMove)
    {
        return enPassantMoves;
    }
    else if (enemyLastMove->getFlags() == Move::DOUBLE_PAWN_PUSH_FLAG)
    {
        while (validPawns)
        {
            unsigned int enemyDestination = enemyLastMove->getDestination();
            int validPawnIndex = BitBoardUtils::getMsbIndex(validPawns);
            validPawns = validPawns ^ ( 0 | 1LL << validPawnIndex); // reset the pawn to 0

            if (abs(validPawnIndex - enemyDestination) == 1)
            {
                Move epMove(validPawnIndex,enemyDestination+8,Move::EP_CAPTURE_FLAG,Move::PAWN_TYPE);
                epMove.setCapturedPieceType(Move::PAWN_TYPE);
                enPassantMoves.push_back(epMove);
            }
        }
    }

    return enPassantMoves;
}

std::vector<Move> MoveGen::getBlackEnPassantMoves() const
{
	std::vector<Move> enPassantMoves;
	U64 validPawns = (myBoard->getBlackPawns() & LookUpTables::MASK_RANK[3]);

	/* Easiest test first */
	if (validPawns == 0) {return enPassantMoves;}

    boost::optional<Move> enemyLastMove(myBoard->getEnemyLastMove());

    if (!enemyLastMove)
    {
        return enPassantMoves;
    }
	else if (enemyLastMove->getFlags() == Move::DOUBLE_PAWN_PUSH_FLAG)
	{
        while (validPawns)
        {
            unsigned int enemyDestination = enemyLastMove->getDestination();
            int validPawnIndex = BitBoardUtils::getMsbIndex(validPawns);
            validPawns = validPawns ^ ( 0 | 1LL << validPawnIndex);

            if (abs(validPawnIndex - enemyDestination) == 1)
            {
                Move epMove(validPawnIndex,enemyDestination-8,Move::EP_CAPTURE_FLAG,Move::PAWN_TYPE);
                epMove.setCapturedPieceType(Move::PAWN_TYPE);
                enPassantMoves.push_back(epMove);
            }
        }

		return enPassantMoves;
	}

	return enPassantMoves;
}

bool MoveGen::isQueenSideCastlingPossible(const int color) const
{
	//This return false if the queen side rook or the king has already moved
	bool iQSCP = myBoard->isQueenSideCastlingAllowed(color); //TODO

	if(!iQSCP) return false;

	int ennemyColor = color == WHITE ? BLACK : WHITE;
	U64 attackedPositions = myBoard->getAttackedPositions(ennemyColor);

	//check if positions between the rook and the king are not attacked
	const U64 bitBoardNotTobeAttacked = color == WHITE ? 28 : 2017612633061982208LL;
	iQSCP &= !(bitBoardNotTobeAttacked & attackedPositions);

	//check if positions between the rook and the king are free
	const U64 bitBoardToBeFree = color == WHITE ? 14 : 1008806316530991104LL;
	iQSCP &= !(bitBoardToBeFree & myBoard->getAllPieces());

	return iQSCP;
}

bool MoveGen::isKingSideCastlingPossible(const int color) const
{
	//This return false if the king side rook or the king has already moved
	bool iKSCP = myBoard->isKingSideCastlingAllowed(color);

	if(!iKSCP) return false;

	int ennemyColor = color == WHITE ? BLACK : WHITE;
	U64 attackedPositions = myBoard->getAttackedPositions(ennemyColor);

	//check if positions between the rook and the king are not attacked
	const U64 bitBoardNotTobeAttacked = color == WHITE ? 112 : 8070450532247928832LL;
	iKSCP &= !(bitBoardNotTobeAttacked & attackedPositions);

	//check if positions between the rook and the king are free
	const U64 bitBoardToBeFree = color == WHITE ? 96 : 6917529027641081856LL;
	iKSCP &= !(bitBoardToBeFree & myBoard->getAllPieces());

	return iKSCP;
}
