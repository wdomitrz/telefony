/** @file
 * Deklaracja klasy przechowującej bazy przekierowań numerów telefonicznych i
 * implementacja metod tej klasy z interfejsem w @ref dictionary.h
 *
 * @author Witalis Domitrz <witekdomitrz@gmail.com>
 * @date 27.05.2018
 */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "phone_forward.h"
#include "dictionary.h"

/**
 * Domyślna wartość hasha dla słowa pustego
 */
#define HASH_DEFAULT 1

/**
 * Podstawa systemu pozycyjnego do hashowania
 */
#define HASH_BASE 41

/**
 * Modulo do hashowania
 */
#define HASH_MOD 999999937

/**
 * Słownik reprezentuję jako listę par (klucz, wartość)
 */
struct Dictionary {
    /**@{*/

    unsigned long hash;
    /**<
     * Hash identyfikatora w danym polu
     */

    char const *identifier;
    /**<
     * Identyfikator w danym polu
     */

    struct PhoneForward *val;
    /**<
     * Baza numerów telefonów w danym polu
     */

    struct Dictionary *next;
    /**<
     * Następny element listy
     */

    /**@}*/
};

/**
 * Hashuje podane słowo.
 * @param identifier – słowo do shashowania.
 * @return Hash podanego słowa, lub @c 0 jeśli to słowo to @c NULL.
 */
unsigned long dictionaryHash(char const *identifier) {
    unsigned long hash;
    size_t i;

    // Sprawdzam NULL-a
    if (identifier == NULL) {
        return 0;
    }

    // Ustawiam wartości początkowe
    hash = HASH_DEFAULT;
    i = 0;

    // Przechodzę po słowie
    while (identifier[i] != '\0') {
        hash *= HASH_BASE;

        // Dodaję kolejną cyfrę do hasha
        if (isdigit(identifier[i])) {
            hash += identifier[i] - '0';
        } else if ('A' <= identifier[i] && identifier[i] <= 'Z') {
            hash += identifier[i] - 'A' + 10;
        } else if ('a' <= identifier[i] && identifier[i] <= 'z') {
            hash += identifier[i] - 'a' + 10 + 26;
        }
        hash %= HASH_MOD;
        i++;
    }
    return hash;
}

/**
 * Tworzy nowy element listy.
 * @param hash – hash identyfikatora elementu do dodania
 * @param identifier – identyfikator nowego elementu listy;
 * @param val – wskaźnik na bazę do umieszczenia w danym miejscu
 * @param next – wskaźnik na następny element listy.
 * @return Wskaźnik na nowoutworzony element listy, lub @c NULL, jeśli nie udało
 *         się zaalokować pamięci.
 */
struct Dictionary *dictionatyCreateElem(unsigned long hash,
                                        char const *identifier,
                                        struct PhoneForward *val,
                                        struct Dictionary *next) {
    struct Dictionary *newDictionary;

    // Zaalokowanie nowej struktury
    newDictionary = malloc(sizeof(struct Dictionary));
    if (newDictionary == NULL)
        return NULL;

    // Ustawienie wartości
    newDictionary->hash = hash;
    newDictionary->identifier = identifier;
    newDictionary->val = val;
    newDictionary->next = next;

    // Zwrócenie nowej struktury
    return newDictionary;
}

struct Dictionary *dictionaryCreate() {

    // Pusty słownik jest reprezentowany przez pustą listę
    return dictionatyCreateElem(0, NULL, NULL, NULL);
}

void dictionaryDestroy(struct Dictionary *dictionary) {
    if (dictionary == NULL)
        return;

    // Zniszczenie następnego elementu
    dictionaryDestroy(dictionary->next);

    // Zwolnienie wartości w aktualnym elemencie
    free((void *) dictionary->identifier);
    phfwdDelete(dictionary->val);

    // Zwolnienie aktulnego elementu
    free(dictionary);
}

struct PhoneForward *dictionaryGet(struct Dictionary *dictionary,
                                   char const *identifier) {
    struct Dictionary *currentElem;
    char *newIdentifier;
    struct PhoneForward *newBase;
    unsigned long hash;

    hash = dictionaryHash(identifier);

    // Sprawdzenie, czy element o danym identyfikatrze już istnieje
    currentElem = dictionary->next;
    while (currentElem != NULL) {

        // Porównuję hashe, żeby było szybciej
        if (hash == currentElem->hash &&
            strcmp(identifier, currentElem->identifier) == 0) {
            // Zwrócenie elementu z pasującym identyfikatorem
            return currentElem->val;
        }
        currentElem = currentElem->next;
    }

    // Stworzenie kopii identyfikatora
    newIdentifier = malloc((strlen(identifier) + 1) * sizeof(char));
    strcpy(newIdentifier, identifier);
    if (newIdentifier == NULL)
        return NULL;

    // Stworzenie nowej bazy danych
    newBase = phfwdNew();
    if (newBase == NULL) {
        free(newIdentifier);
        return NULL;
    }

    // Stworzenie nowego elementu listy
    currentElem =
            dictionatyCreateElem(hash, newIdentifier, newBase, dictionary->next);
    if (currentElem == NULL) {
        free(newIdentifier);
        phfwdDelete(newBase);
        return NULL;
    }

    // Dodanie nowego elementu do listy
    dictionary->next = currentElem;

    // Zwróecnie nowego elementu
    return currentElem->val;
}

bool dictionaryRemove(struct Dictionary *dictionary, char const *identifier,
                      struct PhoneForward **phoneForward) {
    struct Dictionary *currentElem;
    unsigned long hash;

    hash = dictionaryHash(identifier);

    // Przeszukanie bazy
    while (dictionary->next != NULL) {

        // Porównuję najpierw hashe, żeby było szybciej
        if (hash == dictionary->next->hash &&
            strcmp(identifier, dictionary->next->identifier) == 0) {
            // Usunięcie elementu, jeśli został znaleziony
            currentElem = dictionary->next;
            dictionary->next = currentElem->next;
            currentElem->next = NULL;
            if (currentElem->val == *phoneForward)
                *phoneForward = NULL;
            dictionaryDestroy(currentElem);
            return true;
        }

        // Sprawdzenie kolejnego elementu
        dictionary = dictionary->next;
    }

    // W przypadku nieznalezienia elementu zwrócenie stosownej informacji
    return false;
}
