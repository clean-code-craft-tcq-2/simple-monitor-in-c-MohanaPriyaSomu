#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MIN_THRESHOLD_BATT_TEMP 0
#define MAX_THRESHOLD_BATT_TEMP 45
#define MIN_THRESHOLD_BATT_SoC 20
#define MAX_THRESHOLD_BATT_SoC 80
#define MAX_THRESHOLD_BATT_CHARGE_RATE 0.8 

void validityCheck (int validity, char* param);
int checkBatteryTemperature(float temperature);
int checkBatterySoC(float SoC);
int checkBatteryChargeRate(float chargeRate);
int rangeConditionCheck(float param, int min_threshold, int max_threshold);
int limitConditionCheck(float param, float max_threshold);

int rangeConditionCheck(float param, int min_threshold, int max_threshold)
{
	if((param > min_threshold) && (param < max_threshold))
	{
		return 1;
	}
	return 0;
}

int limitConditionCheck(float param, float max_threshold) {
	if (param < max_threshold) {
		return 1;
	}
	return 0;
}

struct BattManagementSystem
{
    float Temperature;
    float stateOfCharge;
    float batteryChargeRate;
    char tempFormat;
};

void validityCheck (int validity, char* param)
{
	char alert[100] = "out of range";
	char param1[100];
	strcpy(param1,param);
	if (validity == 0)
	{
		strcat(param1, alert);
		printf("%s \n", param1);
	}
}

int checkBatteryTemperature(float temperature, char tempFormat) 
{
	int validity;
	tempUnitConversion(temperature, tempFormat);
	validity = rangeConditionCheck(temperature, MIN_THRESHOLD_BATT_TEMP, MAX_THRESHOLD_BATT_TEMP);
	validityCheck(validity, "Temperature");
	return validity;
}

int checkBatterySoC(float SoC) 
{
	int validity;
	validity = rangeConditionCheck(SoC, MIN_THRESHOLD_BATT_SoC, MAX_THRESHOLD_BATT_SoC);
	validityCheck(validity, "State of Charge");
	return validity;
}

int checkBatteryChargeRate(float chargeRate){
	int validity;
	validity = limitConditionCheck(chargeRate, MAX_THRESHOLD_BATT_CHARGE_RATE);
	validityCheck(validity, "Charge Rate");
	return validity;
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

void main()
{
    struct BattManagementSystem bms = {30,60,0.5,'C'};
    assert(checkBatteryTemperature(bms.Temperature, bms.tempFormat) == 1);
    assert(checkBatterySoC(bms.stateOfCharge) == 1);
    assert(checkBatteryChargeRate(bms.batteryChargeRate) == 1);
    struct BattManagementSystem bms1 = {50,90,0.9,'F'};
    assert(checkBatteryTemperature(bms1.Temperature, bms1.tempFormat) == 0);
    assert(checkBatterySoC(bms1.stateOfCharge) == 0);
    assert(checkBatteryChargeRate(bms1.batteryChargeRate) == 0);
    struct BattManagementSystem bms2 = {60,10,1.4,'K'};
    assert(checkBatteryTemperature(bms2.Temperature, bms2.tempFormat) == 0);
    assert(checkBatterySoC(bms2.stateOfCharge) == 0);
    assert(checkBatteryChargeRate(bms2.batteryChargeRate) == 0);
} 
