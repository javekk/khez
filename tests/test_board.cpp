#include <cassert>
#include <iostream>

#include "../src/board.h"

void test_board_initialization() {
    std::cout << "\t\tTesting board initialization...\n";

    Board board;
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

    Board board;

    std::string board_str = board.toString();
    assert(!board_str.empty());
    assert(board_str.length() > 50);  // Should be a reasonable size

    std::cout << "\t\tPiece placement tests passed!\n";
}

void test_initial_position() {
    std::cout << "\t\tTesting initial position setup...\n";

    Board board;
    board.setupInitialPosition();

    // Test white pieces on rank 1
    assert(board.getPieceAt(Board::notationToSquare("a1")) == 'R');
    assert(board.getPieceAt(Board::notationToSquare("b1")) == 'N');
    assert(board.getPieceAt(Board::notationToSquare("c1")) == 'B');
    assert(board.getPieceAt(Board::notationToSquare("d1")) == 'Q');
    assert(board.getPieceAt(Board::notationToSquare("e1")) == 'K');
    assert(board.getPieceAt(Board::notationToSquare("f1")) == 'B');
    assert(board.getPieceAt(Board::notationToSquare("g1")) == 'N');
    assert(board.getPieceAt(Board::notationToSquare("h1")) == 'R');

    // Test white pawns on rank 2
    assert(board.getPieceAt(Board::notationToSquare("a2")) == 'P');
    assert(board.getPieceAt(Board::notationToSquare("h2")) == 'P');

    // Test black pieces on rank 8
    assert(board.getPieceAt(Board::notationToSquare("a8")) == 'r');
    assert(board.getPieceAt(Board::notationToSquare("e8")) == 'k');

    // Test black pawns on rank 7
    assert(board.getPieceAt(Board::notationToSquare("a7")) == 'p');
    assert(board.getPieceAt(Board::notationToSquare("h7")) == 'p');

    // Test empty squares
    assert(board.getPieceAt(Board::notationToSquare("e4")) == '.');
    assert(board.getPieceAt(Board::notationToSquare("d5")) == '.');

    std::cout << "\t\tInitial position tests passed!\n";
}

void test_notation_to_square() {
    std::cout << "\t\tTesting notation to square conversion...\n";

    // Test valid notations
    assert(Board::notationToSquare("a1") == 0);
    assert(Board::notationToSquare("h1") == 7);
    assert(Board::notationToSquare("a8") == 56);
    assert(Board::notationToSquare("h8") == 63);
    assert(Board::notationToSquare("e4") == 28);
    assert(Board::notationToSquare("d5") == 35);

    // Test invalid notations
    assert(Board::notationToSquare("") == -1);
    assert(Board::notationToSquare("a") == -1);
    assert(Board::notationToSquare("a9") == -1);
    assert(Board::notationToSquare("i1") == -1);
    assert(Board::notationToSquare("a0") == -1);
    assert(Board::notationToSquare("abc") == -1);

    std::cout << "\t\tNotation to square tests passed!\n";
}

int run_board_tests() {
    try {
        test_board_initialization();
        test_to_string();
        test_initial_position();
        test_notation_to_square();

        std::cout << "\tAll board tests passed!\n";
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "\tBoard test failed: " << e.what() << "\n";
        return 1;
    }
}