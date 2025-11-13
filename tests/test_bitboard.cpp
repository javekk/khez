#include <cassert>
#include <iostream>

#include "../src/bitboard/bitboard.h"

void test_basic_operations() {
    std::cout << "\t\tTesting basic operations...\n";

    Bitboard bb;
    assert(bb.isEmpty());
    assert(bb.popCount() == 0);

    bb.setBit(0);
    assert(!bb.isEmpty());
    assert(bb.getBit(0));
    assert(bb.popCount() == 1);

    bb.clearBit(0);
    assert(bb.isEmpty());
    assert(!bb.getBit(0));

    std::cout << "\t\tBasic operations tests passed!\n";
}

void test_bitwise_operations() {
    std::cout << "\t\tTesting bitwise operations...\n";

    Bitboard bb1(0xFF);
    Bitboard bb2(0xF0);

    Bitboard and_result = bb1 & bb2;
    assert(and_result.getValue() == 0xF0);

    Bitboard or_result = bb1 | bb2;
    assert(or_result.getValue() == 0xFF);

    Bitboard xor_result = bb1 ^ bb2;
    assert(xor_result.getValue() == 0x0F);

    std::cout << "\t\tBitwise operations tests passed!\n";
}

void test_popcount() {
    std::cout << "\t\tTesting popcount...\n";

    Bitboard bb(0xFF);
    assert(bb.popCount() == 8);

    bb.setBit(8);
    assert(bb.popCount() == 9);

    bb.clear();
    assert(bb.popCount() == 0);

    std::cout << "\t\tPopcount tests passed!\n";
}

void test_equality() {
    std::cout << "\t\tTesting equality...\n";

    Bitboard bb1(0xFF);
    Bitboard bb2(0xFF);
    Bitboard bb3(0xF0);

    assert(bb1 == bb2);
    assert(bb1 != bb3);

    std::cout << "\t\tEquality tests passed!\n";
}

int run_bitboard_tests() {
    std::cout << "\tTesting bitboard...\n";
    test_basic_operations();
    test_bitwise_operations();
    test_popcount();
    test_equality();

    std::cout << "\tAll bitboard tests passed!\n";
    return 0;
}