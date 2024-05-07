#pragma once
#include <vector>
#include <string>

namespace DL{

class MLP{
public:
    MLP(const std::vector<size_t>& shape);
    MLP(const std::string& file_name);

    std::vector<double> val(const std::vector<double>& input)const;
    const std::vector<size_t>& shape()const;
    //return loss
    double learn(const std::vector<double>& input, const std::vector<double>& real_val, double learning_rate);

    size_t input_dim()const;
    size_t output_dim()const;

    void save(const std::string& file_name)const;
    void load(const std::string& file_name);

protected:
    std::vector<size_t> shape_;

    //parameters_[Layer][Neuron][edge]
    std::vector<std::vector<std::vector<double>>> parameters_;
};


}//namespace