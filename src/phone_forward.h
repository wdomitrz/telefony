/** @file
 * Interfejs klasy przechowującej przekierowania numerów telefonicznych
 *
 * @author Marcin Peczarski <marpe@mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 09.04.2018
 */

#ifndef __PHONE_FORWARD_H__
#define __PHONE_FORWARD_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

/**
 * Struktura przechowująca przekierowania numerów telefonów.
 */
struct PhoneForward;

/**
 * Struktura przechowująca ciąg numerów telefonów.
 */
struct PhoneNumbers;

/** @brief Tworzy nową strukturę.
 * Tworzy nową strukturę niezawierającą żadnych przekierowań.
 * @return Wskaźnik na utworzoną strukturę lub @c NULL, gdy nie udało się
 *         zaalokować pamięci.
 */
struct PhoneForward *phfwdNew(void);

/** @brief Usuwa strukturę.
 * Usuwa strukturę wskazywaną przez @p pf. Nic nie robi, jeśli wskaźnik ten ma
 * wartość @c NULL.
 * @param[in] pf – wskaźnik na usuwaną strukturę;
 * @param[out] pf – wskaźnik na niezaalokowane miejsce w pamięci.
 */
void phfwdDelete(struct PhoneForward *pf);

/** @brief Dodaje przekierowanie.
 * Dodaje przekierowanie wszystkich numerów mających prefiks @p num1, na numery,
 * w których ten prefiks zamieniono odpowiednio na prefiks @p num2. Każdy numer
 * jest swoim własnym prefiksem. Jeśli wcześniej zostało dodane przekierowanie
 * z takim samym parametrem @p num1, to jest ono zastępowane.
 * @param[in] pf – wskaźnik na strukturę przechowującą przekierowania numerów;
 * @param[out] pf – wskaźnik na tą samą strukturę po wykonaniu na niej opisanej
 *                  w @ref phfwdAdd operacji;
 * @param[in, out] num1 – wskaźnik na napis reprezentujący prefiks numerów
 *                        przekierowywanych;
 * @param[in, out] num2 – wskaźnik na napis reprezentujący prefiks numerów, na 
 *                        które jest wykonywane przekierowanie.
 * @return Wartość @c true, jeśli przekierowanie zostało dodane.
 *         Wartość @c false, jeśli wystąpił błąd, np. podany napis nie
 *         reprezentuje numeru, oba podane numery są identyczne lub nie udało
 *         się zaalokować pamięci.
 */
bool phfwdAdd(struct PhoneForward *pf, char const *num1, char const *num2);

/** @brief Usuwa przekierowania.
 * Usuwa wszystkie przekierowania, w których parametr @p num jest prefiksem
 * parametru @p num1 użytego przy dodawaniu. Jeśli nie ma takich przekierowań
 * lub napis nie reprezentuje numeru, nic nie robi.
 *
 * @param[in] pf  – wskaźnik na strukturę przechowującą przekierowania numerów;
 * @param[out] pf – wskaźnik na tą samą strukturę po wykonaniu na niej opisanej
 *                  w @ref phfwdRemove operacji;
 * @param[in, out] num – wskaźnik na napis reprezentujący prefiks numerów.
 */
void phfwdRemove(struct PhoneForward *pf, char const *num);

/** @brief Wyznacza przekierowanie numeru.
 * Wyznacza przekierowanie podanego numeru. Szuka najdłuższego pasującego
 * prefiksu. Wynikiem jest co najwyżej jeden numer. Jeśli dany numer nie został
 * przekierowany, to wynikiem jest ten numer. Jeśli podany napis nie
 * reprezentuje numeru, wynikiem jest pusty ciąg. Alokuje strukturę
 * @p PhoneNumbers, która musi być zwolniona za pomocą funkcji @ref phnumDelete.
 * @param[in] pf  – wskaźnik na strukturę przechowującą przekierowania numerów;
 * @param[out] pf – wskaźnik na tą samą strukturę po wykonaniu na niej opisanej
 *                  w @ref phfwdGet operacji;
 * @param[in, out] num – wskaźnik na napis reprezentujący numer.
 * @return Wskaźnik na strukturę przechowującą ciąg numerów lub @c NULL, gdy
 *         nie udało się zaalokować pamięci.
 */
struct PhoneNumbers const *phfwdGet(struct PhoneForward *pf, char const *num);

/** @brief Wyznacza przekierowania na dany numer.
 * Wyznacza wszystkie przekierowania na podany numer. Wynikowy ciąg zawiera też
 * dany numer. Wynikowe numery są posortowane leksykograficznie i nie mogą się
 * powtarzać. Jeśli podany napis nie reprezentuje numeru, wynikiem jest pusty
 * ciąg. Alokuje strukturę @c PhoneNumbers, która musi być zwolniona za pomocą
 * funkcji @ref phnumDelete.
 * @param[in] pf  – wskaźnik na strukturę przechowującą przekierowania numerów;
 * @param[out] pf – wskaźnik na tą samą strukturę po wykonaniu na niej opisanej
 *                  w @ref phfwdReverse operacji;
 * @param[in, out] num – wskaźnik na napis reprezentujący numer.
 * @return Wskaźnik na strukturę przechowującą ciąg numerów lub @c NULL, gdy nie
 *         udało się zaalokować pamięci.
 */
struct PhoneNumbers const *phfwdReverse(struct PhoneForward *pf, char const *num);

/** @brief Usuwa strukturę.
 * Usuwa strukturę wskazywaną przez @p pnum. Nic nie robi, jeśli wskaźnik ten ma
 * wartość @c NULL.
 * @param[in] pnum – wskaźnik na usuwaną strukturę;
 * @param[out] pnum – wskaźnik na niezaalokowane miejsce w pamięci.
 */
void phnumDelete(struct PhoneNumbers const *pnum);

/** @brief Udostępnia numer.
 * Udostępnia wskaźnik na napis reprezentujący numer. Napisy są indeksowane
 * kolejno od zera.
 * @param[in] pnum – wskaźnik na strukturę przechowującą ciąg napisów;
 * @param[out] pnum – wskaźnik na tą samą, niezmienioną strukturę;
 * @param idx  – indeks napisu.
 * @return Wskaźnik na napis. Wartość @c NULL, jeśli wskaźnik @p pnum ma wartość
 *         @c NULL lub indeks ma za dużą wartość.
 */
char const *phnumGet(struct PhoneNumbers const *pnum, size_t idx);

/** @brief Funkcja oblicza liczbę nietrywialnych numerów.
 * Funkcja oblicza liczbę nietrywialnych numerów długości len zawierających
 * tylko cyfry, które znajdują się w napisie set. Obliczenia wykonuje modulo
 * @c 2 do potęgi liczba bitów reprezentacji typu @c size_t. Napis @p set może
 * zawierać dowolne znaki.
 * @param[in] pf  – wskaźnik na strukturę przechowującą przekierowania numerów;
 * @param[out] pf – wskaźnik na tą samą strukturę;
 * @param set – wskaźnik na napis;
 * @param len – długość zliczanych numerów telefonów.
 * @return Wartość @c 0, jeśli wskaźnik @p pf ma wartość @c NULL, @p set ma
 *         wartość @c NULL @p set jest pusty, @p set nie zawiera żadnej cyfry
 *         lub parametr @p len jest równy zeru.
 *         W przeciwnym przypadku szukaną liczbę modulo @c 2 do potęgi liczba
 *         bitów reprezentacji typu @c size_t.
 */
size_t phfwdNonTrivialCount(struct PhoneForward *pf, char const *set, size_t len);

#endif /* __PHONE_FORWARD_H__ */