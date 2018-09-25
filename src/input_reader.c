/** @file
 * Implementacja funkcji wczytującej jedną operację z inferfejsem w
 * @ref input_reader.h
 *
 * @author Witalis Domitrz <witekdomitrz@gmail.com>
 * @date 27.05.2018
 */

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "operation.h"
#include "input_reader.h"
#include "phone_forward_struct.h"

/**
 * Początkowy rozmiar słów do których są wczytywane parametry operacji
 */
#define PARAM_INITIAL_SIZE 1

/**
 * @brief Sprawdza, czy dana cyfra jest dozwoloną cyfrą numeru telefonu.
 * Sprawdza, czy dana cyfra jest dozwoloną cyfrą numeru telefonu, czyli czy jest
 * z przedziału od @ref FIRST_LETTER do @ref LAST_LETTER.
 * @return Wartość różna od @c 0, jeśli jest to dozwolona cyfra numeru telefonu,
 *         w przeciwnym przypadku 0.
 */
int isNumberDigit(char c) {
    if (FIRST_LETTER <= c && c <= LAST_LETTER)
        return 1;
    return 0;
}

/**
 * @brief Czyta parametr będący numerem.
 * Wczytuje ze standardowego wejścia ciąg znaków składających się na
 * numer do pierwszego wystąpienia innego znaku.
 * @param[in] param – niezaalokowany wskaźnik na miejsce do wczytania parametru;
 * @param[out] param – słowo zawierające wczytany parametr, jeśli wczytanie się
 *                     powiodło, lub niezaalokowany wskaźnik, jeśli wczytanie
 *                     nie powiodło się;
 * @param[in] inputCharacterNumber – wskaźnik na liczbę znaków wczytanych przed
 *                                   rozpoczęciem aktualnej operacji wczytywania;
 * @param[out] inputCharacterNumber – wskaźnik na liczbę znaków wczytanych po
 *                                    zanończeniu aktualnej operacji wczytywania.
 * @return Wartość @ref MEMORY_ERROR jeśli podaczas alokacji pamięci napotkano
 *         błąd, wartość @ref PARSING_ERROR jeśli napotkano błąd wejścia, lub
 *         dowolną inną wartość jeśli udało się wczytać numer.
 */
int readNumber(char **param, int *inputCharacterNumber) {
    char c;
    size_t sizeOfParam, paramFirstFreePlace;

    // Sprawdzenie, czy pierwszy znak się zgadza
    c = (char) getchar();
    (*inputCharacterNumber)++;
    if (!isNumberDigit(c))
        return PARSING_ERROR;

    // Odłożenie pierwszego znaku spowrotem
    ungetc(c, stdin);
    (*inputCharacterNumber)--;

    // Przygotoanie parametru do wczytywania
    sizeOfParam = PARAM_INITIAL_SIZE;
    *param = malloc((sizeOfParam + 1) * sizeof(char));
    if (*param == NULL)
        return MEMORY_ERROR;
    paramFirstFreePlace = 0;

    // Wczytywanie tak długo, jak mamy pasujące znaki
    while (isNumberDigit(c = (char) getchar())) {
        (*inputCharacterNumber)++;

        // Zwiększenie parametru wejścia dwuktornie, jeśli zajdzie taka potrzeba
        if (paramFirstFreePlace == sizeOfParam) {
            sizeOfParam *= 2;
            (*param) = realloc((*param), (sizeOfParam + 1) * sizeof(char));
            if ((*param) == NULL) {
                return MEMORY_ERROR;
            }
        }

        // Ustawienie kolejnego znaku
        (*param)[paramFirstFreePlace++] = c;
    }

    // Ustawienie końca słowa
    (*param)[paramFirstFreePlace] = '\0';

    // Zwrócenie pierwszwego niepoprawnego znaku
    ungetc(c, stdin);

    // Zakończenie sukcesem
    return -1;
}

