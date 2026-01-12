#include "square.h"

struct Move {
    Square sourceSquare;
    Square targetSquare;

    bool operator==(const Move& other) const {
        return sourceSquare == other.sourceSquare &&
               targetSquare == other.targetSquare;
    }
};

enum MoveType {
    PAWN_PUSH,
    PAWN_DOUBLE_PUSH,
    PAWN_PROMOTION_TO_QUEEN,
    PAWN_PROMOTION_TO_KNIGHT,
    PAWN_PROMOTION_TO_ROOK,
    PAWN_PROMOTION_TO_BISHOP,
};
