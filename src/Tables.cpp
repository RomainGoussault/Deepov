#include "Tables.hpp"
#include "Types.hpp"

/* List of tables declarations*/
U64 Tables::FRONT_SPANS[2][64];
U64 Tables::PAWN_ATTACK_SPANS[2][64];
U64 Tables::PASSED_PAWN_MASK[2][64];
U64 Tables::ATTACK_TABLE[Piece::PIECE_TYPE_NB][64];
U64 Tables::PAWN_ATTACK_TABLE[Color::COLOR_NB][64];
U64 Tables::LINE_BB[SQUARE_NB][SQUARE_NB];
U64 Tables::SQUARE_BB[SQUARE_NB];

/* Methods */
void Tables::init()
{
	for (Square square = SQ_A1; square < SQUARE_NB; ++square)
	{
		FRONT_SPANS[WHITE][square] = frontBB(square,WHITE);
		FRONT_SPANS[BLACK][square] = frontBB(square,BLACK);
		PAWN_ATTACK_SPANS[WHITE][square] = sidesBB(square,WHITE);
		PAWN_ATTACK_SPANS[BLACK][square] = sidesBB(square,BLACK);
		PASSED_PAWN_MASK[WHITE][square] = FRONT_SPANS[WHITE][square] | PAWN_ATTACK_SPANS[WHITE][square];
		PASSED_PAWN_MASK[BLACK][square] = FRONT_SPANS[BLACK][square] | PAWN_ATTACK_SPANS[BLACK][square];
		ATTACK_TABLE[Piece::KNIGHT][square] = knightAttacks(square);
		ATTACK_TABLE[Piece::KING][square] = kingAttacks(square);
		ATTACK_TABLE[Piece::PAWN][square] = 0x0;
		ATTACK_TABLE[Piece::BISHOP][square] = bishopAttacks(square);
		ATTACK_TABLE[Piece::ROOK][square] = rookAttacks(square);
		ATTACK_TABLE[Piece::QUEEN][square] = queenAttacks(square);
		ATTACK_TABLE[Piece::NO_PIECE_TYPE][square] = 0x0;
		PAWN_ATTACK_TABLE[WHITE][square] = pawnAttacks(square,WHITE);
		PAWN_ATTACK_TABLE[BLACK][square] = pawnAttacks(square,BLACK);
		SQUARE_BB[square] = 1ULL << square;


		for (Square square2 = SQ_A1; square2 < SQUARE_NB; ++square2)
		{
			bool AreOnsameLine = getFile(square) == getFile(square2);
			bool AreOnsameRank = getRank(square) == getRank(square2);

			if(AreOnsameLine)
			{
				U64 b = 0LL; //TODO finish implementing: needs to have a bitboard that's a line between square and square2
				//Note better overload Square and Bitboard operator
				LINE_BB[square][square2] = b;
			}

			//ifSameRank

			//ifSameDiag

			//Or use Magic Number?

		}
	}
}

U64 Tables::frontBB(const Square pos,Color color)
{
	U64 shift = 0xffffffffffffffff << (pos+1); // pos+1 for WHITE, take the complement for BLACk
	if (color == BLACK){shift = (~shift) >> 1;}
	return  shift & MASK_FILE[Utils::getFile(pos)];
}


U64 Tables::sidesBB(const Square pos,Color color)
{
	unsigned int file = Utils::getFile(pos);
	U64 leftSide(0);
	U64 rightSide(0);
	if (file > 0){leftSide = frontBB(static_cast<Square>(pos-1), color);}
	if (file < 7){rightSide = frontBB(static_cast<Square>(pos+1), color);}
	return leftSide | rightSide;
}


U64 Tables::kingAttacks(const Square pos)
{
	U64 posBB = 0 | 1LL << pos;
	/* Copied from http://pages.cs.wisc.edu/~psilord/blog/data/chess-pages/nonsliding.html */
	/* we can ignore the rank clipping since the overflow/underflow with
	respect to rank simply vanishes. We only care about the file
	overflow/underflow. */
	U64	king_clip_file_h(posBB & Tables::CLEAR_FILE[7]);
	U64 king_clip_file_a(posBB & Tables::CLEAR_FILE[0]);

	/* remember the representation of the board in relation to the bitindex
	when looking at these shifts.... There is an error in the source link
	the code is copied from !! */
	U64 NW(king_clip_file_a << 7);
	U64 N(posBB << 8);
	U64 NE(king_clip_file_h << 9);
	U64 E(king_clip_file_h << 1);

	U64 SE(king_clip_file_h >> 7);
	U64 S(posBB >> 8);
	U64 SW(king_clip_file_a >> 9);
	U64 W(king_clip_file_a >> 1);

	/* N = north, NW = North West, from King location, etc */
	return (NW | N | NE | E | SE | S | SW | W);
}

U64 Tables::knightAttacks(const Square pos)
{

	U64 posBB = 0 | 1LL << pos;
	U64	knight_clip_file_h(posBB & Tables::CLEAR_FILE[7]);
	U64 knight_clip_file_a(posBB & Tables::CLEAR_FILE[0]);
	U64	knight_clip_file_gh(posBB & Tables::CLEAR_FILE[7] & Tables::CLEAR_FILE[6]);
	U64 knight_clip_file_ab(posBB & Tables::CLEAR_FILE[0] & Tables::CLEAR_FILE[1]);

	U64 WNW(knight_clip_file_ab << 6);
	U64 NNW(knight_clip_file_a << 15);
	U64 NNE(knight_clip_file_h << 17);
	U64 ENE(knight_clip_file_gh << 10);

	U64 ESE(knight_clip_file_gh >> 6);
	U64 SSE(knight_clip_file_h >> 15);
	U64 SSW(knight_clip_file_a >> 17);
	U64 WSW(knight_clip_file_ab >> 10);

	/* N = north, NW = North West, from knight location, etc */
	return (WNW | NNW | NNE | ENE | ESE | SSE | SSW | WSW);
}

U64 Tables::pawnAttacks(const Square pos, Color color)
{
	U64 posBB = 0 | 1LL << pos;
	U64 leftAttack(0);
	U64 rightAttack(0);

	if (color == WHITE)
	{
		leftAttack = (posBB & Tables::CLEAR_FILE[0]) << 7;
		rightAttack = (posBB & Tables::CLEAR_FILE[7]) << 9;
	}
	else if (color == BLACK)
	{
		leftAttack = (posBB & Tables::CLEAR_FILE[7]) >> 7;
		rightAttack = (posBB & Tables::CLEAR_FILE[0]) >> 9;
	}

	return (leftAttack | rightAttack);
}
