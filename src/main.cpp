#include <bitset>
#include <iostream>

#include "bitboard/bitboard.h"
#include "chessboard/chessboard.h"
#include "engine/engine.h"
#include "lib/square.h"

int main() {
    std::cout << "Khez Chess Engine - Bitboard Demo\n";
    std::cout << "==================================\n\n";

    // board.setupInitialPosition();
    // std::cout << board.toString() << "\n";

    int pieceSquare = a1;
    Bitboard piece;
    piece.setBit(pieceSquare);

    Engine engine;
    Bitboard attacks_or_moves =
        engine.generateSingleRookRelevantOccupanciesMask(pieceSquare);

    int bishop_relevant_occupancies_counts[64];
    for (int rank = 0; rank < 8; rank++) {
        for (int file = 0; file < 8; file++) {
            int square = file + (8 * rank);
            bishop_relevant_occupancies_counts[square] =
                engine.generateSingleBishopRelevantOccupanciesMask(square)
                    .popCount();
        }
    }
    for (int i = 0; i < 64; i++) {
        std::cout << bishop_relevant_occupancies_counts[i] << ",";
    }

    return 0;
}