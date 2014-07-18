#include <utils/Log.h>
#include <fcntl.h>
#include <math.h>

#include "camera_custom_nvram.h"
#include "camera_custom_sensor.h"
#include "image_sensor.h"
#include "kd_imgsensor_define.h"
#include "camera_AE_PLineTable_imx179raw.h"
#include "camera_info_imx179raw.h"
#include "camera_custom_AEPlinetable.h"
const NVRAM_CAMERA_ISP_PARAM_STRUCT CAMERA_ISP_DEFAULT_VALUE =
{{
    //Version
    Version: NVRAM_CAMERA_PARA_FILE_VERSION,
    //SensorId
    SensorId: SENSOR_ID,
    ISPComm:{
        {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        }
    },
    ISPPca:{
        #include INCLUDE_FILENAME_ISP_PCA_PARAM
    },
    ISPRegs:{
        #include INCLUDE_FILENAME_ISP_REGS_PARAM
        },
    ISPMfbMixer:{{
        {//00: MFB mixer for ISO 100
            0x00000000, 0x00000000
        },
        {//01: MFB mixer for ISO 200
            0x00000000, 0x00000000
        },
        {//02: MFB mixer for ISO 400
            0x00000000, 0x00000000
        },
        {//03: MFB mixer for ISO 800
            0x00000000, 0x00000000
        },
        {//04: MFB mixer for ISO 1600
            0x00000000, 0x00000000
        },
        {//05: MFB mixer for ISO 2400
            0x00000000, 0x00000000
        },
        {//06: MFB mixer for ISO 3200
            0x00000000, 0x00000000
        }
    }},
    ISPCcmPoly22:{
        82775,    // i4R_AVG
        19606,    // i4R_STD
        109450,    // i4B_AVG
        29497,    // i4B_STD
        {  // i4P00[9]
            4317500, -1727500, -27500, -740000, 3547500, -247500, 162500, -1697500, 4097500
        },
        {  // i4P10[9]
            883644, -977645, 97218, 45967, -46733, 766, 43352, -208509, 168374
        },
        {  // i4P01[9]
            567456, -634880, 66047, -43386, -216885, 260271, 73360, -691599, 616863
        },
        {  // i4P20[9]
            0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {  // i4P11[9]
            0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {  // i4P02[9]
            0, 0, 0, 0, 0, 0, 0, 0, 0
        }
    }
}};

const NVRAM_CAMERA_3A_STRUCT CAMERA_3A_NVRAM_DEFAULT_VALUE =
{
    NVRAM_CAMERA_3A_FILE_VERSION, // u4Version
    SENSOR_ID, // SensorId

    // AE NVRAM
    {
        // rDevicesInfo
        {
            1024,    // u4MinGain, 1024 base = 1x1136
            10928,    // u4MaxGain, 16x
            100,    // u4MiniISOGain, ISOxx  
            128,    // u4GainStepUnit, 1x/8 
            21,    // u4PreExpUnit 
            30,    // u4PreMaxFrameRate
            17,    // u4VideoExpUnit  
            31,    // u4VideoMaxFrameRate 
            1024,    // u4Video2PreRatio, 1024 base = 1x 
            17,    // u4CapExpUnit 
            25,    // u4CapMaxFrameRate
            1024,    // u4Cap2PreRatio, 1024 base = 1x
            28,    // u4LensFno, Fno = 2.8
            350    // u4FocusLength_100x
        },
        // rHistConfig
        {
            2,    // u4HistHighThres
            40,    // u4HistLowThres
            2,    // u4MostBrightRatio
            1,    // u4MostDarkRatio
            160,    // u4CentralHighBound
            20,    // u4CentralLowBound
            {240, 230, 220, 210, 200},    // u4OverExpThres[AE_CCT_STRENGTH_NUM] 
            {86, 108, 128, 148, 170},    // u4HistStretchThres[AE_CCT_STRENGTH_NUM] 
            {18, 22, 26, 30, 34}    // u4BlackLightThres[AE_CCT_STRENGTH_NUM] 
        },
        // rCCTConfig
        {
            TRUE,    // bEnableBlackLight
            TRUE,    // bEnableHistStretch
            FALSE,    // bEnableAntiOverExposure
            TRUE,    // bEnableTimeLPF
            FALSE,    // bEnableCaptureThres
            FALSE,    // bEnableVideoThres
            FALSE,    // bEnableStrobeThres
            49,    // u4AETarget
            49,    // u4StrobeAETarget0
            20,    // u4InitIndex
            4,    // u4BackLightWeight
            32,    // u4HistStretchWeight
            4,    // u4AntiOverExpWeight
            2,    // u4BlackLightStrengthIndex
            2,    // u4HistStretchStrengthIndex
            2,    // u4AntiOverExpStrengthIndex
            2,    // u4TimeLPFStrengthIndex
            {1, 3, 5, 7, 8},    // u4LPFConvergeTable[AE_CCT_STRENGTH_NUM] 
            90,    // u4InDoorEV = 9.0, 10 base 
            6,    // i4BVOffset delta BV = value/10 
            64,    // u4PreviewFlareOffset
            64,    // u4CaptureFlareOffset
            5,    // u4CaptureFlareThres
            64,    // u4VideoFlareOffset
            5,    // u4VideoFlareThres
            2,    // u4StrobeFlareOffset
            2,    // u4StrobeFlareThres
            8,    // u4PrvMaxFlareThres
            0,    // u4PrvMinFlareThres
            8,    // u4VideoMaxFlareThres
            0,    // u4VideoMinFlareThres
            18,    // u4FlatnessThres    // 10 base for flatness condition.
            75    // u4FlatnessStrength
        }
    },
    // AWB NVRAM
    {
        // AWB calibration data
        {
            // rUnitGain (unit gain: 1.0 = 512)
            {
                0,    // i4R
                0,    // i4G
                0    // i4B
            },
            // rGoldenGain (golden sample gain: 1.0 = 512)
            {
                0,    // i4R
                0,    // i4G
                0    // i4B
            },
            // rTuningUnitGain (Tuning sample unit gain: 1.0 = 512)
            {
                0,    // i4R
                0,    // i4G
                0    // i4B
            },
            // rD65Gain (D65 WB gain: 1.0 = 512)
            {
                1056,    // i4R
                512,    // i4G
                715    // i4B
            }
        },
        // Original XY coordinate of AWB light source
        {
           // Strobe
            {
                144,    // i4X
                -391    // i4Y
            },
            // Horizon
            {
                -348,    // i4X
                -451    // i4Y
            },
            // A
            {
                -255,    // i4X
                -463    // i4Y
            },
            // TL84
            {
                -150,    // i4X
                -386    // i4Y
            },
            // CWF
            {
                -111,    // i4X
                -468    // i4Y
            },
            // DNP
            {
                -4,    // i4X
                -443    // i4Y
            },
            // D65
            {
                144,    // i4X
                -391    // i4Y
            },
            // DF
            {
                0,    // i4X
                0    // i4Y
            }
        },
        // Rotated XY coordinate of AWB light source
        {
            // Strobe
            {
                110,    // i4X
                -402    // i4Y
            },
            // Horizon
            {
                -385,    // i4X
                -419    // i4Y
            },
            // A
            {
                -294,    // i4X
                -439    // i4Y
            },
            // TL84
            {
                -183,    // i4X
                -372    // i4Y
            },
            // CWF
            {
                -151,    // i4X
                -457    // i4Y
            },
            // DNP
            {
                -42,    // i4X
                -441    // i4Y
            },
            // D65
            {
                110,    // i4X
                -402    // i4Y
            },
            // DF
            {
                0,    // i4X
                0    // i4Y
            }
        },
        // AWB gain of AWB light source
        {
            // Strobe 
            {
                1056,    // i4R
                512,    // i4G
                715    // i4B
            },
            // Horizon 
            {
                589,    // i4R
                512,    // i4G
                1510    // i4B
            },
            // A 
            {
                678,    // i4R
                512,    // i4G
                1352    // i4B
            },
            // TL84 
            {
                705,    // i4R
                512,    // i4G
                1058    // i4B
            },
            // CWF 
            {
                830,    // i4R
                512,    // i4G
                1122    // i4B
            },
            // DNP 
            {
                928,    // i4R
                512,    // i4G
                938    // i4B
            },
            // D65 
            {
                1056,    // i4R
                512,    // i4G
                715    // i4B
            },
            // DF 
            {
                512,    // i4R
                512,    // i4G
                512    // i4B
            }
        },
        // Rotation matrix parameter
        {
            5,    // i4RotationAngle
            255,    // i4Cos
            22    // i4Sin
        },
        // Daylight locus parameter
        {
            -160,    // i4SlopeNumerator
            128    // i4SlopeDenominator
        },
        // AWB light area
        {
            // Strobe:FIXME
            {
            0,    // i4RightBound
            0,    // i4LeftBound
            0,    // i4UpperBound
            0    // i4LowerBound
            },
            // Tungsten
            {
            -233,    // i4RightBound
            -883,    // i4LeftBound
            -379,    // i4UpperBound
            -479    // i4LowerBound
            },
            // Warm fluorescent
            {
            -233,    // i4RightBound
            -883,    // i4LeftBound
            -479,    // i4UpperBound
            -599    // i4LowerBound
            },
            // Fluorescent
            {
            -92,    // i4RightBound
            -233,    // i4LeftBound
            -307,    // i4UpperBound
            -414    // i4LowerBound
            },
            // CWF
            {
            -92,    // i4RightBound
            -233,    // i4LeftBound
            -414,    // i4UpperBound
            -540    // i4LowerBound
            },
            // Daylight
            {
            135,    // i4RightBound
            -92,    // i4LeftBound
            -322,    // i4UpperBound
            -482    // i4LowerBound
            },
            // Shade
            {
            495,    // i4RightBound
            135,    // i4LeftBound
            -322,    // i4UpperBound
            -482    // i4LowerBound
            },
            // Daylight Fluorescent
            {
            135,    // i4RightBound
            -92,    // i4LeftBound
            -482,    // i4UpperBound
            -600    // i4LowerBound
            }
        },
        // PWB light area
        {
            // Reference area
            {
            495,    // i4RightBound
            -883,    // i4LeftBound
            0,    // i4UpperBound
            -600    // i4LowerBound
            },
            // Daylight
            {
            160,    // i4RightBound
            -92,    // i4LeftBound
            -322,    // i4UpperBound
            -482    // i4LowerBound
            },
            // Cloudy daylight
            {
            260,    // i4RightBound
            85,    // i4LeftBound
            -322,    // i4UpperBound
            -482    // i4LowerBound
            },
            // Shade
            {
            360,    // i4RightBound
            85,    // i4LeftBound
            -322,    // i4UpperBound
            -482    // i4LowerBound
            },
            // Twilight
            {
            -92,    // i4RightBound
            -252,    // i4LeftBound
            -322,    // i4UpperBound
            -482    // i4LowerBound
            },
            // Fluorescent
            {
            160,    // i4RightBound
            -283,    // i4LeftBound
            -322,    // i4UpperBound
            -507    // i4LowerBound
            },
            // Warm fluorescent
            {
            -194,    // i4RightBound
            -394,    // i4LeftBound
            -322,    // i4UpperBound
            -507    // i4LowerBound
            },
            // Incandescent
            {
            -194,    // i4RightBound
            -394,    // i4LeftBound
            -322,    // i4UpperBound
            -482    // i4LowerBound
            },
            // Gray World
            {
            5000,    // i4RightBound
            -5000,    // i4LeftBound
            5000,    // i4UpperBound
            -5000    // i4LowerBound
            }
        },
        // PWB default gain	
        {
            // Daylight
            {
            962,    // i4R
            512,    // i4G
            800    // i4B
            },
            // Cloudy daylight
            {
            1141,    // i4R
            512,    // i4G
            653    // i4B
            },
            // Shade
            {
            1214,    // i4R
            512,    // i4G
            607    // i4B
            },
            // Twilight
            {
            747,    // i4R
            512,    // i4G
            1081    // i4B
            },
            // Fluorescent
            {
            871,    // i4R
            512,    // i4G
            934    // i4B
            },
            // Warm fluorescent
            {
            654,    // i4R
            512,    // i4G
            1313    // i4B
            },
            // Incandescent
            {
            642,    // i4R
            512,    // i4G
            1293    // i4B
            },
            // Gray World
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            }
        },
        // AWB preference color	
        {
            // Tungsten
            {
            0,    // i4SliderValue
            6099    // i4OffsetThr
            },
            // Warm fluorescent	
            {
            0,    // i4SliderValue
            5704    // i4OffsetThr
            },
            // Shade
            {
            50,    // i4SliderValue
            343    // i4OffsetThr
            },
            // Daylight WB gain
            {
            884,    // i4R
            512,    // i4G
            542    // i4B
            },
            // Preference gain: strobe
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: tungsten
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: warm fluorescent
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: fluorescent
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: CWF
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: daylight
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: shade
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: daylight fluorescent
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            }
        },
        {// CCT estimation
            {// CCT
                2300,    // i4CCT[0]
                2850,    // i4CCT[1]
                4100,    // i4CCT[2]
                5100,    // i4CCT[3]
                6500    // i4CCT[4]
            },
            {// Rotated X coordinate
                -495,    // i4RotatedXCoordinate[0]
                -404,    // i4RotatedXCoordinate[1]
                -293,    // i4RotatedXCoordinate[2]
                -152,    // i4RotatedXCoordinate[3]
                0    // i4RotatedXCoordinate[4]
            }
        }
    },
    {0}
};

