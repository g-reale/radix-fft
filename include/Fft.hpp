#include<vector>
#include <iostream>
#include <complex>
#include <cmath>

#ifndef SPECTRAL_H
#define SPECTRAL_H

class Fft{
    private:

        int sample_size;
        int sample_exp;
        std::vector<int> sample_order;
        std::vector<std::vector<std::complex<uint8_t>>> fft_coefs;

        void fftSequence();
        void fftCoefs();
        void butterfly(int bgn, int exp);
        std::string strBin(int number, int digits);
    
    public:

        std::vector<std::complex<uint8_t>> freqs;
        
        Fft(int exp);
        void analize(std::vector<std::complex<uint8_t>>& samples);
};

#endif
