#include <iostream>

#include "../src/lib/logger/logger.h"
#include "test_lib.h"

// Forward declarations of test functions
void run_bitboard_tests();
void run_chessboard_tests();
void run_engine_tests();
void run_move_tests();

int main() {
    logger.configure(LoggerProps{enabled : false});

    describe("♟️  Khez Chess Engine - Test Suite ♟️", []() {
        run_bitboard_tests();
        run_chessboard_tests();
        run_move_tests();
        run_engine_tests();
    });
    return 0;
}