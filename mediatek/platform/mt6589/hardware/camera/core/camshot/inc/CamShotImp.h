#ifndef _MTK_CAMERA_CORE_CAMSHOT_INC_CAMSHOT_IMP_H_
#define _MTK_CAMERA_CORE_CAMSHOT_INC_CAMSHOT_IMP_H_

//
#include <vector>
//
using namespace std;

//
#include <cutils/atomic.h>
//

//

using namespace NSCamPipe; 

/*******************************************************************************
*
********************************************************************************/
namespace NSCamShot {
////////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
*
********************************************************************************/
class CamShotImp
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Attributes.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
protected:  ////    Data Members.
    EShotMode           meShotMode; 
    char const*const    mszCamShotName;
    MINT32              mi4ErrorCode;

public:     ////    Operations.
    virtual EShotMode     getShotMode() const          {return meShotMode; }
    virtual char const* getCamShotName() const         { return mszCamShotName; }
    virtual MINT32      getLastErrorCode() const    { return mi4ErrorCode; }

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Instantiation.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:     ////    Constructor/Destructor.
                    CamShotImp(
                        EShotMode const eShotMode,
                        char const*const szCamShotName
                    );
    virtual         ~CamShotImp()  {}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Callbacks.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
protected:  ////    Data Members.
    //
    MVOID*          mpCbUser;           //  Callback user.
    //
    //  notify callback
    volatile MINT32         mi4NotifyMsgSet;//  bitset of notify message types.
    CamShotNotifyCallback_t    mNotifyCb;      //  notify callback function pointer.
    //
    //  data callback
    volatile MINT32         mi4DataMsgSet;  //  bitset of data message types.
    CamShotDataCallback_t      mDataCb;        //  data callback function pointer.

protected:  ////    Helpers.
    virtual MBOOL   onNotifyCallback(CamShotNotifyInfo const& msg) const;
    virtual MBOOL   onDataCallback(CamShotDataInfo const& msg) const;

public:     ////    Operations.
    //
    virtual MVOID   setCallbacks(CamShotNotifyCallback_t notify_cb, CamShotDataCallback_t data_cb, MVOID* user);
    //
    //  notify callback
    inline MBOOL    isNotifyMsgEnabled(MINT32 const i4MsgTypes) const   { return (i4MsgTypes & mi4NotifyMsgSet); }
    inline MVOID    enableNotifyMsg(MINT32 const i4MsgTypes)            { ::android_atomic_or(i4MsgTypes, &mi4NotifyMsgSet); }
    inline MVOID    disableNotifyMsg(MINT32 const i4MsgTypes)           { ::android_atomic_and(~i4MsgTypes, &mi4NotifyMsgSet); }
    //
    //  data callback
    inline MBOOL    isDataMsgEnabled(MINT32 const i4MsgTypes) const     { return (i4MsgTypes & mi4DataMsgSet); }
    inline MVOID    enableDataMsg(MINT32 const i4MsgTypes)              { ::android_atomic_or(i4MsgTypes, &mi4DataMsgSet); }
    inline MVOID    disableDataMsg(MINT32 const i4MsgTypes)             { ::android_atomic_and(~i4MsgTypes, &mi4DataMsgSet); }

protected:  ////    Helper function 
    MVOID      dumpPipeProperty(vector<PortProperty> const &vInPorts, vector<PortProperty> const &vOutPorts); 
    MVOID      dumpSensorParam(SensorParam const & rParam);     
    MVOID      dumpShotParam(ShotParam const & rParam); 
    MVOID      dumpJpegParam(JpegParam const & rParam); 
    //

protected:
    MBOOL      handleNotifyCallback(MINT32 const i4Msg, MUINT32 const ext1, MUINT32 const ext2);  
    MBOOL      handleDataCallback(MINT32 const i4Msg, MUINT32 const ext1, MUINT32 const ext2, MUINT8* puData, MUINT32 const u4Size); 
    
protected:

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Scenario.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
protected:  ////    Data Members.
    //

public:     ////    Operations.




};


////////////////////////////////////////////////////////////////////////////////
};  //namespace NSCamShot
#endif  //  _MTK_CAMERA_CORE_CAMSHOT_INC_CAMSHOT_IMP_H_

