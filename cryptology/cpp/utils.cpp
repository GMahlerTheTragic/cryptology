#include <iostream>
#include <cryptology/algebra/algorithms.hpp>

using namespace std;

bool is_letter(char input) {
    return !(input < 0x41 || (input >= 0x5B && input < 0x61) || input > 0x7A);
}

int letter_to_pos(char input) {
    int pos = (input & 0x1F) - 1;
    return pos;
}

char pos_to_letter(int pos) {
    return 0x41 + pos;
}

bool word_from_latin_alphabet(string input) {
    for (int i = 0; i < input.size(); ++i) {
        if (!is_letter(input[i])) {
            return false;
        }
    }
    return true;
}