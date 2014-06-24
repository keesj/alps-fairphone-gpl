#include <utils/Log.h>
#include <cutils/memory.h>
//
//#include <dlfcn.h>
//
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
//
/*
#include <surfaceflinger/Surface.h>
#include <surfaceflinger/ISurface.h>
#include <surfaceflinger/SurfaceComposerClient.h>
*/
//
#include <camera/ICamera.h>
#include <camera/CameraParameters.h>
//
#include "inc/CamLog.h"
#include "inc/Utils.h"
#include "inc/Command.h"
//
using namespace android;
//
//
//
//
//
/*
void
sa_handler_exit(int sig)
{
    printf("(sig, SIGUSR1)=(%d, %d) \n", sig, SIGINT);
//    gbRunning = false;
//    printf("test complete. CTRL+C to finish.\n");
}
*/
//
//
//
static
Vector<String8>
queryCommandVector(char const cCmd[], int fd)
{
    Vector<String8> vCommand;
    //
//    String8 s8Buffer(cCmd);
//    ::write(fd, s8Buffer.string(), s8Buffer.size());
    //
    //  (2) Convert command from string to vector: vCommand
    char const *s1 = cCmd, *s2 = 0;
    while ( 0 != s1 && 0 != (*s1) ) {
        if  ( ' ' == (*s1) ) {
            continue;
        }
        //
        s2 = ::strchr(s1, ' ');
        if  ( s2 == 0 ) {
            // If there's no space, this is the last item.
            vCommand.push_back(String8(s1));
            break;
        }
        vCommand.push_back(String8(s1, (size_t)(s2-s1)));
        s1 = s2 + 1;
    }
    //
#if 0
    for (size_t i = 0; i < vCommand.size(); i++)
    {
        String8 s8Temp = String8::format("[%d] %s\n", i, vCommand[i].string());
        ::write(fd, s8Temp.string(), s8Temp.size());
    }
#endif
    //
    return  vCommand;
}
//
//
//
int main(int argc, char** argv)
{
    char cCmds[256] = {0}; 
    //
    // set up the thread-pool
    sp<ProcessState> proc(ProcessState::self());
    ProcessState::self()->startThreadPool();
    //
    //
/*
    struct sigaction actions;
    ::memset(&actions, 0, sizeof(actions)); 
    ::sigemptyset(&actions.sa_mask);
    actions.sa_flags = 0; 
    actions.sa_handler = sa_handler_exit;
    err = ::sigaction(SIGINT, &actions, NULL);
    printf("sigaction return (%d)""\n", err);
*/
    //
    //
    //
    CmdMap::inst().help();
    while   (1)
    {
        printf("[camtest]$");
        ::fgets(cCmds, sizeof(cCmds), stdin);
        cCmds[::strlen(cCmds)-1] = '\0'; //  remove the '\n' 
        //
        if  ( 0 == ::strcmp(cCmds, "-h") ) {
            CmdMap::inst().help();
            continue;
        }
        //
        Vector<String8> vCmd = queryCommandVector(cCmds, 1);
        if  ( vCmd.empty() ) {
            continue;
        }
        //
        CmdMap::inst().execute(vCmd);
        printf("\n");
    }
    MY_LOGD("exit while""\n");
    //
    //
    IPCThreadState::self()->joinThreadPool();
    return 0;
}

