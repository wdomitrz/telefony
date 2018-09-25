/** @file
 * Interfejs operacji i deklaracja struktury @c PhoneNumbers z implementacją w
 * pliku @ref string_list.c
 *
 * @author Witalis Domitrz <witekdomitrz@gmail.com>
 * @date 13.05.2018
 */

#ifndef TEL_PHONE_NUMBERS_H
#define TEL_PHONE_NUMBERS_H

#include <stdlib.h>

/**
 * @brief Struktura przechowująca ciąg numerów telefonów.
 * Struktura przechowująca ciąg numerów telefonów reprezentowany przez swoją
 * długość oraz tablicę jego elementów w postaci napisów.
 */
struct PhoneNumbers {
    /**@{*/

    size_t size;
    /**<
     * Liczba numerów w ciągu
     */

    char const *const *sequence;
    /**<
     * Ciąg numerów reprezentowanych jako napisy
     */

    /**@}*/
};

/**
 * @brief Tworzy nową stukturę.
 * Tworzy nową stukturę @c PhoneNumbers na podstawie podanego ciągu i jego
 * długości.
 * @param sequence – ciąg do zapisania w strukturze
 * @param size – długość ciągu do zapisania w strukturze
 * @return Wskaźnik na nowoutworzoną strukturę, lub @c NULL, gdy nie udało się
 *         zaalokować pamięci.
 */
struct PhoneNumbers *phoneNumbersCreate(char const *const *sequence,
                                        size_t size);

/**
 * @brief Tworzy nową stukturę.
 * Tworzy nową stukturę @c PhoneNumbers reprezentującą pusty ciąg.
 * @return Wskaźnik na nowoutworzoną strukturę, lub @c NULL, gdy nie udało się
 *         zaalokować pamięci.
 */
struct PhoneNumbers *phoneNumbersCreateEmpty();

/**
 * @brief Usuwa strukturę.
 * Działa jak @ref phnumDelete.
 * Usuwa strukturę wskazywaną przez @p phoneNumbers. Nic nie robi, jeśli
 * wskaźnik ten ma wartość @c NULL.
 * @param[in] phoneNumbers – wskaźnik na usuwaną strukturę.
 * @param[out] phoneNumbers – wskaźnik na niezaalokowane miejsce w pamięci.
 */
void phoneNumbersDelete(struct PhoneNumbers const *phoneNumbers);

/**
 * @brief Udostępnia numer.
 * Działa jak @ref phnumGet.
 * Udostępnia wskaźnik na napis reprezentujący numer. Napisy są indeksowane
 * kolejno od zera.
 * @param[in, out] phoneNumbers – wskaźnik na strukturę przechowującą ciąg 
                                  napisów;
 * @param idx  – indeks napisu.
 * @return Wskaźnik na napis. Wartość @c NULL, jeśli wskaźnik @p phoneNumbers
 *         ma wartość @c NULL lub indeks ma za dużą wartość.
 */
char const *phoneNumbersGet(struct PhoneNumbers const *phoneNumbers, size_t idx);

#endif //TEL_PHONE_NUMBERS_H
