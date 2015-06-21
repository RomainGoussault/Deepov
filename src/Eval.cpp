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

    for (int i1=0; i1<2; ++i1)
    {
        for (int i2=0; i2<6; ++i2)
        {
            // 0 for midgame, 1 for lategame
            std::copy(EvalTables::AllPSQT[WHITE][i1][i2],EvalTables::AllPSQT[WHITE][i1][i2]+64,tmp);
            for (int j=0; j<64; ++j)
            {
                EvalTables::AllPSQT[WHITE][i1][i2][j]=tmp[56-j+j%8];
                EvalTables::AllPSQT[BLACK][i1][i2][j]=tmp[j];
            }
        }
    }

    // Calculate game stage
    /* Currently it is a simple linear interpolation with material score but this will be upgraded */
    int maxValue = 16*PAWN_VALUE + 4*KNIGHT_VALUE + 4*BISHOP_VALUE + 4*ROOK_VALUE + 2*QUEEN_VALUE;
    myGameStage = (getWhitePiecesValue() + getBlackPiecesValue() - 2*KING_VALUE)/maxValue;

    // Calculate initial PSQ value
    /* Maybe there is a simpler way to calculate all this ? */
    int whiteValue(0); int blackValue(0);
    // WHITE
    // PAWNS
    U64 myPos(myBoard->getWhitePawns());
    while(myPos)
	{
		int myIndex = BitBoardUtils::getMsbIndex(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
		whiteValue+=EvalTables::AllPSQT[WHITE][0][0][myIndex]*myGameStage + EvalTables::AllPSQT[WHITE][1][0][myIndex]*(1-myGameStage);
	}

    //KNIGHTS
	myPos=myBoard->getWhiteKnights();
    while(myPos)
	{
		int myIndex = BitBoardUtils::getMsbIndex(myPos);
        myPos = myPos ^ ( 0 | 1LL << myIndex);
		whiteValue+=EvalTables::AllPSQT[WHITE][0][1][myIndex]*myGameStage + EvalTables::AllPSQT[WHITE][1][1][myIndex]*(1-myGameStage);
	}
    //BISHOPS
	myPos=myBoard->getWhiteBishops();
    while(myPos)
	{
		int myIndex = BitBoardUtils::getMsbIndex(myPos);
        myPos = myPos ^ ( 0 | 1LL << myIndex);
		whiteValue+=EvalTables::AllPSQT[WHITE][0][2][myIndex]*myGameStage + EvalTables::AllPSQT[WHITE][1][2][myIndex]*(1-myGameStage);
	}
    //ROOK
	myPos=myBoard->getWhiteRooks();
    while(myPos)
	{
		int myIndex = BitBoardUtils::getMsbIndex(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
		whiteValue+=EvalTables::AllPSQT[WHITE][0][3][myIndex]*myGameStage + EvalTables::AllPSQT[WHITE][1][3][myIndex]*(1-myGameStage);
	}
    //QUEEN
	myPos=myBoard->getWhiteQueens();
    while(myPos)
	{
		int myIndex = BitBoardUtils::getMsbIndex(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
		whiteValue+=EvalTables::AllPSQT[WHITE][0][4][myIndex]*myGameStage + EvalTables::AllPSQT[WHITE][1][4][myIndex]*(1-myGameStage);
	}
    //KING
	myPos=myBoard->getWhiteKing();
    while(myPos)
	{
		int myIndex = BitBoardUtils::getMsbIndex(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
		whiteValue+=EvalTables::AllPSQT[WHITE][0][5][myIndex]*myGameStage + EvalTables::AllPSQT[WHITE][1][5][myIndex]*(1-myGameStage);
	}

    // BLACK
    // PAWNS
    myPos=myBoard->getBlackPawns();
    while(myPos)
	{
		int myIndex = BitBoardUtils::getMsbIndex(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
		blackValue+=EvalTables::AllPSQT[BLACK][0][0][myIndex]*myGameStage + EvalTables::AllPSQT[BLACK][1][0][myIndex]*(1-myGameStage);
	}

    //KNIGHTS
	myPos=myBoard->getBlackKnights();
    while(myPos)
	{
		int myIndex = BitBoardUtils::getMsbIndex(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
		blackValue+=EvalTables::AllPSQT[BLACK][0][1][myIndex]*myGameStage + EvalTables::AllPSQT[BLACK][1][1][myIndex]*(1-myGameStage);
	}
    //BISHOPS
	myPos=myBoard->getBlackBishops();
    while(myPos)
	{
		int myIndex = BitBoardUtils::getMsbIndex(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
		blackValue+=EvalTables::AllPSQT[BLACK][0][2][myIndex]*myGameStage + EvalTables::AllPSQT[BLACK][1][2][myIndex]*(1-myGameStage);
	}
    //ROOK
	myPos=myBoard->getBlackRooks();
    while(myPos)
	{
		int myIndex = BitBoardUtils::getMsbIndex(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
		blackValue+=EvalTables::AllPSQT[BLACK][0][3][myIndex]*myGameStage + EvalTables::AllPSQT[BLACK][1][3][myIndex]*(1-myGameStage);
	}
    //QUEEN
	myPos=myBoard->getBlackQueens();
    while(myPos)
	{
		int myIndex = BitBoardUtils::getMsbIndex(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
		blackValue+=EvalTables::AllPSQT[BLACK][0][4][myIndex]*myGameStage + EvalTables::AllPSQT[BLACK][1][4][myIndex]*(1-myGameStage);
	}
    //KING
	myPos=myBoard->getBlackKing();
    while(myPos)
	{
		int myIndex = BitBoardUtils::getMsbIndex(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
		blackValue+=EvalTables::AllPSQT[BLACK][0][5][myIndex]*myGameStage + EvalTables::AllPSQT[BLACK][1][5][myIndex]*(1-myGameStage);
	}

    myPSQvalue = whiteValue - blackValue;

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
