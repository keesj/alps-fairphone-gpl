#include <utils/Log.h>
#include <cutils/memory.h>
//
//#include <dlfcn.h>
//
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>

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
/******************************************************************************
 *
 ******************************************************************************/
CmdMap&
CmdMap::
inst()
{
    static CmdMap inst;
    return inst;
}


/******************************************************************************
 *
 ******************************************************************************/
CmdMap::
CmdMap()
    : mvCmdMap(0)
{
}


/******************************************************************************
 *
 ******************************************************************************/
bool
CmdMap::
addCommand(char const*const pszName, CmdBase*const pCmdInstance)
{
    mvCmdMap.add(String8(pszName), pCmdInstance);
    printf("    +=: <%s>\n", pszName);
    return  true;
}


/******************************************************************************
 *
 ******************************************************************************/
bool
CmdMap::
execute(Vector<String8>& rvCmd)
{
    sp<CmdBase> pCmdBase = mvCmdMap.valueFor(*rvCmd.begin());
    if  (pCmdBase != 0)
    {
//                            printf("<%s>\n", pCmdBase->getName().string());
        return  pCmdBase->execute(rvCmd);
    }
    MY_LOGW("no command found!");
    return  false;
}


/******************************************************************************
 *
 ******************************************************************************/
void
CmdMap::
help()
{
    printf("\n");
    printf("    ++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("    +                     MENU                         +\n");
    printf("    ++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("    Command: <-h>\n");
    for (size_t i = 0; i < mvCmdMap.size(); i++)
    {
        printf("    Command: <%s>\n", mvCmdMap.keyAt(i).string());
    }
    printf("    ....................................................\n");
}

