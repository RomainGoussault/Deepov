#include "Eval.hpp"
#include "Utils.hpp"

Eval::Eval(std::shared_ptr<Board> boardPtr)
{
    myBoard = boardPtr;
}

int Eval::evaluate()
{
    return 100*getMaterialScore() + getMobilityScore();
}

int Eval::getMobilityScore()
{
    return 0; // Need a way to efficiently get attacking squares => look at Board::getAttackedPositions()
}

int Eval::getMaterialScore()
{
    int whitePiecesValue(0);
    int blackPiecesValue(0);

    whitePiecesValue += Utils::countBBBitsSet(myBoard->getWhitePawns())*PAWN_VALUE
                        + Utils::countBBBitsSet(myBoard->getWhiteKnights())*KNIGHT_VALUE
                        + Utils::countBBBitsSet(myBoard->getWhiteBishops())*BISHOP_VALUE
                        + Utils::countBBBitsSet(myBoard->getWhiteRooks())*ROOK_VALUE
                        + Utils::countBBBitsSet(myBoard->getWhiteQueens())*QUEEN_VALUE
                        + Utils::countBBBitsSet(myBoard->getWhiteKing())*KING_VALUE;

    blackPiecesValue += Utils::countBBBitsSet(myBoard->getBlackPawns())*PAWN_VALUE
                        + Utils::countBBBitsSet(myBoard->getBlackKnights())*KNIGHT_VALUE
                        + Utils::countBBBitsSet(myBoard->getBlackBishops())*BISHOP_VALUE
                        + Utils::countBBBitsSet(myBoard->getBlackRooks())*ROOK_VALUE
                        + Utils::countBBBitsSet(myBoard->getBlackQueens())*QUEEN_VALUE
                        + Utils::countBBBitsSet(myBoard->getBlackKing())*KING_VALUE;

    return whitePiecesValue - blackPiecesValue;
}
