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

			switch (uScale)
			{
				case 1:
					TCCR0B = _BV(CS00);
				break;
				case 8:
					TCCR0B = _BV(CS01);
				break;
				case 64:
					TCCR0B = _BV(CS00) | _BV(CS01);
				break;
				case 256:
					TCCR0B = _BV(CS02);
				break;
				case 1024:
					TCCR0B = _BV(CS00) | _BV(CS02);
				break;
			}

			TCCR0A	=	_BV(WGM01);

			OCR0A	=	uCount;
			OCR0B	=	uPrev;

			TIMSK0	=	OCR0B ? _BV(OCIE0A) | _BV(OCIE0B) : _BV(OCIE0A);

			TCNT0	=	0;

		break;
		case T2:

			switch (uScale)
			{
				case 1:
					TCCR1B = _BV(CS10) | _BV(WGM12);
				break;
				case 8:
					TCCR1B = _BV(CS11) | _BV(WGM12);
				break;
				case 64:
					TCCR1B = _BV(CS10) | _BV(CS11) | _BV(WGM12);
				break;
				case 256:
					TCCR1B = _BV(CS12) | _BV(WGM12);
				break;
				case 1024:
					TCCR1B = _BV(CS10) | _BV(CS12) | _BV(WGM12);
				break;
			}

			TCCR1A	=	0;

			OCR1A	=	uCount;
			OCR1B	=	uPrev;

			TIMSK1	=	OCR1B ? _BV(OCIE1A) | _BV(OCIE1B) : _BV(OCIE1A);

			TCNT1	=	0;

		break;
		case T3:

			switch (uScale)
			{
				case 1:
					TCCR2B = _BV(CS20);
				break;
				case 8:
					TCCR2B = _BV(CS21);
				break;
				case 64:
					TCCR2B = _BV(CS20) | _BV(CS21);
				break;
				case 256:
					TCCR2B = _BV(CS22);
				break;
				case 1024:
					TCCR2B = _BV(CS20) | _BV(CS22);
				break;
			}

			TCCR2A	=	_BV(WGM21);

			OCR2A	=	uCount;
			OCR2B	=	uPrev;

			TIMSK2	=	OCR2B ? _BV(OCIE2A) | _BV(OCIE2B) : _BV(OCIE2A);

			TCNT2	=	0;

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
		case T3:
			TIMSK2 = 0;
		break;
	}

	sei();
}

void Timer::Resume(void)
{
	switch (eTimer)
	{
		case T1:
			TIMSK0 = OCR0B ? _BV(OCIE0A) | _BV(OCIE0B) : _BV(OCIE0A);
		break;
		case T2:
			TIMSK1 = OCR1B ? _BV(OCIE1A) | _BV(OCIE1B) : _BV(OCIE1A);
		break;
		case T3:
			TIMSK2 = OCR2B ? _BV(OCIE2A) | _BV(OCIE2B) : _BV(OCIE2A);
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

		case T3:
			return TIMSK2;

	}
}

void Timer::SetFreq(unsigned long uFreq, unsigned short uProc)
{
	unsigned puDivs[] = { 1, 8, 64, 256, 1024 };
	unsigned puCaps[] = { 255, 65535, 255 };

	register unsigned long	uCap;
	register unsigned short	i;

	for (i = 0; i < 5; i++) if ((uCap = F_CPU / (puDivs[i] * uFreq) - 1) < puCaps[eTimer]) break;

	uCount	=	(uCap > puCaps[eTimer]) ? 0 : uCap;
	uPrev	=	uProc ? (uProc * uCount) / 360 : 0;
	uScale	=	puDivs[i];
}

void Timer::SetTime(unsigned long uTime, unsigned short uProc)
{
	unsigned puDivs[] = { 1, 8, 64, 256, 1024 };
	unsigned puCaps[] = { 255, 65535, 255 };

	register unsigned long	uCap;
	register unsigned short	i;

	for (i = 0; i < 5; i++) if ((uCap = (F_CPU / 1000000) * (uTime / puDivs[i]) - 1) < puCaps[eTimer]) break;

	uCount	=	(uCap > puCaps[eTimer]) ? 0 : uCap;
	uPrev	=	uProc ? (uProc * uCount) / 360 : 0;
	uScale	=	puDivs[i];
}

void Timer::SetPrefs(unsigned uDiv, unsigned uCap, unsigned uPre)
{
	uScale	=	uDiv;
	uCount	=	uCap;
	uPrev	=	uPre;
}
