#include <iostream>

// Forward declarations of test functions
int run_bitboard_tests();
int run_chessboard_tests();
int run_engine_tests();

int main() {
    std::cout << "♟️ Khez Chess Engine - Test Suite ♟️\n";

    int result = 0;

    result += run_bitboard_tests();
    result += run_chessboard_tests();
    result += run_engine_tests();

    if (result == 0) {
        std::cout << "🎉 All tests passed!\n";
    } else {
        std::cout << "\n❌ " << result << " test(s) failed.\n";
    }

    return result;
}