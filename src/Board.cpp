#include "Board.hpp"
#include "Utils.hpp"
#include "BitBoardUtils.hpp"
#include "MagicMoves.hpp"
#include "MoveGen.hpp"

Board::Board() : Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -"){}

Board::Board(const std::string fen) :
myBitboards(), myAllPieces(), myPinnedPieces(), myCastling(), myAtkTo(), myAtkFr()
{
	std::vector<std::string> spaceSplit;
	std::vector<std::string> piecesByRank;

	boost::split(spaceSplit, fen, boost::is_any_of(" "));
	boost::split(piecesByRank, spaceSplit[0], boost::is_any_of("/"));

	unsigned int rank = 7;
	for (unsigned int i=0; i<8; i++)
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

	Utils::getCastling(spaceSplit[2], myCastling);

	if ((spaceSplit[3][0] != '-') && (getMovesHistory().size() == 0))
	{
		unsigned int epIndex = getIndexFromChar(spaceSplit[3]);
		Square origin = static_cast<Square>(epIndex + 8 - 16*myColorToPlay);
		Square destination = static_cast<Square>(epIndex - 8 + 16*myColorToPlay);
		Move lastMove(origin, destination, Move::DOUBLE_PAWN_PUSH_FLAG, Piece::PAWN);
		myMoves.push_back(lastMove);
	}

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

	updateAtkFr();
}

Piece::PieceType Board::findBlackPieceType(const Square position) const
{
	if (myBitboards[6]&(1LL << position))
	{
		return Piece::PAWN;
	}
	else if (myBitboards[7]&(1LL << position))
	{
		return Piece::KNIGHT;
	}
	else if (myBitboards[8]&(1LL << position))
	{
		return Piece::BISHOP;
	}
	else if (myBitboards[9]&(1LL << position))
	{
		return Piece::ROOK;
	}
	else if (myBitboards[10]&(1LL << position))
	{
		return Piece::QUEEN;
	}
    else if (myBitboards[11]&(1LL << position))
	{
		return Piece::KING;
	}
	else
	{
		return Piece::NO_PIECE_TYPE;
	}
}

Piece::PieceType Board::findWhitePieceType(const Square position) const
{
	if (myBitboards[0]&(1LL << position))
	{
		return Piece::PAWN;
	}
	else if (myBitboards[1]&(1LL << position))
	{
		return Piece::KNIGHT;
	}
	else if (myBitboards[2]&(1LL << position))
	{
		return Piece::BISHOP;
	}
	else if (myBitboards[3]&(1LL << position))
	{
		return Piece::ROOK;
	}
	else if (myBitboards[4]&(1LL << position))
	{
		return Piece::QUEEN;
	}
	else if (myBitboards[5]&(1LL << position))
	{
		return Piece::KING;
	}
	else
	{
		return Piece::NO_PIECE_TYPE;
	}
}


/* Commented until proven useful */

//U64 Board::getAttacksFromSq(const Square square) const
//{
//	//TODO Implement the commented functions
//	if (myBitboards[0]&(1LL << square))
//	{
//		//return getPawnDestinations(square, color);
//	}
//	else if (myBitboards[1]&(1LL << square))
//	{
//		return getKnightAttackedDestinations(square);
//	}
//	else if (myBitboards[2]&(1LL << square))
//	{
//		//return getBishopDestinations(square, color);
//	}
//	else if (myBitboards[3]&(1LL << square))
//	{
//		//return getRookDestinations(square, color);
//	}
//	else if (myBitboards[4]&(1LL << square))
//	{
//		//return getQueenDestinations(square, color);
//	}
//	else if (myBitboards[5]&(1LL << square))
//	{
//		//return getKingDestinations(square);
//	}
//	else
//	{
//		return 0LL;
//	}
//
//	return 0LL;
//}

/**
 * This method returns an unsigned int between 0 and 5 representing the type
 *  of the piece at the given position (MSB index) and for the given
 *  color.
 */
Piece::PieceType Board::findPieceType(const Square position, const Color color) const
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