/**
 * @brief Czyta parametr będący identyfikatorem.
 * Wczytuje ze standardowego wejścia ciąg znaków składających się na
 * identyfikator do pierwszego wystąpienia innego znaku.
 * @param[in] param – niezaalokowany wskaźnik na miejsce do wczytania parametru;
 * @param[out] param – słowo zawierające wczytany parametr, jeśli wczytanie się
 *                     powiodło, lub niezaalokowany wskaźnik, jeśli wczytanie
 *                     nie powiodło się;
 * @param[in] inputCharacterNumber – wskaźnik na liczbę znaków wczytanych przed
 *                                   rozpoczęciem aktualnej operacji wczytywania;
 * @param[out] inputCharacterNumber – wskaźnik na liczbę znaków wczytanych po
 *                                    zanończeniu aktualnej operacji wczytywania.
 * @return Wartość @ref MEMORY_ERROR jeśli podaczas alokacji pamięci napotkano
 *         błąd, wartość @ref PARSING_ERROR jeśli napotkano błąd wejścia, lub
 *         dowolną inną wartość jeśli udało się wczytać numer.
 */
int readIdentifier(char **param, int *inputCharacterNumber) {
    char c;
    size_t sizeOfParam, paramFirstFreePlace;

    c = (char) getchar();
    // Sprawdzenie, czy pierwszy znak się zgadza
    (*inputCharacterNumber)++;
    if (!isalpha(c))
        return PARSING_ERROR;

    // Odłożenie pierwszego znaku spowrotem
    ungetc(c, stdin);
    (*inputCharacterNumber)--;

    // Przygotoanie parametru do wczytywania
    sizeOfParam = PARAM_INITIAL_SIZE;
    *param = malloc((sizeOfParam + 1) * sizeof(char));
    if (*param == NULL)
        return MEMORY_ERROR;
    paramFirstFreePlace = 0;

    // Wczytywanie tak długo, jak mamy pasujące znaki
    while (isalnum(c = (char) getchar())) {
        (*inputCharacterNumber)++;

        // Zwiększenie parametru wejścia dwuktornie, jeśli zajdzie taka potrzeba
        if (paramFirstFreePlace == sizeOfParam) {
            sizeOfParam *= 2;
            (*param) = realloc((*param), (sizeOfParam + 1) * sizeof(char));
            if ((*param) == NULL) {
                return MEMORY_ERROR;
            }
        }

        // Ustawienie kolejnego znaku
        (*param)[paramFirstFreePlace++] = c;
    }

    // Ustawienie końca słowa
    (*param)[paramFirstFreePlace] = '\0';

    // NEW i DEL nie mogą być identyfikatormai
    if (strcmp("NEW", *param) == 0 || strcmp("DEL", *param) == 0) {
        free(*param);
        (*inputCharacterNumber) -= 2;
        return PARSING_ERROR;
    }

    // Zwrócenie pierwszwego niepoprawnego znaku
    ungetc(c, stdin);

    // Zakończenie sukcesem
    return -1;
}

/**
 * @brief Czyta białe znaki i komentarze.
 * Wczytuje ze standardowego wejścia ciąg białych znaków i komentarzy do
 * pierwszego wystąpienia innego znaku, lub końca pliku.
 * @param[in] c – wskaźnik na zaalokowany char;
 * @param[out] c – wskaźnik na ostatni wczytany char;
 * @param[in] inputCharacterNumber – wskaźnik na liczbę znaków wczytanych przed
 *                                   rozpoczęciem aktualnej operacji wczytywania;
 * @param[out] inputCharacterNumber – wskaźnik na liczbę znaków wczytanych po
 *                                    zanończeniu aktualnej operacji wczytywania.
 * @return Wartość @c true jeśli wczytano EOF w czasie wczytywania komentarza,
 *         lub wartość @c false w przeciwnym przypadku.
 */
bool readNotImportatantAndLastIsEOF(char *c, int *inputCharacterNumber) {
    // Wczytuje białe znaki i komentarze
    (*inputCharacterNumber)++;
    while (isspace(*c = (char) getchar()) || *c == '$') {
        // Doliczam kolejny wczytany znak
        (*inputCharacterNumber)++;

        // Jeśli wczytałem biały znak to kontynuuję
        if (*c != '$')
            continue;

        // Sprawdzam, czy własnie rozpoczyna się komentarz
        if ((*c = (char) getchar()) != '$') {

            // Jeśli nie, to odkładam zabrany z wejścia znak spowrotem
            ungetc(*c, stdin);
            (*inputCharacterNumber)--;

            // I ustawiam aktualny znak na znak poprzedni
            *c = '$';

            // I kończę wkonanie
            return false;
        }

        // Jeśli właśnie rozpoczął się komentarz, to doliczam drugi '$'
        (*inputCharacterNumber)++;

        // Do czasu nie znalezienia końca komentarza szukam jego końca
        while (true) {

            // Wczytuję kolejny znak
            *c = (char) getchar();

            // Doliczam kolejny wczytany znak
            (*inputCharacterNumber)++;

            /*
             * Jeśli przedwcześnie napodkałem koniec pliku to zwracam o tym
             * informację.
             */
            if (*c == EOF)
                return true;

            /*
             * Sprawdzam możliwy koniec komentarza
             */
            if (*c == '$') {
                // Wczytuję kolejny znak
                *c = (char) getchar();

                // Doliczam kolejny wczytany znak
                (*inputCharacterNumber)++;

                // Sprawdzam, czy faktycznie napotkałem koniec komentarza
                if (*c == '$')
                    break;
            }
        }
    }

    /*
     * Jeśli zakończyłem wczytywanie poptawnie, to kończę z informacją o braku
     * błędu.
     */
    return false;
}

