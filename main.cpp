#include <signal.h>
#include <iostream>
#include <cstdlib>
#include "crashHandler.h"

using namespace std;

int main(int argc, char* argv[])
{
    string filename = "test.txt";
    CrashHandler* crashHandler = CrashHandler::getInstance();
    if(crashHandler->registerCrashHandler(SIGABRT) && crashHandler->registerCrashHandler(SIGSEGV))
    {
        cout << "register sinal handler SIGABRT successfully\n";
    }

    char* ptr;
    free(ptr);

    return 0;
}