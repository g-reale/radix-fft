#ifndef SOUND_H
#define SOUND_H

#include <vector>
#include <iostream>

#include <pulse/simple.h>
#include <pulse/sample.h>
#include <pulse/error.h>


class Sound{

    private:
        
        pa_simple * stream;

    public:
        
        const unsigned int sample_exp;
        const unsigned int sample_size;
        const unsigned int sample_byte_size;
        const float * samples;
        
        Sound(int exp);
        ~Sound();
        void listen();
};

#endif