Piece::Piece Board::findPieceType(const Square position) const
{
    Piece::PieceType whiteType = findWhitePieceType(position);
    Piece::PieceType blackType = findBlackPieceType(position);

    return static_cast<Piece::Piece>(whiteType + blackType*(whiteType == 6));
    //  = whiteType if piece is white, = 6+blackType if piece is black
}

bool Board::isMoveLegal(Move &move, bool isCheckb)
{
	bool isLegalMove = true;
	bool isEnPassant = move.getFlags() == Move::EP_CAPTURE_FLAG;
	Color color = myColorToPlay;

	Square origin = move.getOrigin();
	U64 oribb = 1LL << origin;
	bool isPinned = oribb & getPinnedPieces();
	bool isKingMove = move.getPieceType() == Piece::KING;

	if (isKingMove || isCheckb || isEnPassant || isPinned)
	{
		executeMove(move);

		if(isCheck(color))
		{
			isLegalMove = false;
		}

		undoMove(move);
	}

	return isLegalMove;
}

bool Board::isCheck(const Color color) const
{
	U64 kingPosition = getKing(color);
	return isBitBoardAttacked(kingPosition, color);
}

bool Board::isBitBoardAttacked(U64 bitboard, Color color) const
   {
   	bool isAttacked = false;
   	Color ennemyColor = Utils::getOppositeColor(color);

   	U64 attackers = getPieces(ennemyColor);

    while(attackers)
   	{
       	Square attackerSquare = BitBoardUtils::getMsbIndex(attackers);

       	U64 attackFr = getAtkFr(attackerSquare);

       	isAttacked |= bitboard & attackFr;

       	attackers = attackers ^ (0 | 1LL << attackerSquare);
   	}

       return isAttacked;
   };


void Board::executeMove(Move &move)
{
	Square origin = move.getOrigin();
	Square destination = move.getDestination();
	unsigned int pieceType = move.getPieceType();
	Color oppositeColor = Utils::getOppositeColor(myColorToPlay);

	if(move.isQuiet())
	{
		movePiece(origin, destination, pieceType, myColorToPlay);
	}
	else //Castling or Promotion or Capture
	{
		if(move.isCastling())
		{
			//move King
			movePiece(origin, destination, pieceType, myColorToPlay);

			Square rookOrigin = SQ_NONE;
			Square rookDestination = SQ_NONE;

			if(move.isKingSideCastling())
			{
				rookOrigin = myColorToPlay == WHITE ? SQ_H1 : SQ_H8;
				rookDestination = myColorToPlay == WHITE ? SQ_F1 : SQ_F8;
			}
			else // QueenSideCastling
			{
				rookOrigin = myColorToPlay == WHITE ? SQ_A1 : SQ_A8;
				rookDestination = myColorToPlay == WHITE ? SQ_D1 : SQ_D8;
			}

			//move rook
			movePiece(rookOrigin, rookDestination, Piece::ROOK, myColorToPlay);
		}
		else if (move.isPromotion())
		{
			unsigned int promotedType = move.getPromotedPieceType();

			if(move.isCapture())
			{
				//remove the captured piece
				unsigned int capturedPieceType = move.getCapturedPieceType();
				removePiece(destination, capturedPieceType, oppositeColor);
			}

			removePiece(origin, Piece::PAWN, myColorToPlay);
			addPiece(destination, promotedType, myColorToPlay);
		}
		else
		{
			if (move.isEnPassant()) // watch out ep capture is a capture
			{
				Square capturedPawnIndex = static_cast<Square>(move.getDestination() - 8 + 16*myColorToPlay);
				removePiece(capturedPawnIndex, Piece::PAWN, oppositeColor);
			}
			else //Move is capture
			{
				//remove the captured piece
				unsigned int type(move.getCapturedPieceType());
				removePiece(destination, type, oppositeColor);
			}

			movePiece(origin, destination, pieceType, myColorToPlay);
		}
	}

	myMoves.push_back(move);
	updateCastlingRights(move);

	myMovesCounter += myColorToPlay;

	myHalfMovesCounter++;
	myColorToPlay = oppositeColor;

	updateConvenienceBitboards();
	updateAtkFr();
}

