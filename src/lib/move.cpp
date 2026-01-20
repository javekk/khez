#include "move.h"

#include <bitset>
#include <iomanip>

const std::map<std::tuple<Piece, Piece, bool, bool, bool, bool>, MoveType>
    moveTypeMap = {

        {{KING, EMPTY, false, false, false, true},
         CASTLE_KINGSIDE},  // only king because key would be the same

        {{PAWN, EMPTY, false, false, false, false}, PAWN_PUSH},
        {{PAWN, EMPTY, false, true, false, false}, PAWN_DOUBLE_PUSH},
        {{PAWN, EMPTY, true, false, false, false}, PAWN_CAPTURE},
        {{PAWN, EMPTY, true, false, true, false}, PAWN_CAPTURE_ENPASSANT},

        {{PAWN, QUEEN, false, false, false, false}, PAWN_PROMOTION_TO_QUEEN},
        {{PAWN, KNIGHT, false, false, false, false}, PAWN_PROMOTION_TO_KNIGHT},
        {{PAWN, ROOK, false, false, false, false}, PAWN_PROMOTION_TO_ROOK},
        {{PAWN, BISHOP, false, false, false, false}, PAWN_PROMOTION_TO_BISHOP},

        {{PAWN, QUEEN, true, false, false, false},
         PAWN_CAPTURE_PROMOTION_TO_QUEEN},
        {{PAWN, KNIGHT, true, false, false, false},
         PAWN_CAPTURE_PROMOTION_TO_KNIGHT},
        {{PAWN, ROOK, true, false, false, false},
         PAWN_CAPTURE_PROMOTION_TO_ROOK},
        {{PAWN, BISHOP, true, false, false, false},
         PAWN_CAPTURE_PROMOTION_TO_BISHOP},

        {{KNIGHT, EMPTY, false, false, false, false}, KNIGHT_QUIET},
        {{KNIGHT, EMPTY, true, false, false, false}, KNIGHT_CAPTURE},

        {{BISHOP, EMPTY, false, false, false, false}, BISHOP_QUIET},
        {{BISHOP, EMPTY, true, false, false, false}, BISHOP_CAPTURE},

        {{ROOK, EMPTY, false, false, false, false}, ROOK_QUIET},
        {{ROOK, EMPTY, true, false, false, false}, ROOK_CAPTURE},

        {{QUEEN, EMPTY, false, false, false, false}, QUEEN_QUIET},
        {{QUEEN, EMPTY, true, false, false, false}, QUEEN_CAPTURE},

        {{KING, EMPTY, false, false, false, false}, KING_QUIET},
        {{KING, EMPTY, true, false, false, false}, KING_CAPTURE},
};

std::map<MoveType, std::string> moveDescriptionMap = {
    {PAWN_PUSH, "PAWN_PUSH"},
    {PAWN_DOUBLE_PUSH, "PAWN_DOUBLE_PUSH"},
    {PAWN_PROMOTION_TO_BISHOP, "PAWN_PROMOTION_TO_BISHOP"},
    {PAWN_PROMOTION_TO_ROOK, "PAWN_PROMOTION_TO_ROOK"},
    {PAWN_PROMOTION_TO_KNIGHT, "PAWN_PROMOTION_TO_KNIGHT"},
    {PAWN_PROMOTION_TO_QUEEN, "PAWN_PROMOTION_TO_QUEEN"},
    {PAWN_CAPTURE, "PAWN_CAPTURE"},
    {PAWN_CAPTURE_ENPASSANT, "PAWN_CAPTURE_ENPASSANT"},
    {PAWN_CAPTURE_PROMOTION_TO_BISHOP, "PAWN_CAPTURE_PROMOTION_TO_BISHOP"},
    {PAWN_CAPTURE_PROMOTION_TO_ROOK, "PAWN_CAPTURE_PROMOTION_TO_ROOK"},
    {PAWN_CAPTURE_PROMOTION_TO_KNIGHT, "PAWN_CAPTURE_PROMOTION_TO_KNIGHT"},
    {PAWN_CAPTURE_PROMOTION_TO_QUEEN, "PAWN_CAPTURE_PROMOTION_TO_QUEEN"},
    {CASTLE_KINGSIDE, "CASTLE_KINGSIDE"},
    {CASTLE_QUEENSIDE, "CASTLE_QUEENSIDE"},
    {KNIGHT_QUIET, "KNIGHT_QUIET"},
    {KNIGHT_CAPTURE, "KNIGHT_CAPTURE"},
    {BISHOP_QUIET, "BISHOP_QUIET"},
    {BISHOP_CAPTURE, "BISHOP_CAPTURE"},
    {ROOK_QUIET, "ROOK_QUIET"},
    {ROOK_CAPTURE, "ROOK_CAPTURE"},
    {QUEEN_QUIET, "QUEEN_QUIET"},
    {QUEEN_CAPTURE, "QUEEN_CAPTURE"},
    {KING_QUIET, "KING_QUIET"},
    {KING_CAPTURE, "KING_CAPTURE"},
};

