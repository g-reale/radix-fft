#ifndef SOUND_H
#define SOUND_H

#include <vector>
#include <complex>
#include <iostream>

#include <pulse/simple.h>
#include <pulse/sample.h>
#include <pulse/error.h>


class Sound{

    private:
        
        pa_simple * stream;

    public:
        
        const unsigned int buff_exp;
        const unsigned int buff_size;
        const unsigned int buff_byte_size;
        const float * buff;
        
        const unsigned int sample_exp;
        const unsigned int sample_size;
        std::vector<std::complex<float>> samples;

        Sound(int exp);
        ~Sound();
        void listen();
};

#endif