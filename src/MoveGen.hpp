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
    void appendWhiteEnPassantMoves(std::vector<Move>& moves) const;
    void appendBlackEnPassantMoves(std::vector<Move>& moves) const;

    /* Pseudo Legal Moves */
    void appendQueenPseudoLegalMoves(const unsigned int& color, std::vector<Move>& moves) const;
    void appendKnightPseudoLegalMoves(const unsigned int& color, std::vector<Move>& moves) const;
    void appendKingPseudoLegalMoves(const unsigned int& color, std::vector<Move>& moves) const;
    void appendRookPseudoLegalMoves(const unsigned int& color, std::vector<Move>& moves) const;
    void appendBishopPseudoLegalMoves(const unsigned int& color, std::vector<Move>& moves) const;
    void appendPawnPseudoLegalMoves(const unsigned int& color, std::vector<Move>& moves) const;
    void appendWhitePawnPseudoLegalMoves(std::vector<Move>& moves) const;
    void appendBlackPawnPseudoLegalMoves(std::vector<Move>& moves) const;

	std::vector<Move> getRookPseudoLegalMoves(const unsigned int& color) const
	{
		std::vector<Move> moves;
		appendRookPseudoLegalMoves(color, moves);
		return moves;
	}

	std::vector<Move> getQueenPseudoLegalMoves(const unsigned int& color) const
	{
		std::vector<Move> moves;
		appendQueenPseudoLegalMoves(color, moves);
		return moves;
	}

    std::vector<Move> getKingPseudoLegalMoves(const unsigned int& color)
	{
		std::vector<Move> moves;
		appendKingPseudoLegalMoves(color, moves);
		return moves;
	}

	std::vector<Move> getBishopPseudoLegalMoves(const unsigned int& color) const
	{
		std::vector<Move> moves;
		appendBishopPseudoLegalMoves(color, moves);
		return moves;
	}

    std::vector<Move> getKnightPseudoLegalMoves(const unsigned int& color) const
    {
    	std::vector<Move> moves;
    	appendKnightPseudoLegalMoves(color, moves);
    	return moves;
    }

    std::vector<Move> getPawnPseudoLegalMoves(const unsigned int& color) const
    {
       	std::vector<Move> moves;
       	appendPawnPseudoLegalMoves(color, moves);
       	return moves;
    }

    std::vector<Move> getWhitePawnPseudoLegalMoves() const
    {
       	std::vector<Move> moves;
       	appendWhitePawnPseudoLegalMoves(moves);
       	return moves;
    }

    std::vector<Move> getBlackPawnPseudoLegalMoves() const
    {
       	std::vector<Move> moves;
       	appendBlackPawnPseudoLegalMoves(moves);
       	return moves;
    }

    /* Moves */
    std::vector<Move> getPseudoLegalMoves();
    std::vector<Move> getPseudoLegalMoves(const unsigned int color);
    std::vector<Move> getLegalMoves();
    std::vector<Move> getLegalMoves(const unsigned int color);

    //Castling
    void addKingSideCastlingMove(unsigned int color, unsigned int kingIndex, std::vector<Move>& moves) const;
    void addQueenSideCastlingMove(unsigned int color, unsigned int kingIndex, std::vector<Move>& moves) const;
	bool isQueenSideCastlingPossible(const unsigned int color) const;
	bool isKingSideCastlingPossible(const unsigned int color) const;


private:

    std::shared_ptr<Board> myBoard;

	void addQuietMoves(U64 quietDestinations, unsigned int pieceIndex, std::vector<Move>& moves, Piece::PieceType pieceType) const;
	void addDoublePawnPushMoves(U64 pawnDestinations, unsigned int pieceIndex, std::vector<Move>& moves) const;
	void addCaptureMoves(U64 captureDestinations, unsigned int pieceIndex, std::vector<Move>& moves, Piece::PieceType pieceType) const;
	void addPromotionMoves(U64 promotionDestinations, unsigned int pieceIndex, std::vector<Move>& moves) const;
	void addPromotionCaptureMoves(U64 promotionDestinations, unsigned int pieceIndex, std::vector<Move>& moves) const;

};

#endif // MOVEGEN_HPP_INCLUDED
