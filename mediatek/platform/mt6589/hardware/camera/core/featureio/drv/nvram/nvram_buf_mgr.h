#ifndef _NVRAM_BUF_MGR_H_
#define _NVRAM_BUF_MGR_H_


/*******************************************************************************
*
*******************************************************************************/
namespace NSNvram
{


/*******************************************************************************
*   NVRAM Buffer Manager
*******************************************************************************/
class NvramBufMgr
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:     ////    Autolock

    friend  class Autolock;
    class Autolock
    {
    public:
        Autolock()
            : m_pMutex(&NvramBufMgr::getInstance().m_mutex)
        {
            ::pthread_mutex_lock(m_pMutex);
        }

        ~Autolock()
        {
            ::pthread_mutex_unlock(m_pMutex);
        }

    private:
        pthread_mutex_t*const   m_pMutex;
    };

private:    ////    Data Members.

    NvramDrvBase&   m_rNvramDrv;
    pthread_mutex_t m_mutex;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:    ////    Instance.

    NvramBufMgr()
        : m_rNvramDrv(*NvramDrvBase::createInstance())
        , m_mutex()
    {
        ::pthread_mutex_init(&m_mutex, NULL);
    }

    ~NvramBufMgr()
    {
        m_rNvramDrv.destroyInstance();
    }

public:     ////    Singleton.
    static NvramBufMgr&     getInstance();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:    ////    Nvram Data.

    template <class Buf_T, ESensorEnum_T SensorEnum>
    Buf_T* getBuf() const;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Interfaces.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:     ////

    template <class Buf_T, ENvramDrvCmd_T Cmd, ESensorEnum_T SensorEnum>
    MINT32
    flush(MUINT32 const u4SensorID)
    {
        return  m_rNvramDrv.writeNvram   (
            SensorEnum, u4SensorID, Cmd,
            getBuf<Buf_T, SensorEnum>(), sizeof(Buf_T)
        );
    }

    template <class Buf_T, ENvramDrvCmd_T Cmd, ESensorEnum_T SensorEnum>
    MINT32
    refresh(MUINT32 const u4SensorID)
    {
        return  m_rNvramDrv.readNvram   (
            SensorEnum, u4SensorID, Cmd,
            getBuf<Buf_T, SensorEnum>(), sizeof(Buf_T)
        );
    }

    template <class Buf_T, ENvramDrvCmd_T Cmd, ESensorEnum_T SensorEnum>
    Buf_T*
    getBuf(MUINT32 const u4SensorID)
    {
        static bool fgInitialized = false;
        if  (
                fgInitialized
            || (fgInitialized = (0 == refresh<Buf_T, Cmd, SensorEnum>(u4SensorID)))
            )
            return  getBuf<Buf_T, SensorEnum>();
        return  NULL;
    }

};


/*******************************************************************************
*
*   Map Buffer Type to Command.
*
*       template <class Buf_T> struct BufT2Cmd;
*       template<> struct BufT2Cmd<Buf_T>
*       {
*           static ENvramDrvCmd_T const val = ???;
*       };
*
*******************************************************************************/
template <class Buf_T> struct BufT2Cmd;


/*******************************************************************************
*   Implementation of Buffer I/F
*******************************************************************************/
template <class Buf_T>
struct ImpBufIF : public BufIF<Buf_T>
{
    static ENvramDrvCmd_T const Cmd = BufT2Cmd<Buf_T>::val;

    virtual
    Buf_T*
    getRefBuf(
        ESensorEnum_T const eSensorEnum, MUINT32 const u4SensorID
    )
    {
        NvramBufMgr::Autolock lock;
        switch  (eSensorEnum)
        {
        case DUAL_CAMERA_MAIN_SENSOR:
            return  NvramBufMgr::getInstance().getBuf<
                        Buf_T, Cmd, DUAL_CAMERA_MAIN_SENSOR
                    >(u4SensorID);
        case DUAL_CAMERA_MAIN_SECOND_SENSOR:
            return  NvramBufMgr::getInstance().getBuf<
                        Buf_T, Cmd, DUAL_CAMERA_MAIN_SECOND_SENSOR
                    >(u4SensorID);
        case DUAL_CAMERA_SUB_SENSOR:
            return  NvramBufMgr::getInstance().getBuf<
                        Buf_T, Cmd, DUAL_CAMERA_SUB_SENSOR
                    >(u4SensorID);
        default:
            break;
        }
        return NULL;
    }

    virtual
    MINT32
    refresh(
        ESensorEnum_T const eSensorEnum, MUINT32 const u4SensorID
    )
    {
        NvramBufMgr::Autolock lock;
        switch  (eSensorEnum)
        {
        case DUAL_CAMERA_MAIN_SENSOR:
            return  NvramBufMgr::getInstance().refresh<
                        Buf_T, Cmd, DUAL_CAMERA_MAIN_SENSOR
                    >(u4SensorID);
        case DUAL_CAMERA_MAIN_SECOND_SENSOR:
            return  NvramBufMgr::getInstance().refresh<
                        Buf_T, Cmd, DUAL_CAMERA_MAIN_SECOND_SENSOR
                    >(u4SensorID);
        case DUAL_CAMERA_SUB_SENSOR:
            return  NvramBufMgr::getInstance().refresh<
                        Buf_T, Cmd, DUAL_CAMERA_SUB_SENSOR
                    >(u4SensorID);
        default:
            break;
        }
        return  NVRAM_BAD_SENSOR_ENUM;
    }

    virtual
    MINT32
    flush(
        ESensorEnum_T const eSensorEnum, MUINT32 const u4SensorID
    )
    {
        NvramBufMgr::Autolock lock;
        switch  (eSensorEnum)
        {
        case DUAL_CAMERA_MAIN_SENSOR:
            return  NvramBufMgr::getInstance().flush<
                        Buf_T, Cmd, DUAL_CAMERA_MAIN_SENSOR
                    >(u4SensorID);
        case DUAL_CAMERA_MAIN_SECOND_SENSOR:
            return  NvramBufMgr::getInstance().flush<
                        Buf_T, Cmd, DUAL_CAMERA_MAIN_SECOND_SENSOR
                    >(u4SensorID);
        case DUAL_CAMERA_SUB_SENSOR:
            return  NvramBufMgr::getInstance().flush<
                        Buf_T, Cmd, DUAL_CAMERA_SUB_SENSOR
                    >(u4SensorID);
        default:
            break;
        }
        return  NVRAM_BAD_SENSOR_ENUM;
    }

};


/*******************************************************************************
*
*******************************************************************************/
};  //  NSNvram
#endif // _NVRAM_BUF_MGR_H_

