#include <algorithm>
#include <cassert>
#include <iostream>

#include "../src/chessboard/chessboard-status.h"
#include "../src/chessboard/chessboard.h"
#include "../src/engine/engine.h"
#include "../src/lib/color.h"
#include "../src/lib/masks.h"
#include "../src/lib/square.h"

void test_pawn_attacks_generation() {
    std::cout << "\t\tTesting pawn attacks generations...\n";
    Engine engine;

    std::cout << "\t\t\tTesting pawn attacks on e4 for white...\n";
    Bitboard whiteE4Attacks = engine.generateSinglePawnMaskAttacks(e4, WHITE);
    assert(whiteE4Attacks.getBit(d5));
    assert(whiteE4Attacks.getBit(f5));
    assert(whiteE4Attacks.popCount() == 2);

    std::cout << "\t\t\tTesting pawn attacks on e4 for black...\n";
    Bitboard blackE4Attacks = engine.generateSinglePawnMaskAttacks(e4, BLACK);
    assert(blackE4Attacks.getBit(d3));
    assert(blackE4Attacks.getBit(f3));
    assert(blackE4Attacks.popCount() == 2);

    std::cout << "\t\t\tTesting pawn attacks on a4 for white...\n";
    Bitboard whiteA4Attacks = engine.generateSinglePawnMaskAttacks(a4, WHITE);
    assert(whiteA4Attacks.getBit(b5));
    assert(whiteA4Attacks.popCount() == 1);

    std::cout << "\t\t\tTesting pawn attacks on h4 for black...\n";
    Bitboard blackH4Attacks = engine.generateSinglePawnMaskAttacks(h4, BLACK);
    assert(blackH4Attacks.getBit(g3));
    assert(blackH4Attacks.popCount() == 1);

    std::cout << "\t\tPawn attacks generations tests passed...\n";
}

void test_knight_moves_generation() {
    std::cout << "\t\tTesting knight move generations...\n";

    std::cout << "\t\t\tTesting knight possible moves on e4...\n";
    Engine engine;
    Bitboard e4Attacks = engine.generateSingleKnightAttacksMask(e4);
    assert(e4Attacks.getBit(f6));
    assert(e4Attacks.getBit(g5));
    assert(e4Attacks.getBit(g3));
    assert(e4Attacks.getBit(f2));
    assert(e4Attacks.getBit(d2));
    assert(e4Attacks.getBit(c3));
    assert(e4Attacks.getBit(c5));
    assert(e4Attacks.getBit(d6));
    assert(e4Attacks.popCount() == 8);

    std::cout << "\t\t\tTesting knight possible moves on a1...\n";
    Bitboard a1Attacks = engine.generateSingleKnightAttacksMask(a1);
    assert(a1Attacks.getBit(c2));
    assert(a1Attacks.getBit(b3));
    assert(a1Attacks.popCount() == 2);

    std::cout << "\t\t\tTesting knight possible moves on a2...\n";
    Bitboard a2Attacks = engine.generateSingleKnightAttacksMask(a2);
    assert(a2Attacks.getBit(b4));
    assert(a2Attacks.getBit(c3));
    assert(a2Attacks.getBit(c1));
    assert(a2Attacks.popCount() == 3);

    std::cout << "\t\t\tTesting knight possible moves on g7...\n";
    Bitboard g7Attacks = engine.generateSingleKnightAttacksMask(g7);
    assert(g7Attacks.getBit(h5));
    assert(g7Attacks.getBit(f5));
    assert(g7Attacks.getBit(e6));
    assert(g7Attacks.getBit(e8));
    assert(g7Attacks.popCount() == 4);

    std::cout << "\t\t\tTesting knight possible moves on g3...\n";
    Bitboard g3Attacks = engine.generateSingleKnightAttacksMask(g3);
    assert(g3Attacks.getBit(h5));
    assert(g3Attacks.getBit(h1));
    assert(g3Attacks.getBit(f1));
    assert(g3Attacks.getBit(e2));
    assert(g3Attacks.getBit(e4));
    assert(g3Attacks.getBit(f5));
    assert(g3Attacks.popCount() == 6);

    std::cout << "\t\tKnight possible moves generations tests passed...\n";
}

