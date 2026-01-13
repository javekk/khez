#pragma once

#include <string>
#include <vector>

#include "../bitboard/bitboard.h"
#include "../chessboard/chessboard-status.h"
#include "../lib/color.h"
#include "../lib/move.h"
#include "../lib/sliding-piece.h"
#include "../lib/square.h"

class Engine {
   public:
    void init();

    Bitboard generateSinglePawnMaskAttacks(Square square, Color color);
    Bitboard getSinglePawnAttacks(Square square, Color color);

    Bitboard generateSingleKnightAttacksMask(Square square);
    Bitboard getSingleKnightAttacks(Square square);

    Bitboard generateSingleKingAttacksMask(Square square);
    Bitboard getSingleKingAttacks(Square square);

    Bitboard generateSingleBishopRelevantOccupanciesMask(Square square);
    Bitboard generateSingleBishopAttacks(Square square, Bitboard blocks);
    Bitboard getSingleBishopAttacks(Square square, Bitboard occupancies);

    Bitboard generateSingleRookRelevantOccupanciesMask(Square square);
    Bitboard generateSingleRookAttacks(Square square, Bitboard blocks);
    Bitboard getSingleRookAttacks(Square square, Bitboard occupancies);

    Bitboard getSingleQueenAttacks(Square square, Bitboard occupancies);

    Bitboard setOccupancy(int index, Bitboard attacksMask);
    void generateSliderPiecesAttacks(SlidingPiece piece);

    bool isSquareUnderAttackBy(const ChessboardStatus* const status,
                               Square square, Color color);
    void __printAttackedSquare(const ChessboardStatus* const status,
                               Color color);

    std::vector<Move> generateMoves(const ChessboardStatus* const status);

    void __printMoves(std::vector<Move> moves);

   private:
    Bitboard pawnAttacksMasks[2][64];

    Bitboard knightAttacksMasks[64];

    Bitboard kingAttacksMasks[64];

    Bitboard bishopRelevantOccupanciesMasks[64];
    Bitboard rookRelevantOccupanciesMasks[64];

    Bitboard bishopAttacksTable[64][512];
    Bitboard rookAttacksTable[64][4096];

    void generatePawnMaskAttacks();
    void generateKnightMaskMoves();
    void generateKingMaskMoves();
};