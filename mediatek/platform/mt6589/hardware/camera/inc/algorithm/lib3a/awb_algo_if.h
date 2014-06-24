/*
**
** Copyright 2008, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#ifndef _AWB_ALGO_IF_H_
#define _AWB_ALGO_IF_H_

namespace NS3A
{

class IAwbAlgo {

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
protected:  //    Ctor/Dtor.
    IAwbAlgo() {}
    virtual ~IAwbAlgo() {}

private: // disable copy constructor and copy assignment operator
    IAwbAlgo(const IAwbAlgo&);
    IAwbAlgo& operator=(const IAwbAlgo&);

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Interfaces.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:
	static  IAwbAlgo* createInstance();
	virtual MVOID   destroyInstance() = 0;
	virtual MRESULT initAWB(AWB_INIT_INPUT_T &a_rAWBInitInput,
	                        AWB_OUTPUT_T &a_rAWBOutput,
	                        AWB_STAT_CONFIG_T (&a_rAWBStatConfig)[AWB_STROBE_MODE_NUM][AWB_SENSOR_MODE_NUM][LIB3A_AWB_MODE_NUM]) = 0;
	virtual MRESULT setAWBStatConfig(const AWB_STAT_CONFIG_T &a_rAWBStatConfig) = 0;
	virtual MRESULT setAWBMode(LIB3A_AWB_MODE_T a_eAWBMode) = 0;
	virtual MRESULT handleAWB(AWB_INPUT_T &a_rAWBInput, AWB_OUTPUT_T &a_rAWBOutput) = 0;
	virtual MINT32 getSceneLV() = 0;
	virtual MINT32 getCCT() = 0;
	virtual MRESULT getASDInfo(AWB_ASD_INFO_T &a_rAWBASDInfo) = 0;
    virtual MRESULT getLightProb(AWB_LIGHT_PROBABILITY_T &a_rAWBLightProb) = 0;
	virtual MRESULT getDebugInfo(AWB_DEBUG_INFO_T &a_rAWBDebugInfo, AWB_DEBUG_DATA_T &a_rAWBDebugData) = 0;
	virtual MRESULT updateAWBParam(AWB_INIT_INPUT_T &a_rAWBInitInput, AWB_STAT_CONFIG_T (&a_rAWBStatConfig)[AWB_STROBE_MODE_NUM][AWB_SENSOR_MODE_NUM][LIB3A_AWB_MODE_NUM]) = 0;
};

}; // namespace NS3A

#endif