void Board::undoMove(Move &move)
{
	Square origin = move.getOrigin();
	Square destination = move.getDestination();
	unsigned int pieceType = move.getPieceType();
	Color oppositeColor = Utils::getOppositeColor(myColorToPlay);

	/* Be careful to get the valid move color  */
	rewindCastlingRights(move);

	if(move.isQuiet())
	{
		movePiece(destination, origin, pieceType, oppositeColor);
	}
	else //Castling or Promotion or Capture
	{
		if(move.isCastling())
		{
			//move King
			movePiece(destination, origin, pieceType, oppositeColor);

			Square rookOrigin = SQ_NONE;
			Square rookDestination = SQ_NONE;

			if(move.isKingSideCastling())
			{
				rookOrigin = oppositeColor == WHITE ? SQ_H1 : SQ_H8;
				rookDestination = oppositeColor == WHITE ? SQ_F1 : SQ_F8;
			}
			else // QueenSideCastling
			{
				rookOrigin = oppositeColor == WHITE ? SQ_A1 : SQ_A8;
				rookDestination = oppositeColor == WHITE ? SQ_D1 : SQ_D8;
			}

			//move rook
			movePiece(rookDestination, rookOrigin, Piece::ROOK, oppositeColor);
		}
		else if(move.isPromotion())
		{
			unsigned int promotedType = move.getFlags() - Move::PROMOTION_FLAG +1;

			if(move.isCapture())
			{
				promotedType -= Move::CAPTURE_FLAG;
				//add the captured piece
				unsigned int type(move.getCapturedPieceType());
				addPiece(destination, type, myColorToPlay);
			}

			removePiece(destination, promotedType, oppositeColor);
			addPiece(origin, Piece::PAWN, oppositeColor);
		}
		else
		{
			movePiece(destination, origin, pieceType, oppositeColor);

			if (move.isEnPassant()) // watch out ep capture is a capture
			{
				Square capturedPawnIndex = static_cast<Square>(move.getDestination() - 8 + 16*oppositeColor);
				addPiece(capturedPawnIndex, Piece::PAWN, myColorToPlay);
			}
			else //Move is capture
			{
				//add the captured piece
				unsigned int type(move.getCapturedPieceType());
				addPiece(destination, type, myColorToPlay);
			}
		}
	}

	//Remove the last move from the myMoves list.
	myMoves.pop_back();

	myMovesCounter += myColorToPlay - 1; //-1 only when it's white to play

	myHalfMovesCounter--;
	myColorToPlay = Utils::getOppositeColor(myColorToPlay);

	updateConvenienceBitboards();
	updateAtkFr();
}

void Board::updateConvenienceBitboards()
{
	// White Pieces bitboard
	myBitboards[12] = myBitboards[0] | myBitboards[1] | myBitboards[2] | myBitboards[3] | myBitboards[4] | myBitboards[5];

	// Black Pieces bitboard
	myBitboards[13] = myBitboards[6] | myBitboards[7] | myBitboards[8] | myBitboards[9] | myBitboards[10] | myBitboards[11];

	// All Pawns bitboard
	myBitboards[14] = myBitboards[0] ^ myBitboards[6];
	// All Knights bitboard
	myBitboards[15] = myBitboards[1] ^ myBitboards[7];
	// All Bishops bitboard
	myBitboards[16] = myBitboards[2] ^ myBitboards[8];
	// All Rooks bitboard
	myBitboards[17] = myBitboards[3] ^ myBitboards[9];
	// All Queens bitboard
	myBitboards[18] = myBitboards[4] ^ myBitboards[10];
	// All Kings bitboard
	myBitboards[19] = myBitboards[5] ^ myBitboards[11];

	myAllPieces = myBitboards[12] ^ myBitboards[13];
}

