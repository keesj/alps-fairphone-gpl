#ifndef _ISPIO_PIPE_SCENARIO_H_
#define _ISPIO_PIPE_SCENARIO_H_


/*******************************************************************************
*
********************************************************************************/
namespace NSImageio {
namespace NSIspio   {
////////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
* Scenario ID
********************************************************************************/
enum EScenarioID
{
    //
    eScenarioID_IC,         // 0    //  Image Capture
    //
    eScenarioID_VR,                 //  Video Recording/Preview
    //
    eScenarioID_ZSD,                //  Zero Shutter Delay
    //
    eScenarioID_IP,                 //  Image Playback
    //
    eScenarioID_VEC,                //  Vector Generation
    //
    eScenarioID_RESERVED,   // 5    //  Reserved
    //
    eScenarioID_N3D_IC,             //  Native Stereo Camera IC
    //
    eScenarioID_N3D_VR,             //  Native Stereo Camera VR
    //
    eScenarioID_VSS,                //  video snap shot, derived from N3D_IC
    //
    eScenarioID_ZSD_CDP_CC,         //  ZSD CDP concurrency
    //
    eScenarioID_VSS_CDP_CC, // 10   //  VSS CDP concurrency
    //
    eScenarioID_GDMA,               //  VSS CDP concurrency
    //
    eScenarioID_CONFIG_FMT,         //  FMT
};


/*******************************************************************************
* Scenario Format
********************************************************************************/
enum EScenarioFmt
{
    //
    eScenarioFmt_RAW,       //
    //
    eScenarioFmt_YUV,       //
    //
    eScenarioFmt_RGB,       //
    //
    eScenarioFmt_JPG,       //
    //
    eScenarioFmt_MFB,       //
    //
    eScenarioFmt_RGB_LOAD,  //
    //
    eScenarioFmt_UNKNOWN    = 0xFFFFFFFF,   //
};


////////////////////////////////////////////////////////////////////////////////
};  //namespace NSIspio
};  //namespace NSImageio
#endif  //  _ISPIO_PIPE_SCENARIO_H_

