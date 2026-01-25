#include <algorithm>
#include <iostream>

#include "../src/chessboard/chessboard-status.h"
#include "../src/chessboard/chessboard.h"
#include "../src/engine/engine.h"
#include "../src/lib/color.h"
#include "../src/lib/masks.h"
#include "../src/lib/square.h"
#include "test_lib.h"

void test_pawn_attacks_generation() {
    describe("Testing pawn attacks generations", []() {
        Engine engine;

        it("Testing pawn attacks on e4 for white", [&]() {
            Bitboard whiteE4Attacks =
                engine.generateSinglePawnMaskAttacks(e4, WHITE);
            expect(whiteE4Attacks.getBit(d5));
            expect(whiteE4Attacks.getBit(f5));
            expect(whiteE4Attacks.popCount() == 2);
        });

        it("Testing pawn attacks on e4 for black", [&]() {
            Bitboard blackE4Attacks =
                engine.generateSinglePawnMaskAttacks(e4, BLACK);
            expect(blackE4Attacks.getBit(d3));
            expect(blackE4Attacks.getBit(f3));
            expect(blackE4Attacks.popCount() == 2);
        });

        it("Testing pawn attacks on a4 for white", [&]() {
            Bitboard whiteA4Attacks =
                engine.generateSinglePawnMaskAttacks(a4, WHITE);
            expect(whiteA4Attacks.getBit(b5));
            expect(whiteA4Attacks.popCount() == 1);
        });

        it("Testing pawn attacks on h4 for black", [&]() {
            Bitboard blackH4Attacks =
                engine.generateSinglePawnMaskAttacks(h4, BLACK);
            expect(blackH4Attacks.getBit(g3));
            expect(blackH4Attacks.popCount() == 1);
        });
    });
}

void test_knight_moves_generation() {
    describe("Testing knight move generations", []() {
        Engine engine;

        it("Testing knight possible moves on e4", [&]() {
            Bitboard e4Attacks = engine.generateSingleKnightAttacksMask(e4);
            expect(e4Attacks.getBit(f6));
            expect(e4Attacks.getBit(g5));
            expect(e4Attacks.getBit(g3));
            expect(e4Attacks.getBit(f2));
            expect(e4Attacks.getBit(d2));
            expect(e4Attacks.getBit(c3));
            expect(e4Attacks.getBit(c5));
            expect(e4Attacks.getBit(d6));
            expect(e4Attacks.popCount() == 8);
        });

        it("Testing knight possible moves on a1", [&]() {
            Bitboard a1Attacks = engine.generateSingleKnightAttacksMask(a1);
            expect(a1Attacks.getBit(c2));
            expect(a1Attacks.getBit(b3));
            expect(a1Attacks.popCount() == 2);
        });

        it("Testing knight possible moves on a2", [&]() {
            Bitboard a2Attacks = engine.generateSingleKnightAttacksMask(a2);
            expect(a2Attacks.getBit(b4));
            expect(a2Attacks.getBit(c3));
            expect(a2Attacks.getBit(c1));
            expect(a2Attacks.popCount() == 3);
        });

        it("Testing knight possible moves on g7", [&]() {
            Bitboard g7Attacks = engine.generateSingleKnightAttacksMask(g7);
            expect(g7Attacks.getBit(h5));
            expect(g7Attacks.getBit(f5));
            expect(g7Attacks.getBit(e6));
            expect(g7Attacks.getBit(e8));
            expect(g7Attacks.popCount() == 4);
        });

        it("Testing knight possible moves on g3", [&]() {
            Bitboard g3Attacks = engine.generateSingleKnightAttacksMask(g3);
            expect(g3Attacks.getBit(h5));
            expect(g3Attacks.getBit(h1));
            expect(g3Attacks.getBit(f1));
            expect(g3Attacks.getBit(e2));
            expect(g3Attacks.getBit(e4));
            expect(g3Attacks.getBit(f5));
            expect(g3Attacks.popCount() == 6);
        });
    });
}

void test_king_moves_generation() {
    describe("Testing king move generations", []() {
        Engine engine;

        it("Testing king possible moves on e4", [&]() {
            Bitboard e4moves = engine.generateSingleKingAttacksMask(e4);
            expect(e4moves.getBit(d5));
            expect(e4moves.getBit(e5));
            expect(e4moves.getBit(f5));
            expect(e4moves.getBit(f4));
            expect(e4moves.getBit(f3));
            expect(e4moves.getBit(e3));
            expect(e4moves.getBit(d3));
            expect(e4moves.getBit(d4));
            expect(e4moves.popCount() == 8);
        });

        it("Testing king possible moves on a1", [&]() {
            Bitboard a1moves = engine.generateSingleKingAttacksMask(a1);
            expect(a1moves.getBit(a2));
            expect(a1moves.getBit(b2));
            expect(a1moves.getBit(b1));
            expect(a1moves.popCount() == 3);
        });

        it("Testing king possible moves on a8", [&]() {
            Bitboard a8Moves = engine.generateSingleKingAttacksMask(a8);
            expect(a8Moves.getBit(b8));
            expect(a8Moves.getBit(b7));
            expect(a8Moves.getBit(a7));
            expect(a8Moves.popCount() == 3);
        });

        it("Testing king possible moves on h8", [&]() {
            Bitboard h8Moves = engine.generateSingleKingAttacksMask(h8);
            expect(h8Moves.getBit(g8));
            expect(h8Moves.getBit(h7));
            expect(h8Moves.getBit(g7));
            expect(h8Moves.popCount() == 3);
        });

        it("Testing king possible moves on h1", [&]() {
            Bitboard h1Moves = engine.generateSingleKingAttacksMask(h1);
            expect(h1Moves.getBit(h2));
            expect(h1Moves.getBit(g2));
            expect(h1Moves.getBit(g1));
            expect(h1Moves.popCount() == 3);
        });

        it("Testing king possible moves on d8", [&]() {
            Bitboard d8Moves = engine.generateSingleKingAttacksMask(d8);
            expect(d8Moves.getBit(c8));
            expect(d8Moves.getBit(e8));
            expect(d8Moves.getBit(c7));
            expect(d8Moves.getBit(d7));
            expect(d8Moves.getBit(e7));
            expect(d8Moves.popCount() == 5);
        });
    });
}

void test_bishop_relevant_occupancies_moves_generation() {
    describe("Testing bishop relavant occupancies generations", []() {
        Engine engine;

        it("Testing bishop relavant occupancies on e4", [&]() {
            Bitboard bOnE4 =
                engine.generateSingleBishopRelevantOccupanciesMask(e4);
            expect(bOnE4.getBit(c2));
            expect(bOnE4.getBit(g2));
            expect(bOnE4.getBit(d3));
            expect(bOnE4.getBit(f3));
            expect(bOnE4.getBit(d5));
            expect(bOnE4.getBit(f5));
            expect(bOnE4.getBit(c6));
            expect(bOnE4.getBit(g6));
            expect(bOnE4.getBit(b7));
            expect(bOnE4.popCount() == 9);
        });

        it("Testing bishop relavant occupancies on e1", [&]() {
            Bitboard bOnE1 =
                engine.generateSingleBishopRelevantOccupanciesMask(e1);
            expect(bOnE1.getBit(d2));
            expect(bOnE1.getBit(f2));
            expect(bOnE1.getBit(c3));
            expect(bOnE1.getBit(g3));
            expect(bOnE1.getBit(b4));
            expect(bOnE1.popCount() == 5);
        });

        it("Testing bishop relavant occupancies on h7", [&]() {
            Bitboard bOnH7 =
                engine.generateSingleBishopRelevantOccupanciesMask(h7);
            expect(bOnH7.getBit(g6));
            expect(bOnH7.getBit(f5));
            expect(bOnH7.getBit(e4));
            expect(bOnH7.getBit(d3));
            expect(bOnH7.getBit(c2));
            expect(bOnH7.popCount() == 5);
        });

        it("Testing bishop relavant occupancies on a8", [&]() {
            Bitboard bOnA8 =
                engine.generateSingleBishopRelevantOccupanciesMask(a8);
            expect(bOnA8.getBit(b7));
            expect(bOnA8.getBit(c6));
            expect(bOnA8.getBit(d5));
            expect(bOnA8.getBit(e4));
            expect(bOnA8.getBit(f3));
            expect(bOnA8.getBit(g2));
            expect(bOnA8.popCount() == 6);
        });
    });
}

