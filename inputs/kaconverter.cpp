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
	unsigned Value;

	ADMUX	=	Port;
	ADMUX	|=	(1 << REFS0);
	ADMUX	&=	~(1 << ADLAR);

	ADCSRA 	|=	(1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	ADCSRA	|=	(1 << ADEN);

	ADCSRA	|=	(1 << ADSC);

	while (ADCSRA & (1 << ADSC));

	Value = ADCL;
	Value = (ADCH << 8) + Value;

	return Value;
}

double KAConverter::GetVoltage(PORT Port)
{
	return (GetValue(Port) * 5.0) / 1024.0;
}