void test_king_moves_generation() {
    std::cout << "\t\tTesting king move generations...\n";

    std::cout << "\t\t\tTesting king possible moves on e4...\n";
    Engine engine;
    Bitboard e4moves = engine.generateSingleKingAttacksMask(e4);
    assert(e4moves.getBit(d5));
    assert(e4moves.getBit(e5));
    assert(e4moves.getBit(f5));
    assert(e4moves.getBit(f4));
    assert(e4moves.getBit(f3));
    assert(e4moves.getBit(e3));
    assert(e4moves.getBit(d3));
    assert(e4moves.getBit(d4));
    assert(e4moves.popCount() == 8);

    std::cout << "\t\t\tTesting king possible moves on a1...\n";
    Bitboard a1moves = engine.generateSingleKingAttacksMask(a1);
    assert(a1moves.getBit(a2));
    assert(a1moves.getBit(b2));
    assert(a1moves.getBit(b1));
    assert(a1moves.popCount() == 3);

    std::cout << "\t\t\tTesting king possible moves on a8...\n";
    Bitboard a8Moves = engine.generateSingleKingAttacksMask(a8);
    assert(a8Moves.getBit(b8));
    assert(a8Moves.getBit(b7));
    assert(a8Moves.getBit(a7));
    assert(a8Moves.popCount() == 3);

    std::cout << "\t\t\tTesting king possible moves on h8...\n";
    Bitboard h8Moves = engine.generateSingleKingAttacksMask(h8);
    assert(h8Moves.getBit(g8));
    assert(h8Moves.getBit(h7));
    assert(h8Moves.getBit(g7));
    assert(h8Moves.popCount() == 3);

    std::cout << "\t\t\tTesting king possible moves on h1...\n";
    Bitboard h1Moves = engine.generateSingleKingAttacksMask(h1);
    assert(h1Moves.getBit(h2));
    assert(h1Moves.getBit(g2));
    assert(h1Moves.getBit(g1));
    assert(h1Moves.popCount() == 3);

    std::cout << "\t\t\tTesting king possible moves on d8...\n";
    Bitboard d8Moves = engine.generateSingleKingAttacksMask(d8);
    assert(d8Moves.getBit(c8));
    assert(d8Moves.getBit(e8));
    assert(d8Moves.getBit(c7));
    assert(d8Moves.getBit(d7));
    assert(d8Moves.getBit(e7));
    assert(d8Moves.popCount() == 5);

    std::cout << "\t\tKing possible moves generations tests passed...\n";
}

void test_bishop_relevant_occupancies_moves_generation() {
    std::cout << "\t\tTesting bishop relavant occupancies generations...\n";

    Engine engine;

    std::cout << "\t\t\tTesting bishop relavant occupancies on e4...\n";
    Bitboard bOnE4 = engine.generateSingleBishopRelevantOccupanciesMask(e4);
    assert(bOnE4.getBit(c2));
    assert(bOnE4.getBit(g2));
    assert(bOnE4.getBit(d3));
    assert(bOnE4.getBit(f3));
    assert(bOnE4.getBit(d5));
    assert(bOnE4.getBit(f5));
    assert(bOnE4.getBit(c6));
    assert(bOnE4.getBit(g6));
    assert(bOnE4.getBit(b7));
    assert(bOnE4.popCount() == 9);

    std::cout << "\t\t\tTesting bishop relavant occupancies on e1...\n";
    Bitboard bOnE1 = engine.generateSingleBishopRelevantOccupanciesMask(e1);
    assert(bOnE1.getBit(d2));
    assert(bOnE1.getBit(f2));
    assert(bOnE1.getBit(c3));
    assert(bOnE1.getBit(g3));
    assert(bOnE1.getBit(b4));
    assert(bOnE1.popCount() == 5);

    std::cout << "\t\t\tTesting bishop relavant occupancies on h7...\n";
    Bitboard bOnH7 = engine.generateSingleBishopRelevantOccupanciesMask(h7);
    assert(bOnH7.getBit(g6));
    assert(bOnH7.getBit(f5));
    assert(bOnH7.getBit(e4));
    assert(bOnH7.getBit(d3));
    assert(bOnH7.getBit(c2));
    assert(bOnH7.popCount() == 5);

    std::cout << "\t\t\tTesting bishop relavant occupancies on a8...\n";
    Bitboard bOnA8 = engine.generateSingleBishopRelevantOccupanciesMask(a8);
    assert(bOnA8.getBit(b7));
    assert(bOnA8.getBit(c6));
    assert(bOnA8.getBit(d5));
    assert(bOnA8.getBit(e4));
    assert(bOnA8.getBit(f3));
    assert(bOnA8.getBit(g2));
    assert(bOnA8.popCount() == 6);

    std::cout
        << "\t\tBishop relavant occupancies generations tests passed...\n";
}

