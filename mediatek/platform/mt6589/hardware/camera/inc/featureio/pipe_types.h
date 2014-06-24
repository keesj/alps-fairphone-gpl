#ifndef _PIPE_TYPES_H
#define _PIPE_TYPES_H

/*******************************************************************************
*
*******************************************************************************/
typedef unsigned char   MUINT8;
typedef unsigned short  MUINT16;
typedef unsigned int    MUINT32;
typedef unsigned long long  MUINT64;
typedef signed char     MINT8;
typedef signed short    MINT16;
typedef signed int      MINT32;
typedef signed long long  MINT64;
typedef void            MVOID;
typedef int             MBOOL;
#ifndef MTRUE
    #define MTRUE       1
#endif
#ifndef MFALSE
    #define MFALSE      0
#endif

typedef float				MFLOAT;
/*******************************************************************************
*
*******************************************************************************/
#endif // _PIPE_TYPES_H

