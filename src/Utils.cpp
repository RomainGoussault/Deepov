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
			else
			{
			}
		}
	}

	return piecePtrs;
}

