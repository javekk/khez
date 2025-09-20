#include <bitset>
#include <iostream>

#include "bitboard.h"
#include "board.h"

int main() {
    std::cout << "Khez Chess Engine - Bitboard Demo\n";
    std::cout << "==================================\n\n";

    Bitboard bb;

    Board board;
    board.setupInitialPosition();
    std::cout << board.toString() << "\n";

    return 0;
}