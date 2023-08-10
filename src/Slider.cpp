#include "../include/Slider.hpp"

Slider::Slider(WINDOW * parent,unsigned int y,unsigned int x,unsigned int height, float min, float max):
    y(y),
    x(x),
    min(min),
    max(max),
    value(0),
    height(height),
    ratio(height/(max-min)),
    slider(subwin(parent,height,1,y,x))
{
    refresh();
}

void Slider::update(float new_value){
    
    int mapped_value = ratio * (new_value - min);
    if(mapped_value > max) mapped_value = max;
    if(mapped_value < min) mapped_value = min;

    int delta = mapped_value - value;
    
    if(!delta)
        return;
    
    int dir = delta > 0 ? 1 : - 1;
    char ch = delta > 0 ? '+' : ' ';

    for(int i = value; i != value + delta; i+= dir)
        mvwaddch(slider,height - i,0,ch);
        
    wrefresh(slider);
    value += delta;
}



