#ifndef _MTK_EIS_ERRCODE_H
#define _MTK_EIS_ERRCODE_H


///////////////////////////////////////////////////////////////////////////
//! Error code type definition
///////////////////////////////////////////////////////////////////////////
typedef MINT32 MRESULT;

///////////////////////////////////////////////////////////////////////////
//! Helper macros to define error code
///////////////////////////////////////////////////////////////////////////
#define ERRCODE(modid, errid)           \
  ((MINT32)                              \
    ((MUINT32)(0x80000000) |             \
     (MUINT32)((modid & 0x7f) << 24) |   \
     (MUINT32)(errid & 0xffff))          \
  )

#define OKCODE(modid, okid)             \
  ((MINT32)                              \
    ((MUINT32)(0x00000000) |             \
     (MUINT32)((modid & 0x7f) << 24) |   \
     (MUINT32)(okid & 0xffff))           \
  )

///////////////////////////////////////////////////////////////////////////
//! Helper macros to check error code
///////////////////////////////////////////////////////////////////////////
#define SUCCEEDED(Status)   ((MRESULT)(Status) >= 0)
#define FAILED(Status)      ((MRESULT)(Status) < 0)

#define MODULE_MTK_EIS (5) // Temp value

#define MTKEIS_OKCODE(errid)         OKCODE(MODULE_MTK_EIS, errid)
#define MTKEIS_ERRCODE(errid)        ERRCODE(MODULE_MTK_EIS, errid)


//Error code
#define S_EIS_OK                  MTKEIS_OKCODE(0x0000)

#define E_EIS_NEED_OVER_WRITE     MTKEIS_ERRCODE(0x0001)
#define E_EIS_NULL_OBJECT         MTKEIS_ERRCODE(0x0002)
#define E_EIS_WRONG_STATE         MTKEIS_ERRCODE(0x0003)
#define E_EIS_WRONG_CMD_ID        MTKEIS_ERRCODE(0x0004)
#define E_EIS_WRONG_CMD_PARAM     MTKEIS_ERRCODE(0x0005)
#define E_EIS_NOT_ENOUGH_MEM      MTKEIS_ERRCODE(0x0006)
#define E_EIS_NULL_INIT_PARAM     MTKEIS_ERRCODE(0x0007)
#define E_EIS_LOG_BUFFER_NOT_ENOUGH MTKEIS_ERRCODE(0x0008)
#define E_EIS_SET_NULL_PROCESS_INFO MTKEIS_ERRCODE(0x0009)
#define E_EIS_SET_NULL_IMAGE_SIZE_INFO MTKEIS_ERRCODE(0x000A)
#define E_EIS_SET_WRONG_IMAGE_SIZE MTKEIS_ERRCODE(0x000B)
#define E_EIS_OPEN_LOG_FILE_ERROR MTKEIS_ERRCODE(0x000C)


#define E_EIS_ERR                 MTKEIS_ERRCODE(0x0100)

#endif

