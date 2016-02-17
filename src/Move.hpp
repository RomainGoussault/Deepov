#ifndef Move_H
#define Move_H

#include <iostream>
#include <bitset>
#include <string>
#include <array>

#include "Piece.hpp"
#include "Types.hpp"

class Move
{

public:
	constexpr static unsigned int EP_CAPTURE_FLAG = 0b0101;
	constexpr static unsigned int DOUBLE_PAWN_PUSH_FLAG =0b0001;
	constexpr static unsigned int CAPTURE_FLAG = 0b0100;
	constexpr static unsigned int PROMOTION_FLAG = 0b1000;
	constexpr static unsigned int KING_SIDE_CASTLING = 	0b0010;
	constexpr static unsigned int QUEEN_SIDE_CASTLING = 0b0011;
	constexpr static unsigned int NULL_MOVE = 0;


	inline Move() : myMove() //Default constructor
	{
	}

	inline Move(Square origin, Square destination, unsigned int flags, Piece::PieceType pieceType)
	{
        int capturedPieceType = Piece::NO_PIECE_TYPE;
		myMove = ((capturedPieceType & 0x7) << 19) | ((pieceType &0x7)<<16) | ((flags & 0xf)<<12) | ((origin & 0x3f)<<6) | (destination & 0x3f);
	}

	inline static bool isSameMove(const Move move1, const Move move2)
	{
		return move1.myMove == move2.myMove;
	}

	inline Square getDestination() const
	{
		return static_cast<Square>(myMove & 0x3f);
	}

	inline Square getOrigin() const
	{
		return static_cast<Square>((myMove >> 6) & 0x3f);
	}

	inline unsigned int getFlags() const
	{
		return (myMove >> 12) & 0x0f;
	}

	inline unsigned int getPieceType() const
	{
		return (myMove >> 16) & 0x7;
	}

	inline unsigned int getPromotedPieceType() const
	{
		return (getFlags() & 0b11) + 1;
	}

    inline unsigned int getCapturedPieceType() const
	{
		return (myMove >> 19) & 0x7;
	}

	inline unsigned int getPreviousCastlingRights() const
	{
	    return (myMove >> 22) & 0xf;
	}

    inline void setDestination(const Square destination)
    {
        myMove &= ~0x3f; // clear the first 6 bits
        myMove |= (destination & 0x3f); // mask on the first 6 bits and OR it with myMoves
    }

    inline void setOrigin(const Square origin)
    {
        myMove &= ~0xfc0; myMove |= ((origin & 0x3f) << 6);
    }

	inline void setFlags(const unsigned int flag)
	{
	    myMove &= ~0xf000; myMove |= ((flag & 0xf) << 12); // Mask on the first 4 bits
	}

    inline void setCapturedPieceType(const Piece::PieceType type)
	{
	    myMove &= ~0x380000; myMove |= ((type & 0x7) << 19); // Mask on the first 3 bits
	}

    inline void setPreviousCastlingRights(const unsigned int state) // State contains the 4 bits
    {
        myMove &= ~0x3c00000; myMove |= ((state & 0xf) << 22);
    }

    //isQuiet returns true for quiet AND double pawn push move
	inline bool isQuiet() const
	{
		bool isNotQuiet = getFlags() & 0b1110;
		return !isNotQuiet;
	}

	inline bool isCapture() const {return getFlags() & CAPTURE_FLAG;}
	inline bool isEnPassant() const {return getFlags() == EP_CAPTURE_FLAG;}
	inline bool isPromotion() const {return getFlags() & PROMOTION_FLAG;}
	inline bool isQueenSideCastling() const {return getFlags() == QUEEN_SIDE_CASTLING;}
	inline bool isKingSideCastling() const {return getFlags() == KING_SIDE_CASTLING;}
	inline bool isCastling() const {return isKingSideCastling() || isQueenSideCastling();} // TODO something faster/smarter surely possible
	inline bool isNullMove() const {return myMove == NULL_MOVE;} // TODO something faster/smarter surely possible

	std::string toShortString() const
	{
		if(isNullMove())
		{
			return "";
		}

//		The move format is in long algebraic notation.
		std::array<std::string,8> letters = {{"a", "b", "c", "d", "e", "f", "g", "h"}};

		unsigned int xOrigin = getOrigin() % 8;
		unsigned int yOrigin = (getOrigin() / 8)+1;

		unsigned int xDestination = getDestination() % 8;
		unsigned int yDestination = (getDestination() / 8)+1;

		std::string promotionLetter = "";
		if(isPromotion())
		{
			unsigned int promotedType = getFlags() - Move::PROMOTION_FLAG +1;

			if(isCapture())
			{
				promotedType -= Move::CAPTURE_FLAG;
			}

			if(promotedType == Piece::KNIGHT)
			{
				promotionLetter = "n";
			}
			else if(promotedType == Piece::BISHOP)
			{
				promotionLetter = "b";
			}
			else if(promotedType == Piece::ROOK)
			{
				promotionLetter = "r";
			}
			else if(promotedType == Piece::QUEEN)
			{
				promotionLetter = "q";
			}
		}

		std::stringstream ss;
		ss << letters[xOrigin] << yOrigin << letters[xDestination] << yDestination << promotionLetter;

		return ss.str();
	}

private:

	unsigned int myMove; //26 Bits : Castling Right BEFORE the move 4 bits || Captured Piece 3 bits || Piecetype 3 bits || Flags 4 bits ||  Origin 6 bits ||  Destination 6 bits
	/*
	 * PieceType:
	 * 0 Pawn, 1 Knight, 2 Bishop, 3 Rook, 4 Queen, 5 King
	 * For captured piece 0 Pawn, 1 Knight, 2 Bishop, 3 Rook, 4 Queen, 6: no piece type
	 *
	 * Flags:
	 * The MSB of the flags is the promotion bit, the bit after is the capture bit.
	 * All the possibles flags combinations are represented below:
		0	0	0	0	quiet moves
		0	0	0	1	double pawn push
		0	0	1	0	king castle
		0	0	1	1	queen castle
		0	1	0	0	captures
		0	1	0	1	ep-capture
		1	0	0	0	knight-promotion
		1	0	0	1	bishop-promotion
		1	0	1	0	rook-promotion
		1	0	1	1	queen-promotion
		1	1	0	0	knight-promo capture
		1	1	0	1	bishop-promo capture
		1	1	1	0	rook-promo capture
		1	1	1	1	queen-promo capture


		Castling Rights BEFORE the move 4 bits
		// Same order as FEN : LEFT bit bool[3]: black queen side > black king side > white queen side > RIGHT BIT bool[0] : white king side
	*/
};


inline std::ostream& operator<<(std::ostream &strm, const Move &Move) {

	std::bitset<4> flags(Move.getFlags());
	unsigned int xOrigin = Move.getOrigin() % 8;
	unsigned int yOrigin = Move.getOrigin() / 8;

	unsigned int xDestination = Move.getDestination() % 8;
	unsigned int yDestination = Move.getDestination() / 8;

	strm << "Origin: [" << xOrigin << ", " << yOrigin << "] Dest: ["
			<< xDestination << ", " << yDestination << "] Flags: " << flags
			<< std::endl;

	return strm;
}

#endif // Move_H
