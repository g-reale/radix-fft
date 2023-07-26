#include <complex>
#include <stdlib.h>
#include <stdio.h>
#include <pulse/simple.h>
#include <pulse/sample.h>
#include <pulse/error.h>
#include "../include/Fft.hpp"

using namespace std;

string true_color_escape(int r, int g, int b) {
    return "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
}

int main() {
    pa_simple * stream;
    pa_sample_spec stream_specs;

    stream_specs.format = PA_SAMPLE_U8;
    stream_specs.channels = 1;
    stream_specs.rate = 44100;

    int error;

    stream = pa_simple_new(
        NULL,
        "spectral",
        PA_STREAM_RECORD,
        "spectral.monitor",
        "loopback",
        &stream_specs,
        NULL,
        NULL,
        &error
    );

    if(!stream)
        printf("error: %s", pa_strerror(error));

    Fft fft(8);
    uint8_t samples[255];
    vector<complex<uint8_t>> formated(255,complex<uint8_t>(0,0));

    int rmax = 1;

    while(1) {
        
        pa_simple_read(stream, samples, sizeof(samples), NULL);
        for(int i = 0; i < 255; i++){
            formated[i] = samples[i];
        }

        int r = 0;
        fft.analize(formated);

        for(int i = 0; i < 255/3; i++)
            r += ((fft.freqs[i].real()<<1) + (fft.freqs[i].imag()<<1)) >> 1;
        
        if(r > 255)
            rmax++;

        std::cout << "\033[38;2;" + std::to_string(r/rmax) + ";0;0m";
        std::cout << "a";
    }

    if(stream)
        pa_simple_free(stream);
    else
        printf("error\n");

    return 0;
}