void test_rook_relevant_occupancies_moves_generation() {
    std::cout << "\t\tTesting rook relavant occupancies generations...\n";

    Engine engine;

    std::cout << "\t\t\tTesting rook relavant occupancies on e4...\n";
    Bitboard rInE4 = engine.generateSingleRookRelevantOccupanciesMask(e4);
    assert(rInE4.getBit(e2));
    assert(rInE4.getBit(e3));
    assert(rInE4.getBit(e5));
    assert(rInE4.getBit(e6));
    assert(rInE4.getBit(e7));
    assert(rInE4.getBit(b4));
    assert(rInE4.getBit(c4));
    assert(rInE4.getBit(d4));
    assert(rInE4.getBit(f4));
    assert(rInE4.getBit(g4));
    assert(rInE4.popCount() == 10);

    std::cout << "\t\t\tTesting rook relavant occupancies on a1...\n";
    Bitboard rInA1 = engine.generateSingleRookRelevantOccupanciesMask(a1);
    assert(rInA1.getBit(a2));
    assert(rInA1.getBit(a3));
    assert(rInA1.getBit(a4));
    assert(rInA1.getBit(a5));
    assert(rInA1.getBit(a6));
    assert(rInA1.getBit(a7));
    assert(rInA1.getBit(b1));
    assert(rInA1.getBit(c1));
    assert(rInA1.getBit(d1));
    assert(rInA1.getBit(e1));
    assert(rInA1.getBit(f1));
    assert(rInA1.getBit(g1));
    assert(rInA1.popCount() == 12);

    std::cout << "\t\t\tTesting rook relavant occupancies on h8...\n";
    Bitboard rInH8 = engine.generateSingleRookRelevantOccupanciesMask(h8);
    assert(rInH8.getBit(h7));
    assert(rInH8.getBit(h6));
    assert(rInH8.getBit(h5));
    assert(rInH8.getBit(h4));
    assert(rInH8.getBit(h3));
    assert(rInH8.getBit(h2));
    assert(rInH8.getBit(g8));
    assert(rInH8.getBit(f8));
    assert(rInH8.getBit(e8));
    assert(rInH8.getBit(d8));
    assert(rInH8.getBit(c8));
    assert(rInH8.getBit(b8));
    assert(rInH8.popCount() == 12);

    std::cout << "\t\t\tTesting rook relavant occupancies on c1...\n";
    Bitboard rInC1 = engine.generateSingleRookRelevantOccupanciesMask(c1);
    assert(rInC1.getBit(b1));
    assert(rInC1.getBit(d1));
    assert(rInC1.getBit(e1));
    assert(rInC1.getBit(f1));
    assert(rInC1.getBit(g1));
    assert(rInC1.getBit(c2));
    assert(rInC1.getBit(c3));
    assert(rInC1.getBit(c4));
    assert(rInC1.getBit(c5));
    assert(rInC1.getBit(c6));
    assert(rInC1.getBit(c7));
    assert(rInC1.popCount() == 11);

    std::cout << "\t\tRook relavant occupancies generations tests passed...\n";
}

