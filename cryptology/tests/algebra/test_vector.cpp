#include <iostream>
#include <sstream>
#include <vector>

#include "cryptology/algebra/matrix.hpp"
#include "gtest/gtest.h"

TEST(VectorTest, PrintTest) {
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
    Vector<26> h = Vector<26>({11, 13, 8, 21});
    h.print();
    std::cout.rdbuf(oldCout);
    std::string output = buffer.str();
    EXPECT_EQ(output, "[ 11, 13, 8, 21, ]\n");
}

TEST(MatrixTest, VectorMatrixProduct) {
    Vector<26> left = Vector<26>({11, 13, 8, 21});
    Matrix<26> right = Matrix<26>({{2, 1, 2, 2}, {2, 1, 2, 6}, {1, 2, 3, 1}, {2, 1, 2, 2}});
    Vector<26> result = Vector<26>({20, 9, 10, 20});
    (left * right).print();
    EXPECT_EQ(left * right, result);
}

TEST(MatrixTest, VectorMatrixProductDimensionMismatch) {
    Vector<26> left = Vector<26>({11, 13, 8, 21});
    Matrix<26> right = Matrix<26>({{2, 1, 2}, {2, 1, 2}});
    EXPECT_THROW(left * right, std::runtime_error);
}

TEST(MatrixTest, ScalarMultiplication) {
    Vector<26> left = Vector<26>({11, 13, 8, 21});
    Vector<26> result = Vector<26>({22, 0, 16, 16});
    EXPECT_EQ(left * 2, result);
}

TEST(MatrixTest, Addition) {
    Vector<26> left = Vector<26>({11, 13, 8, 21});
    Vector<26> right = Vector<26>({2, 3, 2, 5});
    Vector<26> result = Vector<26>({13, 16, 10, 0});
    EXPECT_EQ(left + right, result);
}

TEST(MatrixTest, AdditionDimensionMismatch) {
    Vector<26> left = Vector<26>({11, 13, 8, 21});
    Vector<26> right = Vector<26>({2, 3, 2});
    EXPECT_THROW(left + right, std::runtime_error);
}

TEST(MatrixTest, Subtraction) {
    Vector<26> left = Vector<26>({11, 13, 8, 21});
    Vector<26> right = Vector<26>({2, 3, 2, 5});
    Vector<26> result = Vector<26>({9, 10, 6, 16});
    EXPECT_EQ(left - right, result);
}

TEST(MatrixTest, SubtractionDimensionMismatch) {
    Vector<26> left = Vector<26>({11, 13, 8, 21});
    Vector<26> right = Vector<26>({2, 3, 2});
    EXPECT_THROW(left - right, std::runtime_error);
}

TEST(MatrixTest, Indexing) {
    Vector<26> left = Vector<26>({11, 13, 8, 21});
    EXPECT_EQ(left(0), 11);
    EXPECT_EQ(left(1), 13);
    EXPECT_EQ(left(2), 8);
    EXPECT_EQ(left(3), 21);
}

TEST(MatrixTest, IndexingOutofBoundI) {
    Vector<26> left = Vector<26>({11, 13, 8, 21});
    EXPECT_THROW(left(4), std::runtime_error);
}

TEST(MatrixTest, IndexingOutofBoundII) {
    Vector<26> left = Vector<26>({11, 13, 8, 21});
    EXPECT_THROW(left(-1), std::runtime_error);
}

TEST(MatrixTest, EqualityI) {
    Vector<26> left = Vector<26>({11, 13, 8, 21});
    Vector<26> right = Vector<26>({11, 13, 8, 21});
    EXPECT_TRUE(left == right);
}

TEST(MatrixTest, EqualityII) {
    Vector<26> left = Vector<26>({11, 13, 8, 21});
    Vector<26> right = Vector<26>({11, 5, 8, 21});
    EXPECT_FALSE(left == right);
}

TEST(MatrixTest, size) {
    Vector<26> left = Vector<26>({11, 13, 8, 21});
    EXPECT_EQ(left.size(), 4);
    left = Vector<26>({});
    EXPECT_EQ(left.size(), 0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
