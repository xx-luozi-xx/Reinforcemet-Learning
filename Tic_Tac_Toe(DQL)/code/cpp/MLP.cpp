#pragma once

#include "MLP.h"

#include "luozilib.h"   //rand(double)

#include <algorithm>    //max()
#include <assert.h>     //assert()

namespace DL{

MLP::MLP(const std::vector<size_t>& shape):
    shape_(shape),
    parameters_()    
{
    //parameters_[0] is meaningless
    parameters_.push_back(std::vector<std::vector<double>>(1, std::vector<double>(1, 0)));

    for(size_t i = 1; i < shape.size(); ++i){
        //parameters_[i] is shape[i]*shape[i-1]+1 matrices
        parameters_.push_back(std::vector<std::vector<double>>(shape[i], std::vector<double>(shape[i-1]+1, 0)));
        for(size_t j = 0; j < parameters_[i].size(); ++j){
            for(size_t k = 0; k < parameters_[i][j].size(); ++k){
                parameters_[i][j][k] = luozi::rand(1.0);
            }
        }
    }
}

std::vector<double> MLP::val(const std::vector<double>& input)const{
    assert(input.size() ==  input_dim());

    //Rolling Array Optimization
    std::vector<double> last_layer, ret;
    for(size_t i = 1; i < shape().size(); ++i){
        last_layer = ret;
        ret = std::vector<double>(shape()[i], 0);

        const std::vector<double>& src_layer = (i==1?input: last_layer);

        //todo CUDA Optimization
        for(size_t j = 0; j < shape()[i]; ++j){
            for(size_t k = 0; k < shape()[i-1]; ++k){
                ret[j] += src_layer[k]*parameters_[i][j][k];
            }
            //adding b
            ret[j] += parameters_[i][j][shape()[i-1]];
            //ReLU func
            ret[j] = std::max(0.0, ret[j]);
        }
    }
    return ret;
}

void MLP::learn(const std::vector<double>& input, const std::vector<double>& real_val){
    assert(input.size() == input_dim());
    assert(real_val.size() == output_dim());




    
}


size_t MLP::input_dim()const{
    return shape().front();
}

size_t MLP::output_dim()const{
    return shape().back();
}

std::vector<size_t> MLP::shape()const{
    return shape_;
}


}//namespace