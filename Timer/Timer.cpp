#include "Timer.h"

Timer::Timer(TIMER eNumber)
: ID(eNumber), uScale(0), uCount(0), uPrev(0)
{}

Timer::~Timer(void)
{
	Stop();
}

bool Timer::Start(void)
{
	if (!uCount) return false;

	switch (ID)
	{
		case T1:

			TCCR0A	=	2;
			TCCR0B	= 	uScale;

			OCR0A	=	uCount;
			OCR0B	=	uPrev;

			TIMSK0	=	OCR0B ? 6 : 2;

			TCNT0	=	0;

		break;
		case T2:


			TCCR1A	=	0;
			TCCR1B	= 	uScale | 8;

			OCR1A	=	uCount;
			OCR1B	=	uPrev;

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
	if (!uCount) return false;

	switch (ID)
	{
		case T1:

			TCCR0B	= 	uScale;

			OCR0A	=	uCount;
			OCR0B	=	uPrev;

			TCNT0	=	0;

		break;
		case T2:

			TCCR1B	= 	uScale | 8;

			OCR1A	=	uCount;
			OCR1B	=	uPrev;

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

void Timer::SetFreq(unsigned long uFreqA, unsigned long uFreqB)
{
	const unsigned PROGMEM puDivs[] = { 1, 8, 64, 256, 1024 };
	const unsigned PROGMEM puCaps[] = { 255, 65535 };

	register unsigned long	uCap;
	register unsigned short	i;

	for (i = 0; i < 5; i++) if ((uCap = (F_CPU / puDivs[i]) / uFreqA - 1) < puCaps[ID]) break;

	uCount	=	(uCap > puCaps[ID]) ? 0 : uCap;
	uPrev	=	(uFreqB && uCount) ? (F_CPU / puDivs[i]) / uFreqB - 1 : 0;
	uScale	=	i + 1;
}

void Timer::SetTime(unsigned long uTimeA, unsigned long uTimeB)
{
	const unsigned PROGMEM puDivs[] = { 1, 8, 64, 256, 1024 };
	const unsigned PROGMEM puCaps[] = { 255, 65535 };

	register unsigned long	uCap;
	register unsigned short	i;

	for (i = 0; i < 5; i++) if ((uCap = (F_CPU / 1000000) * (uTimeA / puDivs[i]) - 1) < puCaps[ID]) break;

	uCount	=	(uCap > puCaps[ID]) ? 0 : uCap;
	uPrev	=	(uTimeB && uCount) ? (F_CPU / 1000000) * (uTimeB / puDivs[i]) - 1 : 0;
	uScale	=	i + 1;
}

void Timer::SetPrefs(SCALER eScale, unsigned uCapA, unsigned uCapB)
{
	uScale	=	eScale;
	uCount	=	uCapA;
	uPrev	=	uCapB;
}
