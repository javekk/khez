#include "masks.h"

const Bitboard whitePawns = Bitboard(0x00ff000000000000);
const Bitboard blackPawns = Bitboard(0x000000000000ff00);
const Bitboard whiteRooks = Bitboard(0x8100000000000000);
const Bitboard blackRooks = Bitboard(0x0000000000000081);
const Bitboard whiteKnights = Bitboard(0x4200000000000000);
const Bitboard blackKnights = Bitboard(0x0000000000000042);
const Bitboard whiteBishops = Bitboard(0x2400000000000000);
const Bitboard blackBishops = Bitboard(0x0000000000000024);
const Bitboard whiteQueen = Bitboard(0x1000000000000000);
const Bitboard blackQueen = Bitboard(0x0000000000000010);
const Bitboard whiteKing = Bitboard(0x0800000000000000);
const Bitboard blackKing = Bitboard(0x0000000000000008);

/*
  To generate file bitboards you can use this simple script,
  this one in the example is for generate the mask for notAFile

    Bitboard not_a_file;
    for (int rank = 0; rank < 8; rank++) {
        for (int file = 0; file < 8; file++) {
            if (file > 0) {
                not_a_file.setBit(file + (8 * rank));
            }
        }
    }
    std::cout << not_a_file.toString() << std::endl;
    std::cout << std::hex << not_a_file.getValue() << std::endl;
*/

const Bitboard notAFile = Bitboard(0x7f7f7f7f7f7f7f7f);
const Bitboard notHFile = Bitboard(0xfefefefefefefefe);

const Bitboard notABFile = Bitboard(0x3f3f3f3f3f3f3f3f);
const Bitboard notGHFile = Bitboard(0xfcfcfcfcfcfcfcfc);

const Bitboard firstRank = Bitboard(0xFF00000000000000);
const Bitboard eighthRank = Bitboard(0x00000000000000FF);