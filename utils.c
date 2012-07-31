#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "utils.h"
#include "dunst.h"


char *strtrim(char *str)
{
        char *end;
        while (isspace(*str))
                str++;

        end = str + strlen(str) - 1;
        while (isspace(*end)) {
                *end = '\0';
                end--;
        }

        return str;

}

char *string_replace(const char *needle, const char *replacement,
                     char *haystack)
{
        char *tmp, *start;
        int size;
        start = strstr(haystack, needle);
        if (start == NULL) {
                return haystack;
        }

        size = (strlen(haystack) - strlen(needle)) + strlen(replacement) + 1;
        tmp = calloc(sizeof(char), size);
        memset(tmp, '\0', size);

        strncpy(tmp, haystack, start - haystack);
        tmp[start - haystack] = '\0';

        sprintf(tmp + strlen(tmp), "%s%s", replacement, start + strlen(needle));
        free(haystack);

        if (strstr(tmp, needle)) {
                return string_replace(needle, replacement, tmp);
        } else {
                return tmp;
        }
}

void dunst_printf(int level, const char *fmt, ...)
{
        va_list ap;

        if (level > verbosity) {
                return;
        }
        va_start(ap, fmt);
        vfprintf(stderr, fmt, ap);
        va_end(ap);
}

void die(char *text, int exit_value)
{
        fputs(text, stderr);
        exit(exit_value);
}

/* vim: set ts=8 sw=8 tw=0: */
