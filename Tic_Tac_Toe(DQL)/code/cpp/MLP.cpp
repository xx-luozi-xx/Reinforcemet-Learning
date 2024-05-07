#include "MLP.h"

#include "luozilib.h"   //rand(double)

#include <algorithm>    //max()
#include <assert.h>     //assert()
#include <float.h>      //FLT_EPSILON  
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
            if(i != shape().size()-1){
                ret[j] = std::max(0.0, ret[j]);
            }
        }
    }
    return ret;
}

double MLP::learn(const std::vector<double>& input, const std::vector<double>& real_val, double learning_rate){
    assert(input.size() == input_dim());
    assert(real_val.size() == output_dim());

    if(shape().size() <= 1) return -1;

    // for(int i = 9; i < input.size(); ++i){
    //     if(input[i] == 1){
    //         printf("%llf<-%d\n", real_val[0], i-9);
    //         break;
    //     }
    // }

    // printf("\nmake estimate\n");
    std::vector<std::vector<double>> estimate(1, input);
    for(int i = 1; i < shape().size(); ++i){
        estimate.push_back(std::vector<double>(shape()[i], 0));
        for(size_t j = 0; j < shape()[i]; ++j){
            for(size_t k = 0; k < shape()[i-1]; ++k){
                estimate[i][j] += estimate[i-1][k]*parameters_[i][j][k];
            }
            //adding b
            estimate[i][j] += parameters_[i][j][shape()[i-1]];
            //ReLU func
            if(i != shape().size()-1){
                estimate[i][j] = std::max(0.0, estimate[i][j]);
            }
            // printf("[i=%d][j=%d]\n", i, j);
        }
    }

    // printf("make init b\n");
    //init loss
    double loss = 0;
    std::vector<std::vector<std::vector<double>>> grad = parameters_;
    for(size_t i = 0; i < real_val.size(); ++i){
        loss += (estimate.back()[i]-real_val[i])*(estimate.back()[i]-real_val[i]);
        grad.back()[i].back() =  2*(estimate.back()[i]-real_val[i]); 
        //! in this model, without ReLU here
    }

    // printf("make all b\n");
    //make b
    for(size_t i = shape().size()-2; i >= 1; --i){
        for(size_t j = 0; j < shape()[i]; ++j){
            grad[i][j].back() = 0;
            for(size_t k = 0; k < shape()[i+1]; ++k){
                if(estimate[i][j] > FLT_EPSILON){//ReLU, estimate[i][j]>0
                    grad[i][j].back() += grad[i+1][k].back()*parameters_[i+1][k][j];
                }
            }
        }
    }

    // printf("make w\n");
    //make w
    for(size_t i = 1; i < shape().size(); ++i){
        for(size_t j = 0; j < shape()[i]; ++j){
            for(size_t k = 0; k <shape()[i-1]; ++k){
                grad[i][j][k] = grad[i][j].back()*estimate[i-1][k];
            }
        }
    }
    
    // printf("update\n");
    //update
    for(size_t i = 1; i < shape().size(); ++i){
        for(size_t j = 0; j < parameters_[i].size(); ++j){
            for(size_t k = 0; k < parameters_[i][j].size(); ++k){
                parameters_[i][j][k] -= learning_rate*grad[i][j][k];
            }
        }
    }

    // printf("return\n");
    return loss;
}


size_t MLP::input_dim()const{
    return shape().front();
}

size_t MLP::output_dim()const{
    return shape().back();
}

const std::vector<size_t>& MLP::shape()const{
    return shape_;
}


}//namespace