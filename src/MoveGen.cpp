#include "MoveGen.hpp"
#include "MagicMoves.hpp"

/* Constructor */

MoveGen::MoveGen() : myBoard(nullptr)
{
}

MoveGen::MoveGen(std::shared_ptr<FastBoard> board) : myBoard(board)
{
}

/* Moves private methods */

void MoveGen::addQuietMoves(U64 quietDestinations, int pieceIndex, std::vector<FastMove>& moves, int pieceType) const
{
	while (quietDestinations)
	{
		//Getting the index of the MSB
		int positionMsb = FastBoard::getMsbIndex(quietDestinations);

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
		int positionMsb = FastBoard::getMsbIndex(captureDestinations);
		FastMove move = FastMove(pieceIndex, positionMsb, FastMove::CAPTURE_FLAG, pieceType);
        int capturedType(myBoard->findPieceType(positionMsb,Utils::getOppositeColor(myBoard->getColorToPlay())));
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
		int positionMsb = FastBoard::getMsbIndex(promotionDestinations);
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
		int positionMsb = FastBoard::getMsbIndex(promotionDestinations);
		unsigned int flag = FastMove::PROMOTION_FLAG+FastMove::PROMOTION_FLAG;
		FastMove move = FastMove(pieceIndex, positionMsb, flag, FastMove::PAWN_TYPE);
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
std::vector<FastMove> MoveGen::getKingPseudoLegalMoves(const int& color) const
{
	U64 kingPos = color == WHITE ? myBoard->getWhiteKing() : myBoard->getBlackKing();

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
	U64 kingValidDestinations = kingDestinations & ~myBoard->getPieces(color);

	int ennemyColor = Utils::getOppositeColor(color);
	int kingIndex = FastBoard::getMsbIndex(kingPos);
	std::vector<FastMove> kingMoves;

	U64 kingCaptureDestinations = kingValidDestinations & myBoard->getPieces(ennemyColor);
	U64 kingQuietDestinations = kingValidDestinations ^ kingCaptureDestinations;

	addQuietMoves(kingQuietDestinations, kingIndex, kingMoves, FastMove::KING_TYPE);
	addCaptureMoves(kingCaptureDestinations,kingIndex, kingMoves, FastMove::KING_TYPE);

	return kingMoves;
}


std::vector<FastMove> MoveGen::getQueenPseudoLegalMoves(const int& color) const
{
	std::vector<FastMove> queenMoves;
	U64 queenPositions = color == WHITE ? myBoard->getWhiteQueens() : myBoard->getBlackQueens();

	//loop through the queens:
	while(queenPositions)
	{
		int queenIndex = FastBoard::getMsbIndex(queenPositions);
		queenPositions = queenPositions ^ ( 0 | 1LL << queenIndex);

		int ennemyColor = Utils::getOppositeColor(color);

		U64 bishopDestinations = Bmagic(queenIndex, myBoard->getAllPieces()) & ~myBoard->getPieces(color);
		U64 rookDestinations = Rmagic(queenIndex, myBoard->getAllPieces()) & ~myBoard->getPieces(color);
		U64 queenDestinations = bishopDestinations ^ rookDestinations ;

		U64 queenCaptureDestinations = queenDestinations & myBoard->getPieces(ennemyColor);
		U64 queenQuietDestinations = queenDestinations ^ queenCaptureDestinations;

		addQuietMoves(queenQuietDestinations, queenIndex, queenMoves, FastMove::QUEEN_TYPE);
		addCaptureMoves(queenCaptureDestinations, queenIndex, queenMoves, FastMove::QUEEN_TYPE);
	}

	return queenMoves;
}

std::vector<FastMove> MoveGen::getBishopPseudoLegalMoves(const int& color) const
{
	std::vector<FastMove> bishopMoves;
	U64 bishopPositions = color == WHITE ? myBoard->getWhiteBishops() : myBoard->getBlackBishops();

	//loop through the bishops:
	while(bishopPositions)
	{
		int bishopIndex = FastBoard::getMsbIndex(bishopPositions);
		bishopPositions = bishopPositions ^ ( 0 | 1LL << bishopIndex);

		int ennemyColor = Utils::getOppositeColor(color);

		U64 bishopDestinations = Bmagic(bishopIndex, myBoard->getAllPieces()) & ~myBoard->getPieces(color);

		U64 bishopCaptureDestinations = bishopDestinations & myBoard->getPieces(ennemyColor);
		U64 bishopQuietDestinations = bishopDestinations ^ bishopCaptureDestinations;

		addQuietMoves(bishopQuietDestinations, bishopIndex, bishopMoves, FastMove::BISHOP_TYPE);
		addCaptureMoves(bishopCaptureDestinations, bishopIndex, bishopMoves, FastMove::BISHOP_TYPE);
	}

	return bishopMoves;
}

std::vector<FastMove> MoveGen::getRookPseudoLegalMoves(const int& color) const
{
	std::vector<FastMove> rookMoves;
	U64 rookPositions = color == WHITE ? myBoard->getWhiteRooks() : myBoard->getBlackRooks();

	//loop through the rooks:
	while(rookPositions)
	{
		int rookIndex = FastBoard::getMsbIndex(rookPositions);
		rookPositions = rookPositions ^ ( 0 | 1LL << rookIndex);

		int ennemyColor = Utils::getOppositeColor(color);

		U64 rookDestinations = Rmagic(rookIndex, myBoard->getAllPieces()) & ~myBoard->getPieces(color);

		U64 rookCaptureDestinations = rookDestinations & myBoard->getPieces(ennemyColor);
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

	U64 knightPositions = color == WHITE ? myBoard->getWhiteKnights() : myBoard->getBlackKnights();

	//loop through the knights:
	while(knightPositions)
	{
		int knightIndex = FastBoard::getMsbIndex(knightPositions);
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
		U64 knightValidDestinations = (WNW | NNW | NNE | ENE | ESE | SSE | SSW | WSW) & ~myBoard->getPieces(color);

		/* compute only the places where the knight can move and attack. The caller
		will interpret this as a white or black knight. */

		int ennemyColor = Utils::getOppositeColor(color);

		U64 knightCaptureDestinations = knightValidDestinations & myBoard->getPieces(ennemyColor);
		U64 knightQuietDestinations = knightValidDestinations ^ knightCaptureDestinations;

		addQuietMoves(knightQuietDestinations, knightIndex, knightMoves, FastMove::KNIGHT_TYPE);
		addCaptureMoves(knightCaptureDestinations, knightIndex, knightMoves, FastMove::KNIGHT_TYPE);
	}

	return knightMoves;
}

std::vector<FastMove> MoveGen::getWhitePawnPseudoLegalMoves() const
{
	std::vector<FastMove> pawnMoves;
    U64 pawnPositions = myBoard->getWhitePawns();

    while(pawnPositions)
	{
        int pawnIndex = FastBoard::getMsbIndex(pawnPositions);
		U64 pawnPos = 0 | 1LL << pawnIndex;
		pawnPositions = pawnPositions ^ ( 0 | 1LL << pawnIndex);

    /* check the single space in front of the white pawn */
	U64 firstStep = (pawnPos << 8) & ~myBoard->getAllPieces();

	/* for all moves that came from rank 2 (home row), and passed the above
		filter, thereby being on rank 3, ie. on MASK_RANK[2], check and see if I can move forward
		one more */
	U64 twoSteps = ((firstStep & LookUpTables::MASK_RANK[2]) << 8) & ~myBoard->getAllPieces();

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

	U64 validAttacks = (leftAttack | rightAttack) & myBoard->getBlackPieces();

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
    U64 pawnPositions = myBoard->getBlackPawns();

    while(pawnPositions)
	{
        int pawnIndex = FastBoard::getMsbIndex(pawnPositions);
		U64 pawnPos = 0 | 1LL << pawnIndex;
		pawnPositions = pawnPositions ^ ( 0 | 1LL << pawnIndex);

    /* check the single space in front of the white pawn */
	U64 firstStep = (pawnPos >> 8) & ~myBoard->getAllPieces();

	/* for all moves that came from rank 7 (home row), and passed the above
		filter, thereby being on rank 6, ie. on MASK_RANK[5], check and see if I can move forward
		one more */
	U64 twoSteps = ((firstStep & LookUpTables::MASK_RANK[5]) >> 8) & ~myBoard->getAllPieces();

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

	U64 validAttacks = (leftAttack | rightAttack) & myBoard->getWhitePieces();

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


std::vector<FastMove> MoveGen::getLegalMoves()
{
	return getLegalMoves(myBoard->getColorToPlay());
}

std::vector<FastMove> MoveGen::getLegalMoves(const int color)
{
	std::vector<FastMove> legalMoves;

	//TODO we don't want to copy all the moves, better use a reference to the move vector
	std::vector<FastMove> pawnLegalMoves = getPawnPseudoLegalMoves(color);
	std::vector<FastMove> knightLegalMoves = getKnightPseudoLegalMoves(color);
	std::vector<FastMove> bishopLegalMoves = getBishopPseudoLegalMoves(color);
	std::vector<FastMove> rookLegalMoves = getRookPseudoLegalMoves(color);
	std::vector<FastMove> queenLegalMoves = getQueenPseudoLegalMoves(color);
	std::vector<FastMove> kingLegalMoves = getKingPseudoLegalMoves(color);

	legalMoves.insert(legalMoves.end(), pawnLegalMoves.begin(), pawnLegalMoves.end());
	legalMoves.insert(legalMoves.end(), knightLegalMoves.begin(), knightLegalMoves.end());
	legalMoves.insert(legalMoves.end(), bishopLegalMoves.begin(), bishopLegalMoves.end());
	legalMoves.insert(legalMoves.end(), rookLegalMoves.begin(), rookLegalMoves.end());
	legalMoves.insert(legalMoves.end(), queenLegalMoves.begin(), queenLegalMoves.end());
	legalMoves.insert(legalMoves.end(), kingLegalMoves.begin(), kingLegalMoves.end());

	return legalMoves;
}


