//============================================================================
// Name        : Deepov.cpp
// Author      : Romain Goussault
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <vector>
#include <memory>
#include <iostream>
#include <chrono>
#include <ctime>
#include <ratio>

#include "Color.hpp"
#include "Eval.hpp"
#include "Search.hpp"
#include "Board.hpp"
#include "MoveGen.hpp"
#include "Move.hpp"
#include "MagicMoves.hpp"

U64 inBetween(int sq1, int sq2) { //TODO an array look is better https://chessprogramming.wikispaces.com/Square+Attacked+By#Legality%20Test-In%20Between-Rectangular%20Lookup
   const U64 m1   = C64(-1);
   const U64 a2a7 = C64(0x0001010101010100);
   const U64 b2g7 = C64(0x0040201008040200);
   const U64 h1b7 = C64(0x0002040810204080); /* Thanks Dustin, g2b7 did not work for c1-a3 */
   U64 btwn, line, rank, file;

   btwn  = (m1 << sq1) ^ (m1 << sq2);
   file  =   (sq2 & 7) - (sq1   & 7);
   rank  =  ((sq2 | 7) -  sq1) >> 3 ;
   line  =      (   (file  &  7) - 1) & a2a7; /* a2a7 if same file */
   line += 2 * ((   (rank  &  7) - 1) >> 58); /* b1g1 if same rank */
   line += (((rank - file) & 15) - 1) & b2g7; /* b2g7 if same diagonal */
   line += (((rank + file) & 15) - 1) & h1b7; /* h1b7 if same antidiag */
   line *= btwn & -btwn; /* mul acts like shift by smaller square */
   return line & btwn;   /* return the bits on that line in-between */
}

int main() {

	MagicMoves::initmagicmoves();
	Board board("3r4/8/8/8/8/3P4/8/3K4 w - -");

	U64 occ = board.getAllPieces() ;
	U64 kiSq = Utils::getMsbIndex(board.getWhiteKing());
	std::cout << board << std::endl;
	std::cout << "king index " << kiSq << std::endl;


	std::cout << "rookWise "  << std::endl;
	U64 rookWise  = MagicMoves::Rmagic(kiSq, occ);
	std::cout << Board::printBitBoard(rookWise) << std::endl;

	std::cout << "potPinned "  << std::endl;
	U64 potPinned = rookWise & board.getPieces(WHITE);
	std::cout << Board::printBitBoard(potPinned) << std::endl;

	std::cout << "xrays "  << std::endl;
	U64 xrays     = rookWise ^ MagicMoves::Rmagic( kiSq, occ ^ potPinned);
	std::cout << Board::printBitBoard(xrays) << std::endl;

	std::cout << "pinners "  << std::endl;
	U64 pinners = xrays    & (board.getBlackRooks() | board.getBlackQueens());
	std::cout << Board::printBitBoard(pinners) << std::endl;

	U64 pinned    = 0;
	while ( pinners )
	{
		int pinnerSq = Utils::getMsbIndex(pinners);
		pinners = pinners ^ ( 0 | 1LL << pinnerSq);

	    pinned  |= potPinned & inBetween(pinnerSq,kiSq);
	   // pinners &= pinners - 1;
	}


	std::cout << "pinned "  << std::endl;
	std::cout << Board::printBitBoard(pinned) << std::endl;
	//TODO code inBetween



/*
	int rookSq = 59;

	U64 attacks = MagicMoves::Rmagic(rookSq, occ) & ~board.getPieces(0);
	Board::printBitBoard(attacks);
	std::cout << Board::printBitBoard(attacks) << std::endl;

	//U64 rookDestinations = MagicMoves::Rmagic(rookIndex, myBoard->getAllPieces()) & ~myBoard->getPieces(color);

	U64 blockers = board.getPieces(BLACK);
	blockers &= attacks;
	std::cout << " blockers" << std::endl;

	std::cout << Board::printBitBoard(blockers) << std::endl;
/*
	U64 result = attacks ^ MagicMoves::Rmagic(occ ^ blockers, rookSq);


	std::cout << Board::printBitBoard(result) << std::endl;





/*




	std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board("k4K2/8/8/3q4/8/1R3N1P/8/8 b - -"));

	Search search(sp);
	std::cout << search.negaMaxRoot(3,0,0) << std::endl;
	Move move = search.myBestMove;

	std::cout << *sp << std::endl;
	std::cout << move.toShortString()<< std::endl;

	sp->executeMove(move);

	std::cout << *sp << std::endl;
	/*

	Utils::getPerformanceIndicator();
	Utils::getPerformanceIndicator();
	//Romain : 9sec = 995 556 Nodes/sec
	// -O3 1.6sec 5 609 501 Nodes/sec
	// Navid -O3 9sec 100 000 N/sec
	//Stockfish 180 385 601Nodes/sec

    std::string str;
    std::cin >> str;*/

	return 0;
}
