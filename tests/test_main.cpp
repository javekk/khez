#include <iostream>

// Forward declarations of test functions
int run_bitboard_tests();
int run_board_tests();

int main() {
    std::cout << "♟️ Khez Chess Engine - Test Suite ♟️\n";

    int result = 0;

    std::cout << "\tRunning Bitboard Tests...\n";
    result += run_bitboard_tests();

    std::cout << "\tRunning Board Tests...\n";
    result += run_board_tests();

    if (result == 0) {
        std::cout << "🎉 All tests passed!\n";
    } else {
        std::cout << "\n❌ " << result << " test(s) failed.\n";
    }

    return result;
}