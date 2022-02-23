#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MIN_THRESHOLD_BATT_TEMP 0
#define MAX_THRESHOLD_BATT_TEMP 45
#define MIN_THRESHOLD_BATT_SoC 20
#define MAX_THRESHOLD_BATT_SoC 80
#define MAX_THRESHOLD_BATT_CHARGE_RATE 0.8 
#define LOW_BREACH  1
#define LOW_WARNING 2
#define NORMAL 3
#define HIGH_WARNING 4
#define HIGH_BREACH 5
/*
0 to 20: LOW_SOC_BREACH
21 to 24: LOW_SOC_WARNING
25 to 75: NORMAL
76 to 79: HIGH_SOC_WARNING
80 to 100: HIGH_SOC_BREACH

0 to 2.25: LOW_TEMP_WARNING
2.25 to 42.75: NORMAL
42.75 to 45: HIGH_TEMP_WARNING
45 TO 50: HIGH_TEMP_BREACH
*/

int checkBatteryTemperature(float temperature, char tempFormat);
int checkBatterySoC(float SoC);
int checkBatteryChargeRate(float chargeRate);
float tempUnitConversion(float temp, char tempUnit);
int monitorCondition_lowerThreshold (float paramVal, float paramMinThreshold, float paramMaxThreshold);
int monitorCondition_upperThreshold (float paramVal, float paramMaxThreshold);
int BatteryStateOk(float temp, float SoC, float battChargeRate, char tempUnit);
	
struct BattManagementSystem
{
    float Temperature;
    float stateOfCharge;
    float batteryChargeRate;
    char tempFormat;
};

int monitorCondition_lowerThreshold (float paramVal, float paramMinThreshold, float paramMaxThreshold)
{
	int condition_lowerThreshold; 
	int ToleranceVal = 0.05 * paramMaxThreshold;
	if (paramVal <= paramMinThreshold)
	{
		condition_lowerThreshold = 1;
	}
	else if ((paramVal > paramMinThreshold) && (paramVal <= (paramMinThreshold+ToleranceVal)))
	{
		condition_lowerThreshold = 2;
	}
	return condition_lowerThreshold;
}

int monitorCondition_upperThreshold (float paramVal, float paramMaxThreshold)
{
	int condition_upperThreshold;
	int ToleranceVal = 0.05 * paramMaxThreshold;
	if ((paramVal >= (paramMaxThreshold-ToleranceVal)) && (paramVal < paramMaxThreshold))
	{
		condition_upperThreshold = 4;
	}
	else if (paramVal >= paramMaxThreshold)
	{
		condition_upperThreshold = 5;
	}
	return condition_upperThreshold;
}

int checkBatteryTemperature(float temperature, char tempFormat) 
{
	if (tempFormat != 'C')
	{
		temperature = tempUnitConversion(temperature, tempFormat);	
	}
	int temp_condition_1 = monitorCondition_lowerThreshold(temperature, MIN_THRESHOLD_BATT_TEMP, MAX_THRESHOLD_BATT_TEMP );
	int temp_condition_2 = monitorCondition_upperThreshold(temperature, MAX_THRESHOLD_BATT_TEMP);
	int temp_condition = temp_condition_1 + temp_condition_2;
	return temp_condition;
}

int checkBatterySoC(float SoC) 
{
	int SoC_condition_1 = monitorCondition_lowerThreshold(SoC, MIN_THRESHOLD_BATT_SoC, MAX_THRESHOLD_BATT_SoC);
	int SoC_condition_2 = monitorCondition_upperThreshold(SoC, MAX_THRESHOLD_BATT_SoC);
	int SoC_condition = SoC_condition_1 + SoC_condition_2;
	return SoC_condition;
}

int checkBatteryChargeRate(float chargeRate)
{
	int battChargeRate_condition = monitorCondition_upperThreshold(chargeRate, MAX_THRESHOLD_BATT_CHARGE_RATE);
	return battChargeRate_condition;
}

float tempUnitConversion(float temp, char tempUnit)
{
	if (tempUnit == 'F')
	{
		temp = (temp - 32) * 5 / 9;
	}
	else if (tempUnit == 'K')
	{
		temp = temp - 273.15;
	}
	return temp;
}

int BatteryStateOk(float temp, float SoC, float battChargeRate, char tempUnit)
{
	int battCond;
	int cond_temp = checkBatteryTemperature(temp, tempUnit);
	int cond_SoC = checkBatterySoC(SoC);
	int cond_battChargeRate = checkBatteryChargeRate(battChargeRate);
	if ((cond_temp != 3) || (cond_SoC != 3) || (cond_battChargeRate != 3))
	{
		battCond = 0;
	}
	else
	{
		battCond = 1;
	}
	return battCond;
}

void main()
{
    struct BattManagementSystem bms = {30,60,0.5,'K'};
    assert(BatteryStateOk(bms.Temperature, bms.stateOfCharge, bms.batteryChargeRate, bms.tempFormat) == 1);
    struct BattManagementSystem bms1 = {50,90,0.9,'F'};
    assert(BatteryStateOk(bms1.Temperature, bms1.stateOfCharge, bms1.batteryChargeRate, bms1.tempFormat) == 1);	
    struct BattManagementSystem bms2 = {60,10,1.4,'K'};
    assert(BatteryStateOk(bms2.Temperature, bms2.stateOfCharge, bms2.batteryChargeRate, bms2.tempFormat) == 1);
} 