void test_rook_relevant_occupancies_moves_generation() {
    describe("Testing rook relavant occupancies generations", []() {
        Engine engine;

        it("Testing rook relavant occupancies on e4", [&]() {
            Bitboard rInE4 =
                engine.generateSingleRookRelevantOccupanciesMask(e4);
            expect(rInE4.getBit(e2));
            expect(rInE4.getBit(e3));
            expect(rInE4.getBit(e5));
            expect(rInE4.getBit(e6));
            expect(rInE4.getBit(e7));
            expect(rInE4.getBit(b4));
            expect(rInE4.getBit(c4));
            expect(rInE4.getBit(d4));
            expect(rInE4.getBit(f4));
            expect(rInE4.getBit(g4));
            expect(rInE4.popCount() == 10);
        });

        it("Testing rook relavant occupancies on a1", [&]() {
            Bitboard rInA1 =
                engine.generateSingleRookRelevantOccupanciesMask(a1);
            expect(rInA1.getBit(a2));
            expect(rInA1.getBit(a3));
            expect(rInA1.getBit(a4));
            expect(rInA1.getBit(a5));
            expect(rInA1.getBit(a6));
            expect(rInA1.getBit(a7));
            expect(rInA1.getBit(b1));
            expect(rInA1.getBit(c1));
            expect(rInA1.getBit(d1));
            expect(rInA1.getBit(e1));
            expect(rInA1.getBit(f1));
            expect(rInA1.getBit(g1));
            expect(rInA1.popCount() == 12);
        });

        it("Testing rook relavant occupancies on h8", [&]() {
            Bitboard rInH8 =
                engine.generateSingleRookRelevantOccupanciesMask(h8);
            expect(rInH8.getBit(h7));
            expect(rInH8.getBit(h6));
            expect(rInH8.getBit(h5));
            expect(rInH8.getBit(h4));
            expect(rInH8.getBit(h3));
            expect(rInH8.getBit(h2));
            expect(rInH8.getBit(g8));
            expect(rInH8.getBit(f8));
            expect(rInH8.getBit(e8));
            expect(rInH8.getBit(d8));
            expect(rInH8.getBit(c8));
            expect(rInH8.getBit(b8));
            expect(rInH8.popCount() == 12);
        });

        it("Testing rook relavant occupancies on c1", [&]() {
            Bitboard rInC1 =
                engine.generateSingleRookRelevantOccupanciesMask(c1);
            expect(rInC1.getBit(b1));
            expect(rInC1.getBit(d1));
            expect(rInC1.getBit(e1));
            expect(rInC1.getBit(f1));
            expect(rInC1.getBit(g1));
            expect(rInC1.getBit(c2));
            expect(rInC1.getBit(c3));
            expect(rInC1.getBit(c4));
            expect(rInC1.getBit(c5));
            expect(rInC1.getBit(c6));
            expect(rInC1.getBit(c7));
            expect(rInC1.popCount() == 11);
        });
    });
}

void test_bishop_attacks_generation() {
    describe("Testing bishop attacks generations", []() {
        Engine engine;
        Bitboard blocks;

        it("Testing bishop attacks on e4 with no blockers", [&]() {
            Bitboard bOnE4 = engine.generateSingleBishopAttacks(e4, blocks);
            expect(bOnE4.getBit(b1));
            expect(bOnE4.getBit(h1));
            expect(bOnE4.getBit(c2));
            expect(bOnE4.getBit(g2));
            expect(bOnE4.getBit(d3));
            expect(bOnE4.getBit(f3));
            expect(bOnE4.getBit(d5));
            expect(bOnE4.getBit(f5));
            expect(bOnE4.getBit(c6));
            expect(bOnE4.getBit(g6));
            expect(bOnE4.getBit(b7));
            expect(bOnE4.getBit(a8));
            expect(bOnE4.getBit(h7));
            expect(bOnE4.popCount() == 13);
        });

        it("Testing bishop attacks on d5 with blockers b3, c6, g8, g2", [&]() {
            blocks.clear();
            blocks.setBit(b3);
            blocks.setBit(c6);
            blocks.setBit(g8);
            blocks.setBit(g2);
            blocks.setBit(g1);  // not a real blocker

            Bitboard b0nD5 = engine.generateSingleBishopAttacks(d5, blocks);
            expect(b0nD5.getBit(c6));
            expect(b0nD5.getBit(b3));
            expect(b0nD5.getBit(c4));
            expect(b0nD5.getBit(e6));
            expect(b0nD5.getBit(e4));
            expect(b0nD5.getBit(f7));
            expect(b0nD5.getBit(f3));
            expect(b0nD5.getBit(g2));
            expect(b0nD5.getBit(g8));
            expect(b0nD5.popCount() == 9);
        });

        it("Testing bishop attacks on a5 with blockers b6", [&]() {
            blocks.clear();
            blocks.setBit(b6);
            blocks.setBit(g4);  // not a real blocker

            Bitboard b0nA5 = engine.generateSingleBishopAttacks(a5, blocks);
            expect(b0nA5.getBit(b6));
            expect(b0nA5.getBit(b4));
            expect(b0nA5.getBit(c3));
            expect(b0nA5.getBit(d2));
            expect(b0nA5.getBit(e1));
            expect(b0nA5.popCount() == 5);
        });
    });
}

