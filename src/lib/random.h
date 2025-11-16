#pragma once

#include <cstdint>

class PseudoRandomNumberGenerator {
   private:
    unsigned int state_;

   public:
    PseudoRandomNumberGenerator();
    PseudoRandomNumberGenerator(int state);
    unsigned int generateRandomU32Number();
    uint64_t generateRandomU64Number();
    uint64_t generateMagicNumberCandidate();
};
