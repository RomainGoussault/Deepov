#include "BitBoardUtils.hpp"


U64 BitBoardUtils::inBetween(unsigned int sq1, unsigned int sq2) { //TODO an array lookup is better https://chessprogramming.wikispaces.com/Square+Attacked+By#Legality%20Test-In%20Between-Rectangular%20Lookup
   const U64 m1   = U64(-1);
   const U64 a2a7 = U64(0x0001010101010100);
   const U64 b2g7 = U64(0x0040201008040200);
   const U64 h1b7 = U64(0x0002040810204080); /* Thanks Dustin, g2b7 did not work for c1-a3 */
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

std::string BitBoardUtils::printBitBoard(const U64 &bitBoard)
{
	std::ostringstream strm;
	for(int rank = 7; rank >= 0 ; rank--)
	{
		strm << rank << "|  ";

		for(unsigned int file = 0; file < 8 ; file++)
		{
			char c = BitBoardUtils::isBitSet(bitBoard, file, rank) ? 'X' : '*';
			strm << c << " ";
		}

		strm << std::endl;
	}

	strm << "   ________________" << std::endl;
	strm << "    0 1 2 3 4 5 6 7" << std::endl;

	return strm.str();
}
