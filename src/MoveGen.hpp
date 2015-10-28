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
    inline std::vector<Move> generateMoves() {return generateLegalMoves();};

    /* Special Moves */
    void appendWhiteEnPassantMoves(std::vector<Move>& moves, U64 target = Tables::ALL) const;
    void appendBlackEnPassantMoves(std::vector<Move>& moves, U64 target= Tables::ALL) const;

    /* Pseudo Legal Moves */
    void appendQueenPseudoLegalMoves(const Color color, std::vector<Move>& moves, U64 target = Tables::ALL) const;
    void appendKnightPseudoLegalMoves(const Color color, std::vector<Move>& moves, U64 target = Tables::ALL) const;
    void appendKingPseudoLegalMoves(const Color color, std::vector<Move>& moves) const;
    void appendRookPseudoLegalMoves(const Color color, std::vector<Move>& moves, U64 target = Tables::ALL) const;
    void appendBishopPseudoLegalMoves(const Color color, std::vector<Move>& moves, U64 target = Tables::ALL) const;
    void appendPawnPseudoLegalMoves(const Color color, std::vector<Move>& moves, U64 target = Tables::ALL) const;
    void appendWhitePawnPseudoLegalMoves(std::vector<Move>& moves, U64 target = Tables::ALL) const;
    void appendBlackPawnPseudoLegalMoves(std::vector<Move>& moves, U64 target = Tables::ALL) const;

	std::vector<Move> getRookPseudoLegalMoves(const Color color) const
	{
		std::vector<Move> moves;
		appendRookPseudoLegalMoves(color, moves);
		return moves;
	}

	std::vector<Move> getQueenPseudoLegalMoves(const Color color) const
	{
		std::vector<Move> moves;
		appendQueenPseudoLegalMoves(color, moves);
		return moves;
	}

    std::vector<Move> getKingPseudoLegalMoves(const Color color)
	{
		std::vector<Move> moves;
		appendKingPseudoLegalMoves(color, moves);
		return moves;
	}

	std::vector<Move> getBishopPseudoLegalMoves(const Color color) const
	{
		std::vector<Move> moves;
		appendBishopPseudoLegalMoves(color, moves);
		return moves;
	}

    std::vector<Move> getKnightPseudoLegalMoves(const Color color) const
    {
    	std::vector<Move> moves;
    	appendKnightPseudoLegalMoves(color, moves);
    	return moves;
    }

    std::vector<Move> getPawnPseudoLegalMoves(const Color color) const
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
    std::vector<Move> generatePseudoLegalMoves();
    std::vector<Move> generatePseudoLegalMoves(const Color color);
    std::vector<Move> generateEvasionMoves(const Color color);
    std::vector<Move> generateLegalMoves();
    std::vector<Move> generateLegalMoves(const Color color);

    //Castling
    void addKingSideCastlingMove(Color color, Square kingIndex, std::vector<Move>& moves) const;
    void addQueenSideCastlingMove(Color color, Square kingIndex, std::vector<Move>& moves) const;
	bool isQueenSideCastlingPossible(const Color color) const;
	bool isKingSideCastlingPossible(const Color color) const;


private:

    std::shared_ptr<Board> myBoard;

	void addQuietMoves(U64 quietDestinations, Square pieceIndex, std::vector<Move>& moves, Piece::PieceType pieceType) const;
	void addDoublePawnPushMoves(U64 pawnDestinations, Square pieceIndex, std::vector<Move>& moves) const;
	void addCaptureMoves(U64 captureDestinations, Square pieceIndex, std::vector<Move>& moves, Piece::PieceType pieceType) const;
	void addPromotionMoves(U64 promotionDestinations, Square pieceIndex, std::vector<Move>& moves) const;
	void addPromotionCaptureMoves(U64 promotionDestinations, Square pieceIndex, std::vector<Move>& moves) const;

};

#endif // MOVEGEN_HPP_INCLUDED
