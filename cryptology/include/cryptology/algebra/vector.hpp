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
    Vector(size_t size, int default_value = 0);

    Vector(const std::vector<int> &values);

    ~Vector() = default;

    void print() const;

    Vector operator*(const Matrix<modulus> &rhs) const;

    Vector operator+(const Vector &rhs) const;

    Vector operator*(const int64_t &rhs) const;

    Vector operator-(const Vector &rhs) const;

    [[nodiscard]] size_t size() const { return this->_size; }

    bool operator==(const Vector &rhs) const;

    int64_t operator()(size_t idx) const;

    int &operator()(size_t idx);
};

#endif