#ifndef _MTK_CAMERA_INC_CAMPIPE_INENTITY_H_
#define _MTK_CAMERA_INC_CAMPIPE_INENTITY_H_


/*******************************************************************************
*
********************************************************************************/
namespace NSCamPipe {
////////////////////////////////////////////////////////////////////////////////

/**  
 * @enum EPipeID
 * @brief Pipe ID
 * @details 
 * format: ePipeID_<InPortNum>x_<OutPortNum>_<InType>_<OutType>
 */
enum EPipeID
{
    //
    ePipeID_1x2_Sensor_Tg_Isp_Mem,       /*!< (In:1/Out:2) SENSOR -> TG -> ISP -> MEM */  
    //
    ePipeID_1x2_Mem_Isp_Cdp_Mem,        /*!< (In:1/Out:2) MEM -> ISP -> CDP -> MEM */  
    //
    ePipeID_1x2_Mem_Cdp_Mem,            /*!< (In:1/Out:2) MEM -> CDP -> MEM */ 
    //
    ePipeID_Total_Count,                 /*!< total count of pipes */
    //
    ePipeID_0x0_NONE                    /*!< test pipe  */ 
};


////////////////////////////////////////////////////////////////////////////////
};  //namespace NSCamPipe
#endif  //  _MTK_CAMERA_INC_CAMPIPE_INENTITY_H_

