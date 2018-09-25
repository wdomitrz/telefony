/** @file
 * Interfejsem klasy przechowującej bazy przekierowań numerów telefonicznych z
 * implementacją w @ref dictionary.c
 *
 * @author Witalis Domitrz <witekdomitrz@gmail.com>
 * @date 27.05.2018
 */

#ifndef TELEFONY_DICTIONARY_H
#define TELEFONY_DICTIONARY_H

#include "phone_forward.h"
#include <stdbool.h>

/**
 * @brief Struktura przechowująca bazy numerów telefonów.
 * Słownik indeksowany identyfikatorami przechowywujący bazy numerów telefonów.
 */
struct Dictionary;

/** @brief Tworzy nową strukturę.
 * Tworzy nową strukturę niezawierającą żadnych baz numerów telefonów.
 * @return Wskaźnik na utworzoną strukturę lub @c NULL, gdy nie udało się
 *         zaalokować pamięci.
 */
struct Dictionary *dictionaryCreate(void);

/** @brief Usuwa strukturę.
 * Usuwa strukturę wskazywaną przez @p dictionary. Nic nie robi, jeśli wskaźnik
 * ten ma wartość @c NULL.
 * @param[in] dictionary – wskaźnik na usuwaną strukturę;
 * @param[out] dictionary – wskaźnik na niezaalokowane miejsce w pamięci.
 */
void dictionaryDestroy(struct Dictionary *dictionary);

/** @brief Udostępnia bazę numerów telefonów.
 * Udostępnia wskaźnik na bazę numerów telefonów odpowiadającemu danemu
 * identyfikatorowi. Jeśli żadna baza nie ma odpowiadającego jej identyfikatora,
 * to tworzy nową bazę, dodaje ją do słownika i zwraca wskaźnik na nią.
 * @param dictionary – wskaźnik na strukturę dłownika;
 * @param identifier – identyfikator oczekiwanej bazy.
 * @return Wskaźnik na bazę. Wartość @c NULL, jeśli wskaźnik @p pnum ma wartość
 *         @c NULL lub nie udało się stworzyć nowej bazy odpowiadającej
 *         identyfikatorowi.
 */
struct PhoneForward *dictionaryGet(struct Dictionary *dictionary,
                                   char const *identifier);

/** @brief Usuwa bazę numerów telefonów.
 * Usuwa bazę numerów telefonów ze słownika niszcząc ją i usuwając o niej wpis.
 * @param dictionary – wskaźnik na strukturę dłownika;
 * @param identifier – wskaźnik na identyfikator bazy do usunięcia;
 * @param[in] phoneForward – wskaźnik na wskaźnik do aktualnej bazy danych;
 * @param[out] phoneForward – jeśli usuwana baza jest inną niż aktualna, to to,
 *                            co na wejściu, w przeciwnym przyadku @c NULL.
 * @return Wartość @c true, jeśli istniała taka baza, lub wartość @c false,
 *         jeśli nie istniała taka baza.
 */
bool dictionaryRemove(struct Dictionary *dictionary, char const *identifier,
                      struct PhoneForward **phoneForward);

#endif //TELEFONY_DICTIONARY_H

