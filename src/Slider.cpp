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

void Slider::update(float new_value, char ch){
    
    int mapped_value = ratio * (new_value - min);
    if(mapped_value > height-1) mapped_value = height-1;
    if(mapped_value < 0) mapped_value = 0;
    
    int delta = mapped_value - value;
    if(!delta)
        return;
    
    int dir = delta > 0 ? 1 : - 1;
    ch = delta > 0 ? ch : ' ';


    for(int i = value; i != value + delta; i+= dir)
        mvwaddch(slider,height - i,0,ch);
        
    wrefresh(slider);
    value += delta;
}



