#ifndef CRYPTOLOGY_LINEAR_TRACE_HPP
#define CRYPTOLOGY_LINEAR_TRACE_HPP

#include <vector>
#include <cryptology/analysis/linear_attack/linear_approximation.hpp>

using namespace std;

class LinearTrace {
private:
    double bias = 0.5;
    vector<RoundLinearApproximation> data;
    DynamicBitset input;
public:
    LinearTrace(DynamicBitset input);

    void add(RoundLinearApproximation round_linear_approximation);

    double get_bias();

    double get_necessary_pairs();

    DynamicBitset get_active_output(size_t round);

    void print();

    DynamicBitset get_input();

    bool operator<(const LinearTrace &other) const {
        return this->bias < other.bias;
    }
};

#endif //CRYPTOLOGY_LINEAR_TRACE_HPP
