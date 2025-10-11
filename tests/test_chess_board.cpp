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

    std::cout << "\t\t\tTesting white pieces on rank 1...\n";
    assert(board.getPieceAt(a1) == 'R');
    assert(board.getPieceAt(b1) == 'N');
    assert(board.getPieceAt(c1) == 'B');
    assert(board.getPieceAt(d1) == 'Q');
    assert(board.getPieceAt(e1) == 'K');
    assert(board.getPieceAt(f1) == 'B');
    assert(board.getPieceAt(g1) == 'N');
    assert(board.getPieceAt(h1) == 'R');

    std::cout << "\t\t\tTesting white pieces on rank 2...\n";
    assert(board.getPieceAt(a2) == 'P');
    assert(board.getPieceAt(h2) == 'P');

    std::cout << "\t\t\tTesting black pieces on rank 8...\n";
    assert(board.getPieceAt(a8) == 'r');
    assert(board.getPieceAt(e8) == 'k');

    std::cout << "\t\t\tTesting black pieces on rank 7...\n";
    assert(board.getPieceAt(a7) == 'p');
    assert(board.getPieceAt(h7) == 'p');

    std::cout << "\t\t\tTesting empty squares...\n";
    assert(board.getPieceAt(e4) == '.');
    assert(board.getPieceAt(d5) == '.');

    std::cout << "\t\tInitial position tests passed!\n";
}

void test_pawn_attacks_generation() {
    std::cout << "\t\tTesting pawn attacks generations...\n";
    ChessBoard board;

    std::cout << "\t\t\tTesting pawn attacks on e4 for white...\n";
    Bitboard whiteE4Attacks = board.generateSinglePawnMaskAttacks(e4, WHITE);
    assert(whiteE4Attacks.getBit(d5));
    assert(whiteE4Attacks.getBit(f5));
    assert(whiteE4Attacks.popCount() == 2);

    std::cout << "\t\t\tTesting pawn attacks on e4 for black...\n";
    Bitboard blackE4Attacks = board.generateSinglePawnMaskAttacks(e4, BLACK);
    assert(blackE4Attacks.getBit(d3));
    assert(blackE4Attacks.getBit(f3));
    assert(blackE4Attacks.popCount() == 2);

    std::cout << "\t\t\tTesting pawn attacks on a4 for white...\n";
    Bitboard whiteA4Attacks = board.generateSinglePawnMaskAttacks(a4, WHITE);
    assert(whiteA4Attacks.getBit(b5));
    assert(whiteA4Attacks.popCount() == 1);

    std::cout << "\t\t\tTesting pawn attacks on h4 for black...\n";
    Bitboard blackH4Attacks = board.generateSinglePawnMaskAttacks(h4, BLACK);
    assert(blackH4Attacks.getBit(g3));
    assert(blackH4Attacks.popCount() == 1);

    std::cout << "\t\tPawn attacks generations tests passed...\n";
}

void test_knight_attacks_generation() {
    std::cout << "\t\tTesting knight attacks generations...\n";

    std::cout << "\t\t\tTesting knight attacks on e4...\n";
    ChessBoard board;
    Bitboard e4Attacks = board.generateSingleKnightMaskAttacks(e4);
    assert(e4Attacks.getBit(f6));
    assert(e4Attacks.getBit(g5));
    assert(e4Attacks.getBit(g3));
    assert(e4Attacks.getBit(f2));
    assert(e4Attacks.getBit(d2));
    assert(e4Attacks.getBit(c3));
    assert(e4Attacks.getBit(c5));
    assert(e4Attacks.getBit(d6));
    assert(e4Attacks.popCount() == 8);

    std::cout << "\t\t\tTesting knight attacks on a1...\n";
    Bitboard a1Attacks = board.generateSingleKnightMaskAttacks(a1);
    assert(a1Attacks.getBit(c2));
    assert(a1Attacks.getBit(b3));
    assert(a1Attacks.popCount() == 2);

    std::cout << "\t\t\tTesting knight attacks on a2...\n";
    Bitboard a2Attacks = board.generateSingleKnightMaskAttacks(a2);
    assert(a2Attacks.getBit(b4));
    assert(a2Attacks.getBit(c3));
    assert(a2Attacks.getBit(c1));
    assert(a2Attacks.popCount() == 3);

    std::cout << "\t\t\tTesting knight attacks on g7...\n";
    Bitboard g7Attacks = board.generateSingleKnightMaskAttacks(g7);
    assert(g7Attacks.getBit(h5));
    assert(g7Attacks.getBit(f5));
    assert(g7Attacks.getBit(e6));
    assert(g7Attacks.getBit(e8));
    assert(g7Attacks.popCount() == 4);

    std::cout << "\t\t\tTesting knight attacks on g3...\n";
    Bitboard g3Attacks = board.generateSingleKnightMaskAttacks(g3);
    assert(g3Attacks.getBit(h5));
    assert(g3Attacks.getBit(h1));
    assert(g3Attacks.getBit(f1));
    assert(g3Attacks.getBit(e2));
    assert(g3Attacks.getBit(e4));
    assert(g3Attacks.getBit(f5));
    assert(g3Attacks.popCount() == 6);

    std::cout << "\t\tKnight attacks generations tests passed...\n";
}

int run_chess_board_tests() {
    try {
        test_board_initialization();
        test_to_string();
        test_initial_position();

        test_pawn_attacks_generation();
        test_knight_attacks_generation();

        std::cout << "\tAll board tests passed!\n";
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "\tBoard test failed: " << e.what() << "\n";
        return 1;
    }
}