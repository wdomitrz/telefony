/** @file
 * Implementacja podstawowych operacji na strukturze @c PhoneForward z
 * interfejsem w pliku @ref phone_forward_struct.h
 *
 * @author Witalis Domitrz <witekdomitrz@gmail.com>
 * @date 13.05.2018
 */

#include <stdlib.h>
#include "phone_forward_struct.h"

// Deklaracja tej funkcji znajduje się w pliku "phone_forward_list.c"
struct PhoneForwardList *phoneForwardListCreate(void);

// Deklaracja tej funkcji znajduje się w pliku "phone_forward_list.c"
void phoneForwardListDestroy(struct PhoneForwardList *phoneForwardList);

/**
 * @brief Tworzy wierchołek drzewa.
 * Tworzy wierchołek drzewa z podanym znakiem @p nodeChar, głębokością @p depth
 * i ojcem @p prev.
 * @param nodeChar – znak, który zostanie znakiem tego wierzchołka;
 * @param depth – głębokość, którą będzie miał zapisany ten wierzchołek;
 * @param prev – wskaźnik na ojca, który będzie miał zapisany ten wierchołek.
 * @return Wskaźnik na utworzoną strukturę lub @c NULL, gdy nie udało się
 *         zaalokować pamięci.
 */
struct PhoneForward *phoneForwardCreateNode(char nodeChar, int depth,
                                            struct PhoneForward *prev) {
    size_t i;
    struct PhoneForward *newPhoneForward;

    // Zaalkowanie nowej struktury.
    newPhoneForward = malloc(sizeof(struct PhoneForward));
    if (newPhoneForward == NULL)
        return NULL;

    // Utworzenie listy zawartej w tej strukturze
    newPhoneForward->revert = phoneForwardListCreate();
    if (newPhoneForward->revert == NULL) {
        free(newPhoneForward);
        return NULL;
    }

    // Ustawienie parametrów
    newPhoneForward->depth = depth;
    newPhoneForward->nodeChar = nodeChar;
    newPhoneForward->prev = prev;
    newPhoneForward->forwardTo = NULL;
    for (i = 0; i < SIZE_OF_ALPHABET; i++) {
        newPhoneForward->nextLetter[i] = NULL;
    }

    // Zwrócenie nowej struktury
    return newPhoneForward;
}

struct PhoneForward *phoneForwardCreate(void) {
    // Pusta struktura, to reprezentujący drzewo korzeń.
    return phoneForwardCreateNode('\0', 0, NULL);
}

void phoneForwardDestroy(struct PhoneForward *phoneForward) {
    size_t i;
    // Sprawdzenie poprawności danych wejściowych
    if (phoneForward == NULL)
        return;

    // Zniszczenie synów wierzchołka
    for (i = 0; i < SIZE_OF_ALPHABET; i++) {
        phoneForwardDestroy(phoneForward->nextLetter[i]);
    }

    // Zniszczenie listy przechowywanej przez wierchołek i danego wierzchołka
    phoneForwardListDestroy(phoneForward->revert);
    free((void *) phoneForward);
}

struct PhoneForward *phoneForwardFromString(struct PhoneForward *phoneForward,
                                            char const *num) {
    // Sprawdzenie poprawności danych wejściowcyh
    if (num == NULL) {
        return NULL;
    } // Sprawdzenie, czy doszliśmy do końca słowa
    else if (num[0] == '\0') {

        return phoneForward;

    } // Sprawdzenie, czy aktualnie rozpatrywana litera jest dozwolona
    else if (num[0] >= FIRST_LETTER && num[0] <= LAST_LETTER) {
        /*
         * Sprawdzenie, czy istnieje kolejny porzebny wierzchołek i utworzenie
         * go jeśli nie istnieje.
         */
        if (phoneForward->nextLetter[num[0] - FIRST_LETTER] == NULL) {
            phoneForward->nextLetter[num[0] - FIRST_LETTER] =
                    phoneForwardCreateNode(num[0], phoneForward->depth + 1,
                                           phoneForward);
            if (phoneForward->nextLetter[num[0] - FIRST_LETTER] == NULL)
                return NULL;
        }
        //Przejście dalej w słowie
        return phoneForwardFromString(
                phoneForward->nextLetter[num[0] - FIRST_LETTER], num + 1);
    } else {
        // Przypadek niepoprawnego znaku w słowie
        return NULL;
    }
}

char *phoneForwardToString(struct PhoneForward *begin1,
                           struct PhoneForward *end1,
                           struct PhoneForward *begin2,
                           struct PhoneForward *end2) {
    size_t size1, size2;
    char *outString;

    // Sprawdzenie, czy słowa mają nieujemne długości
    if (end1->depth - begin1->depth < 0 || end2->depth - begin2->depth < 0)
        return NULL;

    // Ustawienie długości słów
    size1 = (size_t) (end1->depth - begin1->depth);
    size2 = (size_t) (end2->depth - begin2->depth);

    // Zaalokowanie miejsca na wyjściowe słowo
    outString = malloc((size1 + size2 + 1) * sizeof(char));
    if (outString == NULL)
        return NULL;

    // Ustawienie ostatniejgo znaku słowa
    outString[size1 + size2] = '\0';

    // Zapisanie drugiej części słowa
    while (size2) {
        outString[--size2 + size1] = end2->nodeChar;
        end2 = end2->prev;
    }

    // Zapisanie pierwszej części słowa
    while (size1) {
        outString[--size1] = end1->nodeChar;
        end1 = end1->prev;
    }
    return outString;
}