void test_bishop_attacks_generation() {
    std::cout << "\t\tTesting bishop attacks generations...\n";
    Engine engine;

    Bitboard blocks;

    std::cout << "\t\t\tTesting bishop attacks on e4 with no blockers ...\n";

    Bitboard bOnE4 = engine.generateSingleBishopAttacks(e4, blocks);
    assert(bOnE4.getBit(b1));
    assert(bOnE4.getBit(h1));
    assert(bOnE4.getBit(c2));
    assert(bOnE4.getBit(g2));
    assert(bOnE4.getBit(d3));
    assert(bOnE4.getBit(f3));
    assert(bOnE4.getBit(d5));
    assert(bOnE4.getBit(f5));
    assert(bOnE4.getBit(c6));
    assert(bOnE4.getBit(g6));
    assert(bOnE4.getBit(b7));
    assert(bOnE4.getBit(a8));
    assert(bOnE4.getBit(h7));
    assert(bOnE4.popCount() == 13);

    std::cout << "\t\t\tTesting bishop attacks on d5 with blockers b3, c6, g8, "
                 "g2...\n";
    blocks.clear();
    blocks.setBit(b3);
    blocks.setBit(c6);
    blocks.setBit(g8);
    blocks.setBit(g2);
    blocks.setBit(g1);  // not a real blocker

    Bitboard b0nD5 = engine.generateSingleBishopAttacks(d5, blocks);
    assert(b0nD5.getBit(c6));
    assert(b0nD5.getBit(b3));
    assert(b0nD5.getBit(c4));
    assert(b0nD5.getBit(e6));
    assert(b0nD5.getBit(e4));
    assert(b0nD5.getBit(f7));
    assert(b0nD5.getBit(f3));
    assert(b0nD5.getBit(g2));
    assert(b0nD5.getBit(g8));
    assert(b0nD5.popCount() == 9);

    std::cout << "\t\t\tTesting bishop attacks on a5 with blockers b6...\n";
    blocks.clear();
    blocks.setBit(b6);
    blocks.setBit(g4);  // not a real blocker

    Bitboard b0nA5 = engine.generateSingleBishopAttacks(a5, blocks);
    assert(b0nA5.getBit(b6));
    assert(b0nA5.getBit(b4));
    assert(b0nA5.getBit(c3));
    assert(b0nA5.getBit(d2));
    assert(b0nA5.getBit(e1));
    assert(b0nA5.popCount() == 5);

    std::cout << "\t\tBishop attacks generations tests passed...\n";
}

void test_rook_attacks_generation() {
    std::cout << "\t\tTesting Rook attacks generations...\n";
    Engine engine;

    Bitboard blocks;

    std::cout << "\t\t\tTesting Rook attacks on d5 with no blockers ...\n";

    Bitboard rOnD5 = engine.generateSingleRookAttacks(d5, blocks);
    assert(rOnD5.getBit(d1));
    assert(rOnD5.getBit(d2));
    assert(rOnD5.getBit(d3));
    assert(rOnD5.getBit(d4));
    assert(rOnD5.getBit(d6));
    assert(rOnD5.getBit(d7));
    assert(rOnD5.getBit(d8));
    assert(rOnD5.getBit(a5));
    assert(rOnD5.getBit(b5));
    assert(rOnD5.getBit(c5));
    assert(rOnD5.getBit(e5));
    assert(rOnD5.getBit(f5));
    assert(rOnD5.getBit(g5));
    assert(rOnD5.getBit(h5));
    assert(rOnD5.popCount() == 14);

    std::cout
        << "\t\t\tTesting Rook attacks on e4 with blockers e7, e3, b4, g4...\n";
    blocks.clear();
    blocks.setBit(e7);
    blocks.setBit(e3);
    blocks.setBit(b4);
    blocks.setBit(g4);
    blocks.setBit(g1);  // not a real blocker

    Bitboard r0nE4 = engine.generateSingleRookAttacks(e4, blocks);
    assert(r0nE4.getBit(e3));
    assert(r0nE4.getBit(e5));
    assert(r0nE4.getBit(e6));
    assert(r0nE4.getBit(e7));
    assert(r0nE4.getBit(b4));
    assert(r0nE4.getBit(c4));
    assert(r0nE4.getBit(d4));
    assert(r0nE4.getBit(f4));
    assert(r0nE4.getBit(g4));
    assert(r0nE4.popCount() == 9);

    std::cout << "\t\t\tTesting Rook attacks on b6 with blockers b4...\n";
    blocks.clear();
    blocks.setBit(b4);
    blocks.setBit(g2);  // not a real blocker

    Bitboard r0nB6 = engine.generateSingleRookAttacks(b6, blocks);
    assert(r0nB6.getBit(b8));
    assert(r0nB6.getBit(b7));
    assert(r0nB6.getBit(b5));
    assert(r0nB6.getBit(b4));
    assert(r0nB6.getBit(a6));
    assert(r0nB6.getBit(c6));
    assert(r0nB6.getBit(d6));
    assert(r0nB6.getBit(e6));
    assert(r0nB6.getBit(f6));
    assert(r0nB6.getBit(g6));
    assert(r0nB6.popCount() == 11);

    std::cout << "\t\tRook attacks generations tests passed...\n";
}

