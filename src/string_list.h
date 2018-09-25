/** @file
 * Interfejs operacji i deklaracja listy słów z implementacją w pliku
 * @ref string_list.c
 *
 * @author Witalis Domitrz <witekdomitrz@gmail.com>
 * @date 13.05.2018
 */

#ifndef TELEFONY_CHAR_LIST_LIST_H
#define TELEFONY_CHAR_LIST_LIST_H

#include <stdbool.h>

/**
 * Struktura przechowująca posortowany alfabetycznie ciąg słów niezawierający
 * powtórzeń.
 */
struct StringList {
    /**@{*/

    char const *val;
    /**<
     * Wartość w danym elemencie
     */

    struct StringList *next;
    /**<
     * Wskaźnik na następny element
     */

    /**@}*/
};

/**
 * @brief Usuwa strukturę.
 * Usuwa strukturę wskazywaną przez @p stringList. Nic nie robi, jeśli wskaźnik
 * ten ma wartość @c NULL.
 * @param[in] stringList – wskaźnik na usuwaną strukturę;
 * @param[out] stringList – wskaźnik na niezaalokowane miejsce w pamięci.
 */
void stringListDestroy(struct StringList const *stringList);

/**
 * @brief Tworzy nową listę.
 * Tworzy nową, pustą listę posortowanych alfabetycznie słów.
 * @return Wskaźnik na nowoutworzoną listę lub @c NULL, gdy nie uwało się
 *         zaalokować pamięci.
 */
struct StringList *stringListCreate(void);

/**
 * @brief Dodaje wartość do listy
 * Dodaje nowy element do listy @p stringList z podaną wartością @p toAdd
 * zachowując jej uporządkowanie jeśli takie element jeszcze nie istnieje. Jeśli
 * taki element istnieje, to nic nie robi.
 * @param[in] stringList – lista do której ma zostać dodany element;
 * @param[out] stringList – lista do której został dodany element jeśli
 *                          wcześniej go nie było i udało się zaalokować pamięć;
 * @param[in, out] toAdd – wartość elementu do dodania.
 * @return Wartość @c true jeśli dodawanie się powiodło, lub nie trzeba było
 *         dodawać.
 *         Wartość @c false jeśli dodawanie się nie powiodło (np. z podou błędu
 *         alokacji pamięci)
 */
bool stringListAdd(struct StringList *stringList, char const *toAdd);

/**
 * @brief Zwraca rozmiar lisy.
 * Dla danej listy @p stringList zwraca jej rozmiar.
 * @param stringList – wskaźnik na listę.
 * @return Długość listy, lub @c 0, jeśli wskaźnik na listę to @c NULL.
 */
size_t stringListSize(struct StringList const *stringList);

/**
 * @brief Zamienia listę na tablicę i usuwa lisę.
 * Tworzy tablicę zawierającą elementy danej listy i usuwa listę @p stringList.
 * @param[in] stringList – wskaźnik na lisę do przerobienia;
 * @param[out] stringList – wskaźnik na niezaalokowane miejsce w pamięci.
 * @return Wskaźnik na nowoutworzoną tablicę lub @c NULL jeśli podany wskaźnik
 *         to @c NULL, lub nie udało się zaalokować pamięci.
 */
char const *const *stringListToStringsAndDestroy(struct StringList *stringList);

#endif //TELEFONY_CHAR_LIST_LIST_H
