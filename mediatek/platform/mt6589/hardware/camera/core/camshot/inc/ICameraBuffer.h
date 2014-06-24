#ifndef _MTK_CAMERA_CORE_CAMSHOT_INC_ICAMSHOT_BUFFER_MGR_H_
#define _MTK_CAMERA_CORE_CAMSHOT_INC_ICAMSHOT_BUFFER_MGR_H_
//
//


/******************************************************************************
*
*******************************************************************************/


namespace NSCamShot {


/*******************************************************************************
* Interface of CamShot
********************************************************************************/
class ICamShotBufMgr 
{
public:     ////    Attributes.
    virtual MINT32      getLastErrorCode() const = 0;

protected:  ////    Constructor/Destructor.
    virtual         ~ICamShotBufMgr() {}

public:     ////    Instantiation.
    virtual MVOID   destroyInstance() = 0;
    virtual MBOOL   init() = 0;
    virtual MBOOL   uninit() = 0;

public:     ////    Operations. 


public:     ////    Info 

};


}; // namespace NSCamShot
#endif  //_MTK_CAMERA_CORE_CAMSHOT_INC_ICAMSHOT_BUFFER_MGR_H_