/**
 * Wczytuje operator @c NEW, albo @c DEL.
 * @param[in] inputCharacterNumber – wskaźnik na liczbę znaków wczytanych przed
 *                                   rozpoczęciem aktualnej operacji wczytywania;
 * @param[out] inputCharacterNumber – wskaźnik na liczbę znaków wczytanych po
 *                                    zanończeniu aktualnej operacji wczytywania.
 * @return Kod wczytanej operacji, lub kod błędu, który wystąpił
 */
int readOperatorNEWorDEL(int *inputCharacterNumber) {
    char operationName[4];
    int c;
    int i;

    // Ustawienie końca słowa
    operationName[3] = '\0';

    // Wczytanie słowa
    for (i = 0; i < 3; i++) {
        (*inputCharacterNumber)++;
        operationName[i] = (char) getchar();

        /*
         * Znaki alfanumeryczne muszą zaczynać operator w tym miejscu, a nie
         * identyfikator.
         */
        if (operationName[i] == EOF) {
            return PARSING_ERROR;
        }
    }


    if ((c = getchar()) == EOF) {
        return EOF_ERROR;
    }

    // Sprawdzam, czy zakończyło się słowo kluczowe NEW/DEL
    if (!isalnum(c)) {
        if (strcmp(operationName, "NEW") == 0) {
            if (c != EOF)
                ungetc(c, stdin);
            return NEW_BASE;
        } else if (strcmp(operationName, "DEL") == 0) {
            if (c != EOF)
                ungetc(c, stdin);
            return DEL_UNKNOWN;
        } else {
            return PARSING_ERROR;
        }
    }
    return PARSING_ERROR;
}

