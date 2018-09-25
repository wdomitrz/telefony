/** @file
 * Implementacja funkcji z interfejsu zawartego w @ref phone_forward.h
 *
 * @author Witalis Domitrz <witekdomitrz@gmail.com>
 * @date 13.05.2018
 */

#include <stdbool.h>
#include "phone_forward.h"
#include "phone_numbers.h"
#include "phone_forward_struct.h"
#include "phone_forward_add.h"
#include "phone_forward_get.h"
#include "phone_forward_remove.h"
#include "phone_forward_reverse.h"
#include "phone_forward_non_trivial_count.h"

struct PhoneForward *phfwdNew(void) {
    return phoneForwardCreate();
}

void phfwdDelete(struct PhoneForward *pf) {
    return phoneForwardDestroy(pf);
}

bool phfwdAdd(struct PhoneForward *pf, char const *num1, char const *num2) {
    return phoneForwardAdd(pf, num1, num2);
}

void phfwdRemove(struct PhoneForward *pf, char const *num) {
    return phoneForwardRemove(pf, num);
}

struct PhoneNumbers const *phfwdGet(struct PhoneForward *pf, char const *num) {
    return phoneForwardGet(pf, num);
}

struct PhoneNumbers const *phfwdReverse(struct PhoneForward *pf, char const *num) {
    return phoneForwardReverse(pf, num);
}

void phnumDelete(struct PhoneNumbers const *pnum) {
    return phoneNumbersDelete(pnum);
}

char const *phnumGet(struct PhoneNumbers const *pnum, size_t idx) {
    return phoneNumbersGet(pnum, idx);
}

size_t phfwdNonTrivialCount(struct PhoneForward *pf, char const *set, size_t len) {
    return phoneForwardNonTrivialCount(pf, set, len);
}
