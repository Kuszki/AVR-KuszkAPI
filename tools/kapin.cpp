#include "kapin.hpp"

KAPin::KAPin(PORT Port, char Mask)
: MASK(Mask), ID(Port) {}

volatile unsigned char& KAPin::GetPin(PORT Port)
{
	switch (Port)
	{
		case PORT_B:
			return PINB;

		case PORT_D:
			return PIND;
	}
}

volatile unsigned char& KAPin::GetPort(PORT Port)
{
	switch (Port)
	{
		case PORT_B:
			return PORTB;

		case PORT_D:
			return PORTD;
	}
}

volatile unsigned char& KAPin::GetFlag(PORT Port)
{
	switch (Port)
	{
		case PORT_B:
			return DDRB;

		case PORT_D:
			return DDRD;
	}
}

void KAPin::SetOutputMode(PORT Port, char Mask)
{
	GetFlag(Port)	|=	Mask;
}

void KAPin::SetInputMode(PORT Port, char Mask)
{
	GetFlag(Port)	&=	~Mask;
	GetPort(Port)	&=	~Mask;
}

void KAPin::SetPullupMode(PORT Port, char Mask)
{
	GetFlag(Port)	&=	~Mask;
	GetPort(Port)	|=	Mask;
}
