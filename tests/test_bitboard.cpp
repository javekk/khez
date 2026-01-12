#include <iostream>

#include "../src/bitboard/bitboard.h"
#include "test_lib.h"

void run_bitboard_tests() {
    describe("Testing bitboard", []() {
        it("Testing basic operations", []() {
            Bitboard bb;
            expect(bb.isEmpty());
            expect(bb.popCount() == 0);

            bb.setBit(0);
            expect(!bb.isEmpty());
            expect(bb.getBit(0));
            expect(bb.popCount() == 1);

            bb.clearBit(0);
            expect(bb.isEmpty());
            expect(!bb.getBit(0));
        });

        it("Testing bitwise operations", []() {
            Bitboard bb1(0xFF);
            Bitboard bb2(0xF0);

            Bitboard and_result = bb1 & bb2;
            expect(and_result.getValue() == 0xF0);

            Bitboard or_result = bb1 | bb2;
            expect(or_result.getValue() == 0xFF);

            Bitboard xor_result = bb1 ^ bb2;
            expect(xor_result.getValue() == 0x0F);
        });

        it("Testing popcount", []() {
            Bitboard bb(0xFF);
            expect(bb.popCount() == 8);

            bb.setBit(8);
            expect(bb.popCount() == 9);

            bb.clear();
            expect(bb.popCount() == 0);
        });

        it("Testing equiality", []() {
            Bitboard bb1(0xFF);
            Bitboard bb2(0xFF);
            Bitboard bb3(0xF0);

            expect(bb1 == bb2);
            expect(bb1 != bb3);
        });
    });
}