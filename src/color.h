#ifndef COLOR_H
#define COLOR_H

#define FG_DARK_GRAY 30
#define FG_RED 31
#define FG_GREEN 32
#define FG_YELLOW 33
#define FG_BLUE 34
#define FG_PURPLE 35
#define FG_CYAN 36
#define FG_LIGHT_GRAY 37
#define FG_DEFAULT 39

#define BG_DARK_GRAY 40
#define BG_RED 41
#define BG_GREEN 42
#define BG_YELLOW 43
#define BG_BLUE 44
#define BG_PURPLE 45
#define BG_CYAN 46
#define BG_GRAY 47
#define BG_DEFAULT 49

#define FG_GRAY 90
#define FG_LIGHT_RED 91
#define FG_LIGHT_GREEN 92
#define FG_LIGHT_YELLOW 93
#define FG_LIGHT_BLUE 94
#define FG_LIGHT_PURPLE 95
#define FG_LIGHT_CYAN 96

#define NORMAL 0
#define BOLD 1
#define FAINT 2
#define ITALIC 3
#define UNDERLINED 4
#define NEGATIVE 7
#define HIDDEN 8
#define CROSSED_OUT 9

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <time.h>
#include <cstdlib>

using namespace std;

class Color {
public:

    static string custom(string, int, int);
    static string custom(int, int, int);
    static string red(string);
    static string green(string);
    static string blue(string);

    //functions to define colors of different output data types
    static string ipAddrText(string);
    static string ipAddrText(int);

    static string intText(string);
    static string intText(int);

    static string errorText(string);
    static string errorText(int);
};

class io {
public:

    static string ToString(char * c);
    static string ToString(int i);
    static int ToInt(char * c);

    static string ipAddrToString(string address, int port);

    static bool exists(string filename);
    static string GetTimeStamp();
    static string GetLogFileName();
    static void Log(string);
};
#endif




