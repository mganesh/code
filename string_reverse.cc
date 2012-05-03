/*
 * =====================================================================================
 *
 *       Filename:  string_reverse.c
 *
 *    Description:  string reverse
 *
 *        Version:  1.0
 *        Created:  05/03/12 19:05:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ganesh Muniyandi (gm), ganesh.muniyandi@gmail.com
 *        Company:  Open Source
 *
 * =====================================================================================
 */

#include <string.h>
#include <stdio.h>
#include <assert.h>

#define SWP(x,y) (x^=y, y^=x, x^=y)

void strrev(char *start)
{
    if (start == NULL) return;

    char *end = start;
    while(end && *end) ++end; /* find eos */
    for(--end; start < end; ++start, --end)
        SWP(*start, *end);
    return;
}

int main(int argc, char** argv) {

    /* Case 1: Null String */
    char nullstring[] = "";
    strrev(nullstring);
    assert(strcmp(nullstring, "") == 0);

    /* Case 2: NULL Ptr */
    char *null = NULL;
    strrev(null);

    /* Case 3: Valid string */
    char Valid [] = "ValidString";
    strrev(Valid);
    assert(strcmp(Valid, "gnirtSdilaV") == 0);
    printf("%s\n", Valid);

    return 0;
}
