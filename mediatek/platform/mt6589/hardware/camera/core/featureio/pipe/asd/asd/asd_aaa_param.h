/*
** $Log: asd_hal.h $
 *
*/ 

#ifndef _ASD_AAA_PARAM_H_
#define _ASD_AAA_PARAM_H_

typedef struct
{
    MINT32 i4AELv_x10;          // AE Lv
    MBOOL bAEBacklit;           // AE backlit condition
    MBOOL bAEStable;            // AE stable
    MINT16 i2AEFaceDiffIndex;  // Face AE difference index with central weighting
    MINT32 i4AWBRgain_X128;     // AWB Rgain
    MINT32 i4AWBBgain_X128;     // AWB Bgain
    MINT32 i4AWBRgain_D65_X128; // AWB Rgain (D65; golden sample)
    MINT32 i4AWBBgain_D65_X128; // AWB Bgain (D65; golden sample)
    MINT32 i4AWBRgain_CWF_X128; // AWB Rgain (CWF; golden sample)
    MINT32 i4AWBBgain_CWF_X128; // AWB Bgain (CWF; golden sample)
    MBOOL bAWBStable;           // AWB stable
    MINT32 i4AFPos;             // AF position
    MVOID *pAFTable;            // Pointer to AF table
    MINT32 i4AFTableOffset;     // AF table offset
    MINT32 i4AFTableMacroIdx;   // AF table macro index
    MINT32 i4AFTableIdxNum;     // AF table total index number
    MBOOL bAFStable;            // AF stable
} AAA_ASD_PARAM;
#endif

