#include "Eval.hpp"
#include "BitBoardUtils.hpp"

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

	return myMaterialScore + positionScore;
}

void Eval::init()
{
    /* These values for the initial position. If i can test that the position is initial, i don't need to calculate
    myMaterialScore = 0
    myGameStage = TOTAL_MATERIAL;
    myPSQvalue = 0;  */

    // Calulate Material Score
    myMaterialScore = getWhitePiecesValue() - getBlackPiecesValue();

    // Calculate game stage
    /* Currently it is a simple linear interpolation with material score but this will be upgraded */
   // int maxValue = 16*PAWN_VALUE + 4*KNIGHT_VALUE + 4*BISHOP_VALUE + 4*ROOK_VALUE + 2*QUEEN_VALUE;
    myGameStage = (getWhitePiecesValue() + getBlackPiecesValue() - 2*KING_VALUE);

    // Calculate initial PSQ value
    /* Maybe there is a simpler way to calculate all this ? */
    int whiteOpeningValue(0); int blackOpeningValue(0);
    int whiteEndgameValue(0); int blackEndgameValue(0);
    // WHITE
    // PAWNS
    U64 myPos(myBoard->getWhitePawns());
    while(myPos)
	{
		int myIndex = BitBoardUtils::getMsbIndex(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
		whiteOpeningValue+=EvalTables::AllPSQT[WHITE][0][0][myIndex];
		whiteEndgameValue+=EvalTables::AllPSQT[WHITE][1][0][myIndex];
	}

    //KNIGHTS
	myPos=myBoard->getWhiteKnights();
    while(myPos)
	{
		int myIndex = BitBoardUtils::getMsbIndex(myPos);
        myPos = myPos ^ ( 0 | 1LL << myIndex);
		whiteOpeningValue+=EvalTables::AllPSQT[WHITE][0][1][myIndex];
		whiteEndgameValue+=EvalTables::AllPSQT[WHITE][1][1][myIndex];
    }
    //BISHOPS
	myPos=myBoard->getWhiteBishops();
    while(myPos)
	{
		int myIndex = BitBoardUtils::getMsbIndex(myPos);
        myPos = myPos ^ ( 0 | 1LL << myIndex);
		whiteOpeningValue+=EvalTables::AllPSQT[WHITE][0][2][myIndex];
		whiteEndgameValue+=EvalTables::AllPSQT[WHITE][1][2][myIndex];
	}
    //ROOK
	myPos=myBoard->getWhiteRooks();
    while(myPos)
	{
		int myIndex = BitBoardUtils::getMsbIndex(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
		whiteOpeningValue+=EvalTables::AllPSQT[WHITE][0][3][myIndex];
		whiteEndgameValue+=EvalTables::AllPSQT[WHITE][1][3][myIndex];
	}
    //QUEEN
	myPos=myBoard->getWhiteQueens();
    while(myPos)
	{
		int myIndex = BitBoardUtils::getMsbIndex(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
        whiteOpeningValue+=EvalTables::AllPSQT[WHITE][0][4][myIndex];
		whiteEndgameValue+=EvalTables::AllPSQT[WHITE][1][4][myIndex];
	}
    //KING
	myPos=myBoard->getWhiteKing();
    while(myPos)
	{
		int myIndex = BitBoardUtils::getMsbIndex(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
        whiteOpeningValue+=EvalTables::AllPSQT[WHITE][0][5][myIndex];
		whiteEndgameValue+=EvalTables::AllPSQT[WHITE][1][5][myIndex];
	}

    // BLACK
    // PAWNS
    myPos=myBoard->getBlackPawns();
    while(myPos)
	{
		int myIndex = BitBoardUtils::getMsbIndex(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
        blackOpeningValue+=EvalTables::AllPSQT[BLACK][0][0][myIndex];
		blackEndgameValue+=EvalTables::AllPSQT[BLACK][1][0][myIndex];
	}

    //KNIGHTS
	myPos=myBoard->getBlackKnights();
    while(myPos)
	{
		int myIndex = BitBoardUtils::getMsbIndex(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
        blackOpeningValue+=EvalTables::AllPSQT[BLACK][0][1][myIndex];
		blackEndgameValue+=EvalTables::AllPSQT[BLACK][1][1][myIndex];
	}
    //BISHOPS
	myPos=myBoard->getBlackBishops();
    while(myPos)
	{
		int myIndex = BitBoardUtils::getMsbIndex(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
        blackOpeningValue+=EvalTables::AllPSQT[BLACK][0][2][myIndex];
		blackEndgameValue+=EvalTables::AllPSQT[BLACK][1][2][myIndex];	}
    //ROOK
	myPos=myBoard->getBlackRooks();
    while(myPos)
	{
		int myIndex = BitBoardUtils::getMsbIndex(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
        blackOpeningValue+=EvalTables::AllPSQT[BLACK][0][3][myIndex];
		blackEndgameValue+=EvalTables::AllPSQT[BLACK][1][3][myIndex];	}
    //QUEEN
	myPos=myBoard->getBlackQueens();
    while(myPos)
	{
		int myIndex = BitBoardUtils::getMsbIndex(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
        blackOpeningValue+=EvalTables::AllPSQT[BLACK][0][4][myIndex];
		blackEndgameValue+=EvalTables::AllPSQT[BLACK][1][4][myIndex];	}
    //KING
	myPos=myBoard->getBlackKing();
    while(myPos)
	{
		int myIndex = BitBoardUtils::getMsbIndex(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
        blackOpeningValue+=EvalTables::AllPSQT[BLACK][0][5][myIndex];
		blackEndgameValue+=EvalTables::AllPSQT[BLACK][1][5][myIndex];	}

    myOpeningPSQValue = whiteOpeningValue - blackOpeningValue;
    myEndgamePSQValue = whiteEndgameValue - blackEndgameValue;

    // Init Pawn structure score
    myPawnScore = initPawnScore();
}

int Eval::getMobilityScore() const
{
    return 0; // Need a way to efficiently get attacking squares => look at Board::getAttackedPositions()
}

int Eval::getWhitePiecesValue() const
{
    int whitePiecesValue(0);
    whitePiecesValue += BitBoardUtils::countBBBitsSet(myBoard->getWhitePawns())*PAWN_VALUE
                        + BitBoardUtils::countBBBitsSet(myBoard->getWhiteKnights())*KNIGHT_VALUE
                        + BitBoardUtils::countBBBitsSet(myBoard->getWhiteBishops())*BISHOP_VALUE
                        + BitBoardUtils::countBBBitsSet(myBoard->getWhiteRooks())*ROOK_VALUE
                        + BitBoardUtils::countBBBitsSet(myBoard->getWhiteQueens())*QUEEN_VALUE
                        + BitBoardUtils::countBBBitsSet(myBoard->getWhiteKing())*KING_VALUE;
    return whitePiecesValue;
}
int Eval::getBlackPiecesValue() const
{
    int blackPiecesValue(0);
    blackPiecesValue += BitBoardUtils::countBBBitsSet(myBoard->getBlackPawns())*PAWN_VALUE
                        + BitBoardUtils::countBBBitsSet(myBoard->getBlackKnights())*KNIGHT_VALUE
                        + BitBoardUtils::countBBBitsSet(myBoard->getBlackBishops())*BISHOP_VALUE
                        + BitBoardUtils::countBBBitsSet(myBoard->getBlackRooks())*ROOK_VALUE
                        + BitBoardUtils::countBBBitsSet(myBoard->getBlackQueens())*QUEEN_VALUE
                        + BitBoardUtils::countBBBitsSet(myBoard->getBlackKing())*KING_VALUE;

    return blackPiecesValue;
}

void Eval::updateEvalAttributes(const Move &move)
{
    int origin=move.getOrigin();
    int destination=move.getDestination();
    int pieceType=move.getPieceType();
    int color=myBoard->getColorToPlay();

    myOpeningPSQValue += (-2*color + 1)*
                        (EvalTables::AllPSQT[color][0][pieceType][destination]
                        -EvalTables::AllPSQT[color][0][pieceType][origin]);
    myEndgamePSQValue += (-2*color + 1)*
                        (EvalTables::AllPSQT[color][1][pieceType][destination]
                        -EvalTables::AllPSQT[color][1][pieceType][origin]);
    if (move.isCapture())
    {
        int pieceValue = pieceTypeToValue(move.getCapturedPieceType());
        myGameStage -= pieceValue;
        myMaterialScore +=  (-2*color + 1)*pieceValue;
    }

    if (move.isPromotion())
    {
        int pieceType = (move.getFlags()&0x3)+ 1; // get the 2 last bits pand add one to get piece type
        myMaterialScore += (-2*color + 1)*pieceTypeToValue(pieceType);
    }

    if (pieceType == Move::PAWN_TYPE && move.isCapture())
    {
        int column = Utils::getFile(origin);
        int pawnsOnFile=Pawn::countPawnsInFile(*myBoard,column,color);
        myPawnScore -= (-2*color + 1)*(pawnsOnFile>1)*Pawn::DOUBLED_PAWN_PENALTY;
        /* Substracts the penalty if there were more than one pawn on file) */
        column = Utils::getFile(destination);
        pawnsOnFile=Pawn::countPawnsInFile(*myBoard,column,color);
        myPawnScore += (-2*color + 1)*(pawnsOnFile>0)*Pawn::DOUBLED_PAWN_PENALTY;
        /* Add the penalty if there is already a pawn on destination file) */
    }
}

void Eval::rewindEvalAttributes(const Move &move)
{
    int origin=move.getOrigin();
    int destination=move.getDestination();
    int pieceType=move.getPieceType();
    int color=Utils::getOppositeColor(myBoard->getColorToPlay());

    myOpeningPSQValue -= (-2*color + 1)*
                        (EvalTables::AllPSQT[color][0][pieceType][destination]
                        -EvalTables::AllPSQT[color][0][pieceType][origin]);
    myEndgamePSQValue -= (-2*color + 1)*
                        (EvalTables::AllPSQT[color][1][pieceType][destination]
                        -EvalTables::AllPSQT[color][1][pieceType][origin]);
    if (move.isCapture())
    {
        int pieceValue = pieceTypeToValue(move.getCapturedPieceType());
        myGameStage += pieceValue;
        myMaterialScore -=  (-2*color + 1)*pieceValue;
    }

    if (move.isPromotion())
    {
        int pieceType = (move.getFlags()&0x3)+ 1; // get the 2 last bits and add one to get piece type
        myMaterialScore -= (-2*color + 1)*pieceTypeToValue(pieceType);
    }

    if (pieceType == Move::PAWN_TYPE && move.isCapture())
    {
        int column = Utils::getFile(origin);
        int pawnsOnFile=Pawn::countPawnsInFile(*myBoard,column,color);
        myPawnScore += (-2*color + 1)*(pawnsOnFile>0)*Pawn::DOUBLED_PAWN_PENALTY;
        /* Substracts the penalty if there were more than one pawn on file) */
        column = Utils::getFile(destination);
        pawnsOnFile=Pawn::countPawnsInFile(*myBoard,column,color);
        myPawnScore -= (-2*color + 1)*(pawnsOnFile>1)*Pawn::DOUBLED_PAWN_PENALTY;
        /* Add the penalty if there is already a pawn on destination file) */
    }
}

int Eval::pieceTypeToValue(int type)
{
    switch (type)
    {
        case 0: return PAWN_VALUE;
        case 1: return KNIGHT_VALUE;
        case 2: return BISHOP_VALUE;
        case 3: return ROOK_VALUE;
        case 4: return QUEEN_VALUE;
        case 5: return KING_VALUE;
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
					score += Eval::pieceTypeToValue(lhs.getPromotedPieceType())-Eval::PAWN_VALUE;
				}

				if(rhs.isPromotion())
				{
					otherScore += Eval::pieceTypeToValue(rhs.getPromotedPieceType()-Eval::PAWN_VALUE);
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
