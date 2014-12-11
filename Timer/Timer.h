/***********************************************************************

    Klasa Timer biblioteki AVR KuszkAPI v1.0
    Copyright (C) 2014 Łukasz "Kuszki" Dróżdż

    Niniejszy program jest wolnym oprogramowaniem; możesz go
    rozprowadzać dalej i/lub modyfikować na warunkach Powszechnej
    Licencji Publicznej GNU, wydanej przez Fundację Wolnego
    Oprogramowania - według wersji 2-giej tej Licencji lub którejś
    z późniejszych wersji.

    Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
    użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
    gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
    ZASTOSOWAŃ. W celu uzyskania bliższych informacji - Powszechna
    Licencja Publiczna GNU.

    Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
    Powszechnej Licencji Publicznej GNU (GNU General Public License);
    jeśli nie - napisz do Free Software Foundation, Inc., 675 Mass Ave,
    Cambridge, MA 02139, USA.

***********************************************************************/

/*! \file Timer.h
 *  \brief Zawiera deklaracje klasy Switch.
 *
 * Deklaracja zamieszczona w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 *  \file Timer.cpp
 *  \brief Zawiera implementacje klasy Switch.
 *
 * Implementacja każdej klasy w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 */

#include <Arduino.h>

/*! \brief Obsługa przerwań licznika czasu.
 *  \note Przerwanie wybranego timera należy zaimplementować ręcznie.
 *  \note Klasa działa także z innymi płytkami, nie tylko z Arduino.
 *
 * Klasa umożliwia automatyczne utworzenie przerwania wywoływanego z określoną częstotliowścią lub określonym czasem.
 *
 */ class Timer
{

	/*! \brief Enumeracja dostępnych liczników.
	 *
	 * Określa numer licznika z którego chcemy skorzystać.
	 *
	 */ public: enum TIMER
	{
		T1,	//!< Pierwszy licznik - zakres od 0 do 255.
		T2,	//!< Drugi licznik - zakres od 0 do 65535.
		T3	//!< Trzeci licznik - zakres od 0 do 255.
	};

	protected:

		const TIMER eTimer;	//!< Stały indeks używanego licznika.

		unsigned uScale;	//!< Aktualnie używany prescaler.
		unsigned uCount;	//!< Liczba impulsów do zliczenia.
		unsigned uPrev;	//!< Impulsy do pierwszego zdarzenia.

	public:

		/*! \brief Konstruktor obiektu.
		 *  \param [in] eNumber Określna numer użytego licznika.
		 *  \warning Nie dokonuję się sprawdzania czy wybrany licznik jest w użyciu. Należy zatem pamiętać by nie dublować liczników.
		 *
		 * Inicjuje wszystkie pola obiektu na zero.
		 *
		 */ Timer(TIMER eNumber);

		/*! \brief Destruktor obiektu.
		 *
		 * Zatrzymuje bierzący licznik, nie zeruje jednak jego stanu.
		 *
		 */ ~Timer(void);

		/*! \brief Aktywuje licznik.
		 *  \return Powodzenie operacji.
		 *
		 * Sprawdza poprawność danych i aktywuje licznik. Gdy operacja powiedzie się zwraca wartość true, w przeciwnym wypadku zwraca false.
		 *
		 */ bool Start(void);

		/*! \brief Wyłącza licznik.
		 *
		 * Wyłącza aktywny licznik bez resetowania jego pozycji. Aby wznowić działanie licznika bez potrzeby obliczania parametrów i ustalania flag użyj metody Resume().
		 *
		 */ void Stop(void);

		/*! \brief Wznawia licznik.
		 *
		 * Przywraca pracę wybranego licznika bez potrzeby obliczania na nowo jego parametrów.
		 *
		 */ void Resume(void);

		/*! \brief Sprawdza czy licznik jest aktywny.
		 *  \return Stan licznika.
		 *
		 * Sprawdza czy dany licznik jest aktywny. Zwraca true gdy czasomierz działa, lub false gdy jest wyłączony.
		 *
		 */ bool Active(void) const;

		/*! \brief Ustawia licznik.
		 *  \param [in] uFreq	Częstotliwość wyzwalania.
		 *  \param [in] uProc	Chwila pierwszego zdarzenia wyrażona w kątach (0 - 360).
		 *  \note Jeśli chcesz nastawić częstotliwość poniżej 1Hz możesz użyć funkcji SetTime().
		 *
		 * Ustala odpowiednie parametry licznika potrzebne do aktywowania go na podstawie podanej częstotliwości wyzwalania zdarzenia. Nie zmienia jednak aktualnej pracy licznika - aby tego dokonać wywołaj ponownie metodę Start().
		 *
		 */ void SetFreq(unsigned long uFreq, unsigned short uProc = 0);

		/*! \brief Ustawia licznik.
		 *  \param [in] uTime	Okres wyzwalania w mikrosekundach (us).
		 *  \param [in] uProc	Chwila pierwszego zdarzenia wyrażona w kątach (0 - 360).
		 *
		 * Ustala odpowiednie parametry licznika potrzebne do aktywowania go na podstawie podanego czasu oczekiwania. Nie zmienia jednak aktualnej pracy licznika - aby tego dokonać wywołaj ponownie metodę Start().
		 *
		 */ void SetTime(unsigned long uTime, unsigned short uProc = 0);

		/*! \brief Ustawia licznik.
		 *  \param [in] uDiv	Wybrany prescaler.
		 *  \param [in] uCap	Wybrana pojemność zdarzenia.
		 *  \param [in] uPre	Pojemność pierwszego zdarzenia.
		 *  \warning Istotne jest by parametry były zgodne ze specyfikacją licznika. Nie będą one bowiem sprawdzane pod kątem poprawności szerokości licznika.
		 *
		 * Ustala ręcznie odpowiednie parametry licznika potrzebne do aktywowania go. Nie zmienia jednak aktualnej pracy licznika - aby tego dokonać wywołaj ponownie metodę Start().
		 *
		 */ void SetPrefs(unsigned uDiv, unsigned uCap, unsigned uPre = 0);

};
