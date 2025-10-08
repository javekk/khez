#include <cassert>
#include <iostream>

#include "../src/chess_board.h"

void test_board_initialization() {
    std::cout << "\t\tTesting board initialization...\n";

    ChessBoard board;
    bool has_pieces = false;
    for (int i = 0; i < 64; i++) {
        char c = board.getPieceAt(0);
        if (c >= 'A' && c <= 'Z') {
            has_pieces = true;
            break;
        }
        if (c >= 'a' && c <= 'z') {
            has_pieces = true;
            break;
        }
    }

    assert(!has_pieces);

    std::cout << "\t\tBoard initialization tests passed!\n";
}

void test_to_string() {
    std::cout << "\t\tTesting toString() returning the board...\n";

    ChessBoard board;

    std::string board_str = board.toString();
    assert(!board_str.empty());
    assert(board_str.length() > 50);  // Should be a reasonable size

    std::cout << "\t\tPiece placement tests passed!\n";
}

void test_initial_position() {
    std::cout << "\t\tTesting initial position setup...\n";

    ChessBoard board;
    board.setupInitialPosition();

    // Test white pieces on rank 1
    assert(board.getPieceAt(a1) == 'R');
    assert(board.getPieceAt(b1) == 'N');
    assert(board.getPieceAt(c1) == 'B');
    assert(board.getPieceAt(d1) == 'Q');
    assert(board.getPieceAt(e1) == 'K');
    assert(board.getPieceAt(f1) == 'B');
    assert(board.getPieceAt(g1) == 'N');
    assert(board.getPieceAt(h1) == 'R');

    // Test white pawns on rank 2
    assert(board.getPieceAt(a2) == 'P');
    assert(board.getPieceAt(h2) == 'P');

    // Test black pieces on rank 8
    assert(board.getPieceAt(a8) == 'r');
    assert(board.getPieceAt(e8) == 'k');

    // Test black pawns on rank 7
    assert(board.getPieceAt(a7) == 'p');
    assert(board.getPieceAt(h7) == 'p');

    // Test empty squares
    assert(board.getPieceAt(e4) == '.');
    assert(board.getPieceAt(d5) == '.');

    std::cout << "\t\tInitial position tests passed!\n";
}

int run_chess_board_tests() {
    try {
        test_board_initialization();
        test_to_string();
        test_initial_position();

        std::cout << "\tAll board tests passed!\n";
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "\tBoard test failed: " << e.what() << "\n";
        return 1;
    }
}