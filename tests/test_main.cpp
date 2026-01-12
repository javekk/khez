#include <iostream>

#include "test_lib.h"

// Forward declarations of test functions
void run_bitboard_tests();
void run_chessboard_tests();
int run_engine_tests();

int main() {
    describe("♟️  Khez Chess Engine - Test Suite ♟️", []() {
        run_bitboard_tests();
        run_chessboard_tests();
        run_engine_tests();
    });
    return 0;
}