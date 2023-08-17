#ifndef POSTPROCESSOR_H
#define POSTPROCESSOR_H

#include <tuple>
#include <vector>
#include <complex>

namespace PostProcessor{
    float lowEnergy(float low_proportion, const std::vector<float>& freq_abs);
    float highEnergy(float high_proportion, const std::vector<float>& freq_abs);
    
    template<int N> float normalize(float aging, float value);
    template<int N> float ewma(float alpha, float value);
};

#endif