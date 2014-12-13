#include "Timer.h"

Timer::Timer(TIMER eNumber)
: eTimer(eNumber)
{
	uScale	=	0;
	uCount	=	0;
	uPrev	=	0;
}

Timer::~Timer(void)
{
	Stop();
}

bool Timer::Start(void)
{
	if (!uCount) return false;

	cli();

	switch (eTimer)
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

	sei();

	return true;
}

void Timer::Stop(void)
{
	cli();

	switch (eTimer)
	{
		case T1:
			TIMSK0 = 0;
		break;
		case T2:
			TIMSK1 = 0;
		break;
	}

	sei();
}

void Timer::Reset(void)
{
	switch (eTimer)
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
	cli();

	switch (eTimer)
	{
		case T1:
			TIMSK0 = OCR0B ? 6 : 2;
		break;
		case T2:
			TIMSK1 = OCR1B ? 6 : 2;
		break;
	}

	sei();
}

void Timer::Refresh(void)
{
	cli();

	switch (eTimer)
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

	sei();
}

bool Timer::Active(void) const
{
	switch (eTimer)
	{
		case T1:
			return TIMSK0;

		case T2:
			return TIMSK1;

	}
}

void Timer::SetFreq(unsigned long uFreqA, unsigned long uFreqB)
{
	unsigned puDivs[] = { 1, 8, 64, 256, 1024 };
	unsigned puCaps[] = { 255, 65535, 255 };

	register unsigned long	uCap;
	register unsigned short	i;

	for (i = 0; i < 5; i++) if ((uCap = (F_CPU / puDivs[i]) / uFreqA - 1) < puCaps[eTimer]) break;

	uCount	=	(uCap > puCaps[eTimer]) ? 0 : uCap;
	uPrev	=	(uFreqB && uCount) ? (F_CPU / puDivs[i]) / uFreqB - 1 : 0;
	uScale	=	i + 1;
}

void Timer::SetTime(unsigned long uTimeA, unsigned long uTimeB)
{
	unsigned puDivs[] = { 1, 8, 64, 256, 1024 };
	unsigned puCaps[] = { 255, 65535, 255 };

	register unsigned long	uCap;
	register unsigned short	i;

	for (i = 0; i < 5; i++) if ((uCap = (F_CPU / 1000000) * (uTimeA / puDivs[i]) - 1) < puCaps[eTimer]) break;

	uCount	=	(uCap > puCaps[eTimer]) ? 0 : uCap;
	uPrev	=	(uTimeB && uCount) ? (F_CPU / 1000000) * (uTimeB / puDivs[i]) - 1 : 0;
	uScale	=	i + 1;
}

void Timer::SetPrefs(SCALER eScale, unsigned uCapA, unsigned uCapB)
{
	uScale	=	eScale + 1;
	uCount	=	uCapA;
	uPrev	=	uCapB;
}
