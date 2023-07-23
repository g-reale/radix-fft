#include<vector>
#include <iostream>
#include <complex>
#include <cmath>

using namespace std;

class Fft{
    
    private:
    int sample_size;
    int sample_exp;
    vector<int> sample_order;
    vector<vector<complex<float>>> fft_coefs;

    void fftSequence(){ 
        sample_order = vector<int>(sample_size);
        // cout << "making sample order..." << endl;
        
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

        // cout << "passed!" << endl;
    }

    void fftCoefs(){
        fft_coefs = vector<vector<complex<float>>>(sample_exp + 1,vector<complex<float>>(sample_size/2));

        // cout << "making the coeficients..." << endl;
        // cout << "fft_coefs["<< sample_exp + 1 << "]" << "[" << sample_size <<"]" << endl;

        for(int exp = 1; exp <= sample_exp; exp++){
            // cout << "exp:" << exp << endl;
            for(int idx = 0; idx < sample_size/2; idx++){
                // cout << "\t" << polar(1.0,-2 * M_PI * idx / (1<<exp)) << " = ";
                // cout << "e^(2 * PI *" << idx << ") / (" << (1 << exp) << ") \t";
                // cout << "\t fft_coefs[" << exp << "][" << idx << "]" << endl;
                fft_coefs[exp][idx] = polar(1.0,-2 * M_PI * idx / (1<<exp));
            }
        }
        // cout << "passed!" << endl;
    }

    void butterfly(int bgn, int exp){
        int wing_a = bgn;
        int wing_b = (1<<(exp-1));
        
        // cout << "butterfly(" << bgn << ", " << exp << ")" << endl;
        // cout << "\tbgn: " << bgn << ", 1<<(exp-1): " << (1<<(exp-1)) << endl;
        // cout << "\twing_a: " << wing_a << ", wing_b: " << wing_b << endl << endl;

        for(int i = wing_a; i < wing_a + wing_b; i++){
            complex<float> even = freqs[i];
            complex<float> odd = freqs[i + wing_b];
            complex<float> coef = fft_coefs[exp][i - wing_a];

            // cout << "\tfreqs[" << i << "] = " << "freqs[" << i << "] + fft_coefs[" << exp << "][" << i - wing_a << "] * freqs[" << i + wing_b << "]" << endl;
            // cout << "\t" << even + coef * odd << " = " << even << " + " << coef << " * " << odd << endl << endl;

            // cout << "\tfreqs[" << i + wing_b << "] = " << "freqs[" << i << "] - fft_coefs[" << exp << "][" << i - wing_a << "] * freqs[" << i + wing_b << "]" << endl;
            // cout << "\t" << even - coef * odd << " = " << even << " - " << coef << " * " << odd << endl << endl;

            freqs[i] = even + coef * odd;
            freqs[i + wing_b] = even - coef * odd;
        }
    }

    //helper method 
    string strBin(int number, int digits){
        digits = 1 << digits - 1;
        string rtrn = "";
        do{
            rtrn += (number & digits) ? '1' : '0';
            digits >>= 1;
        }while(digits);
        
        return rtrn;
    }

    public: 
    vector<complex<float>> freqs;

    Fft(int exp): 
    sample_exp(exp),
    sample_size(1<<exp),
    freqs(sample_size,0)
    {
        fftCoefs();
        fftSequence();
    }

    void analize(vector<complex<float>>& samples){
        
        for(int i = 0; i < sample_size; i++)
            freqs[i] = samples[sample_order[i]];


        // cout << "analize" << endl << "freqs:" << "\n\t";
        // for(auto freq : freqs){
        //     cout << freq << " ";
        // }
        // cout << endl;

        for(int exp = 1; exp <= sample_exp; exp++){
            int step = 1<<exp;
            for(int op_idx = 0; op_idx < sample_size; op_idx += step){
                butterfly(op_idx,exp);
            }
        }
        // for(auto freq : freqs){
            // cout << freq << endl;
            //cout << sqrt(pow(freq.real(),2) + pow(freq.imag(),2)) << ";" << endl;
        // }
        // cout << endl;

    }

};


