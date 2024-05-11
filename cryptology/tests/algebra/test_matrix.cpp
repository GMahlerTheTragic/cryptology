#include <iostream>
#include <sstream>
#include <vector>

#include "cryptology/algebra/matrix.hpp"
#include "gtest/gtest.h"

TEST(MatrixTest, PrintTest) {
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
    const auto h = Matrix<26>({{11, 13, 8, 21}, {24, 17, 3, 25}, {18, 12, 23, 17}, {6, 15, 2, 15}});
    h.print();
    std::cout.rdbuf(oldCout);
    const std::string output = buffer.str();
    EXPECT_EQ(
        output,
        "[\n[ 11, 13, 8, 21, ]\n[ 24, 17, 3, 25, ]\n[ 18, 12, 23, 17, ]\n[ 6, 15, 2, 15, ]\n]\n");
}

TEST(MatrixTest, MatrixProduct) {
    Matrix<26> left = Matrix<26>({{11, 13, 8}, {24, 17, 3}, {18, 12, 23}});
    Matrix<26> right = Matrix<26>({{2, 1, 2}, {2, 1, 2}, {1, 2, 3}});
    Matrix<26> result = Matrix<26>({{4, 14, 20}, {7, 21, 13}, {5, 24, 25}});
    EXPECT_EQ(left * right, result);
}

TEST(MatrixTest, MatrixProductDimensionMismatch) {
    Matrix<26> left = Matrix<26>({{11, 13, 8}, {24, 17, 3}, {18, 12, 23}});
    Matrix<26> right = Matrix<26>({{2, 1, 2}, {2, 1, 2}});
    EXPECT_THROW(left * right, std::runtime_error);
}

TEST(MatrixTest, MatrixVectorProduct) {
    Matrix<26> left = Matrix<26>({{11, 13, 8}, {24, 17, 3}, {18, 12, 23}});
    Vector<26> right = Vector<26>({2, 1, 2});
    Vector<26> result = Vector<26>({25, 19, 16});
    EXPECT_EQ(left * right, result);
}

TEST(MatrixTest, MatrixVectorProductDimensionMismatchI) {
    Matrix<26> left = Matrix<26>({{11, 13, 8}, {24, 17, 3}, {18, 12, 23}});
    Matrix<26> right = Matrix<26>({2, 1});
    EXPECT_THROW(left * right, std::runtime_error);
}

TEST(MatrixTest, MatrixVectorProductDimensionMismatchII) {
    Matrix<26> left = Matrix<26>({{11, 13, 8}, {24, 17, 3}, {18, 12, 23}});
    Matrix<26> right = Matrix<26>({2, 1});
    EXPECT_THROW(left * right, std::runtime_error);
}

TEST(MatrixTest, ScalarMultiplication) {
    Matrix<26> left = Matrix<26>({{11, 13, 8}, {12, 17, 3}, {18, 12, 11}});
    Matrix<26> result = Matrix<26>({{22, 0, 16}, {24, 8, 6}, {10, 24, 22}});
    EXPECT_EQ(left * 2, result);
}

TEST(MatrixTest, Addition) {
    Matrix<26> left = Matrix<26>({{11, 13, 8}, {12, 17, 3}, {18, 1, 11}});
    Matrix<26> right = Matrix<26>({{1, 13, 3}, {3, 1, 3}, {18, 12, 11}});
    Matrix<26> result = Matrix<26>({{12, 0, 11}, {15, 18, 6}, {10, 13, 22}});
    EXPECT_EQ(left + right, result);
}

TEST(MatrixTest, AdditionDimensionMismatchI) {
    Matrix<26> left = Matrix<26>({{11, 13, 8}, {12, 17, 3}, {18, 12, 11}});
    Matrix<26> right = Matrix<26>({{3, 1, 3}, {18, 12, 11}});
    EXPECT_THROW(left + right, std::runtime_error);
}

TEST(MatrixTest, AdditionDimensionMismatchII) {
    Matrix<26> left = Matrix<26>({{11, 13, 8}, {12, 17, 3}, {18, 12, 11}});
    Matrix<26> right = Matrix<26>({{1, 13}, {1, 3}, {12, 11}});
    EXPECT_THROW(left + right, std::runtime_error);
}

TEST(MatrixTest, Subtraction) {
    Matrix<26> left = Matrix<26>({{11, 13, 8}, {12, 17, 3}, {18, 1, 11}});
    Matrix<26> right = Matrix<26>({{1, 13, 3}, {3, 1, 3}, {18, 12, 11}});
    Matrix<26> result = Matrix<26>({{10, 0, 5}, {9, 16, 0}, {0, 15, 0}});
    EXPECT_EQ(left - right, result);
}

TEST(MatrixTest, SubtractionDimensionMismatch) {
    Matrix<26> left = Matrix<26>({{11, 13, 8}, {12, 17, 3}, {18, 12, 11}});
    Matrix<26> right = Matrix<26>({{3, 1, 3}, {18, 12, 11}});
    EXPECT_THROW(left - right, std::runtime_error);
}

