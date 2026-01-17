#include "square.h"

enum MoveType {
    PAWN_PUSH,
    PAWN_DOUBLE_PUSH,
    PAWN_PROMOTION_TO_QUEEN,
    PAWN_PROMOTION_TO_KNIGHT,
    PAWN_PROMOTION_TO_ROOK,
    PAWN_PROMOTION_TO_BISHOP,
    PAWN_CAPTURE,
    PAWN_CAPTURE_ENPASSANT,
    PAWN_CAPTURE_PROMOTION_TO_QUEEN,
    PAWN_CAPTURE_PROMOTION_TO_KNIGHT,
    PAWN_CAPTURE_PROMOTION_TO_ROOK,
    PAWN_CAPTURE_PROMOTION_TO_BISHOP,

    CASTLE_KINGSIDE,
    CASTLE_QUEENSIDE,

    KNIGHT_QUIET,
    KNIGHT_CAPTURE,

    BISHOP_QUIET,
    BISHOP_CAPTURE,

    ROOK_QUIET,
    ROOK_CAPTURE,

    QUEEN_QUIET,
    QUEEN_CAPTURE,

    KING_QUIET,
    KING_CAPTURE,
};

struct Move {
    Square sourceSquare;
    Square targetSquare;
    MoveType type;

    bool operator==(const Move& other) const {
        return sourceSquare == other.sourceSquare &&
               targetSquare == other.targetSquare && type == other.type;
    }
};