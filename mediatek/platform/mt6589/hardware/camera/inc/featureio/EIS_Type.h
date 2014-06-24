//!\file  EIS_Type.h

#ifndef _EIS_TYPE_H_
#define _EIS_TYPE_H_

#include "CamTypes.h"
#include "../algorithm/libeis/MTKEis.h"


#define EIS_MAX_WIN_NUM EIS_WIN_NUM

/**  
*@enum EIS_ERROR_ENUM
*@brief Return enum of EIS
*/
typedef enum 
{
    EIS_RETURN_NO_ERROR         = 0,       //! The function work successfully
    EIS_RETURN_UNKNOWN_ERROR    = 0x0001,  //! Unknown error
    EIS_RETURN_INVALID_DRIVER   = 0x0002,  //! invalid driver object
    EIS_RETURN_API_FAIL         = 0x0003,  //! api fail
    EIS_RETURN_INVALID_PARA     = 0x0004,  //! invalid parameter
    EIS_RETURN_NULL_OBJ         = 0x0005,  //! null object  
    EIS_RETURN_MEMORY_ERROR     = 0x0006   //! memory error
} EIS_ERROR_ENUM;

/**  
*@struct EIS_STATISTIC_T
*@brief  EIS statistic data structure
*/
typedef struct
{
    MINT32 i4LMV_X[EIS_MAX_WIN_NUM];
    MINT32 i4LMV_Y[EIS_MAX_WIN_NUM];

    MINT32 i4LMV_X2[EIS_MAX_WIN_NUM];
    MINT32 i4LMV_Y2[EIS_MAX_WIN_NUM];

    MINT32 i4NewTrust_X[EIS_MAX_WIN_NUM];
    MINT32 i4NewTrust_Y[EIS_MAX_WIN_NUM];

    MINT32 i4SAD[EIS_MAX_WIN_NUM];
    MINT32 i4SAD2[EIS_MAX_WIN_NUM];    
    MINT32 i4AVG[EIS_MAX_WIN_NUM];
} EIS_STATISTIC_T;

#endif // _EIS_TYPE_H_

