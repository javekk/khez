#include <bitset>
#include <iostream>

#include "bitboard.h"
#include "chess_board.h"

int main() {
    std::cout << "Khez Chess Engine - Bitboard Demo\n";
    std::cout << "==================================\n\n";

    ChessBoard board;
    // board.setupInitialPosition();
    // std::cout << board.toString() << "\n";

    // int pieceSquare = b6;
    // Bitboard piece;
    // piece.setBit(pieceSquare);
    //
    // Bitboard blocks;
    //
    // Bitboard attacks_or_moves =
    //    board.generateSingleRookAttacks(pieceSquare, blocks);
    //
    // std::cout << (attacks_or_moves).toString() << std::endl;

    std::cout << Bitboard(123434).toString() << std::endl;
    std::cout << squareMap.at(static_cast<Square>(
                     Bitboard(123434).leastSignificantBeatIndex()))
              << std::endl;

    return 0;
}