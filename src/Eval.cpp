#include "Eval.hpp"

Eval::Eval(std::shared_ptr<Board> boardPtr)
{
    myBoard = boardPtr;
    init();
}

int Eval::evaluate()
{
	//int is too small to contain the following values
	//Note that: 0 <= myGameStage <= TOTAL_MATERIAL

	int64_t alpha =  TOTAL_MATERIAL-myGameStage;
	int64_t openingValue = myOpeningPSQValue*myGameStage;
	int64_t endGameValue = myEndgamePSQValue*alpha;
	int64_t diff = openingValue + endGameValue;
	int positionScore =  diff/TOTAL_MATERIAL;

	myBoard->updateAtkFr();
	int mobilityScore = calcMobilityScore(alpha);
	int materialScore = myMaterialScore;// + calcMaterialAdjustments(alpha);

	//int pawnScore = Pawn::pawnScore(*myBoard,myGameStage,alpha);

	return materialScore + positionScore + mobilityScore;
}

void Eval::init()
{
    /* These values are for the initial position :
    myMaterialScore = 0
    myGameStage = TOTAL_MATERIAL;
    myPSQvalue = 0;  */

    // Calulate Material Score
    myMaterialScore = getWhitePiecesValue() - getBlackPiecesValue();

    // Calculate game stage
    /* Currently it is a simple linear interpolation with material score but this will be upgraded */
   // int TOTAL_MATERIAL = 16*PAWN_VALUE + 4*KNIGHT_VALUE + 4*BISHOP_VALUE + 4*ROOK_VALUE + 2*QUEEN_VALUE;
    myGameStage = (getWhitePiecesValue() + getBlackPiecesValue() - 2*Piece::KING_VALUE);

    // Calculate initial PSQ value
    /* Maybe there is a simpler way to calculate all this ? */
    int whiteOpeningValue(0); int blackOpeningValue(0);
    int whiteEndgameValue(0); int blackEndgameValue(0);
    // WHITE
    // PAWNS
    U64 myPos(myBoard->getWhitePawns());
    while(myPos)
	{
		int myIndex = BitBoardUtils::msb(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
		whiteOpeningValue+=EvalTables::AllPSQT[WHITE][0][0][myIndex];
		whiteEndgameValue+=EvalTables::AllPSQT[WHITE][1][0][myIndex];
	}

    //KNIGHTS
	myPos=myBoard->getWhiteKnights();
    while(myPos)
	{
		int myIndex = BitBoardUtils::msb(myPos);
        myPos = myPos ^ ( 0 | 1LL << myIndex);
		whiteOpeningValue+=EvalTables::AllPSQT[WHITE][0][1][myIndex];
		whiteEndgameValue+=EvalTables::AllPSQT[WHITE][1][1][myIndex];
    }
    //BISHOPS
	myPos=myBoard->getWhiteBishops();
    while(myPos)
	{
		int myIndex = BitBoardUtils::msb(myPos);
        myPos = myPos ^ ( 0 | 1LL << myIndex);
		whiteOpeningValue+=EvalTables::AllPSQT[WHITE][0][2][myIndex];
		whiteEndgameValue+=EvalTables::AllPSQT[WHITE][1][2][myIndex];
	}
    //ROOK
	myPos=myBoard->getWhiteRooks();
    while(myPos)
	{
		int myIndex = BitBoardUtils::msb(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
		whiteOpeningValue+=EvalTables::AllPSQT[WHITE][0][3][myIndex];
		whiteEndgameValue+=EvalTables::AllPSQT[WHITE][1][3][myIndex];
	}
    //QUEEN
	myPos=myBoard->getWhiteQueens();
    while(myPos)
	{
		int myIndex = BitBoardUtils::msb(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
        whiteOpeningValue+=EvalTables::AllPSQT[WHITE][0][4][myIndex];
		whiteEndgameValue+=EvalTables::AllPSQT[WHITE][1][4][myIndex];
	}
    //KING
	myPos=myBoard->getWhiteKing();
    while(myPos)
	{
		int myIndex = BitBoardUtils::msb(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
        whiteOpeningValue+=EvalTables::AllPSQT[WHITE][0][5][myIndex];
		whiteEndgameValue+=EvalTables::AllPSQT[WHITE][1][5][myIndex];
	}

    // BLACK
    // PAWNS
    myPos=myBoard->getBlackPawns();
    while(myPos)
	{
		int myIndex = BitBoardUtils::msb(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
        blackOpeningValue+=EvalTables::AllPSQT[BLACK][0][0][myIndex];
		blackEndgameValue+=EvalTables::AllPSQT[BLACK][1][0][myIndex];
	}

    //KNIGHTS
	myPos=myBoard->getBlackKnights();
    while(myPos)
	{
		int myIndex = BitBoardUtils::msb(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
        blackOpeningValue+=EvalTables::AllPSQT[BLACK][0][1][myIndex];
		blackEndgameValue+=EvalTables::AllPSQT[BLACK][1][1][myIndex];
	}
    //BISHOPS
	myPos=myBoard->getBlackBishops();
    while(myPos)
	{
		int myIndex = BitBoardUtils::msb(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
        blackOpeningValue+=EvalTables::AllPSQT[BLACK][0][2][myIndex];
		blackEndgameValue+=EvalTables::AllPSQT[BLACK][1][2][myIndex];	}
    //ROOK
	myPos=myBoard->getBlackRooks();
    while(myPos)
	{
		int myIndex = BitBoardUtils::msb(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
        blackOpeningValue+=EvalTables::AllPSQT[BLACK][0][3][myIndex];
		blackEndgameValue+=EvalTables::AllPSQT[BLACK][1][3][myIndex];	}
    //QUEEN
	myPos=myBoard->getBlackQueens();
    while(myPos)
	{
		int myIndex = BitBoardUtils::msb(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
        blackOpeningValue+=EvalTables::AllPSQT[BLACK][0][4][myIndex];
		blackEndgameValue+=EvalTables::AllPSQT[BLACK][1][4][myIndex];	}
    //KING
	myPos=myBoard->getBlackKing();
    while(myPos)
	{
		int myIndex = BitBoardUtils::msb(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
        blackOpeningValue+=EvalTables::AllPSQT[BLACK][0][5][myIndex];
		blackEndgameValue+=EvalTables::AllPSQT[BLACK][1][5][myIndex];	}

    myOpeningPSQValue = whiteOpeningValue - blackOpeningValue;
    myEndgamePSQValue = whiteEndgameValue - blackEndgameValue;

}

int Eval::calcMobilityScore(const int64_t alpha) const
{
    int64_t score(0);
    U64 currentBB(0LL);
    int pieceMobility(0);
    Square square;

    for (int i = 0; i<COLOR_NB; i++)
    {
        // PAWN : not implemented for now.

        // KNIGHT
        pieceMobility = 0 ; // Re-initialize tmp variable
        currentBB = myBoard->getBitBoard(Piece::KNIGHT,static_cast<Color>(i));
        while(currentBB)
        {
            square = BitBoardUtils::msb(currentBB);
            pieceMobility += BitBoardUtils::countBBBitsSet(myBoard->getAtkFr(square)); // Sums attacking squares
            currentBB = currentBB ^ ( 0 | 1LL << square);
        }

        score += pieceMobility*(EvalTables::MobilityScaling[OPENING][Piece::KNIGHT]*myGameStage +
        EvalTables::MobilityScaling[ENDGAME][Piece::KNIGHT]*alpha)*(-2*i + 1); // Scaling for game stage and color

        // BISHOP
        pieceMobility = 0 ; // Re-initialize tmp variable
        currentBB = myBoard->getBitBoard(Piece::BISHOP,static_cast<Color>(i));
        while(currentBB)
        {
            square = BitBoardUtils::msb(currentBB);
            pieceMobility += BitBoardUtils::countBBBitsSet(myBoard->getAtkFr(square));
            currentBB = currentBB ^ ( 0 | 1LL << square);
        }

        score += pieceMobility*(EvalTables::MobilityScaling[OPENING][Piece::BISHOP]*myGameStage +
        EvalTables::MobilityScaling[ENDGAME][Piece::BISHOP]*alpha)*(-2*i + 1); // Scaling for game stage and color

        // ROOK
        pieceMobility = 0 ; // Re-initialize tmp variable
        currentBB = myBoard->getBitBoard(Piece::ROOK,static_cast<Color>(i));
        while(currentBB)
        {
            square = BitBoardUtils::msb(currentBB);
            pieceMobility += BitBoardUtils::countBBBitsSet(myBoard->getAtkFr(square));
            currentBB = currentBB ^ ( 0 | 1LL << square);
        }

        score += pieceMobility*(EvalTables::MobilityScaling[OPENING][Piece::ROOK]*myGameStage +
        EvalTables::MobilityScaling[ENDGAME][Piece::ROOK]*alpha)*(-2*i + 1); // Scaling for game stage and color

        // QUEEN
        pieceMobility = 0 ; // Re-initialize tmp variable
        currentBB = myBoard->getBitBoard(Piece::QUEEN,static_cast<Color>(i));
        while(currentBB)
        {
            square = BitBoardUtils::msb(currentBB);
            pieceMobility += BitBoardUtils::countBBBitsSet(myBoard->getAtkFr(square));
            currentBB = currentBB ^ ( 0 | 1LL << square);
        }

        score += pieceMobility*(EvalTables::MobilityScaling[OPENING][Piece::QUEEN]*myGameStage +
        EvalTables::MobilityScaling[ENDGAME][Piece::QUEEN]*alpha)*(-2*i + 1); // Scaling for game stage and color

	}

    return score/TOTAL_MATERIAL;
}

int Eval::calcMaterialAdjustments(const int64_t alpha) const
{
    /* Minor pieces value depending on pawns */
    unsigned int whitePawns = Pawn::countPawns(*myBoard,WHITE);
    unsigned int blackPawns = Pawn::countPawns(*myBoard,BLACK);
    unsigned int whiteKnights = BitBoardUtils::countBBBitsSet(myBoard->getWhiteKnights());
    unsigned int blackKnights = BitBoardUtils::countBBBitsSet(myBoard->getBlackKnights());
    unsigned int whiteBishops = BitBoardUtils::countBBBitsSet(myBoard->getWhiteBishops());
    unsigned int blackBishops = BitBoardUtils::countBBBitsSet(myBoard->getBlackBishops());
    int knightBonus = EvalTables::KnightValue*static_cast<int>(whiteKnights*whitePawns-blackKnights*blackPawns)/8;
    int bishopBonus = EvalTables::BishopValue*static_cast<int>(whiteBishops*whitePawns-blackBishops*blackPawns)/8;

    /* Bishop pair */
    unsigned int whiteBishopCount = BitBoardUtils::countBBBitsSet(myBoard->getWhiteBishops());
    unsigned int blackBishopCount = BitBoardUtils::countBBBitsSet(myBoard->getBlackBishops());
    int pairCount = (whiteBishopCount > 1) - (blackBishopCount > 1);

    int bishopPairBonus = pairCount*(EvalTables::BishopPair[OPENING]*myGameStage +
    EvalTables::BishopPair[ENDGAME]*alpha)/Eval::TOTAL_MATERIAL;

    return knightBonus + bishopBonus + bishopPairBonus;
}

int Eval::getWhitePiecesValue() const
{
    int whitePiecesValue(0);
    whitePiecesValue += BitBoardUtils::countBBBitsSet(myBoard->getWhitePawns())*Piece::PAWN_VALUE
                        + BitBoardUtils::countBBBitsSet(myBoard->getWhiteKnights())*Piece::KNIGHT_VALUE
                        + BitBoardUtils::countBBBitsSet(myBoard->getWhiteBishops())*Piece::BISHOP_VALUE
                        + BitBoardUtils::countBBBitsSet(myBoard->getWhiteRooks())*Piece::ROOK_VALUE
                        + BitBoardUtils::countBBBitsSet(myBoard->getWhiteQueens())*Piece::QUEEN_VALUE
                        + BitBoardUtils::countBBBitsSet(myBoard->getWhiteKing())*Piece::KING_VALUE;
    return whitePiecesValue;
}
int Eval::getBlackPiecesValue() const
{
    int blackPiecesValue(0);
    blackPiecesValue += BitBoardUtils::countBBBitsSet(myBoard->getBlackPawns())*Piece::PAWN_VALUE
                        + BitBoardUtils::countBBBitsSet(myBoard->getBlackKnights())*Piece::KNIGHT_VALUE
                        + BitBoardUtils::countBBBitsSet(myBoard->getBlackBishops())*Piece::BISHOP_VALUE
                        + BitBoardUtils::countBBBitsSet(myBoard->getBlackRooks())*Piece::ROOK_VALUE
                        + BitBoardUtils::countBBBitsSet(myBoard->getBlackQueens())*Piece::QUEEN_VALUE
                        + BitBoardUtils::countBBBitsSet(myBoard->getBlackKing())*Piece::KING_VALUE;

    return blackPiecesValue;
}

void Eval::updateEvalAttributes(const Move &move)
{
    int origin = move.getOrigin();
    int destination = move.getDestination();
    int pieceType = move.getPieceType();
    Color nextToPlay = myBoard->getColorToPlay();
    Color color = Utils::getOppositeColor(nextToPlay);

    myOpeningPSQValue += (-2*color + 1)*
                        (EvalTables::AllPSQT[color][0][pieceType][destination]
                        -EvalTables::AllPSQT[color][0][pieceType][origin]);
    myEndgamePSQValue += (-2*color + 1)*
                        (EvalTables::AllPSQT[color][1][pieceType][destination]
                        -EvalTables::AllPSQT[color][1][pieceType][origin]);
    if (move.isCapture())
    {
        int capturedPieceType = move.getCapturedPieceType();
        int pieceValue = pieceTypeToValue(capturedPieceType);
        myGameStage -= pieceValue;
        myMaterialScore +=  (-2*color + 1)*pieceValue;
        myOpeningPSQValue += (-2*color + 1)*EvalTables::AllPSQT[nextToPlay][0][capturedPieceType][destination];
        myEndgamePSQValue += (-2*color + 1)*EvalTables::AllPSQT[nextToPlay][1][capturedPieceType][destination];
    }

    if (move.isPromotion())
    {
        int promotedPieceType = move.getPromotedPieceType();
        myMaterialScore += (-2*color + 1)*(pieceTypeToValue(promotedPieceType)-Piece::PAWN_VALUE);
        myOpeningPSQValue += (-2*color + 1)*EvalTables::AllPSQT[color][0][promotedPieceType][destination];
        myEndgamePSQValue += (-2*color + 1)*EvalTables::AllPSQT[color][1][promotedPieceType][destination];
    }
}

void Eval::rewindEvalAttributes(const Move &move)
{
    int origin=move.getOrigin();
    int destination=move.getDestination();
    int pieceType=move.getPieceType();
    Color color=myBoard->getColorToPlay();
    Color oppositeColor = Utils::getOppositeColor(color);

    myOpeningPSQValue -= (-2*color + 1)*
                        (EvalTables::AllPSQT[color][0][pieceType][destination]
                        -EvalTables::AllPSQT[color][0][pieceType][origin]);
    myEndgamePSQValue -= (-2*color + 1)*
                        (EvalTables::AllPSQT[color][1][pieceType][destination]
                        -EvalTables::AllPSQT[color][1][pieceType][origin]);
    if (move.isCapture())
    {
        int capturedPieceType = move.getCapturedPieceType();
        int pieceValue = pieceTypeToValue(capturedPieceType);
        myGameStage += pieceValue;
        myMaterialScore -=  (-2*color + 1)*pieceValue;
        myOpeningPSQValue -= (-2*color + 1)*EvalTables::AllPSQT[oppositeColor][0][capturedPieceType][destination];
        myEndgamePSQValue -= (-2*color + 1)*EvalTables::AllPSQT[oppositeColor][1][capturedPieceType][destination];
    }

    if (move.isPromotion())
    {
        int promotedPieceType = move.getPromotedPieceType();
        myMaterialScore -= (-2*color + 1)*(pieceTypeToValue(promotedPieceType)-Piece::PAWN_VALUE);
        myOpeningPSQValue -= (-2*color + 1)*EvalTables::AllPSQT[color][0][promotedPieceType][destination];
        myEndgamePSQValue -= (-2*color + 1)*EvalTables::AllPSQT[color][1][promotedPieceType][destination];
    }
}

int Eval::pieceTypeToValue(int type)
{
    switch (type)
    {
        case 0: return Piece::PAWN_VALUE;
        case 1: return Piece::KNIGHT_VALUE;
        case 2: return Piece::BISHOP_VALUE;
        case 3: return Piece::ROOK_VALUE;
        case 4: return Piece::QUEEN_VALUE;
        case 5: return Piece::KING_VALUE;
        default: return 0;
    }
}

void Eval::sortMoveList(std::vector<Move>& moveList)
{
	std::sort(moveList.rbegin(), moveList.rend(), [](const Move& lhs, const Move& rhs)
			{
				int score = 0;
				int otherScore = 0;

				if(lhs.isPromotion())
				{
					score += Eval::pieceTypeToValue(lhs.getPromotedPieceType())-Piece::PAWN_VALUE;
				}

				if(rhs.isPromotion())
				{
					otherScore += Eval::pieceTypeToValue(rhs.getPromotedPieceType()-Piece::PAWN_VALUE);
				}

				if(lhs.isCapture())
				{
					score += Eval::pieceTypeToValue(lhs.getCapturedPieceType());
				}

				if(rhs.isCapture())
				{
					otherScore += Eval::pieceTypeToValue(rhs.getCapturedPieceType());
				}

				return score < otherScore;
			});
}
