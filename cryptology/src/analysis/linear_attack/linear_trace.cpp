#include <cryptology/analysis/linear_attack/linear_trace.hpp>
#include <cryptology/analysis/linear_attack/linear_approximation.hpp>
#include <iostream>
#include <cmath>

using namespace std;

LinearTrace::LinearTrace(DynamicBitset input) : input(input) {
    this->input = input;
}

void LinearTrace::add(RoundLinearApproximation round_approximation) {
    this->data.push_back(round_approximation);
    for (auto linear_approximation: round_approximation
            .linear_approximations) {
        this->bias *= linear_approximation.bias;
        this->bias *= 2;
    }
}

double LinearTrace::get_bias() {
    return this->bias;
}

double LinearTrace::get_necessary_pairs() {
    return std::pow(bias, -3);
}

DynamicBitset LinearTrace::get_active_output(size_t round) {
    return this->data[round].active_outputs;
}

DynamicBitset LinearTrace::get_input() {
    return this->input;
}

void LinearTrace::print() {
    cout << "{" << endl;
    cout << "   lenght: " << this->data.size() << "," << endl;
    cout << "   bias: " << this->bias << "," << endl;
    cout << "   input vector: ";
    this->input.print();
    cout << "   active vectors: [" << endl;
    for (auto r: this->data) {
        cout << "      {" << endl;
        cout << "          round: " << r.round << "," << endl;
        cout << "          active_output: ";
        r.active_outputs.print();
        cout << "      }" << endl;
    }
    cout << "   ]" << endl;
    cout << "}" << endl;
}