void Board::updateAtkFr()
{
	std::fill(myAtkFr, myAtkFr+SQUARE_NB, 0LL);
	U64 currentBB(0);

    for (int i = WHITE; i<COLOR_NB; i++)
    {
        currentBB = getBitBoard(Piece::PAWN,static_cast<Color>(i));
        while(currentBB)
        {
            const Square square = BitBoardUtils::getMsbIndex(currentBB);
            myAtkFr[square] = getPawnAttacks(square, static_cast<Color>(i));
            currentBB = currentBB ^ ( 0 | 1LL << square);
        }

        currentBB = getBitBoard(Piece::KNIGHT,static_cast<Color>(i));
        while(currentBB)
        {
            const Square square = BitBoardUtils::getMsbIndex(currentBB);
            myAtkFr[square] = getKnightAttacks(square,static_cast<Color>(i));
            currentBB = currentBB ^ ( 0 | 1LL << square);
        }

        currentBB = getBitBoard(Piece::BISHOP,static_cast<Color>(i));
        while(currentBB)
        {
            const Square square = BitBoardUtils::getMsbIndex(currentBB);
            myAtkFr[square] = getBishopAttacks(square,static_cast<Color>(i));
            currentBB = currentBB ^ ( 0 | 1LL << square);
        }

        currentBB = getBitBoard(Piece::ROOK,static_cast<Color>(i));
        while(currentBB)
        {
            const Square square = BitBoardUtils::getMsbIndex(currentBB);
            myAtkFr[square] = getRookAttacks(square,static_cast<Color>(i));
            currentBB = currentBB ^ ( 0 | 1LL << square);
        }

        currentBB = getBitBoard(Piece::QUEEN,static_cast<Color>(i));
        while(currentBB)
        {
            const Square square = BitBoardUtils::getMsbIndex(currentBB);
            myAtkFr[square] = getQueenAttacks(square,static_cast<Color>(i));
            currentBB = currentBB ^ ( 0 | 1LL << square);
        }

        currentBB = getBitBoard(Piece::KING,static_cast<Color>(i));
        while(currentBB)
        {
            const Square square = BitBoardUtils::getMsbIndex(currentBB);
            myAtkFr[square] = getKingAttacks(square,static_cast<Color>(i));
            currentBB = currentBB ^ ( 0 | 1LL << square);
        }
	}
}

//This methods returns the char representing the piece at the given position (file,rank)
char Board::getChar(const unsigned int file, const unsigned int rank) const
{
	char c;

	if (BitBoardUtils::isBitSet(getWhitePawns(), file, rank))
	{
		c = 'P';
	}
	else if (BitBoardUtils::isBitSet(getWhiteKnights(), file, rank))
	{
		c = 'N';
	}
	else if (BitBoardUtils::isBitSet(getWhiteBishops(), file, rank))
	{
		c = 'B';
	}
	else if (BitBoardUtils::isBitSet(getWhiteRooks(), file, rank))
	{
		c = 'R';
	}
	else if (BitBoardUtils::isBitSet(getWhiteQueens(), file, rank))
	{
		c = 'Q';
	}
	else if (BitBoardUtils::isBitSet(getWhiteKing(), file, rank))
	{
		c = 'K';
	}
	else if (BitBoardUtils::isBitSet(getBlackPawns(), file, rank))
	{
		c = 'p';
	}
	else if (BitBoardUtils::isBitSet(getBlackKnights(), file, rank))
	{
		c = 'n';
	}
	else if (BitBoardUtils::isBitSet(getBlackBishops(), file, rank))
	{
		c = 'b';
	}
	else if (BitBoardUtils::isBitSet(getBlackRooks(), file, rank))
	{
		c = 'r';
	}
	else if (BitBoardUtils::isBitSet(getBlackQueens(), file, rank))
	{
		c = 'q';
	}
	else if (BitBoardUtils::isBitSet(getBlackKing(), file, rank))
	{
		c = 'k';
	}
	else {
		c = '*';
	}

	return c;
}

//This methods adds pieces to the board at the given rank and based on the give piecesString
void Board::setBitBoards(const std::string piecesString, const unsigned int rank)
{
	unsigned int x = -1;
	unsigned int piecesCharSize = piecesString.size();
	char piecesChar[piecesCharSize];
	strcpy(piecesChar, piecesString.c_str());

	for (unsigned int i=0; i<piecesCharSize; i++)
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
				myBitboards[5] |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'R')
			{
				myBitboards[3] |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'B')
			{
				myBitboards[2] |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'Q')
			{
				myBitboards[4] |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'N')
			{
				myBitboards[1] |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'P')
			{
				myBitboards[0] |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'k')
			{
				myBitboards[11] |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'r')
			{
				myBitboards[9] |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'b')
			{
				myBitboards[8] |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'q')
			{
				myBitboards[10] |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'n')
			{
				myBitboards[7] |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'p')
			{
				myBitboards[6]|= 1LL << (8*rank + x);
			}
		}
	}
}

