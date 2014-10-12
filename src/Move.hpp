/*
 * Move.hpp
 *
 *  Created on: 26 sept. 2014
 *      Author: Romain
 */

#ifndef MOVE_HPP_
#define MOVE_HPP_

#include <memory>
#include "Position.hpp"

class Piece;

class Move
{
public:

    Move(Position origin, Position destination);
    //myCapturedPiece needs to be a pointer
    // because the Piece is a forward declaration

    Position getOrigin() const;
    Position getDestination() const;
    bool isPromotion() const;

    Piece getCapturedPiece();
    void setCapturedPiece(std::shared_ptr<Piece> piece);


private:

    Position myOrigin;
    Position myDestination;
    std::shared_ptr<Piece> myCapturedPiece;
    bool myIsPromotion;

};

inline std::ostream& operator<<(std::ostream &strm, const Move &move)
{
    strm << "Orig: "  << move.getOrigin()  << "  Dest: "  << move.getDestination()<< std::endl;
    return strm;
}

#endif /* MOVE_HPP_ */