void test_rook_attacks_generation() {
    describe("Testing Rook attacks generations", []() {
        Engine engine;
        Bitboard blocks;

        it("Testing Rook attacks on d5 with no blockers", [&]() {
            Bitboard rOnD5 = engine.generateSingleRookAttacks(d5, blocks);
            expect(rOnD5.getBit(d1));
            expect(rOnD5.getBit(d2));
            expect(rOnD5.getBit(d3));
            expect(rOnD5.getBit(d4));
            expect(rOnD5.getBit(d6));
            expect(rOnD5.getBit(d7));
            expect(rOnD5.getBit(d8));
            expect(rOnD5.getBit(a5));
            expect(rOnD5.getBit(b5));
            expect(rOnD5.getBit(c5));
            expect(rOnD5.getBit(e5));
            expect(rOnD5.getBit(f5));
            expect(rOnD5.getBit(g5));
            expect(rOnD5.getBit(h5));
            expect(rOnD5.popCount() == 14);
        });

        it("Testing Rook attacks on e4 with blockers e7, e3, b4, g4", [&]() {
            blocks.clear();
            blocks.setBit(e7);
            blocks.setBit(e3);
            blocks.setBit(b4);
            blocks.setBit(g4);
            blocks.setBit(g1);  // not a real blocker

            Bitboard r0nE4 = engine.generateSingleRookAttacks(e4, blocks);
            expect(r0nE4.getBit(e3));
            expect(r0nE4.getBit(e5));
            expect(r0nE4.getBit(e6));
            expect(r0nE4.getBit(e7));
            expect(r0nE4.getBit(b4));
            expect(r0nE4.getBit(c4));
            expect(r0nE4.getBit(d4));
            expect(r0nE4.getBit(f4));
            expect(r0nE4.getBit(g4));
            expect(r0nE4.popCount() == 9);
        });

        it("Testing Rook attacks on b6 with blockers b4", [&]() {
            blocks.clear();
            blocks.setBit(b4);
            blocks.setBit(g2);  // not a real blocker

            Bitboard r0nB6 = engine.generateSingleRookAttacks(b6, blocks);
            expect(r0nB6.getBit(b8));
            expect(r0nB6.getBit(b7));
            expect(r0nB6.getBit(b5));
            expect(r0nB6.getBit(b4));
            expect(r0nB6.getBit(a6));
            expect(r0nB6.getBit(c6));
            expect(r0nB6.getBit(d6));
            expect(r0nB6.getBit(e6));
            expect(r0nB6.getBit(f6));
            expect(r0nB6.getBit(g6));
            expect(r0nB6.popCount() == 11);
        });
    });
}

void test_sliding_pieces_generation() {
    describe("Testing Sliding pieced attacks generations", []() {
        Engine engine;

        engine.generateSliderPiecesAttacks(IS_BISHOP);
        engine.generateSliderPiecesAttacks(IS_ROOK);

        describe("Occupancies on: f6, f2, b2, b1, h2, h7, e4", [&]() {
            Bitboard occupancies;
            occupancies.setBit(f6);
            occupancies.setBit(f2);
            occupancies.setBit(b2);
            occupancies.setBit(b1);
            occupancies.setBit(h2);
            occupancies.setBit(h7);
            occupancies.setBit(e4);

            it("Testing bishop on d4", [&]() {
                Bitboard bOnd4Attacks =
                    engine.getSingleBishopAttacks(d4, occupancies);
                expect(bOnd4Attacks.getBit(c5));
                expect(bOnd4Attacks.getBit(b6));
                expect(bOnd4Attacks.getBit(a7));
                expect(bOnd4Attacks.getBit(e5));
                expect(bOnd4Attacks.getBit(f6));
                expect(bOnd4Attacks.getBit(e3));
                expect(bOnd4Attacks.getBit(f2));
                expect(bOnd4Attacks.getBit(c3));
                expect(bOnd4Attacks.getBit(b2));
                expect(bOnd4Attacks.popCount() == 9);
            });

            it("Testing bishop on c2", [&]() {
                Bitboard bOnc2Attacks =
                    engine.getSingleBishopAttacks(c2, occupancies);
                expect(bOnc2Attacks.getBit(b1));
                expect(bOnc2Attacks.getBit(d1));
                expect(bOnc2Attacks.getBit(b3));
                expect(bOnc2Attacks.getBit(d3));
                expect(bOnc2Attacks.getBit(a4));
                expect(bOnc2Attacks.getBit(e4));
                expect(bOnc2Attacks.popCount() == 6);
            });

            it("Testing rook on f4", [&]() {
                Bitboard rOnf4Attacks =
                    engine.getSingleRookAttacks(f4, occupancies);
                expect(rOnf4Attacks.getBit(e4));
                expect(rOnf4Attacks.getBit(g4));
                expect(rOnf4Attacks.getBit(h4));
                expect(rOnf4Attacks.getBit(f2));
                expect(rOnf4Attacks.getBit(f3));
                expect(rOnf4Attacks.getBit(f5));
                expect(rOnf4Attacks.getBit(f6));
                expect(rOnf4Attacks.popCount() == 7);
            });

            it("Testing rook on e2", [&]() {
                Bitboard rOne2Attacks =
                    engine.getSingleRookAttacks(e2, occupancies);
                expect(rOne2Attacks.getBit(e1));
                expect(rOne2Attacks.getBit(e3));
                expect(rOne2Attacks.getBit(e4));
                expect(rOne2Attacks.getBit(b2));
                expect(rOne2Attacks.getBit(c2));
                expect(rOne2Attacks.getBit(d2));
                expect(rOne2Attacks.getBit(f2));
                expect(rOne2Attacks.popCount() == 7);
            });
        });

        describe("Occupancies on: a3, b3, c3, c2, c1", [&]() {
            Bitboard occupancies_2;
            occupancies_2.setBit(a3);
            occupancies_2.setBit(b3);
            occupancies_2.setBit(c3);
            occupancies_2.setBit(c2);
            occupancies_2.setBit(c1);

            it("Testing bishop on a1", [&]() {
                Bitboard bOna1Attacks =
                    engine.getSingleBishopAttacks(a1, occupancies_2);
                expect(bOna1Attacks.getBit(b2));
                expect(bOna1Attacks.getBit(c3));
                expect(bOna1Attacks.popCount() == 2);
            });

            it("Testing bishop on h8", [&]() {
                Bitboard bOnh8Attacks =
                    engine.getSingleBishopAttacks(h8, occupancies_2);
                expect(bOnh8Attacks.getBit(g7));
                expect(bOnh8Attacks.getBit(f6));
                expect(bOnh8Attacks.getBit(e5));
                expect(bOnh8Attacks.getBit(d4));
                expect(bOnh8Attacks.getBit(c3));
                expect(bOnh8Attacks.popCount() == 5);
            });

            it("Testing rook on b2", [&]() {
                Bitboard rOnb2Attacks =
                    engine.getSingleRookAttacks(b2, occupancies_2);
                expect(rOnb2Attacks.getBit(b1));
                expect(rOnb2Attacks.getBit(a2));
                expect(rOnb2Attacks.getBit(b3));
                expect(rOnb2Attacks.getBit(c2));
                expect(rOnb2Attacks.popCount() == 4);
            });

            it("Testing rook on h2", [&]() {
                Bitboard rOnh2Attacks =
                    engine.getSingleRookAttacks(h2, occupancies_2);
                expect(rOnh2Attacks.getBit(h1));
                expect(rOnh2Attacks.getBit(h3));
                expect(rOnh2Attacks.getBit(h4));
                expect(rOnh2Attacks.getBit(h5));
                expect(rOnh2Attacks.getBit(h6));
                expect(rOnh2Attacks.getBit(h7));
                expect(rOnh2Attacks.getBit(h8));
                expect(rOnh2Attacks.getBit(g2));
                expect(rOnh2Attacks.getBit(f2));
                expect(rOnh2Attacks.getBit(e2));
                expect(rOnh2Attacks.getBit(d2));
                expect(rOnh2Attacks.getBit(c2));
                expect(rOnh2Attacks.popCount() == 12);
            });
        });
    });
}

