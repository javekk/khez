
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

    ALL,
    BOARDS_COUNTER,  // Must be last - used only for size
};

struct ChessboardStatus {
    Bitboard boards[BOARDS_COUNTER];

    std::optional<Color> side;
    std::optional<Square> enpassant;
    int8_t availableCastle;

    int halfmoveCounter;
    int fullmoveNumber;
};