void test_sliding_pieces_generation() {
    std::cout << "\t\tTesting Sliding pieced attacks generations...\n";
    Engine engine;

    engine.generateSliderPiecesAttacks(IS_BISHOP);
    engine.generateSliderPiecesAttacks(IS_ROOK);

    Bitboard occupancies;
    occupancies.setBit(f6);
    occupancies.setBit(f2);
    occupancies.setBit(b2);
    occupancies.setBit(b1);
    occupancies.setBit(h2);
    occupancies.setBit(h7);
    occupancies.setBit(e4);
    std::cout << "\t\t\tSetting Occupancies on: f6, f2, b2, b1, h2, h7, e4\n";

    std::cout << "\t\t\t\tTesting bishop on d4\n";
    Bitboard bOnd4Attacks = engine.getSingleBishopAttacks(d4, occupancies);
    assert(bOnd4Attacks.getBit(c5));
    assert(bOnd4Attacks.getBit(b6));
    assert(bOnd4Attacks.getBit(a7));
    assert(bOnd4Attacks.getBit(e5));
    assert(bOnd4Attacks.getBit(f6));
    assert(bOnd4Attacks.getBit(e3));
    assert(bOnd4Attacks.getBit(f2));
    assert(bOnd4Attacks.getBit(c3));
    assert(bOnd4Attacks.getBit(b2));
    assert(bOnd4Attacks.popCount() == 9);
    std::cout << "\t\t\t\tBishop on d4 tests passed...\n";

    std::cout << "\t\t\t\tTesting bishop on c2\n";
    Bitboard bOnc2Attacks = engine.getSingleBishopAttacks(c2, occupancies);
    assert(bOnc2Attacks.getBit(b1));
    assert(bOnc2Attacks.getBit(d1));
    assert(bOnc2Attacks.getBit(b3));
    assert(bOnc2Attacks.getBit(d3));
    assert(bOnc2Attacks.getBit(a4));
    assert(bOnc2Attacks.getBit(e4));
    assert(bOnc2Attacks.popCount() == 6);

    std::cout << "\t\t\t\tBishop on c2 tests passed...\n";

    std::cout << "\t\t\t\tTesting rook on f4\n";
    Bitboard rOnf4Attacks = engine.getSingleRookAttacks(f4, occupancies);
    assert(rOnf4Attacks.getBit(e4));
    assert(rOnf4Attacks.getBit(g4));
    assert(rOnf4Attacks.getBit(h4));
    assert(rOnf4Attacks.getBit(f2));
    assert(rOnf4Attacks.getBit(f3));
    assert(rOnf4Attacks.getBit(f5));
    assert(rOnf4Attacks.getBit(f6));
    assert(rOnf4Attacks.popCount() == 7);
    std::cout << "\t\t\t\tRook on f4 tests passed...\n";

    std::cout << "\t\t\t\tTesting rook on e2\n";
    Bitboard rOne2Attacks = engine.getSingleRookAttacks(e2, occupancies);
    assert(rOne2Attacks.getBit(e1));
    assert(rOne2Attacks.getBit(e3));
    assert(rOne2Attacks.getBit(e4));
    assert(rOne2Attacks.getBit(b2));
    assert(rOne2Attacks.getBit(c2));
    assert(rOne2Attacks.getBit(d2));
    assert(rOne2Attacks.getBit(f2));
    assert(rOne2Attacks.popCount() == 7);
    std::cout << "\t\t\t\tRook on e2 tests passed...\n";

    std::cout
        << "\t\t\tOccupancies on: f6, f2, b2, b1, h2, h7, e4, tests passed\n";

    Bitboard occupancies_2;
    occupancies_2.setBit(a3);
    occupancies_2.setBit(b3);
    occupancies_2.setBit(c3);
    occupancies_2.setBit(c2);
    occupancies_2.setBit(c1);
    std::cout << "\t\t\tSetting Occupancies on: a3, b3, c3, c2, c1...\n";

    std::cout << "\t\t\t\tTesting bishop on a1\n";
    Bitboard bOna1Attacks = engine.getSingleBishopAttacks(a1, occupancies_2);
    assert(bOna1Attacks.getBit(b2));
    assert(bOna1Attacks.getBit(c3));
    assert(bOna1Attacks.popCount() == 2);
    std::cout << "\t\t\t\tBishop on a1 tests passed...\n";

    std::cout << "\t\t\t\tTesting bishop on h8\n";
    Bitboard bOnh8Attacks = engine.getSingleBishopAttacks(h8, occupancies_2);
    assert(bOnh8Attacks.getBit(g7));
    assert(bOnh8Attacks.getBit(f6));
    assert(bOnh8Attacks.getBit(e5));
    assert(bOnh8Attacks.getBit(d4));
    assert(bOnh8Attacks.getBit(c3));
    assert(bOnh8Attacks.popCount() == 5);
    std::cout << "\t\t\t\tBishop on h8 tests passed...\n";

    std::cout << "\t\t\t\tTesting rook on b2\n";
    Bitboard rOnb2Attacks = engine.getSingleRookAttacks(b2, occupancies_2);
    assert(rOnb2Attacks.getBit(b1));
    assert(rOnb2Attacks.getBit(a2));
    assert(rOnb2Attacks.getBit(b3));
    assert(rOnb2Attacks.getBit(c2));
    assert(rOnb2Attacks.popCount() == 4);
    std::cout << "\t\t\t\tRook on b2 tests passed...\n";

    std::cout << "\t\t\t\tTesting rook on h2\n";
    Bitboard rOnh2Attacks = engine.getSingleRookAttacks(h2, occupancies_2);
    assert(rOnh2Attacks.getBit(h1));
    assert(rOnh2Attacks.getBit(h3));
    assert(rOnh2Attacks.getBit(h4));
    assert(rOnh2Attacks.getBit(h5));
    assert(rOnh2Attacks.getBit(h6));
    assert(rOnh2Attacks.getBit(h7));
    assert(rOnh2Attacks.getBit(h8));
    assert(rOnh2Attacks.getBit(g2));
    assert(rOnh2Attacks.getBit(f2));
    assert(rOnh2Attacks.getBit(e2));
    assert(rOnh2Attacks.getBit(d2));
    assert(rOnh2Attacks.getBit(c2));
    assert(rOnh2Attacks.popCount() == 12);
    std::cout << "\t\t\t\tRook on h2 tests passed...\n";

    std::cout << "\t\t\tOccupancies on: a3, b3, c3, c2, c1, tests passed\n";

    std::cout << "\t\tSliding pieced attacks generations tests passed...\n";
}

