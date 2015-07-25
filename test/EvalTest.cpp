#include "catch.hpp"
#include "Eval.hpp"
#include "Search.hpp"

TEST_CASE( "Test the initialisation of EvalTables", "[EvalTables]")
{
    std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board());
    Eval initEval(sp);
    REQUIRE(EvalTables::AllPSQT[WHITE][0][0][42] == 15);
    REQUIRE(EvalTables::AllPSQT[WHITE][0][0][41] == -20);
    REQUIRE(EvalTables::AllPSQT[WHITE][0][0][43] == +30);
    REQUIRE(EvalTables::AllPSQT[WHITE][0][1][0] == -70);
    REQUIRE(EvalTables::AllPSQT[WHITE][1][2][14] == 0);
    REQUIRE(EvalTables::AllPSQT[BLACK][1][2][14] == 0);
    REQUIRE(EvalTables::AllPSQT[BLACK][0][2][21] == 5);
    REQUIRE(EvalTables::AllPSQT[BLACK][0][3][60] == 5);
    REQUIRE(EvalTables::AllPSQT[BLACK][1][4][1] == -40);

    REQUIRE(initEval.getGameStage()==7940); // This value will change when tuning for pieces values ...
    REQUIRE(initEval.getOpeningPSQValue()==0);
    REQUIRE(initEval.getEndgamePSQValue()==0);
}

TEST_CASE( "Test the update of evaluation attributes", "[Eval]")
{
    std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board());
    Eval eval(sp);
    REQUIRE(eval.getOpeningPSQValue()==0);
    REQUIRE(sp->getColorToPlay()==WHITE);
    Move e2e4(12,28,0,Piece::PAWN_TYPE);
    eval.updateEvalAttributes(e2e4);
    sp->executeMove(e2e4);

    REQUIRE(eval.getOpeningPSQValue()==60);
    REQUIRE(eval.getEndgamePSQValue()==5);

    eval.rewindEvalAttributes(e2e4);
    sp->undoMove(e2e4);

    REQUIRE(eval.getOpeningPSQValue()==0);
    REQUIRE(eval.getEndgamePSQValue()==0);
}

TEST_CASE( "Test the update of material evaluation attributes", "[Eval]")
{
    std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board());
    Search search(sp);
    REQUIRE(search.getCurrentScore() == 0);
    search.negaMaxRoot(7);
    REQUIRE(search.getCurrentScore() == 0);
}

TEST_CASE( "Test the update of material evaluation attributes 2", "[Eval]")
{
    std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -"));
    Search search(sp);
    unsigned int initScore = search.getCurrentScore();
    search.negaMaxRoot(7);
    REQUIRE(search.getCurrentScore() == initScore);
}
