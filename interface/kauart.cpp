#include "kauart.hpp"

volatile KAUart::Buffer RecvBuff 		= {0, 0};
volatile KAUart::Buffer SendBuff 		= {0, 0};

volatile KAUart::Buffer* KAUart::IN	= &RecvBuff;
volatile KAUart::Buffer* KAUart::OUT	= &SendBuff;

static const char TRUE_STR[]		 	= "true";
static const char FALSE_STR[] 		= "flase";

KAUart::KAUart(unsigned Biterate)
: Current(0)
{
	Biterate = (F_CPU / 8 / Biterate - 1) / 2;

	UCSR0A = 0;
	UCSR0C = 6;

	UBRR0H = Biterate >> 8;
	UBRR0L = Biterate;

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
	UCSR0B = 152;
}

void KAUart::Stop(void)
{
	while (OUT->Head != OUT->Tail);

	UCSR0B = 0;

	IN->Head = IN->Tail;
}

void KAUart::Send(char Char)
{
	register unsigned short Head = (OUT->Head + 1) & (BUFF_SIZE - 1);

	while (Head == OUT->Tail);

	OUT->Data[Head] = Char;
	OUT->Head = Head;

	UCSR0B |= (1 << UDRE0);
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

bool KAUart::Wait(unsigned Time) const
{
	while (IN->Head == IN->Tail);

	return true;
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

	register unsigned short Head = (RecvBuff.Head + 1) & (BUFF_SIZE - 1);

	if (Head != RecvBuff.Tail)
	{
		RecvBuff.Head = Head;

		RecvBuff.Data[Head] = Buff;
	}
}

ISR(USART_UDRE_vect)
{
	if (SendBuff.Head != SendBuff.Tail)
	{
		SendBuff.Tail = (SendBuff.Tail + 1) & (BUFF_SIZE - 1);

		UDR0 = SendBuff.Data[SendBuff.Tail];
	}
	else UCSR0B &= ~(1 << UDRIE0);
}
