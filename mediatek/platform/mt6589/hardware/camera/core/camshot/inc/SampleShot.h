#ifndef _MTK_CAMERA_CORE_CAMSHOT_INC_SAMPLE_SHOT_H_
#define _MTK_CAMERA_CORE_CAMSHOT_INC_SAMPLE_SHOT_H_
//
//

//

/*******************************************************************************
*
********************************************************************************/
namespace NSCamShot {
////////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
*
********************************************************************************/

class CamShotImp;


/*******************************************************************************
*
********************************************************************************/
class SampleShot : public CamShotImp
{
public:     ////    Constructor/Destructor.
                    SampleShot(
                        EShotMode const eShotMode,
                        char const*const szCamShotName
                    );

public:     ////    Instantiation.
    virtual MBOOL   init();
    virtual MBOOL   uninit();

public:     ////    Operations.
    virtual MBOOL   start(SensorParam const & rSensorParam);
    virtual MBOOL   startAsync(SensorParam const & rSensorParam);    
    virtual MBOOL   startOne(SensorParam const  & rSensorParam); 
    virtual MBOOL   startOne(ImgBufInfo const  & rImgBufInfo); 
    virtual MBOOL   stop();

public:     ////    Settings.
    virtual MBOOL   setShotParam(ShotParam const & rParam); 
    virtual MBOOL   setJpegParam(JpegParam const & rParam); 
    
public:     ////    Info.

public:     ////    buffer setting. 
    virtual MBOOL   registerImgBufInfo(ECamShotImgBufType const eBufType, ImgBufInfo const &rImgBuf); 

public:     ////    Old style commnad.
    virtual MBOOL   sendCommand(MINT32 cmd, MINT32 arg1, MINT32 arg2, MINT32 arg3);


private:
    

};


////////////////////////////////////////////////////////////////////////////////
};  //namespace NSCamShot
#endif  //  _MTK_CAMERA_CORE_CAMSHOT_INC_SAMPLE_SHOT_H_

