#include "kawave.hpp"

unsigned char KAWave::Scale	=	0;
unsigned char KAWave::Mode	=	0;

KAWave::KAWave(WAVE Number)
: ID(Number), Count(0)
{
	switch (ID)
	{
		case W_1:

			DDRB		|=	8;

		break;
		case W_2:

			DDRD		|=	8;

		break;
	}
}

KAWave::~KAWave(void)
{
	switch (ID)
	{
		case W_1:

			TCCR2A	&=	~128;
			DDRB		&=	~8;

		break;
		case W_2:

			TCCR2A	&=	~32;
			DDRD		&=	~8;

		break;
	}
}

bool KAWave::Start(void)
{
	if (!Count || !Scale || !Mode) return false;

	TCCR2A	=	Mode | (TCCR2A & 160);
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

void KAWave::Stop(void)
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

void KAWave::Resume(void)
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

bool KAWave::Refresh(void)
{
	if (!Count || !Scale || !Mode) return false;

	TCCR2A	=	Mode | (TCCR2A & 160);
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

bool KAWave::Active(void) const
{
	switch (ID)
	{
		case W_1:
			return (TCCR2A & 128) && TCCR2B;

		case W_2:
			return (TCCR2A & 32) && TCCR2B;

	}
}

void KAWave::SetWidth(unsigned char Width)
{
	Count = Width;
}

void KAWave::SetFreq(FREQ Freq)
{
	const unsigned char PROGMEM Divs[]		=	{ 0, 1, 1, 2, 2, 3, 3, 4, 5, 6, 7, 7 };
	const unsigned char PROGMEM Modes[]	=	{ 0, 3, 1, 3, 1, 3, 1, 1, 1, 1, 3, 1 };

	Scale	=	Divs[Freq];
	Mode		=	Modes[Freq];
}
