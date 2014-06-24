//! \file  AcdkCallback.h

#ifndef _ACDKCALLBACK_H_
#define _ACDKCALLBACK_H_


//! Prototype of ACDK Callback Function
typedef void (*pfAcdkCallback)(void *);

/**  
*@enum ACDK_CB_ENUM
*@brief Type of ACDK Callback
*/
enum ACDK_CB_ENUM
{
    ACDK_CB_ERR = 0,    //! error callback
    ACDK_CB_PREVIEW,    //! preview callback
    ACDK_CB_RAW,        //! RAW capture callback
    ACDK_CB_JPEG,       //! JPEG capture callback
    ACDK_CB_QV,         //! QV callback
    ACDK_CB_AF          //! AF callback
};

/**  
*@struct acdkCallbackParam_s
*@brief  ACDK callback parameter used by AcdkMain
*/
typedef struct acdkCallbackParam_s {
    MUINT32 type;
    MUINT32 addr1;
    MUINT32 addr2;
    MUINT32 imgSize;
    MUINT32 thubSize;
} acdkCallbackParam_t;


/**  
*@struct acdkCBInfo
*@brief  ACDK callback parameter used by acdkObserver
*/
struct acdkCBInfo
{
    void    *mCookie;
    MUINT32 mType;
    MUINT32 mAddr1;
    MUINT32 mAddr2;
    MUINT32 mDataSize1;
    MUINT32 mDataSize2;
    
    acdkCBInfo(
        void    *cookie, 
        MUINT32 aType, 
        MUINT32 aAddr1 = 0, 
        MUINT32 aAddr2 = 0,
        MUINT32 aDataSize1 = 0,
        MUINT32 aDataSize2 = 0)
        : mCookie(cookie)
        , mType(aType)
        , mAddr1(aAddr1)
        , mAddr2(aAddr2)
        , mDataSize1(aDataSize1)
        , mDataSize2(aDataSize2)
    {}
};


/**  
*@struct acdkObserver
*@brief ACDK will use acdkObserver to set and call callback function
*/
struct acdkObserver
{
    typedef pfAcdkCallback  CallbackFunc_t;
    
    CallbackFunc_t  mpfCallback;
    void            *mCookie;
   
    acdkObserver(
        CallbackFunc_t  pfCallback = 0, 
        void            *cookie = 0
    )
        : mpfCallback(pfCallback)
        , mCookie(cookie)
    {}
    
    inline  bool operator!() const
    {
        return  (0 == mpfCallback);
    }
    
    inline  void notify(MUINT32 u4Type, MUINT32 u4Addr1 = 0, MUINT32 u4Addr2 = 0, MUINT32 u4DataSize1 = 0,MUINT32 u4DataSize2 = 0)
    {
        if( mpfCallback )
        {
            acdkCBInfo info(mCookie, u4Type, u4Addr1, u4Addr2, u4DataSize1, u4DataSize2);
            mpfCallback(&info);
        }
    }
};

#endif  //  _ACDKCALLBACK_H_

