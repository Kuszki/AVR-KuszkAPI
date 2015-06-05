#include "katimer.hpp"

KATimer::KATimer(TIMER Number)
: ID(Number), Scale(0), Count(0), Prev(0)
{}

KATimer::~KATimer(void)
{
	Stop();
}

bool KATimer::Start(void)
{
	if (!Count) return false;

	switch (ID)
	{
		case T_1:

			TCCR0A	=	2;
			TCCR0B	= 	Scale;

			OCR0A	=	Count;
			OCR0B	=	Prev;

			TIMSK0	=	OCR0B ? 6 : 2;

			TCNT0	=	0;

		break;
		case T_2:


			TCCR1A	=	0;
			TCCR1B	= 	Scale | 8;

			OCR1A	=	Count;
			OCR1B	=	Prev;

			TIMSK1	=	OCR1B ? 6 : 2;

			TCNT1	=	0;

		break;
	}

	return true;
}

void KATimer::Stop(void)
{
	switch (ID)
	{
		case T_1:
			TIMSK0 = 0;
		break;
		case T_2:
			TIMSK1 = 0;
		break;
	}
}

void KATimer::Reset(void)
{
	switch (ID)
	{
		case T_1:
			TCNT0 = 0;
		break;
		case T_2:
			TCNT1 = 0;
		break;
	}
}

void KATimer::Resume(void)
{
	switch (ID)
	{
		case T_1:
			TIMSK0 = OCR0B ? 6 : 2;
		break;
		case T_2:
			TIMSK1 = OCR1B ? 6 : 2;
		break;
	}
}

bool KATimer::Refresh(void)
{
	if (!Count) return false;

	switch (ID)
	{
		case T_1:

			TCCR0B	= 	Scale;

			OCR0A	=	Count;
			OCR0B	=	Prev;

			TCNT0	=	0;

		break;
		case T_2:

			TCCR1B	= 	Scale | 8;

			OCR1A	=	Count;
			OCR1B	=	Prev;

			TCNT1	=	0;

		break;
	}

	return true;
}

bool KATimer::Active(void) const
{
	switch (ID)
	{
		case T_1:
			return TIMSK0;

		case T_2:
			return TIMSK1;

	}
}

void KATimer::SetFreq(unsigned long FreqA, unsigned long FreqB)
{
	const unsigned PROGMEM Divs[] = { 1, 8, 64, 256, 1024 };
	const unsigned PROGMEM Caps[] = { 255, 65535 };

	register unsigned long	Cap;
	register unsigned short	i;

	for (i = 0; i < 5; i++) if ((Cap = (F_CPU / Divs[i]) / FreqA - 1) < Caps[ID]) break;

	Count	=	(Cap > Caps[ID]) ? 0 : Cap;
	Prev		=	(FreqB && Count) ? (F_CPU / Divs[i]) / FreqB - 1 : 0;
	Scale	=	i + 1;
}

void KATimer::SetTime(unsigned long TimeA, unsigned long TimeB)
{
	const unsigned PROGMEM Divs[] = { 1, 8, 64, 256, 1024 };
	const unsigned PROGMEM Caps[] = { 255, 65535 };

	register unsigned long	Cap;
	register unsigned short	i;

	for (i = 0; i < 5; i++) if ((Cap = (F_CPU / 1000000) * (TimeA / Divs[i]) - 1) < Caps[ID]) break;

	Count	=	(Cap > Caps[ID]) ? 0 : Cap;
	Prev		=	(TimeB && Count) ? (F_CPU / 1000000) * (TimeB / Divs[i]) - 1 : 0;
	Scale	=	i + 1;
}

void KATimer::SetPrefs(SCALER Div, unsigned CapA, unsigned CapB)
{
	Scale	=	Div;
	Count	=	CapA;
	Prev		=	CapB;
}
