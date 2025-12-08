using namespace std;

#include <bitset>
#include <iostream>

#include "bitboard/bitboard.h"
#include "chessboard/chessboard.h"
#include "engine/engine.h"
#include "lib/color.h"
#include "lib/magic.h"
#include "lib/piece.h"
#include "lib/random.h"
#include "lib/square.h"

int main() {
    std::cout << "Khez Chess Engine - Bitboard Demo\n";
    std::cout << "==================================\n\n";

    Engine engine;
    engine.init();

    Bitboard occupancies = Bitboard();
    Bitboard queensAttacks = engine.getSingleQueenAttacks(e4, occupancies);

    cout << queensAttacks.toString() << endl;
}