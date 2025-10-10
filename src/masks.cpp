#include "masks.h"

/*
  To generate bitboards you can use this simple script,
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