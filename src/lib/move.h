#include "piece.h"
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

class Move {
   public:
    Square from;
    Square to;

    MoveType type;

    Piece piece;
    Piece promoted;
    bool isCapture;
    bool isDoublePush;
    bool isEnpassant;
    bool isCastling;

    Move(Square from, Square to, MoveType type);
    Move(u_int32_t binary);

    std::string toString() const;

    bool operator==(const Move& other) const;
    u_int32_t toBinary() const;

    static u_int32_t createBinary(Square from, Square to, MoveType type);
};