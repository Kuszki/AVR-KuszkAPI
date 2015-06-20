#include "kaswitch.hpp"

KASwitch::KASwitch(PORT Port, char Mask, ONCHANGE Proc, EVENT Event, MODE Mode)
: KAPin(Port, Mask), Callback(Proc), Active(false)
{
	Count	=	(Event == ON_RISING) ? 1 : 0;
	Change	=	(Event == ON_SWITCH) ? 1 : 2;

	Last		=	(Mode == PULLUP);

	switch (Mode)
	{
		case NORMAL:
			SetInputMode(ID, MASK);
		break;
		case PULLUP:
			SetPullupMode(ID, MASK);
		break;
	}
}

bool KASwitch::Check(void)
{
	register bool Now = GetPin(ID) & MASK;

	if (Last != Now) Last = Now, Count++;

	if (Count == Change)
	{
		Count	= 0;
		Active	= !Active;

		if (Callback) Callback(Active);
	}

	return Active;
}

void KASwitch::On(bool Call)
{
	Active = true;

	if (Callback && Call) Callback(true);
}

void KASwitch::Off(bool Call)
{
	Active = false;

	if (Callback && Call) Callback(false);
}

void KASwitch::SetAction(ONCHANGE Proc)
{
	Callback = Proc;
}

void KASwitch::SetMode(EVENT Event)
{
	Count	=	(Event == ON_RISING) ? 1 : 0;
	Change	=	(Event == ON_SWITCH) ? 1 : 2;
}

void KASwitch::SetState(bool State)
{
	Active = State;
}
