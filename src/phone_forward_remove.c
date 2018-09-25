/** @file
 * Implementacja operacji usuwania przekierowania z interfejsem w pliku
 * @ref phone_forward_remove.h
 *
 * @author Witalis Domitrz <witekdomitrz@gmail.com>
 * @date 13.05.2018
 */

#include <stdlib.h>
#include "phone_forward_remove.h"
#include "phone_forward_struct.h"
#include "phone_forward_list.h"

/**
 * @brief Usuwa przekierowania w drzewie
 * Usuwa wszystkie przekierowania w danym drzewie.
 * @param[in] phoneForward – drzewo do usunięcia przekierowań;
 * @param[out] phoneForward – drzewo z usuniętymi przekierowaniami.
 */
void phoneForwardCleanAll(struct PhoneForward *phoneForward) {
	size_t i;
	// Jeśli w danym wierzchołku istnieje przekierowanie, to je usuwamy
	if (phoneForward->forwardTo != NULL) {
		phoneForwardListRemove(phoneForward->forwardTo->revert, phoneForward);
		phoneForward->forwardTo = NULL;
	}

	// Iterujemy się po synach i w nich też usuwamy przekierowania
	for (i = 0; i < SIZE_OF_ALPHABET; i++)
		if (phoneForward->nextLetter[i] != NULL)
			phoneForwardCleanAll(phoneForward->nextLetter[i]);
}

void phoneForwardRemove(struct PhoneForward *phoneForward, char const *number) {
	struct PhoneForward *numberNode;
	// Sprawdzenie poprawności wejścia
	if (phoneForward == NULL)
		return;

	// Znalezienie wierzchołka reprezentującego dany numer
	numberNode = phoneForwardFromString(phoneForward, number);

	// Sprawdzenie poprawności numeru
	if (numberNode == NULL || numberNode == phoneForward)
		return;

	// Wyczyszczenie przekierowań
	phoneForwardCleanAll(numberNode);
}