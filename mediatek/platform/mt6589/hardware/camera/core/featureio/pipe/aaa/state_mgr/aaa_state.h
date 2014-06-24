#ifndef _AAA_STATE_H_
#define _AAA_STATE_H_

#include <utils/threads.h>

using namespace android;

namespace NS3A
{

typedef enum {
     eIntent_CameraPreviewStart = ECmd_CameraPreviewStart,
     eIntent_CameraPreviewEnd = ECmd_CameraPreviewEnd,
     eIntent_CamcorderPreviewStart = ECmd_CamcorderPreviewStart,
     eIntent_CamcorderPreviewEnd = ECmd_CamcorderPreviewEnd,
     eIntent_PrecaptureStart = ECmd_PrecaptureStart,
     eIntent_PrecaptureEnd = ECmd_PrecaptureEnd,
     eIntent_CaptureStart = ECmd_CaptureStart,
     eIntent_CaptureEnd = ECmd_CaptureEnd,
     eIntent_RecordingStart = ECmd_RecordingStart,
     eIntent_RecordingEnd = ECmd_RecordingEnd,
     eIntent_VsyncUpdate = ECmd_Update,
     eIntent_AFUpdate = ECmd_AFUpdate,
     eIntent_AFStart = ECmd_AFStart,
     eIntent_AFEnd = ECmd_AFEnd,
     eIntent_Init = ECmd_Init,
     eIntent_Uninit = ECmd_Uninit
} EIntent_T;

typedef enum
{
	eState_Invalid=-1,
    eState_Uninit,
    eState_Init,
    eState_CameraPreview,
    eState_CamcorderPreview,
    eState_Precapture,
    eState_Capture,
    eState_Recording,
    eState_AF
} EState_T;


template<EIntent_T eIntent> struct intent2type { enum {v=eIntent}; };

class StateMgr;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  IState
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class IState
{
public:
    IState(char const*const pcszName);
    virtual ~IState() {};


public:     //    Interfaces
    virtual MRESULT  sendIntent(intent2type<eIntent_CameraPreviewStart>) {
            MY_ERR("[%s]E_3A_UNSUPPORT_COMMAND: eIntent_CameraPreviewStart", m_pcszName);
            return  E_3A_UNSUPPORT_COMMAND;
        }
    virtual MRESULT  sendIntent(intent2type<eIntent_CameraPreviewEnd>) {
            MY_ERR("[%s]E_3A_UNSUPPORT_COMMAND: eIntent_CameraPreviewEnd", m_pcszName);
            return  E_3A_UNSUPPORT_COMMAND;
        }
    virtual MRESULT  sendIntent(intent2type<eIntent_CamcorderPreviewStart>) {
            MY_ERR("[%s]E_3A_UNSUPPORT_COMMAND: eIntent_CamcorderPreviewStart", m_pcszName);
            return  E_3A_UNSUPPORT_COMMAND;
        }
    virtual MRESULT  sendIntent(intent2type<eIntent_CamcorderPreviewEnd>) {
            MY_ERR("[%s]E_3A_UNSUPPORT_COMMAND: eIntent_CamcorderPreviewEnd", m_pcszName);
            return  E_3A_UNSUPPORT_COMMAND;
        }
    virtual MRESULT  sendIntent(intent2type<eIntent_PrecaptureStart>) {
            MY_ERR("[%s]E_3A_UNSUPPORT_COMMAND: eIntent_PrecaptureStart", m_pcszName);
            return  E_3A_UNSUPPORT_COMMAND;
        }
    virtual MRESULT  sendIntent(intent2type<eIntent_PrecaptureEnd>) {
            MY_ERR("[%s]E_3A_UNSUPPORT_COMMAND: eIntent_PrecaptureEnd", m_pcszName);
            return  E_3A_UNSUPPORT_COMMAND;
        }
    virtual MRESULT  sendIntent(intent2type<eIntent_CaptureStart>) {
            MY_ERR("[%s]E_3A_UNSUPPORT_COMMAND: eIntent_CaptureStart", m_pcszName);
            return  E_3A_UNSUPPORT_COMMAND;
        }
    virtual MRESULT  sendIntent(intent2type<eIntent_CaptureEnd>) {
            MY_ERR("[%s]E_3A_UNSUPPORT_COMMAND: eIntent_CaptureEnd", m_pcszName);
            return  E_3A_UNSUPPORT_COMMAND;
        }
    virtual MRESULT  sendIntent(intent2type<eIntent_RecordingStart>) {
            MY_ERR("[%s]E_3A_UNSUPPORT_COMMAND: eIntent_RecordingStart", m_pcszName);
            return  E_3A_UNSUPPORT_COMMAND;
        }
    virtual MRESULT  sendIntent(intent2type<eIntent_RecordingEnd>) {
            MY_ERR("[%s]E_3A_UNSUPPORT_COMMAND: eIntent_RecordingEnd", m_pcszName);
            return  E_3A_UNSUPPORT_COMMAND;
        }
    virtual MRESULT  sendIntent(intent2type<eIntent_VsyncUpdate>) {
            MY_ERR("[%s]E_3A_UNSUPPORT_COMMAND: eIntent_VsyncUpdate", m_pcszName);
            return  E_3A_UNSUPPORT_COMMAND;
        }
    virtual MRESULT  sendIntent(intent2type<eIntent_AFUpdate>) {
            MY_ERR("[%s]E_3A_UNSUPPORT_COMMAND: eIntent_AFUpdate", m_pcszName);
            return  E_3A_UNSUPPORT_COMMAND;
        }
    virtual MRESULT  sendIntent(intent2type<eIntent_AFStart>) {
            MY_ERR("[%s]E_3A_UNSUPPORT_COMMAND: eIntent_AFStart", m_pcszName);
            return  E_3A_UNSUPPORT_COMMAND;
        }
    virtual MRESULT  sendIntent(intent2type<eIntent_AFEnd>) {
            MY_ERR("[%s]E_3A_UNSUPPORT_COMMAND: eIntent_AFEnd", m_pcszName);
            return  E_3A_UNSUPPORT_COMMAND;
        }
    virtual MRESULT  sendIntent(intent2type<eIntent_Init>) {
            MY_ERR("[%s]E_3A_UNSUPPORT_COMMAND: eIntent_Init", m_pcszName);
            return  E_3A_UNSUPPORT_COMMAND;
        }
    virtual MRESULT  sendIntent(intent2type<eIntent_Uninit>) {
            MY_ERR("[%s]E_3A_UNSUPPORT_COMMAND: eIntent_Uninit", m_pcszName);
            return  E_3A_UNSUPPORT_COMMAND;
        }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:     ////    Operations.
    virtual char const* getName() const { return m_pcszName; }

protected:  ////    Data Members.
    Hal3A*              m_pHal3A;
    char const*const    m_pcszName;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  States
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:

protected:

    MRESULT transitState(EState_T const eCurrState, EState_T const eNewState);


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  AF States
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
protected:

    typedef enum
    {
        eAFState_None,
        eAFState_PreAF,
        eAFState_AF,
        eAFState_PostAF
    } EAFState_T;

    static EAFState_T m_eAFState;

    inline MVOID transitAFState(EAFState_T const eNewAFState)
    {
        m_eAFState = eNewAFState;
    }

    inline EAFState_T getAFState()
    {
        return m_eAFState;
    }

private:
    static IState*  getStateInstance(EState_T const eState);
    static IState*  sm_pCurrState;  //  Pointer to the current state.
    static IState*  getCurrStateInstance();
    friend class StateMgr;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Frame count
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
private:
    static MINT32  m_i4FrameCount;

public:
    inline MVOID  updateFrameCount()
    {
        if (++m_i4FrameCount >= 0x7FFFFFFF)
        {
            m_i4FrameCount = 0;
        }
    }

    inline MVOID  resetFrameCount()
    {
            m_i4FrameCount = -3; // delay 2 frames for 3A statistics ready
    }

    inline MINT32  getFrameCount()
    {
            return m_i4FrameCount;
    }


};


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  StateUninit
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
struct StateUninit : public IState
{
    StateUninit();
    virtual MRESULT  sendIntent(intent2type<eIntent_Init>);
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  StateInit
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
struct StateInit : public IState
{
    StateInit();
    virtual MRESULT  sendIntent(intent2type<eIntent_Uninit>);
    virtual MRESULT  sendIntent(intent2type<eIntent_CameraPreviewStart>);
    virtual MRESULT  sendIntent(intent2type<eIntent_CamcorderPreviewStart>);
    virtual MRESULT  sendIntent(intent2type<eIntent_AFUpdate>);
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  StateCameraPreview
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
struct StateCameraPreview : public IState
{
    StateCameraPreview();
    virtual MRESULT  sendIntent(intent2type<eIntent_Uninit>);
    virtual MRESULT  sendIntent(intent2type<eIntent_CameraPreviewStart>);
    virtual MRESULT  sendIntent(intent2type<eIntent_CameraPreviewEnd>);
    virtual MRESULT  sendIntent(intent2type<eIntent_VsyncUpdate>);
    virtual MRESULT  sendIntent(intent2type<eIntent_AFUpdate>);
    virtual MRESULT  sendIntent(intent2type<eIntent_PrecaptureStart>);
    virtual MRESULT  sendIntent(intent2type<eIntent_CaptureStart>); //for zsd
    virtual MRESULT  sendIntent(intent2type<eIntent_AFStart>);
    virtual MRESULT  sendIntent(intent2type<eIntent_AFEnd>);
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  StateCamcorderPreview
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
struct StateCamcorderPreview : public IState
{
    StateCamcorderPreview();
    virtual MRESULT  sendIntent(intent2type<eIntent_Uninit>);
    virtual MRESULT  sendIntent(intent2type<eIntent_CamcorderPreviewStart>);
    virtual MRESULT  sendIntent(intent2type<eIntent_CamcorderPreviewEnd>);
    virtual MRESULT  sendIntent(intent2type<eIntent_VsyncUpdate>);
    virtual MRESULT  sendIntent(intent2type<eIntent_AFUpdate>);
    virtual MRESULT  sendIntent(intent2type<eIntent_RecordingStart>);
    virtual MRESULT  sendIntent(intent2type<eIntent_AFStart>);
    virtual MRESULT  sendIntent(intent2type<eIntent_AFEnd>);
    virtual MRESULT  sendIntent(intent2type<eIntent_PrecaptureStart>); // for CTS only
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  StatePrecapture
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
struct StatePrecapture : public IState
{
    StatePrecapture();
    virtual MRESULT  sendIntent(intent2type<eIntent_PrecaptureStart>);
    virtual MRESULT  sendIntent(intent2type<eIntent_PrecaptureEnd>);
    virtual MRESULT  sendIntent(intent2type<eIntent_VsyncUpdate>);
    virtual MRESULT  sendIntent(intent2type<eIntent_AFUpdate>);
    virtual MRESULT  sendIntent(intent2type<eIntent_CaptureStart>);
    virtual MRESULT  sendIntent(intent2type<eIntent_CameraPreviewEnd>);
    virtual MRESULT  sendIntent(intent2type<eIntent_CamcorderPreviewEnd>);
    virtual MRESULT  sendIntent(intent2type<eIntent_AFEnd>);
};


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  StateCapture
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
struct StateCapture : public IState
{
    StateCapture();
    virtual MRESULT  sendIntent(intent2type<eIntent_CaptureStart>);
    virtual MRESULT  sendIntent(intent2type<eIntent_CaptureEnd>);
    virtual MRESULT  sendIntent(intent2type<eIntent_VsyncUpdate>);
    virtual MRESULT  sendIntent(intent2type<eIntent_AFUpdate>);
    virtual MRESULT  sendIntent(intent2type<eIntent_CameraPreviewStart>);
    virtual MRESULT  sendIntent(intent2type<eIntent_CameraPreviewEnd>); // for ZSD capture
    virtual MRESULT  sendIntent(intent2type<eIntent_AFEnd>);
    virtual MRESULT  sendIntent(intent2type<eIntent_Uninit>);
    virtual MRESULT  sendIntent(intent2type<eIntent_CamcorderPreviewStart>); // for CTS only
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  StateRecording
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
struct StateRecording : public IState
{
    StateRecording();
    virtual MRESULT  sendIntent(intent2type<eIntent_CamcorderPreviewEnd>);
    virtual MRESULT  sendIntent(intent2type<eIntent_RecordingStart>);
    virtual MRESULT  sendIntent(intent2type<eIntent_RecordingEnd>);
    virtual MRESULT  sendIntent(intent2type<eIntent_VsyncUpdate>);
    virtual MRESULT  sendIntent(intent2type<eIntent_AFUpdate>);
    virtual MRESULT  sendIntent(intent2type<eIntent_AFStart>);
    virtual MRESULT  sendIntent(intent2type<eIntent_AFEnd>);

