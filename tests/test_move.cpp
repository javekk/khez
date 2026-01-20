#include <iostream>

#include "../src/lib/move.h"
#include "test_lib.h"

void run_move_tests() {
    describe("Testing Move class", []() {
        describe("Testing pawn moves", []() {
            it("Testing pawn push", []() {
                Move move(e2, e3, PAWN_PUSH);
                expect(move.from == e2);
                expect(move.to == e3);
                expect(move.piece == PAWN);
                expect(!move.isCapture);
                expect(!move.isDoublePush);
                expect(!move.isEnpassant);
                expect(!move.isCastling);
                expect(move.promoted == EMPTY);
            });

            it("Testing pawn double push", []() {
                Move move(e2, e4, PAWN_DOUBLE_PUSH);
                expect(move.from == e2);
                expect(move.to == e4);
                expect(move.piece == PAWN);
                expect(!move.isCapture);
                expect(move.isDoublePush);
                expect(!move.isEnpassant);
                expect(!move.isCastling);
            });

            it("Testing pawn capture", []() {
                Move move(e4, d5, PAWN_CAPTURE);
                expect(move.piece == PAWN);
                expect(move.isCapture);
                expect(!move.isDoublePush);
                expect(!move.isEnpassant);
            });

            it("Testing pawn en passant capture", []() {
                Move move(e5, d6, PAWN_CAPTURE_ENPASSANT);
                expect(move.piece == PAWN);
                expect(move.isCapture);
                expect(move.isEnpassant);
                expect(!move.isDoublePush);
            });

            it("Testing pawn promotion to queen", []() {
                Move move(e7, e8, PAWN_PROMOTION_TO_QUEEN);
                expect(move.piece == PAWN);
                expect(move.promoted == QUEEN);
                expect(!move.isCapture);
            });

            it("Testing pawn promotion to knight", []() {
                Move move(a7, a8, PAWN_PROMOTION_TO_KNIGHT);
                expect(move.piece == PAWN);
                expect(move.promoted == KNIGHT);
            });

            it("Testing pawn promotion to rook", []() {
                Move move(h7, h8, PAWN_PROMOTION_TO_ROOK);
                expect(move.piece == PAWN);
                expect(move.promoted == ROOK);
            });

            it("Testing pawn promotion to bishop", []() {
                Move move(c7, c8, PAWN_PROMOTION_TO_BISHOP);
                expect(move.piece == PAWN);
                expect(move.promoted == BISHOP);
            });

            it("Testing pawn capture promotion to queen", []() {
                Move move(e7, d8, PAWN_CAPTURE_PROMOTION_TO_QUEEN);
                expect(move.piece == PAWN);
                expect(move.promoted == QUEEN);
                expect(move.isCapture);
            });

            it("Testing pawn capture promotion to knight", []() {
                Move move(e7, f8, PAWN_CAPTURE_PROMOTION_TO_KNIGHT);
                expect(move.piece == PAWN);
                expect(move.promoted == KNIGHT);
                expect(move.isCapture);
            });
        });

        describe("Testing knight moves", []() {
            it("Testing knight quiet move", []() {
                Move move(b1, c3, KNIGHT_QUIET);
                expect(move.from == b1);
                expect(move.to == c3);
                expect(move.piece == KNIGHT);
                expect(!move.isCapture);
                expect(move.promoted == EMPTY);
            });

            it("Testing knight capture", []() {
                Move move(c3, d5, KNIGHT_CAPTURE);
                expect(move.piece == KNIGHT);
                expect(move.isCapture);
            });
        });

        describe("Testing bishop moves", []() {
            it("Testing bishop quiet move", []() {
                Move move(c1, e3, BISHOP_QUIET);
                expect(move.piece == BISHOP);
                expect(!move.isCapture);
            });

            it("Testing bishop capture", []() {
                Move move(e3, a7, BISHOP_CAPTURE);
                expect(move.piece == BISHOP);
                expect(move.isCapture);
            });
        });

        describe("Testing rook moves", []() {
            it("Testing rook quiet move", []() {
                Move move(a1, a4, ROOK_QUIET);
                expect(move.piece == ROOK);
                expect(!move.isCapture);
            });

            it("Testing rook capture", []() {
                Move move(a4, e4, ROOK_CAPTURE);
                expect(move.piece == ROOK);
                expect(move.isCapture);
            });
        });

        describe("Testing queen moves", []() {
            it("Testing queen quiet move", []() {
                Move move(d1, d5, QUEEN_QUIET);
                expect(move.piece == QUEEN);
                expect(!move.isCapture);
            });

            it("Testing queen capture", []() {
                Move move(d5, h5, QUEEN_CAPTURE);
                expect(move.piece == QUEEN);
                expect(move.isCapture);
            });
        });

        describe("Testing king moves", []() {
            it("Testing king quiet move", []() {
                Move move(e1, e2, KING_QUIET);
                expect(move.piece == KING);
                expect(!move.isCapture);
                expect(!move.isCastling);
            });

            it("Testing king capture", []() {
                Move move(e4, d5, KING_CAPTURE);
                expect(move.piece == KING);
                expect(move.isCapture);
            });

            it("Testing kingside castle", []() {
                Move move(e1, g1, CASTLE_KINGSIDE);
                expect(move.piece == KING);
                expect(move.isCastling);
                expect(!move.isCapture);
            });

            it("Testing queenside castle", []() {
                Move move(e1, c1, CASTLE_QUEENSIDE);
                expect(move.piece == KING);
                expect(move.isCastling);
                expect(!move.isCapture);
            });
        });

        describe("Testing move equality operator", []() {
            it("Testing equal moves", []() {
                Move move1(e2, e4, PAWN_DOUBLE_PUSH);
                Move move2(e2, e4, PAWN_DOUBLE_PUSH);
                expect(move1 == move2);
            });

            it("Testing different from squares", []() {
                Move move1(e2, e4, PAWN_PUSH);
                Move move2(d2, e4, PAWN_PUSH);
                expect(!(move1 == move2));
            });

            it("Testing different to squares", []() {
                Move move1(e2, e4, PAWN_PUSH);
                Move move2(e2, e3, PAWN_PUSH);
                expect(!(move1 == move2));
            });

            it("Testing different move types", []() {
                Move move1(e2, e4, PAWN_DOUBLE_PUSH);
                Move move2(e2, e4, PAWN_PUSH);
                expect(!(move1 == move2));
            });
        });

        describe("Testing binary encoding and decoding", []() {
            it("Testing pawn push encoding", []() {
                Move move(e2, e4, PAWN_DOUBLE_PUSH);
                u_int32_t binary = move.getBinaryMove();
                Move decoded(binary);

                expect(decoded.from == e2);
                expect(decoded.to == e4);
                expect(decoded.piece == PAWN);
                expect(decoded.isDoublePush);
                expect(!decoded.isCapture);
            });

            it("Testing knight capture encoding", []() {
                Move move(c3, d5, KNIGHT_CAPTURE);
                u_int32_t binary = move.getBinaryMove();
                Move decoded(binary);

                expect(decoded.from == c3);
                expect(decoded.to == d5);
                expect(decoded.piece == KNIGHT);
                expect(decoded.isCapture);
            });

            it("Testing promotion encoding", []() {
                Move move(e7, e8, PAWN_PROMOTION_TO_QUEEN);
                u_int32_t binary = move.getBinaryMove();
                Move decoded(binary);

                expect(decoded.piece == PAWN);
                expect(decoded.promoted == QUEEN);
                expect(decoded.from == e7);
                expect(decoded.to == e8);
            });

            it("Testing castle encoding", []() {
                Move move(e1, g1, CASTLE_KINGSIDE);
                u_int32_t binary = move.getBinaryMove();
                Move decoded(binary);

                expect(decoded.piece == KING);
                expect(decoded.isCastling);
                expect(decoded.from == e1);
                expect(decoded.to == g1);
            });

            it("Testing en passant encoding", []() {
                Move move(e5, d6, PAWN_CAPTURE_ENPASSANT);
                u_int32_t binary = move.getBinaryMove();
                Move decoded(binary);

                expect(decoded.piece == PAWN);
                expect(decoded.isEnpassant);
                expect(decoded.isCapture);
            });

            it("Testing round-trip for all piece types", []() {
                Move moves[] = {
                    Move(a2, a3, PAWN_PUSH),
                    Move(b1, c3, KNIGHT_QUIET),
                    Move(c1, e3, BISHOP_QUIET),
                    Move(a1, a5, ROOK_QUIET),
                    Move(d1, h5, QUEEN_QUIET),
                    Move(a2, a1, PAWN_CAPTURE_PROMOTION_TO_QUEEN),
                    Move(b2, b3, PAWN_CAPTURE_ENPASSANT),
                    Move(e8, c8, CASTLE_QUEENSIDE),
                    Move(e1, g1, CASTLE_KINGSIDE),
                    Move(a2, a4, PAWN_DOUBLE_PUSH),
                };

                for (const auto& original : moves) {
                    u_int32_t binary = original.getBinaryMove();
                    Move decoded(binary);
                    expect(original == decoded);
                }
            });
        });

        describe("Testing toString method", []() {
            it("Testing toString returns non-empty string", []() {
                Move move(e2, e4, PAWN_DOUBLE_PUSH);
                std::string str = move.toString();
                expect(!str.empty());
            });

            it("Testing toString contains square information", []() {
                Move move(a1, h8, QUEEN_QUIET);
                std::string str = move.toString();
                expect(str.find("a1") != std::string::npos);
                expect(str.find("h8") != std::string::npos);
            });

            it("Testing toString contains move type", []() {
                Move move(e1, g1, CASTLE_KINGSIDE);
                std::string str = move.toString();
                expect(str.find("CASTLE_KINGSIDE") != std::string::npos);
            });
        });
    });
}