Move::Move(Square from, Square to, MoveType type)
    : from(from),
      to(to),
      type(type),
      promoted(EMPTY),
      isCapture(false),
      isDoublePush(false),
      isEnpassant(false),
      isCastling(false) {
    // Piece
    switch (type) {
        case PAWN_PUSH:
        case PAWN_CAPTURE:
        case PAWN_DOUBLE_PUSH:
        case PAWN_CAPTURE_ENPASSANT:
        case PAWN_PROMOTION_TO_QUEEN:
        case PAWN_PROMOTION_TO_KNIGHT:
        case PAWN_PROMOTION_TO_ROOK:
        case PAWN_PROMOTION_TO_BISHOP:
        case PAWN_CAPTURE_PROMOTION_TO_QUEEN:
        case PAWN_CAPTURE_PROMOTION_TO_KNIGHT:
        case PAWN_CAPTURE_PROMOTION_TO_ROOK:
        case PAWN_CAPTURE_PROMOTION_TO_BISHOP:
            piece = PAWN;
            break;
        case KING_QUIET:
        case KING_CAPTURE:
        case CASTLE_KINGSIDE:
        case CASTLE_QUEENSIDE:
            piece = KING;
            break;
        case KNIGHT_QUIET:
        case KNIGHT_CAPTURE:
            piece = KNIGHT;
            break;
        case BISHOP_QUIET:
        case BISHOP_CAPTURE:
            piece = BISHOP;
            break;
        case ROOK_QUIET:
        case ROOK_CAPTURE:
            piece = ROOK;
            break;
        case QUEEN_QUIET:
        case QUEEN_CAPTURE:
            piece = QUEEN;
            break;
    }

    // Promoted piece
    switch (type) {
        case PAWN_PROMOTION_TO_QUEEN:
        case PAWN_CAPTURE_PROMOTION_TO_QUEEN:
            promoted = QUEEN;
            break;
        case PAWN_PROMOTION_TO_KNIGHT:
        case PAWN_CAPTURE_PROMOTION_TO_KNIGHT:
            promoted = KNIGHT;
            break;
        case PAWN_PROMOTION_TO_ROOK:
        case PAWN_CAPTURE_PROMOTION_TO_ROOK:
            promoted = ROOK;
            break;
        case PAWN_PROMOTION_TO_BISHOP:
        case PAWN_CAPTURE_PROMOTION_TO_BISHOP:
            promoted = BISHOP;
            break;
        default:
            break;
    }

    // Flags
    switch (type) {
        case PAWN_DOUBLE_PUSH:
            isDoublePush = true;
            break;
        case PAWN_CAPTURE:
        case KNIGHT_CAPTURE:
        case BISHOP_CAPTURE:
        case ROOK_CAPTURE:
        case QUEEN_CAPTURE:
        case KING_CAPTURE:
        case PAWN_CAPTURE_PROMOTION_TO_QUEEN:
        case PAWN_CAPTURE_PROMOTION_TO_ROOK:
        case PAWN_CAPTURE_PROMOTION_TO_BISHOP:
        case PAWN_CAPTURE_PROMOTION_TO_KNIGHT:
            isCapture = true;
            break;
        case PAWN_CAPTURE_ENPASSANT:
            isCapture = true;
            isEnpassant = true;
            break;
        case CASTLE_KINGSIDE:
        case CASTLE_QUEENSIDE:
            isCastling = true;
            break;
        default:
            break;
    }
}

Move::Move(u_int32_t binary) {
    from = static_cast<Square>(binary & 0x3f);            // bit 0-5
    to = static_cast<Square>((binary >> 6) & 0x3f);       // bit 6-11
    piece = static_cast<Piece>((binary >> 12) & 0xf);     // bit 12-15
    promoted = static_cast<Piece>((binary >> 16) & 0xf);  // bit 16-19
    isCapture = (binary >> 20) & 1;                       // bit 20
    isDoublePush = (binary >> 21) & 1;                    // bit 21
    isEnpassant = (binary >> 22) & 1;                     // bit 22
    isCastling = (binary >> 23) & 1;                      // bit 23

    auto key = std::make_tuple(piece, promoted, isCapture, isDoublePush,
                               isEnpassant, isCastling);

    auto _moveType = moveTypeMap.find(key);
    type = (_moveType != moveTypeMap.end()) ? _moveType->second : PAWN_PUSH;

    if (isCastling && (to == c8 || to == c1)) {
        type = CASTLE_QUEENSIDE;
    }
}

std::string Move::toString() const {
    std::ostringstream oss;

    std::string moveStr = " [" + squareMap.at(from) + " -> " +
                          squareMap.at(to) + ", " +
                          moveDescriptionMap.at(type) + "]";

    int padding = 56 - moveStr.length();

    std::bitset<24> binaryMove(getBinaryMove());
    std::string binary = binaryMove.to_string();
    std::string formatted;
    for (size_t i = 0; i < binary.length(); ++i) {
        if (i > 0 && i % 4 == 0) formatted += " ";
        formatted += binary[i];
    }

    oss << moveStr << std::setw(padding) << " #Binary (" << formatted << ")";

    return oss.str();
}

bool Move::operator==(const Move& other) const {
    return from == other.from && to == other.to && type == other.type;
}

u_int32_t Move::getBinaryMove() const {
    /*
        0000 0000 0000 0000 0011 1111    source square       0x3f
        0000 0000 0000 1111 1100 0000    target square       0xfc0
        0000 0000 1111 0000 0000 0000    piece               0xf000
        0000 1111 0000 0000 0000 0000    promoted piece      0xf0000
        0001 0000 0000 0000 0000 0000    capture flag        0x100000
        0010 0000 0000 0000 0000 0000    double push flag    0x200000
        0100 0000 0000 0000 0000 0000    enpassant flag      0x400000
        1000 0000 0000 0000 0000 0000    castling flag       0x800000
    */

    u_int32_t ret = (from) | (to << 6) | ((piece != EMPTY ? piece : 0) << 12) |
                    ((promoted != EMPTY ? promoted : EMPTY) << 16) |
                    (isCapture << 20) | (isDoublePush << 21) |
                    (isEnpassant << 22) | (isCastling << 23);
    return ret;
}
