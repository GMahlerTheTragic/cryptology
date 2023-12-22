#include "cryptology/analysis/linear_attack/linear_trace.hpp"

#include <cmath>
#include <iostream>
#include <stdint.h>

#include "cryptology/analysis/linear_attack/linear_approximation.hpp"
using std::cout;

LinearTrace::LinearTrace(DynamicBitset input) : input(input) {}

void LinearTrace::add(RoundLinearApproximation round_approximation) {
    this->data.push_back(round_approximation);
    for (auto linear_approximation : round_approximation.linear_approximations) {
        this->bias *= linear_approximation.bias;
        this->bias *= 2;
    }
}

double LinearTrace::GetBias() const { return this->bias; }

double LinearTrace::GetNecessaryPairs() const { return std::pow(bias, -3); }

DynamicBitset LinearTrace::GetActiveOuput(size_t round) const {
    return this->data[round].active_outputs;
}

DynamicBitset LinearTrace::GetInput() const { return this->input; }

void LinearTrace::print() const {
    cout << "{" << endl;
    cout << "   lenght: " << this->data.size() << "," << endl;
    cout << "   bias: " << this->bias << "," << endl;
    cout << "   input vector: ";
    this->input.print();
    cout << "   active vectors: [" << endl;
    for (auto round_data : this->data) {
        cout << "      {" << endl;
        cout << "          round: " << round_data.round << "," << endl;
        cout << "          active_output: ";
        round_data.active_outputs.print();
        cout << "      }" << endl;
    }
    cout << "   ]" << endl;
    cout << "}" << endl;
}
