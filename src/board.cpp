#include "board.h"

#include <sstream>

Board::Board() {
    for (int color = 0; color < 2; ++color) {
        for (int piece = 0; piece < 6; ++piece) {
            pieces_[color][piece].clear();
        }
    }
}

void Board::setupInitialPosition() {
    // White pawns on rank 2 (squares 8-15)
    for (int i = 8; i < 16; ++i) {
        pieces_[Color::WHITE][PieceType::PAWN].setBit(i);
    }

    // Black pawns on rank 7 (squares 48-55)
    for (int i = 48; i < 56; ++i) {
        pieces_[Color::BLACK][PieceType::PAWN].setBit(i);
    }

    // White pieces on rank 1
    pieces_[Color::WHITE][PieceType::ROOK].setBit(0);    // a1
    pieces_[Color::WHITE][PieceType::ROOK].setBit(7);    // h1
    pieces_[Color::WHITE][PieceType::KNIGHT].setBit(1);  // b1
    pieces_[Color::WHITE][PieceType::KNIGHT].setBit(6);  // g1
    pieces_[Color::WHITE][PieceType::BISHOP].setBit(2);  // c1
    pieces_[Color::WHITE][PieceType::BISHOP].setBit(5);  // f1
    pieces_[Color::WHITE][PieceType::QUEEN].setBit(3);   // d1
    pieces_[Color::WHITE][PieceType::KING].setBit(4);    // e1

    // Black pieces on rank 8
    pieces_[Color::BLACK][PieceType::ROOK].setBit(56);    // a8
    pieces_[Color::BLACK][PieceType::ROOK].setBit(63);    // h8
    pieces_[Color::BLACK][PieceType::KNIGHT].setBit(57);  // b8
    pieces_[Color::BLACK][PieceType::KNIGHT].setBit(62);  // g8
    pieces_[Color::BLACK][PieceType::BISHOP].setBit(58);  // c8
    pieces_[Color::BLACK][PieceType::BISHOP].setBit(61);  // f8
    pieces_[Color::BLACK][PieceType::QUEEN].setBit(59);   // d8
    pieces_[Color::BLACK][PieceType::KING].setBit(60);    // e8
}

char Board::getPieceAt(int square) const {
    for (int color = 0; color < 2; ++color) {
        for (int piece = 0; piece < 6; ++piece) {
            if (pieces_[color][piece].getBit(square)) {
                char symbols[] = {'P', 'R', 'N', 'B', 'Q', 'K'};
                return (color == Color::WHITE) ? symbols[piece]
                                               : (symbols[piece] + 32);
            }
        }
    }
    return '.';
}

std::string Board::toString() const {
    std::ostringstream oss;
    oss << "  a b c d e f g h\n";

    for (int rank = 7; rank >= 0; --rank) {
        oss << (rank + 1) << " ";
        for (int file = 0; file < 8; ++file) {
            int square = rank * 8 + file;
            oss << getPieceAt(square) << " ";
        }
        oss << "\n";
    }

    return oss.str();
}

int Board::notationToSquare(const std::string& notation) {
    if (notation.length() != 2) {
        return -1;
    }

    char file = notation[0];
    char rank = notation[1];

    if (file < 'a' || file > 'h' || rank < '1' || rank > '8') {
        return -1;
    }

    int file_index = file - 'a';
    int rank_index = rank - '1';

    return rank_index * 8 + file_index;
}

bool Board::movePiece(int from, int to) {
    // Basic validation
    if (from < 0 || from >= 64 || to < 0 || to >= 64) {
        return false;
    }

    // Check if there's a piece at the from square
    if (isSquareEmpty(from)) {
        return false;
    }

    // Get piece info at from square
    if (!isValidMove(from, to)) {
        return false;
    }

    for (int color = 0; color < 2; ++color) {
        for (int piece_idx = 0; piece_idx < 6; ++piece_idx) {
            if (pieces_[color][piece_idx].getBit(from)) {
                pieces_[color][piece_idx].clearBit(from);
                pieces_[color][piece_idx].setBit(to);
                return true;
            }
        }
    }

    return false;
}

bool Board::isSquareEmpty(int square) const {
    if (square < 0 || square >= 64) {
        return false;
    }

    // Combine all piece bitboards to get occupied squares
    Bitboard occupied;
    for (int color = 0; color < 2; ++color) {
        for (int piece = 0; piece < 6; ++piece) {
            occupied = occupied | pieces_[color][piece];
        }
    }
    return !occupied.getBit(square);
}

bool Board::isValidMove(int from, int to) const {
    char piece = getPieceAt(from);
    bool isWhite = (piece >= 'A' && piece <= 'Z');
    char pieceType = isWhite ? piece : (piece - 32);

    // Only pawns for now
    if (pieceType != 'P') return false;

    return isValidPawnMove(from, to, isWhite);
}

bool Board::isValidPawnMove(int from, int to, bool isWhite) const {
    int rankDiff = (to / 8) - (from / 8);
    int fileDiff = (to % 8) - (from % 8);

    // Pawn one square forward: same file, correct direction, target empty
    return fileDiff == 0 &&
           rankDiff == (isWhite ? 1 : -1) &&
           isSquareEmpty(to);
}