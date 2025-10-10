#pragma once

#include <cstdint>
#include <string>

class Bitboard {
   public:
    Bitboard();
    explicit Bitboard(uint64_t board);

    void setBit(int square);
    void clearBit(int square);
    bool getBit(int square) const;

    void clear();
    bool isEmpty() const;
    int popCount() const;

    uint64_t getValue() const;
    std::string toString() const;

    Bitboard operator&(const Bitboard& other) const;
    Bitboard operator|(const Bitboard& other) const;
    Bitboard operator^(const Bitboard& other) const;
    Bitboard operator~() const;

    Bitboard operator<<(const int shift) const;
    Bitboard operator>>(const int shift) const;

    Bitboard& operator|=(const Bitboard& other);
    Bitboard& operator&=(const Bitboard& other);

    bool operator==(const Bitboard& other) const;
    bool operator!=(const Bitboard& other) const;

   private:
    uint64_t board_;
};