#include "cryptology/ciphers/affine_cipher.hpp"
#include "gtest/gtest.h"

TEST(AffineCipherTest, testEncryptI) {
    AffineCipher affine_cipher = AffineCipher(8, 5);
    string plain_text = "Hallo Welt";
    string cipher_text = affine_cipher.encrypt(plain_text);
    ASSERT_EQ(cipher_text, "RILLA OCLZ");
}

TEST(AffineCipherTest, testDecryptI) {
    AffineCipher affine_cipher = AffineCipher(8, 5);
    string cipher_text = "RILLA OCLZ";
    string plain_text = affine_cipher.decrypt(cipher_text);
    ASSERT_EQ(plain_text, "HALLO WELT");
}

TEST(AffineCipherTest, testIdentityI) {
    AffineCipher affine_cipher = AffineCipher(8, 5);
    string plain_text = "ASDFASD";
    string cipher_text = affine_cipher.encrypt(plain_text);
    ASSERT_EQ(affine_cipher.decrypt(cipher_text), plain_text);
}

TEST(AffineCipherTest, testEncryptII) {
    AffineCipher affine_cipher = AffineCipher(0, 5);
    string plain_text = "Hallo Welt";
    string cipher_text = affine_cipher.encrypt(plain_text);
    ASSERT_EQ(cipher_text, "JADDS GUDR");
}

TEST(AffineCipherTest, testDecryptII) {
    AffineCipher affine_cipher = AffineCipher(0, 5);
    string cipher_text = "JADDS GUDR";
    string plain_text = affine_cipher.decrypt(cipher_text);
    ASSERT_EQ(plain_text, "HALLO WELT");
}

TEST(AffineCipherTest, testIdentityII) {
    AffineCipher affine_cipher = AffineCipher(0, 5);
    string plain_text = "ASDFASD";
    string cipher_text = affine_cipher.encrypt(plain_text);
    ASSERT_EQ(affine_cipher.decrypt(cipher_text), plain_text);
}

TEST(AffineCipherTest, testEncryptNoShiftNoSlope) {
    AffineCipher affine_cipher = AffineCipher(0, 1);
    string cipher_text = affine_cipher.encrypt("Hallo Welt");
    ASSERT_EQ(cipher_text, "HALLO WELT");
}

TEST(AffineCipherTest, testDecryptNoShiftNoSlope) {
    AffineCipher affine_cipher = AffineCipher(0, 1);
    string cipher_text = affine_cipher.decrypt("Hallo Welt");
    ASSERT_EQ(cipher_text, "HALLO WELT");
}

TEST(AffineCipherTest, testIdentityNoShiftNoSlope) {
    AffineCipher affine_cipher = AffineCipher(0, 1);
    string plain_text = "HALLO WELT";
    string cipher_text = affine_cipher.encrypt(plain_text);
    ASSERT_EQ(affine_cipher.decrypt(cipher_text), plain_text);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}