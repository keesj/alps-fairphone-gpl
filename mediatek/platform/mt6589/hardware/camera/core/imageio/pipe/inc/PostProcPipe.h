#ifndef _ISPIO_POSTPROC_PIPE_H_
#define _ISPIO_POSTPROC_PIPE_H_
//
#include <vector>
#include <map>
#include <list>
//
using namespace std;
//
//
#include <ispio_pipe_ports.h>
#include <ispio_pipe_buffer.h>
//
#include "cam_path.h"

/*******************************************************************************
*
********************************************************************************/
namespace NSImageio {
namespace NSIspio   {
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
                        EScenarioID const eScenarioID,
                        EScenarioFmt const eScenarioFmt
                    );

                    virtual ~PostProcPipe();

public:     ////    Instantiation.
    virtual MBOOL   init();
    virtual MBOOL   uninit();

public:     ////    Operations.
    virtual MBOOL   start();
    virtual MBOOL   stop();

public:     ////    Buffer Quening.
    virtual MBOOL   enqueInBuf(PortID const portID, QBufInfo const& rQBufInfo);
    virtual MBOOL   dequeInBuf(PortID const portID, QTimeStampBufInfo& rQBufInfo, MUINT32 const u4TimeoutMs = 0xFFFFFFFF);
    //
    virtual MBOOL   enqueOutBuf(PortID const portID, QBufInfo const& rQBufInfo);
    virtual MBOOL   dequeOutBuf(PortID const portID, QTimeStampBufInfo& rQBufInfo, MUINT32 const u4TimeoutMs = 0xFFFFFFFF);

public:     ////    Settings.
    virtual MBOOL   configPipe(vector<PortInfo const*>const& vInPorts, vector<PortInfo const*>const& vOutPorts);
    virtual MBOOL   configPipeUpdate(vector<PortInfo const*>const& vInPorts, vector<PortInfo const*>const& vOutPorts);

public:     ////    Commands.
    virtual MBOOL   onSet2Params(MUINT32 const u4Param1, MUINT32 const u4Param2);
    virtual MBOOL   onGet1ParamBasedOn1Input(MUINT32 const u4InParam, MUINT32*const pu4OutParam);

public:     ////    Interrupt handling
	virtual MBOOL   irq(EPipePass pass, EPipeIRQ irq_int);

public:     ////    original style sendCommand method
    virtual MBOOL   sendCommand(MINT32 cmd, MINT32 arg1, MINT32 arg2, MINT32 arg3);


//
private:
    IspDrvShell*             m_pIspDrvShell;
    CamPathPass2             m_CamPathPass2;
    CamPathPass2Parameter    m_camPass2Param;
    vector<BufInfo>          m_vBufImgi;
    vector<BufInfo>          m_vBufVipi;
    vector<BufInfo>          m_vBufVip2i;
    vector<BufInfo>          m_vBufDispo;
    vector<BufInfo>          m_vBufVido;
    //
    MUINT32 tdriSize, tdriPhy;
    MUINT8 *pTdriVir;
    MINT32  tdriMemId;
    MUINT32 tpipe_config_size;
    MUINT32 *pTpipeConfigVa;
    MUINT32 segmSimpleConfIdxNum;

    MINT32  tpipe_config_memId;
    MUINT32 cq1_size,cq1_phy;
    MUINT8 *cq1_vir;
    MINT32 cq1_memId;
    MUINT32 cq2_size,cq2_phy;
    MUINT8 *cq2_vir;
    MINT32 cq2_memId;
    MUINT32 cq3_size,cq3_phy;
    MUINT8 *cq3_vir;
    MINT32 cq3_memId;
    //
    EPipePass   m_pipePass;
    //
    MINT32  m_pass2_CQ;
    EConfigSettingStage     m_settingStage;
    //
    MBOOL   m_isImgPlaneByImgi;
    //
    MBOOL   m_Nr3dEn;
    MBOOL   m_Nr3dDmaSel;
};


////////////////////////////////////////////////////////////////////////////////
};  //namespace NSIspio
};  //namespace NSImageio
#endif  //  _ISPIO_POSTPROC_PIPE_H_

