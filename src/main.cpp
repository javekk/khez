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

    PseudoRandomNumberGenerator rng = PseudoRandomNumberGenerator(1804289383);
    MagicNumberGenerator mng = MagicNumberGenerator(rng);
    u_int64_t* bishopMagicNumbers = mng.findBishopMagicNumbers();

    for (int square = 0; square < 64; square++) {
        cout << "0x" << hex << bishopMagicNumbers[square] << "," << endl;
    }
    cout << "\n\n";
    u_int64_t* rookMagicNumbers = mng.findRookMagicNumbers();
    for (int square = 0; square < 64; square++) {
        cout << "0x" << hex << rookMagicNumbers[square] << "," << endl;
    }

    return 0;
}