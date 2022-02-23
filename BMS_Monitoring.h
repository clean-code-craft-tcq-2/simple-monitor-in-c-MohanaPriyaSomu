#include <stdio.h>
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

extern int checkBatteryTemperature(float temperature, char tempFormat);
extern int checkBatterySoC(float SoC);
extern int checkBatteryChargeRate(float chargeRate);
float tempUnitConversion(float temp, char tempUnit);
int monitorCondition_lowerThreshold (float paramVal, float paramMinThreshold, float paramMaxThreshold);
int monitorCondition_upperThreshold (float paramVal, float paramMaxThreshold);
extern int BatteryStateOk(float temp, float SoC, float battChargeRate, char tempUnit);
	
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