bool inputReaderReadNextOperation(struct Operation *operation,
                                  int *inputCharacterNumber) {
    char c;
    char *firstParam, *secondParam;
    bool operatorRead;

    // Inicjalizacja wartości
    firstParam = NULL;
    secondParam = NULL;
    operatorRead = false;


    /*
     * Wczytanie białych znaków i komentarzy i sprawdzenie przypadku końca pliku
     * w czasie wczytywania komentarza.
     */
    if (readNotImportatantAndLastIsEOF(&c, inputCharacterNumber)) {
        operation->typeOfOperation = EOF_ERROR;
        return true;
    }

    // Sprawdzenie przypadku końca pliku
    if (c == EOF)
        return false;

    // Ustawienie ostatniego aktywnego znaku
    operation->firstSignNumber = (*inputCharacterNumber);

    // Próba wczytania operatora
    if (c == '?') {
        strcpy(operation->operationName, "?");
        operatorRead = true;
        operation->typeOfOperation = REV;
    } else if (c == '@') {
        strcpy(operation->operationName, "@");
        operatorRead = true;
        operation->typeOfOperation = NTRIV;
    } else if (c == 'N' || c == 'D') {
        ungetc(c, stdin);
        operation->firstSignNumber = (*inputCharacterNumber);
        (*inputCharacterNumber)--;

        // Próga wczytania operatora
        operation->typeOfOperation = readOperatorNEWorDEL(inputCharacterNumber);

        if (operation->typeOfOperation == NEW_BASE) {

            // Jeśli wczytano operator NEW
            strcpy(operation->operationName, "NEW");
            operatorRead = true;

        } else if (operation->typeOfOperation == DEL_UNKNOWN) {

            // Jeśli wczytano operator DEL
            strcpy(operation->operationName, "DEL");
            operatorRead = true;

        } else {
            // Jeśli wystąpił błąd
            return true;
        }

    } else {
        (*inputCharacterNumber)--;
        ungetc(c, stdin);
    }

    // Wczytanie białych znaków i komentarzy i sprawdzenie przypadku końca pliku
    if (readNotImportatantAndLastIsEOF(&c, inputCharacterNumber) || c == EOF) {
        operation->typeOfOperation = EOF_ERROR;
        return true;
    }

    // Jeśli operator to DEL, to sprawdzenie czy jest to DEL, czy DEL_BASE
    if (operation->typeOfOperation == DEL_UNKNOWN) {
        if (isNumberDigit(c)) {
            operation->typeOfOperation = DEL;
        } else {
            operation->typeOfOperation = DEL_BASE;
        }
    }

    // Sprawdzam, czy możeliwe jest, żeby wejście było dalej poprawne
    if (!isNumberDigit(c) && !isalnum(c)) {
        operation->typeOfOperation = PARSING_ERROR;
        operation->firstSignNumber = (*inputCharacterNumber);
        return true;
    }

    // Zwracam pierwszy znak na wejście
    (*inputCharacterNumber)--;
    ungetc(c, stdin);

    // Wczytuję pierwszy argument
    if (!operatorRead || operation->typeOfOperation == REV ||
        operation->typeOfOperation == DEL ||
        operation->typeOfOperation == NTRIV) {
        // Jeśli argument powinien być numerem
        switch (readNumber(&firstParam, inputCharacterNumber)) {
            case MEMORY_ERROR:
                operation->typeOfOperation = MEMORY_ERROR;
                return true;

            case PARSING_ERROR:
                operation->typeOfOperation = PARSING_ERROR;
                operation->firstSignNumber = (*inputCharacterNumber);
                return true;

            default:
                // Wczytanie się powiodło
                break;
        }
    } else {
        // Jeśli argument powinien być identyfikatorem
        switch (readIdentifier(&firstParam, inputCharacterNumber)) {
            case MEMORY_ERROR:
                operation->typeOfOperation = MEMORY_ERROR;
                return true;

            case PARSING_ERROR:
                operation->typeOfOperation = PARSING_ERROR;
                operation->firstSignNumber = (*inputCharacterNumber);
                return true;

            default:
                // Wczytanie się powiodło
                break;
        }
    }

    // Ustawiam pierwszy argument operacji
    operation->firstParameter = firstParam;

    // Wszystkie operatry prefiksowe mają dokładnie jeden argument
    if (operatorRead) {
        return true;
    }

    // Wczytanie białych znaków i komentarzy i sprawdzenie przypadku końca pliku
    if (readNotImportatantAndLastIsEOF(&c, inputCharacterNumber) || c == EOF) {
        operation->typeOfOperation = EOF_ERROR;
        return true;
    }

    // Ustawienie ostatniego aktywnego znaku
    operation->firstSignNumber = (*inputCharacterNumber);

    /*
     * Operacja nie została jeszcze wczytana, więc jest jedną z dwóch możliwych
     * operacji postfixowych
     */
    if (c == '?') {

        // Jeśli jest to GET, to ma już wszystkie możliwe argumenty
        strcpy(operation->operationName, "?");
        operation->typeOfOperation = GET;
        return true;
    } else if (c == '>') {
        strcpy(operation->operationName, ">");
        // Jeśli jest to ADD, to będzie potrzeba jeszcze jednego argumentu
        operation->typeOfOperation = ADD;
    } else {

        // Jeśli nie jest to ani GET, ani ADD, to jest to niepoprawne wejście
        operation->typeOfOperation = PARSING_ERROR;
        return true;
    }

    // Wczytanie drugiego argumentu do ADD-a

    // Wczytanie białych znaków i komentarzy i sprawdzenie przypadku końca pliku
    if (readNotImportatantAndLastIsEOF(&c, inputCharacterNumber) || c == EOF) {
        operation->typeOfOperation = EOF_ERROR;
        return true;
    }

    // Zwracam pierwszy znak na wejście
    (*inputCharacterNumber)--;
    ungetc(c, stdin);

    switch (readNumber(&secondParam, inputCharacterNumber)) {
        case MEMORY_ERROR:
            operation->typeOfOperation = MEMORY_ERROR;
            return true;

        case PARSING_ERROR:
            operation->typeOfOperation = PARSING_ERROR;
            operation->firstSignNumber = (*inputCharacterNumber);
            return true;

        default:
            // Wczytanie się powiodło
            break;
    }

    operation->secondParameter = secondParam;

    return true;
}