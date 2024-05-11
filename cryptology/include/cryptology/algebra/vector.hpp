#ifndef CRYPTOLOGY_ALGEBRA_VECTOR_HPP_
#define CRYPTOLOGY_ALGEBRA_VECTOR_HPP_

#include <vector>

using namespace std;

template <int modulus>
class Matrix;

template <int modulus>
class Vector final {
   private:
    size_t _size{};
    vector<int> values;

   public:
    explicit Vector<modulus>(size_t size, int default_value = 0);

    explicit Vector<modulus>(const std::vector<int> &values);

    ~Vector<modulus>() = default;

    void print() const;

    Vector<modulus> operator*(const Matrix<modulus> &rhs) const;

    Vector<modulus> operator+(const Vector<modulus> &rhs) const;

    Vector<modulus> operator*(const int64_t &rhs) const;

    Vector<modulus> operator-(const Vector<modulus> &rhs) const;

    [[nodiscard]] size_t size() const { return this->_size; }

    bool operator==(const Vector<modulus> &rhs) const;

    int64_t operator()(size_t idx) const;

    int &operator()(size_t idx);
};

#endif