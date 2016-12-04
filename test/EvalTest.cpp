/*
    Deepov, a UCI chess playing engine.

    Copyright (c) 20014-2016 Romain Goussault, Navid Hedjazian

    Deepov is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Deepov is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Deepov.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "catch.hpp"
#include "Eval.hpp"
#include "Search.hpp"

TEST_CASE( "Test the initialisation of EvalTables", "[EvalTables]")
{
    Tables::init();
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
    Tables::init();
    std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board());
    Eval eval(sp);
    REQUIRE(eval.getOpeningPSQValue()==0);
    REQUIRE(sp->getColorToPlay()==WHITE);
    Move e2e4(static_cast<Square>(12),static_cast<Square>(28),0,Piece::PAWN);
    sp->executeMove(e2e4);
    eval.updateEvalAttributes(e2e4);

    REQUIRE(eval.getOpeningPSQValue()==60);
    REQUIRE(eval.getEndgamePSQValue()==5);

    sp->undoMove(e2e4);
    eval.rewindEvalAttributes(e2e4);

    REQUIRE(eval.getOpeningPSQValue()==0);
    REQUIRE(eval.getEndgamePSQValue()==0);
}

TEST_CASE( "Test the update of material evaluation attributes", "[Eval]")
{
    Tables::init();
    std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board());
    Search search(sp);
    REQUIRE(search.getCurrentScore() == 0);
    search.negaMaxRoot(7);
    REQUIRE(search.getCurrentScore() == 0);
}

TEST_CASE( "Test the update of material evaluation attributes 2", "[Eval]")
{
    Tables::init();
    std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -"));
    Search search(sp);
    unsigned int initScore = search.getCurrentScore();
    search.negaMaxRoot(7);
    REQUIRE(search.getCurrentScore() == initScore);
}

TEST_CASE( "Test the update of evaluation for promotion moves", "[Eval]")
{
    Tables::init();
    std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q2/PPPBBPpP/R3K2R b KQkq - 0 1"));
    Eval eval(sp);

    Move promotion(static_cast<Square>(14),static_cast<Square>(7),0b1111,Piece::PAWN); // Queen promotion-capture
    promotion.setCapturedPieceType(Piece::ROOK);

    int materialScore = eval.getMaterialScore();

    sp->executeMove(promotion);
    eval.updateEvalAttributes(promotion);

    int changedValue = - Piece::ROOK_VALUE - Piece::QUEEN_VALUE + Piece::PAWN_VALUE;
    REQUIRE(eval.getMaterialScore() == materialScore + changedValue);
}


TEST_CASE( "Test the mobility calculation", "[Eval]")
{
    Tables::init();
	MagicMoves::initmagicmoves();

    std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board());
    Eval eval(sp);
    int mobilityScore = eval.calcMobilityScore(0LL);
    REQUIRE(mobilityScore == 0);

    Move e2e4(static_cast<Square>(12),static_cast<Square>(28),0,Piece::PAWN);
    sp->executeMove(e2e4);
    // val.updateEvalAttributes(e2e4) not needed
    // sp->updateAtkFr();

    // REQUIRE(popcount(sp->getAtkFr(SQ_F1)) == 5); // Verify the attacked squares
    // REQUIRE(popcount(sp->getAtkFr(SQ_D1)) == 4);

    int64_t gameStage = eval.getGameStage();

    mobilityScore = eval.calcMobilityScore(0LL);
    int score(0);
    score += EvalTables::MobilityScaling[OPENING][Piece::KNIGHT]*gameStage; //+1 square for knight
    score += 5*EvalTables::MobilityScaling[OPENING][Piece::BISHOP]*gameStage; // +5 squares for bishop
    score += 4*EvalTables::MobilityScaling[OPENING][Piece::QUEEN]*gameStage; // +4 squares for queen

    score  = score / Eval::TOTAL_MATERIAL;
    REQUIRE(mobilityScore == score);

}

TEST_CASE( "Test the eval of material ", "[Eval]")
{
    Tables::init();
    std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board("kn6/nn2rr2/8/4Q3/8/2p1p2b/1Q6/KN6 w - -"));
    Eval eval(sp);

    int whitePieceValue = 2*Piece::QUEEN_VALUE + Piece::KNIGHT_VALUE;
    int blackPieceValue = 3*Piece::KNIGHT_VALUE + 2*Piece::ROOK_VALUE + 2*Piece::PAWN_VALUE + Piece::BISHOP_VALUE;

    REQUIRE(eval.getWhitePiecesValue() == whitePieceValue);
    REQUIRE(eval.getBlackPiecesValue() == blackPieceValue);
}
