#include "move.h"

#include <bitset>
#include <iomanip>

#include "../masks/masks.h"

static MoveType deriveMoveType(Piece piece, Piece promoted, bool isCapture,
                               bool isDoublePush, bool isEnpassant,
                               bool isCastling, Square to) {
    if (isCastling) {
        return (to == c1 || to == c8) ? CASTLE_QUEENSIDE : CASTLE_KINGSIDE;
    }

    switch (piece) {
        case PAWN:
            if (isEnpassant) return PAWN_CAPTURE_ENPASSANT;
            if (promoted != EMPTY) {
                switch (promoted) {
                    case QUEEN:
                        return isCapture ? PAWN_CAPTURE_PROMOTION_TO_QUEEN
                                         : PAWN_PROMOTION_TO_QUEEN;
                    case KNIGHT:
                        return isCapture ? PAWN_CAPTURE_PROMOTION_TO_KNIGHT
                                         : PAWN_PROMOTION_TO_KNIGHT;
                    case ROOK:
                        return isCapture ? PAWN_CAPTURE_PROMOTION_TO_ROOK
                                         : PAWN_PROMOTION_TO_ROOK;
                    case BISHOP:
                        return isCapture ? PAWN_CAPTURE_PROMOTION_TO_BISHOP
                                         : PAWN_PROMOTION_TO_BISHOP;
                    default:
                        break;
                }
            }
            if (isDoublePush) return PAWN_DOUBLE_PUSH;
            return isCapture ? PAWN_CAPTURE : PAWN_PUSH;
        case KNIGHT:
            return isCapture ? KNIGHT_CAPTURE : KNIGHT_QUIET;
        case BISHOP:
            return isCapture ? BISHOP_CAPTURE : BISHOP_QUIET;
        case ROOK:
            return isCapture ? ROOK_CAPTURE : ROOK_QUIET;
        case QUEEN:
            return isCapture ? QUEEN_CAPTURE : QUEEN_QUIET;
        case KING:
            return isCapture ? KING_CAPTURE : KING_QUIET;
        default:
            return PAWN_PUSH;
    }
}

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

Move::Move(Square from, Square to, MoveType type) {
    // Use the static createBinary function and then the binary constructor
    *this = Move(createBinary(from, to, type));
}

u_int32_t Move::createBinary(Square from, Square to, MoveType type) {
    Piece piece = EMPTY;
    Piece promoted = EMPTY;
    bool isCapture = false;
    bool isDoublePush = false;
    bool isEnpassant = false;
    bool isCastling = false;

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

    return (from) | (to << 6) | ((piece != EMPTY ? piece : 0) << 12) |
           ((promoted != EMPTY ? promoted : EMPTY) << 16) | (isCapture << 20) |
           (isDoublePush << 21) | (isEnpassant << 22) | (isCastling << 23);
}

bool Move::isPromotion() const { return promoted && promoted != EMPTY; }

Move::Move(u_int32_t binary) {
    from = static_cast<Square>(binary & 0x3f);            // bit 0-5
    to = static_cast<Square>((binary >> 6) & 0x3f);       // bit 6-11
    piece = static_cast<Piece>((binary >> 12) & 0xf);     // bit 12-15
    promoted = static_cast<Piece>((binary >> 16) & 0xf);  // bit 16-19
    isCapture = (binary >> 20) & 1;                       // bit 20
    isDoublePush = (binary >> 21) & 1;                    // bit 21
    isEnpassant = (binary >> 22) & 1;                     // bit 22
    isCastling = (binary >> 23) & 1;                      // bit 23

    type = deriveMoveType(piece, promoted, isCapture, isDoublePush, isEnpassant,
                          isCastling, to);
}

std::string Move::toString() const {
    std::ostringstream oss;

    oss << " [" + squareMap.at(from) << " -> " << squareMap.at(to) << ", "
        << moveDescriptionMap.at(type) << "]";
    return oss.str();
}

std::string Move::toStringComplete() const {
    std::ostringstream oss;

    std::string moveStr = " [" + squareMap.at(from) + " -> " +
                          squareMap.at(to) + ", " +
                          moveDescriptionMap.at(type) + "]";

    int padding = 56 - moveStr.length();

    std::bitset<24> binaryMove(toBinary());
    std::string binary = binaryMove.to_string();
    std::string formatted;
    for (size_t i = 0; i < binary.length(); ++i) {
        if (i > 0 && i % 4 == 0) formatted += " ";
        formatted += binary[i];
    }

    oss << moveStr << std::setw(padding) << " #Binary (" << formatted << ")";

    return oss.str();
}

std::string Move::toStringUCI() const {
    std::string move = squareMap.at(from) + squareMap.at(to);

    if (promoted) {
        switch (promoted) {
            case QUEEN:
                return move + "q";
            case KNIGHT:
                return move + "n";
            case BISHOP:
                return move + "b";
            case ROOK:
                return move + "r";
            default:
                break;
        }
    }
    return move;
}

bool Move::operator==(const Move& other) const {
    return from == other.from && to == other.to && type == other.type;
}

u_int32_t Move::toBinary() const {
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