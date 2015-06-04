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
