#include "../include/Sound.hpp"

#include <vector>
#include <iostream>

#include <pulse/simple.h>
#include <pulse/sample.h>
#include <pulse/error.h>

using namespace std;

Sound::Sound(int exp):
    sample_exp(exp),
    sample_size(1<<exp),
    samples(new float[sample_size]),
    sample_byte_size(sizeof(samples))
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
        free((void*)samples);
        exit(1);
    }
}

Sound::~Sound(){
    free((void*)samples);
    pa_simple_free(stream);
}

void Sound::listen(){
    pa_simple_read(stream,(void *)samples, sample_byte_size, NULL);
}

