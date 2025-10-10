#pragma once

#include <string>

#include "bitboard.h"
#include "masks.h"

enum Square {
    a1,
    b1,
    c1,
    d1,
    e1,
    f1,
    g1,
    h1,
    a2,
    b2,
    c2,
    d2,
    e2,
    f2,
    g2,
    h2,
    a3,
    b3,
    c3,
    d3,
    e3,
    f3,
    g3,
    h3,
    a4,
    b4,
    c4,
    d4,
    e4,
    f4,
    g4,
    h4,
    a5,
    b5,
    c5,
    d5,
    e5,
    f5,
    g5,
    h5,
    a6,
    b6,
    c6,
    d6,
    e6,
    f6,
    g6,
    h6,
    a7,
    b7,
    c7,
    d7,
    e7,
    f7,
    g7,
    h7,
    a8,
    b8,
    c8,
    d8,
    e8,
    f8,
    g8,
    h8,
};

enum PieceBoard {
    WHITE_PAWNS,
    BLACK_PAWNS,
    WHITE_ROOKS,
    BLACK_ROOKS,
    WHITE_KNIGHTS,
    BLACK_KNIGHTS,
    WHITE_BISHOPS,
    BLACK_BISHOPS,
    WHITE_QUEEN,
    BLACK_QUEEN,
    WHITE_KING,
    BLACK_KING,

    WHITE_ALL,
    BLACK_ALL,

    ALL,
};

class ChessBoard {
   public:
    ChessBoard();
    void setupInitialPosition();
    std::string toString() const;
    char getPieceAt(int square) const;
    Bitboard generateSingleKnightMaskAttacks(int square);

   private:
    Bitboard boards_[15];

    char pieceNames_[12] = {'P', 'p', 'R', 'r', 'N', 'n',
                            'B', 'b', 'Q', 'q', 'K', 'k'};

    void updateAllBoards();
    void generateKnightMaskAttacks();
};