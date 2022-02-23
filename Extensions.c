#include <stdio.h>
#include "BMS_Monitoring.h"

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
