#include <iostream>
#include <csignal>

#include "../include/Sound.hpp"
#include "../include/Fft.hpp"


using namespace std;

Sound loopback(6);
Fft analizer(6);

void cleanUp(int signal){
    loopback.~Sound();
    exit(0);
}


void vizualiser(){
    for(int i = 0; i < analizer.sample_size; i++){
        int modulus = 255 * (fabs(analizer.freqs[i].real()) + fabs(analizer.freqs[i].imag()));
        cout << "\033[38;2;" + std::to_string(modulus) + ";" + std::to_string(modulus) + ";" + std::to_string(modulus) + "m";
        cout << "+";
    }
    cout << endl;
}

//"\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
//"\033[38;2;" + std::to_string(r) + ";0;0m";

int main(){
    signal(SIGINT,cleanUp);

    while(1){
        loopback.listen();
        analizer.analize(loopback.samples);
        
        // for(int i = 0; i < loopback.sample_size; i++){
        //     cout << loopback.samples[i] << " ";
        // }
        // cout << endl;

        float low = 0, hi = 0;
        int i = 0;
        
        for(int j = 0; j < analizer.sample_size >> 2; j++, i++)
            low += fabs(analizer.freqs[i].real()) + fabs(analizer.freqs[i].imag());

        for(int j = 0; j < analizer.sample_size >> 1; j++, i++){
            hi += fabs(analizer.freqs[i].real()) + fabs(analizer.freqs[i].imag());
        }

        for(int j = 0; j < analizer.sample_size >> 2; j++, i++)
            low += fabs(analizer.freqs[i].real()) + fabs(analizer.freqs[i].imag());

        //cout << low << " " << hi << endl;
        hi = 5*hi;
        low = low;
        
        cout << "\033[38;2;" + std::to_string((int)hi) + ";0;"+ std::to_string((int)low) +"m";
        cout <<"||||||||||||||||||||||||||||||||"<<endl;
    }
}