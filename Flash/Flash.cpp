#include "Flash.h"

Flash::Flash(unsigned uStart)
: uAdress(uStart) {}

char Flash::Read(void)
{
	return eeprom_read_byte((unsigned char*) uAdress++);
}

void Flash::Read(void* pvData, size_t sSize)
{
	eeprom_read_block(pvData, (unsigned char*) uAdress, sSize);

	uAdress += sSize;
}

void Flash::Write(char cChar)
{
	eeprom_write_byte((unsigned char*) uAdress++, cChar);
}

void Flash::Write(const void* pvData, size_t sSize)
{
	eeprom_write_block(pvData, (unsigned char*) uAdress, sSize);

	uAdress += sSize;
}

void Flash::SetAdress(unsigned uStart)
{
	uAdress = uStart;
}

unsigned Flash::GetAdress(void) const
{
	return uAdress;
}

char Flash::Read(unsigned uStart)
{
	return eeprom_read_byte((unsigned char*) uStart);
}

void Flash::Write(unsigned uStart, char cChar)
{
	eeprom_write_byte((unsigned char*) uStart, cChar);
}
