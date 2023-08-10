#include "../include/PlotSlider.hpp"

using namespace std;

PlotSlider::PlotSlider(WINDOW * parent,unsigned int y,unsigned int x,unsigned int height, int width,float min, float max):
    y(y),
    x(x),
    min(min),
    max(max),
    width(width),
    plot(subwin(parent,height,width,y,x))
{
    for(int i = 0; i < width; i++)
        sliders.push_back(Slider(plot,y,i,height,min,max));
    box(plot,0,0);
    wrefresh(plot);
}

void PlotSlider::update(vector<float> new_values){
    for(int i = 0; i < width; i++)
        sliders[i].update(new_values[i]);
}



