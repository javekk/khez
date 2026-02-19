#include "random.h"

#include <cstdlib>

PseudoRandomNumberGenerator::PseudoRandomNumberGenerator() {
    state_ = std::rand();
}
PseudoRandomNumberGenerator::PseudoRandomNumberGenerator(int state) {
    state_ = state;
}

unsigned int PseudoRandomNumberGenerator::generateRandomU32Number() {
    unsigned int number = state_;

    // XOR shift algorithm
    number ^= number << 13;
    number ^= number >> 17;
    number ^= number << 5;

    state_ = number;
    return number;
}

uint64_t PseudoRandomNumberGenerator::generateRandomU64Number() {
    uint64_t n1, n2, n3, n4;

    // Slide the number 16 bits from the most significant bit side
    n1 = (uint64_t)(this->generateRandomU32Number()) & 0xFFFF;
    n2 = (uint64_t)(this->generateRandomU32Number()) & 0xFFFF;
    n3 = (uint64_t)(this->generateRandomU32Number()) & 0xFFFF;
    n4 = (uint64_t)(this->generateRandomU32Number()) & 0xFFFF;

    return n1 | (n2 << 16) | (n3 << 32) | (n4 << 48);
}

uint64_t PseudoRandomNumberGenerator::generateMagicNumberCandidate() {
    return this->generateRandomU64Number() & this->generateRandomU64Number() &
           this->generateRandomU64Number();
};
