using namespace std;

#include <bitset>
#include <iostream>

#include "bitboard/bitboard.h"
#include "chessboard/chessboard.h"
#include "engine/engine.h"
#include "lib/random.h"
#include "lib/square.h"

int main() {
    std::cout << "Khez Chess Engine - Bitboard Demo\n";
    std::cout << "==================================\n\n";

    RandonNumberGenerator rng = RandonNumberGenerator(1804289383);

    Bitboard bb1 = Bitboard(rng.generateRandomU32Number());
    cout << bb1.toString() << endl;
    Bitboard bb2 = Bitboard(rng.generateRandomU32Number() & 0xFFFF);
    cout << bb2.toString() << endl;
    Bitboard bb3 = Bitboard(rng.generateRandomU64Number());
    cout << bb3.toString() << endl;
    Bitboard bb4 = Bitboard(rng.generateMagicNumberCandidate());
    cout << bb4.toString() << endl;

    return 0;
}