unsigned int Board::perft(unsigned int depth)
{
	unsigned int nodes = 0;

	if (depth == 0)
	{
		return 1;
	}

	MoveGen movegen(*this);
	std::vector<Move> moves(movegen.getMoves());

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

unsigned int Board::divide(unsigned int depth)
{
	unsigned int nMoves;
	unsigned int nodes = 0;
	unsigned int nodeTotal = 0;

	if (depth == 0)
	{
		return 1;
	}

	MoveGen movegen(*this);
	std::vector<Move> moves(movegen.getMoves());
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

boost::optional<Move> Board::getEnemyLastMove() const
{
	if (myMoves.size()>0)
	{
		return boost::optional<Move>(myMoves[myMoves.size()-1]);
	}
	else
	{
		return boost::optional<Move>();
	}
}

void Board::updateCastlingRights(Move &move)
{
    move.setPreviousCastlingRights(myCastling); // store for undoMove

    /* Update Castling rights for king move */
    unsigned int isKingMove(move.getPieceType() == Piece::KING);
    myCastling &= ~((isKingMove*3) << (myColorToPlay*2));
    /* 0011 = 3 and i shift it by 0 or by 2 , then take the ~ to get the mask*/

    /* Update Castling Rights for rook moves */
    Square origin = move.getOrigin();
    if (((1LL << origin)&Tables::ROOK_INITIAL_POS)!=0)
    {
        // King side produces bit 0, queen side produces bit 1
        unsigned int shift(((~origin)&0b0001) + 2*((origin&0b1000)>>3));
        unsigned int mask = ~(0b0001 << shift);
        myCastling &= mask;
        /* 0001 if this is a rook Move and i shift it by the right amount to mask the bit*/
    }

    Square destination = move.getDestination();
    if (((1LL << destination)&Tables::ROOK_INITIAL_POS)!=0)
    {
        /* Update Castling Rights for rook capture */
        unsigned int shift(((~destination)&0b0001) + 2*((destination&0b1000)>>3));
        unsigned int mask = ~(0b0001 << shift);
        myCastling &= mask;
    }
}

void Board::rewindCastlingRights(const Move &move)
{
    myCastling = move.getPreviousCastlingRights();
}

void Board::updatePinnedPieces()
{
	Color color = getColorToPlay();
	Color oppositeColor = Utils::getOppositeColor(color);
	U64 occ = getAllPieces();
	U64 kingBitboard = getKing(color);
	U64 kiSq = BitBoardUtils::getMsbIndex(kingBitboard);

	U64 rookWise = MagicMoves::Rmagic(kiSq, occ);
	U64 potPinned = rookWise & getPieces(color);
	U64 xrays = rookWise ^ MagicMoves::Rmagic(kiSq, occ ^ potPinned);
	U64 possiblePinners = getRooks(oppositeColor) | getQueens(oppositeColor);
	U64 pinners = xrays & possiblePinners;

	while ( pinners )
	{
		unsigned int pinnerSq = BitBoardUtils::getMsbIndex(pinners);
		pinners = pinners ^ ( 0 | 1LL << pinnerSq);

	    myPinnedPieces  |= potPinned & BitBoardUtils::inBetween(pinnerSq, kiSq);
	}

	U64 bishopWise = MagicMoves::Bmagic(kiSq, occ);
	potPinned = bishopWise & getPieces(color);
	xrays = rookWise ^ MagicMoves::Bmagic(kiSq, occ ^ potPinned);
	possiblePinners = getBishops(oppositeColor) | getQueens(oppositeColor);
	pinners = xrays & possiblePinners;

	while ( pinners )
	{
		unsigned int pinnerSq = BitBoardUtils::getMsbIndex(pinners);
		pinners = pinners ^ ( 0 | 1LL << pinnerSq);

	    myPinnedPieces  |= potPinned & BitBoardUtils::inBetween(pinnerSq,kiSq);
	}
}
