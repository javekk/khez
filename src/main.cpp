using namespace std;

#include <bitset>
#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

#include "bitboard/bitboard.h"
#include "engine/chessboard/chessboard.h"
#include "engine/chessboard/color.h"
#include "engine/engine.h"
#include "lib/args/ command-line-args.h"
#include "lib/logger/logger.h"

int main(int argc, char* argv[]) {
    CommandLineParser parser;
    CommandLineArgs args = parser.parseCommandLine(argc, argv);

    bool uciMode = args.uciMode;

    logger.configure(LoggerProps{
        minLevel : static_cast<LogLevel>(args.logLevel),
        enabled : args.logEnable,
    });

    logger.info("=============================================");
    logger.info("=============================================");
    logger.info("===== Khez Chess Engine - Bitboard Demo =====");
    logger.info("=============================================");
    logger.info("=============================================");

    Engine engine;
    engine.init();

    if (uciMode) {
        logger.info("Starint in UCI mode");
        engine.setupInitialPosition();
        engine.UCI();
    }

    if (args.benchMode) {
        struct BenchPos {
            const char* name;
            const char* fen;
        };
        const std::vector<BenchPos> positions = {
            {"startpos",
             "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"},
            {"kiwipete",
             "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq "
             "- 0 1"},
            {"endgame", "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1"},
            {"midgame",
             "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/"
             "R4RK1 w - - 0 10"},
        };

        long long int totalNodes = 0;
        long long int totalMs = 0;
        for (const auto& p : positions) {
            Engine e;
            e.init();
            e.parseFEN(p.fen);
            SearchResults r = e.searchBestMove(args.benchDepth);
            totalNodes += r.numberOfNodes;
            totalMs += r.time_ms;
            cout << p.name << " depth=" << args.benchDepth
                 << " nodes=" << r.numberOfNodes << " time_ms=" << r.time_ms
                 << endl;
        }

        long long int nps =
            totalMs > 0 ? (totalNodes * 1000) / totalMs : 0;
        cout << "===" << endl;
        cout << "total_nodes=" << totalNodes << endl;
        cout << "total_time_ms=" << totalMs << endl;
        cout << "nps=" << nps << endl;

        std::ofstream out("bench_results.json");
        out << "[\n";
        out << "  {\"name\": \"search_total_time_ms\", \"unit\": \"ms\", "
               "\"value\": "
            << totalMs << "},\n";
        out << "  {\"name\": \"search_total_nodes\", \"unit\": \"nodes\", "
               "\"value\": "
            << totalNodes << "},\n";
        out << "  {\"name\": \"search_nps\", \"unit\": \"nodes/sec\", "
               "\"value\": "
            << nps << "}\n";
        out << "]\n";
        out.close();
        return 0;
    }

    // DEBUG

    // engine.parseFEN("4k3/q7/4K3/8/8/8/8/8 w - - 0 1 ");
    // cout << engine.board.toStringFancy();
    // engine.__printMoves(engine.generateAllPseudoLegalMovesAsMoveList());
    // cout << engine.evaluatePosition() << endl;
    //  cout << engine.searchBestMove(4).first.toStringUCI() << endl

    engine.setupInitialPosition();
    // engine.parseUCIPosition(
    //     "position startpos moves g1f3 g8f6 d2d4 d7d5 b1c3 b8c6 c1g5 c8g4 h2h3
    //     " "g4e6 h1g1 h7h6 g5e3 h8g8 b2b3 b7b6 g2g4 g7g5");
    int totalHalfMoves = 0;
    int totalTime = 0;
    while (true) {
        cout << "┏━━━ RUN " << endl;
        cout << engine.board.toStringFancy();
        SearchResults searchResult = engine.searchBestMove(
            args.depthSearch, [](const SearchResults& r, int d) {
                cout << "┃ info score cp " << r.score << " depth " << d
                     << " nodes " << r.numberOfNodes << " time(ms) "
                     << r.time_ms << " pv ";
                for (int i = 0; i < r.pvLength; i++)
                    cout << Move(r.pvTable[i]).toStringUCI() << " ";
                cout << endl;
            });
        Move bestMove = searchResult.bestMove;
        int score = searchResult.score;
        u_int64_t nodes = searchResult.numberOfNodes;

        cout << "┃ Score: " << score << endl;
        cout << "┃ Best move: " << bestMove.toStringComplete() << endl;
        cout << "┃ Searched Node: " << nodes << endl;
        cout << "┃ Time(ms): " << searchResult.time_ms << endl;
        cout << "┗━━ " << endl;

        totalHalfMoves++;
        totalTime += searchResult.time_ms;
        cout << "┏━━━ Total " << endl;
        cout << "┃ Half Moves: " << totalHalfMoves << endl;
        cout << "┃ Time(ms): " << totalTime << endl;
        cout << "┃ Time(s): " << totalTime / 1000 << endl;
        cout << "┗━━ " << endl;

        // getchar();

        engine.makeMove(bestMove);
    }
}