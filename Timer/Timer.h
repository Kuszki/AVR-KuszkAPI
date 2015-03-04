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
 *  \brief Zawiera deklaracje klasy Timer.
 *
 * Deklaracja zamieszczona w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 *  \file Timer.cpp
 *  \brief Zawiera implementacje klasy Timer.
 *
 * Implementacja każdej klasy w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 */

#ifndef _AVR_KUSZKAPI_TIMER_H
#define _AVR_KUSZKAPI_TIMER_H

#include <Arduino.h>

/*! \brief Obsługa przerwań licznika czasu.
 *  \note Przerwanie wybranego timera należy zaimplementować ręcznie.
 *  \note Klasa działa także z innymi płytkami, nie tylko z Arduino.
 *  \bug Po aktywacji licznika metodą Start() zdarza się, że pierwsze wyzwolenie nastąpi w nieokreślonym czasie. Takie działanie ma miejsce gdy ręcznie załączymy zliczanie w trakcie programu. Timer aktywowany na początku programu działa zwykle poprawnie. Bug dotyczy tylko pierwszego wyzwolenia. Zdarzenie odnotowano tylko dla licznika T2 - dla pozostałych liczników nie przeprowadzono testów.
 *
 * Klasa umożliwia automatyczne utworzenie przerwania wywoływanego z określoną częstotliowścią lub określonym czasem.
 *
 * Aby obsłużyć główne zdarzenie zdefiniuj w programie przerwanie TIMERX_COMPA_vect, gdzie X to numer licznika (0, 1 lub 2). W celu obsłurzenie przerwania pomocniczego adefiniuj przerwanie TIMERX_COMPB_vect.
 *
 */
class Timer
{

	/*! \brief Enumeracja dostępnych liczników.
	 *
	 * Określa numer licznika z którego chcemy skorzystać.
	 *
	 */
	public: enum TIMER
	{
		T1,	//!< Pierwszy licznik - zakres od 0 do 255.
		T2	//!< Drugi licznik - zakres od 0 do 65535.
	};

	/*! \brief Enumeracja dostępnych prescalerów.
	 *
	 * Określa prescaler z którego korzystamy.
	 *
	 */
	public: enum SCALER
	{
		OFF,		//!< Zerowy prescaler - brak zliczania.
		P1,		//!< Prescaler 1/1.
		P8,		//!< Prescaler 1/8.
		P64,		//!< Prescaler 1/64.
		P256,	//!< Prescaler 1/265.
		P1024	//!< Prescaler 1/1024.
	};

	protected:

		const TIMER ID;		//!< Stały indeks używanego licznika.

		unsigned char uScale;	//!< Aktualnie używany prescaler.

		unsigned uCount;		//!< Liczba impulsów do zliczenia.
		unsigned uPrev;		//!< Impulsy do pierwszego zdarzenia.

	public:

		/*! \brief Konstruktor obiektu.
		 *  \param [in] eNumber Określna numer użytego licznika.
		 *  \warning Nie dokonuję się sprawdzania czy wybrany licznik jest w użyciu. Należy zatem pamiętać by nie dublować liczników.
		 *
		 * Inicjuje wszystkie pola obiektu na zero.
		 *
		 */
		Timer(TIMER eNumber);

		/*! \brief Destruktor obiektu.
		 *
		 * Zatrzymuje bierzący licznik, nie zeruje jednak jego stanu.
		 *
		 */
		~Timer(void);

		/*! \brief Aktywuje licznik.
		 *  \return Powodzenie operacji.
		 *
		 * Sprawdza poprawność danych i aktywuje licznik. Gdy operacja powiedzie się zwraca wartość true, w przeciwnym wypadku zwraca false.
		 *
		 */
		bool Start(void);

		/*! \brief Wyłącza licznik.
		 *
		 * Wyłącza aktywny licznik bez resetowania jego pozycji. Aby wznowić działanie licznika bez potrzeby obliczania parametrów i ustalania flag użyj metody Resume().
		 *
		 */
		void Stop(void);

		/*! \brief Zeruje licznik i restartuje pomiar.
		 *
		 * Powoduje, że cykl zliczania zaczyna się od nowa.
		 *
		 */
		void Reset(void);

		/*! \brief Wznawia licznik.
		 *
		 * Przywraca pracę wybranego licznika bez potrzeby obliczania na nowo jego parametrów.
		 *
		 */
		void Resume(void);

		/*! \brief Aktywuje nowe ustawienia.
		 *  \return Powodzenie operacji.
		 *  \see SetFreq(), SetTime(), SetPrefs().
		 *
		 * Wprowadza w życie nowe ustawienia licznika.
		 *
		 */
		bool Refresh(void);

		/*! \brief Sprawdza czy licznik jest aktywny.
		 *  \return Stan licznika.
		 *
		 * Sprawdza czy dany licznik jest aktywny. Zwraca true gdy czasomierz działa, lub false gdy jest wyłączony.
		 *
		 */
		bool Active(void) const;

		/*! \brief Ustawia licznik.
		 *  \param [in] uFreqA	Częstotliwość wyzwalania w hercach (Hz).
		 *  \param [in] uFreqB	Częstotliwość wyzwalania pomocniczego zdarzenia w hercach (Hz).
		 *  \note Jeśli chcesz nastawić częstotliwość poniżej 1Hz możesz użyć funkcji SetTime().
		 *
		 * Ustala odpowiednie parametry licznika potrzebne do aktywowania go na podstawie podanej częstotliwości wyzwalania zdarzenia. Nie zmienia jednak aktualnej pracy licznika - aby tego dokonać wywołaj ponownie metodę Start() lub Refresh().
		 *
		 */
		void SetFreq(unsigned long uFreqA, unsigned long uFreqB = 0);

		/*! \brief Ustawia licznik.
		 *  \param [in] uTimeA	Okres wyzwalania zdarzenia w mikrosekundach (us).
		 *  \param [in] uTimeB	Okres wyzwalania pomocniczego zdarzenia w mikrosekundach (us) - musi być większy od okresu pierwszego wydarzenia.
		 *
		 * Ustala odpowiednie parametry licznika potrzebne do aktywowania go na podstawie podanego czasu. Nie zmienia jednak aktualnej pracy licznika - aby tego dokonać wywołaj ponownie metodę Start() lub Refresh().
		 *
		 */
		void SetTime(unsigned long uTimeA, unsigned long uTimeB = 0);

		/*! \brief Ustawia licznik.
		 *  \param [in] eScale	Wybrany prescaler.
		 *  \param [in] uCapA	Wybrana pojemność zdarzenia.
		 *  \param [in] uCapB	Pojemność pierwszego zdarzenia.
		 *  \see SCALER.
		 *  \warning Istotne jest by parametry były zgodne ze specyfikacją licznika. Nie będą one bowiem sprawdzane pod kątem poprawności szerokości licznika.
		 *
		 * Ustala ręcznie odpowiednie parametry licznika potrzebne do aktywowania go. Nie zmienia jednak aktualnej pracy licznika - aby tego dokonać wywołaj ponownie metodę Start().
		 *
		 */
		void SetPrefs(SCALER eScale, unsigned uCapA, unsigned uCapB = 0);

};

#endif