    MRESULT exitPreview();
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  StateAF
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
struct StateAF : public IState
{
    StateAF();
    virtual MRESULT  sendIntent(intent2type<eIntent_AFStart>);
    virtual MRESULT  sendIntent(intent2type<eIntent_AFEnd>);
    virtual MRESULT  sendIntent(intent2type<eIntent_Uninit>);    
    virtual MRESULT  sendIntent(intent2type<eIntent_VsyncUpdate>);
    virtual MRESULT  sendIntent(intent2type<eIntent_AFUpdate>);
    virtual MRESULT  sendIntent(intent2type<eIntent_PrecaptureStart>);
    virtual MRESULT  sendIntent(intent2type<eIntent_CameraPreviewEnd>);
    virtual MRESULT  sendIntent(intent2type<eIntent_CamcorderPreviewEnd>);
    virtual MRESULT  sendIntent(intent2type<eIntent_CameraPreviewStart>);
    virtual MRESULT  sendIntent(intent2type<eIntent_CamcorderPreviewStart>);
    virtual MRESULT  sendIntent(intent2type<eIntent_RecordingEnd>);




    template<EAFState_T eAFState> struct state2type { enum {v=eAFState}; };

    MRESULT  sendAFIntent(intent2type<eIntent_VsyncUpdate>, state2type<eAFState_None>);
    MRESULT  sendAFIntent(intent2type<eIntent_AFUpdate>, state2type<eAFState_None>);
    MRESULT  sendAFIntent(intent2type<eIntent_VsyncUpdate>, state2type<eAFState_PreAF>);
    MRESULT  sendAFIntent(intent2type<eIntent_AFUpdate>, state2type<eAFState_PreAF>);
    MRESULT  sendAFIntent(intent2type<eIntent_VsyncUpdate>, state2type<eAFState_AF>);
    MRESULT  sendAFIntent(intent2type<eIntent_AFUpdate>, state2type<eAFState_AF>);
    MRESULT  sendAFIntent(intent2type<eIntent_VsyncUpdate>, state2type<eAFState_PostAF>);
    MRESULT  sendAFIntent(intent2type<eIntent_AFUpdate>, state2type<eAFState_PostAF>);
    MRESULT exitPreview();

};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  State Manager
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class StateMgr
{
public:
    static StateMgr& getInstance()
    {
        static StateMgr singleton;
        return singleton;
    }

    StateMgr() : m_Lock() {}

    MRESULT sendCmd(ECmd_T eCmd)
    {
        Mutex::Autolock lock(m_Lock);

        EIntent_T eNewIntent = static_cast<EIntent_T>(eCmd);

        #define SEND_INTENT(_intent_)\
        case _intent_: return IState::getCurrStateInstance()->sendIntent(intent2type<_intent_>());\

        switch (eNewIntent)
        {
        SEND_INTENT(eIntent_CameraPreviewStart)
        SEND_INTENT(eIntent_CameraPreviewEnd)
        SEND_INTENT(eIntent_CamcorderPreviewStart)
        SEND_INTENT(eIntent_CamcorderPreviewEnd)
        SEND_INTENT(eIntent_PrecaptureStart)
        SEND_INTENT(eIntent_PrecaptureEnd)
        SEND_INTENT(eIntent_CaptureStart)
        SEND_INTENT(eIntent_CaptureEnd)
        SEND_INTENT(eIntent_RecordingStart)
        SEND_INTENT(eIntent_RecordingEnd)
        SEND_INTENT(eIntent_VsyncUpdate)
        SEND_INTENT(eIntent_AFUpdate)
        SEND_INTENT(eIntent_AFStart)
        SEND_INTENT(eIntent_AFEnd)
        SEND_INTENT(eIntent_Init)
        SEND_INTENT(eIntent_Uninit)
        }
        return  -1;
    }

private:
    mutable Mutex m_Lock;
};



};  //  namespace NS3A
#endif // _AAA_STATE_H_

