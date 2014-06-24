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

#ifndef _AF_ALGO_IF_H_
#define _AF_ALGO_IF_H_

namespace NS3A
{

class IAfAlgo {

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
protected:
    IAfAlgo() {}
    virtual ~IAfAlgo() {}

private:
    IAfAlgo(const IAfAlgo&);
    IAfAlgo& operator=(const IAfAlgo&);

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Interfaces.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:
	static  IAfAlgo* createInstance();
	virtual MVOID   destroyInstance() = 0;

	virtual MRESULT triggerAF() = 0;
	virtual MRESULT pauseAF() = 0;    
	virtual MRESULT resetAF() = 0;
    virtual MRESULT setAFMode(LIB3A_AF_MODE_T a_eAFMode) = 0;
	virtual MRESULT initAF(AF_INPUT_T a_sAFInput, AF_OUTPUT_T &a_sAFOutput) = 0;
	virtual MRESULT handleAF(AF_INPUT_T a_sAFInput, AF_OUTPUT_T &a_sAFOutput) = 0;
	virtual MRESULT setAFParam(AF_PARAM_T a_sAFParam, AF_CONFIG_T a_sAFConfig, AF_NVRAM_T a_sAFNvram) = 0;    
    virtual MRESULT getDebugInfo(AF_DEBUG_INFO_T &a_sAFDebugInfo) = 0;
    virtual void    setMFPos(MINT32 a_i4Pos) = 0;
    virtual void    updateAFtableBoundary(MINT32 a_i4InfPos, MINT32 a_i4MacroPos) = 0;
    virtual MRESULT setFDWin(AF_AREA_T a_sFDInfo) = 0;

private:

    

    
};

}; // namespace NS3A

#endif

