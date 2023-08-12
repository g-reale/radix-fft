#ifndef SLIDER_H
#define SLIDER_H

#include<ncurses.h>

class Slider{
    
    private:
        unsigned int y;
        unsigned int x;
        unsigned int height;
        float min;
        float max;
        WINDOW * slider;

        float ratio;
        int value;

    public:
        Slider(WINDOW * parent,unsigned int y,unsigned int x,unsigned int height, float min, float max);
        void update(float new_value, char ch);
};

#endif