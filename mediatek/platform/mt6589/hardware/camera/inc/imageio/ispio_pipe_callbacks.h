#ifndef _ISPIO_PIPE_CALLBACKS_H_
#define _ISPIO_PIPE_CALLBACKS_H_


/*******************************************************************************
*
********************************************************************************/
namespace NSImageio {
namespace NSIspio   {
////////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
* Pipe Notify Callback
********************************************************************************/
struct PipeNotifyInfo
{
    MUINT32     msgType;    //  Pipe-dependent Notify Message Type.
    MUINT32     ext1;       //  Extended parameter 1.
    MUINT32     ext2;       //  Extended parameter 2.
    //
    PipeNotifyInfo(
        MUINT32 const _msgType = 0, 
        MUINT32 const _ext1 = 0, 
        MUINT32 const _ext2 = 0
    )
        : msgType(_msgType)
        , ext1(_ext1)
        , ext2(_ext2)
    {}
};

typedef MBOOL   (*PipeNotifyCallback_t)(MVOID* user, PipeNotifyInfo const msg);


/*******************************************************************************
* Pipe Data Callback
********************************************************************************/
struct PipeDataInfo
{
    MUINT32     msgType;    //  Pipe-dependent Data Message Type.
    MUINT32     ext1;       //  Extended parameter 1.
    MUINT32     ext2;       //  Extended parameter 2.
    MUINT8*     puData;     //  Pointer to the callback data.
    MUINT32     u4Size;     //  Size of the callback data.
    //
    PipeDataInfo(
        MUINT32 const _msgType = 0, 
        MUINT32 const _ext1 = 0, 
        MUINT32 const _ext2 = 0, 
        MUINT8* const _puData = NULL, 
        MUINT32 const _u4Size = 0
    )
        : msgType(_msgType)
        , ext1(_ext1)
        , ext2(_ext2)
        , puData(_puData)
        , u4Size(_u4Size)
    {
    }
};

typedef MBOOL   (*PipeDataCallback_t)(MVOID* user, PipeDataInfo const msg);


////////////////////////////////////////////////////////////////////////////////
};  //namespace NSIspio
};  //namespace NSImageio
#endif  //  _ISPIO_PIPE_CALLBACKS_H_

