#include "FastBoard.hpp"
#include "Utils.hpp"
#include "MagicMoves.hpp"
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

    /* Moves methods */


void FastBoard::addQuietMoves(U64 quietDestinations, int pieceIndex, std::vector<FastMove>& moves) const
{
	while (quietDestinations)
	{
		//Getting the index of the MSB
		int positionMsb = getMsbIndex(quietDestinations);

		FastMove move = FastMove(pieceIndex, positionMsb, 0, FastMove::KNIGHT_TYPE);
		moves.push_back(move);

		//Removing the MSB
		quietDestinations = quietDestinations ^ (0 | 1LL << positionMsb);
	}
}

void FastBoard::addCaptureMoves(U64 captureDestinations, int pieceIndex, std::vector<FastMove>& moves) const
{
	while (captureDestinations)
	{
		//Getting the index of the MSB
		int positionMsb = getMsbIndex(captureDestinations);
		FastMove move = FastMove(pieceIndex, positionMsb, FastMove::CAPTURE_FLAG);
		moves.push_back(move);

		//Removing the MSB
		captureDestinations = captureDestinations ^ (0 | 1LL << positionMsb);
	}
}

void FastBoard::addPromotionMoves(U64 promotionDestinations, int pieceIndex, std::vector<FastMove>& moves) const
{
	while (promotionDestinations)
	{
		//Getting the index of the MSB
		int positionMsb = getMsbIndex(promotionDestinations);
		FastMove move = FastMove(pieceIndex, positionMsb, FastMove::PROMOTION_FLAG);
		moves.push_back(move);
		move.setFlags(FastMove::PROMOTION_FLAG+1);
		moves.push_back(move);
		move.setFlags(FastMove::PROMOTION_FLAG+2);
		moves.push_back(move);
		move.setFlags(FastMove::PROMOTION_FLAG+3);
		moves.push_back(move);

		//Removing the MSB
		promotionDestinations = promotionDestinations ^ (0 | 1LL << positionMsb);
	}
}

void FastBoard::addPromotionCaptureMoves(U64 promotionDestinations, int pieceIndex, std::vector<FastMove>& moves) const
{
	while (promotionDestinations)
	{
		//Getting the index of the MSB
		int positionMsb = getMsbIndex(promotionDestinations);
		unsigned int flag = FastMove::PROMOTION_FLAG+FastMove::PROMOTION_FLAG;
		FastMove move = FastMove(pieceIndex, positionMsb, flag);
		moves.push_back(move);
		move.setFlags(flag+1);
		moves.push_back(move);
		move.setFlags(flag+2);
		moves.push_back(move);
		move.setFlags(flag+3);
		moves.push_back(move);

		//Removing the MSB
		promotionDestinations = promotionDestinations ^ (0 | 1LL << positionMsb);
	}
}

    /* Get moves methods */
std::vector<FastMove> FastBoard::getKingPseudoLegalMoves(const int& color) const
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

	addQuietMoves(kingQuietDestinations, kingIndex, kingMoves);
	addCaptureMoves(kingCaptureDestinations,kingIndex, kingMoves);

	return kingMoves;
}


std::vector<FastMove> FastBoard::getQueenPseudoLegalMoves(const int& color) const
{
	std::vector<FastMove> queenMoves;
	U64 queenPositions = color == WHITE ? myWhiteQueens : myBlackQueens;

	//loop through the queens:
	while(queenPositions)
	{
		int queenIndex = getMsbIndex(queenPositions);
		queenPositions = queenPositions ^ ( 0 | 1LL << queenIndex);

		int ennemyColor = Utils::getOppositeColor(color);

		U64 bishopDestinations = Bmagic(queenIndex, myAllPieces) & ~getPieces(color);
		U64 rookDestinations = Rmagic(queenIndex, myAllPieces) & ~getPieces(color);
		U64 queenDestinations = bishopDestinations ^ rookDestinations ;

		U64 queenCaptureDestinations = queenDestinations & getPieces(ennemyColor);
		U64 queenQuietDestinations = queenDestinations ^ queenCaptureDestinations;

		addQuietMoves(queenQuietDestinations, queenIndex, queenMoves);
		addCaptureMoves(queenCaptureDestinations, queenIndex, queenMoves);
	}

	return queenMoves;
}

