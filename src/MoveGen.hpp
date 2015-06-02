#ifndef MOVEGEN_HPP_INCLUDED
#define MOVEGEN_HPP_INCLUDED

#include <vector>
#include <cmath>

#include "FastBoard.hpp"
#include "FastMove.hpp"
#include "Utils.hpp"


class MoveGen {

public:

    MoveGen(FastBoard* board);

    /* Get Attributes */
    inline std::vector<FastMove> getMoves() {return getLegalMoves();};

    /* Special Moves */
    std::vector<FastMove> getWhiteEnPassantMoves() const;
    std::vector<FastMove> getBlackEnPassantMoves() const;

    /* Pseudo Legal Moves */
    std::vector<FastMove> getKingPseudoLegalMoves(const int& color) const;
	std::vector<FastMove> getQueenPseudoLegalMoves(const int& color) const;
	std::vector<FastMove> getBishopPseudoLegalMoves(const int& color) const;
	std::vector<FastMove> getRookPseudoLegalMoves(const int& color) const;
    std::vector<FastMove> getKnightPseudoLegalMoves(const int& color) const;
    std::vector<FastMove> getPawnPseudoLegalMoves(const int& color) const;
    std::vector<FastMove> getWhitePawnPseudoLegalMoves() const;
    std::vector<FastMove> getBlackPawnPseudoLegalMoves() const;

    /* Moves */
    std::vector<FastMove> getPseudoLegalMoves();
    std::vector<FastMove> getPseudoLegalMoves(const int color);
    std::vector<FastMove> getLegalMoves();
    std::vector<FastMove> getLegalMoves(const int color);

    //Castling
	bool isQueenSideCastlingPossible(const int color) const;
	bool isKingSideCastlingPossible(const int color) const;


private:

    FastBoard* myBoard;

	void addQuietMoves(U64 quietDestinations, int pieceIndex, std::vector<FastMove>& moves, int pieceType) const;
	void addDoublePawnPushMoves(U64 pawnDestinations, int pieceIndex, std::vector<FastMove>& moves) const;
	void addCaptureMoves(U64 captureDestinations, int pieceIndex, std::vector<FastMove>& moves, int pieceType) const;
	void addPromotionMoves(U64 promotionDestinations, int pieceIndex, std::vector<FastMove>& moves) const;
	void addPromotionCaptureMoves(U64 promotionDestinations, int pieceIndex, std::vector<FastMove>& moves) const;

};

#endif // MOVEGEN_HPP_INCLUDED
