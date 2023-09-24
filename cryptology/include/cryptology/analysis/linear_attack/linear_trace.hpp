#ifndef CRYPTOLOGY_LINEAR_TRACE_HPP
#define CRYPTOLOGY_LINEAR_TRACE_HPP

#include <cryptology/analysis/linear_attack/linear_approximation.hpp>
#include <vector>

using namespace std;

class LinearTrace {
   private:
    double bias = 0.5;
    vector<RoundLinearApproximation> data;
    DynamicBitset input;

   public:
    LinearTrace(DynamicBitset input);

    void add(RoundLinearApproximation round_linear_approximation);

    double GetBias() const;

    double GetNecessaryPairs() const;

    DynamicBitset GetActiveOuput(size_t round) const;

    void print() const;

    DynamicBitset GetInput() const;

    bool operator<(const LinearTrace &other) const { return this->bias < other.bias; }
};

#endif  // CRYPTOLOGY_LINEAR_TRACE_HPP
