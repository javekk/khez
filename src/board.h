#pragma once

#include <string>

#include "bitboard.h"

enum PieceType { PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING };

enum Color { WHITE, BLACK };

class Board {
   public:
    Board();
    void setupInitialPosition();
    std::string toString() const;
    char getPieceAt(int square) const;

    static int notationToSquare(const std::string& notation);

   private:
    Bitboard pieces_[2][6];  // [color][piece_type]
};