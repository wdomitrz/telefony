/** @file
 * Implementacja operacji na liście wskaźników na struktury @c PhoneForward
 * stworzonych w pliku @ref phone_forward_struct.h z interfejscem w pliku
 * @ref phone_forward_list.h
 *
 * @author Witalis Domitrz <witekdomitrz@gmail.com>
 * @date 13.05.2018
 */

#include <stdlib.h>
#include <stdbool.h>
#include "phone_forward_list.h"
#include "phone_forward_struct.h"

/**
 * @brief Tworzy element listy
 * Tworzy element listy będący poprzednikiem @p next i z wartością @p val
 * @param[in, out] next – wskaźnik na następnik nowotworzonego elementu;
 * @param[in, out] val – wskaźnik na wartość nowotworzonego elementu.
 * @return Zwraca wskaźnik na nowoutworzony element, lub @c NULL gdy nie
 *         udało się zaalokować pamięci.
 */
struct PhoneForwardList *phoneForwardListElemCreate(
        struct PhoneForwardList *next, struct PhoneForward *val) {
    struct PhoneForwardList *newPhoneForwardList;

    // Alokacja nowej struktury
    newPhoneForwardList = malloc(sizeof(struct PhoneForwardList));
    if (newPhoneForwardList == NULL)
        return NULL;

    // Ustawienie wartości
    newPhoneForwardList->val = val;
    newPhoneForwardList->next = next;

    // Zwrócenie nowej struktury
    return newPhoneForwardList;
}

struct PhoneForwardList *phoneForwardListCreate(void) {
    // Lista pusta to wskaźnik na pierwszy element, który jest NULL-em
    return phoneForwardListElemCreate(NULL, NULL);
}

void phoneForwardListDestroy(struct PhoneForwardList *phoneForwardList) {
    // Sprawdzenie, czy nie jesteśmy już na końcu
    if (phoneForwardList == NULL)
        return;

    // Zwolnienie kolejnego elementu
    phoneForwardListDestroy(phoneForwardList->next);

    // Zwolnienie aktualnego elemntu
    free(phoneForwardList);
}

bool phoneForwardListAdd(struct PhoneForwardList *phoneForwardList,
                         struct PhoneForward *phoneForward) {
    struct PhoneForwardList *currentElem;

    // Sprawdzenie poprawności wejścia
    if (phoneForward == NULL || phoneForwardList == NULL)
        return false;

    // Utworzenie nowego elementu
    currentElem = phoneForwardListElemCreate(phoneForwardList->next,
                                             phoneForward);
    if (currentElem == NULL)
        return false;

    // Dodanie nowego elementu do listy
    phoneForwardList->next = currentElem;
    return true;
}

void phoneForwardListRemove(struct PhoneForwardList *phoneForwardList,
                            struct PhoneForward const *phoneForward) {
    struct PhoneForwardList *currentElem, *helper;

    // Sprawdzenie poprawności wejścia
    if (phoneForward == NULL || phoneForwardList == NULL)
        return;

    // Przeiterowanie się po liście w celu znalezienie elementu o danej wartości
    currentElem = phoneForwardList;
    while (currentElem->next != NULL) {
        if (currentElem->next->val == phoneForward) {
            // Usunięcie znalezionego elementu
            helper = currentElem->next;
            currentElem->next = helper->next;
            helper->next = NULL;
            phoneForwardListDestroy(helper);
            return;
        }
        currentElem = currentElem->next;
    }
}

bool phoneForwardListIsEmpty(struct PhoneForwardList *phoneForwardList) {
    return phoneForwardList->next == NULL;
}