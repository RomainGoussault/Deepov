# Deepov

C++ Chess Engine, UCI compliant

[![Build Status](https://travis-ci.org/RomainGoussault/Deepov.svg?branch=master)](https://travis-ci.org/RomainGoussault/Deepov)

## Board representation
* Bitboards
* Magic bitboards

## Search
* Iterative Deepening
* Transposition Table
* Move ordering
 * MVV/LVA
 * SEE
 * Killer moves
* Selectivity
 * Null Move Pruning
 * Check extensions
 * LMR
 * Quiescence Search

## Evaluation
* Material
* Piece Square table
* Mobility
* Pawn structure

## Useful links:
* To start with bitboards: http://pages.cs.wisc.edu/~psilord/blog/data/chess-pages/
* The most complete ressource on chess programming : http://chessprogramming.wikispaces.com
* Magic bitboards explained: http://www.rivalchess.com/magic-bitboards/
* UCI protocol documentation: http://wbec-ridderkerk.nl/html/UCIProtocol.html
* FEN editor: http://en.lichess.org/editor
* Game analysis from PGN: http://en.lichess.org/paste
* Bit Twiddling Hacks: https://graphics.stanford.edu/~seander/bithacks.html
* BitBoard Calculator: http://cinnamonchess.altervista.org/bitboard_calculator/Calc.html
* Write Chess Programming in 99 steps: http://aghaznawi.comuf.com/computer%20chess/winglet/

## Other Open Source C++ Engines:
* StockFish: https://github.com/mcostalba/Stockfish/
* Faile: http://faile.sourceforge.net/
* Senpai: https://chessprogramming.wikispaces.com/Senpai
* Maverick: http://www.chessprogramming.net/downloads/
