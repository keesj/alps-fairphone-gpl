//
#include <utils/Log.h>
#include <cutils/memory.h>
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
#if defined(HAVE_COMMAND_exit)
//
using namespace android;
//
//
//
/*******************************************************************************
 *  Command
 *      exit
 *
 ******************************************************************************/
namespace NSCmd_exit {
struct CmdImp : public CmdBase
{
    static bool                 isInstantiate;

                                CmdImp(char const* szCmdName)
                                    : CmdBase(szCmdName)
                                {}

    virtual bool                execute(Vector<String8>& rvCmd);
};
/******************************************************************************
 *
 ******************************************************************************/
bool CmdImp::isInstantiate = CmdMap::inst().addCommand(HAVE_COMMAND_exit, new CmdImp(HAVE_COMMAND_exit));
};  // NSCmd_exit
using namespace NSCmd_exit;


/******************************************************************************
 *
 ******************************************************************************/
bool
CmdImp::
execute(Vector<String8>& rvCmd)
{
    MY_LOGW("exit......");
    ::exit(0);
    return  true;
}


/******************************************************************************
*
*******************************************************************************/
#endif  //  HAVE_COMMAND_xxx

