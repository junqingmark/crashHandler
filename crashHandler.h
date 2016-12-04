#ifndef _CRASH_HANDLER_H_
#define _CRASH_HANDLER_H_

#include <iostream>
#include <errno.h>
#include <cstdio>
#include <string>

using namespace std;

class CrashHandler
{
public:
    static CrashHandler* getInstance();
    static void releaseInstance();
    bool registerCrashHandler(int errcode);

private:
    static CrashHandler* m_pCrashHandler;
    CrashHandler();
    ~CrashHandler();
    static void signal_handler(int signo);
    static void printStackTrace(ostream& out = cerr, unsigned int maxframes = 63);
};

#endif