void test_square_under_attacks() {
    std::cout << "\t\tTesting Square under attacks...\n";
    Engine engine;
    engine.init();

    std::cout << "\t\t\tTesting Squares under attacks in 8/8/8/8/3p4/8/8/8 w "
                 "KQkq - 0 0\n";

    ChessBoard board;
    board.parseFEN("8/8/8/8/3p4/8/8/8 w KQkq - 0 0");

    assert(engine.isSquareUnderAttackBy(&board.status, c3, BLACK));
    assert(engine.isSquareUnderAttackBy(&board.status, e3, BLACK));
    assert(!engine.isSquareUnderAttackBy(&board.status, a1, BLACK));

    assert(!engine.isSquareUnderAttackBy(&board.status, e3, WHITE));
    assert(!engine.isSquareUnderAttackBy(&board.status, c3, WHITE));
    assert(!engine.isSquareUnderAttackBy(&board.status, f7, WHITE));

    std::cout << "\t\t\tSquares under attacks in 8/8/8/8/3P4/8/8/8 w "
                 "KQkq - 0 0 tests passed...\n";

    std::cout << "\t\t\tTesting Squares under attacks in 8/8/8/8/3P4/8/8/8 w "
                 "KQkq - 0 0\n";

    board.parseFEN("8/8/8/8/3P4/8/8/8 w KQkq - 0 0");

    assert(engine.isSquareUnderAttackBy(&board.status, e5, WHITE));
    assert(engine.isSquareUnderAttackBy(&board.status, c5, WHITE));
    assert(!engine.isSquareUnderAttackBy(&board.status, f7, WHITE));

    assert(!engine.isSquareUnderAttackBy(&board.status, c3, BLACK));
    assert(!engine.isSquareUnderAttackBy(&board.status, e3, BLACK));
    assert(!engine.isSquareUnderAttackBy(&board.status, a1, BLACK));

    std::cout << "\t\t\tSquares under attacks in 8/8/8/8/3P4/8/8/8 w "
                 "KQkq - 0 0 tests passed...\n";

    std::cout << "\t\t\tTesting Squares under attacks in 8/2p3/8/8/2P5/8/8/8 w "
                 "KQkq - 0 0\n";

    board.parseFEN("8/2p3/8/8/2P5/8/8/8 w KQkq - 0 0");

    assert(engine.isSquareUnderAttackBy(&board.status, b5, WHITE));
    assert(engine.isSquareUnderAttackBy(&board.status, d5, WHITE));
    assert(!engine.isSquareUnderAttackBy(&board.status, c5, WHITE));
    assert(!engine.isSquareUnderAttackBy(&board.status, d6, WHITE));
    assert(!engine.isSquareUnderAttackBy(&board.status, b6, WHITE));

    assert(engine.isSquareUnderAttackBy(&board.status, b6, BLACK));
    assert(engine.isSquareUnderAttackBy(&board.status, d6, BLACK));
    assert(!engine.isSquareUnderAttackBy(&board.status, c3, BLACK));
    assert(!engine.isSquareUnderAttackBy(&board.status, e3, BLACK));
    assert(!engine.isSquareUnderAttackBy(&board.status, a1, BLACK));

    std::cout << "\t\t\tSquares under attacks in 8/2p3/8/8/2P5/8/8/8 w KQkq - "
                 "0 0  tests passed...\n";

    // 8/2p3/8/8/2P5/8/1q6/8 w KQkq - 0 0

    std::cout << "\t\t\tTesting Squares under attacks in 8/2p3/8/8/2P5/8/1q6/8 "
                 "w KQkq - 0 0\n";

    board.parseFEN("8/2p3/8/8/2P5/8/1q6/8 w KQkq - 0 0");

    assert(engine.isSquareUnderAttackBy(&board.status, b5, WHITE));
    assert(engine.isSquareUnderAttackBy(&board.status, d5, WHITE));
    assert(!engine.isSquareUnderAttackBy(&board.status, c5, WHITE));
    assert(!engine.isSquareUnderAttackBy(&board.status, d6, WHITE));
    assert(!engine.isSquareUnderAttackBy(&board.status, b6, WHITE));

    assert(engine.isSquareUnderAttackBy(&board.status, a1, BLACK));
    assert(engine.isSquareUnderAttackBy(&board.status, b6, BLACK));
    assert(engine.isSquareUnderAttackBy(&board.status, d6, BLACK));
    assert(engine.isSquareUnderAttackBy(&board.status, c3, BLACK));
    assert(engine.isSquareUnderAttackBy(&board.status, b8, BLACK));
    assert(engine.isSquareUnderAttackBy(&board.status, h8, BLACK));
    assert(!engine.isSquareUnderAttackBy(&board.status, e3, BLACK));

    std::cout << "\t\t\tSquares under attacks in 8/2p3/8/8/2P5/8/1q6/8 w KQkq "
                 "- 0 0  tests "
                 "passed...\n";

    std::cout << "\t\tSquare under attacks tests passed...\n";
}

