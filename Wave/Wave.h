/***********************************************************************

    Klasa Wave biblioteki AVR KuszkAPI v1.0
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

/*! \file Wave.h
 *  \brief Zawiera deklaracje klasy Wave.
 *
 * Deklaracja zamieszczona w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 *  \file Wave.cpp
 *  \brief Zawiera implementacje klasy Wave.
 *
 * Implementacja każdej klasy w innym pliku pomaga uniknąć chaosu w organizacji kodu.
 *
 */

#include <Arduino.h>

/*! \brief Obsługa generowania impulsów z modulacją wypełnienia.
 *  \note Klasa działa także z innymi płytkami, nie tylko z Arduino.
 *  \warning Częstotliwość jest nastawiana wspólnie dla wszystkich generatorów.
 *
 * Klasa umożliwia automatyczne utworzenie generatora sygnału prostokątnego o podanym wypełnieniu i częstotliwości.
 *
 */
class Wave
{

	/*! \brief Enumeracja dostępnych generatorów.
	 *
	 * Określa numer generatora z którego chcemy skorzystać.
	 *
	 */
	public: enum WAVE
	{
		W1	=	11,	//!< Pierwszy generator - pin 11.
		W2	=	3	//!< Drugi generator - pin 3.
	};

	/*! \brief Enumeracja dostępnych częstotliwości.
	 *
	 * Określa częstotliwość przebiegu z której korzystamy.
	 *
	 */
	public: enum FREQ
	{
		OFF,			//!< Zerowa częstotliwość - brak generacji.
		F62500,		//!< Częstotliwość 62500 Hz.
		F31400,		//!< Częstotliwość 31373 Hz.
		F7800,		//!< Częstotliwość 7812,5 Hz.
		F4000,		//!< Częstotliwość 3921,6 Hz.
		F2000,		//!< Częstotliwość 1953,1 Hz.
		F1000,		//!< Częstotliwość 980,39 Hz.
		F500,		//!< Częstotliwość 490,20 Hz.
		F250,		//!< Częstotliwość 245,10 Hz.
		F120,		//!< Częstotliwość 122,55 Hz.
		F60,			//!< Częstotliwość 61,035 Hz.
		F30			//!< Częstotliwość 30,637 Hz.
	};

	protected:

		static unsigned char uScale;	//!< Aktualnie używany prescaler wybrany na podstwie trybu pracy i częstotliwości.
		static unsigned char uMode;	//!< Określa tryb pracy generatorów na podstawie wybranej częstotliwości.

		const WAVE eWave;			//!< Stały indeks używanego generatora.

		unsigned char uCount;		//!< Liczba impulsów do zliczenia.

	public:

		/*! \brief Konstruktor obiektu.
		 *  \param [in] eNumber Określna numer użytego generatora.
		 *  \warning Nie dokonuję się sprawdzania czy wybrany generator jest w użyciu. Należy zatem pamiętać by nie dublować generatorów.
		 *
		 * Inicjuje wszystkie pola obiektu na zero.
		 *
		 */
		Wave(WAVE eNumber);

		/*! \brief Destruktor obiektu.
		 *
		 * Zatrzymuje bierzący generator, nie zeruje jednak jego stanu.
		 *
		 */
		~Wave(void);

		/*! \brief Aktywuje generator.
		 *  \return Powodzenie operacji.
		 *
		 * Sprawdza poprawność danych i aktywuje generator. Gdy operacja powiedzie się zwraca wartość true, w przeciwnym wypadku zwraca false.
		 *
		 */
		bool Start(void);

		/*! \brief Wyłącza generator.
		 *
		 * Wyłącza aktywny generator bez resetowania ustawień. Aby wznowić działanie generatora bez potrzeby obliczania parametrów i ustalania flag użyj metody Resume().
		 *
		 */
		void Stop(void);

		/*! \brief Wznawia generator.
		 *
		 * Przywraca pracę wybranego generatora bez potrzeby obliczania na nowo jego parametrów.
		 *
		 */
		void Resume(void);

		/*! \brief Aktywuje nowe ustawienia.
		 *  \return Powodzenie operacji.
		 *  \see SetFreq(), SetWidth().
		 *
		 * Wprowadza w życie nowe ustawienia generatora.
		 *
		 */
		bool Refresh(void);

		/*! \brief Sprawdza czy generator jest aktywny.
		 *  \return Stan generatora.
		 *
		 * Sprawdza czy dany generator jest aktywny. Zwraca true gdy czasomierz działa, lub false gdy jest wyłączony.
		 *
		 */
		bool Active(void) const;

		/*! \brief Ustawia generator.
		 *  \param [in] uWidth Wypełnienie przebiegu (od 0 do 255)..
		 *
		 * Ustala wypełnienie generowanego przebiegu. Nie zmienia jednak aktualnej pracy generatora - aby tego dokonać wywołaj ponownie metodę Start() lub Refresh().
		 *
		 */
		void SetWidth(unsigned char uWidth);

		/*! \brief Ustawia generator.
		 *  \param [in] eFreq Częstotliwość przebiegu w hercach (Hz).
		 *  \see FREQ.
		 *
		 * Ustala odpowiednie parametry generatorów potrzebne do aktywowania ich na podstawie podanej częstotliwości. Nie zmienia jednak aktualnej pracy generatora - aby tego dokonać wywołaj ponownie metodę Start() lub Refresh().
		 *
		 */
		static void SetFreq(FREQ eFreq);

};
