![example workflow](https://github.com/GMahlerTheTragic/cryptology/actions/workflows/cmake-multi-platform.yml/badge.svg)
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=GMahlerTheTragic_cryptology&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=GMahlerTheTragic_cryptology)
[![Coverage](https://sonarcloud.io/api/project_badges/measure?project=GMahlerTheTragic_cryptology&metric=coverage)](https://sonarcloud.io/summary/new_code?id=GMahlerTheTragic_cryptology)
[![Lines of Code](https://sonarcloud.io/api/project_badges/measure?project=GMahlerTheTragic_cryptology&metric=ncloc)](https://sonarcloud.io/summary/new_code?id=GMahlerTheTragic_cryptology)
# Cryptology Learning Library
Welcome to the Cryptology Learning Library! This resource is designed for educational purposes, allowing
you to explore various ciphers and basic attacks on them. Please note that the ciphers provided here are not
intended for production use but are meant to enhance understanding of cryptology concepts.

## Table of Contents
1. [Prerequisites](#prerequisites)
2. [Running the code](#running-the-code)
3. [Running the tests](#running-the-tests)
4. [Affine Cipher](#affine-cipher)
5. [Vigenere Cipher & Other Stream Ciphers (Beaufort and Autokey)](#vigenere-cipher)
6. [Hill Cipher](#hill-cipher)
7. [Substitution Permutation Networks](#substitution-permutation-networks)

## Prerequisites
This library uses the c++20 standard.

You will need:

1. A linux or macOS system with an installation of CMake.

2. If you are using macOS you can use the preinstalled Clang compiler.

3. On Linux you will need the GNU g++ C++ compiler

The library has not been tested on Windows.
The pipeline only checks the above two compilation approaches...

## Running the Code
To build the Cryptology library and run the examples, follow these steps:

1. Clone or download the project repository.

2. Open a terminal or command prompt and navigate to the project's root directory.

3. Build the project using CMake by running the following commands:
   1. On Linux
       ```bash
       mkdir build
       cmake -S . -B build -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc -DCMAKE_BUILD_TYPE=Release
       cmake --build build/ --config Release
       ```
   2. On Mac
       ```bash
       mkdir build
       cmake -S . -B build -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Release
       cmake --build build/ --config Release
       ```

4. Run the example executable of your choice:
   ```bash
    build/SPNExample
    ```

## Running the Tests
To build the Cryptology library and run the examples, follow these steps:

1. Clone or download the project repository.

2. Open a terminal or command prompt and navigate to the project's root directory.

3. Build the project using CMake by running the following commands:
   1. On Linux
       ```bash
       mkdir build
       cmake -S . -B build -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc -DCMAKE_BUILD_TYPE=Release
       cmake --build build/ --config Release
       ```
   2. On Mac
       ```bash
       mkdir build
       cmake -S . -B build -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Release
       cmake --build build/ --config Release
       ```

4. Run the tests using CMake's testing utilities:
   ```bash
   cd build
   ctest --build-config Release --output-on-failure
   ```

### Affine Cipher
The Affine Cipher is a type of substitution cipher that combines the Caesar Cipher with modular arithmetic. Discover how
the Affine Cipher works and how to perform encryption and decryption using its unique mathematical formula.
We implement a Brute Force attack on the Affine cipher. See example below.
Example: `examples/affine_cipher_examples.cpp`
---

### Vigenere Cipher
The Vigenère Cipher is a poly-alphabetic substitution cipher that builds upon the Caesar Cipher. Unlike the Caesar
Cipher, which uses a fixed shift value for each character, the Vigenère Cipher employs a keyword or passphrase to
determine the shift value for each character in the plaintext. This makes it significantly more secure than the simple
Caesar Cipher. We implement an Index of Coincidence based attack on the Vigenere cipher. See example below.
Example: `examples/vigenere_cipher_examples.cpp`
---

### Hill Cipher
The Hill Cipher is a holographic substitution cipher that operates on multiple letters at once. Explore the mathematical
operations behind the Hill Cipher and practice encrypting and decrypting text.
We are yet to implement the well-known n-gram frequency based attack on the Hill Cipher.
Example: `examples/hill_cipher_example.cpp`
---

### Substitution Permutation Networks
Substitution Permutation Networks (SPN) represent a modern approach to block ciphers and symmetric-key encryption.
We implement linear cryptanalysis and demonstrate a successful linear attack on the last round key of an example SPN.
The SPN works on 16 bit inputs and has insecure SBoxes (allowing for linear traces with high bias).
In addition, we assume only 5 rounds with an easy key schedule...
Example: `examples/spn_cipher_example.cpp`
---

## Disclaimer
This Cryptology Learning and Teaching Library is solely for educational purposes and is not intended for use in
production or secure applications. The ciphers presented here may have vulnerabilities and should not be relied upon for
secure communications.

Happy exploring!
