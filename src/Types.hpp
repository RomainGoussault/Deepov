/*
  Deepov, a UCI chess playing engine.

  Copyright (c) 20014-2016 Romain Goussault, Navid Hedjazian

    Deepov is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Deepov is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Deepov.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TYPES_HPP_
#define TYPES_HPP_

#include <cstdint>

#ifndef _U64
typedef std::uint64_t U64;
#define _U64
#endif // _U64

#ifndef _Move16
typedef std::uint16_t Move16;
#define _Move16
#endif

typedef std::uint64_t Zkey; 

enum Color {
	WHITE = 0,
	BLACK = 1,
    NO_COLOR,
    COLOR_NB = 2
};

enum Stage {
    OPENING = 0,
    ENDGAME = 1
};

enum Square {
  SQ_A1, SQ_B1, SQ_C1, SQ_D1, SQ_E1, SQ_F1, SQ_G1, SQ_H1,
  SQ_A2, SQ_B2, SQ_C2, SQ_D2, SQ_E2, SQ_F2, SQ_G2, SQ_H2,
  SQ_A3, SQ_B3, SQ_C3, SQ_D3, SQ_E3, SQ_F3, SQ_G3, SQ_H3,
  SQ_A4, SQ_B4, SQ_C4, SQ_D4, SQ_E4, SQ_F4, SQ_G4, SQ_H4,
  SQ_A5, SQ_B5, SQ_C5, SQ_D5, SQ_E5, SQ_F5, SQ_G5, SQ_H5,
  SQ_A6, SQ_B6, SQ_C6, SQ_D6, SQ_E6, SQ_F6, SQ_G6, SQ_H6,
  SQ_A7, SQ_B7, SQ_C7, SQ_D7, SQ_E7, SQ_F7, SQ_G7, SQ_H7,
  SQ_A8, SQ_B8, SQ_C8, SQ_D8, SQ_E8, SQ_F8, SQ_G8, SQ_H8,
  SQ_NONE,
  SQUARE_NB = 64
};

enum File {
  FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NB
};

enum Rank {
  RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NB
};

inline Square& operator++(Square& d) { return d = Square(int(d) + 1); }
inline File& operator++(File& i) { return i = File(int(i) + 1); }
inline Rank& operator++(Rank& i) { return i = Rank(int(i) + 1); }
inline Color& operator++(Color& i) { return i = Color(int(i) + 1); }

inline Square& operator--(Square& d) { return d = Square(int(d) - 1); }
inline File& operator--(File& i) { return i = File(int(i) - 1); }
inline Rank& operator--(Rank& i) { return i = Rank(int(i) - 1); }
inline Color& operator--(Color& i) { return i = Color(int(i) - 1); }

inline Rank getRank(const Square s) { return Rank(s >> 3);}
inline File getFile(const Square s) { return File(s & 7);}

inline bool isOnBoard(const File f, const Rank r) { return f<FILE_NB && r<RANK_NB && f>=FILE_A && r>=RANK_1;}

#endif /* TYPES_HPP_ */
