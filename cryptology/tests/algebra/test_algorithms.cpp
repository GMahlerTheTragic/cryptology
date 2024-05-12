#include "cryptology/algebra/algorithms.hpp"
#include "gtest/gtest.h"

TEST(ModTest, ModTest) {
    EXPECT_EQ(Mod(0, 3), 0);
    EXPECT_EQ(Mod(10, 3), 1);
    EXPECT_EQ(Mod(11, 3), 2);
    EXPECT_EQ(Mod(12, 3), 0);
    EXPECT_EQ(Mod(-10, 3), 2);
    EXPECT_THROW(Mod(3, 0), std::runtime_error);
}

TEST(IsInvertibleTest, IsInvertibleTest) {
    EXPECT_TRUE(IsInvertible(3, 7));
    EXPECT_FALSE(IsInvertible(4, 6));
    EXPECT_FALSE(IsInvertible(0, 6));
    EXPECT_THROW(IsInvertible(3, 0), std::runtime_error);
}

TEST(EuclidTest, EuclidTest) {
    EXPECT_EQ(Euclid(10, 3), 1);
    EXPECT_EQ(Euclid(15, 5), 5);
    EXPECT_EQ(Euclid(693, 147), 21);
    EXPECT_THROW(Euclid(3, 0), std::runtime_error);
    EXPECT_THROW(Euclid(0, 3), std::runtime_error);
}

TEST(ExtendedEuclidTest, ExtendedEuclidTest) {
    GcdDecomposition result = ExtendedEuclid(10, 3);
    std::cout << "gcd " << result.gcd << "fl: " << result.factor_left << "fr: " << result.factor_right << std::endl;
    EXPECT_EQ(result.gcd, 1);
    EXPECT_EQ(result.factor_left, 1);
    EXPECT_EQ(result.factor_right, -3);
    result = ExtendedEuclid(693, 147);
    std::cout << "gcd " << result.gcd << "fl: " << result.factor_left << "fr: " << result.factor_right << std::endl;
    EXPECT_EQ(result.gcd, 21);
    EXPECT_EQ(result.factor_left, 3);
    EXPECT_EQ(result.factor_right, -14);
    EXPECT_THROW(ExtendedEuclid(3, 0), std::runtime_error);
    EXPECT_THROW(ExtendedEuclid(0, 3), std::runtime_error);
}

TEST(InverseTest, InverseTest) {
    EXPECT_EQ(Inverse(11, 26), 19);
    EXPECT_EQ(Inverse(25, 26), 25);
    EXPECT_THROW(Inverse(3, 0), std::runtime_error);
    EXPECT_THROW(Inverse(6, 3), std::runtime_error);
}

TEST(InverseMatrixTest, InverseMatrixTest) {
    Matrix<26> h = Matrix<26>({{11, 13, 8, 21}, {24, 17, 3, 25}, {18, 12, 23, 17}, {6, 15, 2, 15}});
    Matrix<26> h_inv =
        Matrix<26>({{15, 4, 6, 21}, {8, 13, 13, 20}, {22, 9, 18, 17}, {16, 5, 3, 11}});
    Matrix<26> k = Matrix<26>({{13, 2, 2}, {2, 13, 2}, {13, 2, 13}});
    Matrix<26> k_inv = Matrix<26>({{19, 20, 20}, {0, 13, 20}, {7, 0, 19}});
    Matrix<26> not_invertable = Matrix<26>({{19, 20, 20}, {19, 20, 20}, {7, 0, 19}});

    EXPECT_EQ(Inverse(h), h_inv);
    EXPECT_EQ(Inverse(k), k_inv);
    EXPECT_THROW(Inverse(not_invertable), std::runtime_error);
}

TEST(DeterminantTest, DeterminantTest) {
    Matrix<26> h = Matrix<26>({{2, 14, 13}, {21, 4, 17}, {18, 0, 19}});
    Matrix<26> k = Matrix<26>({{7, 8, 0}, {17, 17, 19}, {13, 20, 24}});
    EXPECT_EQ(Determinant(h), 20);
    EXPECT_EQ(Determinant(k), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
