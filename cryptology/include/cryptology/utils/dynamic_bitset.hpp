#ifndef CRYPTOLOGY_DYNAMIC_BITSET_HPP
#define CRYPTOLOGY_DYNAMIC_BITSET_HPP

#include <stdexcept>
#include <vector>
#include <iterator>

class DynamicBitset {
public:
    DynamicBitset(size_t size);

    DynamicBitset(const std::string &binaryString);

    DynamicBitset(uint64_t value, size_t size);

    void set(size_t index);

    void clear(size_t index);

    bool test(size_t index) const;

    size_t size() const;

    uint64_t to_uint64() const;

    void print() const;

    DynamicBitset operator+(const DynamicBitset &rhs) const;

    bool operator*(const DynamicBitset &rhs) const;

    DynamicBitset concat(const DynamicBitset &rhs) const;

    DynamicBitset slice(size_t i, size_t j) const;

    bool is_zero();

private:
    std::vector<uint8_t> bits_;
    size_t size_;
};

#endif //CRYPTOLOGY_DYNAMIC_BITSET_HPP
