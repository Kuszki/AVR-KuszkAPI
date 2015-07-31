#include "kaoutput.hpp"

KAOutput::KAOutput(PORT Port, char Mask)
: KAPin(Port, Mask)
{
	SetOutputMode(ID, MASK);
}

KAOutput::~KAOutput(void)
{
	SetInputMode(ID, MASK);
}

void KAOutput::On(void)
{
	GetPort(ID)	|=	MASK;
}

void KAOutput::Off(void)
{
	GetPort(ID)	&=	~MASK;
}

void KAOutput::Switch(void)
{
	if (GetState()) Off();
	else On();
}

void KAOutput::SetState(bool State)
{
	if (State) On();
	else Off();
}

bool KAOutput::GetState(void) const
{
	return GetPort(ID) & MASK;
}

void KAOutput::SetState(PORT Port, char Mask, bool State)
{
	SetOutputMode(Port, Mask);

	if (State) GetPort(Port) |= Mask;
	else GetPort(Port) &= ~Mask;
}

bool KAOutput::GetState(PORT Port, char Mask)
{
	return GetPort(Port) & Mask;
}

void KAOutput::SwitchState(PORT Port, char Mask, char Count, char Delay)
{
	SetOutputMode(Port, Mask);

	bool State = GetState(Port, Mask);

	while (Count--)
	{
		if (State) GetPort(Port) &= ~Mask;
		else GetPort(Port) |= Mask;

		State = !State;

		if (Delay) DELAY(Delay);
	}
}
