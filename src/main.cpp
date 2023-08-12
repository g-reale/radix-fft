
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
PostProcessor post(analizer.sample_size,0.5,0.999);

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
    
    Slider s(stdscr,0,2,40,0,1);
    Slider s1(stdscr,0,4,40,0,1);
    vector<float> low_hi;

     while(1){
        loopback.listen();
        analizer.analize(loopback.samples);
        analizer.abs();
        
        //.filter allocs a vector each iteration, change this later
        low_hi = post.filter(analizer.freqs_abs);
        post.adapitativeNormalization(low_hi);
        //allocates a vector each iteration, change this later
        
        mvprintw(0,0,"%f %f",low_hi[0],low_hi[1]);
        
        init_color(COLOR_BLACK,0,(low_hi[0] * 999),(low_hi[1] * 999));
        s.update(low_hi[0],'|');
        s1.update(low_hi[1],'|');
        refresh();
        
    }
    endwin();
}