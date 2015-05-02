#include "FastBoard.hpp"
#include "Utils.hpp"
#include <boost/algorithm/string.hpp>




FastBoard::FastBoard() :
		myWhitePawns(0 | 0xFF << 8),
		myWhiteKnights(0 | (1 << 1) | (1 << 6) ),
		myWhiteBishops(0 | (1 << 2) | (1 << 5) ),
		myWhiteRooks(0 | (1 << 0) | (1 << 7) ),
		myWhiteQueens(0 | (1 << 3)),
		myWhiteKing(0 | (1 << 4)),
		myBlackPawns(0 | 0xFFLL  << 8*6),
		myBlackKnights(0 | (1LL << (8*7+1)) | (1LL<< (8*7+6)) ),
		myBlackBishops(0 | (1LL << (8*7+2)) | (1LL<< (8*7+5)) ),
		myBlackRooks(0 | (1LL << (8*7+0)) | (1LL<< (8*7+7)) ),
		myBlackQueens(0 | (1LL << (8*7+3)) ),
		myBlackKing(0 | (1LL << (8*7+4)) ),
		myWhitePieces(myWhitePawns | myWhiteKnights | myWhiteBishops | myWhiteRooks | myWhiteQueens | myWhiteKing),
		myBlackPieces(myBlackPawns | myBlackKnights | myBlackBishops | myBlackRooks | myBlackQueens | myBlackKing),
		myAllPieces(myBlackPieces | myWhitePieces),
		myColorToPlay(WHITE)
{
}

FastBoard::FastBoard(const std::string fen)
{
		std::vector<std::string> spaceSplit;
		std::vector<std::string> piecesByRank;

		boost::split(spaceSplit, fen, boost::is_any_of(" "));
		boost::split(piecesByRank, spaceSplit[0], boost::is_any_of("/"));

		myWhitePawns = 0;
		myWhiteKnights = 0;
		myWhiteBishops = 0;
		myWhiteRooks = 0;
		myWhiteQueens = 0;
		myWhiteKing = 0;
		myBlackPawns = 0;
		myBlackKnights = 0;
		myBlackBishops = 0;
		myBlackRooks = 0;
		myBlackQueens = 0;
		myBlackKing = 0;

		int rank = 7;
		for (int i=0; i<8; i++)
		{
			setBitBoards(piecesByRank[i], rank);
			rank--;
		}

		updateConvenienceBitboards();

		if (spaceSplit[1][0] == 'w')
		{
			myColorToPlay = WHITE;
		}
		else if (spaceSplit[1][0] == 'b')
		{
			myColorToPlay = BLACK;
		}

		/*for (int i=0; i<3; ++i)
		{
			myCastling[i] = false;
		}

		Utils::getCastling(spaceSplit[2],myCastling);

		if (spaceSplit[3][0] == '-')
		{
			myEnPassant=boost::optional<Position>();
		}
		else
		{
			myEnPassant=boost::optional<Position>(Utils::getPosition(spaceSplit[3]));
		}

		// I put a condition in case the FEN format doesn't include the move counters
		if (spaceSplit.size() >= 5)
		{
		    myMovesCounter = Utils::convertStringToInt(spaceSplit[4]);
	    // Waiting for a fix for windows
		//	myMovesCounter = std::stoi(spaceSplit[4]);
		}
		else
		{
			myMovesCounter = 0;
		}

		if (spaceSplit.size() >= 6)
		{
		    myHalfMovesCounter = Utils::convertStringToInt(spaceSplit[5]);
		//	myHalfMovesCounter = std::stoi(spaceSplit[5]);
		}
		else
		{
			myHalfMovesCounter = 0;
		}*/
}


	/* Get the bitboards */

U64 FastBoard::getWhitePawns() const{return myWhitePawns;}
U64 FastBoard::getWhiteKnights() const{return myWhiteKnights ;}
U64 FastBoard::getWhiteBishops() const{return myWhiteBishops;}
U64 FastBoard::getWhiteRooks() const{return myWhiteRooks;}
U64 FastBoard::getWhiteQueens() const{return myWhiteQueens;}
U64 FastBoard::getWhiteKing() const{return myWhiteKing;}