void test_move_generations() {
    std::cout << "\t\tTesting move generations...\n";
    Engine engine;
    engine.init();

    ChessBoard board;
    std::vector<std::tuple<Move, MoveType>> moves;

    std::cout << "\t\t\tTesting quite pawn move generation...\n";

    std::cout << "\t\t\t\tTesting initial position white to play\n";
    board.setupInitialPosition();
    moves = engine.generateMoves(&board.status);
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{a2, a3}, PAWN_PUSH)) != moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{b2, b3}, PAWN_PUSH)) != moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{c2, c3}, PAWN_PUSH)) != moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{d2, d3}, PAWN_PUSH)) != moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{e2, e3}, PAWN_PUSH)) != moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{f2, f3}, PAWN_PUSH)) != moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{g2, g3}, PAWN_PUSH)) != moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{h2, h3}, PAWN_PUSH)) != moves.end());

    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{a2, a4}, PAWN_DOUBLE_PUSH)) !=
           moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{b2, b4}, PAWN_DOUBLE_PUSH)) !=
           moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{c2, c4}, PAWN_DOUBLE_PUSH)) !=
           moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{d2, d4}, PAWN_DOUBLE_PUSH)) !=
           moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{e2, e4}, PAWN_DOUBLE_PUSH)) !=
           moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{f2, f4}, PAWN_DOUBLE_PUSH)) !=
           moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{g2, g4}, PAWN_DOUBLE_PUSH)) !=
           moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{h2, h4}, PAWN_DOUBLE_PUSH)) !=
           moves.end());

    std::cout << "\t\t\t\tInitial position white to play tests passed\n";

    std::cout
        << "\t\t\t\tTesting initial position after a2->a4, black to play\n";
    board.parseFEN(
        "rnbqkbnr/pppppppp/8/8/P7/8/1PPPPPPP/RNBQKBNR b KQkq e3 0 1");
    moves = engine.generateMoves(&board.status);
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{a7, a6}, PAWN_PUSH)) != moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{b7, b6}, PAWN_PUSH)) != moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{c7, c6}, PAWN_PUSH)) != moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{d7, d6}, PAWN_PUSH)) != moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{e7, e6}, PAWN_PUSH)) != moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{f7, f6}, PAWN_PUSH)) != moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{g7, g6}, PAWN_PUSH)) != moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{h7, h6}, PAWN_PUSH)) != moves.end());

    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{a7, a5}, PAWN_DOUBLE_PUSH)) !=
           moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{b7, b5}, PAWN_DOUBLE_PUSH)) !=
           moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{c7, c5}, PAWN_DOUBLE_PUSH)) !=
           moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{d7, d5}, PAWN_DOUBLE_PUSH)) !=
           moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{e7, e5}, PAWN_DOUBLE_PUSH)) !=
           moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{f7, f5}, PAWN_DOUBLE_PUSH)) !=
           moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{g7, g5}, PAWN_DOUBLE_PUSH)) !=
           moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{h7, h5}, PAWN_DOUBLE_PUSH)) !=
           moves.end());

    std::cout << "\t\t\t\tInitial position after a2->a4, black to play tests "
                 "passed\n";

    std::cout << "\t\t\t\tTesting "
                 "r3k2r/pPppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPpP/R3K2R b "
                 "KQkq - 0 0\n";
    board.parseFEN(
        "r3k2r/pPppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPpP/R3K2R b KQkq - 0 0");
    moves = engine.generateMoves(&board.status);
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{b4, b3}, PAWN_PUSH)) != moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{g6, g5}, PAWN_PUSH)) != moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{c7, c6}, PAWN_PUSH)) != moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{d7, d6}, PAWN_PUSH)) != moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{c7, c5}, PAWN_DOUBLE_PUSH)) !=
           moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{g2, g1}, PAWN_PROMOTION_TO_BISHOP)) !=
           moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{g2, g1}, PAWN_PROMOTION_TO_ROOK)) !=
           moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{g2, g1}, PAWN_PROMOTION_TO_KNIGHT)) !=
           moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{g2, g1}, PAWN_PROMOTION_TO_QUEEN)) !=
           moves.end());

    std::cout
        << "\t\t\t\tr3k2r/pPppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPpP/R3K2R b "
           "KQkq - 0 0 tests passed\n";

    std::cout << "\t\t\t\tTesting "
                 "r3k2r/pPppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPpP/R3K2R w "
                 "KQkq - 0 0\n";
    board.parseFEN(
        "r3k2r/pPppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPpP/R3K2R w KQkq - 0 0");
    moves = engine.generateMoves(&board.status);
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{a2, a3}, PAWN_PUSH)) != moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{b2, b3}, PAWN_PUSH)) != moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{d5, d6}, PAWN_PUSH)) != moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{a2, a4}, PAWN_DOUBLE_PUSH)) !=
           moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{b7, b8}, PAWN_PROMOTION_TO_BISHOP)) !=
           moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{b7, b8}, PAWN_PROMOTION_TO_ROOK)) !=
           moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{b7, b8}, PAWN_PROMOTION_TO_KNIGHT)) !=
           moves.end());
    assert(std::find(moves.begin(), moves.end(),
                     std::make_tuple(Move{b7, b8}, PAWN_PROMOTION_TO_QUEEN)) !=
           moves.end());

    std::cout
        << "\t\t\t\tr3k2r/pPppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPpP/R3K2R w "
           "KQkq - 0 0 tests passed\n";

    std::cout << "\t\t\tPawn move generation tests passed...\n";

    std::cout << "\t\tSquare under attacks tests passed...\n";
}

int run_engine_tests() {
    std::cout << "\tTesting engine...!\n";
    test_pawn_attacks_generation();
    test_knight_moves_generation();
    test_king_moves_generation();

    test_bishop_relevant_occupancies_moves_generation();
    test_rook_relevant_occupancies_moves_generation();

    test_bishop_attacks_generation();
    test_rook_attacks_generation();

    test_sliding_pieces_generation();
    test_square_under_attacks();

    test_move_generations();

    std::cout << "\tAll engine tests passed!\n";
    return 0;
}