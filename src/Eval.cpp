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

#include "Eval.hpp"
#include "Board.hpp"

#include <algorithm>

int Eval::POSITIONNAL_GAIN_PERCENT = 100;
int Eval::MOBILITY_GAIN_PERCENT = 100;
int Eval::PAWN_GAIN_PERCENT = 100;




Eval::Eval(std::shared_ptr<Board> boardPtr)
{
    myBoard = boardPtr;
    init();
}

int Eval::calculateKingSafety() {

	int hasWhiteCastled = myBoard->hasWhiteCastled();
	int hasBlackCastled = myBoard->hasBlackCastled();
	int kingSafetyScore = 45*(hasWhiteCastled - hasBlackCastled);

    //White king safety
    if(hasWhiteCastled && getRank(myBoard->getWhiteKingSquare()) <= RANK_4)
    {   
        Square kSq = myBoard->getWhiteKingSquare();
        File kingFile = getFile(kSq);
        Rank kingRank = getRank(kSq);
        
        if(kingFile >= FILE_G)
        {   
            //king side castling
            U64 safeArea = 14737632ULL;

            U64 pawnShelter = Tables::MASK_RANK[kingRank+1] & myBoard->getWhitePawns() & safeArea;
            U64 farAwayPawnShelter = Tables::MASK_RANK[kingRank+2] & myBoard->getWhitePawns() & safeArea;
            kingSafetyScore += 5*popcount(pawnShelter);
            kingSafetyScore += 3*popcount(farAwayPawnShelter);
        }
        else if(kingFile <= FILE_C)
        {
            //queen side castling
            U64 safeArea = 1799ULL;

            U64 pawnShelter = Tables::MASK_RANK[kingRank+1] & myBoard->getWhitePawns() & safeArea;
            kingSafetyScore += 5*popcount(pawnShelter);
        }
    }

    //Black king safety
    if(hasBlackCastled && getRank(myBoard->getBlackKingSquare()) >= RANK_5)
    {
        Square kSq = myBoard->getBlackKingSquare();
        File kingFile = getFile(kSq);
        Rank kingRank = getRank(kSq);

        if(kingFile >= FILE_G)
        {
            //king side castling
            U64 safeArea = 16204197749883666432ULL;

            U64 pawnShelter = Tables::MASK_RANK[kingRank-1] & myBoard->getBlackPawns() & safeArea;
            U64 farAwayPawnShelter = Tables::MASK_RANK[kingRank-2] & myBoard->getBlackPawns() & safeArea;
            kingSafetyScore -= 5*popcount(pawnShelter);
            kingSafetyScore -= 3*popcount(farAwayPawnShelter);
        }
        else if(kingFile <= FILE_C)
        {
            //queen side castling
            U64 safeArea = 506373483102470144ULL;

            U64 pawnShelter = Tables::MASK_RANK[kingRank-1] & myBoard->getBlackPawns() & safeArea;;
            kingSafetyScore -= 5*popcount(pawnShelter);
        }
    }

	return kingSafetyScore;
}