U64 FastBoard::getBlackPawns() const{return myBlackPawns;}
U64 FastBoard::getBlackKnights() const{return myBlackKnights;}
U64 FastBoard::getBlackBishops() const{return myBlackBishops;}
U64 FastBoard::getBlackRooks() const{return myBlackRooks;}
U64 FastBoard::getBlackQueens() const{return myBlackQueens;}
U64 FastBoard::getBlackKing() const{return myBlackKing;}

U64 FastBoard::getWhitePieces() const{return myWhitePieces;}
U64 FastBoard::getBlackPieces() const{return myBlackPieces;}
U64 FastBoard::getAllPieces() const{return myAllPieces;}

	/*  **********  */

    /* Moves methods */

std::vector<FastMove> FastBoard::getKingPseudoLegalMoves(const int& color)
{
	U64 kingPos = color == WHITE ? myWhiteKing : myBlackKing;

    /* Copied from http://pages.cs.wisc.edu/~psilord/blog/data/chess-pages/nonsliding.html */
	/* we can ignore the rank clipping since the overflow/underflow with
		respect to rank simply vanishes. We only care about the file
		overflow/underflow. */
    U64	king_clip_file_h(kingPos & LookUpTables::CLEAR_FILE[7]);
	U64 king_clip_file_a(kingPos & LookUpTables::CLEAR_FILE[0]);

	/* remember the representation of the board in relation to the bitindex
		when looking at these shifts.... There is an error in the source link
		the code is copied from !! */
	U64 NW(king_clip_file_a << 7);
	U64 N(kingPos << 8);
	U64 NE(king_clip_file_h << 9);
	U64 E(king_clip_file_h << 1);

	U64 SE(king_clip_file_h >> 7);
	U64 S(kingPos >> 8);
	U64 SW(king_clip_file_a >> 9);
	U64 W(king_clip_file_a >> 1);

	/* N = north, NW = North West, from King location, etc */
	U64 kingDestinations = NW | N | NE | E | SE | S | SW | W;
	U64 kingValidDestinations = kingDestinations & ~getPieces(color);

	int ennemyColor = Utils::getOppositeColor(color);
	int kingIndex = getMsbIndex(kingPos);
	std::vector<FastMove> kingMoves;

	U64 kingCaptureDestinations = kingValidDestinations & getPieces(ennemyColor);
	U64 kingQuietDestinations = kingValidDestinations ^ kingCaptureDestinations;

	while(kingQuietDestinations)
	{
		//Getting the index of the MSB
		int positionMsb = getMsbIndex(kingQuietDestinations);

		FastMove move = FastMove(kingIndex, positionMsb, 0);
		kingMoves.push_back(move);

		//Removing the MSB
		kingQuietDestinations = kingQuietDestinations ^ ( 0 | 1LL << positionMsb);
	}

	while(kingCaptureDestinations)
	{
		//Getting the index of the MSB
		int positionMsb = getMsbIndex(kingCaptureDestinations);

		FastMove move = FastMove(kingIndex, positionMsb, FastMove::CAPTURE_FLAG);
		kingMoves.push_back(move);

		//Removing the MSB
		kingCaptureDestinations = kingCaptureDestinations ^ ( 0 | 1LL << positionMsb);
	}

	return kingMoves;
}
/*
U64 FastBoard::queenPseudoLegalMoves(const int& color, const U64& queenPos) const
{
    return 0;
}

U64 FastBoard::bishopPseudoLegalMoves(const int& color, const U64& bishopPos) const
{
    return 0;
}

U64 FastBoard::rookPseudoLegalMoves(const int& color, const U64& rookPos) const
{
    return 0;
}
*/
U64 FastBoard::knightPseudoLegalMoves(const int& color, const U64& knightPos) const
{
	/* we can ignore the rank clipping since the overflow/underflow with
		respect to rank simply vanishes. We only care about the file
		overflow/underflow. */

    U64	knight_clip_file_h(knightPos & LookUpTables::CLEAR_FILE[7]);
	U64 knight_clip_file_a(knightPos & LookUpTables::CLEAR_FILE[0]);

    U64	knight_clip_file_gh(knightPos & LookUpTables::CLEAR_FILE[7] & LookUpTables::CLEAR_FILE[6]);
	U64 knight_clip_file_ab(knightPos & LookUpTables::CLEAR_FILE[0] & LookUpTables::CLEAR_FILE[1]);

	/* remember the representation of the board in relation to the bitindex
		when looknight at these shifts.... */
    U64 WNW(knight_clip_file_ab << 6);
	U64 NNW(knight_clip_file_a << 15);
	U64 NNE(knight_clip_file_h << 17);
	U64 ENE(knight_clip_file_gh << 10);

	U64 ESE(knight_clip_file_gh >> 6);
    U64 SSE(knight_clip_file_h >> 15);
	U64 SSW(knight_clip_file_a >> 17);
	U64 WSW(knight_clip_file_ab >> 10);


	/* N = north, NW = North West, from knight location, etc */
	U64 knightMoves = WNW | NNW | NNE | ENE | ESE | SSE | SSW | WSW;

	U64 knightValid = knightMoves & ~getPieces(color);

	/* compute only the places where the knight can move and attack. The caller
		will interpret this as a white or black knight. */
	return knightValid;
}

