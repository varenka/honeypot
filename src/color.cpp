#include "color.h"

string Color::custom(string in, int _color, int modifier)
{
    stringstream ss;
    ss << "\033[" << modifier << ";" << _color << "m" << in << "\033[0m";
    return ss.str();
}

string Color::custom(int in, int _color, int modifier)
{
    stringstream ss;
    ss << "\033[" << modifier << ";" << _color << "m" << in << "\033[0m";
    return ss.str();
}

string Color::ipAddrText(string in)
{
    return custom(in, FG_PURPLE, 0);
}

string Color::ipAddrText(int in)
{
    return custom(in, FG_PURPLE, 0);
}

string Color::intText(string in)
{
    return custom(in, FG_RED, 0);
}

string Color::intText(int in)
{
    return custom(in, FG_RED, 0);
}

string Color::errorText(string in)
{
    return custom(in, BG_RED, 0);
}

string Color::errorText(int in)
{
    return custom(in, BG_RED, 0);
}

//function for printing addresses in the form of address:port
string io::ipAddrToString(string address, int port)
{
    stringstream ss;
    ss << address << ":" << port;
    return Color::ipAddrText(ss.str());
}

string io::ToString(char * c)
{
    stringstream ss;
    ss << c;
    return ss.str();
}

string io::ToString(int i)
{
    stringstream ss;
    ss << i;
    return ss.str();
}

int io::ToInt(char * c)
{
    string s = ToString(c);
    return atoi(s.c_str());
}

bool io::exists(string filename)
{
    ifstream if_stream(filename.c_str());
    if(if_stream.good())
    {
        return true;
    }
    return false;
}

//get the current time in y-m-d@hr:min:sec format
string io::GetTimeStamp()
{
    time_t t = time(0); //get current time
    struct tm * now = localtime(&t);

    stringstream ss;
    ss << (now->tm_year + 1900) << '-' << (now->tm_mon + 1) << '-' << now->tm_mday << '@' << now->tm_hour << ':' << now->tm_min << ':' << now->tm_sec;

    return ss.str();
}

string io::GetLogFileName()
{
    stringstream ss;
    string fname;
    int i = 0;

    while(true)
    {
        ss << GetTimeStamp() << '#' << i << endl;
        ss >> fname;
        if(exists(fname))
        {
            i ++;
        }
        else
        {
            return fname;
        }
    }
}

void io::Log(string msg)
{
    ofstream of_stream(GetLogFileName().c_str());
    of_stream << msg;
    of_stream.close();

}
