/** @file
 * Interfejs operacji i deklaracja listy wskaźników na struktury @c PhoneForward
 * zadeklarowanych w pliku @ref phone_forward_struct.h z implementacją w pliku
 * @ref phone_forward_list.c
 *
 * @author Witalis Domitrz <witekdomitrz@gmail.com>
 * @date 13.05.2018
 */

#ifndef TEL_PHONE_FORWARD_LIST_H
#define TEL_PHONE_FORWARD_LIST_H

#include <stdbool.h>
#include "phone_forward_struct.h"

/**
 * @brief Lista wskaźników na struktury @c PhoneForward
 * Jednokierunkowa lista z elementami będącymi wskaźnikami na struktury
 * @c PhoneForward.
 */
struct PhoneForwardList {
    /**@{*/

    struct PhoneForward *val;
    /**<
     * Wartość elementu listy.
     */

    struct PhoneForwardList *next;
    /**<
     * Wskaźnik na następny element listy.
     */

    /**@}*/
};

/**
 * @brief Tworzy pustą listę
 * Tworzy strukturę będącą reprezentacją pustej listy
 * @return Wskaźnik na nowoutworzoną listę, lub @c NULL gdy nie udało się
 *         zaalokować pamięci
 */
struct PhoneForwardList *phoneForwardListCreate(void);

/**
 * @brief Niszczy listę
 * Zwalnia listę @p phoneForwardList, ale nie zwalnia jej elementów - te
 * elementy muszą zosać zwolnione oddzielnie.
 * @param[in] phoneForwardList – wskaźnik na listę do zwolnienia;
 * @param[out] phoneForwardList – niezaalokowany wskaźnik.
 */
void phoneForwardListDestroy(struct PhoneForwardList *phoneForwardList);

/**
 * @brief Dodaje element do listy
 * Dodaje element o wartości @p phoneForward różnej od @c NULL do listy
 * @p phoneForwardList na jej początek.
 * @param[in] phoneForwardList – wskaźnik na listę do której ma zostać dopisany
 *                               nowy element o wartości @p phoneForward;
 * @param[out] phoneForwardList – wskaźnik na listę do której został dopiany
 *                                nowy element o wartości @p phoneForward jeśli
 *                                dodawanie się powiodło, lub listę wejściową,
 *                                jeśli dodawanie się nie powiodło.
 * @param[in, out] phoneForward – Wskaźnik na wartość elementu do dopisania.
 * @return Wartość @c true, jeśli dodawanie się powiodło.
 *         Wartość @c false, jeśli dodawnia się nie powiodło (np. z powodu
 *         błędu alokacji pamięci, wskaźnik @p phoneForwardList to
 *         @c NULL, albo wskaźnik @p phoneForward to @c NULL).
 */
bool phoneForwardListAdd(struct PhoneForwardList *phoneForwardList,
                         struct PhoneForward *phoneForward);

/**
 * @brief Usuwa element z listy
 * Usuwa element o wartości @p phoneForward różnej od @c NULL z listy, jeśli
 * istnieje on w tej liście. W przeciwnym przypadku nic nie robi.
 * @param[in] phoneForwardList – wskaźnik na listę z której ma zostać usunięty
 *                               element @p phoneForward;
 * @param[out] phoneForwardList – wskaźnik na listę z której został usunięty
 *                                element o wartości @p phoneForward jeśli
 *                                usuwanie się powiodło, lub listę wejściową,
 *                                jeśli nie było takiego elementu.
 * @param[in, out] phoneForward – Wskaźnik na wartość elementu do usunięcia.
 */
void phoneForwardListRemove(struct PhoneForwardList *phoneForwardList,
                            struct PhoneForward const *phoneForward);

/**
 * @brief Sprawdza, czy lista jest pusta.
 * Sprawdza, czy podana lista jest pusta.
 * @param[in] phoneForwardList – wskaźnik na listę do sprawdzenia pustości;
 * @param[out] phoneForwardList – wskaźnik na tą samą listę.
 * @return Wartość @c true, jeśli @p phoneForwardList jest wskaźnikiem na
 *         pustą listę. W przeciwnym przypadku wartość @c false.
 */
bool phoneForwardListIsEmpty(struct PhoneForwardList *phoneForwardList);

#endif //TEL_PHONE_FORWARD_LIST_H
