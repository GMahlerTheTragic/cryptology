#ifndef CRYPTOLOGY_DYNAMIC_BITSET_HPP
#define CRYPTOLOGY_DYNAMIC_BITSET_HPP

#include <vector>
#include <iostream>


class DynamicBitset {
   public:
    explicit DynamicBitset(size_t size);

    explicit DynamicBitset(const std::string &binaryString);

    DynamicBitset(uint64_t value, size_t size);

    void set(size_t index);

    void clear(size_t index);

    [[nodiscard]] bool test(size_t index) const;

    [[nodiscard]] size_t size() const;

    [[nodiscard]] uint64_t to_uint64() const;

    void print() const;

    DynamicBitset operator+(const DynamicBitset &rhs) const;

    bool operator*(const DynamicBitset &rhs) const;

    [[nodiscard]] DynamicBitset concat(const DynamicBitset &rhs) const;

    [[nodiscard]] DynamicBitset slice(size_t i, size_t j) const;

    [[nodiscard]] bool is_zero() const;

    bool operator==(const DynamicBitset &rhs) const;

   private:
    std::vector<uint8_t> bits_;
    size_t size_;
};

#endif  // CRYPTOLOGY_DYNAMIC_BITSET_HPP
