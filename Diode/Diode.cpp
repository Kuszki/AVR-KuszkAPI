#include "Diode.h"

Diode::Diode(short iPin, bool bState)
: PORT(iPin)
{
	pinMode(PORT, OUTPUT);

	digitalWrite(PORT, bState);
}

Diode::~Diode(void)
{
	pinMode(PORT, INPUT);
}

void Diode::On(void)
{
	digitalWrite(PORT, true);
}

void Diode::Off(void)
{
	digitalWrite(PORT, false);
}

void Diode::SetState(bool bState)
{
	digitalWrite(PORT, bState);
}
