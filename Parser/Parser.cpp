#include "Parser.h"

Parser::Parser(size_t sBytes, ONCOMPLETE fProc)
: sSize(sBytes), fCallback(fProc)
{
	ptData = new char[sSize];

	sPos = 0;
}

Parser::~Parser(void)
{
	delete ptData;
}

bool Parser::Check(Stream* sPort)
{
	while (sPort->available())
	{
		ptData[sPos++] = sPort->read();

		if (sPos == sSize)
		{
			sPos = 0;

			fCallback(ptData);

			return true;
		}
	}

	return false;
}

void Parser::SetAction(ONCOMPLETE fProc)
{
	fCallback = fProc;
}
