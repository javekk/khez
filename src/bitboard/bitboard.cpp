#include "bitboard.h"

#include <iomanip>
#include <sstream>

Bitboard::Bitboard() : board_(0ULL) {}

Bitboard::Bitboard(uint64_t board) : board_(board) {}

Bitboard Bitboard::fromSquare(int square) {
    Bitboard bitboard;
    bitboard.setBit(square);
    return bitboard;
}

void Bitboard::setBit(int square) {
    if (square >= 0 && square < 64) {
        board_ |= (1ULL << (63 - square));
    }
}

void Bitboard::clearBit(int square) {
    if (square >= 0 && square < 64) {
        board_ &= ~(1ULL << (63 - square));
    }
}

bool Bitboard::getBit(int square) const {
    if (square >= 0 && square < 64) {
        return (board_ & (1ULL << (63 - square))) != 0;
    }
    return false;
}

void Bitboard::clear() { board_ = 0ULL; }

bool Bitboard::isEmpty() const { return board_ == 0ULL; }

int Bitboard::popCount() const { return __builtin_popcountll(board_); }

int Bitboard::leastSignificantBeatIndex() const {
    if (board_ == 0) {
        return -1;
    }
    return __builtin_clzll(board_);
}

uint64_t Bitboard::getValue() const { return board_; }

std::string Bitboard::toString() const {
    std::ostringstream oss;
    oss << "  a b c d e f g h\n";

    for (int rank = 7; rank >= 0; --rank) {
        oss << (rank + 1) << " ";
        for (int file = 0; file < 8; ++file) {
            int square = rank * 8 + file;
            oss << (getBit(square) ? "1" : ".") << " ";
        }
        oss << "\n";
    }

    oss << "Decimal: " << board_ << "\n";

    return oss.str();
}

Bitboard Bitboard::operator&(const Bitboard& other) const {
    return Bitboard(board_ & other.board_);
}

Bitboard Bitboard::operator|(const Bitboard& other) const {
    return Bitboard(board_ | other.board_);
}

Bitboard Bitboard::operator^(const Bitboard& other) const {
    return Bitboard(board_ ^ other.board_);
}

Bitboard Bitboard::operator~() const { return Bitboard(~board_); }

Bitboard Bitboard::operator>>(const int shift) const {
    return Bitboard(board_ >> shift);
}

Bitboard Bitboard::operator<<(const int shift) const {
    return Bitboard(board_ << shift);
}

Bitboard& Bitboard::operator|=(const Bitboard& other) {
    board_ |= other.board_;
    return *this;
}

Bitboard& Bitboard::operator&=(const Bitboard& other) {
    board_ &= other.board_;
    return *this;
}

bool Bitboard::operator==(const Bitboard& other) const {
    return board_ == other.board_;
}

bool Bitboard::operator!=(const Bitboard& other) const {
    return board_ != other.board_;
}