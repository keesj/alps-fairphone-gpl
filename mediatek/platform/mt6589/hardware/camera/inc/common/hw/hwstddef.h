#ifndef _MTK_CAMERA_INC_COMMON_HW_HWSTDDEF_H_
#define _MTK_CAMERA_INC_COMMON_HW_HWSTDDEF_H_

#include <common/CamDefs.h>

/*******************************************************************************
*
*******************************************************************************/
namespace NSCamHW {
////////////////////////////////////////////////////////////////////////////////

/**  
 * @struct ImgInfo
 * @brief This structure is Image Info. 
 *
 */
struct ImgInfo
{
public:     //// fields.
    /**
      * @var eImgFmt 
      * Image Pixel Format
      */
    EImageFormat   eImgFmt;      
    /**
      * @var u4ImgWidth 
      * Image Width
      */    
    MUINT32        u4ImgWidth;     //  
    /**
      * @var u4ImgHeight
      * Image Height
      */    
    MUINT32        u4ImgHeight;    //  Image Height
    //
public:     //// constructors.
    ImgInfo(
        EImageFormat const _eImgFmt = eImgFmt_UNKNOWN, 
        MUINT32      const _u4ImgWidth = 0, 
        MUINT32      const _u4ImgHeight = 0
    )
        : eImgFmt(_eImgFmt)
        , u4ImgWidth(_u4ImgWidth)
        , u4ImgHeight(_u4ImgHeight)
    {}
};

/**  
 * @struct Rect 
 * @brief This structure is for rectangle info 
 *
 */
struct Rect{
public:
    /**
      * @var x 
      * x offset 
      */	
    MUINT32 x;
    /**
      * @var y 
      * y offset 
      */    
    MUINT32 y;
    /**
      * @var w
      * width 
      */    
    MUINT32 w;
    /**
      * @var h
      * height
      */    
    MUINT32 h;
     
public:     //// constructors. 
    // 
    Rect(MUINT32 const _x = 0 , 
         MUINT32 const _y = 0 , 
         MUINT32 const _w = 0, 
         MUINT32 const _h = 0)
        : x(_x)
        , y(_y)
        , w(_w)
        , h(_h)
    {
    }

};

/**  
 * @struct BufInfo 
 * @brief This structure is for buffer Info.
 *
 */
struct BufInfo
{
public:     //// fields.
    /**
      * @var u4BufSize
      * Per buffer size
      */
    MUINT32        u4BufSize;  
    /**
      * @var u4BufVA 
      * Virtual Address
      */    
    MUINT32        u4BufVA;    
    /**
      * @var u4BufPA 
      * Physical Address
      */    
    MUINT32        u4BufPA; 
    /**
      * @var i4MemID
      * Memory device ID 
      */    
    MINT32         i4MemID;       //  
    //
    MINT32         i4BufSecu;
    MINT32         i4BufCohe;
    //
public:     //// constructors.
    BufInfo(
        MUINT32 const _u4BufSize = 0, 
        MUINT32 const _u4BufVA = 0, 
        MUINT32 const _u4BufPA = 0,
        MINT32  const _i4MemID = -1,
        MINT32  const _i4BufSecu = 0,
        MINT32  const _i4BufCohe = 0
        //EMemoryType const _eMemType = eMemoryType_STD_M4U
    )
        : u4BufSize(_u4BufSize)
        , u4BufVA(_u4BufVA)
        , u4BufPA(_u4BufPA)
        , i4MemID(_i4MemID)
        , i4BufSecu(_i4BufSecu)
        , i4BufCohe(_i4BufCohe)
        //, eMemType(_eMemType)
    {
    }
    //
};

/**  
 * @struct ImgBufInfo 
 * @brief This structure is for image buffer info.
 *
 */
struct ImgBufInfo: public ImgInfo, public BufInfo
{
public:    //// constructors. 
    /**
      * @var u4Stride
      * The stride of the width for 3 planes 
      */   
    MUINT32 u4Stride[3]; 
    //
    ImgBufInfo( 
    )
        : ImgInfo()
        , BufInfo()
    {    
        u4Stride[0] = u4Stride[1] = u4Stride[2] = 0; 
    }
    //
    ImgBufInfo( 
        ImgInfo const &_ImgInfo, 
        BufInfo const &_BufInfo, 
        MUINT32 const _u4Stride[3]
    )
        : ImgInfo(_ImgInfo)
        , BufInfo(_BufInfo)
    {    
        u4Stride[0] = _u4Stride[0];  
        u4Stride[1] = _u4Stride[1];         
        u4Stride[2] = _u4Stride[2];  
    }
}; 


////////////////////////////////////////////////////////////////////////////////

};  //namespace NSCamHW
#endif // _MTK_HAL_INC_COMMON_HW_HWSTDDEF_H_

