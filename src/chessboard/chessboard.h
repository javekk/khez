#pragma once

#include <string>

#include "../bitboard/bitboard.h"

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

   private:
    Bitboard boards_[15];

    char pieceNames_[12] = {'P', 'p', 'R', 'r', 'N', 'n',
                            'B', 'b', 'Q', 'q', 'K', 'k'};

    void updateAllBoards();
};