#include "cryptology/utils/utils.hpp"
#include "gtest/gtest.h"

TEST(UtilsTest, IsLetter) {
    EXPECT_TRUE(is_letter('A'));
    EXPECT_TRUE(is_letter('a'));
    EXPECT_TRUE(is_letter('Z'));
    EXPECT_TRUE(is_letter('z'));
    EXPECT_FALSE(is_letter(' '));
    EXPECT_FALSE(is_letter('0'));
    EXPECT_FALSE(is_letter('9'));
    EXPECT_FALSE(is_letter('$'));
}

TEST(UtilsTest, LetterToPos) {
    EXPECT_EQ(letter_to_pos('A'), 0);
    EXPECT_EQ(letter_to_pos('B'), 1);
    EXPECT_EQ(letter_to_pos('Z'), 25);
    EXPECT_EQ(letter_to_pos('a'), 0);
    EXPECT_EQ(letter_to_pos('b'), 1);
    EXPECT_EQ(letter_to_pos('z'), 25);
}

TEST(UtilsTest, LetterToPosExceptionSpecial) {
    EXPECT_THROW(letter_to_pos('#'), std::runtime_error);
}

TEST(UtilsTest, LetterToPosExceptionNumber) {
    EXPECT_THROW(letter_to_pos('4'), std::runtime_error);
}

TEST(UtilsTest, LetterToPosExceptionI) { EXPECT_THROW(letter_to_pos('\n'), std::runtime_error); }

TEST(UtilsTest, LetterToPosExceptionII) { EXPECT_THROW(letter_to_pos('\r'), std::runtime_error); }

TEST(UtilsTest, LetterToPosExceptionIII) { EXPECT_THROW(letter_to_pos('\t'), std::runtime_error); }

TEST(UtilsTest, LetterToPosExceptionSpace) { EXPECT_THROW(letter_to_pos(' '), std::runtime_error); }

TEST(UtilsTest, PosToLetter) {
    EXPECT_EQ(pos_to_letter(0), 'A');
    EXPECT_EQ(pos_to_letter(1), 'B');
    EXPECT_EQ(pos_to_letter(25), 'Z');
}

TEST(UtilsTest, PosToLetterNegative) { EXPECT_THROW(letter_to_pos(-1), std::runtime_error); }

TEST(UtilsTest, PosToLetterHigherThan25) { EXPECT_THROW(letter_to_pos(26), std::runtime_error); }

TEST(UtilsTest, WordFromLatinAlphabet) {
    EXPECT_TRUE(word_from_latin_alphabet("Hello"));
    EXPECT_TRUE(word_from_latin_alphabet("World"));
    EXPECT_FALSE(word_from_latin_alphabet("Hello!"));
    EXPECT_FALSE(word_from_latin_alphabet("123"));
    EXPECT_FALSE(word_from_latin_alphabet("123 "));
    EXPECT_FALSE(word_from_latin_alphabet("1Ö3"));
}

TEST(UtilsTest, WordToVec) {
    std::vector<int> expected_result = {0, 1, 2, 3, 25};
    EXPECT_EQ(word_to_vec("abcdz"), expected_result);
}

TEST(UtilsTest, WordToVecException) { EXPECT_THROW(word_to_vec("abcdz!"), std::runtime_error); }

TEST(UtilsTest, Tuples) {
    std::vector<std::vector<int>> expected_result = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    EXPECT_EQ(tuples(2, 2), expected_result);
}

TEST(UtilsTest, GenerateCombinations) {
    const std::vector<std::vector<DynamicBitset>> lists = {
        {DynamicBitset("0101"), DynamicBitset("0011")},
        {DynamicBitset("1100"), DynamicBitset("1010")}};

    const std::vector<DynamicBitset> combinations = generateCombinations(lists);

    const std::vector result = {DynamicBitset("11000101"), DynamicBitset("10100101"),
        DynamicBitset("11000011"), DynamicBitset("10100011")};

    EXPECT_EQ(combinations, result);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
