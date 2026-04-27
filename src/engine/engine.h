#pragma once

#include <chrono>
#include <cstring>
#include <functional>
#include <string>
#include <vector>

#include "../bitboard/bitboard.h"
#include "./chessboard/chessboard-status.h"
#include "./chessboard/chessboard.h"
#include "./chessboard/color.h"
#include "./chessboard/piece.h"
#include "./chessboard/sliding-piece.h"
#include "./chessboard/square.h"
#include "./move/move.h"

/**
 * Mutable per-search state passed through every negamax_ / quiescence_
 * recursion.
 *
 * Holds everything that varies during a search but must be visible across
 * plies: current ply, node counter, move-ordering tables (PV, killers,
 * history), and PV-search flags. Survives across iterative-deepening
 * passes via initFromPreviousContenxt(), so move ordering compounds with
 * depth.
 */
struct SearchContext {
    static constexpr int MAX_PLY = 64;

    /// Below this remaining depth LMR is disabled (too shallow to risk
    /// reductions safely).
    static constexpr int REDUCTION_LIMIT = 3;

    /// Move-list index from which LMR may apply: the first FULL_DEPTH_MOVE
    /// moves at each node are always searched at full depth.
    static constexpr int FULL_DEPTH_MOVE = 4;

    /// Distance from the root, in plies.
    int ply = 0;

    /// Total nodes visited (negamax_ + quiescence_).
    u_int64_t nodes = 0;

    /// Two killer slots per ply: quiet moves that recently caused a beta
    /// cutoff at the same distance from root, likely strong here too.
    /// [ply][0] = most recent, [ply][1] = previous.
    uint32_t killerMoves[MAX_PLY][2] = {};

    /// History heuristic, indexed [piece][to-square]. Each quiet-move
    /// beta cutoff bumps its entry by depth*depth, so cutoffs deeper in
    /// the tree carry more weight.
    int historyMoves[6][64] = {};

    /// Triangular PV table: pvTable[ply] holds the principal variation
    /// from this ply downward, length pvLength[ply]. The root PV lives
    /// in pvTable[0].
    uint32_t pvTable[MAX_PLY][MAX_PLY] = {};
    int pvLength[MAX_PLY] = {};

    // PV-search flags. Three flags because they answer three different
    // questions about the PV (the best line found by the previous
    // iterative-deepening pass, stored in pvTable[0]):
    //
    //   foundPv  - "have we already found a move that raised alpha at
    //              THIS ply?" Switches the rest of this ply's move list
    //              from full-window to PVS null-window probes.
    //
    //   followPv - "are we still on the previous PV line in the tree?"
    //              True at the root; stays true only while we keep
    //              picking the PV move at each ply. Once we deviate,
    //              there is no point looking for the old PV in
    //              unrelated subtrees, so it's cleared.
    //
    //   scoringPv - "does THIS ply's move list actually contain the old
    //               PV move?" Set by togglePVScoring when found, read
    //               by evaluateMoveScore to boost that move to the
    //               front, then cleared by sortMoves after one use.

    bool foundPv = false;
    bool followPv = true;
    bool scoringPv = false;

    void initFromPreviousContenxt(const SearchContext* previousCtx) {
        if (previousCtx) {
            nodes = previousCtx->nodes;
            memcpy(pvTable, previousCtx->pvTable, sizeof(pvTable));
            memcpy(historyMoves, previousCtx->historyMoves,
                   sizeof(historyMoves));
            memcpy(killerMoves, previousCtx->killerMoves, sizeof(killerMoves));
        }
    }

    void storeKillerMove(Move move) {
        killerMoves[ply][1] = killerMoves[ply][0];
        killerMoves[ply][0] = move.toBinary();
    }

    void updateHistoryMove(Move move, int depth) {
        historyMoves[static_cast<int>(move.piece)][move.to] += depth * depth;
    }

    bool isKillerMove0(Move move) const {
        return killerMoves[ply][0] == move.toBinary();
    }
    bool isKillerMove1(Move move) const {
        return killerMoves[ply][1] == move.toBinary();
    }

    bool isKillerMove(Move move) const {
        return isKillerMove0(move) || isKillerMove1(move);
    }

    void updatePVLengthCurrentLevel() { pvLength[ply] = ply; }

    void updatePVTable(Move move) {
        pvTable[ply][ply] = move.toBinary();

        for (int nextPly = ply + 1; nextPly < pvLength[ply + 1]; nextPly++) {
            pvTable[ply][nextPly] = pvTable[ply + 1][nextPly];
        }

        pvLength[ply] = pvLength[ply + 1];
    }

    void resetScoring() { scoringPv = false; }

    void togglePVScoring(std::vector<Move> moves) {
        if (followPv) {
            followPv = false;
            for (Move move : moves) {
                if (pvTable[0][ply] == move.toBinary()) {
                    scoringPv = true;
                    followPv = true;
                }
            }
        }
    }
};

/**
 * Result of a completed search, returned by negamax() and searchBestMove().
 * Carries the user-facing answer (move, score, PV, time) plus the full
 * SearchContext so the next iterative-deepening pass can re-seed its
 * move-ordering tables.
 */
