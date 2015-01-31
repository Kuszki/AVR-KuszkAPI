#include "Switch.h"

Switch::Switch(short iPin, ONCHANGE fProc, MODE eMode, short iType)
: iInput(iPin), fCallback(fProc), bOn(false)
{
	iCount	=	(eMode == ON_RISING) ? 1 : 0;
	iChange	=	(eMode == ON_SWITCH) ? 1 : 2;

	bLast	=	(iType == INPUT_PULLUP);

	pinMode(iInput, iType);
}

bool Switch::Check(void)
{
	register bool bNow = digitalRead(iInput);

	if (bLast != bNow) bLast = bNow, iCount++;

	if (iCount == iChange)
	{
		iCount = 0;
		bOn = !bOn;

		if (fCallback) fCallback(bOn);
	}

	return bOn;
}

void Switch::On(void)
{
	bOn = true;

	if (fCallback) fCallback(true);
}

void Switch::Off(void)
{
	bOn = false;

	if (fCallback) fCallback(false);
}

void Switch::SetAction(ONCHANGE fProc)
{
	fCallback = fProc;
}

void Switch::SetMode(MODE eMode)
{
	if (eMode == ON_RISING) iCount = 1;
	else iCount = 0;

	if (eMode == ON_SWITCH) iChange = 1;
	else iChange = 2;
}

void Switch::SetState(bool bState)
{
	bOn = bState;
}
