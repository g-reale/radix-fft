#include<vector>
#include <iostream>
#include <complex>
#include <cmath>

using namespace std;

class Fft{
    private:
        int N;
        vector<int> map;
        vector<vector<complex<float>>> coef_bank;
        
        string strBin(int number, int digits){
            digits = 1 << digits - 1;
            string rtrn = "";
            do{
                rtrn += (number & digits) ? '1' : '0';
                digits >>= 1;
            }while(digits);
            
            return rtrn;
        }

        vector<vector<complex<float>>> fftCoefs(int exp){
            vector<vector<complex<float>>> coefs(exp,vector<complex<float>>(1<<exp));
            
            int freqs = 1 << exp;

            for(int n = 0; n < exp; n++){
                for(int k = 0; k < freqs; k++)
                    coefs[n][k] = std::exp(complex<float>(0,-2 * M_PI * k / (1<<n)));
            }
            return coefs;
        }

        vector<int> fftSequence(int n){    
            vector<int> sequence(0,1<<n);
    
            for(int i = 0; i < sequence.size(); i++){
                int low_mask = 1;
                int high_mask = 1 << (n - 1);
                sequence[i] = 0;

                while(low_mask < high_mask){
                    sequence[i] = sequence[i] | (i & high_mask ? low_mask : 0) | (i & low_mask ? high_mask : 0);
                    low_mask <<= 1;
                    high_mask >>= 1;
                }
                cout << strBin(sequence[i],n) + " " << sequence[i] << endl;
            }
            return sequence;
        }

    public:

        Fft(int exp): N(exp), map(fftSequence(exp)), coef_bank(fftCoefs(exp)){};
    
        // vector<complex<float>> exec(const vector<unsigned char>& samples){
            
        //     vector<complex<float>> ordered(0,map.size()>>1);
        //     for(int i = 0; i < map.size()>>1; i++)
        //         ordered[i] = samples[map[i<<1]] + samples[map[i<<1 + 1]];
            

        //     int K = 1 << N;
        //     int exp = 1;
        //     int len = ordered.size()/2;
        //     vector<vector<complex<float>>> freqBin(K,vector<complex<float>>(len));

        //     for(int k = 0; k < K; k++){
        //         for(int i = 0; i < len; i++){
        //             freqBin[k][i] = ordered[i<<1] + coef_bank[exp][k] * ordered[i<<1 + 1];
        //         }
        //     }

        //     len >>= 1;
        //     exp ++;
            
        //     while(len){

        //         for(int k = 0; k < K; k++){
        //             for(int i = 0; i < len; i++)
        //                 freqBin[k][i] = freqBin[k][i<<1] + coef_bank[exp][k] * freqBin[k][i<<1 + 1];
        //         }

        //         exp++;
        //         len >>= 1;
        //     }

        // }

        void exec(const vector<unsigned char>& samples){
            vector<complex<float>> ordered(0,map.size()>>1);
            for(int i = 0; i < map.size()>>1; i++)
                ordered[i] = samples[map[i<<1]] + samples[map[i<<1 + 1]];
        }

};

#define N 8



int main(){

}