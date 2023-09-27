#include "cryptology/ciphers/hill_cipher.hpp"
#include "gtest/gtest.h"

TEST(HillCipherTest, testEncrypt) {
    Matrix<26> h = Matrix<26>({{11, 13, 8, 21}, {24, 17, 3, 25}, {18, 12, 23, 17}, {6, 15, 2, 15}});
    HillCipher hill_cipher = HillCipher(h);
    string plain_text = "HILL";
    string cipher_text = hill_cipher.encrypt(plain_text);
    ASSERT_EQ(cipher_text, "NERX");
}

TEST(HillCipherTest, testEncryptFailI) {
    Matrix<26> h = Matrix<26>({{11, 13, 8, 21}, {24, 17, 3, 25}, {18, 12, 23, 17}, {6, 15, 2, 15}});
    HillCipher hill_cipher = HillCipher(h);
    string plain_text = "HILLL";
    EXPECT_THROW(hill_cipher.encrypt(plain_text), std::runtime_error);
}

TEST(HillCipherTest, testEncryptFailII) {
    Matrix<26> h = Matrix<26>({{11, 13, 8, 21}, {24, 17, 3, 25}, {18, 12, 23, 17}, {6, 15, 2, 15}});
    HillCipher hill_cipher = HillCipher(h);
    string plain_text = "HIL";
    EXPECT_THROW(hill_cipher.encrypt(plain_text), std::runtime_error);
}

TEST(HillCipherTest, testDecrypt) {
    Matrix<26> h = Matrix<26>({{11, 13, 8, 21}, {24, 17, 3, 25}, {18, 12, 23, 17}, {6, 15, 2, 15}});
    HillCipher hill_cipher = HillCipher(h);
    string cipher_text = "NERX";
    string plain_text = hill_cipher.decrypt(cipher_text);
    ASSERT_EQ(plain_text, "HILL");
}

TEST(HillCipherTest, testIdentity) {
    Matrix<26> h = Matrix<26>({{11, 13, 8, 21}, {24, 17, 3, 25}, {18, 12, 23, 17}, {6, 15, 2, 15}});
    HillCipher hill_cipher = HillCipher(h);
    string plain_text = "ASDFASDF";
    string cipher_text = hill_cipher.encrypt(plain_text);
    ASSERT_EQ(hill_cipher.decrypt(cipher_text), plain_text);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}