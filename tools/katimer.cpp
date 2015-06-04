#include "katimer.hpp"

Timer::Timer(TIMER Number)
: ID(Number), Scale(0), Count(0), Prev(0)
{}

Timer::~Timer(void)
{
	Stop();
}

bool Timer::Start(void)
{
	if (!Count) return false;

	switch (ID)
	{
		case T1:

			TCCR0A	=	2;
			TCCR0B	= 	Scale;

			OCR0A	=	Count;
			OCR0B	=	Prev;

			TIMSK0	=	OCR0B ? 6 : 2;

			TCNT0	=	0;

		break;
		case T2:


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

void Timer::Stop(void)
{
	switch (ID)
	{
		case T1:
			TIMSK0 = 0;
		break;
		case T2:
			TIMSK1 = 0;
		break;
	}
}

void Timer::Reset(void)
{
	switch (ID)
	{
		case T1:
			TCNT0 = 0;
		break;
		case T2:
			TCNT1 = 0;
		break;
	}
}

void Timer::Resume(void)
{
	switch (ID)
	{
		case T1:
			TIMSK0 = OCR0B ? 6 : 2;
		break;
		case T2:
			TIMSK1 = OCR1B ? 6 : 2;
		break;
	}
}

bool Timer::Refresh(void)
{
	if (!Count) return false;

	switch (ID)
	{
		case T1:

			TCCR0B	= 	Scale;

			OCR0A	=	Count;
			OCR0B	=	Prev;

			TCNT0	=	0;

		break;
		case T2:

			TCCR1B	= 	Scale | 8;

			OCR1A	=	Count;
			OCR1B	=	Prev;

			TCNT1	=	0;

		break;
	}

	return true;
}

bool Timer::Active(void) const
{
	switch (ID)
	{
		case T1:
			return TIMSK0;

		case T2:
			return TIMSK1;

	}
}

void Timer::SetFreq(unsigned long FreqA, unsigned long FreqB)
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

void Timer::SetTime(unsigned long TimeA, unsigned long TimeB)
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

void Timer::SetPrefs(SCALER Scale, unsigned CapA, unsigned CapB)
{
	Scale	=	Scale;
	Count	=	CapA;
	Prev		=	CapB;
}
