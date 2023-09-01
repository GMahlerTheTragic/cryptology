#include <iostream>

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

vector<int> word_to_vec(string input) {
  vector<int> result = vector<int>(input.length());
  for (int i = 0; i < input.length(); ++i) {
    result[i] = letter_to_pos(input[i]);
  }
  return result;
}

vector<vector<int>> tuples(int range, int tuple_size) {
  vector<vector<int>> result;
  int maxValue = 1;
  for (int i = 0; i < tuple_size; i++) {
    maxValue *= range;
  }
  for (int counter = 0; counter < maxValue; counter++) {
    int current_value = counter;
    vector<int> tuple(tuple_size);
    for (int i = 0; i < tuple_size; i++) {
      int digit = current_value % range;
      tuple[tuple_size - i - 1] = digit;
      current_value /= range;
    }
    result.push_back(tuple);
  }
  return result;
}