#ifndef _CUST_BAT_H_
#define _CUST_BAT_H_

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
#define CONFIG_USB_IF 						0   
#define USB_CHARGER_CURRENT_SUSPEND			Cust_CC_0MA		// def CONFIG_USB_IF
#define USB_CHARGER_CURRENT_UNCONFIGURED	Cust_CC_70MA	// def CONFIG_USB_IF
#define USB_CHARGER_CURRENT_CONFIGURED		Cust_CC_450MA	// def CONFIG_USB_IF
#define USB_CHARGER_CURRENT					Cust_CC_450MA
#define AC_CHARGER_CURRENT					Cust_CC_900MA	

//#define  bq24158_AC_CHARGING_CURRENT_1250
//#define  bq24158_AC_CHARGING_CURRENT_1150
//#define  bq24158_AC_CHARGING_CURRENT_1050
//#define  bq24158_AC_CHARGING_CURRENT_950	//ghong hhongyan 20130816
//#define  bq24158_AC_CHARGING_CURRENT_850
#define  bq24158_AC_CHARGING_CURRENT_750

#define HIGH_BATTERY_VOLTAGE_SUPPORT    //w33 support

/* Battery Meter Solution */
#define CONFIG_ADC_SOLUTION 	1

/* Battery Voltage and Percentage Mapping Table */
VBAT_TO_PERCENT Batt_VoltToPercent_Table[] = {
	/*BattVolt,BattPercent*/
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
};

/* Precise Tunning */
//#define BATTERY_AVERAGE_SIZE 	30
#define BATTERY_AVERAGE_SIZE   	6			//12			//modify by xchangwei 20140506		

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

/* Battery Notify */
#define BATTERY_NOTIFY_CASE_0001
#define BATTERY_NOTIFY_CASE_0002
//#define BATTERY_NOTIFY_CASE_0003
//#define BATTERY_NOTIFY_CASE_0004
//#define BATTERY_NOTIFY_CASE_0005

//#define CONFIG_POWER_VERIFY

#endif /* _CUST_BAT_H_ */ 
