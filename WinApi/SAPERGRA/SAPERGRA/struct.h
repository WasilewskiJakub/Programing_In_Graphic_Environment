#pragma once
#include "framework.h"
#include "SAPERGRA.h"
#include"Function.h"
#include<time.h>

struct WindowProperty
{
    int Gxcount;    // number of child in row
    int Gycount;    // number of child in column
    int Gheight;    // height of window (pixels)
    int Gwidth;     // width of window (pixels)
    HWND main;      // handler to main window
    HINSTANCE hInt;
    bool Debug;     // true if debuging is active
};
//============================//
struct GameProps
{
    bool Gtimerstart;  // true if timer is working
    int Gtick;         // temp variable to timer
    int Gmillisec;     // count time of game
    int Gmines_count;  // Overral nuber of mines on board
    int Gmines_found;  // Number of found mines 
    int Gflagues;      // Flags to put Yet.
    bool Gdebug_on;    // if debug mode is active
    int Gncm;          // this shell sth.
    bool EndGame;      // cant type when End game!
};

struct Board
{
    HWND child_window;
    int number_of_nearest_mines;
};