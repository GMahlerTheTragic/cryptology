#include <cryptology/utils/dynamic_bitset.hpp>

#include <iostream>

DynamicBitset::DynamicBitset(size_t size) {
  if (size >= 0) {
    size_ = size;
    bits_.resize((size_ + 7) / 8, 0);
  } else {
    throw std::invalid_argument("Size must be greater than 0");
  }
}

DynamicBitset::DynamicBitset(const std::string &binaryString) {
  size_ = binaryString.size();
  bits_.resize((size_ + 7) / 8, 0);

  for (size_t i = 0; i < size_; ++i) {
    if (binaryString[size_ - 1 - i] == '1') {
      set(i);
    } else if (binaryString[size_ - 1 - i] != '0') {
      throw std::invalid_argument("Invalid character in binary string");
    }
  }
}

DynamicBitset::DynamicBitset(u_int64_t value, size_t size) {
  size_ = size;
  bits_.resize((size_ + 7) / 8, 0);
  uint64_t one = 1;
  for (size_t i = 0; i < this->size_; ++i) {
    if (value & (1ULL << i)) {
      set(i);
    }
  }
}

void DynamicBitset::set(size_t index) {
  if (index < size_) {
    bits_[index / 8] |= (1 << (index % 8));
  } else {
    throw std::out_of_range("Index out of range");
  }
}

void DynamicBitset::clear(size_t index) {
  if (index < size_) {
    bits_[index / 8] &= ~(1 << (index % 8));
  } else {
    throw std::out_of_range("Index out of range");
  }
}

bool DynamicBitset::test(size_t index) const {
  if (index < size_) {
    return (bits_[index / 8] & (1 << (index % 8))) != 0;
  } else {
    throw std::out_of_range("Index out of range");
  }
}

size_t DynamicBitset::size() const {
  return size_;
}

uint64_t DynamicBitset::to_uint64() const {
  if (size_ > sizeof(uint64_t) * 8) {
    throw std::overflow_error(
        "Bitset too large to convert to unsigned long long");
  }

  uint64_t result = 0;
  uint64_t one = 1;
  for (size_t i = 0; i < size_; ++i) {
    if (test(i)) {
      result |= (one << i);
    }
  }
  return result;
}

void DynamicBitset::print() const {
  for (int i = size_ - 1; i >= 0; --i) {
    std::cout << (test(i) ? '1' : '0');
  }
  std::cout << std::endl;
}

DynamicBitset DynamicBitset::operator+(const DynamicBitset &rhs) const {
  if (this->size_ != rhs.size_) {
    throw std::runtime_error("sizes do not match");
  }
  DynamicBitset result = DynamicBitset(this->size_);
  for (size_t i = 0; i < this->bits_.size(); i++) {
    result.bits_[i] = this->bits_[i] ^ rhs.bits_[i];
  }
  return result;
}

DynamicBitset DynamicBitset::concat(const DynamicBitset &rhs) const {
  size_t result_size = this->size_ + rhs.size_;
  DynamicBitset result = DynamicBitset(result_size);
  for (size_t i = 0; i < this->size_; i++) {
    if (this->test(i)) {
      result.set(i);
    }
  }
  for (size_t i = 0; i < rhs.size_; i++) {
    if (rhs.test(i)) {
      result.set(this->size_ + i);
    }
  }
  return result;
}

DynamicBitset DynamicBitset::slice(size_t i, size_t j) const {
  if (i >= j || j > this->size_) {
    throw std::out_of_range("i must be smaller than j and j can be at "
                            "most the length of the Bitset");
  }
  size_t slice_size = j - i;
  DynamicBitset result = DynamicBitset(slice_size);
  for (size_t k = 0; k < slice_size; ++k) {
    if (this->test(i + k)) {
      result.set(k);
    }
  }

  return result;
}

bool DynamicBitset::operator*(const DynamicBitset &rhs) const {
  if (rhs.size() != this->size_) {
    throw std::length_error("size mismatch");
  }
  bool result = 0;
  for (size_t i = 0; i < this->size_; ++i) {
    result = result ^ (this->test(i) && rhs.test(i));
  }
  return result;
}

bool DynamicBitset::is_zero() {
  for (size_t i = 0; i < this->size_; i++) {
    if (this->bits_[i] != 0) {
      return false;
    }
  }
  return true;
}

