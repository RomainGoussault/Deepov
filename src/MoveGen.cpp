#include "MoveGen.hpp"

/* Constructor */

MoveGen::MoveGen() : myBoard(nullptr)
{
}

MoveGen(std::shared_ptr<FastBoard> board) : myBoard(board)
{
    myPseudoLegalMoves(getMoves());
}

/* Moves private methods */


void MoveGen::addQuietMoves(U64 quietDestinations, int pieceIndex, std::vector<FastMove>& moves, int pieceType) const
{
	while (quietDestinations)
	{
		//Getting the index of the MSB
		int positionMsb = getMsbIndex(quietDestinations);

		FastMove move = FastMove(pieceIndex, positionMsb, 0, pieceType);
		moves.push_back(move);

		//Removing the MSB
		quietDestinations = quietDestinations ^ (0 | 1LL << positionMsb);
	}
}

void MoveGen::addCaptureMoves(U64 captureDestinations, int pieceIndex, std::vector<FastMove>& moves, int pieceType) const
{
	while (captureDestinations)
	{
		//Getting the index of the MSB
		int positionMsb = getMsbIndex(captureDestinations);
		FastMove move = FastMove(pieceIndex, positionMsb, FastMove::CAPTURE_FLAG, pieceType);
        int capturedType(findPieceType(positionMsb,Utils::getOppositeColor(myColorToPlay)));
		move.setCapturedPieceType(capturedType);
		moves.push_back(move);

		//Removing the MSB
		captureDestinations = captureDestinations ^ (0 | 1LL << positionMsb);
	}
}

void MoveGen::addPromotionMoves(U64 promotionDestinations, int pieceIndex, std::vector<FastMove>& moves) const
{
	while (promotionDestinations)
	{
		//Getting the index of the MSB
		int positionMsb = getMsbIndex(promotionDestinations);
		FastMove move = FastMove(pieceIndex, positionMsb, FastMove::PROMOTION_FLAG, FastMove::PAWN_TYPE);
		moves.push_back(move);
		move.setFlags(FastMove::PROMOTION_FLAG+1);
		moves.push_back(move);
		move.setFlags(FastMove::PROMOTION_FLAG+2);
		moves.push_back(move);
		move.setFlags(FastMove::PROMOTION_FLAG+3);
		moves.push_back(move);

		//Removing the MSB
		promotionDestinations = promotionDestinations ^ (0 | 1LL << positionMsb);
	}
}

