#include <stdio.h>
#include "BMS_Monitoring.h"

int monitorCondition_lowerThreshold (float paramVal, float paramMinThreshold, float paramMaxThreshold)
{
	int condition_lowerThreshold; 
	int ToleranceVal = 0.05 * paramMaxThreshold;
	int lowerToleranceLevel = paramMinThreshold+ToleranceVal;
	if (paramVal <= paramMinThreshold)
	{
		condition_lowerThreshold = LOW_BREACH;
	}
	else if ((paramVal > paramMinThreshold) && (paramVal <= lowerToleranceLevel))
	{
		condition_lowerThreshold = LOW_WWARNING;
	}
	return condition_lowerThreshold;
}

int monitorCondition_upperThreshold (float paramVal, float paramMaxThreshold)
{
	int condition_upperThreshold;
	int ToleranceVal = 0.05 * paramMaxThreshold;
	int upperToleranceLevel = paramMaxThreshold-ToleranceVal;
	if ((paramVal >= upperToleranceLevel) && (paramVal < paramMaxThreshold))
	{
		condition_upperThreshold = HIGH_WARNING;
	}
	else if (paramVal >= paramMaxThreshold)
	{
		condition_upperThreshold = HIGH_BREACH;
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