//evaluate always return the white point of view
int Eval::evaluate()
{
	//int is too small to contain the following values
	//Note that: 0 <= myGameStage <= TOTAL_MATERIAL

	int64_t alpha =  TOTAL_MATERIAL-myGameStage;
	int64_t openingValue = myOpeningPSQValue*myGameStage;
	int64_t endGameValue = myEndgamePSQValue*alpha;
	int64_t diff = openingValue + endGameValue;
	int positionScore =  diff/TOTAL_MATERIAL;

	int mobilityScore = calcMobilityScore(alpha);
	int materialScore = myMaterialScore;

	int kingSafetyScore = myGameStage*calculateKingSafety()/TOTAL_MATERIAL;
	int pawnScore = Pawn::getScore(*myBoard, myGameStage, alpha);
	// + calcMaterialAdjustments(alpha);

    return calcMaterialAdjustments(alpha) + materialScore + 1.16*positionScore + 0.62*mobilityScore + kingSafetyScore + pawnScore/4;
    // return calcMaterialAdjustments(alpha) + materialScore + positionScore + mobilityScore/2 + kingSafetyScore + pawnScore/4;
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
    myGameStage = (getWhitePiecesValue() + getBlackPiecesValue());

    // Calculate initial PSQ value
    /* Maybe there is a simpler way to calculate all this ? */
    int whiteOpeningValue(0); int blackOpeningValue(0);
    int whiteEndgameValue(0); int blackEndgameValue(0);
    // WHITE
    // PAWNS
    U64 myPos(myBoard->getWhitePawns());
    while(myPos)
	{
		int myIndex = msb(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
		whiteOpeningValue+=EvalTables::AllPSQT[WHITE][0][0][myIndex];
		whiteEndgameValue+=EvalTables::AllPSQT[WHITE][1][0][myIndex];
	}

    //KNIGHTS
	myPos=myBoard->getWhiteKnights();
    while(myPos)
	{
		int myIndex = msb(myPos);
        myPos = myPos ^ ( 0 | 1LL << myIndex);
		whiteOpeningValue+=EvalTables::AllPSQT[WHITE][0][1][myIndex];
		whiteEndgameValue+=EvalTables::AllPSQT[WHITE][1][1][myIndex];
    }
    //BISHOPS
	myPos=myBoard->getWhiteBishops();
    while(myPos)
	{
		int myIndex = msb(myPos);
        myPos = myPos ^ ( 0 | 1LL << myIndex);
		whiteOpeningValue+=EvalTables::AllPSQT[WHITE][0][2][myIndex];
		whiteEndgameValue+=EvalTables::AllPSQT[WHITE][1][2][myIndex];
	}
    //ROOK
	myPos=myBoard->getWhiteRooks();
    while(myPos)
	{
		int myIndex = msb(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
		whiteOpeningValue+=EvalTables::AllPSQT[WHITE][0][3][myIndex];
		whiteEndgameValue+=EvalTables::AllPSQT[WHITE][1][3][myIndex];
	}
    //QUEEN
	myPos=myBoard->getWhiteQueens();
    while(myPos)
	{
		int myIndex = msb(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
        whiteOpeningValue+=EvalTables::AllPSQT[WHITE][0][4][myIndex];
		whiteEndgameValue+=EvalTables::AllPSQT[WHITE][1][4][myIndex];
	}
    //KING
	myPos=myBoard->getWhiteKing();
    while(myPos)
	{
		int myIndex = msb(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
        whiteOpeningValue+=EvalTables::AllPSQT[WHITE][0][5][myIndex];
		whiteEndgameValue+=EvalTables::AllPSQT[WHITE][1][5][myIndex];
	}

    // BLACK
    // PAWNS
    myPos=myBoard->getBlackPawns();
    while(myPos)
	{
		int myIndex = msb(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
        blackOpeningValue+=EvalTables::AllPSQT[BLACK][0][0][myIndex];
		blackEndgameValue+=EvalTables::AllPSQT[BLACK][1][0][myIndex];
	}

    //KNIGHTS
	myPos=myBoard->getBlackKnights();
    while(myPos)
	{
		int myIndex = msb(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
        blackOpeningValue+=EvalTables::AllPSQT[BLACK][0][1][myIndex];
		blackEndgameValue+=EvalTables::AllPSQT[BLACK][1][1][myIndex];
	}
    //BISHOPS
	myPos=myBoard->getBlackBishops();
    while(myPos)
	{
		int myIndex = msb(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
        blackOpeningValue+=EvalTables::AllPSQT[BLACK][0][2][myIndex];
		blackEndgameValue+=EvalTables::AllPSQT[BLACK][1][2][myIndex];	}
    //ROOK
	myPos=myBoard->getBlackRooks();
    while(myPos)
	{
		int myIndex = msb(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
        blackOpeningValue+=EvalTables::AllPSQT[BLACK][0][3][myIndex];
		blackEndgameValue+=EvalTables::AllPSQT[BLACK][1][3][myIndex];	}
    //QUEEN
	myPos=myBoard->getBlackQueens();
    while(myPos)
	{
		int myIndex = msb(myPos);
		myPos = myPos ^ ( 0 | 1LL << myIndex);
        blackOpeningValue+=EvalTables::AllPSQT[BLACK][0][4][myIndex];
		blackEndgameValue+=EvalTables::AllPSQT[BLACK][1][4][myIndex];	}
    //KING
	myPos=myBoard->getBlackKing();
    while(myPos)
	{
		int myIndex = msb(myPos);
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


    for (Color color = WHITE; color<COLOR_NB; ++color)
    {
        // King safety to implement..
        // Color oppositeColor = Utils::getOppositeColor(static_cast<Color>(i));
        // U64 kingPos = myBoard->getKing(oppositeColor);
        // Square kingIndex = msb(kingPos);
        // U64 kingRing = myBoard->getKingAttacks(kingIndex);
        // ksIndex = 0;
       
        pieceMobility = 0;
        // PAWN : not implemented for now.

        // KNIGHT
        currentBB = myBoard->getBitBoard(Piece::KNIGHT, color);
        while(currentBB)
        {
            square = pop_lsb(&currentBB);
            U64 attacks = myBoard->getKnightAttacks(square, color);
            pieceMobility += popcount(attacks); // Sums attacking squares
        }

        score += pieceMobility*(EvalTables::MobilityScaling[OPENING][Piece::KNIGHT]*myGameStage +
        EvalTables::MobilityScaling[ENDGAME][Piece::KNIGHT]*alpha)*(-2*color + 1); // Scaling for game stage and color

        // BISHOP
        pieceMobility = 0 ; // Re-initialize tmp variable
        currentBB = myBoard->getBitBoard(Piece::BISHOP, color);
        while(currentBB)
        {
            square = pop_lsb(&currentBB);
            U64 attacks = myBoard->getBishopAttacks(square, color);
            pieceMobility += popcount(attacks);
         }

        score += pieceMobility*(EvalTables::MobilityScaling[OPENING][Piece::BISHOP]*myGameStage +
        EvalTables::MobilityScaling[ENDGAME][Piece::BISHOP]*alpha)*(-2*color + 1); // Scaling for game stage and color

        // ROOK
        pieceMobility = 0 ; // Re-initialize tmp variable
        currentBB = myBoard->getBitBoard(Piece::ROOK, color);
        while(currentBB)
        {
            square = pop_lsb(&currentBB);
            U64 attacks = myBoard->getRookAttacks(square, color);
            pieceMobility += popcount(attacks);
        }

        score += pieceMobility*(EvalTables::MobilityScaling[OPENING][Piece::ROOK]*myGameStage +
        EvalTables::MobilityScaling[ENDGAME][Piece::ROOK]*alpha)*(-2*color + 1); // Scaling for game stage and color

        // QUEEN
        pieceMobility = 0 ; // Re-initialize tmp variable
        currentBB = myBoard->getBitBoard(Piece::QUEEN, color);
        while(currentBB)
        {
            square = pop_lsb(&currentBB);
            U64 attacks = myBoard->getQueenAttacks(square, color);
            pieceMobility += popcount(attacks); 
       }

        score += pieceMobility*(EvalTables::MobilityScaling[OPENING][Piece::QUEEN]*myGameStage +
        EvalTables::MobilityScaling[ENDGAME][Piece::QUEEN]*alpha)*(-2*color + 1); // Scaling for game stage and color

	}

    return score/TOTAL_MATERIAL;
}

int Eval::calcMaterialAdjustments(const int64_t alpha) const
{
    /* Minor pieces value depending on pawns */
    unsigned int whitePawns = Pawn::countPawns(*myBoard,WHITE);
    unsigned int blackPawns = Pawn::countPawns(*myBoard,BLACK);
    unsigned int whiteKnights = popcount(myBoard->getWhiteKnights());
    unsigned int blackKnights = popcount(myBoard->getBlackKnights());
    unsigned int whiteBishops = popcount(myBoard->getWhiteBishops());
    unsigned int blackBishops = popcount(myBoard->getBlackBishops());
    int knightBonus = EvalTables::KnightValue*static_cast<int>(whiteKnights*whitePawns-blackKnights*blackPawns)/8;
    int bishopBonus = EvalTables::BishopValue*static_cast<int>(whiteBishops*whitePawns-blackBishops*blackPawns)/8;

    /* Bishop pair */
    unsigned int whiteBishopCount = popcount(myBoard->getWhiteBishops());
    unsigned int blackBishopCount = popcount(myBoard->getBlackBishops());
    int pairCount = (whiteBishopCount > 1) - (blackBishopCount > 1);

    int bishopPairBonus = pairCount*(EvalTables::BishopPair[OPENING]*myGameStage +
    EvalTables::BishopPair[ENDGAME]*alpha)/Eval::TOTAL_MATERIAL;

    return knightBonus + bishopBonus + bishopPairBonus;
}

int Eval::getWhitePiecesValue() const
{
    int whitePiecesValue(0);
    whitePiecesValue += popcount(myBoard->getWhitePawns())*Piece::PAWN_VALUE
                        + popcount(myBoard->getWhiteKnights())*Piece::KNIGHT_VALUE
                        + popcount(myBoard->getWhiteBishops())*Piece::BISHOP_VALUE
                        + popcount(myBoard->getWhiteRooks())*Piece::ROOK_VALUE
                        + popcount(myBoard->getWhiteQueens())*Piece::QUEEN_VALUE;
    return whitePiecesValue;
}
int Eval::getBlackPiecesValue() const
{
    int blackPiecesValue(0);
    blackPiecesValue += popcount(myBoard->getBlackPawns())*Piece::PAWN_VALUE
                        + popcount(myBoard->getBlackKnights())*Piece::KNIGHT_VALUE
                        + popcount(myBoard->getBlackBishops())*Piece::BISHOP_VALUE
                        + popcount(myBoard->getBlackRooks())*Piece::ROOK_VALUE
                        + popcount(myBoard->getBlackQueens())*Piece::QUEEN_VALUE;

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
					otherScore += Eval::pieceTypeToValue(rhs.getPromotedPieceType())-Piece::PAWN_VALUE;
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
