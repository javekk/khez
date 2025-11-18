#pragma once

#include <array>
#include <cstdint>

#include "../bitboard/bitboard.h"
#include "../engine/engine.h"
#include "random.h"
#include "sliding-piece.h"

class MagicNumberGenerator {
   private:
    PseudoRandomNumberGenerator prng_;
    Engine engine_;

   public:
    MagicNumberGenerator();
    MagicNumberGenerator(PseudoRandomNumberGenerator prng);
    uint64_t findMagicNumber(int square, int relevantBits, SlidingPiece piece);
    uint64_t* findBishopMagicNumbers();
    uint64_t* findRookMagicNumbers();
};
