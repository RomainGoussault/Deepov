#include "FastBoard.hpp"
#include "Utils.hpp"
#include "MagicMoves.hpp"
#include "MoveGen.hpp"






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
		myColorToPlay(WHITE),
	    myMovesCounter(0),
	    myHalfMovesCounter(0)
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
*/
		// I put a condition in case the FEN format doesn't include the move counters
		if (spaceSplit.size() >= 5)
		{
		    myMovesCounter = Utils::convertStringToInt(spaceSplit[4]);
	    //  Waiting for a fix for windows! Ahaha a link to the error maybe?
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
		}
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


int FastBoard::findBlackPieceType(const int position) const
{
    if ((myBlackPawns&(1LL << position))>>position==1)
    {
        return 0;
    }
    else if ((myBlackKnights&(1LL << position))>>position==1)
    {
        return 1;
    }
    else if ((myBlackBishops&(1LL << position))>>position==1)
    {
        return 2;
    }
    else if ((myBlackRooks&(1LL << position))>>position==1)
    {
        return 3;
    }
    else if ((myBlackQueens&(1LL << position))>>position==1)
    {
        return 4;
    }
    else
    {
        return 6;
    }
}

int FastBoard::findWhitePieceType(const int position) const
{
    if ((myWhitePawns&(1LL << position))>>position==1)
    {
        return 0;
    }
    else if ((myWhiteKnights&(1LL << position))>>position==1)
    {
        return 1;
    }
    else if ((myWhiteBishops&(1LL << position))>>position==1)
    {
        return 2;
    }
    else if ((myWhiteRooks&(1LL << position))>>position==1)
    {
        return 3;
    }
    else if ((myWhiteQueens&(1LL << position))>>position==1)
    {
        return 4;
    }
    else
    {
        return 6;
    }
}

/**
 * This method returns an int between 0 and 5 representing the type
 *  of the piece at the given position (MSB index) and for the given
 *  color.
 */
int FastBoard::findPieceType(const int position, const int color) const
{
	if(color == WHITE)
	{
		return findWhitePieceType(position);
	}
	else
	{
		return findBlackPieceType(position);
	}
}

bool FastBoard::isMoveLegal(FastMove &move)
{
	bool isLegalMove = true;
	int color = myColorToPlay;

	executeMove(move);

	if(isCheck(color))
	{
		isLegalMove = false;
	}

	undoMove(move);

	return isLegalMove;
}

bool FastBoard::isCheck(const int color) const
{
	int ennemyColor = Utils::getOppositeColor(color);
	U64 ennemyAttackingPositions = getAttackedPositions(ennemyColor);

	U64 kingPosition = color == WHITE ? getWhiteKing() : getBlackKing();

	bool isCheck = ennemyAttackingPositions & kingPosition;

	return isCheck;
}

U64 FastBoard::getAttackedPositions(const int color) const
{
	U64 knightAttackedDestinations = getKnightAttackedPositions(color);
	U64 rookAttackedPosition = getRookAttackedPositions(color);

	U64 attackedPositions = knightAttackedDestinations | rookAttackedPosition;
	return attackedPositions;
}

U64 FastBoard::getKnightAttackedPositions(const int& color) const
{
	U64 knightAttackedDestinations = 0LL;

	U64 knightPositions = color == WHITE ? getWhiteKnights() : getBlackKnights();

	//loop through the knights:
	while(knightPositions)
	{
		const int knightIndex = FastBoard::getMsbIndex(knightPositions);
		U64 knightValidDestinations = getKnightDestinations(knightIndex, color);
		knightAttackedDestinations |= knightValidDestinations;

		knightPositions = knightPositions ^ ( 0 | 1LL << knightIndex);
	}

	return knightAttackedDestinations;
}

U64 FastBoard::getRookAttackedPositions(const int& color) const
{
	U64 rookAttackedDestinations = 0LL;
	U64 rookPositions = color == WHITE ? getWhiteRooks() : getBlackRooks();

	//loop through the rooks:
	while(rookPositions)
	{
		int rookIndex = FastBoard::getMsbIndex(rookPositions);
		rookPositions = rookPositions ^ ( 0 | 1LL << rookIndex);

		U64 rookDestinations = Rmagic(rookIndex, getAllPieces()) & ~getPieces(color);
		rookAttackedDestinations |= rookDestinations;
	}

	return rookAttackedDestinations;
}


