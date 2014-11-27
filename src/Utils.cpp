/*
 * Utils.cpp
 *
 *  Created on: 24 sept. 2014
 */
#include "Utils.hpp"
#include "Color.hpp"
#include "King.hpp"
#include "Queen.hpp"
#include "Rook.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"
#include "Pawn.hpp"
#include "Piece.hpp"

#include <boost/algorithm/string.hpp>


std::vector<PiecePtr> Utils::getPiecesFromFen(std::string fen)
{
	std::vector<PiecePtr> pieces;

	std::vector<std::string> spaceSplit;
	std::vector<std::string> piecesByRank;

	boost::split(spaceSplit, fen, boost::is_any_of(" "));
	boost::split(piecesByRank, spaceSplit[0], boost::is_any_of("/"));

	int rank = 7;
	for (int i=0; i<8; i++)
	{
		std::vector<PiecePtr> piecesOnRank = Utils::getPieces(piecesByRank[i], rank);
		pieces.insert(pieces.end(), piecesOnRank.begin(), piecesOnRank.end());
		rank--;
	}

	return pieces;
}

std::vector<PiecePtr> Utils::getPieces(std::string piecesString, int rank)
{
	std::vector<PiecePtr> piecePtrs;
	int x = -1;
	int piecesCharSize = piecesString.size();
	char piecesChar[piecesCharSize];
	strcpy(piecesChar, piecesString.c_str());

	for (int i=0; i<piecesCharSize; i++)
	{
		char pieceChar = piecesChar[i];

		if(isdigit(pieceChar))
		{
			x += pieceChar - '0';
		}
		else
		{
			x++;
			int color = islower(pieceChar) ? BLACK : WHITE;
			pieceChar = tolower(pieceChar);
			Position position(x, rank);

			if (pieceChar == 'k')
			{
				PiecePtr piecePtr(new King(position, color));
				piecePtrs.push_back(piecePtr);
			}
			else if (pieceChar == 'r')
			{
				PiecePtr piecePtr(new Rook(position, color));
				piecePtrs.push_back(piecePtr);
			}
			else if (pieceChar == 'b')
			{
				PiecePtr piecePtr(new Bishop(position, color));
				piecePtrs.push_back(piecePtr);
			}
			else if (pieceChar == 'q')
			{
				PiecePtr piecePtr(new Queen(position, color));
				piecePtrs.push_back(piecePtr);
			}
			else if (pieceChar == 'n')
			{
				PiecePtr piecePtr(new Knight(position, color));
				piecePtrs.push_back(piecePtr);
			}
            else if (pieceChar == 'p')
			{
				PiecePtr piecePtr(new Pawn(position, color));
				piecePtrs.push_back(piecePtr);
			}
			else
			{
			}
		}
	}

	return piecePtrs;
}

bool[3] Utils::getCastling(std:string castleString)
{
    bool[3] castleBool(false);

    if (castleString[0]) == '-')
    {
        return castleBool;
    }
    else
    {
        for (int i=0; i<castleString.size(); ++i)
        {
            if (castleString[i]=='K')
            {
                castleBool[0]=true;
            }
            else if (castleString[i]=='Q')
            {
                castleBool[1]=true;
            }
            else if (castleString[i]=='k')
            {
                castleBool[2]=true;
            }
            else if (castleString[i]=='q')
            {
                castleBool[3]=true;
            }
        }
    }

    return castleBool;

}

Position Utils::getSquare(std::string fenSquare)
{
    int line(0);

    if (fenSquare[1] == '3')
    {
        line = 2;
    }
    else if (fenSquare[2] == '5')
    {
        line = 4;
    }

    if (fenSquare[0] == 'a')
    {
        return Position(0,line)
    }
    else if (fenSquare[0] == 'b')
    {
        return Position(1,line)
    }
    else if (fenSquare[0] == 'c')
    {
        return Position(2,line)
    }
    else if (fenSquare[0] == 'd')
    {
        return Position(3,line)
    }
    else if (fenSquare[0] == 'e')
    {
        return Position(4,line)
    }
    else if (fenSquare[0] == 'f')
    {
        return Position(5,line)
    }
    else if (fenSquare[0] == 'g')
    {
        return Position(6,line)
    }
    else if (fenSquare[0] == 'h')
    {
        return Position(7,line)
    }
}