void MoveGen::addPromotionCaptureMoves(U64 promotionDestinations, int pieceIndex, std::vector<FastMove>& moves) const
{
	while (promotionDestinations)
	{
		//Getting the index of the MSB
		int positionMsb = getMsbIndex(promotionDestinations);
		unsigned int flag = FastMove::PROMOTION_FLAG+FastMove::PROMOTION_FLAG;
		FastMove move = FastMove(pieceIndex, positionMsb, flag, FastMove::PAWN_TYPE);
        int capturedType(findPieceType(positionMsb,Utils::getOppositeColor(myColorToPlay)));
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
std::vector<FastMove> MoveGen::getKingPseudoLegalMoves(const int& color) const
{
	U64 kingPos = color == WHITE ? myWhiteKing : myBlackKing;

    /* Copied from http://pages.cs.wisc.edu/~psilord/blog/data/chess-pages/nonsliding.html */
	/* we can ignore the rank clipping since the overflow/underflow with
		respect to rank simply vanishes. We only care about the file
		overflow/underflow. */
    U64	king_clip_file_h(kingPos & LookUpTables::CLEAR_FILE[7]);
	U64 king_clip_file_a(kingPos & LookUpTables::CLEAR_FILE[0]);

	/* remember the representation of the board in relation to the bitindex
		when looking at these shifts.... There is an error in the source link
		the code is copied from !! */
	U64 NW(king_clip_file_a << 7);
	U64 N(kingPos << 8);
	U64 NE(king_clip_file_h << 9);
	U64 E(king_clip_file_h << 1);

	U64 SE(king_clip_file_h >> 7);
	U64 S(kingPos >> 8);
	U64 SW(king_clip_file_a >> 9);
	U64 W(king_clip_file_a >> 1);

	/* N = north, NW = North West, from King location, etc */
	U64 kingDestinations = NW | N | NE | E | SE | S | SW | W;
	U64 kingValidDestinations = kingDestinations & ~getPieces(color);

	int ennemyColor = Utils::getOppositeColor(color);
	int kingIndex = getMsbIndex(kingPos);
	std::vector<FastMove> kingMoves;

	U64 kingCaptureDestinations = kingValidDestinations & getPieces(ennemyColor);
	U64 kingQuietDestinations = kingValidDestinations ^ kingCaptureDestinations;

	addQuietMoves(kingQuietDestinations, kingIndex, kingMoves, FastMove::KING_TYPE);
	addCaptureMoves(kingCaptureDestinations,kingIndex, kingMoves, FastMove::KING_TYPE);

	return kingMoves;
}


std::vector<FastMove> MoveGen::getQueenPseudoLegalMoves(const int& color) const
{
	std::vector<FastMove> queenMoves;
	U64 queenPositions = color == WHITE ? myWhiteQueens : myBlackQueens;

	//loop through the queens:
	while(queenPositions)
	{
		int queenIndex = getMsbIndex(queenPositions);
		queenPositions = queenPositions ^ ( 0 | 1LL << queenIndex);

		int ennemyColor = Utils::getOppositeColor(color);

		U64 bishopDestinations = Bmagic(queenIndex, myAllPieces) & ~getPieces(color);
		U64 rookDestinations = Rmagic(queenIndex, myAllPieces) & ~getPieces(color);
		U64 queenDestinations = bishopDestinations ^ rookDestinations ;

		U64 queenCaptureDestinations = queenDestinations & getPieces(ennemyColor);
		U64 queenQuietDestinations = queenDestinations ^ queenCaptureDestinations;

		addQuietMoves(queenQuietDestinations, queenIndex, queenMoves, FastMove::QUEEN_TYPE);
		addCaptureMoves(queenCaptureDestinations, queenIndex, queenMoves, FastMove::QUEEN_TYPE);
	}

	return queenMoves;
}

std::vector<FastMove> MoveGen::getBishopPseudoLegalMoves(const int& color) const
{
	std::vector<FastMove> bishopMoves;
	U64 bishopPositions = color == WHITE ? myWhiteBishops : myBlackBishops;

	//loop through the bishops:
	while(bishopPositions)
	{
		int bishopIndex = getMsbIndex(bishopPositions);
		bishopPositions = bishopPositions ^ ( 0 | 1LL << bishopIndex);

		int ennemyColor = Utils::getOppositeColor(color);

		U64 bishopDestinations = Bmagic(bishopIndex, myAllPieces) & ~getPieces(color);

		U64 bishopCaptureDestinations = bishopDestinations & getPieces(ennemyColor);
		U64 bishopQuietDestinations = bishopDestinations ^ bishopCaptureDestinations;

		addQuietMoves(bishopQuietDestinations, bishopIndex, bishopMoves, FastMove::BISHOP_TYPE);
		addCaptureMoves(bishopCaptureDestinations, bishopIndex, bishopMoves, FastMove::BISHOP_TYPE);
	}

	return bishopMoves;
}

std::vector<FastMove> MoveGen::getRookPseudoLegalMoves(const int& color) const
{
	std::vector<FastMove> rookMoves;
	U64 rookPositions = color == WHITE ? myWhiteRooks : myBlackRooks;

	//loop through the rooks:
	while(rookPositions)
	{
		int rookIndex = getMsbIndex(rookPositions);
		rookPositions = rookPositions ^ ( 0 | 1LL << rookIndex);

		int ennemyColor = Utils::getOppositeColor(color);

		U64 rookDestinations = Rmagic(rookIndex, myAllPieces) & ~getPieces(color);

		U64 rookCaptureDestinations = rookDestinations & getPieces(ennemyColor);
		U64 rookQuietDestinations = rookDestinations ^ rookCaptureDestinations;

		addQuietMoves(rookQuietDestinations, rookIndex, rookMoves, FastMove::ROOK_TYPE);
		addCaptureMoves(rookCaptureDestinations, rookIndex, rookMoves, FastMove::ROOK_TYPE);
	}

	return rookMoves;
}

std::vector<FastMove> MoveGen::getPawnPseudoLegalMoves(const int& color) const
{
	if(color == WHITE)
	{
		return getWhitePawnPseudoLegalMoves();
	}
	else
	{
		return getBlackPawnPseudoLegalMoves();
	}
}

std::vector<FastMove> MoveGen::getKnightPseudoLegalMoves(const int& color) const
{
	std::vector<FastMove> knightMoves;

	U64 knightPositions = color == WHITE ? myWhiteKnights : myBlackKnights;

	//loop through the knights:
	while(knightPositions)
	{
		int knightIndex = getMsbIndex(knightPositions);
		U64 knightPos = 0 | 1LL << knightIndex;
		knightPositions = knightPositions ^ ( 0 | 1LL << knightIndex);

		/* we can ignore the rank clipping since the overflow/underflow with
		respect to rank simply vanishes. We only care about the file
		overflow/underflow. */
		U64	knight_clip_file_h(knightPos & LookUpTables::CLEAR_FILE[7]);
		U64 knight_clip_file_a(knightPos & LookUpTables::CLEAR_FILE[0]);

		U64	knight_clip_file_gh(knightPos & LookUpTables::CLEAR_FILE[7] & LookUpTables::CLEAR_FILE[6]);
		U64 knight_clip_file_ab(knightPos & LookUpTables::CLEAR_FILE[0] & LookUpTables::CLEAR_FILE[1]);

		U64 WNW(knight_clip_file_ab << 6);
		U64 NNW(knight_clip_file_a << 15);
		U64 NNE(knight_clip_file_h << 17);
		U64 ENE(knight_clip_file_gh << 10);

		U64 ESE(knight_clip_file_gh >> 6);
		U64 SSE(knight_clip_file_h >> 15);
		U64 SSW(knight_clip_file_a >> 17);
		U64 WSW(knight_clip_file_ab >> 10);

		/* N = north, NW = North West, from knight location, etc */
		U64 knightValidDestinations = (WNW | NNW | NNE | ENE | ESE | SSE | SSW | WSW) & ~getPieces(color);

		/* compute only the places where the knight can move and attack. The caller
		will interpret this as a white or black knight. */

		int ennemyColor = Utils::getOppositeColor(color);

		U64 knightCaptureDestinations = knightValidDestinations & getPieces(ennemyColor);
		U64 knightQuietDestinations = knightValidDestinations ^ knightCaptureDestinations;

		addQuietMoves(knightQuietDestinations, knightIndex, knightMoves, FastMove::KNIGHT_TYPE);
		addCaptureMoves(knightCaptureDestinations, knightIndex, knightMoves, FastMove::KNIGHT_TYPE);
	}

	return knightMoves;
}

std::vector<FastMove> MoveGen::getWhitePawnPseudoLegalMoves() const
{
	std::vector<FastMove> pawnMoves;
    U64 pawnPositions = myWhitePawns;

    while(pawnPositions)
	{
        int pawnIndex = getMsbIndex(pawnPositions);
		U64 pawnPos = 0 | 1LL << pawnIndex;
		pawnPositions = pawnPositions ^ ( 0 | 1LL << pawnIndex);

    /* check the single space in front of the white pawn */
	U64 firstStep = (pawnPos << 8) & ~myAllPieces;

	/* for all moves that came from rank 2 (home row), and passed the above
		filter, thereby being on rank 3, ie. on MASK_RANK[2], check and see if I can move forward
		one more */
	U64 twoSteps = ((firstStep & LookUpTables::MASK_RANK[2]) << 8) & ~myAllPieces;

	/* the union of the movements dictate the possible moves forward
		available */

	U64 whitePawnQuietMoves = firstStep | twoSteps ;

	/* next we calculate the pawn attacks */

	/* check the left side of the pawn, minding the underflow File A */
	U64 leftAttack = (pawnPos & LookUpTables::CLEAR_FILE[0]) << 7;

	/* then check the right side of the pawn, minding the overflow File H */
	U64 rightAttack = (pawnPos & LookUpTables::CLEAR_FILE[7]) << 9;

	/* the union of the left and right attacks together make up all the
        possible attacks
	   Calculate where I can _actually_ attack something */

	U64 validAttacks = (leftAttack | rightAttack) & myBlackPieces;

	/* then we combine the two situations in which a white pawn can legally
		attack/move. */
	// whitePawnValid = (firstStep | twoSteps) | validAttacks; // not needed for now

    addQuietMoves(whitePawnQuietMoves & LookUpTables::CLEAR_RANK[7],pawnIndex, pawnMoves, FastMove::PAWN_TYPE);
    addPromotionMoves(whitePawnQuietMoves & LookUpTables::MASK_RANK[7],pawnIndex, pawnMoves);
    addCaptureMoves(validAttacks & LookUpTables::CLEAR_RANK[7],pawnIndex, pawnMoves, FastMove::PAWN_TYPE);
    addPromotionCaptureMoves(validAttacks & LookUpTables::MASK_RANK[7],pawnIndex, pawnMoves);

	}

	return pawnMoves;
}

std::vector<FastMove> MoveGen::getBlackPawnPseudoLegalMoves() const
{
	std::vector<FastMove> pawnMoves;
    U64 pawnPositions = myBlackPawns;

    while(pawnPositions)
	{
        int pawnIndex = getMsbIndex(pawnPositions);
		U64 pawnPos = 0 | 1LL << pawnIndex;
		pawnPositions = pawnPositions ^ ( 0 | 1LL << pawnIndex);

    /* check the single space in front of the white pawn */
	U64 firstStep = (pawnPos >> 8) & ~myAllPieces;

	/* for all moves that came from rank 7 (home row), and passed the above
		filter, thereby being on rank 6, ie. on MASK_RANK[5], check and see if I can move forward
		one more */
	U64 twoSteps = ((firstStep & LookUpTables::MASK_RANK[5]) >> 8) & ~myAllPieces;

	/* the union of the movements dictate the possible moves forward
		available */

	U64 blackPawnQuietMoves = firstStep | twoSteps ;

	/* next we calculate the pawn attacks */

	/* check the left side of the pawn, minding the underflow File A */
	U64 leftAttack = (pawnPos & LookUpTables::CLEAR_FILE[7]) >> 7;

	/* then check the right side of the pawn, minding the overflow File H */
	U64 rightAttack = (pawnPos & LookUpTables::CLEAR_FILE[0]) >> 9;

	/* the union of the left and right attacks together make up all the
        possible attacks
	   Calculate where I can _actually_ attack something */

	U64 validAttacks = (leftAttack | rightAttack) & myWhitePieces;

	/* then we combine the two situations in which a white pawn can legally
		attack/move. */
	// blackPawnValid = (firstStep | twoSteps) | validAttacks; // not needed for now

    addQuietMoves(blackPawnQuietMoves & LookUpTables::CLEAR_RANK[0],pawnIndex, pawnMoves, FastMove::PAWN_TYPE);
    addPromotionMoves(blackPawnQuietMoves & LookUpTables::MASK_RANK[0],pawnIndex, pawnMoves);
    addCaptureMoves(validAttacks & LookUpTables::CLEAR_RANK[0],pawnIndex, pawnMoves, FastMove::PAWN_TYPE);
    addPromotionCaptureMoves(validAttacks & LookUpTables::MASK_RANK[0],pawnIndex, pawnMoves);

	}

	return pawnMoves;
}

std::vector<FastMove> MoveGen::getMoves() const
{
    return myMoves;
}
