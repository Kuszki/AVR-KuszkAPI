#include "Wave.h"

unsigned char Wave::uScale	=	0;
unsigned char Wave::uMode	=	0;

Wave::Wave(WAVE eNumber)
: ID(eNumber)
{
	uScale	=	0;
	uCount	=	0;

	pinMode(ID, OUTPUT);
}

Wave::~Wave(void)
{
	Stop();
}

bool Wave::Start(void)
{
	if (!uCount || !uScale || !uMode) return false;

	cli();

	TCCR2A	=	uMode | (TCCR2A & 128) | (TCCR2A & 32);
	TCCR2B	=	uScale;

	switch (ID)
	{
		case W1:

			TCCR2A	|=	128;

			OCR2A	=	uCount;

		break;
		case W2:

			TCCR2A	|=	32;

			OCR2B	=	uCount;

		break;
	}

	sei();

	return true;
}

void Wave::Stop(void)
{
	cli();

	switch (ID)
	{
		case W1:
			TCCR2A	&=	~128;
		break;
		case W2:
			TCCR2A	&=	~32;
		break;
	}

	sei();
}

void Wave::Resume(void)
{
	cli();

	switch (ID)
	{
		case W1:
			TCCR2A	|=	128;
		break;
		case W2:
			TCCR2A	|=	32;
		break;
	}

	sei();
}

bool Wave::Refresh(void)
{
	if (!uCount || !uScale || !uMode) return false;

	cli();

	TCCR2A	=	uMode | (TCCR2A & 128) | (TCCR2A & 32);
	TCCR2B	=	uScale;

	switch (ID)
	{
		case W1:

			OCR2A	=	uCount;

		break;
		case W2:

			OCR2B	=	uCount;

		break;
	}

	sei();

	return true;
}

bool Wave::Active(void) const
{
	switch (ID)
	{
		case W1:
			return (TCCR2A & 128) && TCCR2B;

		case W2:
			return (TCCR2A & 32) && TCCR2B;

	}
}

void Wave::SetWidth(unsigned char uWidth)
{
	uCount = uWidth;
}

void Wave::SetFreq(FREQ eFreq)
{
	unsigned char puDivs[]	=	{ 0, 1, 1, 2, 2, 3, 3, 4, 5, 6, 7, 7 };
	unsigned char puModes[]	=	{ 0, 3, 1, 3, 1, 3, 1, 1, 1, 1, 3, 1 };

	uScale	=	puDivs[eFreq];
	uMode	=	puModes[eFreq];
}