U64 FastBoard::getKnightDestinations(const int knightIndex, const int& color) const
{
	const U64 knightPos = 0 | 1LL << knightIndex;

	/* we can ignore the rank clipping since the overflow/underflow with
		respect to rank simply vanishes. We only care about the file
		overflow/underflow. */
	U64	knight_clip_file_h(knightPos & LookUpTables::CLEAR_FILE[7]);
	U64 knight_clip_file_a(knightPos & LookUpTables::CLEAR_FILE[0]);

	U64	knight_clip_file_gh(knightPos & LookUpTables::CLEAR_FILE[7] & LookUpTables::CLEAR_FILE[6]);
	U64 knight_clip_file_ab(knightPos & LookUpTables::CLEAR_FILE[0] & LookUpTables::CLEAR_FILE[1]);

	U64 WNW(knight_clip_file_ab << 6);
	U64 NNW(knight_clip_file_a << 15);
	U64 NNE(knight_clip_file_h << 17);
	U64 ENE(knight_clip_file_gh << 10);

	U64 ESE(knight_clip_file_gh >> 6);
	U64 SSE(knight_clip_file_h >> 15);
	U64 SSW(knight_clip_file_a >> 17);
	U64 WSW(knight_clip_file_ab >> 10);

	/* N = north, NW = North West, from knight location, etc */
	U64 knightValidDestinations = (WNW | NNW | NNE | ENE | ESE | SSE | SSW | WSW) & ~getPieces(color);

	return knightValidDestinations;
}

void FastBoard::executeMove(const FastMove &move)
{
	int origin = move.getOrigin();
	int destination = move.getDestination();
	int pieceType = move.getPieceType();

/*	if(move.isCastling())
	{
		movePiece(pieceToMove, destination);
		Position rookOrigin;
		Position rookDestination;

		if (destination.getX() == 6)
		{
			rookOrigin = Position(7, destination.getY());
			rookDestination = Position(5, destination.getY());
		}
		else
		{
			rookOrigin = Position(0, destination.getY());
			rookDestination = Position(3, destination.getY());
		}

		movePiece(getPiecePtr(rookOrigin),rookDestination);
	}
	else if(move.isPromotion())
	{
		if(isCaptureMove)
		{
			//remove the captured piece
			removePiece(capturePiecePtr->getPosition());
		}

        removePiece(pieceToMove->getPosition());
        addPiece(move.getPromotedPiece());
	}
	else
	{*/
		if(move.isCapture())
		{
			//remove the captured piece
			int type(move.getCapturedPieceType());
			removePiece(destination, type, Utils::getOppositeColor(myColorToPlay)); //TODO does not work for en passsant
		}

	movePiece(origin, destination, pieceType, myColorToPlay);


	myMoves.push_back(move);

	if (myColorToPlay == BLACK)
    {
        myMovesCounter++;
    }

    myHalfMovesCounter++;
	myColorToPlay = Utils::getOppositeColor(myColorToPlay);

	updateConvenienceBitboards();
}

void FastBoard::movePiece(const int origin, const int destination, const int pieceType, const int color)
{
	switch (pieceType)
	{
	case FastMove::KNIGHT_TYPE:
		color == WHITE ? movePiece(origin, destination, myWhiteKnights) : movePiece(origin, destination, myBlackKnights) ;
		break;
	case FastMove::PAWN_TYPE:
		color == WHITE ? movePiece(origin, destination, myWhitePawns) : movePiece(origin, destination, myBlackPawns) ;
		break;
	case FastMove::BISHOP_TYPE:
		color == WHITE ? movePiece(origin, destination, myWhiteBishops) : movePiece(origin, destination, myBlackBishops) ;
		break;
	case FastMove::ROOK_TYPE:
		color == WHITE ? movePiece(origin, destination, myWhiteRooks) : movePiece(origin, destination, myBlackRooks) ;
		break;
	case FastMove::QUEEN_TYPE:
		color == WHITE ? movePiece(origin, destination, myWhiteQueens) : movePiece(origin, destination, myBlackQueens) ;
		break;
	case FastMove::KING_TYPE:
		color == WHITE ? movePiece(origin, destination, myWhiteKing) : movePiece(origin, destination, myBlackKing) ;
		break;
	}
}

void FastBoard::movePiece(const int origin, const int destination, U64 &bitBoard)
{
	//Remove piece from origin position
	removePiece(origin, bitBoard);

	//Add piece to destination positions
	addPiece(destination, bitBoard);
}

