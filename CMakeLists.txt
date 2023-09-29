cmake_minimum_required(VERSION 3.26)

project(Cryptology)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(CryptologyLib STATIC cryptology/src/algebra/algorithms.cpp
        cryptology/include/cryptology/algebra/algorithms.hpp
        cryptology/src/algebra/matrix.cpp
        cryptology/include/cryptology/algebra/matrix.hpp
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

add_executable(Cryptology main.cpp)

target_include_directories(CryptologyLib PUBLIC cryptology/include)
target_include_directories(Cryptology PUBLIC cryptology/include)

target_link_libraries(Cryptology LINK_PUBLIC CryptologyLib)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


enable_testing()

add_executable(
  test_algorithms
  cryptology/tests/algebra/test_algorithms.cpp
)
target_link_libraries(
        test_algorithms
  GTest::gtest_main CryptologyLib
)

add_executable(
  test_stream_cipher
  cryptology/tests/ciphers/test_stream_cipher.cpp
)

target_link_libraries(
  test_stream_cipher
  GTest::gtest_main CryptologyLib
)

add_executable(
  test_affine_cipher
  cryptology/tests/ciphers/test_affine_cipher.cpp
)

target_link_libraries(
  test_affine_cipher
  GTest::gtest_main CryptologyLib
)

add_executable(
  test_hill_cipher
  cryptology/tests/ciphers/test_hill_cipher.cpp
)

target_link_libraries(
  test_hill_cipher
  GTest::gtest_main CryptologyLib
)

add_executable(
  test_matrix
  cryptology/tests/algebra/test_matrix.cpp
)

target_link_libraries(
  test_matrix
  GTest::gtest_main CryptologyLib
)

add_executable(
  test_vector
  cryptology/tests/algebra/test_vector.cpp
)

target_link_libraries(
  test_vector
  GTest::gtest_main CryptologyLib
)

include(GoogleTest)
gtest_discover_tests(test_algorithms)

target_include_directories(test_algorithms PUBLIC cryptology/include)
target_include_directories(test_stream_cipher PUBLIC cryptology/include)
target_include_directories(test_affine_cipher PUBLIC cryptology/include)
target_include_directories(test_hill_cipher PUBLIC cryptology/include)
target_include_directories(test_matrix PUBLIC cryptology/include)
target_include_directories(test_vector PUBLIC cryptology/include)