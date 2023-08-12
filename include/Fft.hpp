#ifndef FFT_H
#define FFT_H

#include<vector>
#include <iostream>
#include <complex>
#include <cmath>


class Fft{
    private:

        std::vector<int> sample_order;
        std::vector<std::vector<std::complex<float>>> fft_coefs;

        void fftSequence();
        void fftCoefs();
        void butterfly(int bgn, int exp);
        std::string strBin(int number, int digits);
    
    public:

        const unsigned int sample_size;
        const unsigned int sample_exp;
        
        std::vector<std::complex<float>> freqs;
        std::vector<float> freqs_abs;
        
        Fft(int exp);
        void analize(const std::vector<std::complex<float>>& samples);
        void abs();
};

#endif