U64 FastBoard::pawnPseudoLegalMoves(const int& color, const U64& pawnPos) const
{
    return 0;
}

std::vector<FastMove> FastBoard::getMoves() const
{
    return myMoves;
}

void FastBoard::updateConvenienceBitboards()
{
	myWhitePieces = myWhitePawns | myWhiteKnights | myWhiteBishops | myWhiteRooks | myWhiteQueens | myWhiteKing;
	myBlackPieces = myBlackPawns | myBlackKnights | myBlackBishops | myBlackRooks | myBlackQueens | myBlackKing;
	myAllPieces = myBlackPieces | myWhitePieces;
}

bool FastBoard::isBitSet(U64 bitBoard, const int x, const int y)
{
	int shift = 8*y + x;

	return (0 | 1LL << shift) & bitBoard;
}

//This methods returns the char representing the piece at the given position (file,rank)
char FastBoard::getChar(const int file, const int rank) const
{
	char c;

	if (FastBoard::isBitSet(getWhitePawns(), file, rank))
	{
		c = 'P';
	}
	else if (FastBoard::isBitSet(getWhiteKnights(), file, rank))
	{
		c = 'N';
	}
	else if (FastBoard::isBitSet(getWhiteBishops(), file, rank))
	{
		c = 'B';
	}
	else if (FastBoard::isBitSet(getWhiteRooks(), file, rank))
	{
		c = 'R';
	}
	else if (FastBoard::isBitSet(getWhiteQueens(), file, rank))
	{
		c = 'Q';
	}
	else if (FastBoard::isBitSet(getWhiteKing(), file, rank))
	{
		c = 'K';
	}
	else if (FastBoard::isBitSet(getBlackPawns(), file, rank))
	{
		c = 'p';
	}
	else if (FastBoard::isBitSet(getBlackKnights(), file, rank))
	{
		c = 'n';
	}
	else if (FastBoard::isBitSet(getBlackBishops(), file, rank))
	{
		c = 'b';
	}
	else if (FastBoard::isBitSet(getBlackRooks(), file, rank))
	{
		c = 'r';
	}
	else if (FastBoard::isBitSet(getBlackQueens(), file, rank))
	{
		c = 'q';
	}
	else if (FastBoard::isBitSet(getBlackKing(), file, rank))
	{
		c = 'k';
	}
	else {
		c = '*';
	}

	return c;
}

//This methods adds pieces to the board at the given rank and based on the give piecesString
void FastBoard::setBitBoards(const std::string piecesString, const int rank)
{
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

			if (pieceChar == 'K')
			{
				myWhiteKing |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'R')
			{
				myWhiteRooks |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'B')
			{
				myWhiteBishops |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'Q')
			{
				myWhiteQueens |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'N')
			{
				myWhiteKnights |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'P')
			{
				myWhitePawns|= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'k')
			{
				myBlackKing |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'r')
			{
				myBlackRooks |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'b')
			{
				myBlackBishops |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'q')
			{
				myBlackQueens |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'n')
			{
				myBlackKnights |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'p')
			{
				myBlackPawns|= 1LL << (8*rank + x);
			}
		}
	}
}

std::string FastBoard::printBitBoard(const U64 &bitBoard)
{
	std::ostringstream strm;
	for(int rank = 7; rank >= 0 ; rank--)
	{
		strm << rank << "|  ";

		for(int file = 0; file < 8 ; file++)
		{
			char c = FastBoard::isBitSet(bitBoard, file, rank) ? 'X' : '*';
			strm << c << " ";
		}

		strm << std::endl;
	}

	strm << "   ________________" << std::endl;
	strm << "    0 1 2 3 4 5 6 7" << std::endl;

	return strm.str();
}
