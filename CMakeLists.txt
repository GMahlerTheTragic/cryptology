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
        cryptology/src/utils/utils.cpp
        cryptology/include/cryptology/utils/utils.hpp
        cryptology/include/cryptology/analysis/analysis.hpp
        cryptology/include/cryptology/ciphers/sp_network/sbox.hpp
        cryptology/include/cryptology/ciphers/sp_network/pbox.hpp
        cryptology/include/cryptology/ciphers/sp_network/sp_network.hpp
        cryptology/include/cryptology/ciphers/key_schedules/key_schedules.hpp
        cryptology/include/cryptology/utils/dynamic_bitset.hpp
        cryptology/src/utils/dynamic_bitset.cpp
        cryptology/src/ciphers/sp_network/pbox.cpp
        cryptology/src/ciphers/sp_network/sbox.cpp
        cryptology/src/ciphers/sp_network/sp_network.cpp
        cryptology/include/cryptology/analysis/linear_attack/linear_trace.hpp
        cryptology/include/cryptology/analysis/linear_attack/linear_approximation.hpp
        cryptology/src/analysis/linear_attack/linear_trace.cpp
        cryptology/src/analysis/linear_attack/linear_attack_worker.cpp
        cryptology/include/cryptology/analysis/linear_attack/linear_attack_worker.hpp)

add_executable(Cryptology main.cpp
        cryptology/src/algebra/algorithms.cpp
        cryptology/include/cryptology/analysis/linear_attack/linear_trace.hpp)

target_include_directories(CryptologyLib PUBLIC cryptology/include)
target_include_directories(Cryptology PUBLIC cryptology/include)

target_link_libraries(Cryptology LINK_PUBLIC CryptologyLib)
