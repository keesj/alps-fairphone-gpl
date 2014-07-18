#ifndef _CUST_BAT_H_
#define _CUST_BAT_H_

#include <platform/mt_typedefs.h>

typedef enum
{
	Cust_CC_1600MA = 0x0,
	Cust_CC_1500MA = 0x1,
	Cust_CC_1400MA = 0x2,
	Cust_CC_1300MA = 0x3,
	Cust_CC_1200MA = 0x4,
	Cust_CC_1100MA = 0x5,
	Cust_CC_1000MA = 0x6,
	Cust_CC_900MA  = 0x7,
	Cust_CC_800MA  = 0x8,
	Cust_CC_700MA  = 0x9,
	Cust_CC_650MA  = 0xA,
	Cust_CC_550MA  = 0xB,
	Cust_CC_450MA  = 0xC,
	Cust_CC_400MA  = 0xD,
	Cust_CC_200MA  = 0xE,
	Cust_CC_70MA   = 0xF,
	Cust_CC_0MA	   = 0xDD
}cust_charging_current_enum;

typedef struct{	
	unsigned int BattVolt;
	unsigned int BattPercent;
}VBAT_TO_PERCENT;

/* Battery Temperature Protection */
#define MAX_CHARGE_TEMPERATURE  50
#define MIN_CHARGE_TEMPERATURE  0
#define ERR_CHARGE_TEMPERATURE  0xFF

/* Recharging Battery Voltage */
#define RECHARGING_VOLTAGE      4110

/* Charging Current Setting */
#define USB_CHARGER_CURRENT					Cust_CC_450MA
#define AC_CHARGER_CURRENT					Cust_CC_900MA //ghong tyang //Cust_CC_650MA
	
//#define  bq24158_AC_CHARGING_CURRENT_1250
//#define  bq24158_AC_CHARGING_CURRENT_1150
//#define  bq24158_AC_CHARGING_CURRENT_1050
#define  bq24158_AC_CHARGING_CURRENT_950
//#define  bq24158_AC_CHARGING_CURRENT_850
//#define  bq24158_AC_CHARGING_CURRENT_750

#define HIGH_BATTERY_VOLTAGE_SUPPORT    //w33 support

/* Battery Meter Solution */
#define CONFIG_ADC_SOLUTION 	1

/*Battery Voltage and Percentage Mapping Table */
VBAT_TO_PERCENT *Batt_VoltToPercent_Table;
/*[] = {
	
	{3400,0},
	{3686,10},
	{3740,20},
	{3771,30},
	{3789,40},
	{3820,50},
	{3873,60},
	{3943,70},
	{4013,80},
	{4100,90},
	{4189,100},
};*/

//////////ghong_yliu_begin_20120827
#if 1
//0C
VBAT_TO_PERCENT Batt_VoltToPercent_Table_0[] = {

	{3335,0},
	{3577,10},
	{3722,20},
	{3776,30},
	{3785,40},
	{3791,50},
	{3824,60},
	{3885,70},
	{3939,80},
	{4010,90},
	{4181,100},
};
VBAT_TO_PERCENT Batt_VoltToPercent_Table_25[] = {
	
	{3242,0},
	{3619,10},
	{3751,20},
	{3776,30},
	{3780,40},
	{3796,50},
	{3863,60},
	{3911,70},
	{3981,80},
	{4057,90},
	{4172,100}
};
VBAT_TO_PERCENT Batt_VoltToPercent_Table_50[] = {

	{3235,0},
	{3610,10},
	{3732,20},
	{3767,30},
	{3773,40},
	{3796,50},
	{3857,60},
	{3913,70},
	{3987,80},
	{4063,90},
	{4182,100}
};
#endif
/////////ghong_yliu_end_20120827

/* Precise Tunning */
#define BATTERY_AVERAGE_SIZE 	1200
//#define BATTERY_AVERAGE_SIZE 	60


#define CHARGING_IDLE_MODE	 1

#define CHARGING_PICTURE	 1

/* Common setting */
#define R_CURRENT_SENSE 2				// 0.2 Ohm
#define R_BAT_SENSE 4					// times of voltage
#define R_I_SENSE 4						// times of voltage
#define R_CHARGER_1 330
#define R_CHARGER_2 39
#define R_CHARGER_SENSE ((R_CHARGER_1+R_CHARGER_2)/R_CHARGER_2)	// times of voltage
#define V_CHARGER_MAX 6500				// 6.5 V
#define V_CHARGER_MIN 4400				// 4.4 V
#define V_CHARGER_ENABLE 0				// 1:ON , 0:OFF
#define BACKLIGHT_KEY 10					// camera key

/* Teperature related setting */
#define RBAT_PULL_UP_R             24000
//#define RBAT_PULL_UP_VOLT          2500
#define RBAT_PULL_UP_VOLT          1200
//#define TBAT_OVER_CRITICAL_LOW     68237
//#define TBAT_OVER_CRITICAL_LOW     483954
#define TBAT_OVER_CRITICAL_LOW     70603
#define BAT_TEMP_PROTECT_ENABLE    0
#define BAT_NTC_10 0
#define BAT_NTC_47 0
#define BAT_NTC_TSM_1

/* The option of new charging animation */
#define ANIMATION_NEW

#endif /* _CUST_BAT_H_ */ 
