#include "Comport.h"

volatile Comport::Buffer bRecv = {0, 0};
volatile Comport::Buffer bSend = {0, 0};

volatile Comport::Buffer* Comport::bIN	= &bRecv;
volatile Comport::Buffer* Comport::bOUT	= &bSend;

Comport::Comport(unsigned uRate)
{
	uRate = (F_CPU / 8 / uRate - 1) / 2;

	UCSR0A = 0;
	UCSR0C = 0x06;

	UBRR0H = uRate >> 8;
	UBRR0L = uRate;
}

Comport::~Comport(void)
{
	Stop();

	UCSR0A = 0;
	UCSR0C = 0;

	UBRR0H = 0;
	UBRR0L = 0;
}

void Comport::Start(void)
{
	UCSR0B = 152;
}

void Comport::Stop(void)
{
	while (bOUT->uHead != bOUT->uTail);

	UCSR0B = 0;

	bIN->uHead = bIN->uTail;
}

void Comport::Send(char cChar)
{
	register unsigned short uHead = (bOUT->uHead + 1) & (BUFF_SIZE - 1);

	while (uHead == bOUT->uTail);

	bOUT->pcBuff[uHead] = cChar;
	bOUT->uHead = uHead;

	UCSR0B |= (1 << UDRE0);
}

void Comport::Send(const char* pcData)
{
	register char cBuff;

	while (cBuff = *pcData++) Send(cBuff);
}

void Comport::Send(const void* pvData, size_t sBytes)
{
	register const char* pcData = (char*) pvData;

	while (sBytes--) Send(*pcData++);
}

char Comport::Recv(void)
{
    while (bIN->uHead == bIN->uTail);

    bIN->uTail = (bIN->uTail + 1) & (BUFF_SIZE - 1);

    return bIN->pcBuff[bIN->uTail];
}

bool Comport::Recv(void* pvData, size_t sBytes)
{
	static size_t sPos = 0;

	register char* ptData = (char*) pvData;

	while (bIN->uHead != bIN->uTail)
	{
		bIN->uTail = (bIN->uTail + 1) & (BUFF_SIZE - 1);

		ptData[sPos++] = bIN->pcBuff[bIN->uTail];

		if (sPos == sBytes)
		{
			sPos = 0;

			return true;
		}
	}

	return false;
}

bool Comport::Ready(void) const
{
	return (bIN->uHead != bIN->uTail);
}

bool Comport::Wait(unsigned uTime) const
{
	while (bIN->uHead == bIN->uTail);

	return true;
}

ISR(USART_RX_vect)
{
	register char cBuff = UDR0;

	register unsigned short uHead = (bRecv.uHead + 1) & (BUFF_SIZE - 1);

	if (uHead != bRecv.uTail)
	{
		bRecv.uHead = uHead;

		bRecv.pcBuff[uHead] = cBuff;
	}
}

ISR(USART_UDRE_vect)
{
	if (bSend.uHead != bSend.uTail)
	{
		bSend.uTail = (bSend.uTail + 1) & (BUFF_SIZE - 1);

		UDR0 = bSend.pcBuff[bSend.uTail];
	}
	else UCSR0B &= ~(1 << UDRIE0);
}

