#include "stdio.h"
#include "ctype.h"
#include "string.h"

int main(int argv, char *args[]) {
    int len = strlen(args[0]);
    char str[len];
    strncpy(str, args[0], len);
    int i = 1;
    while (i < strlen(str)) {
        if (str[i - 1] == 32 && str[i] == 32) {
            memmove(&str[i], &str[i + 1], len - i);
            --i;
        }
        ++i;
    }
    write(1, str, sizeof(char) * strlen(str));   
}