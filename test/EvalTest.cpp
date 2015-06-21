#include "catch.hpp"
#include "Eval.hpp"

TEST_CASE( "Test the initialisation of EvalTables", "[EvalTables]")
{
    std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board());
    Eval initEval(sp);
    initEval.init();

//    for (int i=0; i<8; ++i)
//    {
//        for (int j=0; j<8; ++j)
//        {
//        std::cout << EvalTables::AllPSQT[WHITE][0][0][8*i+j] << " ";
//        }
//        std::cout << "" << std::endl;
//    }
//
//        for (int i=0; i<8; ++i)
//    {
//        for (int j=0; j<8; ++j)
//        {
//        std::cout << EvalTables::AllPSQT[BLACK][0][0][8*i+j] << " ";
//        }
//        std::cout << "" << std::endl;
//    }

    REQUIRE(EvalTables::AllPSQT[WHITE][0][0][42] == 15);
    REQUIRE(EvalTables::AllPSQT[WHITE][0][0][41] == -20);
    REQUIRE(EvalTables::AllPSQT[WHITE][0][0][43] == +30);
    REQUIRE(EvalTables::AllPSQT[WHITE][0][1][0] == -70);
    REQUIRE(EvalTables::AllPSQT[WHITE][1][2][14] == 5);
    REQUIRE(EvalTables::AllPSQT[BLACK][0][2][21] == 5);
    REQUIRE(EvalTables::AllPSQT[BLACK][0][3][60] == 5);
    REQUIRE(EvalTables::AllPSQT[BLACK][1][4][1] == -40);

    REQUIRE(initEval.getGameStage()==1);
    REQUIRE(initEval.getPSQvalue()==0);

}
