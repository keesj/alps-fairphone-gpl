#ifndef _MTK_CAMERA_INC_CAMPIPE_SCENARIO_H_
#define _MTK_CAMERA_INC_CAMPIPE_SCENARIO_H_


/*******************************************************************************
*
********************************************************************************/
namespace NSCamPipe {
////////////////////////////////////////////////////////////////////////////////


/**  
 * @enum ESWScenarioID
 * @brief SW Scenario ID, this will map to sw feature or use case 
 */
enum ESWScenarioID
{
    //
    eSWScenarioID_MTK_PREVIEW,            /*!< MTK preview scenario */ 
    //
    eSWScenarioID_DEFAULT_PREVIEW,        /*!< Default/3rd party APK preview scenario */ 
    //
    eSWScenarioID_VIDEO,                  /*!< Video preview scenario */  
    //
    eSWScenarioID_VSS,                    /*!< Video snapshot scenario */  
    //    
    eSWScenarioID_CAPTURE_NORMAL,         /*!< Normal capture scenario */  
    //
    eSWScenarioID_CAPTURE_ZSD,            /*!< ZSD capture scenario */
    //
    eSWScenarioID_PLAYBACK,               /*!< Image playback scenario  */
    //
};


/**  
 * @enum EScenarioFmt
 * @brief Scenario Format
 */
enum EScenarioFmt
{
    //
    eScenarioFmt_RAW,       /*!< RAW sensor scenario format  */
    //
    eScenarioFmt_YUV,       /*!< YUV sensor scenario format  */
    //
    eScenarioFmt_RGB,       /*!< RGB sensor scenario format  */
    //
    eScenarioFmt_JPG,       /*!< Jpeg sensor scenario format  */
    //
    eScenarioFmt_UNKNOWN    = 0xFFFFFFFF,    /*!< Unknow sensor scenario format  */
};


////////////////////////////////////////////////////////////////////////////////
};  //namespace NSCamPipe
#endif  //  _MTK_CAMERA_INC_CAMPIPE_SCENARIO_H_

