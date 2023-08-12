#ifndef POSTPROCESSOR_H
#define POSTPROCESSOR_H

#include <tuple>
#include <vector>
#include <complex>

class PostProcessor{
    private:
        
        int freq_size;
        float low_size;
        float half_high_size;

        float aging;
        std::vector<float> low_hi_max;

    public:
        PostProcessor(unsigned int freq_size, float low_size, float aging);
        std::vector<float> filter(std::vector<float>& freq_abs);
        void adapitativeNormalization(std::vector<float>& low_hi);
};
#endif