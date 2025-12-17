#pragma once

#include <string>

#include "../bitboard/bitboard.h"
#include "../chessboard/chessboard-status.h"
#include "../lib/color.h"
#include "../lib/sliding-piece.h"
#include "../lib/square.h"

class Engine {
   public:
    void init();

    Bitboard generateSinglePawnMaskAttacks(Square square, Color color);

    Bitboard generateSingleKnightMaskMoves(Square square);

    Bitboard generateSingleKingMaskMoves(Square square);

    Bitboard generateSingleBishopRelevantOccupanciesMask(Square square);
    Bitboard generateSingleBishopAttacks(Square square, Bitboard blocks);
    Bitboard getSingleBishopAttacks(Square square, Bitboard occupancies);

    Bitboard generateSingleRookRelevantOccupanciesMask(Square square);
    Bitboard generateSingleRookAttacks(Square square, Bitboard blocks);
    Bitboard getSingleRookAttacks(Square square, Bitboard occupancies);

    Bitboard getSingleQueenAttacks(Square square, Bitboard occupancies);

    Bitboard setOccupancy(int index, Bitboard attacksMask);
    void generateSliderPiecesAttacks(SlidingPiece piece);

    bool isSquareUnderAttack(ChessboardStatus status, Square square,
                             Color color);
    void __printAttackedSquare(ChessboardStatus status, Color color);

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