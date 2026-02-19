#pragma once

#include <array>
#include <cstdint>

#include "../bitboard/bitboard.h"
#include "../engine/chessboard/chessboard-status.h"
#include "../engine/engine.h"
#include "random.h"

class MagicNumberGenerator {
   private:
    PseudoRandomNumberGenerator prng_;
    Engine engine_;

   public:
    MagicNumberGenerator();
    MagicNumberGenerator(PseudoRandomNumberGenerator prng);
    uint64_t findMagicNumber(Square square, int relevantBits,
                             SlidingPiece piece);
    uint64_t* findBishopMagicNumbers();
    uint64_t* findRookMagicNumbers();
};