void FastBoard::removePiece(const int index, const int pieceType, const int color)
{
    switch (pieceType)
	{
	case FastMove::KNIGHT_TYPE:
		color == WHITE ? removePiece(index, myWhiteKnights) : removePiece(index, myBlackKnights) ;
		break;
	case FastMove::PAWN_TYPE:
		color == WHITE ? removePiece(index, myWhitePawns) : removePiece(index, myBlackPawns) ;
		break;
	case FastMove::BISHOP_TYPE:
		color == WHITE ? removePiece(index, myWhiteBishops) : removePiece(index, myBlackBishops) ;
		break;
	case FastMove::ROOK_TYPE:
		color == WHITE ? removePiece(index, myWhiteRooks) : removePiece(index, myBlackRooks) ;
		break;
	case FastMove::QUEEN_TYPE:
		color == WHITE ? removePiece(index, myWhiteQueens) : removePiece(index, myBlackQueens) ;
		break;
	}
}

void FastBoard::addPiece(const int index, const int pieceType, const int color)
{
    switch (pieceType)
	{
	case FastMove::KNIGHT_TYPE:
		color == WHITE ? addPiece(index, myWhiteKnights) : addPiece(index, myBlackKnights) ;
		break;
	case FastMove::PAWN_TYPE:
		color == WHITE ? addPiece(index, myWhitePawns) : addPiece(index, myBlackPawns) ;
		break;
	case FastMove::BISHOP_TYPE:
		color == WHITE ? addPiece(index, myWhiteBishops) : addPiece(index, myBlackBishops) ;
		break;
	case FastMove::ROOK_TYPE:
		color == WHITE ? addPiece(index, myWhiteRooks) : addPiece(index, myBlackRooks) ;
		break;
	case FastMove::QUEEN_TYPE:
		color == WHITE ? addPiece(index, myWhiteQueens) : addPiece(index, myBlackQueens) ;
		break;
	}
}

void FastBoard::undoMove(const FastMove &move)
{
	int origin = move.getOrigin();
	int destination = move.getDestination();
	int pieceType = move.getPieceType();
/*
	// Be careful to get the valid move color
	rewindCastlingRights(move, Utils::getOppositeColor(myColorToPlay));

	if(move.isCastling())
	{
        movePiece(pieceToMove,origin);

        Position rookOrigin;
		Position rookDestination;

		if (destination.getX() == 6)
		{
			rookOrigin = Position(7, destination.getY());
			rookDestination = Position(5, destination.getY());
		}
		else
		{
			rookOrigin = Position(0, destination.getY());
			rookDestination = Position(3, destination.getY());
		}

		movePiece(getPiecePtr(rookDestination),rookOrigin);
	}
	else if(move.isPromotion())
	{
        removePiece(destination);
//        PiecePtr pawnPtr(new Pawn(origin, Utils::getOppositeColor(myColorToPlay)));
//        addPiece(pawnPtr);
        addPiece(move.getPromotedPawn());

        if(isCaptureMove)
		{
			//add the captured piece
			addPiece(capturePiecePtr);
		}

	}
	else
	{*/
	movePiece(destination, origin, pieceType, Utils::getOppositeColor(myColorToPlay));

		if(move.isCapture())
		{
			//add the captured piece
			int type(move.getCapturedPieceType());
			addPiece(destination, type, myColorToPlay); // TODO
		}

	//Remove the last move from the myMoves list.
	myMoves.pop_back();

    if (myColorToPlay == WHITE)
    {
        myMovesCounter--;
    }

    myHalfMovesCounter--;
	myColorToPlay = Utils::getOppositeColor(myColorToPlay);

	updateConvenienceBitboards();
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

int FastBoard::perft(int depth)
{
	int nodes = 0;

	if (depth == 0)
	{
		return 1;
	}

    MoveGen movegen(*this);
	std::vector<FastMove> moves(movegen.getMoves());

	if (moves.empty())
    {
       // std::cout << "Position is mate" <<std::endl;
    }

	for (auto &move : moves)
	{
		executeMove(move);

		nodes += perft(depth - 1);
		undoMove(move);
	}

	return nodes;
}

int FastBoard::divide(int depth)
{
	int nMoves;
	int nodes = 0;
	int nodeTotal = 0;

	if (depth == 0)
	{
		return 1;
	}

    MoveGen movegen(*this);
	std::vector<FastMove> moves(movegen.getMoves());
	nMoves = moves.size();

	for (auto &move : moves)
	{
		executeMove(move);
		nodes = perft(depth - 1);
		std::cout <<  move.toShortString() <<  " " << nodes << std::endl;
		nodeTotal += nodes;
		undoMove(move);
	}

	std::cout << std::endl;
	std::cout << "Total nodes: " << nodeTotal << std::endl;
	std::cout << "Total moves: " << nMoves << std::endl;
	return nodes;
}

boost::optional<FastMove> FastBoard::getEnemyLastMove() const
{
	if (myMoves.size()>0)
	{
		return boost::optional<FastMove>(myMoves[myMoves.size()-1]);
	}
	else
	{
		return boost::optional<FastMove>();
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
