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
#include "Piece.hpp"
#include "MoveGen.hpp"
#include "FastBoard.hpp"

#include "math.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <ratio>
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

void Utils::getCastling(std::string const& castleString, bool (&castleBool)[4])
{
	if (castleString[0] == '-')
	{
		return;
	}
	else
	{
		for (unsigned int i=0; i<castleString.size(); ++i)
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
			else
			{
				throw std::runtime_error("");
			}
		}
	}
}

void Utils::getCastling(std::string const& castleString, int &castlingRights)
{
	castlingRights = 0b0000;
	if (castleString[0] == '-')
	{
		return;
	}
	else
	{
		for (unsigned int i=0; i<castleString.size(); ++i)
		{
			if (castleString[i]=='K')
			{
				castlingRights |= 0x1;
			}
			else if (castleString[i]=='Q')
			{
				castlingRights |= 0x2;
			}
			else if (castleString[i]=='k')
			{
				castlingRights |= 0x4;
			}
			else if (castleString[i]=='q')
			{
				castlingRights |= 0x8;
			}
			else
			{
				throw std::runtime_error("");
			}
		}
	}
}

Position Utils::getPosition(std::string const& stringPosition)
{
	int row = stringPosition[1] - '0'; //convert from char to int
	row = row-1; //In our board model row starts at index 0.

	if (stringPosition[0] == 'a')
	{
		return Position(0,row);
	}
	else if (stringPosition[0] == 'b')
	{
		return Position(1,row);
	}
	else if (stringPosition[0] == 'c')
	{
		return Position(2,row);
	}
	else if (stringPosition[0] == 'd')
	{
		return Position(3,row);
	}
	else if (stringPosition[0] == 'e')
	{
		return Position(4,row);
	}
	else if (stringPosition[0] == 'f')
	{
		return Position(5,row);
	}
	else if (stringPosition[0] == 'g')
	{
		return Position(6,row);
	}
	else if (stringPosition[0] == 'h')
	{
		return Position(7,row);
	}

	throw std::invalid_argument("");
}

//Waiting to have a fix for stoi
int Utils::convertStringToInt(std::string const& fenMoveCounter)
{
	int counter = 0;
	for (unsigned int i=0; fenMoveCounter[i] != '\0';++i)
	{
		counter = counter*10 + (fenMoveCounter[i]- '0') ;
	}
	return counter;
}

Move Utils::getUCIMove(std::string const& fenMove, Board &board)
{
	std::string subMove = fenMove.substr(0,2) ;
	Position origin = getPosition(subMove) ;
	subMove = fenMove.substr(2,2) ;
	Position destination = getPosition(subMove) ;

	Move theMove(origin,destination);

	if (fenMove.size() >= 5)
	{
		switch (fenMove[5])
		{
		case 'k' :
		{
			PiecePtr promotedPtr(new Knight(destination, board.getColorToPlay()));
			theMove.setPromotedPiece(promotedPtr);
			break;
		}
		case 'b' :
		{
			PiecePtr promotedPtr(new Bishop(destination, board.getColorToPlay()));
			theMove.setPromotedPiece(promotedPtr);
			break;
		}
		case 'r' :
		{
			PiecePtr promotedPtr(new Rook(destination, board.getColorToPlay()));
			theMove.setPromotedPiece(promotedPtr);
			break;
		}
		case 'q' :
		{
			PiecePtr promotedPtr(new Queen(destination, board.getColorToPlay()));
			theMove.setPromotedPiece(promotedPtr);
			break;
		}
		default :
		{
			throw std::invalid_argument("");
		}
		}
	}

	if (!board.isPositionFree(destination))
	{
		theMove.setCapturedPiece(board.getPiecePtr(destination));
	}

	if (abs(origin.getX()-destination.getX()) == 2 &&
			std::dynamic_pointer_cast<King>(board.getPiecePtr(origin)) != nullptr)
	{
		theMove.setIsCastling();
	}

	return theMove ;
}

void Utils::getPerformanceIndicator()
{
	initmagicmoves();

    FastBoard board("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -");
	MoveGen moveGen(board);

	std::chrono::high_resolution_clock::time_point t1 =
			std::chrono::high_resolution_clock::now();

	int n = board.perft(4);
	board = FastBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	n += board.perft(5);

	std::chrono::high_resolution_clock::time_point t2 =
			std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> time_span = std::chrono::duration_cast<
			std::chrono::duration<double>>(t2 - t1);

	int nodesPerSec = n/time_span.count();
	std::cout << "It took me " << time_span.count() << " seconds.";
	std::cout << "Nodes per sec: " << nodesPerSec;

	std::cout << std::endl;
}
