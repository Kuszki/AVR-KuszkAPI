#include "Parser.h"

Parser::Parser(size_t sBytes, ONCOMPLETE fProc)
: sSize(sBytes), fCallback(fProc)
{
	ptData	=	new char[sSize];

	sPos		=	0;
}

Parser::~Parser(void)
{
	delete [] ptData;
}

bool Parser::Check(Stream* sPort)
{
	while (sPort->available())
	{
		ptData[sPos++] = sPort->read();

		if (sPos == sSize)
		{
			sPos = 0;

			fCallback(ptData, sSize);

			return true;
		}
	}

	return false;
}

void Parser::SetAction(ONCOMPLETE fProc)
{
	fCallback = fProc;
}

void Parser::SetSize(size_t sBytes)
{
	cli();

	sSize	=	sBytes;
	sPos		=	0;

	delete [] ptData;

	ptData = new char[sSize];

	sei();
}
