#ifndef MOVEGEN_HPP_INCLUDED
#define MOVEGEN_HPP_INCLUDED

#include "FastBoard.hpp"

class MoveGen {

public:

    MoveGen();
    MoveGen(std::shared_ptr<FastBoard> board);

    /* Pseudo Legal Moves */
    std::vector<FastMove> getKingPseudoLegalMoves(const int& color) const;
	std::vector<FastMove> getQueenPseudoLegalMoves(const int& color) const;
	std::vector<FastMove> getBishopPseudoLegalMoves(const int& color) const;
	std::vector<FastMove> getRookPseudoLegalMoves(const int& color) const;
    std::vector<FastMove> getKnightPseudoLegalMoves(const int& color) const;
    std::vector<FastMove> getPawnPseudoLegalMoves(const int& color) const;
    std::vector<FastMove> getWhitePawnPseudoLegalMoves() const;
    std::vector<FastMove> getBlackPawnPseudoLegalMoves() const;
    getMoves();

    /* Legal Moves */
    std::vector<FastMove> getLegalMoves();
    std::vector<FastMove> getLegalMoves(const int color);
    boost::optional<FastMove> getEnemyLastMove() const; // I use boost::optional in case there is no move to return


private:

    std::shared_ptr<FastBoard> myBoard;
    std::vector<FastMove> myPseudoLegalMoves;

	void addQuietMoves(U64 quietDestinations, int pieceIndex, std::vector<FastMove>& moves, int pieceType) const;
	void addCaptureMoves(U64 captureDestinations, int pieceIndex, std::vector<FastMove>& moves, int pieceType) const;
	void addPromotionMoves(U64 promotionDestinations, int pieceIndex, std::vector<FastMove>& moves) const;
	void addPromotionCaptureMoves(U64 promotionDestinations, int pieceIndex, std::vector<FastMove>& moves) const;


#endif // MOVEGEN_HPP_INCLUDED
