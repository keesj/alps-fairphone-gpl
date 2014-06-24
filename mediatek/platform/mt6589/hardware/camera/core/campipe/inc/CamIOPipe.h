#ifndef _MTK_CAMERA_CORE_CAMPIPE_INC_CAMIO_PIPE_H_
#define _MTK_CAMERA_CORE_CAMPIPE_INC_CAMIO_PIPE_H_
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
    class ICamIOPipe;
    struct PortInfo; 
};
};

class SensorHal;

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
class CamIOPipe : public PipeImp
{
public:     ////    Constructor/Destructor.
                    CamIOPipe(
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
    virtual MBOOL   startOne(); 
    virtual MBOOL   stop();

public:     ////    Buffer Quening.
    virtual MBOOL   enqueBuf(PortID const ePortID, QBufInfo const& rQBufInfo);
    //
    virtual MBOOL   dequeBuf(PortID const ePortID, QTimeStampBufInfo& rQBufInfo, MUINT32 const u4TimeoutMs = 0xFFFFFFFF);

public:     ////    Settings.
    virtual MBOOL   configPipe(vector<PortInfo const*>const& vInPorts, vector<PortInfo const*>const& vOutPorts);

public:     ////    Info.
    virtual MBOOL   queryPipeProperty(vector<PortProperty> &vInPorts, vector<PortProperty> &vOutPorts); 

public:     ////    Old style commnad.
    virtual MBOOL   sendCommand(MINT32 cmd, MINT32 arg1, MINT32 arg2, MINT32 arg3);

public:     ////    notify 
    virtual MVOID   waitSignal(EPipeSignal ePipeSignal, MUINT32 const u4TimeoutMs = 0xFFFFFFFF);

private:
    


private:    ////    mapper
    //
    MBOOL configSensor(MUINT32 const u4DeviceID, MUINT32 const u4Scenario, MUINT32 const u4Width, MUINT32 const u4Height, MUINT32 const byPassDelay, MUINT32 const u4ByPassScenario,  MBOOL const fgIsContinuous); 
    MBOOL querySensorInfo(MUINT32 const u4DeviceID, MUINT32 const u4Scenario, MUINT32 const u4BitDepth, EImageFormat &eFmt,  MUINT32 &u4Width, MUINT32 &u4Height, MUINT32 & u4RawPixelID);


    //
    MBOOL dequeHWBuf(MUINT32 const u4TimeoutMs /*= 0xFFFFFFFF*/);

    MBOOL skipFrame(MUINT32 const u4SkipCount); 

private:
    NSImageio::NSIspio::ICamIOPipe *mpCamIOPipe; 
    SensorHal* mpSensorHal; 
 
    SensorPortInfo mrSensorPortInfo; 
    MBOOL mfgIsYUVPortON; 

    QTimeStampBufInfo mrRawQTBufInfo; 
    QTimeStampBufInfo mrYuvQTBufInfo; 
    MUINT32 mu4DeviceID; 

};


////////////////////////////////////////////////////////////////////////////////
};  //namespace NSCamPipe
#endif  //  _MTK_CAMERA_CORE_CAMPIPE_INC_CAMIO_PIPE_H_

