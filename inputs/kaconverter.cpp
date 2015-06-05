#include "kaconverter.hpp"

KAConverter::KAConverter(PORT Port)
: ID(Port) {}

unsigned KAConverter::GetValue(void) const
{
	return GetValue(ID);
}

double KAConverter::GetVoltage(void) const
{
	return GetVoltage(ID);
}

unsigned KAConverter::GetValue(PORT Port)
{
	ADMUX	=	(Port | 64) & -33;
	ADCSRA	=	199;

	while (ADCSRA & 64);

	return ADCL + (ADCH << 8);
}

double KAConverter::GetVoltage(PORT Port)
{
	return (GetValue(Port) * 5.0) / 1024.0;
}
