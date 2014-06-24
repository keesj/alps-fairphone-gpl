#ifndef _ISPIO_PIPE_IDENTITY_H_
#define _ISPIO_PIPE_IDENTITY_H_


/*******************************************************************************
*
********************************************************************************/
namespace NSImageio {
namespace NSIspio   {
////////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
* Pipe ID
********************************************************************************/
enum EPipeID
{
    //
    ePipeID_1x1_Sensor_Tg_Mem,          //  (In:1/Out:1) SENSOR -> TG -> MEM
    //
    ePipeID_1x2_Sensor_Tg_Mem,          //  (In:1/Out:2) SENSOR -> TG -> MEM
    //
    ePipeID_2x2_Sensor_Tg_Mem,          //  (In:2/Out:2) SENSOR -> TG -> MEM
                                        //                      -> ISP-> MEM
    //
    ePipeID_1x1_Sensor_Tg_Isp_Mem,      //  (In:1/Out:1) SENSOR -> TG -> ISP -> MEM
    //
    ePipeID_1x3_Mem_Cdp_Mem,            //  (In:1/Out:3) MEM -> TG -> ISP -> MEM
    //
    ePipeID_1x3_Gdma_Cdp_Mem,           //  (In:1/Out:3) GDMA -> CDP -> MEM
    //
    ePipeID_1x3_Mem_Isp_Cdp_Mem,        //  (In:1/Out:3) MEM -> ISP -> CDP -> MEM
    //
    ePipeID_1x3_Gdma_Isp_Cdp_Mem,       //  (In:1/Out:3) GDMA -> ISP -> CDP -> MEM
    //
    ePipeID_1x1_Mem_Vec_Mem,            //  (In:1/Out:1) MEM -> Vec -> MEM
    //
    ePipeID_1x1_Mem_Lsc_PreGain_Mem,    //  (In:1/Out:1) MEM -> Lsc -> PreGain -> MEM (img2o)
    //
    ePipeID_Total_Count                 //  total count of pipes.
};


////////////////////////////////////////////////////////////////////////////////
};  //namespace NSIspio
};  //namespace NSImageio
#endif  //  _ISPIO_PIPE_IDENTITY_H_

