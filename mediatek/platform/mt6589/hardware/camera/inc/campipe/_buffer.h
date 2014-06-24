#ifndef _MTK_CAMERA_INC_CAMPIPE_BUFFER_H_
#define _MTK_CAMERA_INC_CAMPIPE_BUFFER_H_
//

using namespace NSCamHW; 

/*******************************************************************************
*
********************************************************************************/
namespace NSCamPipe {
////////////////////////////////////////////////////////////////////////////////


/**  
 * @struct QBufInfo
 * @brief This structure is for the pipe buffer info
 *
 */
struct QBufInfo
{
public: ////    fields.
    /**
      * @var u4User 
      * user-specific data. Cannot be modified by pipes.
      */      
    MUINT32             u4User;
    /**
      * @var u4Reserved 
      * reserved data. Cannot be modified by pipes.
      */     
    MUINT32             u4Reserved;
    /**
      * @var vBufInfo 
      * vector of buffer information.
      * @note: The vector size depends on the image format. For example, the vector \n
      *            must contain 3 buffer information for yuv420 3-plane.      
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


/**  
 * @struct QTimeStampBufInfo
 * @brief This structure is pipe buffer info with timestamp
 *
 */
struct QTimeStampBufInfo : public QBufInfo
{
public: ////    fields.
    /**
      * @var i4TimeStamp_sec 
      *  time stamp in seconds.
      */ 
    MINT32              i4TimeStamp_sec;
    /**
      * @var i4TimeStamp_us 
      *  time stamp in microseconds.
      */     
    MINT32              i4TimeStamp_us; //  
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
    /**
     * @brief get the time stamp in ns 
     *
     * @details 
     *
     * @note 
     * 
     * @return 
     * - The ns of the timestamp 
     *
     */ 
    inline MINT64   getTimeStamp_ns() const
    {
        return  i4TimeStamp_sec * 1000000000LL + i4TimeStamp_us * 1000LL;
    }
    /**
     * @brief set the time stamp 
     *
     * @details 
     *
     * @note 
     * 
     * @return 
     * -    MTRUE indicates success; 
     * -    MFALSE indicates failure.     
     *
     */ 
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


////////////////////////////////////////////////////////////////////////////////
};  //namespace NSCamPipe
#endif  //  _MTK_CAMERA_INC_CAMPIPE_BUFFER_H_

