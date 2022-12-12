#include "stdio.h"
#include "ctype.h"
#include "string.h"

int main(int argv, char *args[]) {
    int len = strlen(args[0]);
    char str[len];
    strncpy(str, args[0], len);
    for (int i = 0; i < len; ++i)
        str[i] = tolower(str[i]);
    write(1, str, sizeof(char) * strlen(str));
}