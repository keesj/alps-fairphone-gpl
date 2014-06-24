#ifndef _MTK_CAMERA_CORE_CAMPIPE_INC_POSTPROC_PIPE_H_
#define _MTK_CAMERA_CORE_CAMPIPE_INC_POSTPROC_PIPE_H_
//
#include <vector>
//
using namespace std;
//

/*******************************************************************************
* real implement in imageio 
********************************************************************************/
namespace NSImageio{
namespace NSIspio{
    class IPostProcPipe;
};
};

/*******************************************************************************
*
********************************************************************************/
namespace NSCamPipe {
////////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
*
********************************************************************************/

class PipeImp;


/*******************************************************************************
*
********************************************************************************/
class PostProcPipe : public PipeImp
{
public:     ////    Constructor/Destructor.
                    PostProcPipe(
                        char const*const szPipeName, 
                        EPipeID const ePipeID, 
                        ESWScenarioID const eSWScenarioID, 
                        EScenarioFmt const eScenarioFmt
                    );

public:     ////    Instantiation.
    virtual MBOOL   init();
    virtual MBOOL   uninit();

public:     ////    Operations.
    virtual MBOOL   start();
    virtual MBOOL   stop();

public:     ////    Buffer Quening.
    virtual MBOOL   enqueBuf(PortID const ePortID, QBufInfo const& rQBufInfo);
    //
    virtual MBOOL   dequeBuf(PortID const ePortID, QTimeStampBufInfo& rQBufInfo, MUINT32 const u4TimeoutMs = 0xFFFFFFFF);

public:     ////    Settings.
    virtual MBOOL   configPipe(vector<PortInfo const*>const& vInPorts, vector<PortInfo const*>const& vOutPorts);

public:     ////    Info.
    virtual MBOOL   queryPipeProperty(vector<PortProperty > &vInPorts, vector<PortProperty > &vOutPorts); 

public:     ////    Old style commnad.
    virtual MBOOL   sendCommand(MINT32 cmd, MINT32 arg1, MINT32 arg2, MINT32 arg3);

private:
    NSImageio::NSIspio::IPostProcPipe *mpPostProcPipe;     
    MUINT32 mu4OutPortEnableFlag;     

};


////////////////////////////////////////////////////////////////////////////////
};  //namespace NSCamPipe
#endif  //  _MTK_CAMERA_CORE_CAMPIPE_INC_POSTPROC_PIPE_H_

