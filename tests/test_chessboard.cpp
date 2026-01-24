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

        describe("Testing makeMove and undoLastMove", []() {
            it("Testing simple pawn move e2-e4 from initial position", []() {
                ChessBoard board;
                board.setupInitialPosition();

                Move move(e2, e4, PAWN_DOUBLE_PUSH);

                board.makeMove(move);

                expect(board.getPieceAt(e2) == '.');
                expect(board.getPieceAt(e4) == 'P');
                expect(board.status.side == BLACK);
                expect(board.status.enpassant.has_value());
                expect(board.status.enpassant.value() == e3);

                expect(board.moveHistory.size() == 1);
                expect(board.statusHistory.size() == 1);

                board.undoLastMove();

                expect(board.getPieceAt(e2) == 'P');
                expect(board.getPieceAt(e4) == '.');
                expect(board.status.side == WHITE);
                expect(!board.status.enpassant.has_value());
                expect(board.moveHistory.size() == 0);
                expect(board.statusHistory.size() == 0);
            });

            it("Testing knight move Ng1-f3 from initial position", []() {
                ChessBoard board;
                board.setupInitialPosition();

                Move move(g1, f3, KNIGHT_QUIET);

                board.makeMove(move);

                expect(board.getPieceAt(g1) == '.');
                expect(board.getPieceAt(f3) == 'N');
                expect(board.status.side == BLACK);
                expect(board.moveHistory.size() == 1);
                expect(!board.status.enpassant.has_value());

                board.undoLastMove();

                expect(board.getPieceAt(g1) == 'N');
                expect(board.getPieceAt(f3) == '.');
                expect(board.status.side == WHITE);
                expect(board.moveHistory.size() == 0);
                expect(board.statusHistory.size() == 0);
                expect(!board.status.enpassant.has_value());
            });

            it("Testing pawn capture e4xd5", []() {
                ChessBoard board;
                board.parseFEN(
                    "rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - "
                    "0 2");

                Move move(e4, d5, PAWN_CAPTURE);

                board.makeMove(move);

                expect(board.getPieceAt(e4) == '.');
                expect(board.getPieceAt(d5) == 'P');
                expect(board.status.side == BLACK);

                board.undoLastMove();

                expect(board.getPieceAt(e4) == 'P');
                expect(board.getPieceAt(d5) == 'p');
                expect(board.status.side == WHITE);
            });

            it("Testing en passant capture", []() {
                ChessBoard board;
                board.parseFEN(
                    "rnbqkbnr/ppp1p1pp/8/3pPp2/8/8/PPPP1PPP/RNBQKBNR w KQkq f6 "
                    "0 3");

                Move move(e5, f6, PAWN_CAPTURE_ENPASSANT);

                board.makeMove(move);

                expect(board.getPieceAt(e5) == '.');
                expect(board.getPieceAt(f6) == 'P');
                expect(board.getPieceAt(f5) == '.');
                expect(board.status.side == BLACK);
                expect(!board.status.enpassant.has_value());

                board.undoLastMove();

                expect(board.getPieceAt(e5) == 'P');
                expect(board.getPieceAt(f6) == '.');
                expect(board.getPieceAt(f5) == 'p');
                expect(board.status.enpassant.has_value());
                expect(board.status.enpassant.value() == f6);
            });

            it("Testing white kingside castling", []() {
                ChessBoard board;
                board.parseFEN(
                    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQK2R w KQkq - 0 1");

                Move move(e1, g1, CASTLE_KINGSIDE);

                board.makeMove(move);

                expect(board.getPieceAt(e1) == '.');
                expect(board.getPieceAt(f1) == 'R');
                expect(board.getPieceAt(g1) == 'K');
                expect(board.getPieceAt(h1) == '.');
                expect((board.status.availableCastle & WHITE_KINGSIDE) == 0);
                expect((board.status.availableCastle & WHITE_QUEENSIDE) == 0);

                board.undoLastMove();

                expect(board.getPieceAt(e1) == 'K');
                expect(board.getPieceAt(f1) == '.');
                expect(board.getPieceAt(g1) == '.');
                expect(board.getPieceAt(h1) == 'R');
                expect((board.status.availableCastle & WHITE_KINGSIDE) != 0);
            });

            it("Testing white queenside castling", []() {
                ChessBoard board;
                board.parseFEN(
                    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/R3KBNR w KQkq - 0 1");

                Move move(e1, c1, CASTLE_QUEENSIDE);

                board.makeMove(move);

                expect(board.getPieceAt(e1) == '.');
                expect(board.getPieceAt(d1) == 'R');
                expect(board.getPieceAt(c1) == 'K');
                expect(board.getPieceAt(b1) == '.');
                expect(board.getPieceAt(a1) == '.');
                expect((board.status.availableCastle & WHITE_KINGSIDE) == 0);
                expect((board.status.availableCastle & WHITE_QUEENSIDE) == 0);

                board.undoLastMove();

                expect(board.getPieceAt(e1) == 'K');
                expect(board.getPieceAt(d1) == '.');
                expect(board.getPieceAt(c1) == '.');
                expect(board.getPieceAt(b1) == '.');
                expect(board.getPieceAt(a1) == 'R');
                expect((board.status.availableCastle & WHITE_QUEENSIDE) != 0);
            });

            it("Testing black kingside castling", []() {
                ChessBoard board;
                board.parseFEN(
                    "rnbqk2r/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1");

                Move move(e8, g8, CASTLE_KINGSIDE);

                board.makeMove(move);

                expect(board.getPieceAt(e8) == '.');
                expect(board.getPieceAt(f8) == 'r');
                expect(board.getPieceAt(g8) == 'k');
                expect(board.getPieceAt(h8) == '.');
                expect((board.status.availableCastle & BLACK_KINGSIDE) == 0);
                expect((board.status.availableCastle & BLACK_QUEENSIDE) == 0);

                board.undoLastMove();

                expect(board.getPieceAt(e8) == 'k');
                expect(board.getPieceAt(f8) == '.');
                expect(board.getPieceAt(g8) == '.');
                expect(board.getPieceAt(h8) == 'r');
                expect((board.status.availableCastle & BLACK_KINGSIDE) != 0);
            });

            it("Testing black queenside castling", []() {
                ChessBoard board;
                board.parseFEN(
                    "r3kbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1");

                Move move(e8, c8, CASTLE_QUEENSIDE);

                board.makeMove(move);

                expect(board.getPieceAt(e8) == '.');
                expect(board.getPieceAt(d8) == 'r');
                expect(board.getPieceAt(c8) == 'k');
                expect(board.getPieceAt(b8) == '.');
                expect(board.getPieceAt(a8) == '.');
                expect((board.status.availableCastle & BLACK_KINGSIDE) == 0);
                expect((board.status.availableCastle & BLACK_QUEENSIDE) == 0);

                board.undoLastMove();

                expect(board.getPieceAt(e8) == 'k');
                expect(board.getPieceAt(d8) == '.');
                expect(board.getPieceAt(c8) == '.');
                expect(board.getPieceAt(b8) == '.');
                expect(board.getPieceAt(a8) == 'r');
                expect((board.status.availableCastle & BLACK_QUEENSIDE) != 0);
            });

            it("Testing pawn promotion to queen", []() {
                ChessBoard board;
                board.parseFEN("4k3/P7/8/8/8/8/8/4K3 w - - 0 1");

                Move move(a7, a8, PAWN_PROMOTION_TO_QUEEN);

                board.makeMove(move);

                expect(board.getPieceAt(a7) == '.');
                expect(board.getPieceAt(a8) == 'Q');
                expect(board.status.side == BLACK);

                board.undoLastMove();

                expect(board.getPieceAt(a7) == 'P');
                expect(board.getPieceAt(a8) == '.');
                expect(board.status.side == WHITE);
            });

            it("Testing pawn capture with promotion to knight", []() {
                ChessBoard board;
                board.parseFEN("1n2k3/P7/8/8/8/8/8/4K3 w - - 0 1");

                Move move(a7, b8, PAWN_CAPTURE_PROMOTION_TO_KNIGHT);

                board.makeMove(move);

                expect(board.getPieceAt(a7) == '.');
                expect(board.getPieceAt(b8) == 'N');
                expect(board.status.side == BLACK);

                board.undoLastMove();

                expect(board.getPieceAt(a7) == 'P');
                expect(board.getPieceAt(b8) == 'n');
                expect(board.status.side == WHITE);
            });

            it("Testing rook move loses castling rights", []() {
                ChessBoard board;
                board.parseFEN(
                    "r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R w KQkq - 0 1");

                Move move(a1, a3, ROOK_QUIET);

                board.makeMove(move);

                expect(board.getPieceAt(a1) == '.');
                expect(board.getPieceAt(a3) == 'R');
                expect((board.status.availableCastle & WHITE_QUEENSIDE) == 0);
                expect((board.status.availableCastle & WHITE_KINGSIDE) != 0);

                board.undoLastMove();

                expect(board.getPieceAt(a1) == 'R');
                expect(board.getPieceAt(a3) == '.');
                expect((board.status.availableCastle & WHITE_QUEENSIDE) != 0);
            });

            it("Testing king move loses all castling rights", []() {
                ChessBoard board;
                board.parseFEN(
                    "r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R w KQkq - 0 1");

                Move move(e1, f1, KING_QUIET);

                board.makeMove(move);

                expect(board.getPieceAt(e1) == '.');
                expect(board.getPieceAt(f1) == 'K');
                expect((board.status.availableCastle & WHITE_QUEENSIDE) == 0);
                expect((board.status.availableCastle & WHITE_KINGSIDE) == 0);
                expect((board.status.availableCastle & BLACK_QUEENSIDE) != 0);

                board.undoLastMove();

                expect(board.getPieceAt(e1) == 'K');
                expect(board.getPieceAt(f1) == '.');
                expect((board.status.availableCastle & WHITE_QUEENSIDE) != 0);
                expect((board.status.availableCastle & WHITE_KINGSIDE) != 0);
            });

            it("Testing multiple moves and undo", []() {
                ChessBoard board;
                board.setupInitialPosition();

                Move move1(e2, e4, PAWN_DOUBLE_PUSH);
                Move move2(e7, e5, PAWN_DOUBLE_PUSH);
                Move move3(g1, f3, KNIGHT_QUIET);

                board.makeMove(move1);
                board.makeMove(move2);
                board.makeMove(move3);

                expect(board.getPieceAt(f3) == 'N');
                expect(board.getPieceAt(e4) == 'P');
                expect(board.getPieceAt(e5) == 'p');
                expect(board.moveHistory.size() == 3);
                expect(board.status.side == BLACK);

                board.undoLastMove();
                expect(board.moveHistory.size() == 2);
                expect(board.getPieceAt(f3) == '.');
                expect(board.getPieceAt(g1) == 'N');
                expect(board.status.side == WHITE);

                board.undoLastMove();
                expect(board.moveHistory.size() == 1);
                expect(board.getPieceAt(e5) == '.');
                expect(board.getPieceAt(e7) == 'p');
                expect(board.status.side == BLACK);

                board.undoLastMove();
                expect(board.getPieceAt(e4) == '.');
                expect(board.getPieceAt(e2) == 'P');
                expect(board.status.side == WHITE);
                expect(board.moveHistory.size() == 0);
            });

            it("Testing bishop capture", []() {
                ChessBoard board;
                board.parseFEN(
                    "rnbqkbnr/pppp1ppp/8/4p3/2B1P3/8/PPPP1PPP/RNBQK1NR w KQkq "
                    "- 0 2");

                Move move(c4, e6, BISHOP_CAPTURE);

                board.makeMove(move);

                expect(board.getPieceAt(c4) == '.');
                expect(board.getPieceAt(e6) == 'B');
                expect(board.status.side == BLACK);

                board.undoLastMove();

                expect(board.getPieceAt(c4) == 'B');
                expect(board.getPieceAt(e6) == '.');
                expect(board.status.side == WHITE);
            });

            it("Testing queen capture", []() {
                ChessBoard board;
                board.parseFEN(
                    "rnb1kbnr/pppp1ppp/8/4p3/4P1q1/8/PPPPQPPP/RNB1KBNR w KQkq "
                    "- 0 3");

                Move move(e2, g4, QUEEN_CAPTURE);

                board.makeMove(move);

                expect(board.getPieceAt(e2) == '.');
                expect(board.getPieceAt(g4) == 'Q');
                expect(board.status.side == BLACK);

                board.undoLastMove();

                expect(board.getPieceAt(e2) == 'Q');
                expect(board.getPieceAt(g4) == 'q');
                expect(board.status.side == WHITE);
            });

            it("Testing enpassant flag cleared after normal move", []() {
                ChessBoard board;
                board.parseFEN(
                    "rnbqkbnr/ppp1p1pp/8/3pPp2/8/8/PPPP1PPP/RNBQKBNR w KQkq f6 "
                    "0 3");

                Move move(g1, f3, KNIGHT_QUIET);

                board.makeMove(move);

                expect(board.getPieceAt(f3) == 'N');
                expect(!board.status.enpassant.has_value());

                board.undoLastMove();

                expect(board.getPieceAt(f3) == '.');
                expect(board.status.enpassant.has_value());
                expect(board.status.enpassant.value() == f6);
            });

            it("Testing rook capture on h8 loses black kingside castling",
               []() {
                   ChessBoard board;
                   board.parseFEN(
                       "rnbqk2r/ppppppp1/7p/8/8/7P/PPPPPPP1/RNBQK2R w KQkq - 0 "
                       "2");

                   Move move(h1, h8, ROOK_CAPTURE);

                   board.makeMove(move);

                   expect(board.getPieceAt(h1) == '.');
                   expect(board.getPieceAt(h8) == 'R');
                   expect((board.status.availableCastle & WHITE_KINGSIDE) == 0);

                   board.undoLastMove();

                   expect(board.getPieceAt(h1) == 'R');
                   expect(board.getPieceAt(h8) == 'r');
                   expect((board.status.availableCastle & WHITE_KINGSIDE) != 0);
               });

            it("Testing double pawn push sets correct enpassant square for "
               "white",
               []() {
                   ChessBoard board;
                   board.setupInitialPosition();

                   Move move(d2, d4, PAWN_DOUBLE_PUSH);

                   board.makeMove(move);

                   expect(board.getPieceAt(d4) == 'P');
                   expect(board.status.enpassant.has_value());
                   expect(board.status.enpassant.value() == d3);

                   board.undoLastMove();

                   expect(board.getPieceAt(d2) == 'P');
                   expect(!board.status.enpassant.has_value());
               });

            it("Testing double pawn push sets correct enpassant square for "
               "black",
               []() {
                   ChessBoard board;
                   board.parseFEN(
                       "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - "
                       "0 1");

                   Move move(c7, c5, PAWN_DOUBLE_PUSH);

                   board.makeMove(move);

                   expect(board.getPieceAt(c5) == 'p');
                   expect(board.status.enpassant.has_value());
                   expect(board.status.enpassant.value() == c6);

                   board.undoLastMove();

                   expect(board.getPieceAt(c7) == 'p');
                   expect(!board.status.enpassant.has_value());
               });

            it("Testing promotion to rook", []() {
                ChessBoard board;
                board.parseFEN("4k3/P7/8/8/8/8/8/4K3 w - - 0 1");

                Move move(a7, a8, PAWN_PROMOTION_TO_ROOK);

                board.makeMove(move);

                expect(board.getPieceAt(a7) == '.');
                expect(board.getPieceAt(a8) == 'R');

                board.undoLastMove();

                expect(board.getPieceAt(a7) == 'P');
                expect(board.getPieceAt(a8) == '.');
            });

            it("Testing promotion to bishop", []() {
                ChessBoard board;
                board.parseFEN("4k3/P7/8/8/8/8/8/4K3 w - - 0 1");

                Move move(a7, a8, PAWN_PROMOTION_TO_BISHOP);

                board.makeMove(move);

                expect(board.getPieceAt(a7) == '.');
                expect(board.getPieceAt(a8) == 'B');

                board.undoLastMove();

                expect(board.getPieceAt(a7) == 'P');
                expect(board.getPieceAt(a8) == '.');
            });

            it("Testing black pawn promotion to queen", []() {
                ChessBoard board;
                board.parseFEN("4k3/8/8/8/8/8/p7/4K3 b - - 0 1");

                Move move(a2, a1, PAWN_PROMOTION_TO_QUEEN);

                board.makeMove(move);

                expect(board.getPieceAt(a2) == '.');
                expect(board.getPieceAt(a1) == 'q');

                board.undoLastMove();

                expect(board.getPieceAt(a2) == 'p');
                expect(board.getPieceAt(a1) == '.');
            });

            it("Testing capture promotion to queen", []() {
                ChessBoard board;
                board.parseFEN("1r2k3/P7/8/8/8/8/8/4K3 w - - 0 1");

                Move move(a7, b8, PAWN_CAPTURE_PROMOTION_TO_QUEEN);

                board.makeMove(move);

                expect(board.getPieceAt(a7) == '.');
                expect(board.getPieceAt(b8) == 'Q');

                board.undoLastMove();

                expect(board.getPieceAt(a7) == 'P');
                expect(board.getPieceAt(b8) == 'r');
            });

            it("Testing capture promotion to rook", []() {
                ChessBoard board;
                board.parseFEN("1n2k3/P7/8/8/8/8/8/4K3 w - - 0 1");

                Move move(a7, b8, PAWN_CAPTURE_PROMOTION_TO_ROOK);

                board.makeMove(move);

                expect(board.getPieceAt(a7) == '.');
                expect(board.getPieceAt(b8) == 'R');

                board.undoLastMove();

                expect(board.getPieceAt(a7) == 'P');
                expect(board.getPieceAt(b8) == 'n');
            });

            it("Testing capture promotion to bishop", []() {
                ChessBoard board;
                board.parseFEN("1q2k3/P7/8/8/8/8/8/4K3 w - - 0 1");

                Move move(a7, b8, PAWN_CAPTURE_PROMOTION_TO_BISHOP);

                board.makeMove(move);

                expect(board.getPieceAt(a7) == '.');
                expect(board.getPieceAt(b8) == 'B');

                board.undoLastMove();

                expect(board.getPieceAt(a7) == 'P');
                expect(board.getPieceAt(b8) == 'q');
            });

            it("Testing halfmove counter resets on pawn move", []() {
                ChessBoard board;
                board.parseFEN(
                    "rnbqkbnr/pppppppp/8/8/8/5N2/PPPPPPPP/RNBQKB1R w KQkq - 3 "
                    "2");

                Move move(e2, e4, PAWN_DOUBLE_PUSH);

                board.makeMove(move);

                expect(board.status.halfmoveCounter == 0);

                board.undoLastMove();

                expect(board.status.halfmoveCounter == 3);
            });

            it("Testing halfmove counter resets on capture", []() {
                ChessBoard board;
                board.parseFEN(
                    "rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - "
                    "5 2");

                Move move(e4, d5, PAWN_CAPTURE);

                board.makeMove(move);

                expect(board.status.halfmoveCounter == 0);

                board.undoLastMove();

                expect(board.status.halfmoveCounter == 5);
            });

            it("Testing halfmove counter increments on quiet move", []() {
                ChessBoard board;
                board.parseFEN(
                    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 2 1");

                Move move(g1, f3, KNIGHT_QUIET);

                board.makeMove(move);

                expect(board.status.halfmoveCounter == 3);

                board.undoLastMove();

                expect(board.status.halfmoveCounter == 2);
            });

            it("Testing fullmove number increments after black move", []() {
                ChessBoard board;
                board.parseFEN(
                    "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 "
                    "1");

                Move move(e7, e5, PAWN_DOUBLE_PUSH);

                board.makeMove(move);

                expect(board.status.fullmoveNumber == 2);

                board.undoLastMove();

                expect(board.status.fullmoveNumber == 1);
            });

            it("Testing fullmove number stays same after white move", []() {
                ChessBoard board;
                board.parseFEN(
                    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

                Move move(e2, e4, PAWN_DOUBLE_PUSH);

                board.makeMove(move);

                expect(board.status.fullmoveNumber == 1);

                board.undoLastMove();

                expect(board.status.fullmoveNumber == 1);
            });

            it("Testing counters through multiple moves", []() {
                ChessBoard board;
                board.setupInitialPosition();

                Move move1(e2, e4, PAWN_DOUBLE_PUSH);
                Move move2(e7, e5, PAWN_DOUBLE_PUSH);
                Move move3(g1, f3, KNIGHT_QUIET);
                Move move4(b8, c6, KNIGHT_QUIET);

                board.makeMove(move1);
                expect(board.status.halfmoveCounter == 0);
                expect(board.status.fullmoveNumber == 1);

                board.makeMove(move2);
                expect(board.status.halfmoveCounter == 0);
                expect(board.status.fullmoveNumber == 2);

                board.makeMove(move3);
                expect(board.status.halfmoveCounter == 1);
                expect(board.status.fullmoveNumber == 2);

                board.makeMove(move4);
                expect(board.status.halfmoveCounter == 2);
                expect(board.status.fullmoveNumber == 3);

                board.undoLastMove();
                expect(board.status.halfmoveCounter == 1);
                expect(board.status.fullmoveNumber == 2);
            });
        });
    });
}