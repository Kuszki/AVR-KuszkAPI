#include "kaint.hpp"

KAInt::KAInt(INT Int, MODE Mode)
: ID(Int)
{
	SetMode(ID, Mode);

	Enable(ID);
}

KAInt::~KAInt(void)
{
	Disable(ID);

	SetMode(ID, ON_CHANGE);
}

void KAInt::SetMode(MODE Mode)
{
	SetMode(ID, Mode);
}

KAInt::MODE KAInt::GetMode(void) const
{
	return GetMode(ID);
}

void KAInt::Enable(void)
{
	Enable(ID);
}

void KAInt::Disable(void)
{
	Disable(ID);
}

bool KAInt::Active(void) const
{
	return Active(ID);
}

void KAInt::SetMode(INT Int, MODE Mode)
{
	switch (Int)
	{
		case INT_0:

			EICRA &= 0b11111100;
			EICRA |= Mode;

		break;
		case INT_1:

			EICRA &= 0b11110011;
			EICRA |= Mode << 2;

		break;
	}
}

KAInt::MODE KAInt::GetMode(INT Int)
{
	switch (Int)
	{
		case INT_0:
		return MODE(EICRA & 0b00000011);

		case INT_1:
		return MODE((EICRA & 0b00001100) >> 2);

	}
}

void KAInt::Enable(INT Int)
{
	switch (Int)
	{
		case INT_0:

			EIMSK |= 0b00000001;

		break;
		case INT_1:

			EIMSK |= 0b00000010;

		break;
	}
}

void KAInt::Disable(INT Int)
{
	switch (Int)
	{
		case INT_0:

			EIMSK &= 0b11111110;

		break;
		case INT_1:

			EIMSK &= 0b11111101;

		break;
	}
}

bool KAInt::Active(INT Int)
{
	switch (Int)
	{
		case INT_0:
		return EIMSK & 0b00000001;

		case INT_1:
		return EIMSK & 0b00000010;

	}
}