TEST(MatrixTest, SubtractionDimensionMismatchII) {
    Matrix<26> left = Matrix<26>({{11, 13, 8}, {12, 17, 3}, {18, 12, 11}});
    Matrix<26> right = Matrix<26>({{1, 13}, {1, 3}, {12, 11}});
    EXPECT_THROW(left - right, std::runtime_error);
}

TEST(MatrixTest, Indexing) {
    Matrix<26> left = Matrix<26>({{11, 13, 8}, {12, 17, 3}, {18, 12, 11}});
    EXPECT_EQ(left(0, 0), 11);
    EXPECT_EQ(left(0, 1), 13);
    EXPECT_EQ(left(0, 2), 8);
    EXPECT_EQ(left(1, 0), 12);
    EXPECT_EQ(left(1, 1), 17);
    EXPECT_EQ(left(1, 2), 3);
    EXPECT_EQ(left(2, 0), 18);
    EXPECT_EQ(left(2, 1), 12);
    EXPECT_EQ(left(2, 2), 11);
}

TEST(MatrixTest, IndexingOutofBoundI) {
    Matrix<26> left = Matrix<26>({{11, 13, 8}, {12, 17, 3}, {18, 12, 11}});
    EXPECT_THROW(left(3, 0), std::runtime_error);
}

TEST(MatrixTest, IndexingOutofBoundII) {
    Matrix<26> left = Matrix<26>({{11, 13, 8}, {12, 17, 3}, {18, 12, 11}});
    EXPECT_THROW(left(0, 3), std::runtime_error);
}

TEST(MatrixTest, IndexingOutofBoundIII) {
    Matrix<26> left = Matrix<26>({{11, 13, 8}, {12, 17, 3}, {18, 12, 11}});
    EXPECT_THROW(left(-1, 2), std::runtime_error);
}

TEST(MatrixTest, EqualityI) {
    Matrix<26> left = Matrix<26>({{11, 13, 8}, {12, 17, 3}, {18, 12, 11}});
    Matrix<26> right = Matrix<26>({{11, 13, 8}, {12, 17, 3}, {18, 12, 11}});
    EXPECT_TRUE(left == right);
}

TEST(MatrixTest, EqualityII) {
    Matrix<26> left = Matrix<26>({{11, 13, 8}, {12, 17, 3}, {18, 12, 11}});
    Matrix<26> right = Matrix<26>({{11, 1, 8}, {12, 17, 3}, {18, 12, 11}});
    EXPECT_FALSE(left == right);
}

TEST(MatrixTest, GetCol) {
    Matrix<26> left = Matrix<26>({{11, 13, 8}, {12, 17, 3}, {18, 12, 11}});
    ASSERT_EQ(left.get_col(0), Vector<26>({11, 12, 18}));
    ASSERT_EQ(left.get_col(1), Vector<26>({13, 17, 12}));
    ASSERT_EQ(left.get_col(2), Vector<26>({8, 3, 11}));
}

TEST(MatrixTest, GetColOutOfBoundsI) {
    Matrix<26> left = Matrix<26>({{11, 13, 8}, {12, 17, 3}, {18, 12, 11}});
    EXPECT_THROW(left.get_col(3), std::runtime_error);
}

TEST(MatrixTest, GetColOutOfBoundsII) {
    Matrix<26> left = Matrix<26>({{11, 13, 8}, {12, 17, 3}, {18, 12, 11}});
    EXPECT_THROW(left.get_col(-1), std::runtime_error);
}

TEST(MatrixTest, GetRow) {
    Matrix<26> left = Matrix<26>({{11, 13, 8}, {12, 17, 3}, {18, 12, 11}});
    ASSERT_EQ(left.get_row(0), Vector<26>({11, 13, 8}));
    ASSERT_EQ(left.get_row(1), Vector<26>({12, 17, 3}));
    ASSERT_EQ(left.get_row(2), Vector<26>({18, 12, 11}));
}

TEST(MatrixTest, GetRowOutOfBoundsI) {
    Matrix<26> left = Matrix<26>({{11, 13, 8}, {12, 17, 3}, {18, 12, 11}});
    EXPECT_THROW(left.get_row(3), std::runtime_error);
}

TEST(MatrixTest, GetRowOutOfBoundsII) {
    Matrix<26> left = Matrix<26>({{11, 13, 8}, {12, 17, 3}, {18, 12, 11}});
    EXPECT_THROW(left.get_row(-1), std::runtime_error);
}

TEST(MatrixTest, SetRow) {
    Matrix<26> left = Matrix<26>({{11, 13, 8}, {12, 17, 3}, {18, 12, 11}});
    left.set_row(0, Vector<26>({1, 1, 1}));
    ASSERT_EQ(left, Matrix<26>({{1, 1, 1}, {12, 17, 3}, {18, 12, 11}}));
    left.set_row(1, Vector<26>({1, 1, 1}));
    ASSERT_EQ(left, Matrix<26>({{1, 1, 1}, {1, 1, 1}, {18, 12, 11}}));
    left.set_row(2, Vector<26>({1, 1, 1}));
    ASSERT_EQ(left, Matrix<26>({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}}));
}

