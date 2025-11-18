using namespace std;

#include <bitset>
#include <iostream>

#include "bitboard/bitboard.h"
#include "chessboard/chessboard.h"
#include "engine/engine.h"
#include "lib/magic.h"
#include "lib/random.h"
#include "lib/square.h"

int main() {
    std::cout << "Khez Chess Engine - Bitboard Demo\n";
    std::cout << "==================================\n\n";

    Engine engine;

    engine.generateSliderPiecesAttacks(BISHOP);
    engine.generateSliderPiecesAttacks(ROOK);

    Bitboard occupancies;
    occupancies.setBit(a3);
    occupancies.setBit(b3);
    occupancies.setBit(c3);
    occupancies.setBit(c2);
    occupancies.setBit(c1);

    Bitboard attacks = engine.getSingleBishopAttacks(a1, occupancies);

    cout << "Occupancies: \n" << occupancies.toString() << endl;

    cout << "Attacks from c2 " << endl << attacks.toString();

    Bitboard attacks2 = engine.getSingleRookAttacks(e2, occupancies);

    cout << "Attacks from f4" << endl << attacks2.toString();

    return 0;
}