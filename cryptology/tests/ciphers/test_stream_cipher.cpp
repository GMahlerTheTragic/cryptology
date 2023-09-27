#include "cryptology/ciphers/stream_cipher.hpp"
#include "gtest/gtest.h"

TEST(VigenereCipherTest, testEncrypt) {
    VigenereCipher vigenere_cipher = VigenereCipher("WIE");
    string plain_text = "VIGENERE";
    string cipher_text = vigenere_cipher.encrypt(plain_text);
    ASSERT_EQ(cipher_text, "RQKAVINM");
}

TEST(VigenereCipherTest, testDecrypt) {
    VigenereCipher vigenere_cipher = VigenereCipher("WIE");
    string cipher_text = "RQKAVINM";
    string plain_text = vigenere_cipher.decrypt(cipher_text);
    ASSERT_EQ(plain_text, "VIGENERE");
}

TEST(VigenereCipherTest, testIdentity) {
    VigenereCipher vigenere_cipher = VigenereCipher("WIE");
    string plain_text = "ASDFOAINOSINIDUAIUVSYVRASAD";
    string cipher_text = vigenere_cipher.encrypt(plain_text);
    ASSERT_EQ(vigenere_cipher.decrypt(cipher_text), plain_text);
}

TEST(BeaufortCipherTest, testEncrypt) {
    BeaufortCipher beaufort_cipher = BeaufortCipher("WIE");
    string plain_text = "BEAUFORT";
    string cipher_text = beaufort_cipher.encrypt(plain_text);
    ASSERT_EQ(cipher_text, "VEECDQFP");
}

TEST(BeaufortCipherTest, testDecrypt) {
    BeaufortCipher beaufort_cipher = BeaufortCipher("WIE");
    string cipher_text = "VEECDQFP";
    string plain_text = beaufort_cipher.decrypt(cipher_text);
    ASSERT_EQ(plain_text, "BEAUFORT");
}

TEST(BeaufortCipherTest, testIdentity) {
    BeaufortCipher beaufort_cipher = BeaufortCipher("WIE");
    string plain_text = "ASDFOAINOSINIDUAIUVSYVRASAD";
    string cipher_text = beaufort_cipher.encrypt(plain_text);
    ASSERT_EQ(beaufort_cipher.decrypt(cipher_text), plain_text);
}

TEST(AutoKeyPlainTextCipherTest, testEncrypt) {
    AutoKeyPlainTextCipher auto_key_plain_text_cipher = AutoKeyPlainTextCipher("WIE");
    string plain_text = "VIGENERE";
    string cipher_text = auto_key_plain_text_cipher.encrypt(plain_text);
    ASSERT_EQ(cipher_text, "RQKZVKVR");
}

TEST(AutoKeyPlainTextCipherTest, testDecrypt) {
    AutoKeyPlainTextCipher auto_key_plain_text_cipher = AutoKeyPlainTextCipher("WIE");
    string cipher_text = "RQKZVKVR";
    string plain_text = auto_key_plain_text_cipher.decrypt(cipher_text);
    ASSERT_EQ(plain_text, "VIGENERE");
}

TEST(AutoKeyPlainTextCipherTest, testIdentity) {
    AutoKeyPlainTextCipher auto_key_plain_text_cipher = AutoKeyPlainTextCipher("WIE");
    string plain_text = "ASDFOAINOSINIDUAIUVSYVRASAD";
    string cipher_text = auto_key_plain_text_cipher.encrypt(plain_text);
    ASSERT_EQ(auto_key_plain_text_cipher.decrypt(cipher_text), plain_text);
}

TEST(AutoKeyCipherTextCipherTest, testEncrypt) {
    AutoKeyCipherTextCipher auto_key_cipher_text_cipher = AutoKeyCipherTextCipher("WIE");
    string plain_text = "VIGENERE";
    string cipher_text = auto_key_cipher_text_cipher.encrypt(plain_text);
    ASSERT_EQ(cipher_text, "RQKVDOMH");
}

TEST(AutoKeyCipherTextCipherTest, testDecrypt) {
    AutoKeyCipherTextCipher auto_key_cipher_text_cipher = AutoKeyCipherTextCipher("WIE");
    string cipher_text = "RQKVDOMH";
    string plain_text = auto_key_cipher_text_cipher.decrypt(cipher_text);
    ASSERT_EQ(plain_text, "VIGENERE");
}

TEST(AutoKeyCipherTextCipherTest, testIdentity) {
    AutoKeyCipherTextCipher auto_key_cipher_text_cipher = AutoKeyCipherTextCipher("WIE");
    string plain_text = "ASDFOAINOSINIDUAIUVSYVRASAD";
    string cipher_text = auto_key_cipher_text_cipher.encrypt(plain_text);
    ASSERT_EQ(auto_key_cipher_text_cipher.decrypt(cipher_text), plain_text);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}