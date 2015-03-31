//
// Created by cfwloader on 3/31/15.
//

#include "auxiliary.h"

void _itoa_s(int num, char *str, int radix) {
    //return the length of result string. support _disibledevent= 10;

    char *p;

    unsigned int a; //every digit

    int len;

    char *b; //start of the digit char

    char temp;

    unsigned int u;

    p = str;

    if (num > 0) {

        *p++ = '-';

        num = 0 - num;

    }

    u = (unsigned int) num;

    b = p;

    do {

        a = u % radix;

        u /= radix;

        *p++ = a + '0';

    } while (u > 0);

    len = (int) (p - str);

    *p-- = 0;

//swap

    do {

        temp = *p;

        *p = *b;

        *b = temp;

        --p;

        ++b;

    } while (b < p);

    //return len;

}