#ifndef POSTPROCESSOR_H
#define POSTPROCESSOR_H

#define cimg_use_jpeg
#include "../include/CImg.h"

#include <tuple>
#include <vector>
#include <complex>

namespace PostProcessor{
    float lowEnergy(float low_proportion, const std::vector<float>& freq_abs);
    float highEnergy(float high_proportion, const std::vector<float>& freq_abs);
    
    template<int N> float normalize(float aging, float value);
    template<int N> float ewma(float alpha, float value);

    class Map2Image{
        private:
            cimg_library::CImg<unsigned char> image;
            int width;
            int height;
        public:
            unsigned char color[3];
            Map2Image(std::string path);
            void map(float x, float y);
    };
};

#endif