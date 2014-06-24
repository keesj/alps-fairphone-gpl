#ifndef ZSD_SCENARIO_H
#define ZSD_SCENARIO_H

using namespace NSImageio;
using namespace NSIspio;

namespace NSImageio{
namespace NSIspio{
    class ICamIOPipe;
    //class IPostProcPipe;
    class ICdpPipe;
};
};
//class EisHalBase;
#include <utils/threads.h>
using namespace android;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  setConfig --> start --> Loop {enque, deque} --> stop
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class ZSDScenario : public IhwScenario{

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  IhwScenario Interface.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:
    /////
    static ZSDScenario*     createInstance(EScenarioFmt rSensorType, halSensorDev_e const &dev, ERawPxlID const &bitorder);
    virtual MVOID           destroyInstance();
    virtual                 ~ZSDScenario();
    
protected:
                            ZSDScenario(EScenarioFmt rSensorType, halSensorDev_e const &dev, ERawPxlID const &bitorder);     

public: 
    virtual MBOOL           init();
    virtual MBOOL           uninit();

    virtual MBOOL           start();
    virtual MBOOL           stop();
                                 
    virtual MVOID           wait(EWaitType rType);
    
    virtual MBOOL           deque(EHwBufIdx port, vector<PortQTBufInfo> *pBufIn);
    virtual MBOOL           enque(vector<PortBufInfo> *pBufIn = NULL, vector<PortBufInfo> *pBufOut = NULL);
    virtual MBOOL           enque(vector<IhwScenario::PortQTBufInfo> const &in);
    virtual MBOOL           replaceQue(vector<PortBufInfo> *pBufOld, vector<PortBufInfo> *pBufNew);

    virtual MBOOL           setConfig(vector<PortImgInfo> *pImgIn); 

    virtual MVOID           getHwValidSize(MUINT32 &width, MUINT32 &height);
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Private Operations.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
private:
            MVOID           defaultSetting();
            MVOID           dumpPass1EnqueSeq();
            MVOID           dumpPass1DequeSeq();

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Data Members.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++    
private:
    ICamIOPipe*             mpCamIOPipe;
    //IPostProcPipe *mPostProcPipe;
    ICdpPipe                *mpCdpPipe;
    //EisHalBase*           mpEis; 
    EScenarioFmt            mSensorType;
    halSensorDev_e          mSensorDev;
    ERawPxlID               mSensorBitOrder;
    Mutex                   mModuleMtx;   
    Vector<MUINT32>         mvPass1EnqueSeq;
    Vector<MUINT32>         mvPass1DequeSeq;


    struct sDefaultSetting_Ports{
        PortInfo tgi;
        PortInfo imgo;
        PortInfo imgi;
        PortInfo vido;
        PortInfo dispo;
        // zsd added
        PortInfo img2o;
        //
        MVOID dump();
        //
    };
    sDefaultSetting_Ports   mSettingPorts;
};


#endif
