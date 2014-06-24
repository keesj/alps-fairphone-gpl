#define LOG_TAG "NvramBufMgr"
#ifndef ENABLE_MY_LOG
    #define ENABLE_MY_LOG       (1)
#endif
//
#include <utils/Errors.h>
#include <cutils/log.h>
//
#include "../inc/nvram_drv.h"
#include "nvram_buf_mgr.h"
//
using namespace NSNvram;
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
NvramBufMgr&
NvramBufMgr::
getInstance()
{
    static NvramBufMgr singleton;
    return singleton;
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Buffers.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define SPECIALIZATION_GET_BUF(Buf_T, SensorEnum) \
    template <> \
    Buf_T* \
    NvramBufMgr::\
    getBuf<Buf_T, SensorEnum>() const \
    { \
        static Buf_T buf; \
        return &buf; \
    }


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Map Buffer Type to Command.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define MAP_BUF_TYPE_TO_CMD(Buf_T, Cmd)\
    template<> \
    struct BufT2Cmd<Buf_T> \
    { \
        static ENvramDrvCmd_T const val = Cmd; \
    }


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  NvramDrvBase::getBufIF()
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define SPECIALIZATION_GET_BUF_IF(Buf_T)\
    template <> \
    NSNvram::BufIF<Buf_T>* \
    NvramDrvBase:: \
    getBufIF() const \
    { \
        static NSNvram::ImpBufIF<Buf_T> singleton; \
        return &singleton; \
    }


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Specialization
//      getBuf
//      BufT2Cmd
//      getBufIF
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define _SPECIALIZATION_(Buf_T, Cmd) \
    namespace NSNvram { \
        SPECIALIZATION_GET_BUF(Buf_T, DUAL_CAMERA_MAIN_SENSOR); \
        SPECIALIZATION_GET_BUF(Buf_T, DUAL_CAMERA_MAIN_SECOND_SENSOR); \
        SPECIALIZATION_GET_BUF(Buf_T, DUAL_CAMERA_SUB_SENSOR); \
        MAP_BUF_TYPE_TO_CMD(Buf_T, Cmd); \
    } /* NSNvram */\
    SPECIALIZATION_GET_BUF_IF(Buf_T);


/*******************************************************************************
* List of Specializations.
*******************************************************************************/
//  To-add:
_SPECIALIZATION_( NVRAM_CAMERA_ISP_PARAM_STRUCT, CAMERA_NVRAM_DATA_ISP);
// namespace NSNvram {
//     SPECIALIZATION_GET_BUF(NVRAM_CAMERA_ISP_PARAM_STRUCT, DUAL_CAMERA_MAIN_SENSOR);
       // template <> Buf_T* NvramBufMgr::getBuf<NVRAM_CAMERA_ISP_PARAM_STRUCT, DUAL_CAMERA_MAIN_SENSOR>() const
       // {
       //     static NVRAM_CAMERA_ISP_PARAM_STRUCT buf;
       //     return &buf;
       // }
//     SPECIALIZATION_GET_BUF(NVRAM_CAMERA_ISP_PARAM_STRUCT, DUAL_CAMERA_SUB_SENSOR);
       // template <> Buf_T* NvramBufMgr::getBuf<NVRAM_CAMERA_ISP_PARAM_STRUCT, DUAL_CAMERA_SUB_SENSOR>() const
       // {
       //     static NVRAM_CAMERA_ISP_PARAM_STRUCT buf;
       //     return &buf;
       // }
//     MAP_BUF_TYPE_TO_CMD(NVRAM_CAMERA_ISP_PARAM_STRUCT, CAMERA_NVRAM_DATA_ISP);
       // template<> struct BufT2Cmd<NVRAM_CAMERA_ISP_PARAM_STRUCT>
       // {
       //     static ENvramDrvCmd_T const val = CAMERA_NVRAM_DATA_ISP;
       // }
// }
// SPECIALIZATION_GET_BUF_IF(NVRAM_CAMERA_ISP_PARAM_STRUCT);
    // template <> NSNvram::BufIF<NVRAM_CAMERA_ISP_PARAM_STRUCT>* NvramDrvBase:: getBufIF() const
    // {
    //     static NSNvram::ImpBufIF<NVRAM_CAMERA_ISP_PARAM_STRUCT> singleton;
    //     return &singleton;
    // }

_SPECIALIZATION_( NVRAM_CAMERA_SHADING_STRUCT  , CAMERA_NVRAM_DATA_SHADING);
_SPECIALIZATION_( NVRAM_CAMERA_3A_STRUCT   , CAMERA_NVRAM_DATA_3A);
_SPECIALIZATION_( NVRAM_LENS_PARA_STRUCT   , CAMERA_NVRAM_DATA_LENS);
_SPECIALIZATION_( AE_PLINETABLE_T   , CAMERA_DATA_AE_PLINETABLE);
_SPECIALIZATION_( NVRAM_CAMERA_STROBE_STRUCT   , CAMERA_NVRAM_DATA_STROBE);


















/*******************************************************************************
* Test
*******************************************************************************/
#if 0
void test()
{
    NvramDrvBase& rDrv = *NvramDrvBase::createInstance();

    //  NVRAM_CAMERA_ISP_PARAM_STRUCT
    {
    typedef NVRAM_CAMERA_ISP_PARAM_STRUCT   buf_t;
    NSNvram::BufIF<buf_t>*const pBufIF = rDrv.getBufIF<buf_t>();

    MINT32 err = 0;
    buf_t*      p  = pBufIF->getRefBuf(DUAL_CAMERA_MAIN_SENSOR, 0x1234);
    buf_t const*pc = pBufIF->getRefBuf(DUAL_CAMERA_MAIN_SENSOR, 0x1234);
               err = pBufIF->refresh  (DUAL_CAMERA_MAIN_SENSOR, 0x1234);
               err = pBufIF->flush    (DUAL_CAMERA_MAIN_SENSOR, 0x1234);
    }

    //  NVRAM_CAMERA_SHADING_STRUCT
    {
    typedef NVRAM_CAMERA_SHADING_STRUCT   buf_t;
    NSNvram::BufIF<buf_t>*const pBufIF = rDrv.getBufIF<buf_t>();

    MINT32 err = 0;
    buf_t*      p  = pBufIF->getRefBuf(DUAL_CAMERA_MAIN_SENSOR, 0x1234);
    buf_t const*pc = pBufIF->getRefBuf(DUAL_CAMERA_MAIN_SENSOR, 0x1234);
               err = pBufIF->refresh  (DUAL_CAMERA_MAIN_SENSOR, 0x1234);
               err = pBufIF->flush    (DUAL_CAMERA_MAIN_SENSOR, 0x1234);
    }

    //  NVRAM_CAMERA_DEFECT_STRUCT
    {
    typedef NVRAM_CAMERA_DEFECT_STRUCT   buf_t;
    NSNvram::BufIF<buf_t>*const pBufIF = rDrv.getBufIF<buf_t>();

    MINT32 err = 0;
    buf_t*      p  = pBufIF->getRefBuf(DUAL_CAMERA_MAIN_SENSOR, 0x1234);
    buf_t const*pc = pBufIF->getRefBuf(DUAL_CAMERA_MAIN_SENSOR, 0x1234);
               err = pBufIF->refresh  (DUAL_CAMERA_MAIN_SENSOR, 0x1234);
               err = pBufIF->flush    (DUAL_CAMERA_MAIN_SENSOR, 0x1234);
    }

    rDrv.destroyInstance();
}
#endif

