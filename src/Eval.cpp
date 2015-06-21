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
                EvalTables::AllPSQT[WHITE][i1][i2][j]=tmp[56-j/8*8+j%8];
                EvalTables::AllPSQT[BLACK][i1][i2][j]=tmp[j];
            }
        }
    }

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
		whiteOpeningValue+=EvalTables::AllPSQT[WHITE][0][0][myIndex];
		whiteEndgameValue+=EvalTables::AllPSQT[WHITE][1][0][myIndex];	}
    //BISHOPS
	myPos=myBoard->getWhiteBishops();
    while(myPos)
	{
		int myIndex = BitBoardUtils::getMsbIndex(myPos);
        myPos = myPos ^ ( 0 | 1LL << myIndex);
		whiteOpeningValue+=EvalTables::AllPSQT[WHITE][0][0][myIndex];
		whiteEndgameValue+=EvalTables::AllPSQT[WHITE][1][0][myIndex];
	}
    //ROOK
	myPos=myBoard->getWhiteRooks();
    while(myPos)
	{
		int myIndex = BitBoardUtils::getMsbIndex(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
		whiteOpeningValue+=EvalTables::AllPSQT[WHITE][0][0][myIndex];
		whiteEndgameValue+=EvalTables::AllPSQT[WHITE][1][0][myIndex];
	}
    //QUEEN
	myPos=myBoard->getWhiteQueens();
    while(myPos)
	{
		int myIndex = BitBoardUtils::getMsbIndex(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
			whiteOpeningValue+=EvalTables::AllPSQT[WHITE][0][0][myIndex];
		whiteEndgameValue+=EvalTables::AllPSQT[WHITE][1][0][myIndex];
	}
    //KING
	myPos=myBoard->getWhiteKing();
    while(myPos)
	{
		int myIndex = BitBoardUtils::getMsbIndex(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
        whiteOpeningValue+=EvalTables::AllPSQT[WHITE][0][0][myIndex];
		whiteEndgameValue+=EvalTables::AllPSQT[WHITE][1][0][myIndex];
	}

    // BLACK
    // PAWNS
    myPos=myBoard->getBlackPawns();
    while(myPos)
	{
		int myIndex = BitBoardUtils::getMsbIndex(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
        blackOpeningValue+=EvalTables::AllPSQT[WHITE][0][0][myIndex];
		blackEndgameValue+=EvalTables::AllPSQT[WHITE][1][0][myIndex];
	}

    //KNIGHTS
	myPos=myBoard->getBlackKnights();
    while(myPos)
	{
		int myIndex = BitBoardUtils::getMsbIndex(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
        blackOpeningValue+=EvalTables::AllPSQT[WHITE][0][0][myIndex];
		blackEndgameValue+=EvalTables::AllPSQT[WHITE][1][0][myIndex];
	}
    //BISHOPS
	myPos=myBoard->getBlackBishops();
    while(myPos)
	{
		int myIndex = BitBoardUtils::getMsbIndex(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
        blackOpeningValue+=EvalTables::AllPSQT[WHITE][0][0][myIndex];
		blackEndgameValue+=EvalTables::AllPSQT[WHITE][1][0][myIndex];	}
    //ROOK
	myPos=myBoard->getBlackRooks();
    while(myPos)
	{
		int myIndex = BitBoardUtils::getMsbIndex(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
        blackOpeningValue+=EvalTables::AllPSQT[WHITE][0][0][myIndex];
		blackEndgameValue+=EvalTables::AllPSQT[WHITE][1][0][myIndex];	}
    //QUEEN
	myPos=myBoard->getBlackQueens();
    while(myPos)
	{
		int myIndex = BitBoardUtils::getMsbIndex(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
        blackOpeningValue+=EvalTables::AllPSQT[WHITE][0][0][myIndex];
		blackEndgameValue+=EvalTables::AllPSQT[WHITE][1][0][myIndex];	}
    //KING
	myPos=myBoard->getBlackKing();
    while(myPos)
	{
		int myIndex = BitBoardUtils::getMsbIndex(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
        blackOpeningValue+=EvalTables::AllPSQT[WHITE][0][0][myIndex];
		blackEndgameValue+=EvalTables::AllPSQT[WHITE][1][0][myIndex];	}

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

void Eval::updateEvalAttributes(Move &move)
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
        myGameStage -= move.getCapturedPieceType();
    }
}
