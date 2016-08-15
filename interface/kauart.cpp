#include "kauart.hpp"

volatile KAUart::Buffer	RecvBuff 		= { 0, 0 };
volatile KAUart::Buffer*	KAUart::IN	= &RecvBuff;

KAUart::KAUart(BAUD Biterate)
: Current(0)
{
	unsigned Baud = F_CPU / (8 * Biterate) - 1;

	cli();

	UCSR0B = 0;

	UCSR0A = 0b00000010;
	UCSR0C = 0b00000110;

	UBRR0H = Baud >> 8;
	UBRR0L = Baud & 0xFF;

	sei();
}

KAUart::~KAUart(void)
{
	Stop();

	UCSR0A = 0;
	UCSR0C = 0;

	UBRR0H = 0;
	UBRR0L = 0;
}

void KAUart::Start(void)
{
	UCSR0B = 0b10011000;
}

void KAUart::Stop(void)
{
	while (!(UCSR0A & (1 << UDRE0)));

	UCSR0B = 0;

	IN->Head = IN->Tail;
}

void KAUart::Send(char Char)
{
	while (!(UCSR0A & (1 << UDRE0))); UDR0 = Char;
}

void KAUart::Send(const char* String)
{
	while (*String) Send(*String++);
}

void KAUart::Send(const void* Data, size_t Size)
{
	register const char* String = (char*) Data;

	while (Size--) Send(*String++);
}

char KAUart::Recv(void)
{
    while (IN->Head == IN->Tail);

    IN->Tail = (IN->Tail + 1) & (BUFF_SIZE - 1);

    return IN->Data[IN->Tail];
}

bool KAUart::Recv(void* Data, size_t Size)
{
	register char* ptData = (char*) Data;

	while (IN->Head != IN->Tail)
	{
		IN->Tail = (IN->Tail + 1) & (BUFF_SIZE - 1);

		ptData[Current++] = IN->Data[IN->Tail];

		if (Current == Size)
		{
			Current = 0;

			return true;
		}
	}

	return false;
}

bool KAUart::Ready(void) const
{
	return (IN->Head != IN->Tail);
}

bool KAUart::Wait(void) const
{
	while (!Ready()); return true;
}

void KAUart::SendPgmChar(unsigned Adress)
{
	Send(__LPM(Adress));
}

void KAUart::SendPgmString(unsigned Adress)
{
	while (char c = __LPM(Adress++)) Send(c);
}

void KAUart::SendPgmData(unsigned Adress, size_t Size)
{
	while (Size--) Send(__LPM(Adress++));
}

KAUart& KAUart::operator << (unsigned Unsigned)
{
	char Buff[16];

	itoa(Unsigned, Buff, 10);

	Send(Buff);

	return *this;
}

KAUart& KAUart::operator << (double Number)
{
	char Buff[32];

	dtostrf(Number, 0, 5, Buff);

	Send(Buff);

	return *this;
}

KAUart& KAUart::operator << (int Integer)
{
	char Buff[16];

	itoa(Integer, Buff, 10);

	Send(Buff);

	return *this;
}

KAUart& KAUart::operator << (bool Bool)
{
	Send(Bool ? "true" : "false");

	return *this;
}

KAUart& KAUart::operator << (char Char)
{
	Send(Char);

	return *this;
}

KAUart& KAUart::operator << (const char* String)
{
	Send(String);

	return *this;
}

KAUart& KAUart::operator << (const void* Adress)
{
	SendPgmString((unsigned) Adress);

	return *this;
}

KAUart& KAUart::operator >> (char& Char)
{
	Char = Recv();

	return *this;
}

ISR(USART_RX_vect)
{
	register char Buff = UDR0;

	register unsigned char Head = (RecvBuff.Head + 1) & (BUFF_SIZE - 1);

	RecvBuff.Head = Head;
	RecvBuff.Data[Head] = Buff;
}
