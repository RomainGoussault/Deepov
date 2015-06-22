#include "Eval.hpp"
#include "BitBoardUtils.hpp"

Eval::Eval(std::shared_ptr<Board> boardPtr)
{
    myBoard = boardPtr;
}

int Eval::evaluate()
{
    return getMaterialScore() + getMobilityScore();
}

void Eval::init()
{
    /* These values for the initial position. If i can test that the position is initial, i don't need to calculate
    myGameStage = 1;
    myPSQvalue = 0;  */

    int tmp[64]; // tmp variable
    std::cout << "+Destination -Origin before flip" << std::endl;
    std::cout << EvalTables::AllPSQT[WHITE][0][0][28] << std::endl;
    std::cout << EvalTables::AllPSQT[WHITE][0][0][12] << std::endl;
    for (int i1=0; i1<2; ++i1)
    {
        for (int i2=0; i2<6; ++i2)
        {
            // 0 for midgame, 1 for lategame
            std::copy(EvalTables::AllPSQT[WHITE][i1][i2],EvalTables::AllPSQT[WHITE][i1][i2]+64,tmp);
            for (int j=0; j<64; ++j)
            {
                EvalTables::AllPSQT[WHITE][i1][i2][j]=tmp[56-j/8*8+j%8]; // flips the board
                EvalTables::AllPSQT[BLACK][i1][i2][j]=tmp[j];
            }
        }
    }
    std::cout << "+Destination -Origin after flip" << std::endl;
    std::cout << EvalTables::AllPSQT[WHITE][0][0][28] << std::endl;
    std::cout << EvalTables::AllPSQT[WHITE][0][0][12] << std::endl;
    std::cout << "E2E4 for Black" << std::endl;
    std::cout << EvalTables::AllPSQT[BLACK][0][0][28] << std::endl;
    std::cout << EvalTables::AllPSQT[BLACK][0][0][12] << std::endl;
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
}
int Eval::getMobilityScore()
{
    return 0; // Need a way to efficiently get attacking squares => look at Board::getAttackedPositions()
}

int Eval::getWhitePiecesValue()
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
int Eval::getBlackPiecesValue()
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
    std::cout << "+Destination -Origin" << std::endl;
    std::cout << EvalTables::AllPSQT[color][0][pieceType][destination] << std::endl;
    std::cout << EvalTables::AllPSQT[color][0][pieceType][origin] << std::endl;

    myOpeningPSQValue += (-2*color + 1)*
                        (EvalTables::AllPSQT[color][0][pieceType][destination]
                        -EvalTables::AllPSQT[color][0][pieceType][origin]);
    myEndgamePSQValue += (-2*color + 1)*
                        (EvalTables::AllPSQT[color][1][pieceType][destination]
                        -EvalTables::AllPSQT[color][1][pieceType][origin]);
    if (move.isCapture())
    {
        myGameStage -= move.getCapturedPieceType();
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
        myGameStage += move.getCapturedPieceType();
    }
}
