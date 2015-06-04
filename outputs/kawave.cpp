#include "kawave.hpp"

unsigned char Wave::Scale	=	0;
unsigned char Wave::Mode		=	0;

Wave::Wave(WAVE Number)
: ID(Number), Count(0)
{
	switch (ID)
	{
		case W_1:

			DDRB		|=	8;

		break;
		case W_2:

			DDRD		|=	4;

		break;
	}
}

Wave::~Wave(void)
{
	switch (ID)
	{
		case W_1:

			TCCR2A	&=	~128;
			DDRB		&=	~8;

		break;
		case W_2:

			TCCR2A	&=	~32;
			DDRD		&=	~4;

		break;
	}
}

bool Wave::Start(void)
{
	if (!Count || !Scale || !Mode) return false;

	TCCR2A	=	Mode | (TCCR2A & 128) | (TCCR2A & 32);
	TCCR2B	=	Scale;

	switch (ID)
	{
		case W_1:

			TCCR2A	|=	128;

			OCR2A	=	Count;

		break;
		case W_2:

			TCCR2A	|=	32;

			OCR2B	=	Count;

		break;
	}

	sei();

	return true;
}

void Wave::Stop(void)
{
	switch (ID)
	{
		case W_1:
			TCCR2A	&=	~128;
		break;
		case W_2:
			TCCR2A	&=	~32;
		break;
	}
}

void Wave::Resume(void)
{
	switch (ID)
	{
		case W_1:
			TCCR2A	|=	128;
		break;
		case W_2:
			TCCR2A	|=	32;
		break;
	}

	sei();
}

bool Wave::Refresh(void)
{
	if (!Count || !Scale || !Mode) return false;

	TCCR2A	=	Mode | (TCCR2A & 128) | (TCCR2A & 32);
	TCCR2B	=	Scale;

	switch (ID)
	{
		case W_1:

			OCR2A	=	Count;

		break;
		case W_2:

			OCR2B	=	Count;

		break;
	}

	sei();

	return true;
}

bool Wave::Active(void) const
{
	switch (ID)
	{
		case W_1:
			return (TCCR2A & 128) && TCCR2B;

		case W_2:
			return (TCCR2A & 32) && TCCR2B;

	}
}

void Wave::SetWidth(unsigned char Width)
{
	Count = Width;
}

void Wave::SetFreq(FREQ Freq)
{
	const unsigned char PROGMEM Divs[]		=	{ 0, 1, 1, 2, 2, 3, 3, 4, 5, 6, 7, 7 };
	const unsigned char PROGMEM Modes[]	=	{ 0, 3, 1, 3, 1, 3, 1, 1, 1, 1, 3, 1 };

	Scale	=	Divs[Freq];
	Mode		=	Modes[Freq];
}