std::vector<FastMove> FastBoard::getBishopPseudoLegalMoves(const int& color) const
{
	std::vector<FastMove> bishopMoves;
	U64 bishopPositions = color == WHITE ? myWhiteBishops : myBlackBishops;

	//loop through the bishops:
	while(bishopPositions)
	{
		int bishopIndex = getMsbIndex(bishopPositions);
		bishopPositions = bishopPositions ^ ( 0 | 1LL << bishopIndex);

		int ennemyColor = Utils::getOppositeColor(color);

		U64 bishopDestinations = Bmagic(bishopIndex, myAllPieces) & ~getPieces(color);

		U64 bishopCaptureDestinations = bishopDestinations & getPieces(ennemyColor);
		U64 bishopQuietDestinations = bishopDestinations ^ bishopCaptureDestinations;

		addQuietMoves(bishopQuietDestinations, bishopIndex, bishopMoves);
		addCaptureMoves(bishopCaptureDestinations, bishopIndex, bishopMoves);
	}

	return bishopMoves;
}

std::vector<FastMove> FastBoard::getRookPseudoLegalMoves(const int& color) const
{
	std::vector<FastMove> rookMoves;
	U64 rookPositions = color == WHITE ? myWhiteRooks : myBlackRooks;

	//loop through the rooks:
	while(rookPositions)
	{
		int rookIndex = getMsbIndex(rookPositions);
		rookPositions = rookPositions ^ ( 0 | 1LL << rookIndex);

		int ennemyColor = Utils::getOppositeColor(color);

		U64 rookDestinations = Rmagic(rookIndex, myAllPieces) & ~getPieces(color);

		U64 rookCaptureDestinations = rookDestinations & getPieces(ennemyColor);
		U64 rookQuietDestinations = rookDestinations ^ rookCaptureDestinations;

		addQuietMoves(rookQuietDestinations, rookIndex, rookMoves);
		addCaptureMoves(rookCaptureDestinations, rookIndex, rookMoves);
	}

	return rookMoves;
}

std::vector<FastMove> FastBoard::getKnightPseudoLegalMoves(const int& color) const
{
	std::vector<FastMove> knightMoves;

	U64 knightPositions = color == WHITE ? myWhiteKnights : myBlackKnights;

	//loop through the knights:
	while(knightPositions)
	{
		int knightIndex = getMsbIndex(knightPositions);
		U64 knightPos = 0 | 1LL << knightIndex;
		knightPositions = knightPositions ^ ( 0 | 1LL << knightIndex);

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

		/* compute only the places where the knight can move and attack. The caller
		will interpret this as a white or black knight. */

		int ennemyColor = Utils::getOppositeColor(color);

		U64 knightCaptureDestinations = knightValidDestinations & getPieces(ennemyColor);
		U64 knightQuietDestinations = knightValidDestinations ^ knightCaptureDestinations;

		addQuietMoves(knightQuietDestinations, knightIndex, knightMoves);
		addCaptureMoves(knightCaptureDestinations, knightIndex, knightMoves);
	}

	return knightMoves;
}

std::vector<FastMove> FastBoard::getWhitePawnPseudoLegalMoves() const
{
	std::vector<FastMove> pawnMoves;
    U64 pawnPositions = myWhitePawns;

    while(pawnPositions)
	{
        int pawnIndex = getMsbIndex(pawnPositions);
		U64 pawnPos = 0 | 1LL << pawnIndex;
		pawnPositions = pawnPositions ^ ( 0 | 1LL << pawnIndex);

    /* check the single space in front of the white pawn */
	U64 firstStep = (pawnPos << 8) & ~myAllPieces;

	/* for all moves that came from rank 2 (home row), and passed the above
		filter, thereby being on rank 3, ie. on MASK_RANK[2], check and see if I can move forward
		one more */
	U64 twoSteps = ((firstStep & LookUpTables::MASK_RANK[2]) << 8) & ~myAllPieces;

	/* the union of the movements dictate the possible moves forward
		available */

	U64 whitePawnQuietMoves = firstStep | twoSteps ;

	/* next we calculate the pawn attacks */

	/* check the left side of the pawn, minding the underflow File A */
	U64 leftAttack = (pawnPos & LookUpTables::CLEAR_FILE[0]) << 7;

	/* then check the right side of the pawn, minding the overflow File H */
	U64 rightAttack = (pawnPos & LookUpTables::CLEAR_FILE[7]) << 9;

	/* the union of the left and right attacks together make up all the
        possible attacks
	   Calculate where I can _actually_ attack something */

	U64 validAttacks = (leftAttack | rightAttack) & myBlackPieces;

	/* then we combine the two situations in which a white pawn can legally
		attack/move. */
	// whitePawnValid = (firstStep | twoSteps) | validAttacks; // not needed for now

    addQuietMoves(whitePawnQuietMoves & LookUpTables::CLEAR_RANK[7],pawnIndex, pawnMoves);
    addPromotionMoves(whitePawnQuietMoves & LookUpTables::MASK_RANK[7],pawnIndex, pawnMoves);
    addCaptureMoves(validAttacks & LookUpTables::CLEAR_RANK[7],pawnIndex, pawnMoves);
    addPromotionCaptureMoves(validAttacks & LookUpTables::MASK_RANK[7],pawnIndex, pawnMoves);

	}

	return pawnMoves;
}