#include INCLUDE_FILENAME_ISP_LSC_PARAM
//};  //  namespace


typedef NSFeature::RAWSensorInfo<SENSOR_ID> SensorInfoSingleton_T;


namespace NSFeature {
template <>
UINT32
SensorInfoSingleton_T::
impGetDefaultData(CAMERA_DATA_TYPE_ENUM const CameraDataType, VOID*const pDataBuf, UINT32 const size) const
{
    UINT32 dataSize[CAMERA_DATA_TYPE_NUM] = {sizeof(NVRAM_CAMERA_ISP_PARAM_STRUCT),
                                             sizeof(NVRAM_CAMERA_3A_STRUCT),
                                             sizeof(NVRAM_CAMERA_SHADING_STRUCT),
                                             sizeof(NVRAM_LENS_PARA_STRUCT),
                                             sizeof(AE_PLINETABLE_T)};

    if (CameraDataType > CAMERA_DATA_AE_PLINETABLE || NULL == pDataBuf || (size < dataSize[CameraDataType]))
    {
        return 1;
    }

    switch(CameraDataType)
    {
        case CAMERA_NVRAM_DATA_ISP:
            memcpy(pDataBuf,&CAMERA_ISP_DEFAULT_VALUE,sizeof(NVRAM_CAMERA_ISP_PARAM_STRUCT));
            break;
        case CAMERA_NVRAM_DATA_3A:
            memcpy(pDataBuf,&CAMERA_3A_NVRAM_DEFAULT_VALUE,sizeof(NVRAM_CAMERA_3A_STRUCT));
            break;
        case CAMERA_NVRAM_DATA_SHADING:
            memcpy(pDataBuf,&CAMERA_SHADING_DEFAULT_VALUE,sizeof(NVRAM_CAMERA_SHADING_STRUCT));
            break;
        case CAMERA_DATA_AE_PLINETABLE:
            memcpy(pDataBuf,&g_PlineTableMapping,sizeof(AE_PLINETABLE_T));
            break;
        default:
            break;
    }
    return 0;
}}; // NSFeature


