#include "crashHandler.h"
#include <signal.h>
#include <execinfo.h>
#include <cstring>
#include <fstream>

CrashHandler* CrashHandler::m_pCrashHandler = NULL;

CrashHandler::CrashHandler()
{

}

CrashHandler::~CrashHandler()
{

}

CrashHandler* CrashHandler::getInstance()
{
    if(NULL == m_pCrashHandler)
    {
        m_pCrashHandler = new CrashHandler();
    }
    return m_pCrashHandler;
}

void CrashHandler::releaseInstance()
{
    if(m_pCrashHandler != NULL)
    {
        delete m_pCrashHandler;
        m_pCrashHandler = NULL;
    }
}

void CrashHandler::signal_handler(int signo)
{
    printStackTrace();

    signal(signo, SIG_DFL);
    raise(signo);
}

bool CrashHandler::registerCrashHandler(int errcode)
{
    if(signal(errcode, signal_handler) == SIG_ERR)
    {
        return false;
    }
    return true;
}


void CrashHandler::printStackTrace(ostream& os, unsigned int max_frames)
{
    ofstream ofs("log.txt");
    if(!ofs.is_open())
    {
        cerr << "Fail to open the log file!" << endl;
    }


    void* addrlist[max_frames + 1];
    int addrlen = backtrace(addrlist, sizeof(addrlist)/sizeof(void*));
    if(0 == addrlen)
    {
        return;
    }

    char** symbollist = backtrace_symbols(addrlist, addrlen);


    for(int i = 0; i < addrlen; i++)
    {
        os << symbollist[i] << endl;
        ofs << symbollist[i] << endl;
    }

}