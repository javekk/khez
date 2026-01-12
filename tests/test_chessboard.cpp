#include <iostream>

#include "../src/chessboard/chessboard.h"
#include "../src/lib/square.h"
#include "test_lib.h"

void run_chessboard_tests() {
    describe("Testing chessboard", []() {
        it("Testing board initialization", []() {
            ChessBoard board;
            bool has_pieces = false;
            for (int square = 0; square < 64; square++) {
                char c = board.getPieceAt(static_cast<Square>(square));
                if (c >= 'A' && c <= 'Z') {
                    has_pieces = true;
                    break;
                }
                if (c >= 'a' && c <= 'z') {
                    has_pieces = true;
                    break;
                }
            }

            expect(!has_pieces);
        });

        it("Testing toString() returning the board", []() {
            ChessBoard board;

            std::string board_str = board.toString();
            expect(!board_str.empty());
            expect(board_str.length() > 50);  // Should be a reasonable size
        });

        describe("Testing initial position setup", []() {
            ChessBoard board;
            board.setupInitialPosition();

            it("Testing white pieces on rank 1", [board]() {
                expect(board.getPieceAt(a1) == 'R');
                expect(board.getPieceAt(b1) == 'N');
                expect(board.getPieceAt(c1) == 'B');
                expect(board.getPieceAt(d1) == 'Q');
                expect(board.getPieceAt(e1) == 'K');
                expect(board.getPieceAt(f1) == 'B');
                expect(board.getPieceAt(g1) == 'N');
                expect(board.getPieceAt(h1) == 'R');
            });

            it("Testing white pieces on rank 2", [board]() {
                expect(board.getPieceAt(a2) == 'P');
                expect(board.getPieceAt(h2) == 'P');
            });
            it("Testing black pieces on rank 8", [board]() {
                expect(board.getPieceAt(a8) == 'r');
                expect(board.getPieceAt(e8) == 'k');
            });
            it("Testing black pieces on rank 7", [board]() {
                expect(board.getPieceAt(a7) == 'p');
                expect(board.getPieceAt(h7) == 'p');
            });
            it("Testing empty squares", [board]() {
                expect(board.getPieceAt(e4) == '.');
                expect(board.getPieceAt(d5) == '.');
            });
        });

        describe("Testing set piece at function", []() {
            ChessBoard board;
            it("Testing e4", [&board]() {
                expect(board.getPieceAt(e4) == '.');
                board.setPieceAt(e4, PAWN, WHITE);
                expect(board.getPieceAt(e4) == 'P');
                board.clearPieceAt(e4);
                board.setPieceAt(e4, QUEEN, BLACK);
                expect(board.getPieceAt(e4) == 'q');
                board.clearPieceAt(e4);
                expect(board.getPieceAt(e4) == '.');
            });

            it("Testing a1", [&board]() {
                expect(board.getPieceAt(a1) == '.');
                board.setPieceAt(a1, ROOK, WHITE);
                expect(board.getPieceAt(a1) == 'R');
                board.clearPieceAt(a1);
                board.setPieceAt(a1, KNIGHT, BLACK);
                expect(board.getPieceAt(a1) == 'n');
                board.clearPieceAt(a1);
                expect(board.getPieceAt(a1) == '.');
            });
        });

        describe("Testing parseFEN", []() {
            ChessBoard board;

            describe(
                "Testing "
                "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w "
                "KQkq - 0 1 (Initial position)",
                [&board]() {
                    board.parseFEN(
                        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - "
                        "0 1");

                    it("Testing white pieces on rank 1", [&board]() {
                        expect(board.getPieceAt(a1) == 'R');
                        expect(board.getPieceAt(b1) == 'N');
                        expect(board.getPieceAt(c1) == 'B');
                        expect(board.getPieceAt(d1) == 'Q');
                        expect(board.getPieceAt(e1) == 'K');
                        expect(board.getPieceAt(f1) == 'B');
                        expect(board.getPieceAt(g1) == 'N');
                        expect(board.getPieceAt(h1) == 'R');
                    });
                    it("Testing white pieces on rank 2", [&board]() {
                        expect(board.getPieceAt(a2) == 'P');
                        expect(board.getPieceAt(h2) == 'P');
                    });
                    it("Testing white pieces on rank 8", [&board]() {
                        expect(board.getPieceAt(a8) == 'r');
                        expect(board.getPieceAt(e8) == 'k');
                    });
                    it("Testing white pieces on rank 7", [&board]() {
                        expect(board.getPieceAt(a7) == 'p');
                        expect(board.getPieceAt(h7) == 'p');
                    });
                    it("Testing empty squares", [&board]() {
                        expect(board.getPieceAt(e4) == '.');
                        expect(board.getPieceAt(d5) == '.');
                        expect(board.getPieceAt(c5) == '.');
                    });
                    it("Testing extra info", [&board]() {
                        expect(board.status.side == WHITE);
                        expect(!board.status.enpassant.has_value());
                        expect(board.status.availableCastle == 0b1111);
                        expect(board.status.halfmoveCounter == 0);
                        expect(board.status.fullmoveNumber == 1);
                    });
                });

            describe(
                "Testing FEN; "
                "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b "
                "KQkq - 1 2 (Init pos after a couple of moves)",
                [&board]() {
                    board.parseFEN(
                        "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b "
                        "KQkq "
                        "- 1 2");

                    it("Testing white pieces on rank 1", [&board]() {
                        expect(board.getPieceAt(a1) == 'R');
                        expect(board.getPieceAt(b1) == 'N');
                        expect(board.getPieceAt(c1) == 'B');
                        expect(board.getPieceAt(d1) == 'Q');
                        expect(board.getPieceAt(e1) == 'K');
                        expect(board.getPieceAt(f1) == 'B');
                        expect(board.getPieceAt(g1) == '.');
                        expect(board.getPieceAt(h1) == 'R');
                    });
                    it("Testing white pieces on rank 2", [&board]() {
                        expect(board.getPieceAt(a2) == 'P');
                        expect(board.getPieceAt(h2) == 'P');
                        expect(board.getPieceAt(e2) == '.');
                    });
                    it("Testing white pieces on rank 3", [&board]() {
                        expect(board.getPieceAt(f3) == 'N');
                        expect(board.getPieceAt(h3) == '.');
                        expect(board.getPieceAt(e3) == '.');
                    });
                    it("Testing white pieces on rank 8", [&board]() {
                        expect(board.getPieceAt(a8) == 'r');
                        expect(board.getPieceAt(e8) == 'k');
                    });
                    it("Testing white pieces on rank 7", [&board]() {
                        expect(board.getPieceAt(a7) == 'p');
                        expect(board.getPieceAt(h7) == 'p');
                        expect(board.getPieceAt(c7) == '.');
                    });
                    it("Testing white pieces on rank 5", [&board]() {
                        expect(board.getPieceAt(a5) == '.');
                        expect(board.getPieceAt(h5) == '.');
                        expect(board.getPieceAt(c5) == 'p');
                    });
                    it("Testing empty squares", [&board]() {
                        expect(board.getPieceAt(b4) == '.');
                        expect(board.getPieceAt(d5) == '.');
                        expect(board.getPieceAt(g5) == '.');
                    });
                    it("Testing extra info", [&board]() {
                        expect(board.status.side == BLACK);
                        expect(!board.status.enpassant.has_value());
                        expect(board.status.availableCastle == 0b1111);
                        expect(board.status.halfmoveCounter == 1);
                        expect(board.status.fullmoveNumber == 2);
                    });
                });
        });
    });
}