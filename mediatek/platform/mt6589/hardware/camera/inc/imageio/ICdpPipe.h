#ifndef _ISPIO_I_CDP_PIPE_H_
#define _ISPIO_I_CDP_PIPE_H_


/*******************************************************************************
*
********************************************************************************/
namespace NSImageio {
namespace NSIspio   {
////////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
* Pipe Interface
********************************************************************************/
class ICdpPipe : public IPipe
{
public:
    static EPipeID const ePipeID = ePipeID_1x3_Mem_Cdp_Mem;

public:     ////    Instantiation.
    static ICdpPipe* createInstance(EScenarioID const eScenarioID, EScenarioFmt const eScenarioFmt);

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Command Class.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:
    //
    //  Interface of Command Class.
    class ICmd : public IPipeCommand
    {
    public:     ////    Interfaces.
        ICmd(IPipe*const pIPipe);
        virtual MBOOL   verifySelf();
        //
    protected:
        MVOID*const     mpIPipe;
    };

    //
    //  Command: Set 2 parameters.
    class Cmd_Set2Params : public ICmd
    {
    public:     ////    Interfaces.
        Cmd_Set2Params(IPipe*const pIPipe, MUINT32 const u4Param1, MUINT32 const u4Param2);
        virtual MBOOL   execute();
        //
    protected:  ////    Data Members.
        MUINT32         mu4Param1;
        MUINT32         mu4Param2;
    };

    //
    //  Command: Get 1 parameter based on 1 input parameter.
    class Cmd_Get1ParamBasedOn1Input : public ICmd
    {
    public:     ////    Interfaces.
        Cmd_Get1ParamBasedOn1Input(IPipe*const pIPipe, MUINT32 const u4InParam, MUINT32*const pu4OutParam);
        virtual MBOOL   execute();
        //
    protected:  ////    Data Members.
        MUINT32         mu4InParam;
        MUINT32*        mpu4OutParam;
    };

    virtual MBOOL   syncJpegPass2C() = 0;
    virtual MBOOL   startFmt() = 0;
};


////////////////////////////////////////////////////////////////////////////////
};  //namespace NSIspio
};  //namespace NSImageio
#endif  //  _ISPIO_I_CDP_PIPE_H_

