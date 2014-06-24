#ifndef _ISPIO_PIPE_BUFFER_H_
#define _ISPIO_PIPE_BUFFER_H_
//
#include "ispio_stddef.h"
#include <sys/time.h>
#include <vector>
using namespace std;
/*******************************************************************************
*
********************************************************************************/
namespace NSImageio {
namespace NSIspio   {
////////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
* Pipe Buffer Info
********************************************************************************/
struct QBufInfo
{
public: ////    fields.
    /*
     * user-specific data. Cannot be modified by pipes.
     */
    MUINT32             u4User;
    /*
     * reserved data. Cannot be modified by pipes.
     */
    MUINT32             u4Reserved;
    //
    MUINT32             u4BufIndex;
    /*
     * vector of buffer information.
     * Note:
     *      The vector size depends on the image format. For example, the vector
     *      must contain 3 buffer information for yuv420 3-plane.
     */
    vector<BufInfo>     vBufInfo;
    //
public:     //// constructors.
    QBufInfo(MUINT32 const _u4User = 0)
        : u4User(0)
        , u4Reserved(0)
        , vBufInfo()
    {
    }
    //
};


/*******************************************************************************
* Pipe Buffer Info with Timestamp
********************************************************************************/
struct QTimeStampBufInfo : public QBufInfo
{
public: ////    fields.
    MINT32              i4TimeStamp_sec;//  time stamp in seconds.
    MINT32              i4TimeStamp_us; //  time stamp in microseconds
    //
    MUINT32             u4BufIndex; //buffer index
    //
public:     //// constructors.
    QTimeStampBufInfo(MUINT32 const _u4User = 0)
        : QBufInfo(_u4User)
        , i4TimeStamp_sec(0)
        , i4TimeStamp_us(0)
    {
    }
    //
public: ////    operations.
    inline MINT64   getTimeStamp_ns() const
    {
        return  i4TimeStamp_sec * 1000000000LL + i4TimeStamp_us * 1000LL;
    }
    //
    inline MBOOL    setTimeStamp()
    {
        struct timeval tv;
        if  ( 0 == ::gettimeofday(&tv, NULL) )
        {
            i4TimeStamp_sec = tv.tv_sec;
            i4TimeStamp_us  = tv.tv_usec;
            return  MTRUE;
        }
        return  MFALSE;
    }
    //
};

//
//
struct MemInfo {
    MUINT32 virtAddr; 
    MUINT32 phyAddr; 
    MUINT32 bufCnt; 
    MUINT32 bufSize; 
    //
    MemInfo(MUINT32 const _virtAddr = 0,           
              MUINT32 const _phyAddr = 0, 
              MUINT32 const _bufCnt = 0, 
              MUINT32 const _bufSize = 0
             )
              : virtAddr(_virtAddr), phyAddr(_phyAddr),
                bufCnt(_bufCnt), bufSize(_bufSize)
    {}
};   


////////////////////////////////////////////////////////////////////////////////
};  //namespace NSIspio
};  //namespace NSImageio
#endif  //  _ISPIO_PIPE_BUFFER_H_

