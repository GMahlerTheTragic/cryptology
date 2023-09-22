#ifndef CRYPTOLOGY_CIPHERS_STREAM_CIPHER_HPP_
#define CRYPTOLOGY_CIPHERS_STREAM_CIPHER_HPP_

#include <iostream>
#include <string>

using namespace std;

class StreamCipher {
 protected:
  const string keyword;
  virtual int get_next_shift(size_t round, string &plain_text, string &cipher_text) = 0;
 public:
  StreamCipher(string keyword);
  virtual string encrypt(string plain_text);
  virtual string decrypt(string cipher_text);
};

class VigenereCipher : public StreamCipher {
 private:
  int get_next_shift(size_t round, string &plain_text, string &cipher_text);
 public:
  VigenereCipher(string keyword) : StreamCipher(keyword) {};
};

class BeaufortCipher : public StreamCipher {
 private:
  int get_next_shift(size_t round, string &plain_text, string &cipher_text);
 public:
  BeaufortCipher(string keyword) : StreamCipher(keyword) {};
  string encrypt(string plain_text);
  string decrypt(string cipher_text);
};

class AutoKeyPlainTextCipher : public StreamCipher {
 private:
  int get_next_shift(size_t round, string &plain_text, string &cipher_text);
 public:
  AutoKeyPlainTextCipher(string keyword) : StreamCipher(keyword) {};
};

class AutoKeyCipherTextCipher : public StreamCipher {
 private:
  int get_next_shift(size_t round, string &plain_text, string &cipher_text);
 public:
  AutoKeyCipherTextCipher(string keyword) : StreamCipher(keyword) {};
};

#endif