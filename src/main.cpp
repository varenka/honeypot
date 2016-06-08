#include <iostream>
#include <vector>
#include "tcpsocket.h"
#include "color.h"

using namespace std;

int main(int argc, char* argv[])
{
    //print timestamp
    cout << Color::custom(io::GetTimeStamp(), FG_LIGHT_GREEN, UNDERLINED) << endl;

    vector<TCPSocket> sockets;
    sockets.resize(argc - 1);
    cout << "Size of sockets[] is: " << sockets.size() << endl;

    for(int i = 0; i < (argc - 1); i++)
    {
        cout << i << endl;
        sockets[i].ListenOnPort(io::ToInt(argv[i + 1]));
    }

    bool shouldClose = false;
    string input;
    while(!shouldClose)
    {
        cout << "> ";
        getline(cin, input);
        cout << endl;
        if(input == "exit" || input == "quit")
        {
            shouldClose = true;
        }
    }

    return 0;
}
