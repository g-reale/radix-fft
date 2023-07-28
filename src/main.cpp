#include <iostream>
#include <csignal>

#include "../include/Sound.hpp"
#include "../include/Fft.hpp"


using namespace std;

Sound loopback(3);
Fft analizer(3);

void cleanUp(int signal){
    loopback.~Sound();
    exit(0);
}


//"\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
//"\033[38;2;" + std::to_string(r) + ";0;0m";

int main(){
    signal(SIGINT,cleanUp);

    while(1){
        loopback.listen();
        analizer.analize(loopback.samples);
        for(int i = 0; i < analizer.sample_size; i++){
            string val = to_string((int)(sqrt(pow(analizer.freqs[i].real(),2) + pow(analizer.freqs[i].imag(),2)) * 255));
            cout << "\033[38;2;" + val + ";" + val + ";" + val + "m";
            cout << "+";
        }
        cout << endl;
    }
}