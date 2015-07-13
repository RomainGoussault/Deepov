#include "Board.hpp"
#include "Utils.hpp"
#include "BitBoardUtils.hpp"
#include "MagicMoves.hpp"
#include "MoveGen.hpp"

Board::Board() : Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -"){}

Board::Board(const std::string fen) :
bitboards(), myPinnedPieces(), myCastling()
{
	std::vector<std::string> spaceSplit;
	std::vector<std::string> piecesByRank;

	boost::split(spaceSplit, fen, boost::is_any_of(" "));
	boost::split(piecesByRank, spaceSplit[0], boost::is_any_of("/"));

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

	Utils::getCastling(spaceSplit[2], myCastling);

	if ((spaceSplit[3][0] != '-') && (getMovesHistory().size() == 0))
	{
		int epIndex = getIndexFromChar(spaceSplit[3]);
		int origin = epIndex + 8 - 16*myColorToPlay;
		int destination = epIndex - 8 + 16*myColorToPlay;
		Move lastMove(origin, destination, Move::DOUBLE_PAWN_PUSH_FLAG, Move::PAWN_TYPE);
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
}

int Board::findBlackPieceType(const int position) const
{
	if (bitboards[6]&(1LL << position))
	{
		return 0;
	}
	else if (bitboards[7]&(1LL << position))
	{
		return 1;
	}
	else if (bitboards[8]&(1LL << position))
	{
		return 2;
	}
	else if (bitboards[9]&(1LL << position))
	{
		return 3;
	}
	else if (bitboards[10]&(1LL << position))
	{
		return 4;
	}
	else
	{
		return 6;
	}
}

int Board::findWhitePieceType(const int position) const
{
	if (bitboards[0]&(1LL << position))
	{
		return 0;
	}
	else if (bitboards[1]&(1LL << position))
	{
		return 1;
	}
	else if (bitboards[2]&(1LL << position))
	{
		return 2;
	}
	else if (bitboards[3]&(1LL << position))
	{
		return 3;
	}
	else if (bitboards[4]&(1LL << position))
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
int Board::findPieceType(const int position, const int color) const
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

bool Board::isMoveLegal(Move &move, bool isCheckb)
{
	bool isLegalMove = true;
	bool isEnPassant = move.getFlags() == Move::EP_CAPTURE_FLAG;
	int color = myColorToPlay;

	int origin = move.getOrigin();
	U64 oribb = 1LL << origin;
	bool isPinned = oribb & getPinnedPieces();
	bool isKingMove = move.getPieceType() == Move::KING_TYPE;


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

bool Board::isCheck(const int color) const
{
	int ennemyColor = Utils::getOppositeColor(color);
	U64 ennemyAttackingPositions = getAttackedPositions(ennemyColor);

	U64 kingPosition = color == WHITE ? getWhiteKing() : getBlackKing();
	bool isCheck = ennemyAttackingPositions & kingPosition;

	return isCheck;
}

U64 Board::getAttackedPositions(const int color) const {
	U64 kingAttackedPosition = getKingAttackedPositions(color);
	U64 queenAttackedPosition = getQueenAttackedPositions(color);
	U64 rookAttackedPosition = getRookAttackedPositions(color);
	U64 bishopAttackedPosition = getBishopAttackedPositions(color);
	U64 knightAttackedDestinations = getKnightAttackedPositions(color);
	U64 pawnAttackedPosition = getPawnAttackedPositions(color);

	U64 attackedPositions = knightAttackedDestinations | rookAttackedPosition
			| bishopAttackedPosition | queenAttackedPosition
			| kingAttackedPosition | pawnAttackedPosition;
	return attackedPositions;
}

U64 Board::getKnightAttackedPositions(const int& color) const
{
	U64 knightAttackedDestinations = 0LL;

	U64 knightPositions = color == WHITE ? getWhiteKnights() : getBlackKnights();

	//loop through the knights:
	while(knightPositions)
	{
		const int knightIndex = BitBoardUtils::getMsbIndex(knightPositions);
		U64 knightValidDestinations = getKnightDestinations(knightIndex, color);
		knightAttackedDestinations |= knightValidDestinations;

		knightPositions = knightPositions ^ ( 0 | 1LL << knightIndex);
	}

	return knightAttackedDestinations;
}

U64 Board::getKingAttackedPositions(const int& color) const
{
	U64 kingPosition = color == WHITE ? getWhiteKing() : getBlackKing();
	U64 kingAttackedDestinations = getKingDestinations(kingPosition, color);

	return kingAttackedDestinations;
}

U64 Board::getKingDestinations(const U64 kingPos, const int& color) const
{
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

	return kingValidDestinations;
}

U64 Board::getRookAttackedPositions(const int& color) const
{
	U64 rookAttackedDestinations = 0LL;
	U64 rookPositions = color == WHITE ? getWhiteRooks() : getBlackRooks();

	//loop through the rooks:
	while(rookPositions)
	{
		int rookIndex = BitBoardUtils::getMsbIndex(rookPositions);
		rookPositions = rookPositions ^ ( 0 | 1LL << rookIndex);

		U64 rookDestinations = MagicMoves::Rmagic(rookIndex, getAllPieces()) & ~getPieces(color);
		rookAttackedDestinations |= rookDestinations;
	}

	return rookAttackedDestinations;
}

U64 Board::getBishopAttackedPositions(const int& color) const
{
	U64 bishopAttackedDestinations = 0LL;
	U64 bishopPositions = color == WHITE ? getWhiteBishops() : getBlackBishops();

	//loop through the bishops:
	while(bishopPositions)
	{
		int bishopIndex = BitBoardUtils::getMsbIndex(bishopPositions);
		bishopPositions = bishopPositions ^ ( 0 | 1LL << bishopIndex);

		U64 bishopDestinations = MagicMoves::Bmagic(bishopIndex, getAllPieces()) & ~getPieces(color);
		bishopAttackedDestinations |= bishopDestinations;
	}

	return bishopAttackedDestinations;
}

U64 Board::getQueenAttackedPositions(const int& color) const
{
	U64 queenAttackedDestinations = 0LL;
	U64 queenPositions = color == WHITE ? getWhiteQueens() : getBlackQueens();

	//loop through the queens:
	while(queenPositions)
	{
		int queenIndex = BitBoardUtils::getMsbIndex(queenPositions);
		queenPositions = queenPositions ^ ( 0 | 1LL << queenIndex);

		U64 queenDestinations = MagicMoves::Rmagic(queenIndex, getAllPieces()) | MagicMoves::Bmagic(queenIndex, getAllPieces());
		U64 queenValidDestinations = queenDestinations & ~getPieces(color);
		queenAttackedDestinations |= queenValidDestinations;
	}

	return queenAttackedDestinations;
}

U64 Board::getWhitePawnAttackedPositions() const
{
	U64 pawnAttackedDestinations = 0LL;
	U64 pawnPositions = getWhitePawns();

	//loop through the pawns:
	while(pawnPositions)
	{
		int pawnIndex = BitBoardUtils::getMsbIndex(pawnPositions);
		pawnPositions = pawnPositions ^ ( 0 | 1LL << pawnIndex);
		U64 pawnPos = 0 | 1LL << pawnIndex;

		/* check the left side of the pawn, minding the underflow File A */
		U64 leftAttack = (pawnPos & LookUpTables::CLEAR_FILE[0]) << 7;

		/* then check the right side of the pawn, minding the overflow File H */
		U64 rightAttack = (pawnPos & LookUpTables::CLEAR_FILE[7]) << 9;

		U64 pawnDestinations = leftAttack | rightAttack;
		U64 pawnValidDestinations = pawnDestinations & ~getWhitePieces();
		pawnAttackedDestinations |= pawnValidDestinations;
	}

	return pawnAttackedDestinations;
}

U64 Board::getBlackPawnAttackedPositions() const
{
	U64 pawnAttackedDestinations = 0LL;
	U64 pawnPositions = getBlackPawns();

	//loop through the pawns:
	while(pawnPositions)
	{
		int pawnIndex = BitBoardUtils::getMsbIndex(pawnPositions);
		pawnPositions = pawnPositions ^ ( 0 | 1LL << pawnIndex);
		U64 pawnPos = 0 | 1LL << pawnIndex;

		/* check the left side of the pawn, minding the underflow File A */
		U64 leftAttack = (pawnPos & LookUpTables::CLEAR_FILE[7]) >> 7;

		/* then check the right side of the pawn, minding the overflow File H */
		U64 rightAttack = (pawnPos & LookUpTables::CLEAR_FILE[0]) >> 9;

		U64 pawnDestinations = leftAttack | rightAttack;
		U64 pawnValidDestinations = pawnDestinations & ~getBlackPieces();
		pawnAttackedDestinations |= pawnValidDestinations;
	}

	return pawnAttackedDestinations;
}

U64 Board::getPawnAttackedPositions(const int& color) const
{
	if(color == WHITE)
	{
		return getWhitePawnAttackedPositions();
	}
	else
	{
		return getBlackPawnAttackedPositions();
	}
}

U64 Board::getKnightDestinations(const int knightIndex, const int& color) const
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

void Board::executeMove(Move &move)
{
	int origin = move.getOrigin();
	int destination = move.getDestination();
	int pieceType = move.getPieceType();

	if(move.isCastling())
	{
		//move King
		movePiece(origin, destination, pieceType, myColorToPlay);

		int rookOrigin = 0;
		int rookDestination = 0;

		if(move.isKingSideCastling())
		{
			rookOrigin = myColorToPlay == WHITE ? 7 : 63;
			rookDestination = myColorToPlay == WHITE ? 5 : 61;
		}
		else // QueenSideCastling
		{
			rookOrigin = myColorToPlay == WHITE ? 0 : 56;
			rookDestination =  myColorToPlay == WHITE ? 3 : 59;
		}

		//move rook
		movePiece(rookOrigin, rookDestination, Move::ROOK_TYPE, myColorToPlay);
	}
	else if (move.isPromotion())
	{
		int promotedType = move.getPromotedPieceType();

		if(move.isCapture())
		{
			//remove the captured piece
			int pieceType = move.getCapturedPieceType();
			removePiece(destination, pieceType, Utils::getOppositeColor(myColorToPlay));
		}

		removePiece(origin, Move::PAWN_TYPE, myColorToPlay);
		addPiece(destination, promotedType, myColorToPlay);
	}
	else
	{
		if (move.getFlags() == Move::EP_CAPTURE_FLAG) // watch out ep capture is a capture
		{
			unsigned int capturedPawnIndex = move.getDestination() - 8 + 16*myColorToPlay;
			removePiece(capturedPawnIndex, Move::PAWN_TYPE, Utils::getOppositeColor(myColorToPlay));
		}
		else if(move.isCapture())
		{
			//remove the captured piece
			int type(move.getCapturedPieceType());
			removePiece(destination, type, Utils::getOppositeColor(myColorToPlay));
		}

		movePiece(origin, destination, pieceType, myColorToPlay);
	}

	myMoves.push_back(move);
    updateCastlingRights(move);

	if (myColorToPlay == BLACK)
	{
		myMovesCounter++;
	}

	myHalfMovesCounter++;
	myColorToPlay = Utils::getOppositeColor(myColorToPlay);

	updateConvenienceBitboards();
}

void Board::movePiece(const int origin, const int destination, const int pieceType, const int color)
{
	movePiece(origin, destination, bitboards[pieceType+color*6]);
}

void Board::movePiece(const int origin, const int destination, U64 &bitBoard)
{
	//Remove piece from origin position
	removePiece(origin, bitBoard);

	//Add piece to destination positions
	addPiece(destination, bitBoard);
}

void Board::removePiece(const int index, const int pieceType, const int color)
{
	removePiece(index, bitboards[pieceType+color*6]);
}

void Board::addPiece(const int index, const int pieceType, const int color)
{
	addPiece(index, bitboards[pieceType+color*6]);
}

void Board::undoMove(Move &move)
{
	int origin = move.getOrigin();
	int destination = move.getDestination();
	int pieceType = move.getPieceType();

	/* Be careful to get the valid move color  */
	rewindCastlingRights(move);

	if(move.isCastling())
	{
		//move King
		movePiece(destination, origin, pieceType, Utils::getOppositeColor(myColorToPlay));

		int rookOrigin = 0;
		int rookDestination = 0;

		if(move.isKingSideCastling())
		{
			rookOrigin = Utils::getOppositeColor(myColorToPlay) == WHITE ? 7 : 63;
			rookDestination = Utils::getOppositeColor(myColorToPlay) == WHITE ? 5 : 61;
		}
		else // QueenSideCastling
		{
			rookOrigin = Utils::getOppositeColor(myColorToPlay) == WHITE ? 0 : 56;
			rookDestination =  Utils::getOppositeColor(myColorToPlay) == WHITE ? 3 : 59;
		}

		//move rook
		movePiece(rookDestination, rookOrigin, Move::ROOK_TYPE, Utils::getOppositeColor(myColorToPlay));
	}
	else if(move.isPromotion())
	{
		int promotedType = move.getFlags() - Move::PROMOTION_FLAG +1;

		if(move.isCapture())
		{
			promotedType -= Move::CAPTURE_FLAG;
			//add the captured piece
			int type(move.getCapturedPieceType());
			addPiece(destination, type, myColorToPlay);
		}

		removePiece(destination, promotedType, Utils::getOppositeColor(myColorToPlay));
		addPiece(origin, Move::PAWN_TYPE, Utils::getOppositeColor(myColorToPlay));
	}
	else
	{
		movePiece(destination, origin, pieceType, Utils::getOppositeColor(myColorToPlay));

		if (move.getFlags() == Move::EP_CAPTURE_FLAG) // watch out ep capture is a capture
		{
			unsigned int capturedPawnIndex = move.getDestination() - 8 + 16*Utils::getOppositeColor(myColorToPlay);
			addPiece(capturedPawnIndex, Move::PAWN_TYPE, myColorToPlay);
		}
		else if(move.isCapture())
		{
			//add the captured piece
			int type(move.getCapturedPieceType());
			addPiece(destination, type, myColorToPlay);
		}
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

void Board::updateConvenienceBitboards()
{
	myWhitePieces = bitboards[0] | bitboards[1] | bitboards[2] | bitboards[3] | bitboards[4] | bitboards[5];
	myBlackPieces = bitboards[6] | bitboards[7] | bitboards[8] | bitboards[9] | bitboards[10] | bitboards[11];
	myAllPieces = myBlackPieces | myWhitePieces;
}


//This methods returns the char representing the piece at the given position (file,rank)
char Board::getChar(const int file, const int rank) const
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
void Board::setBitBoards(const std::string piecesString, const int rank)
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
				bitboards[5] |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'R')
			{
				bitboards[3] |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'B')
			{
				bitboards[2] |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'Q')
			{
				bitboards[4] |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'N')
			{
				bitboards[1] |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'P')
			{
				bitboards[0] |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'k')
			{
				bitboards[11] |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'r')
			{
				bitboards[9] |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'b')
			{
				bitboards[8] |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'q')
			{
				bitboards[10] |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'n')
			{
				bitboards[7] |= 1LL << (8*rank + x);
			}
			else if (pieceChar == 'p')
			{
				bitboards[6]|= 1LL << (8*rank + x);
			}
		}
	}
}

int Board::perft(int depth)
{
	int nodes = 0;

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

int Board::divide(int depth)
{
	int nMoves;
	int nodes = 0;
	int nodeTotal = 0;

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
    int isKingMove(move.getPieceType() == Move::KING_TYPE);
    myCastling &= ~((isKingMove*3) << (myColorToPlay*2));
    /* 0011 = 3 and i shift it by 0 or by 2 , then take the ~ to get the mask*/

    /* Update Castling Rights for rook moves */
    int origin = move.getOrigin();
    if (((1LL << origin)&LookUpTables::ROOK_INITIAL_POS)!=0)
    {
        // King side produces bit 0, queen side produces bit 1
        unsigned int shift(((~origin)&0b0001) + 2*((origin&0b1000)>>3));
        unsigned int mask = ~(0b0001 << shift);
        myCastling &= mask;
        /* 0001 if this is a rook Move and i shift it by the right amount to mask the bit*/
    }

    int destination = move.getDestination();
    if (((1LL << destination)&LookUpTables::ROOK_INITIAL_POS)!=0)
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
	int color = getColorToPlay();
	U64 occ = getAllPieces();
	U64 kingBitboard = color == WHITE ? getWhiteKing() : getBlackKing();
	U64 kiSq = BitBoardUtils::getMsbIndex(kingBitboard);

	U64 rookWise = MagicMoves::Rmagic(kiSq, occ);
	U64 potPinned = rookWise & getPieces(color);
	U64 xrays = rookWise ^ MagicMoves::Rmagic(kiSq, occ ^ potPinned);
	U64 possiblePinners = color == WHITE ? (getBlackRooks() | getBlackQueens()) : (getWhiteRooks() | getWhiteQueens());
	U64 pinners = xrays & possiblePinners;

	while ( pinners )
	{
		int pinnerSq = BitBoardUtils::getMsbIndex(pinners);
		pinners = pinners ^ ( 0 | 1LL << pinnerSq);

	    myPinnedPieces  |= potPinned & BitBoardUtils::inBetween(pinnerSq, kiSq);
	}

	U64 bishopWise = MagicMoves::Bmagic(kiSq, occ);
	potPinned = bishopWise & getPieces(color);
	xrays = rookWise ^ MagicMoves::Bmagic(kiSq, occ ^ potPinned);
	possiblePinners = color == WHITE ? (getBlackBishops() | getBlackQueens()) : (getWhiteBishops() | getWhiteQueens());
	pinners = xrays & possiblePinners;

	while ( pinners )
	{
		int pinnerSq = BitBoardUtils::getMsbIndex(pinners);
		pinners = pinners ^ ( 0 | 1LL << pinnerSq);

	    myPinnedPieces  |= potPinned & BitBoardUtils::inBetween(pinnerSq,kiSq);
	}
}
