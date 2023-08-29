#include "../include/PostProcessor.hpp"

#define cimg_use_jpeg
#include "../include/CImg.h"

#include <tuple>
#include <vector>
#include <complex>


namespace PostProcessor{
    
    using namespace std;


    float lowEnergy(float low_proportion, const vector<float>& freq_abs){
        
        static float proportion = -1;
        static int sum_start = -1;
        static int sum_end = -1;
        if(proportion < 0 || proportion != low_proportion){
            proportion = low_proportion > 1 ? 1 : low_proportion < 0 ? 0 : low_proportion;
            sum_start = freq_abs.size() * (1 - proportion) / 2;
            sum_end = sum_start + freq_abs.size() * proportion;
        }

        int low = 0;
        for(int i = sum_start; i < sum_end; i++)
            low += freq_abs[i];
        return low;
    }


    float highEnergy(float high_proportion, const vector<float>& freq_abs){
        
        static float proportion = - 1;
        static int sum_end = -1;
        static int sum_start = -1;
        
        if(proportion < 0 || proportion != high_proportion){
            proportion = high_proportion > 1 ? 1 : high_proportion < 0 ? 0 : high_proportion;
            sum_end = (freq_abs.size() * proportion)/2;
            sum_start = freq_abs.size() - sum_end;
        }

        int high = 0;
        for(int i = 0; i < sum_end; i++)
            high += freq_abs[i];

        for(int i = sum_start; i < freq_abs.size(); i++)
            high += freq_abs[i];
        
        return high;
    }

    
    template <int N> float normalize(float aging, float value){
        if(value == 0) return 0;

        static float max = 0;
        max = max < value ? value : max;
        float normalized = value / max;
        max *= aging;
        return normalized;
    }

    
    template <int N> float ewma(float alpha, float value){
        static float past = 0;
        alpha = alpha > 1 ? 1 : alpha < 0 ? 0 : alpha;

        past = value * alpha + past * (1 - alpha);
        return past;
    }

    //CPP is dumb and silly
    template float normalize<0>(float aging, float value);
    template float normalize<1>(float aging, float value);
    template float ewma<0>(float alpha, float value);
    template float ewma<1>(float alpha, float value);

    Map2Image::Map2Image(std::string path):
        color({0,0,0}),
        image(path.c_str()),
        width(image.width()),
        height(image.height())
    {}

    void Map2Image::map(float x, float y){
        int mapped_x = x * width;
        int mapped_y = y * height;

        color[0] = image(mapped_x,mapped_y,0,0);
        color[1] = image(mapped_x,mapped_y,0,1);
        color[2] = image(mapped_x,mapped_y,0,2);
    }

};

