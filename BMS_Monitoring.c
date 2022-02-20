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
int monitorCondition (float paramVal, float paramMinThreshold, float paramMaxThreshold)
bool BatteryStateOk(float temp, float SoC, float battChargeRate, char tempUnit)
	
struct BattManagementSystem
{
    float Temperature;
    float stateOfCharge;
    float batteryChargeRate;
    char tempFormat;
};

int monitorCondition (float paramVal, float paramMinThreshold, float paramMaxThreshold)
{
	int condition; 
	ToleranceVal = 0.05 * paramMaxThreshold;
	if (paramVal <= paramMinThreshold)
	{
		condition = 1;
	}
	else if ((paramVal > paramMinThreshold) && (paramVal <= (paramMinThreshold+ToleranceVal)))
	{
		condition = 2;
	}
	else if ((paramVal > (paramMinThreshold+ToleranceVal)) && (paramVal > (paramMinThreshold+ToleranceVal)))
	{
		condition = 3;
	}
	else if ((paramVal >= (paramMaxThreshold-ToleranceVal)) && (paramVal < paramMaxThreshold))
	{
		condition = 4;
	}
	else if (paramVal >= paramMaxThreshold)
	{
		condition = 5;
	}
	else
	{
		/*do nothing*/
	}
	return condition;
}

int checkBatteryTemperature(float temperature, char tempFormat) 
{
	int temp_condition;
	tempUnitConversion(temperature, tempFormat);
	temp_condition = monitorCondition(temperature, MIN_THRESHOLD_BATT_TEMP, MAX_THRESHOLD_BATT_TEMP);
	return temp_condition;
}

int checkBatterySoC(float SoC) 
{
	int SoC_condition;
	SoC_condition = monitorCondition(SoC, MIN_THRESHOLD_BATT_SoC, MAX_THRESHOLD_BATT_SoC);
	return SoC_condition;
}

int checkBatteryChargeRate(float chargeRate)
{
	int battChargeRate_condition;
	battChargeRate_condition = monitorCondition(chargeRate, MAX_THRESHOLD_BATT_CHARGE_RATE);
	return battChargeRate_condition;
}

float tempUnitConversion(float temp, char tempUnit)
{
	switch (tempUnit)
	{
		case 'F':
			temp = (temp - 32) * 5 / 9;
			break;
		case 'K':
			temp = temp - 273.15;
			break;
		default:
			/*do nothing*/
			break;
	}
	return temp;
}

bool BatteryStateOk(float temp, float SoC, float battChargeRate, char tempUnit)
{
	cond_temp = checkBatteryTemperature(temp, tempUnit);
	cond_SoC = checkBatterySoC(SoC);
	cond_battChargeRate = checkBatteryChargeRate(battChage);
	if ((cond_temp == 3) && (cond_SoC == 3) && (cond_battChargeRate == 3))
	{
		BattCond = 1;
	}
	else
	{
		BattCond = 0;
	}
	return BatteryCond;
}

void main()
{
    struct BattManagementSystem bms = {30,60,0.5,'C'};
    assert(BatteryStateOk(bms.Temperature, bms.stateOfCharge, bms.batteryChargeRate, bms.tempFormat) == 1);
    struct BattManagementSystem bms1 = {50,90,0.9,'F'};
    assert(BatteryStateOk(bms.Temperature, bms.stateOfCharge, bms.batteryChargeRate, bms.tempFormat) == 1);	
    struct BattManagementSystem bms2 = {60,10,1.4,'K'};
    assert(BatteryStateOk(bms.Temperature, bms.stateOfCharge, bms.batteryChargeRate, bms.tempFormat) == 1);
} 
