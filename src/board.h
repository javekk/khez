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
    bool movePiece(int from, int to);

    static int notationToSquare(const std::string& notation);

   private:
    Bitboard pieces_[2][6];  // [color][piece_type]

    bool isSquareEmpty(int square) const;
    bool isValidMove(int from, int to) const;
    bool isValidPawnMove(int from, int to, bool isWhite) const;
};