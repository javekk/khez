#pragma once

#include <cstdint>

class RandonNumberGenerator {
   private:
    unsigned int state_;

   public:
    RandonNumberGenerator();
    RandonNumberGenerator(int state);
    unsigned int generateRandomU32Number();
    uint64_t generateRandomU64Number();
    uint64_t generateMagicNumberCandidate();
};
