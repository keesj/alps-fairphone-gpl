#ifndef _ISPIO_PIPE_UTILITY_H_
#define _ISPIO_PIPE_UTILITY_H_


/*******************************************************************************
*
********************************************************************************/
namespace NSImageio {
namespace NSIspio   {

/*******************************************************************************
*
********************************************************************************/
#include <cutils/xlog.h>
#define ISPUTIL_MSG(fmt, arg...)    XLOGD("[%s]"          fmt, __FUNCTION__,           ##arg)
#define ISPUTIL_WRN(fmt, arg...)    XLOGW("[%s]WRN(%5d):" fmt, __FUNCTION__, __LINE__, ##arg)
#define ISPUTIL_ERR(fmt, arg...)    XLOGE("[%s]ERR(%5d):" fmt, __FUNCTION__, __LINE__, ##arg)

/*******************************************************************************
*
********************************************************************************/
static MUINT32
queryRawStride(MUINT32 const imgFmt, MUINT32 const& imgWidth)
{
    MUINT32 stride = imgWidth;
       
    //
    if ( imgWidth % 2) {
        ISPUTIL_ERR("width and stride should be even number");
    }
    //
    switch (imgFmt) {
        case eImgFmt_BAYER8:          //= 0x0001,   //Bayer format, 8-bit
            stride = imgWidth;
            break;
            
        case eImgFmt_BAYER10:         //= 0x0002,   //Bayer format, 10-bit
            if ( imgWidth % 8 ) {
                stride = imgWidth + 8 - (imgWidth % 8);
            }            
            if ( imgWidth > stride ) {
                ISPUTIL_ERR(" RAW10 STRIDE SHOULD BE MULTIPLE OF 8(%d)->(%d)", imgWidth, stride);
            }
            break;
            
        case eImgFmt_BAYER12:         //= 0x0004,   //Bayer format, 12-bit
            if ( stride % 4 ) {
                stride = stride + 4 - (stride % 4);
            }            
            if ( imgWidth > stride ) {
                ISPUTIL_ERR(" RAW12 STRIDE SHOULD BE MULTIPLE OF 4(%d)->(%d)", imgWidth, stride);
            }
            break;
            
        default:
            ISPUTIL_WRN("NOT SUPPORT imgFmt(%d)",imgFmt);
            break;
    }
    
    ISPUTIL_MSG("imgFmt(%d), imgWidth(%d), stride(%d)", imgFmt, imgWidth, stride);
    return stride;
}


/*******************************************************************************
*
********************************************************************************/
static MUINT32
queryRawBitPerPixel(MUINT32 const imgFmt)
{      
    MUINT32 pixel_bit = 0;    
    
    switch (imgFmt) {
        case eImgFmt_BAYER8:          //= 0x0001,   //Bayer format, 8-bit
            pixel_bit = 8;
            break;
            
        case eImgFmt_BAYER10:         //= 0x0002,   //Bayer format, 10-bit
            pixel_bit = 10;
            break;
            
        case eImgFmt_BAYER12:         //= 0x0004,   //Bayer format, 12-bit
            pixel_bit = 12;
            break;
            
        default:
            ISPUTIL_WRN("NOT SUPPORT imgFmt(%d)",imgFmt);
            break;
    }
    //
    return pixel_bit;
}


};  //namespace NSIspio
};  //namespace NSImageio

#endif  //  _ISPIO_PIPE_UTILITY_H_

