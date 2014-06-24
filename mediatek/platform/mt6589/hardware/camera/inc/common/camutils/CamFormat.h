#ifndef _MTK_CAMERA_INC_COMMON_CAMUTILS_CAMFORMAT_H_
#define _MTK_CAMERA_INC_COMMON_CAMUTILS_CAMFORMAT_H_
//


namespace android {
namespace MtkCamUtils {
namespace FmtUtils {


/*****************************************************************************
 * @brief Query the imageio format.
 *
 * @details Given a CameraParameters::PIXEL_FORMAT_xxx, return its corresponding
 * imageio format.
 *
 * @note
 *
 * @param[in] szPixelFormat: A null-terminated string for pixel format (i.e. 
 * CameraParameters::PIXEL_FORMAT_xxx)
 *
 * @return its corresponding imageio format (i.e. EImageFormat)
 *
 ******************************************************************************/
uint_t
queryImageioFormat(
    char const* szPixelFormat
);


/*****************************************************************************
 * @brief Query the bits per pixel.
 *
 * @details Given a CameraParameters::PIXEL_FORMAT_xxx, return its corresponding
 * bits per pixel.
 *
 * @note
 *
 * @param[in] szPixelFormat: A null-terminated string for pixel format (i.e. 
 * CameraParameters::PIXEL_FORMAT_xxx)
 *
 * @return its corresponding bits per pixel.
 *
 ******************************************************************************/
int
queryBitsPerPixel(
    char const* szPixelFormat
);


/*****************************************************************************
 * @brief Query the plane count.
 *
 * @details Given a CameraParameters::PIXEL_FORMAT_xxx, return its corresponding
 * plane count.
 *
 * @note
 *
 * @param[in] szPixelFormat: A null-terminated string for pixel format (i.e. 
 * CameraParameters::PIXEL_FORMAT_xxx)
 *
 * @return its corresponding plane count.
 *
 ******************************************************************************/
size_t
queryPlaneCount(
    char const* szPixelFormat
);


/*****************************************************************************
 * @brief Query a specific plane's width stride.
 *
 * @details Given a CameraParameters::PIXEL_FORMAT_xxx, image width and plane's 
 * index, return its corresponding plane's stride.
 *
 * @note
 *
 * @param[in] szPixelFormat: A null-terminated string for pixel format (i.e. 
 * CameraParameters::PIXEL_FORMAT_xxx)
 *
 * @param[in] imgWidth: image width, in pixel.
 *
 * @param[in] planeIndex: plane's index; 0, 1, and 2 refer to 1st-, 2nd-, and 
 * 3rd plane, respectively.
 *
 * @return its corresponding plane's stride, in pixel
 *
 ******************************************************************************/
size_t
queryImgWidthStride(
    char const* szPixelFormat, 
    size_t imgWidth, 
    size_t planeIndex
);


/*****************************************************************************
 * @brief Query a specific plane's height stride.
 *
 * @details Given a CameraParameters::PIXEL_FORMAT_xxx, image height and plane's 
 * index, return its corresponding plane's stride.
 *
 * @note
 *
 * @param[in] szPixelFormat: A null-terminated string for pixel format (i.e. 
 * CameraParameters::PIXEL_FORMAT_xxx)
 *
 * @param[in] imgHeight: image height, in pixel.
 *
 * @param[in] planeIndex: plane's index; 0, 1, and 2 refer to 1st-, 2nd-, and 
 * 3rd plane, respectively.
 *
 * @return its corresponding plane's stride, in pixel
 *
 ******************************************************************************/
size_t
queryImgHeightStride(
    char const* szPixelFormat, 
    size_t imgHeight, 
    size_t planeIndex
);


/*****************************************************************************
 * @brief Query a striding buffer size, in bytes.
 *
 * @details Given a CameraParameters::PIXEL_FORMAT_xxx, image width/height, 
 * return its corresponding striding buffer size, in bytes.
 *
 * @note
 *
 * @param[in] szPixelFormat: A null-terminated string for pixel format (i.e. 
 * CameraParameters::PIXEL_FORMAT_xxx)
 *
 * @param[in] imgWidth: image width, in pixel.
 *
 * @param[in] imgHeight: image height, in pixel.
 *
 * @return its corresponding striding buffer size, in bytes
 *
 ******************************************************************************/
size_t
queryImgBufferSize(
    char const* szPixelFormat, 
    size_t imgWidth, 
    size_t imgHeight
);


};  // namespace FmtUtils
};  // namespace MtkCamUtils
};  // namespace android
#endif  //_MTK_CAMERA_INC_COMMON_CAMUTILS_CAMFORMAT_H_

