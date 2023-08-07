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
        // const unsigned int freq_size;
        // const unsigned int freq_exp;

        std::vector<std::complex<float>> freqs;
        
        Fft(int exp);
        void analize(std::vector<std::complex<float>>& samples);
};

#endif
