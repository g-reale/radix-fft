#include "../include/Fft.hpp"
#include<vector>
#include <iostream>
#include <complex>
#include <cmath>

using namespace std;

void Fft::fftSequence(){
    sample_order = vector<int>(sample_size);
    
    for(int i = 0; i < sample_size; i++){
        int low_mask = 1;
        int high_mask = 1 << (sample_exp - 1);
        sample_order[i] = 0;

        while(low_mask < high_mask){
            sample_order[i] = sample_order[i] | (i & high_mask ? low_mask : 0) | (i & low_mask ? high_mask : 0);
            low_mask <<= 1;
            high_mask >>= 1;
        }
    }
}

void Fft::fftCoefs(){
    fft_coefs = vector<vector<complex<float>>>(sample_exp + 1,vector<complex<float>>(sample_size/2));

    for(int exp = 1; exp <= sample_exp; exp++){
        for(int idx = 0; idx < sample_size/2; idx++){
            fft_coefs[exp][idx] = polar(1.0,-2 * M_PI * idx / (1<<exp));
        }
    }
}

void Fft::butterfly(int bgn, int exp){
    int wing_a = bgn;
    int wing_b = (1<<(exp-1));
    
    for(int i = wing_a; i < wing_a + wing_b; i++){
        complex<float> even = freqs[i];
        complex<float> odd = freqs[i + wing_b];
        complex<float> coef = fft_coefs[exp][i - wing_a];
        
        freqs[i] = even + coef * odd;
        freqs[i + wing_b] = even - coef * odd;
    }
}

string Fft::strBin(int number, int digits){
    digits = 1 << digits - 1;
    string rtrn = "";
    do{
        rtrn += (number & digits) ? '1' : '0';
        digits >>= 1;
    }while(digits);
    
    return rtrn;
}

Fft::Fft(int exp): 
    sample_exp(exp),
    sample_size(1<<exp),
    freqs(sample_size,0)
{
    fftCoefs();
    fftSequence();
}

 void Fft::analize(vector<complex<float>>& samples){
    
    for(int i = 0; i < sample_size; i++)
        freqs[i] = samples[sample_order[i]];

    for(int exp = 1; exp <= sample_exp; exp++){
        int step = 1<<exp;
        for(int op_idx = 0; op_idx < sample_size; op_idx += step){
            butterfly(op_idx,exp);
        }
    }
}
