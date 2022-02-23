#include "BMS_Monitoring.h"
	
struct BattManagementSystem
{
    float Temperature;
    float stateOfCharge;
    float batteryChargeRate;
    char tempFormat;
};

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
    //struct BattManagementSystem bms = {30,60,0.5,'K'};
    //assert(BatteryStateOk(bms.Temperature, bms.stateOfCharge, bms.batteryChargeRate, bms.tempFormat) == 1);
    struct BattManagementSystem bms1 = {50,90,0.9,'F'};
    assert(BatteryStateOk(bms1.Temperature, bms1.stateOfCharge, bms1.batteryChargeRate, bms1.tempFormat) == 1);	
    struct BattManagementSystem bms2 = {60,10,1.4,'K'};
    assert(BatteryStateOk(bms2.Temperature, bms2.stateOfCharge, bms2.batteryChargeRate, bms2.tempFormat) == 1);
} 
