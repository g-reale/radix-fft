#include "../include/PostProcessor.hpp"
#include <tuple>
#include <vector>
#include <complex>

using namespace std;

PostProcessor::PostProcessor(unsigned int freq_size, float low_proportion, float aging):
    low_hi_max(vector<float>({0,0})),
    aging(aging > 0 ? aging : 0),
    freq_size(freq_size)
{
    if(low_proportion > 1) low_proportion = 1;
    low_size = low_proportion * freq_size;
    half_high_size = (freq_size - low_size) / 2;
}

vector<float> PostProcessor::filter(vector<float>& freq_abs){
    float low = 0;
    float hi = 0;
    int i = 0;

    for(int j = 0; j < half_high_size; j++,i++)
        hi += freq_abs[i];

    for(int j = 0; j < low_size; j++, i++)
        low += freq_abs[i];
    
    for(int j = i; j < freq_size; j++)
        hi += freq_abs[i];

    return vector<float>({low,hi});
}

void PostProcessor::adapitativeNormalization(vector<float>& low_hi){
    
    for(int i = 0; i < 2; i++){
        if(low_hi[i] == 0) continue;
        if(low_hi[i] > low_hi_max[i]) low_hi_max[i] = low_hi[i];
        low_hi[i] /= low_hi_max[i];
        low_hi_max[i] *= aging;
    }
}
