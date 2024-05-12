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
    explicit LinearTrace(DynamicBitset input);

    void add(const RoundLinearApproximation &round_linear_approximation);

    [[nodiscard]] double GetBias() const;

    [[nodiscard]] double GetNecessaryPairs() const;

    [[nodiscard]] DynamicBitset GetActiveOuput(size_t round) const;

    void print() const;

    [[nodiscard]] DynamicBitset GetInput() const;

    bool operator<(const LinearTrace &other) const { return this->bias < other.bias; }
};

#endif
