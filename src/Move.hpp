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
    const static unsigned int QUIET_FLAG = 0b0000;
    const static unsigned int EP_CAPTURE_FLAG = 0b0101;
    const static unsigned int DOUBLE_PAWN_PUSH_FLAG =0b0001;
	const static unsigned int CAPTURE_FLAG = 0b0100;
	const static unsigned int PROMOTION_FLAG = 0b1000;
	const static unsigned int KING_SIDE_CASTLING = 	0b0010;
	const static unsigned int QUEEN_SIDE_CASTLING = 0b0011;
    const static unsigned int NULL_MOVE = 0;

	inline Move() : myMove(0), myMoveRating(0) //Default constructor = null move
	{
	}

	inline Move(int move) : myMove(move), myMoveRating(0)
	{
	}

	inline Move(Square origin, Square destination, unsigned int flags, Piece::PieceType pieceType) : myMoveRating(0)
	{
        int capturedPieceType = Piece::NO_PIECE_TYPE;
		myMove = ((capturedPieceType & 0x7) << 19) | ((pieceType &0x7)<<16) | ((flags & 0xf)<<12) | ((origin & 0x3f)<<6) | (destination & 0x3f);
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

    inline unsigned int getMoveRating() const
    {
        return myMoveRating;
    }

    inline unsigned int getMove() const
    {
        return myMove;
    }

    inline Move16 getMove16() const
    {
        return static_cast<Move16>(myMove & 0xffff);
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

    inline void setMoveRating(const unsigned int rating)
    {
        myMoveRating = rating;
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
    inline bool isDoublePawnPush() const {return getFlags() == DOUBLE_PAWN_PUSH_FLAG;}
    inline bool isNullMove() const {return myMove == NULL_MOVE;}

    std::string toShortString() const;

    /* Equality to check if two moves are identical for killer moves */
    inline bool operator==(const Move &otherMove) const 
    {
        return (getOrigin() == otherMove.getOrigin()) && (getDestination() == otherMove.getDestination()) && (getFlags() == otherMove.getFlags());
    };

    /* Defines an order for moves ratings */
    inline bool operator<(const Move &otherMove) const {return getMoveRating() < otherMove.getMoveRating();};
    inline bool operator>(const Move &otherMove) const {return getMoveRating() > otherMove.getMoveRating();};
    inline bool operator<=(const Move &otherMove) const {return getMoveRating() <= otherMove.getMoveRating();};
    inline bool operator>=(const Move &otherMove) const {return getMoveRating() >= otherMove.getMoveRating();};


private:

	unsigned int myMove; //26 Bits : Castling Right BEFORE the move 4 bits || Captured Piece 3 bits || Piecetype 3 bits || Flags 4 bits ||  Origin 6 bits ||  Destination 6 bits
	/*
	 * PieceType:
	 * 0 Pawn, 1 Knight, 2 Bishop, 3 Rook, 4 Queen, 5 King, 6 no piece type (for null move)
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

    unsigned int myMoveRating;
};


inline std::ostream& operator<<(std::ostream &strm, const Move &move) {

	std::bitset<4> flags(move.getFlags());
	unsigned int xOrigin = move.getOrigin() % 8;
	unsigned int yOrigin = move.getOrigin() / 8;

	unsigned int xDestination = move.getDestination() % 8;
	unsigned int yDestination = move.getDestination() / 8;

    unsigned int moveOrderingScore = move.getMoveRating();

	strm << move.toShortString() << " "     
            << "Origin: [" << xOrigin << ", " << yOrigin << "] Dest: ["
			<< xDestination << ", " << yDestination << "] Flags: " << flags
            << " MO score : " << moveOrderingScore 
			<< std::endl;

	return strm;
}

#endif // Move_H
