#ifndef _IHDR_H_
#define _IHDR_H_

/*******************************************************************************
*
*******************************************************************************/
class IShot;
class ShotBase;


/*******************************************************************************
*
*******************************************************************************/
class IHdr : public IShot
{
private:
    IHdr(ShotBase*const pShot);
    virtual ~IHdr() {}

public:     ////    Interfaces.
    //
    static IHdr*    createInstance(ESensorType_t const eSensorType, EDeviceId_t const eDeviceId);

    virtual MVOID   destroyInstance();

    virtual MBOOL   init(ShotParam const& rShotParam, Hal3ABase*const pHal3A);

    virtual MBOOL   uninit()
                    { return mrShotBase.uninit(); }

    virtual MBOOL   capture()
                    { return mrShotBase.capture(); }

    virtual MBOOL   setParam(ShotParam const& rShotParam)
                    { return mrShotBase.setParam(rShotParam); }

public:     ////    Attributes.
    //
    virtual char const*     getShotName() const
                    { return mrShotBase.getShotName(); }

    virtual ESensorType_t   getSensorType() const
                    { return mrShotBase.getSensorType(); }

    virtual EDeviceId_t     getDeviceId() const
                    { return mrShotBase.getDeviceId(); }

protected:
    ShotBase&       mrShotBase;
};


#endif  //  _IHDR_H_

