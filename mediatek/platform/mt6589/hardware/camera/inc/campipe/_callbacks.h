#ifndef _MTK_CAMERA_INC_CAMPIPE_CALLBACKS_H_
#define _MTK_CAMERA_INC_CAMPIPE_CALLBACKS_H_


/*******************************************************************************
*
********************************************************************************/
namespace NSCamPipe {
////////////////////////////////////////////////////////////////////////////////


/**  
 * @struct PipeNotifyInfo
 * @brief This structure is the pipe notify callback 
 *
 */
struct PipeNotifyInfo
{
    /**
      * @var msgType 
      * The notify message type of the pipe-dependent notify message type. 
      */
    MUINT32     msgType;    //  
    /**
      * @var ext1 
      * The extended parameter 1.
      */         
    MUINT32     ext1;       //  Extended parameter 1.
    /**
      * @var ext2 
      * The extended parameter 2.
      */        
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


/**  
 * @struct PipeDataInfo
 * @brief This structure is the pipe data callback
 *
 */
struct PipeDataInfo
{
    /**
      * @var msgType 
      * Pipe-dependent Data Message Type.
      */     
    MUINT32     msgType;  
    /**
      * @var ext1 
      * Extended parameter 1.
      */     
    MUINT32     ext1;       //  
    /**
      * @var ext2 
      * Extended parameter 2.
      */     
    MUINT32     ext2;       //  
    /**
      * @var puData 
      * Pointer to the callback data.
      */     
    MUINT8*     puData;      
    /**
      * @var u4Size 
      * Size of the callback data.
      */     
    MUINT32     u4Size;     
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
};  //namespace NSCamPipe
#endif  //  _MTK_CAMERA_INC_CAMPIPE_CALLBACKS_H_