std::vector<FastMove> FastBoard::getBlackPawnPseudoLegalMoves() const
{
	std::vector<FastMove> pawnMoves;
    U64 pawnPositions = myBlackPawns;

    while(pawnPositions)
	{
        int pawnIndex = getMsbIndex(pawnPositions);
		U64 pawnPos = 0 | 1LL << pawnIndex;
		pawnPositions = pawnPositions ^ ( 0 | 1LL << pawnIndex);

    /* check the single space in front of the white pawn */
	U64 firstStep = (pawnPos >> 8) & ~myAllPieces;

	/* for all moves that came from rank 7 (home row), and passed the above
		filter, thereby being on rank 6, ie. on MASK_RANK[5], check and see if I can move forward
		one more */
	U64 twoSteps = ((firstStep & LookUpTables::MASK_RANK[5]) >> 8) & ~myAllPieces;

	/* the union of the movements dictate the possible moves forward
		available */

	U64 blackPawnQuietMoves = firstStep | twoSteps ;

	/* next we calculate the pawn attacks */

	/* check the left side of the pawn, minding the underflow File A */
	U64 leftAttack = (pawnPos & LookUpTables::CLEAR_FILE[7]) >> 7;

	/* then check the right side of the pawn, minding the overflow File H */
	U64 rightAttack = (pawnPos & LookUpTables::CLEAR_FILE[0]) >> 9;

	/* the union of the left and right attacks together make up all the
        possible attacks
	   Calculate where I can _actually_ attack something */

	U64 validAttacks = (leftAttack | rightAttack) & myWhitePieces;

	/* then we combine the two situations in which a white pawn can legally
		attack/move. */
	// blackPawnValid = (firstStep | twoSteps) | validAttacks; // not needed for now

    addQuietMoves(blackPawnQuietMoves & LookUpTables::CLEAR_RANK[0],pawnIndex, pawnMoves);
    addPromotionMoves(blackPawnQuietMoves & LookUpTables::MASK_RANK[0],pawnIndex, pawnMoves);
    addCaptureMoves(validAttacks & LookUpTables::CLEAR_RANK[0],pawnIndex, pawnMoves);
    addPromotionCaptureMoves(validAttacks & LookUpTables::MASK_RANK[0],pawnIndex, pawnMoves);

	}

	return pawnMoves;
}

std::vector<FastMove> FastBoard::getMoves() const
{
    return myMoves;
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
			removePiece(destination); //TODO does not work for en passsant
		}

		movePiece(origin, destination, pieceType);


	myMoves.push_back(move);

	if (myColorToPlay == BLACK)
    {
        myMovesCounter++;
    }

    myHalfMovesCounter++;
	myColorToPlay = Utils::getOppositeColor(myColorToPlay);

	updateConvenienceBitboards();
}

void FastBoard::movePiece(const int origin, const int destination, const int pieceType)
{
/*
	switch (pieceType)
	{
	case FastMove::KNIGHT_TYPE:
		moveKnight(origin, destination);
		break;
	case 0:
		break;
	}*/

	switch (pieceType)
	{
	case FastMove::KNIGHT_TYPE:
		myColorToPlay == WHITE ? movePiece(origin, destination, myWhiteKnights) : movePiece(origin, destination, myBlackKnights) ;
		break;
	case 0:
		break;
	}
}

void FastBoard::movePiece(const int origin, const int destination, U64 &bitBoard)
{
	bitBoard &= 1LL & (0 << origin);
	bitBoard |= 0 | (1LL << destination);
}

void FastBoard::removePiece(const int index)
{
	//TODO implement
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