void test_square_under_attacks() {
    describe("Testing Square under attacks", []() {
        Engine engine;
        engine.init();
        ChessBoard board;

        it("Testing Squares under attacks in 8/8/8/8/3p4/8/8/8 w KQkq - 0 0",
           [&]() {
               board.parseFEN("8/8/8/8/3p4/8/8/8 w KQkq - 0 0");

               expect(engine.isSquareUnderAttackBy(&board.status, c3, BLACK));
               expect(engine.isSquareUnderAttackBy(&board.status, e3, BLACK));
               expect(!engine.isSquareUnderAttackBy(&board.status, a1, BLACK));

               expect(!engine.isSquareUnderAttackBy(&board.status, e3, WHITE));
               expect(!engine.isSquareUnderAttackBy(&board.status, c3, WHITE));
               expect(!engine.isSquareUnderAttackBy(&board.status, f7, WHITE));
           });

        it("Testing Squares under attacks in 8/8/8/8/3P4/8/8/8 w KQkq - 0 0",
           [&]() {
               board.parseFEN("8/8/8/8/3P4/8/8/8 w KQkq - 0 0");

               expect(engine.isSquareUnderAttackBy(&board.status, e5, WHITE));
               expect(engine.isSquareUnderAttackBy(&board.status, c5, WHITE));
               expect(!engine.isSquareUnderAttackBy(&board.status, f7, WHITE));

               expect(!engine.isSquareUnderAttackBy(&board.status, c3, BLACK));
               expect(!engine.isSquareUnderAttackBy(&board.status, e3, BLACK));
               expect(!engine.isSquareUnderAttackBy(&board.status, a1, BLACK));
           });

        it("Testing Squares under attacks in 8/2p3/8/8/2P5/8/8/8 w KQkq - 0 0",
           [&]() {
               board.parseFEN("8/2p3/8/8/2P5/8/8/8 w KQkq - 0 0");

               expect(engine.isSquareUnderAttackBy(&board.status, b5, WHITE));
               expect(engine.isSquareUnderAttackBy(&board.status, d5, WHITE));
               expect(!engine.isSquareUnderAttackBy(&board.status, c5, WHITE));
               expect(!engine.isSquareUnderAttackBy(&board.status, d6, WHITE));
               expect(!engine.isSquareUnderAttackBy(&board.status, b6, WHITE));

               expect(engine.isSquareUnderAttackBy(&board.status, b6, BLACK));
               expect(engine.isSquareUnderAttackBy(&board.status, d6, BLACK));
               expect(!engine.isSquareUnderAttackBy(&board.status, c3, BLACK));
               expect(!engine.isSquareUnderAttackBy(&board.status, e3, BLACK));
               expect(!engine.isSquareUnderAttackBy(&board.status, a1, BLACK));
           });

        it("Testing Squares under attacks in 8/2p3/8/8/2P5/8/1q6/8 w KQkq - 0 "
           "0",
           [&]() {
               board.parseFEN("8/2p3/8/8/2P5/8/1q6/8 w KQkq - 0 0");

               expect(engine.isSquareUnderAttackBy(&board.status, b5, WHITE));
               expect(engine.isSquareUnderAttackBy(&board.status, d5, WHITE));
               expect(!engine.isSquareUnderAttackBy(&board.status, c5, WHITE));
               expect(!engine.isSquareUnderAttackBy(&board.status, d6, WHITE));
               expect(!engine.isSquareUnderAttackBy(&board.status, b6, WHITE));

               expect(engine.isSquareUnderAttackBy(&board.status, a1, BLACK));
               expect(engine.isSquareUnderAttackBy(&board.status, b6, BLACK));
               expect(engine.isSquareUnderAttackBy(&board.status, d6, BLACK));
               expect(engine.isSquareUnderAttackBy(&board.status, c3, BLACK));
               expect(engine.isSquareUnderAttackBy(&board.status, b8, BLACK));
               expect(engine.isSquareUnderAttackBy(&board.status, h8, BLACK));
               expect(!engine.isSquareUnderAttackBy(&board.status, e3, BLACK));
           });
    });
}

