#include "Timer.h"

Timer::Timer(TIMER eNumber)
: eTimer(eNumber)
{
	uScale	=	0;
	uCount	=	0;
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

			TCCR0A = TCCR0B = TCNT0 = 0;

			OCR0A = uCount;

			switch (uScale)
			{
				case 1:
					TCCR0B |= _BV(CS00);
				break;
				case 8:
					TCCR0B |= _BV(CS01);
				break;
				case 64:
					TCCR0B |= _BV(CS00) | _BV(CS01);
				break;
				case 256:
					TCCR0B |= _BV(CS02);
				break;
				case 1024:
					TCCR0B |= _BV(CS00) | _BV(CS02);
				break;
			}

			TCCR0A |= _BV(WGM01);

			TIMSK0 = _BV(OCIE0A);

		break;
		case T2:

			TCCR1A = TCCR1B = TCNT1 = 0;

			OCR1A = uCount;

			switch (uScale)
			{
				case 1:
					TCCR1B |= _BV(CS10);
				break;
				case 8:
					TCCR1B |= _BV(CS11);
				break;
				case 64:
					TCCR1B |= _BV(CS10) | _BV(CS11);
				break;
				case 256:
					TCCR1B |= _BV(CS12);
				break;
				case 1024:
					TCCR1B |= _BV(CS10) | _BV(CS12);
				break;
			}

			TCCR1B |= _BV(WGM12);

			TIMSK1 = _BV(OCIE1A);

		break;
		case T3:

			TCCR2A = TCCR2B = TCNT2 = 0;

			OCR2A = uCount;

			switch (uScale)
			{
				case 1:
					TCCR2B |= _BV(CS20);
				break;
				case 8:
					TCCR2B |= _BV(CS21);
				break;
				case 64:
					TCCR2B |= _BV(CS20) | _BV(CS21);
				break;
				case 256:
					TCCR2B |= _BV(CS22);
				break;
				case 1024:
					TCCR2B |= _BV(CS20) | _BV(CS22);
				break;
			}

			TCCR2A |= _BV(WGM21);

			TIMSK2 = _BV(OCIE2A);

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

void Timer::SetFreq(long unsigned uFreq)
{
	unsigned puDivs[] = { 1, 8, 64, 256, 1024 };
	unsigned puCaps[] = { 255, 65535, 255 };

     register unsigned long	uCap;
     register unsigned short	i;

     for (i = 0; i < 5; i++) if ((uCap = F_CPU / (puDivs[i] * uFreq) - 1) < 256) break;

     uCount	=	(uCap > puCaps[eTimer]) ? 0 : uCap;
     uScale	=	puDivs[i];
}

void Timer::SetTime(long unsigned uTime)
{
	SetFreq(1000000 / uTime);
}

void Timer::SetPrefs(unsigned uDiv, unsigned uCap)
{
	uScale	=	uDiv;
	uCount	=	uCap;
}
