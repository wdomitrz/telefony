/** @file
 * Implementacja operacji na liście słów z interfejsem w pliku
 * @ref string_list.h
 *
 * @author Witalis Domitrz <witekdomitrz@gmail.com>
 * @date 13.05.2018
 */

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "string_list.h"

void stringListDestroy(struct StringList const *stringList) {
	if (stringList == NULL)
		return;
	free((void *) stringList->val);
	stringListDestroy(stringList->next);
	free((void *) stringList);
}

/**
 * @brief Tworzy element listy
 * Tworzy element listy będący poprzednikiem @p next i z wartością @p val
 * @param next – wskaźnik na następnik nowotworzonego elementu;
 * @param val – wskaźnik na wartość nowotworzonego elementu.
 * @return Zwraca wskaźnik na nowoutworzony element, lub @c NULL gdy nie
 *         udało się zaalokować pamięci.
 */
struct StringList *stringListElemCreate(struct StringList *next,
                                        char const *val) {
	struct StringList *newCharListList;

	// Alokacja nowej struktury
	newCharListList = malloc(sizeof(struct StringList));
	if (newCharListList == NULL)
		return NULL;

	// Ustawienie parametrów
	newCharListList->val = val;
	newCharListList->next = next;

	// Zwrócenie nowej struktury
	return newCharListList;
}

struct StringList *stringListCreate(void) {
	// Pusty ciąg to wskaźnik na pierwszy element, który jest NULL-em
	return stringListElemCreate(NULL, NULL);
}

bool stringListAdd(struct StringList *stringList, char const *toAdd) {
	struct StringList *helper;
	int comparision;
	if (stringList == NULL)
		return false;

	// Znalezienie miejsca na nowy element
	comparision = 1;
	while (stringList->next != NULL &&
	        (comparision = strcmp(toAdd, stringList->next->val)) > 0) {
		stringList = stringList->next;
	}

	// Taki element już istnieje
	if (stringList->next != NULL && comparision == 0) {
		free((void *) toAdd);
		return true;
	}

	// Stworzenie nowego elementu
	helper = stringListElemCreate(stringList->next, toAdd);
	if (helper == NULL)
		return false;

	// Dodanie nowego elementu do listy
	stringList->next = helper;
	return true;
}

size_t stringListSize(struct StringList const *stringList) {
	size_t size = 0;

	// Sprawdzenie poprawności wejścia
	if (stringList == NULL)
		return 0;

	// Znalezienie długości
	while (stringList->next != NULL) {
		size++;
		stringList = stringList->next;
	}

	// Zwrócenie długości
	return size;
}

char const *const *stringListToStringsAndDestroy(struct StringList *stringList) {
	size_t size, i;
	char const **outList;
	struct StringList *helper;

	// Sprawdzenie poprawności wejścia
	if (stringList == NULL)
		return NULL;

	// Znalezienie rozmiaru listy
	size = stringListSize(stringList);

	// Zaalokowanie listy
	outList = malloc(size * sizeof(char *));
	if (outList == NULL)
		return NULL;

	// Zwolnienie zerowego elementu listy
	helper = stringList;
	stringList = stringList->next;
	free(helper);

	// Przepisanie listy ze zwalnianiem jej
	i = 0;
	while (stringList != NULL) {
		// Przepisanie elementu
		outList[i++] = stringList->val;

		// Zwolnienie aktualnego elementu i skok do kolejnego
		helper = stringList;
		stringList = stringList->next;
		free(helper);
	}
	return outList;
}