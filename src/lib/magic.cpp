#include "magic.h"

#include <cstring>
#include <iostream>

#include "masks.h"
#include "square.h"

MagicNumberGenerator::MagicNumberGenerator() {
    prng_ = PseudoRandomNumberGenerator();
    engine_ = Engine();
}

MagicNumberGenerator::MagicNumberGenerator(PseudoRandomNumberGenerator prng) {
    prng_ = prng;
    engine_ = Engine();
}

uint64_t MagicNumberGenerator::findMagicNumber(Square square, int relevantBits,
                                               SlidingPiece piece) {
    Bitboard occupancies[4096];
    Bitboard attacks[4096];
    Bitboard usedAttacks[4096];

    Bitboard attackMasks =
        piece == IS_BISHOP
            ? engine_.generateSingleBishopRelevantOccupanciesMask(square)
            : engine_.generateSingleRookRelevantOccupanciesMask(square);

    int occupancyIndecies = 1 << relevantBits;

    for (int index = 0; index < occupancyIndecies; index++) {
        occupancies[index] = engine_.setOccupancy(index, attackMasks);

        attacks[index] =
            piece == IS_BISHOP
                ? engine_.generateSingleBishopAttacks(square,
                                                      occupancies[index])
                : engine_.generateSingleRookAttacks(square, occupancies[index]);
    }

    for (int randomCount = 0; randomCount < 100000000; randomCount++) {
        u_int64_t magicNumberCandidate = prng_.generateMagicNumberCandidate();

        // skip inapporpriate candidates
        if (__builtin_popcountll(
                (attackMasks.getValue() * magicNumberCandidate) &
                0xFF00000000000000ULL) < 6) {
            continue;
        }

        for (int i = 0; i < 4096; i++) {
            usedAttacks[i] = Bitboard();
        }

        int index, fail;

        for (index = 0, fail = 0; !fail && index < occupancyIndecies; index++) {
            int magicIndex =
                (int)((occupancies[index].getValue() * magicNumberCandidate) >>
                      (64 - relevantBits));

            if (usedAttacks[magicIndex].getValue() == 0ULL) {
                usedAttacks[magicIndex] = attacks[index];
            } else if (usedAttacks[magicIndex].getValue() !=
                       attacks[index].getValue()) {
                fail = 1;
                break;
            }
        }

        if (!fail) {
            return magicNumberCandidate;
        }
    }

    return 0;
}

uint64_t* MagicNumberGenerator::findBishopMagicNumbers() {
    uint64_t* magicNumbers = new u_int64_t[64];
    for (int square = 0; square < 64; square++) {
        magicNumbers[square] =
            findMagicNumber(static_cast<Square>(square),
                            bishopRelevantOccupanciesCounts[square], IS_BISHOP);
    }
    return magicNumbers;
}

uint64_t* MagicNumberGenerator::findRookMagicNumbers() {
    uint64_t* magicNumbers = new u_int64_t[64];
    for (int square = 0; square < 64; square++) {
        magicNumbers[square] =
            findMagicNumber(static_cast<Square>(square),
                            rookRelevantOccupanciesCounts[square], IS_ROOK);
    }
    return magicNumbers;
}
