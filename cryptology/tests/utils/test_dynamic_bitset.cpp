#include "cryptology/utils/dynamic_bitset.hpp"
#include "gtest/gtest.h"

class DynamicBitsetTest : public ::testing::Test {
   protected:
    DynamicBitset bitset = DynamicBitset(10);

    void TearDown() override { bitset = DynamicBitset(10); }
};

TEST_F(DynamicBitsetTest, ConstructorSize) { EXPECT_EQ(bitset.size(), 10); }

TEST_F(DynamicBitsetTest, ConstructorBinaryString) {
    DynamicBitset binary_bitset = DynamicBitset("10101010");
    for (size_t i = 0; i < binary_bitset.size(); ++i) {
        if (i % 2 == 0) {
            EXPECT_FALSE(binary_bitset.test(i));
        } else {
            EXPECT_TRUE(binary_bitset.test(i));
        }
    }
}

TEST_F(DynamicBitsetTest, ConstructorUint64) {
    DynamicBitset uint64_bitset(42, 6);
    for (size_t i = 0; i < uint64_bitset.size(); ++i) {
        if (i == 1 || i == 3 || i == 5) {
            EXPECT_TRUE(uint64_bitset.test(i));
        } else {
            EXPECT_FALSE(uint64_bitset.test(i));
        }
    }
}

TEST_F(DynamicBitsetTest, SetBit) {
    bitset.set(5);
    EXPECT_TRUE(bitset.test(5));

    bitset.clear(5);
    EXPECT_FALSE(bitset.test(5));

    EXPECT_THROW(bitset.set(20), std::out_of_range);
}

// TEST_F(DynamicBitsetTest, Print) {
//     std::stringstream buffer;
//     std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
//     DynamicBitset binary_bitset = DynamicBitset("10101010");
//     binary_bitset.print();
//     std::cout.rdbuf(oldCout);
//     std::string output = buffer.str();
//     EXPECT_EQ(output, "10101010");
// }

TEST_F(DynamicBitsetTest, OperatorPlus) {
    DynamicBitset bitset2 = DynamicBitset("1010101010");
    DynamicBitset result = bitset + bitset2;
    for (size_t i = 0; i < bitset2.size(); ++i) {
        if (i % 2 == 0) {
            EXPECT_FALSE(result.test(i));
        } else {
            EXPECT_TRUE(result.test(i));
        }
    }
}

TEST_F(DynamicBitsetTest, Concat) {
    DynamicBitset bitset2 = DynamicBitset("1010101010");
    DynamicBitset result = bitset.concat(bitset2);
    for (size_t i = 0; i < result.size(); ++i) {
        if (i < bitset.size()) {
            EXPECT_EQ(result.test(i), bitset.test(i));
        } else {
            EXPECT_EQ(result.test(i), bitset2.test(i - bitset.size()));
        }
    }
}

TEST_F(DynamicBitsetTest, Slice) {
    DynamicBitset result = bitset.slice(2, 6);
    for (size_t i = 0; i < result.size(); ++i) {
        if (i >= 2 && i < 6) {
            EXPECT_EQ(result.test(i - 2), bitset.test(i));
        } else {
            EXPECT_FALSE(result.test(i));
        }
    }
}

TEST_F(DynamicBitsetTest, OperatorMultiply) {
    DynamicBitset bitset1 = DynamicBitset("1010101010");
    DynamicBitset bitset2 = DynamicBitset("1010101010");
    bool result = bitset1 * bitset2;
    EXPECT_TRUE(result);
    bool result2 = bitset * bitset2;
    EXPECT_FALSE(result2);
}

TEST_F(DynamicBitsetTest, IsZero) {
    auto bitset1 = DynamicBitset("0000000000");
    EXPECT_TRUE(bitset1.is_zero());
    bitset1.set(5);
    EXPECT_FALSE(bitset1.is_zero());
}

TEST_F(DynamicBitsetTest, EqulityI) {
    const auto bitset1 = DynamicBitset("1010101010");
    const auto bitset2 = DynamicBitset("1010101010");
    EXPECT_TRUE(bitset1 == bitset2);
}

TEST_F(DynamicBitsetTest, EqulityII) {
    DynamicBitset bitset1 = DynamicBitset("1010111010");
    DynamicBitset bitset2 = DynamicBitset("1010101010");
    EXPECT_FALSE(bitset1 == bitset2);
}

TEST_F(DynamicBitsetTest, EqulityIII) {
    DynamicBitset bitset1 = DynamicBitset("10101110");
    DynamicBitset bitset2 = DynamicBitset("1010101010");
    EXPECT_FALSE(bitset1 == bitset2);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
