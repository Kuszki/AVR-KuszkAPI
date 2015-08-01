#include "kaflash.hpp"

KAFlash::KAFlash(unsigned Start)
: Adress(Start)
{}

char KAFlash::Read(void)
{
	return eeprom_read_byte((unsigned char*) Adress++);
}

void KAFlash::Read(void* Data, size_t Size)
{
	eeprom_read_block(Data, (unsigned char*) Adress, Size);

	Adress += Size;
}

void KAFlash::Write(char Char)
{
	eeprom_write_byte((unsigned char*) Adress++, Char);
}

void KAFlash::Write(const void* Data, size_t Size)
{
	eeprom_write_block(Data, (unsigned char*) Adress, Size);

	Adress += Size;
}

void KAFlash::SetAdress(unsigned Start)
{
	Adress = Start;
}

unsigned KAFlash::GetAdress(void) const
{
	return Adress;
}

char KAFlash::Read(unsigned Start)
{
	return eeprom_read_byte((unsigned char*) Start);
}

void KAFlash::Write(unsigned Start, char Char)
{
	eeprom_write_byte((unsigned char*) Start, Char);
}

char KAFlash::operator [] (unsigned Adress) const
{
	return Read(Adress);
}
