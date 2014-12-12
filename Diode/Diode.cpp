#include "Diode.h"

Diode::Diode(short iPin, bool bState)
: iPort(iPin)
{
	pinMode(iPort, OUTPUT);

	digitalWrite(iPort, bState);
}

Diode::~Diode(void)
{
	pinMode(iPort, INPUT);
}

void Diode::On(void)
{
	digitalWrite(iPort, true);
}

void Diode::Off(void)
{
	digitalWrite(iPort, false);
}

void Diode::SetState(bool bState)
{
	digitalWrite(iPort, bState);
}
