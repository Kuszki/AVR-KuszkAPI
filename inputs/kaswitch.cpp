#include "kaswitch.hpp"

KASwitch::KASwitch(PORT Port, char Mask, ONCHANGE Proc, EVENT Event, MODE Mode)
: KAPin(Port, Mask), Callback(Proc), Active(false)
{
	Count	=	(Event == ON_RISING) ? 1 : 0;
	Change	=	(Event == ON_SWITCH) ? 1 : 2;

	Last		=	(Mode == PULLUP);

	if (Mode == NORMAL) SetInputMode(ID, MASK);
	else SetPullupMode(ID, MASK);
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
	if (Event == ON_RISING) Count = 1;
	else Count = 0;

	if (Event == ON_SWITCH) Change = 1;
	else Change = 2;
}

void KASwitch::SetState(bool State)
{
	Active = State;
}
