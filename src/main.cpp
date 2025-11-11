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

    int pieceSquare = a5;
    Bitboard piece;
    piece.setBit(pieceSquare);

    Bitboard blocks;
    blocks.setBit(b6);

    Bitboard attacks_or_moves =
        board.generateSingleBishopAttacks(pieceSquare, blocks);

    std::cout << (attacks_or_moves).toString() << std::endl;

    // std::cout << Bitboard(0x00000000000000FF).toString() << std::endl;
    // std::cout << notAFile.toString() << std::endl;

    return 0;
}