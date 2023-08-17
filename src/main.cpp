
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
    initscr();
    curs_set(0);

     if(!can_change_color())
        return ERR;
    start_color();
    init_color(COLOR_BLACK,0,0,0);
    init_pair(1, COLOR_WHITE, COLOR_BLACK); // Define color pair 1: Custom red text on black background
    attron(COLOR_PAIR(1));

    Slider s(stdscr,0,10,30,0,1);
    Slider s1(stdscr,0,11,30,0,1);

    while(1){
        loopback.listen();
        analizer.analize(loopback.samples);
        analizer.abs();    

        float low = PostProcessor::lowEnergy(0.5,analizer.freqs_abs);
        low = PostProcessor::normalize<0>(0.99,low);
        low = PostProcessor::ewma<0>(0.3,low);

        float high = PostProcessor::highEnergy(0.5,analizer.freqs_abs);
        high = PostProcessor::normalize<1>(0.99,high);
        high = PostProcessor::ewma<1>(0.3,high);

        mvprintw(0,0,"%f %f",low,high);
        init_color(COLOR_BLACK,(low * 999),0,(high * 999));

        s.update(low,'|');
        s1.update(high,'|');

        refresh();
    }
    endwin();
}