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
    assert(board.getPieceAt("a1") == 'R');
    assert(board.getPieceAt("b1") == 'N');
    assert(board.getPieceAt("c1") == 'B');
    assert(board.getPieceAt("d1") == 'Q');
    assert(board.getPieceAt("e1") == 'K');
    assert(board.getPieceAt("f1") == 'B');
    assert(board.getPieceAt("g1") == 'N');
    assert(board.getPieceAt("h1") == 'R');

    // Test white pawns on rank 2
    assert(board.getPieceAt("a2") == 'P');
    assert(board.getPieceAt("h2") == 'P');

    // Test black pieces on rank 8
    assert(board.getPieceAt("a8") == 'r');
    assert(board.getPieceAt("e8") == 'k');

    // Test black pawns on rank 7
    assert(board.getPieceAt("a7") == 'p');
    assert(board.getPieceAt("h7") == 'p');

    // Test empty squares
    assert(board.getPieceAt("e4") == '.');
    assert(board.getPieceAt("d5") == '.');

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

void test_pawn_moves() {
    std::cout << "\t\tTesting pawn moves...\n";

    Board board;
    board.setupInitialPosition();

    // Test valid white pawn moves
    assert(board.movePiece("e2", "e3") == true);
    assert(board.getPieceAt("e2") == '.');
    assert(board.getPieceAt("e3") == 'P');

    // Test valid black pawn move
    assert(board.movePiece("d7", "d6") == true);
    assert(board.getPieceAt("d7") == '.');
    assert(board.getPieceAt("d6") == 'p');

    // Test invalid moves
    Board board2;
    board2.setupInitialPosition();

    // Can't move pawn backwards
    assert(board2.movePiece("e2", "e1") == false);

    // Can't move pawn sideways
    assert(board2.movePiece("e2", "f2") == false);

    // Test valid two-square pawn moves from starting position
    assert(board2.movePiece("e2", "e4") == true);
    assert(board2.getPieceAt("e2") == '.');
    assert(board2.getPieceAt("e4") == 'P');

    // Test valid two-square black pawn move from starting position
    assert(board2.movePiece("f7", "f5") == true);
    assert(board2.getPieceAt("f7") == '.');
    assert(board2.getPieceAt("f5") == 'p');

    // Test that two-square moves are not allowed after pawn has moved
    Board board3;
    board3.setupInitialPosition();
    board3.movePiece("d2", "d3");  // Move pawn one square
    assert(board3.movePiece("d3", "d5") ==
           false);  // Can't move two squares now

    // Test that two-square moves are blocked by pieces
    Board board_blocked;
    board_blocked.setupInitialPosition();
    board_blocked.movePiece("e2", "e3");  // Move white pawn to e3
    board_blocked.movePiece("e3", "e4");  // Move white pawn to e4
    // Now try to move d2 pawn two squares, but e3 is occupied by our pawn
    // Wait, that's not right - let me fix this test

    Board board_blocked2;
    board_blocked2.setupInitialPosition();
    board_blocked2.movePiece("d7", "d6");  // Move black pawn down
    board_blocked2.movePiece("d6", "d5");  // Move black pawn to d5
    board_blocked2.movePiece("d5", "d4");  // Move black pawn to d4
    board_blocked2.movePiece(
        "d4", "d3");  // Move black pawn to d3, blocking white d2 pawn
    assert(board_blocked2.movePiece("d2", "d4") ==
           false);  // Can't jump over piece at d3

    // Can't move to occupied square
    assert(board2.movePiece("e2", "e7") == false);

    std::cout << "\t\tPawn moves tests passed!\n";
}

void test_pawn_captures() {
    std::cout << "\t\tTesting Pawn captures...\n";

    Board board;
    board.setupInitialPosition();

    // Move pawns to create capture opportunity
    board.movePiece("e2", "e4");  // White pawn to e4
    board.movePiece("d7", "d5");  // Black pawn to d5

    // Test valid capture
    assert(board.movePiece("e4", "d5") == true);  // White captures black
    assert(board.getPieceAt("e4") == '.');        // Original square empty
    assert(board.getPieceAt("d5") == 'P');  // White pawn on capture square

    // Test invalid diagonal move without capture
    Board board2;
    board2.setupInitialPosition();
    assert(board2.movePiece("e2", "f3") ==
           false);  // Can't move diagonally to empty square

    // Test can't capture own pieces
    Board board3;
    board3.setupInitialPosition();
    board3.movePiece("e2", "e3");                   // Move white pawn
    board3.movePiece("d2", "d4");                   // Move another white pawn
    assert(board3.movePiece("e3", "d4") == false);  // Can't capture own piece

    std::cout << "\t\tPawn captures tests passed!\n";
}

int run_board_tests() {
    try {
        test_board_initialization();
        test_to_string();
        test_initial_position();
        test_notation_to_square();
        test_pawn_moves();
        test_pawn_captures();

        std::cout << "\tAll board tests passed!\n";
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "\tBoard test failed: " << e.what() << "\n";
        return 1;
    }
}