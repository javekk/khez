#pragma once

#include <string>

#include "../bitboard/bitboard.h"

class Engine {
   public:
    Bitboard generateSinglePawnMaskAttacks(int square, int color);
    Bitboard generateSingleKnightMaskMoves(int square);
    Bitboard generateSingleKingMaskMoves(int square);
    Bitboard generateSingleBishopRelevantOccupanciesMask(int square);
    Bitboard generateSingleBishopAttacks(int square, Bitboard blocks);
    Bitboard generateSingleRookRelevantOccupanciesMask(int square);
    Bitboard generateSingleRookAttacks(int square, Bitboard blocks);

   private:
    Bitboard pawnMoveMasks[2][64];
    Bitboard knightMoveMasks[64];
    Bitboard kingMoveMasks[64];
    Bitboard bishopRelevantOccupanciesMasks[64];
    Bitboard rookRelevantOccupanciesMasks[64];

    void generatePawnMaskAttacks();
    void generateKnightMaskMoves();
    void generateKingMaskMoves();

    void generateBishopRelevantOccupancies();
    void generateRookRelevantOccupancies();
};