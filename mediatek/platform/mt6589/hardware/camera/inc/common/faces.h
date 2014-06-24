#ifndef _MHAL_MTK_FACES_H_
#define _MHAL_MTK_FACES_H_


/******************************************************************************
 *  The information of a face from camera face detection.
 ******************************************************************************/
 struct MtkCameraFace {
    /**
     * Bounds of the face [left, top, right, bottom]. (-1000, -1000) represents
     * the top-left of the camera field of view, and (1000, 1000) represents the
     * bottom-right of the field of view. The width and height cannot be 0 or
     * negative. This is supported by both hardware and software face detection.
     *
     * The direction is relative to the sensor orientation, that is, what the
     * sensor sees. The direction is not affected by the rotation or mirroring
     * of CAMERA_CMD_SET_DISPLAY_ORIENTATION.
     */
    int32_t rect[4];

    /**
     * The confidence level of the face. The range is 1 to 100. 100 is the
     * highest confidence. This is supported by both hardware and software
     * face detection.
     */
    int32_t score;

    /**
     * An unique id per face while the face is visible to the tracker. If
     * the face leaves the field-of-view and comes back, it will get a new
     * id. If the value is 0, id is not supported.
     */
    int32_t id;

    /**
     * The coordinates of the center of the left eye. The range is -1000 to
     * 1000. -2000, -2000 if this is not supported.
     */
    int32_t left_eye[2];

    /**
     * The coordinates of the center of the right eye. The range is -1000 to
     * 1000. -2000, -2000 if this is not supported.
     */
    int32_t right_eye[2];

    /**
     * The coordinates of the center of the mouth. The range is -1000 to 1000.
     * -2000, -2000 if this is not supported.
     */
    int32_t mouth[2];

};


/******************************************************************************
 *   FD Pose Information: ROP & RIP
 *****************************************************************************/
struct MtkFaceInfo {

    int32_t rop_dir;
    int32_t rip_dir;
};


/******************************************************************************
 *  The metadata of the frame data.
 *****************************************************************************/
struct MtkCameraFaceMetadata {
    /**
     * The number of detected faces in the frame.
     */
    int32_t number_of_faces;

    /**
     * An array of the detected faces. The length is number_of_faces.
     */
    MtkCameraFace *faces;
    MtkFaceInfo   *posInfo;
};


#endif

