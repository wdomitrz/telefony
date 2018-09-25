/** @file
 * Implementacja operacji na strukturze @c PhoneNumbers z interfejsem w
 * pliku @ref string_list.h
 *
 * @author Witalis Domitrz <witekdomitrz@gmail.com>
 * @date 13.05.2018
 */

#include <stdlib.h>
#include "phone_numbers.h"

struct PhoneNumbers *phoneNumbersCreate(char const *const *sequence,
                                        size_t size) {
    struct PhoneNumbers *newPhoneNumbers;
    size_t i;

    // Stworzenie nowej struktury
    newPhoneNumbers = malloc(sizeof(struct PhoneNumbers));
    if (newPhoneNumbers == NULL) {
        // Zwolnienie ciągu w przypadku błędu alokacji
        for (i = 0; i < size; i++) {
            free((void *) sequence[i]);
        }
        free((void *) sequence);
        return NULL;
    }

    // Ustawienie parametrów
    newPhoneNumbers->sequence = sequence;
    newPhoneNumbers->size = size;

    // Zwrócenie nowaj struktury
    return newPhoneNumbers;
}

struct PhoneNumbers *phoneNumbersCreateEmpty() {
    // Pusty ciąg to ciąg o zerowej długości ze wskaźnikiem na NULL.
    return phoneNumbersCreate(NULL, 0);
}

void phoneNumbersDelete(struct PhoneNumbers const *phoneNumbers) {
    size_t i;

    // Sprawdzenie poprawności wejścia
    if (phoneNumbers == NULL)
        return;

    // Zwolnienie wszystkich słów
    for (i = 0; i < phoneNumbers->size; i++) {
        free((void *) phoneNumbers->sequence[i]);
    }

    // Zwolnienie tablicy słów i struktury
    free((void *) phoneNumbers->sequence);
    free((void *) phoneNumbers);
}

char const *phoneNumbersGet(struct PhoneNumbers const *phoneNumbers,
                            size_t idx) {
    // Sprawdzenie poprawności wejścia
    if (phoneNumbers == NULL)
        return NULL;

    // Sprawdzenie poprawności indeksu
    if (idx >= phoneNumbers->size)
        return NULL;

    // Zwrócenie wartości w danym miejscu
    return phoneNumbers->sequence[idx];
}

