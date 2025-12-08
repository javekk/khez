#pragma once

#include <string>

#include "../bitboard/bitboard.h"
#include "../lib/sliding-piece.h"

class Engine {
   public:
    void init();

    Bitboard generateSinglePawnMaskAttacks(int square, int color);
    Bitboard generateSingleKnightMaskMoves(int square);
    Bitboard generateSingleKingMaskMoves(int square);

    Bitboard generateSingleBishopRelevantOccupanciesMask(int square);
    Bitboard generateSingleBishopAttacks(int square, Bitboard blocks);
    Bitboard getSingleBishopAttacks(int square, Bitboard occupancies);

    Bitboard generateSingleRookRelevantOccupanciesMask(int square);
    Bitboard generateSingleRookAttacks(int square, Bitboard blocks);
    Bitboard getSingleRookAttacks(int square, Bitboard occupancies);

    Bitboard getSingleQueenAttacks(int square, Bitboard occupancies);

    Bitboard setOccupancy(int index, Bitboard attacksMask);
    void generateSliderPiecesAttacks(SlidingPiece piece);

   private:
    Bitboard pawnMoveMasks[2][64];
    Bitboard knightMoveMasks[64];
    Bitboard kingMoveMasks[64];

    Bitboard bishopRelevantOccupanciesMasks[64];
    Bitboard rookRelevantOccupanciesMasks[64];

    Bitboard bishopAttacksTable[64][512];
    Bitboard rookAttacksTable[64][4096];

    void generatePawnMaskAttacks();
    void generateKnightMaskMoves();
    void generateKingMaskMoves();
};