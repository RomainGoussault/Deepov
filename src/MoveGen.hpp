#ifndef MOVEGEN_HPP_INCLUDED
#define MOVEGEN_HPP_INCLUDED

#include <vector>
#include <cmath>

#include "Board.hpp"
#include "Move.hpp"
#include "Utils.hpp"


class MoveGen {

public:

    MoveGen(Board board);
    MoveGen(std::shared_ptr<Board> boardPtr);

    /* Get Attributes */
    inline std::vector<Move> getMoves() {return getLegalMoves();};

    /* Special Moves */
    std::vector<Move> getWhiteEnPassantMoves() const;
    std::vector<Move> getBlackEnPassantMoves() const;

    /* Pseudo Legal Moves */
    std::vector<Move> getKingPseudoLegalMoves(const int& color) const;
	std::vector<Move> getQueenPseudoLegalMoves(const int& color) const;
	std::vector<Move> getBishopPseudoLegalMoves(const int& color) const;
	std::vector<Move> getRookPseudoLegalMoves(const int& color) const;
    std::vector<Move> getKnightPseudoLegalMoves(const int& color) const;
    std::vector<Move> getPawnPseudoLegalMoves(const int& color) const;
    std::vector<Move> getWhitePawnPseudoLegalMoves() const;
    std::vector<Move> getBlackPawnPseudoLegalMoves() const;

    /* Moves */
    std::vector<Move> getPseudoLegalMoves();
    std::vector<Move> getPseudoLegalMoves(const int color);
    std::vector<Move> getLegalMoves();
    std::vector<Move> getLegalMoves(const int color);

    //Castling
    void addKingSideCastlingMove(int color, int kingIndex, std::vector<Move>& moves) const;
    void addQueenSideCastlingMove(int color, int kingIndex, std::vector<Move>& moves) const;
	bool isQueenSideCastlingPossible(const int color) const;
	bool isKingSideCastlingPossible(const int color) const;


private:

    std::shared_ptr<Board> myBoard;

	void addQuietMoves(U64 quietDestinations, int pieceIndex, std::vector<Move>& moves, int pieceType) const;
	void addDoublePawnPushMoves(U64 pawnDestinations, int pieceIndex, std::vector<Move>& moves) const;
	void addCaptureMoves(U64 captureDestinations, int pieceIndex, std::vector<Move>& moves, int pieceType) const;
	void addPromotionMoves(U64 promotionDestinations, int pieceIndex, std::vector<Move>& moves) const;
	void addPromotionCaptureMoves(U64 promotionDestinations, int pieceIndex, std::vector<Move>& moves) const;

};

#endif // MOVEGEN_HPP_INCLUDED
