#include <cstdlib> //why do you need this?
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
    system("TITLE centro de comando"); //never do this, instead use: SetConsoleTitle("centro de comando");
    cout << "$";
    string line;
    string command;
    string argument;               //why do you need this now?
    string empty;                  //why do you need this?
    stringstream str_stream(line); //but...line is empty, so what is the point?

    getline(cin, line); //so, you get input to line after making the string stream?
    //HELP
    cout << line << endl;
    if (line == "HELP" || line == "help") //this should be fine because you inputted to line and are comparing to line
    {
        cout << "HELPING.......OK!" << endl;
        main(); //never do this
    }
    //infomações
    if (line == "INFO" || line == "info") //but...the input is in "line", not "line2"
    {
        cout << "© Centro de Comando 2012 , desenvolvido por BRUNOPESCAROLLI" << endl;
        main(); //never do this
    }
    //versão
    if (line == "VER") //but...the input is in "line", not "line3"
    {
        cout << "VERSAO 2.0.0.1 beta!" << endl;
        main(); //never do this
    }
    else //what if they entered one of the other commands?
    {
        cout << "ERROR!" << endl;
        main(); //never do this
    }

    system("PAUSE > NULL"); //never do this, instead use: cin.ignore(unsigned(-1), '\n');
    return 0;
}