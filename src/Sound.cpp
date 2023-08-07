#include "../include/Sound.hpp"

#include <vector>
#include <iostream>

#include <pulse/simple.h>
#include <pulse/sample.h>
#include <pulse/error.h>

using namespace std;

Sound::Sound(int exp):
    buff_exp(exp + 1),
    buff_size(1<<(exp+1)),
    buff(new float[buff_size]),
    buff_byte_size(buff_size * sizeof(float)),

    sample_exp(exp),
    sample_size(1<<(exp)),
    samples(sample_size)
{
    int error;
    
    pa_sample_spec stream_specs;
    stream_specs.format = PA_SAMPLE_FLOAT32LE;
    stream_specs.channels = 2;
    stream_specs.rate = 44100;


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

    if(!stream){
        cerr << "error: " << pa_strerror(error);
        free((void*)buff);
        exit(1);
    }
}

Sound::~Sound(){
    free((void*)buff);
    pa_simple_free(stream);
}

void Sound::listen(){
    while(pa_simple_read(stream,(void*)buff, buff_byte_size, NULL) < 0);
    for(int i = 0; i < buff_size; i+=2){
        samples[i>>1].real(buff[i]);
        samples[i>>1].imag(buff[i+1]);
    }
}

