#ifndef CRYPTOLOGY_CIPHERS_STREAM_CIPHER_HPP_
#define CRYPTOLOGY_CIPHERS_STREAM_CIPHER_HPP_

#include <iostream>
#include <string>

using namespace std;

class StreamCipher {
   protected:
    const string keyword;
    virtual u_int8_t get_next_shift(size_t round, string &plain_text, string &cipher_text) = 0;

   public:
    virtual ~StreamCipher() = default;
    explicit StreamCipher(const string &keyword);
    virtual string encrypt(string plain_text);
    virtual string decrypt(string cipher_text);
};

class VigenereCipher : public StreamCipher {
   private:
    u_int8_t get_next_shift(size_t round, string &plain_text, string &cipher_text) override;

   public:
    explicit VigenereCipher(const string &keyword) : StreamCipher(keyword){};
};

class BeaufortCipher : public StreamCipher {
   private:
    u_int8_t get_next_shift(size_t round, string &plain_text, string &cipher_text) override;

   public:
    explicit BeaufortCipher(const string &keyword) : StreamCipher(keyword){};
    string encrypt(string plain_text) override;
    string decrypt(string cipher_text) override;
};

class AutoKeyPlainTextCipher : public StreamCipher {
   private:
    u_int8_t get_next_shift(size_t round, string &plain_text, string &cipher_text) override;

   public:
    explicit AutoKeyPlainTextCipher(const string &keyword) : StreamCipher(keyword){};
};

class AutoKeyCipherTextCipher : public StreamCipher {
   private:
    u_int8_t get_next_shift(size_t round, string &plain_text, string &cipher_text) override;

   public:
    explicit AutoKeyCipherTextCipher(const string &keyword) : StreamCipher(keyword){};
};

#endif