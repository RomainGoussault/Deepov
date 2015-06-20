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
    int myGameStage = 1;

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

    int myPSQvalue = 0;

}
int Eval::getMobilityScore()
{
    return 0; // Need a way to efficiently get attacking squares => look at Board::getAttackedPositions()
}

int Eval::getMaterialScore()
{
    int whitePiecesValue(0);
    int blackPiecesValue(0);

    whitePiecesValue += BitBoardUtils::countBBBitsSet(myBoard->getWhitePawns())*PAWN_VALUE
                        + BitBoardUtils::countBBBitsSet(myBoard->getWhiteKnights())*KNIGHT_VALUE
                        + BitBoardUtils::countBBBitsSet(myBoard->getWhiteBishops())*BISHOP_VALUE
                        + BitBoardUtils::countBBBitsSet(myBoard->getWhiteRooks())*ROOK_VALUE
                        + BitBoardUtils::countBBBitsSet(myBoard->getWhiteQueens())*QUEEN_VALUE
                        + BitBoardUtils::countBBBitsSet(myBoard->getWhiteKing())*KING_VALUE;

    blackPiecesValue += BitBoardUtils::countBBBitsSet(myBoard->getBlackPawns())*PAWN_VALUE
                        + BitBoardUtils::countBBBitsSet(myBoard->getBlackKnights())*KNIGHT_VALUE
                        + BitBoardUtils::countBBBitsSet(myBoard->getBlackBishops())*BISHOP_VALUE
                        + BitBoardUtils::countBBBitsSet(myBoard->getBlackRooks())*ROOK_VALUE
                        + BitBoardUtils::countBBBitsSet(myBoard->getBlackQueens())*QUEEN_VALUE
                        + BitBoardUtils::countBBBitsSet(myBoard->getBlackKing())*KING_VALUE;

    return whitePiecesValue - blackPiecesValue;
}
