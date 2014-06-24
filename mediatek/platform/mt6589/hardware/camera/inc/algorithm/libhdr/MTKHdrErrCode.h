#ifndef _MTK_HDR_ERRCODE_H
#define _MTK_HDR_ERRCODE_H


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

#define MODULE_MTK_HDR (0) // Temp value

#define MTKHDR_OKCODE(errid)         OKCODE(MODULE_MTK_HDR, errid)
#define MTKHDR_ERRCODE(errid)        ERRCODE(MODULE_MTK_HDR, errid)


//Error code
#define S_HDR_OK                  MTKHDR_OKCODE(0x0000)

#define E_HDR_NEED_OVER_WRITE     MTKHDR_ERRCODE(0x0001)
#define E_HDR_NULL_OBJECT         MTKHDR_ERRCODE(0x0002)
#define E_HDR_WRONG_STATE         MTKHDR_ERRCODE(0x0003)
#define E_HDR_WRONG_CMD_ID        MTKHDR_ERRCODE(0x0004)
#define E_HDR_WRONG_CMD_PARAM     MTKHDR_ERRCODE(0x0005)
#define E_HDR_NOT_ENOUGH_MEM     MTKHDR_ERRCODE(0x0006)
#define E_BMAP_BUFFER_NOT_ENOUGH MTKHDR_ERRCODE(0x0007)
#define E_RESULT_BUFFER_NOT_ENOUGH MTKHDR_ERRCODE(0x0008)
#define E_OPEN_LOG_FILE_FAIL MTKHDR_ERRCODE(0x0009)

#define E_TO3D_ERR                 MTKHDR_ERRCODE(0x0100)

#endif

