#ifndef PLOTSLIDER_H
#define PLOTSLIDER_H

#include "../include/Slider.hpp"
#include<ncurses.h>
#include<vector>

class PlotSlider{
    
    private:
        unsigned int y;
        unsigned int x;
        unsigned int height;
        unsigned int width;

        float min;
        float max;

        WINDOW * plot;

        std::vector<Slider> sliders;

    public:
        PlotSlider(WINDOW * parent,unsigned int y,unsigned int x,unsigned int height, int width,float min, float max);
        void update(std::vector<float> new_value);
};

#endif