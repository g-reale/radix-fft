#include <csignal>
#include <iostream>

#include "../include/Sound.hpp"
#include "../include/Fft.hpp"
#include "../include/Slider.hpp"
#include "../include/PlotSlider.hpp"
#include "../include/PostProcessor.hpp"


using namespace std;

Sound loopback(7);
Fft analizer(7);

// void cleanUp(int signal){
//     loopback.~Sound();
//     exit(0);
// }

int main(){

    int range_ratio = 999/255;
    PostProcessor::Map2Image image("resources/gradient3.jpg");

    initscr();
    curs_set(0);

     if(!can_change_color())
        return ERR;
    start_color();
    init_color(COLOR_BLACK,0,0,0);
    init_pair(1, COLOR_WHITE, COLOR_BLACK); // Define color pair 1: Custom red text on black background
    attron(COLOR_PAIR(1));


    while(1){
        loopback.listen();
        analizer.analize(loopback.samples);
        analizer.abs();    

        float low = PostProcessor::lowEnergy(0.5,analizer.freqs_abs);
        low = PostProcessor::normalize<0>(0.999,low);
        low = PostProcessor::ewma<0>(0.05,low);

        float high = PostProcessor::highEnergy(0.5,analizer.freqs_abs);
        high = PostProcessor::normalize<1>(0.999,high);
        high = PostProcessor::ewma<1>(0.05,high);

        image.map(low,high);

        mvprintw(0,0,"%f %f",low,high);
        init_color(COLOR_BLACK,image.color[0] * range_ratio,image.color[1] * range_ratio, image.color[2] * range_ratio);
        refresh();
    }
    endwin();
}
