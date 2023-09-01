cmake_minimum_required(VERSION 3.26)

project(Cryptology)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(CryptologyLib STATIC cryptology/src/algebra/algorithms.cpp
        cryptology/include/cryptology/algebra/algorithms.hpp
        cryptology/src/algebra/matrix.cpp
        cryptology/include/cryptology/algebra/matrix.hpp
        cryptology/src/algebra/residue_class.cpp
        cryptology/include/cryptology/algebra/residue_class.hpp
        cryptology/src/algebra/vector.cpp
        cryptology/include/cryptology/algebra/vector.hpp
        cryptology/src/analysis/analysis.cpp
        cryptology/src/analysis/statistics.cpp
        cryptology/include/cryptology/analysis/statistics.hpp
        cryptology/src/ciphers/affine_cipher.cpp
        cryptology/include/cryptology/ciphers/affine_cipher.hpp
        cryptology/src/ciphers/hill_cipher.cpp
        cryptology/include/cryptology/ciphers/hill_cipher.hpp
        cryptology/src/ciphers/stream_cipher.cpp
        cryptology/include/cryptology/ciphers/stream_cipher.hpp
        cryptology/src/utils.cpp
        cryptology/include/cryptology/utils.hpp
        cryptology/include/cryptology/analysis/analysis.hpp)

add_executable(Cryptology main.cpp
        cryptology/src/algebra/algorithms.cpp)

target_include_directories (CryptologyLib PUBLIC cryptology/include)
target_include_directories (Cryptology PUBLIC cryptology/include)

target_link_libraries(Cryptology LINK_PUBLIC CryptologyLib)