struct SearchResults {
    Move bestMove;
    uint32_t pvTable[64];  ///< Principal variation, only first pvLength valid.
    int pvLength;
    int score;  ///< Centipawns, from side-to-move at root. Mates: -49000 + ply.
    u_int64_t numberOfNodes;
    SearchContext ctx;  ///< Carried over to the next ID iteration.
    int64_t time_ms;
};

class Engine {
   public:
    // ============================================================
    // Setup
    // ============================================================
    // Board state and how to load a position into it.

    ChessBoard board;

    void init();
    void emptyBoard();
    void setupInitialPosition();
    void parseFEN(const std::string FEN);

    Bitboard setOccupancy(int index, Bitboard attacksMask);

    // ============================================================
    // Attack masks (precomputed lookup)
    // ============================================================
    // For each piece/square, the squares it can attack. Sliders use
    // magic-bitboard tables indexed by occupancy.

    Bitboard generateSinglePawnMaskAttacks(Square square, Color color);
    Bitboard getSinglePawnAttacks(Square square, Color color);

    Bitboard generateSingleKnightAttacksMask(Square square);
    Bitboard getSingleKnightAttacks(Square square);

    Bitboard generateSingleKingAttacksMask(Square square);
    Bitboard getSingleKingAttacks(Square square);

    Bitboard generateSingleBishopRelevantOccupanciesMask(Square square);
    Bitboard generateSingleBishopAttacks(Square square, Bitboard blocks);
    Bitboard getSingleBishopAttacks(Square square, Bitboard occupancies);

    Bitboard generateSingleRookRelevantOccupanciesMask(Square square);
    Bitboard generateSingleRookAttacks(Square square, Bitboard blocks);
    Bitboard getSingleRookAttacks(Square square, Bitboard occupancies);

    Bitboard getSingleQueenAttacks(Square square, Bitboard occupancies);

    void generateSliderPiecesAttacks(SlidingPiece piece);

    // ============================================================
    // Move generation & make/unmake
    // ============================================================
    // Pseudo-legal move generation (legality via makeMove rejecting
    // self-check), and attack queries used by check detection.

    std::vector<u_int32_t> generateAllPseudoLegalMoves();
    std::vector<Move> generateAllPseudoLegalMovesAsMoveList();

    bool makeMove(Move move);
    void undoMove();

    bool isSquareUnderAttackBy(Square square, Color color);

    // ============================================================
    // Search
    // ============================================================
    // Iterative deepening, negamax with alpha-beta + PVS + LMR, and
    // move ordering. See engine.cpp for per-function docs.

    SearchResults negamax(int depth,
                          const SearchContext* previousCtx = nullptr);
    SearchResults searchBestMove(
        int depth,
        std::function<void(const SearchResults&, int)> onIteration = nullptr);

    void sortMoves(std::vector<Move>& moves, SearchContext& ctx);

    // ============================================================
    // Evaluation
    // ============================================================
    // Static scoring of positions and individual moves.

    int evaluatePosition() const;
    int evaluateMaterialScore() const;
    int evaluateMoveScore(const Move move, const SearchContext& ctx) const;

    // ============================================================
    // UCI
    // ============================================================
    // Universal Chess Interface protocol I/O.

    bool parseUCIGo(std::string input);
    bool parseUCIPosition(std::string input);
    bool parseUCIMove(std::string input);
    bool UCIok();
    void UCI();

    // ============================================================
    // Debug / perft
    // ============================================================
    // Performance tests and pretty-printers (prefix __ = debug-only).

    long long int perftDriver(const int depth);
    void perfTest(const int depth);

    void __printMoves(std::vector<Move> moves);
    void __printAttackedSquare(Color color);

   private:
    // ============================================================
    // Precomputed mask tables
    // ============================================================
    // Filled by init() and never mutated after.

    Bitboard pawnAttacksMasks[2][64];
    Bitboard knightAttacksMasks[64];
    Bitboard kingAttacksMasks[64];

    Bitboard bishopRelevantOccupanciesMasks[64];
    Bitboard rookRelevantOccupanciesMasks[64];

    Bitboard bishopAttacksTable[64][512];
    Bitboard rookAttacksTable[64][4096];

    void generatePawnMaskAttacks();
    void generateKnightMaskMoves();
    void generateKingMaskMoves();

    // ============================================================
    // Move generation helpers
    // ============================================================
    // Per-piece generators called by generateAllPseudoLegalMoves.

    void generatePawnMoves(std::vector<u_int32_t>& moves);
    void generatePawnQuietMoves(Square from, std::vector<u_int32_t>& moves);
    void generatePawnCaptureMoves(Square from, std::vector<u_int32_t>& moves);

    void generateKingMoves(std::vector<u_int32_t>& moves);
    void generateKingCastlingMoves(std::vector<u_int32_t>& moves);
    bool canWhiteCastleKingSide();
    bool canWhiteCastleQueenSide();
    bool canBlackCastleKingSide();
    bool canBlackCastleQueenSide();

    void generateSliderAndLeaperMoves(Piece piece,
                                      std::vector<u_int32_t>& moves);
    Bitboard getAttacksBoard(Piece piece, Square square);

    bool isMyKingInCheck();
    bool isOpponentKingInCheck();

    // ============================================================
    // Search internals
    // ============================================================
    // Recursive search core; the public negamax/searchBestMove drive
    // these.

    int negamax_(int alpha, int beta, int depth, SearchContext& ctx);
    int quiescence_(int alpha, int beta, SearchContext& ctx);
};
