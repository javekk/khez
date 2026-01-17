#pragma once

#include <optional>

#include "../bitboard/bitboard.h"
#include "../lib/color.h"
#include "../lib/square.h"

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

    ALL_PIECES,
    BOARDS_COUNTER,  // Must be last - used only for size
};

enum Castle {
    WHITE_KINGSIDE = 0b0001,
    WHITE_QUEENSIDE = 0b0010,
    BLACK_KINGSIDE = 0b0100,
    BLACK_QUEENSIDE = 0b1000,
};

struct ChessboardStatus {
    Bitboard boards[BOARDS_COUNTER];

    std::optional<Color> side;
    std::optional<Square> enpassant;
    int8_t availableCastle;

    int halfmoveCounter;
    int fullmoveNumber;
};