void test_move_generations() {
    describe("Testing move generations", []() {
        Engine engine;
        engine.init();
        ChessBoard board;
        std::vector<Move> moves;

        describe("Testing quite pawn move generation", [&]() {
            it("Testing initial position white to play", [&]() {
                board.setupInitialPosition();
                moves = engine.generateAllMovesAsMoveList(&board.status);
                expect(std::find(moves.begin(), moves.end(),
                                 Move{a2, a3, PAWN_PUSH}) != moves.end());
                expect(std::find(moves.begin(), moves.end(),
                                 (Move{b2, b3, PAWN_PUSH})) != moves.end());
                expect(std::find(moves.begin(), moves.end(),
                                 (Move{c2, c3, PAWN_PUSH})) != moves.end());
                expect(std::find(moves.begin(), moves.end(),
                                 (Move{d2, d3, PAWN_PUSH})) != moves.end());
                expect(std::find(moves.begin(), moves.end(),
                                 (Move{e2, e3, PAWN_PUSH})) != moves.end());
                expect(std::find(moves.begin(), moves.end(),
                                 (Move{f2, f3, PAWN_PUSH})) != moves.end());
                expect(std::find(moves.begin(), moves.end(),
                                 (Move{g2, g3, PAWN_PUSH})) != moves.end());
                expect(std::find(moves.begin(), moves.end(),
                                 (Move{h2, h3, PAWN_PUSH})) != moves.end());

                expect(std::find(moves.begin(), moves.end(),
                                 (Move{a2, a4, PAWN_DOUBLE_PUSH})) !=
                       moves.end());
                expect(std::find(moves.begin(), moves.end(),
                                 (Move{b2, b4, PAWN_DOUBLE_PUSH})) !=
                       moves.end());
                expect(std::find(moves.begin(), moves.end(),
                                 (Move{c2, c4, PAWN_DOUBLE_PUSH})) !=
                       moves.end());
                expect(std::find(moves.begin(), moves.end(),
                                 (Move{d2, d4, PAWN_DOUBLE_PUSH})) !=
                       moves.end());
                expect(std::find(moves.begin(), moves.end(),
                                 (Move{e2, e4, PAWN_DOUBLE_PUSH})) !=
                       moves.end());
                expect(std::find(moves.begin(), moves.end(),
                                 (Move{f2, f4, PAWN_DOUBLE_PUSH})) !=
                       moves.end());
                expect(std::find(moves.begin(), moves.end(),
                                 (Move{g2, g4, PAWN_DOUBLE_PUSH})) !=
                       moves.end());
                expect(std::find(moves.begin(), moves.end(),
                                 (Move{h2, h4, PAWN_DOUBLE_PUSH})) !=
                       moves.end());
            });

            it("Testing initial position after a2->a4, black to play", [&]() {
                board.parseFEN(
                    "rnbqkbnr/pppppppp/8/8/P7/8/1PPPPPPP/RNBQKBNR b KQkq e3 0 "
                    "1");
                moves = engine.generateAllMovesAsMoveList(&board.status);
                expect(std::find(moves.begin(), moves.end(),
                                 Move{a7, a6, PAWN_PUSH}) != moves.end());
                expect(std::find(moves.begin(), moves.end(),
                                 Move{b7, b6, PAWN_PUSH}) != moves.end());
                expect(std::find(moves.begin(), moves.end(),
                                 Move{c7, c6, PAWN_PUSH}) != moves.end());
                expect(std::find(moves.begin(), moves.end(),
                                 Move{d7, d6, PAWN_PUSH}) != moves.end());
                expect(std::find(moves.begin(), moves.end(),
                                 Move{e7, e6, PAWN_PUSH}) != moves.end());
                expect(std::find(moves.begin(), moves.end(),
                                 Move{f7, f6, PAWN_PUSH}) != moves.end());
                expect(std::find(moves.begin(), moves.end(),
                                 Move{g7, g6, PAWN_PUSH}) != moves.end());
                expect(std::find(moves.begin(), moves.end(),
                                 Move{h7, h6, PAWN_PUSH}) != moves.end());

                expect(std::find(moves.begin(), moves.end(),
                                 Move{a7, a5, PAWN_DOUBLE_PUSH}) !=
                       moves.end());
                expect(std::find(moves.begin(), moves.end(),
                                 Move{b7, b5, PAWN_DOUBLE_PUSH}) !=
                       moves.end());
                expect(std::find(moves.begin(), moves.end(),
                                 Move{c7, c5, PAWN_DOUBLE_PUSH}) !=
                       moves.end());
                expect(std::find(moves.begin(), moves.end(),
                                 Move{d7, d5, PAWN_DOUBLE_PUSH}) !=
                       moves.end());
                expect(std::find(moves.begin(), moves.end(),
                                 Move{e7, e5, PAWN_DOUBLE_PUSH}) !=
                       moves.end());
                expect(std::find(moves.begin(), moves.end(),
                                 Move{f7, f5, PAWN_DOUBLE_PUSH}) !=
                       moves.end());
                expect(std::find(moves.begin(), moves.end(),
                                 Move{g7, g5, PAWN_DOUBLE_PUSH}) !=
                       moves.end());
                expect(std::find(moves.begin(), moves.end(),
                                 Move{h7, h5, PAWN_DOUBLE_PUSH}) !=
                       moves.end());
            });

            it("Testing "
               "r3k2r/pPppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPpP/R3K2R b KQkq "
               "- 0 0",
               [&]() {
                   board.parseFEN(
                       "r3k2r/pPppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPpP/"
                       "R3K2R b KQkq - 0 0");
                   moves = engine.generateAllMovesAsMoveList(&board.status);
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{b4, b3, PAWN_PUSH}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{g6, g5, PAWN_PUSH}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{c7, c6, PAWN_PUSH}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{d7, d6, PAWN_PUSH}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{c7, c5, PAWN_DOUBLE_PUSH}) !=
                          moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{g2, g1, PAWN_PROMOTION_TO_BISHOP}) !=
                          moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{g2, g1, PAWN_PROMOTION_TO_ROOK}) !=
                          moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{g2, g1, PAWN_PROMOTION_TO_KNIGHT}) !=
                          moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{g2, g1, PAWN_PROMOTION_TO_QUEEN}) !=
                          moves.end());
               });

            it("Testing "
               "r3k2r/pPppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPpP/R3K2R w KQkq "
               "- 0 0",
               [&]() {
                   board.parseFEN(
                       "r3k2r/pPppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPpP/"
                       "R3K2R w KQkq - 0 0");
                   moves = engine.generateAllMovesAsMoveList(&board.status);
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{a2, a3, PAWN_PUSH}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{b2, b3, PAWN_PUSH}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{d5, d6, PAWN_PUSH}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{a2, a4, PAWN_DOUBLE_PUSH}) !=
                          moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{b7, b8, PAWN_PROMOTION_TO_BISHOP}) !=
                          moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{b7, b8, PAWN_PROMOTION_TO_ROOK}) !=
                          moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{b7, b8, PAWN_PROMOTION_TO_KNIGHT}) !=
                          moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{b7, b8, PAWN_PROMOTION_TO_QUEEN}) !=
                          moves.end());
               });
        });

        describe("Testing pawn capture move generation", [&]() {
            it("Testing initial position white to play", [&]() {
                board.setupInitialPosition();
                moves = engine.generateAllMovesAsMoveList(&board.status);
                expect(std::all_of(moves.begin(), moves.end(),
                                   [](const Move& move) {
                                       return move.type != PAWN_CAPTURE;
                                   }));
                expect(std::all_of(
                    moves.begin(), moves.end(), [](const Move& move) {
                        return move.type != PAWN_CAPTURE_PROMOTION_TO_BISHOP;
                    }));
                expect(std::all_of(
                    moves.begin(), moves.end(), [](const Move& move) {
                        return move.type != PAWN_CAPTURE_PROMOTION_TO_QUEEN;
                    }));
                expect(std::all_of(
                    moves.begin(), moves.end(), [](const Move& move) {
                        return move.type != PAWN_CAPTURE_PROMOTION_TO_KNIGHT;
                    }));
                expect(std::all_of(
                    moves.begin(), moves.end(), [](const Move& move) {
                        return move.type != PAWN_CAPTURE_PROMOTION_TO_ROOK;
                    }));
            });

            it("Testing "
               "r3k2r/pPppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPpP/R3K2R w KQkq "
               "- 0 0",
               [&]() {
                   board.parseFEN(
                       "r3k2r/pPppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPpP/"
                       "R3K2R w KQkq - 0 0");
                   moves = engine.generateAllMovesAsMoveList(&board.status);
                   expect(std::find(moves.begin(), moves.end(),
                                    (Move{d5, e6, PAWN_CAPTURE})) !=
                          moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    (Move{b7, a8,
                                          PAWN_CAPTURE_PROMOTION_TO_BISHOP})) !=
                          moves.end());
                   expect(std::find(
                              moves.begin(), moves.end(),
                              (Move{b7, a8, PAWN_CAPTURE_PROMOTION_TO_ROOK})) !=
                          moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    (Move{b7, a8,
                                          PAWN_CAPTURE_PROMOTION_TO_QUEEN})) !=
                          moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    (Move{b7, a8,
                                          PAWN_CAPTURE_PROMOTION_TO_KNIGHT})) !=
                          moves.end());
               });

            it("Testing "
               "r3k2r/pPppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPpP/R3K2R b KQkq "
               "- 0 0",
               [&]() {
                   board.parseFEN(
                       "r3k2r/pPppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPpP/"
                       "R3K2R b KQkq - 0 0");
                   moves = engine.generateAllMovesAsMoveList(&board.status);
                   expect(std::find(moves.begin(), moves.end(),
                                    (Move{b4, c3, PAWN_CAPTURE})) !=
                          moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    (Move{e6, d5, PAWN_CAPTURE})) !=
                          moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    (Move{g2, h1,
                                          PAWN_CAPTURE_PROMOTION_TO_BISHOP})) !=
                          moves.end());
                   expect(std::find(
                              moves.begin(), moves.end(),
                              (Move{g2, h1, PAWN_CAPTURE_PROMOTION_TO_ROOK})) !=
                          moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    (Move{g2, h1,
                                          PAWN_CAPTURE_PROMOTION_TO_QUEEN})) !=
                          moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    (Move{g2, h1,
                                          PAWN_CAPTURE_PROMOTION_TO_KNIGHT})) !=
                          moves.end());
               });
        });

        describe("Testing enpassant capture", [&]() {
            it("Testing initial position white to play", [&]() {
                board.setupInitialPosition();
                moves = engine.generateAllMovesAsMoveList(&board.status);
                expect(std::all_of(
                    moves.begin(), moves.end(), [](const Move& move) {
                        return move.type != PAWN_CAPTURE_ENPASSANT;
                    }));
            });

            it("Testing rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq "
               "e3 0 1",
               [&]() {
                   board.setupInitialPosition();
                   moves = engine.generateAllMovesAsMoveList(&board.status);
                   expect(std::all_of(
                       moves.begin(), moves.end(), [](const Move& move) {
                           return move.type != PAWN_CAPTURE_ENPASSANT;
                       }));
               });

            it("Testing "
               "rnbqk2r/p1pp1pbp/5n2/PpP1p1p1/4P3/8/1P1P1PPP/RNBQKBNR w KQkq "
               "b6 0 6",
               [&]() {
                   board.parseFEN(
                       "rnbqk2r/p1pp1pbp/5n2/PpP1p1p1/4P3/8/1P1P1PPP/RNBQKBNR "
                       "w KQkq b6 0 6");
                   moves = engine.generateAllMovesAsMoveList(&board.status);
                   expect(std::find(moves.begin(), moves.end(),
                                    (Move{a5, b6, PAWN_CAPTURE_ENPASSANT})) !=
                          moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    (Move{c5, b6, PAWN_CAPTURE_ENPASSANT})) !=
                          moves.end());
               });

            it("Testing "
               "rnbqkbnr/1p1p1ppp/8/4p3/pPp1P3/5NP1/P1PPQPBP/RNB1K2R b KQkq b3 "
               "0 6",
               [&]() {
                   board.parseFEN(
                       "rnbqkbnr/1p1p1ppp/8/4p3/pPp1P3/5NP1/P1PPQPBP/RNB1K2R b "
                       "KQkq b3 0 6");
                   moves = engine.generateAllMovesAsMoveList(&board.status);
                   expect(std::find(moves.begin(), moves.end(),
                                    (Move{a4, b3, PAWN_CAPTURE_ENPASSANT})) !=
                          moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    (Move{c4, b3, PAWN_CAPTURE_ENPASSANT})) !=
                          moves.end());
               });
        });

        describe("Testing castle moves", [&]() {
            it("Testing initial position white to play", [&]() {
                board.setupInitialPosition();
                moves = engine.generateAllMovesAsMoveList(&board.status);
                expect(std::all_of(moves.begin(), moves.end(),
                                   [](const Move& move) {
                                       return move.type != CASTLE_KINGSIDE;
                                   }));
                expect(std::all_of(moves.begin(), moves.end(),
                                   [](const Move& move) {
                                       return move.type != CASTLE_QUEENSIDE;
                                   }));
            });

            it("Testing 4k2r/pp3ppp/1rp5/2Ppqb2/2B1n2N/2N1Q3/P4PPP/R3K2R w KQk "
               "- 0 20",
               [&]() {
                   board.parseFEN(
                       "4k2r/pp3ppp/1rp5/2Ppqb2/2B1n2N/2N1Q3/P4PPP/R3K2R w KQk "
                       "- 0 20");
                   moves = engine.generateAllMovesAsMoveList(&board.status);
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{e1, g1, CASTLE_KINGSIDE}) !=
                          moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{e1, c1, CASTLE_QUEENSIDE}) !=
                          moves.end());
               });

            it("Testing 4k2r/pp3ppp/1rp5/2Ppqb2/2B1n2N/2N1Q3/P4PPP/R3K2R w - "
               "- 0 20",
               [&]() {
                   board.parseFEN(
                       "4k2r/pp3ppp/1rp5/2Ppqb2/2B1n2N/2N1Q3/P4PPP/R3K2R w - "
                       "- 0 20");
                   moves = engine.generateAllMovesAsMoveList(&board.status);
                   expect(std::all_of(moves.begin(), moves.end(),
                                      [](const Move& move) {
                                          return move.type != CASTLE_KINGSIDE;
                                      }));
                   expect(std::all_of(moves.begin(), moves.end(),
                                      [](const Move& move) {
                                          return move.type != CASTLE_QUEENSIDE;
                                      }));
               });

            it("Testing 4k2r/pp3ppp/1rp5/2Ppqb2/2B1n2N/2N1Q3/P4PPP/R3K2R w Kk "
               "- 0 20",
               [&]() {
                   board.parseFEN(
                       "4k2r/pp3ppp/1rp5/2Ppqb2/2B1n2N/2N1Q3/P4PPP/R3K2R w Kk "
                       "- 0 20");
                   moves = engine.generateAllMovesAsMoveList(&board.status);
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{e1, g1, CASTLE_KINGSIDE}) !=
                          moves.end());
                   expect(std::all_of(moves.begin(), moves.end(),
                                      [](const Move& move) {
                                          return move.type != CASTLE_QUEENSIDE;
                                      }));
               });

            it("Testing 4k2r/pp3ppp/1rp5/2Ppqb2/2B1n2N/2N1Q3/P4PPP/R3K1BR w Kk "
               "- 0 20",
               [&]() {
                   board.parseFEN(
                       "4k2r/pp3ppp/1rp5/2Ppqb2/2B1n2N/2N1Q3/P4PPP/R3K1BR w Kk "
                       "- 0 20");
                   moves = engine.generateAllMovesAsMoveList(&board.status);
                   expect(std::all_of(moves.begin(), moves.end(),
                                      [](const Move& move) {
                                          return move.type != CASTLE_KINGSIDE;
                                      }));
                   expect(std::all_of(moves.begin(), moves.end(),
                                      [](const Move& move) {
                                          return move.type != CASTLE_QUEENSIDE;
                                      }));
               });

            it("Testing "
               "rn1qkbnr/p1p2ppp/1p1p4/4p1BQ/2B1P1b1/2NP4/PPP2PPP/R3K1NR w "
               "KQkq - 3 7",
               [&]() {
                   board.parseFEN(
                       "4k2r/pp3ppp/1rp5/2Ppqb2/2B1n2N/2N1Q3/P4PPP/R3K1BR w Kk "
                       "- 0 20");
                   moves = engine.generateAllMovesAsMoveList(&board.status);
                   expect(std::all_of(moves.begin(), moves.end(),
                                      [](const Move& move) {
                                          return move.type != CASTLE_KINGSIDE;
                                      }));
                   expect(std::all_of(moves.begin(), moves.end(),
                                      [](const Move& move) {
                                          return move.type != CASTLE_QUEENSIDE;
                                      }));
               });

            it("Testing rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq "
               "e3 0 1",
               [&]() {
                   board.parseFEN(
                       "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq "
                       "e3 0 1");
                   moves = engine.generateAllMovesAsMoveList(&board.status);
                   expect(std::all_of(moves.begin(), moves.end(),
                                      [](const Move& move) {
                                          return move.type != CASTLE_KINGSIDE;
                                      }));
                   expect(std::all_of(moves.begin(), moves.end(),
                                      [](const Move& move) {
                                          return move.type != CASTLE_QUEENSIDE;
                                      }));
               });

            it("Testing "
               "r3k2r/pppq1ppp/2n2n2/2bppb2/2BPP3/2N1BN2/PPPQ1PPP/R3K2R b KQkq "
               "- 11 8",
               [&]() {
                   board.parseFEN(
                       "r3k2r/pppq1ppp/2n2n2/2bppb2/2BPP3/2N1BN2/PPPQ1PPP/"
                       "R3K2R b KQkq - 11 8");
                   moves = engine.generateAllMovesAsMoveList(&board.status);
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{e8, g8, CASTLE_KINGSIDE}) !=
                          moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{e8, c8, CASTLE_QUEENSIDE}) !=
                          moves.end());
               });

            it("Testing "
               "rnbqk2r/pppp1ppp/5n2/2b1p3/2B1P3/2N2N2/PPPP1PPP/R1BQK2R b KQkq "
               "- 5 4",
               [&]() {
                   board.parseFEN(
                       "rnbqk2r/pppp1ppp/5n2/2b1p3/2B1P3/2N2N2/PPPP1PPP/"
                       "R1BQK2R b KQkq - 5 4");
                   moves = engine.generateAllMovesAsMoveList(&board.status);
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{e8, g8, CASTLE_KINGSIDE}) !=
                          moves.end());
                   expect(std::all_of(moves.begin(), moves.end(),
                                      [](const Move& move) {
                                          return move.type != CASTLE_QUEENSIDE;
                                      }));
               });

            it("Testing "
               "rnbqk2r/1ppp1ppp/p4n2/4p3/2B1P3/BPN2N2/P1PP1PPP/R2QK2R b KQkq "
               "- 0 6",
               [&]() {
                   board.parseFEN(
                       "rnbqk2r/1ppp1ppp/p4n2/4p3/2B1P3/BPN2N2/P1PP1PPP/R2QK2R "
                       "b KQkq - 0 6");
                   moves = engine.generateAllMovesAsMoveList(&board.status);
                   expect(std::all_of(moves.begin(), moves.end(),
                                      [](const Move& move) {
                                          return move.type != CASTLE_KINGSIDE;
                                      }));
                   expect(std::all_of(moves.begin(), moves.end(),
                                      [](const Move& move) {
                                          return move.type != CASTLE_QUEENSIDE;
                                      }));
               });
        });

        describe("Testing knight moves generation", [&]() {
            it("Testing initial position white to play", [&]() {
                board.setupInitialPosition();
                moves = engine.generateAllMovesAsMoveList(&board.status);
                expect(std::find(moves.begin(), moves.end(),
                                 Move{g1, h3, KNIGHT_QUIET}) != moves.end());
                expect(std::find(moves.begin(), moves.end(),
                                 Move{g1, f3, KNIGHT_QUIET}) != moves.end());
                expect(std::find(moves.begin(), moves.end(),
                                 Move{b1, a3, KNIGHT_QUIET}) != moves.end());
                expect(std::find(moves.begin(), moves.end(),
                                 Move{b1, c3, KNIGHT_QUIET}) != moves.end());
            });

            it("Testing "
               "r3k2r/pppq1ppp/2n2n2/2bppb2/2BPP3/2N1BN2/PPPQ1PPP/R3K2R b KQkq "
               "- 11 8",
               [&]() {
                   board.parseFEN(
                       "r3k2r/pppq1ppp/2n2n2/2bppb2/2BPP3/2N1BN2/PPPQ1PPP/"
                       "R3K2R b KQkq - 11 8");
                   moves = engine.generateAllMovesAsMoveList(&board.status);
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{c6, b4, KNIGHT_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{c6, d4, KNIGHT_CAPTURE}) !=
                          moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{c6, a5, KNIGHT_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{c6, e7, KNIGHT_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{c6, b8, KNIGHT_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{c6, d8, KNIGHT_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{f6, e4, KNIGHT_CAPTURE}) !=
                          moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{f6, g4, KNIGHT_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{f6, h5, KNIGHT_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{f6, g8, KNIGHT_QUIET}) != moves.end());
               });

            it("Testing "
               "2kr3r/pppq1p1p/3b1np1/3ppb2/2BnP3/4BN2/PPPQNPPP/R3K2R w KQ - 0 "
               "12",
               [&]() {
                   board.parseFEN(
                       "2kr3r/pppq1p1p/3b1np1/3ppb2/2BnP3/4BN2/PPPQNPPP/R3K2R "
                       "w KQ - 0 12");
                   moves = engine.generateAllMovesAsMoveList(&board.status);
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{e2, c1, KNIGHT_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{e2, g1, KNIGHT_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{e2, c3, KNIGHT_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{e2, g3, KNIGHT_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{e2, d4, KNIGHT_CAPTURE}) !=
                          moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{e2, f4, KNIGHT_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{f3, g1, KNIGHT_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{f3, d4, KNIGHT_CAPTURE}) !=
                          moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{f3, h4, KNIGHT_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{f3, e5, KNIGHT_CAPTURE}) !=
                          moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{f3, g5, KNIGHT_QUIET}) != moves.end());
               });
        });

        describe("Testing bishop moves generation", [&]() {
            it("Testing initial position white to play", [&]() {
                board.setupInitialPosition();
                moves = engine.generateAllMovesAsMoveList(&board.status);
                expect(std::all_of(moves.begin(), moves.end(),
                                   [](const Move& move) {
                                       return move.type != BISHOP_QUIET;
                                   }));
                expect(std::all_of(moves.begin(), moves.end(),
                                   [](const Move& move) {
                                       return move.type != BISHOP_CAPTURE;
                                   }));
            });

            it("Testing "
               "2kr3r/pppq1p1p/3b1np1/3ppb2/2BnP3/4BN2/PPPQNPPP/R3K2R w KQ - 0 "
               "12",
               [&]() {
                   board.parseFEN(
                       "2kr3r/pppq1p1p/3b1np1/3ppb2/2BnP3/4BN2/PPPQNPPP/R3K2R "
                       "w KQ - 0 12");
                   moves = engine.generateAllMovesAsMoveList(&board.status);
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{e3, d4, BISHOP_CAPTURE}) !=
                          moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{e3, f4, BISHOP_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{e3, g5, BISHOP_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{e3, h6, BISHOP_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{c4, b3, BISHOP_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{c4, d3, BISHOP_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{c4, b5, BISHOP_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{c4, d5, BISHOP_CAPTURE}) !=
                          moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{c4, a6, BISHOP_QUIET}) != moves.end());
               });

            it("Testing 2kr3r/pppq1p1p/3b1np1/3ppb2/1QBnP3/4BN2/PPP1NPPP/R3K2R "
               "b KQ - "
               "1 12",
               [&]() {
                   board.parseFEN(
                       "2kr3r/pppq1p1p/3b1np1/3ppb2/1QBnP3/4BN2/PPP1NPPP/R3K2R "
                       "b KQ - 1 12");
                   moves = engine.generateAllMovesAsMoveList(&board.status);
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{f5, h3, BISHOP_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{f5, e4, BISHOP_CAPTURE}) !=
                          moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{f5, g4, BISHOP_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{f5, e6, BISHOP_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{d6, b4, BISHOP_CAPTURE}) !=
                          moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{d6, c5, BISHOP_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{d6, e7, BISHOP_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{d6, f8, BISHOP_QUIET}) != moves.end());
               });
        });

        describe("Testing rook moves generation", [&]() {
            it("Testing initial position white to play", [&]() {
                board.setupInitialPosition();
                moves = engine.generateAllMovesAsMoveList(&board.status);
                expect(std::all_of(
                    moves.begin(), moves.end(),
                    [](const Move& move) { return move.type != ROOK_QUIET; }));
                expect(std::all_of(moves.begin(), moves.end(),
                                   [](const Move& move) {
                                       return move.type != ROOK_CAPTURE;
                                   }));
            });

            it("Testing 2kr3r/pppq1p2/3b1npB/3ppb2/1QBnP3/5N2/PPP1NPPP/R3K2R b "
               "KQ - 0 13",
               [&]() {
                   board.parseFEN(
                       "2kr3r/pppq1p2/3b1npB/3ppb2/1QBnP3/5N2/PPP1NPPP/R3K2R b "
                       "KQ - 0 13");
                   moves = engine.generateAllMovesAsMoveList(&board.status);
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{d8, e8, ROOK_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{d8, f8, ROOK_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{d8, g8, ROOK_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{h8, h6, ROOK_CAPTURE}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{h8, h7, ROOK_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{h8, e8, ROOK_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{h8, f8, ROOK_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{h8, g8, ROOK_QUIET}) != moves.end());
               });

            it("Testing "
               "2kr3r/ppp2p2/3b1npB/1q1pp3/1QB1P1P1/1n3N2/PPP1NPbP/3RK1R1 w - "
               "- 3 17",
               [&]() {
                   board.parseFEN(
                       "2kr3r/ppp2p2/3b1npB/1q1pp3/1QB1P1P1/1n3N2/PPP1NPbP/"
                       "3RK1R1 w - - 3 17");
                   moves = engine.generateAllMovesAsMoveList(&board.status);
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{d1, a1, ROOK_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{d1, b1, ROOK_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{d1, c1, ROOK_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{d1, d2, ROOK_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{d1, d3, ROOK_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{d1, d4, ROOK_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{d1, d5, ROOK_CAPTURE}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{g1, f1, ROOK_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{g1, h1, ROOK_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{g1, g2, ROOK_CAPTURE}) != moves.end());
               });
        });

        describe("Testing queen moves generation", [&]() {
            it("Testing initial position white to play", [&]() {
                board.setupInitialPosition();
                moves = engine.generateAllMovesAsMoveList(&board.status);
                expect(std::all_of(
                    moves.begin(), moves.end(),
                    [](const Move& move) { return move.type != QUEEN_QUIET; }));
                expect(std::all_of(moves.begin(), moves.end(),
                                   [](const Move& move) {
                                       return move.type != QUEEN_CAPTURE;
                                   }));
            });

            it("Testing "
               "2kr3r/ppp2p2/3b1npB/1q1pp3/1QB1P1P1/1n3N2/PPP1NPbP/3RK1R1 w - "
               "- 3 17",
               [&]() {
                   board.parseFEN(
                       "2kr3r/ppp2p2/3b1npB/1q1pp3/1QB1P1P1/1n3N2/PPP1NPbP/"
                       "3RK1R1 w - - 3 17");
                   moves = engine.generateAllMovesAsMoveList(&board.status);
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{b4, d2, QUEEN_QUIET}) != moves.end());

                   expect(std::find(moves.begin(), moves.end(),
                                    Move{b4, a3, QUEEN_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{b4, b3, QUEEN_CAPTURE}) !=
                          moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{b4, c3, QUEEN_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{b4, a4, QUEEN_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{b4, a5, QUEEN_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{b4, b5, QUEEN_CAPTURE}) !=
                          moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{b4, c5, QUEEN_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{b4, d6, QUEEN_CAPTURE}) !=
                          moves.end());
               });

            it("Testing "
               "2kr3r/ppp2p2/3b1npB/1q1pp3/2B1P1P1/1Q3N2/PPP1NPbP/3RK1R1 b - - "
               "0 17",
               [&]() {
                   board.parseFEN(
                       "2kr3r/ppp2p2/3b1npB/1q1pp3/2B1P1P1/1Q3N2/PPP1NPbP/"
                       "3RK1R1 b - - 0 17");
                   moves = engine.generateAllMovesAsMoveList(&board.status);
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{b5, b3, QUEEN_CAPTURE}) !=
                          moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{b5, a4, QUEEN_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{b5, b4, QUEEN_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{b5, c4, QUEEN_CAPTURE}) !=
                          moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{b5, a5, QUEEN_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{b5, c5, QUEEN_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{b5, a6, QUEEN_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{b5, b6, QUEEN_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{b5, c6, QUEEN_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{b5, d7, QUEEN_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{b5, e8, QUEEN_QUIET}) != moves.end());
               });
        });

        describe("Testing king moves generation", [&]() {
            it("Testing initial position white to play", [&]() {
                board.setupInitialPosition();
                moves = engine.generateAllMovesAsMoveList(&board.status);
                expect(std::all_of(
                    moves.begin(), moves.end(),
                    [](const Move& move) { return move.type != KING_QUIET; }));
                expect(std::all_of(moves.begin(), moves.end(),
                                   [](const Move& move) {
                                       return move.type != KING_CAPTURE;
                                   }));
            });

            it("Testing "
               "2kr3r/ppp2p2/3b1npB/1q1pp3/2B1P1P1/1Q3N2/PPP1NP1P/3RKbR1 w - - "
               "1 18",
               [&]() {
                   board.parseFEN(
                       "2kr3r/ppp2p2/3b1npB/1q1pp3/2B1P1P1/1Q3N2/PPP1NP1P/"
                       "3RKbR1 w - - 1 18");
                   moves = engine.generateAllMovesAsMoveList(&board.status);
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{e1, f1, KING_CAPTURE}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{e1, d2, KING_QUIET}) != moves.end());
               });

            it("Testing 2kr3r/pQp2p2/5npB/3pp3/2B1P1P1/2b2N2/PPP1NP1P/3R1KR1 b "
               "- - 0 20",
               [&]() {
                   board.parseFEN(
                       "2kr3r/pQp2p2/5npB/3pp3/2B1P1P1/2b2N2/PPP1NP1P/3R1KR1 b "
                       "- - 0 20");
                   moves = engine.generateAllMovesAsMoveList(&board.status);
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{c8, b7, KING_CAPTURE}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{c8, d7, KING_QUIET}) != moves.end());
                   expect(std::find(moves.begin(), moves.end(),
                                    Move{c8, b8, KING_QUIET}) != moves.end());
               });
        });
    });
}

void test_make_move() {
    Engine engine;
    engine.init();
    ChessBoard board;

    describe("Testing make move function", [&]() {
        it("Testing initial position white to play", [&]() {
            board.setupInitialPosition();
            Move move{a2, a4, PAWN_DOUBLE_PUSH};
            bool hasMoved = engine.makeMove(&board, move);
            expect(hasMoved);
            expect(board.getPieceAt(a2) == '.');
            expect(board.getPieceAt(a4) == 'P');
        });

        it("Testing illegal pawn push", [&]() {
            board.parseFEN(
                "rnbqkbnr/pppp1ppp/8/4p2Q/4P3/8/PPPP1PPP/RNB1KBNR b KQkq - 1 "
                "2");
            Move move{f7, f6, PAWN_PUSH};
            bool hasMoved = engine.makeMove(&board, move);
            expect(!hasMoved);
            expect(board.getPieceAt(h5) == 'Q');  // White queen pins the pawn
            expect(board.getPieceAt(f7) == 'p');
            expect(board.getPieceAt(f6) == '.');

            // restore the previous status
            expect(board.status.side == BLACK);
            expect(board.status.fullmoveNumber == 1);
        });

        it("Testing kings under checks (only move that moves the king out of "
           "checks)",
           [&]() {
               board.parseFEN(
                   "r1b2rk1/pppp1pbp/2n3p1/4p1q1/2B1Q3/3P4/PPPK1PPP/RN4NR w - "
                   "- 0 9");

               Move move1{a2, a3, PAWN_PUSH};
               bool hasMoved1 = engine.makeMove(&board, move1);
               expect(!hasMoved1);

               Move move2{a2, a4, PAWN_DOUBLE_PUSH};
               bool hasMoved2 = engine.makeMove(&board, move2);
               expect(!hasMoved2);

               Move move3{f2, f4, PAWN_DOUBLE_PUSH};
               bool hasMoved3 = engine.makeMove(&board, move3);
               expect(hasMoved3);  // Moves the king out of check
           });
    });
}

void run_engine_tests() {
    describe("Testing engine", []() {
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
        test_make_move();
    });
}