TEST(MatrixTest, SetRowOutOfBoundsI) {
    Matrix<26> left = Matrix<26>({{11, 13, 8}, {12, 17, 3}, {18, 12, 11}});
    EXPECT_THROW(left.set_row(3, Vector<26>({1, 1, 1}));, std::runtime_error);
}

TEST(MatrixTest, SetRowOutOfBoundsII) {
    Matrix<26> left = Matrix<26>({{11, 13, 8}, {12, 17, 3}, {18, 12, 11}});
    EXPECT_THROW(left.set_row(-1, Vector<26>({1, 1, 1}));, std::runtime_error);
}

TEST(MatrixTest, SetRowOutOfBoundsIII) {
    Matrix<26> left = Matrix<26>({{11, 13, 8}, {12, 17, 3}, {18, 12, 11}});
    EXPECT_THROW(left.set_row(1, Vector<26>({1, 1, 1, 1}));, std::runtime_error);
}

TEST(MatrixTest, SetCol) {
    Matrix<26> left = Matrix<26>({{11, 13, 8}, {12, 17, 3}, {18, 12, 11}});
    left.set_col(0, Vector<26>({1, 1, 1}));
    ASSERT_EQ(left, Matrix<26>({{1, 13, 8}, {1, 17, 3}, {1, 12, 11}}));
    left.set_col(1, Vector<26>({1, 1, 1}));
    ASSERT_EQ(left, Matrix<26>({{1, 1, 8}, {1, 1, 3}, {1, 1, 11}}));
    left.set_col(2, Vector<26>({1, 1, 1}));
    ASSERT_EQ(left, Matrix<26>({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}}));
}

TEST(MatrixTest, SetColOutOfBoundsI) {
    Matrix<26> left = Matrix<26>({{11, 13, 8}, {12, 17, 3}, {18, 12, 11}});
    EXPECT_THROW(left.set_col(3, Vector<26>({1, 1, 1}));, std::runtime_error);
}

TEST(MatrixTest, SetColOutOfBoundsII) {
    Matrix<26> left = Matrix<26>({{11, 13, 8}, {12, 17, 3}, {18, 12, 11}});
    EXPECT_THROW(left.set_col(-1, Vector<26>({1, 1, 1}));, std::runtime_error);
}

TEST(MatrixTest, SetColOutOfBoundsIII) {
    Matrix<26> left = Matrix<26>({{11, 13, 8}, {12, 17, 3}, {18, 12, 11}});
    EXPECT_THROW(left.set_col(1, Vector<26>({1, 1, 1, 1}));, std::runtime_error);
}

TEST(MatrixTest, cols) {
    Matrix<26> left = Matrix<26>({{11, 13, 8}, {12, 17, 3}, {18, 12, 11}});
    EXPECT_EQ(left.cols(), 3);
    left = Matrix<26>({});
    EXPECT_EQ(left.cols(), 0);
}

TEST(MatrixTest, rows) {
    Matrix<26> left = Matrix<26>({{11, 13, 8}, {12, 17, 3}, {18, 12, 11}});
    EXPECT_EQ(left.rows(), 3);
    left = Matrix<26>({});
    EXPECT_EQ(left.rows(), 0);
}

TEST(MatrixTest, eye) {
    Matrix<26> eye3 = Matrix<26>({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}});
    EXPECT_EQ(Matrix<26>::eye(3), eye3);
    Matrix<26> eye0 = Matrix<26>({});
    EXPECT_EQ(Matrix<26>::eye(0), eye0);
}

TEST(MatrixTest, ConcatAxis0) {
    Matrix<5> left({{2, 3}});
    Matrix<5> right({{3, 3}});
    Matrix<5> expectedResult({{2, 3}, {3, 3}});
    EXPECT_NO_THROW({
        Matrix<5> result = Matrix<5>::concat(left, right, 0);
        EXPECT_EQ(result, expectedResult);
    });
}

TEST(MatrixTest, ConcatAxis1) {
    Matrix<5> left({{2, 3}});
    Matrix<5> right({{2, 2}});
    Matrix<5> expectedResult({{2, 3, 2, 2}});
    EXPECT_NO_THROW({
        Matrix<5> result = Matrix<5>::concat(left, right, 1);
        EXPECT_EQ(result, expectedResult);
    });
}

TEST(MatrixTest, InvalidAxis) {
    Matrix<5> left({{2, 3}});
    Matrix<5> right({{3, 3}});

    EXPECT_THROW({ Matrix<5> result = Matrix<5>::concat(left, right, 2); }, std::runtime_error);
}

TEST(MatrixTest, InvalidColumnLengths) {
    Matrix<5> left({{2, 3}});
    Matrix<5> right({{3}});

    EXPECT_THROW({ Matrix<5> result = Matrix<5>::concat(left, right, 0); }, std::runtime_error);
}

TEST(MatrixTest, InvalidRowLengths) {
    vector<vector<int>> vals = {{2}, {3}};
    Matrix<5> left = Matrix<5>(vals);
    Matrix<5> right({{3, 3}});

    EXPECT_THROW({ Matrix<5> result = Matrix<5>::concat(left, right, 1); }, std::runtime_error);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
