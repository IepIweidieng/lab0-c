#include "compare.h"

#include <ctype.h>
#include <stdbool.h>

#define CMP_EXPAND_FMT(n) [CMP_ENUM_NAME(n)] = CMP_FUNC_NAME(n),
static const cmp_func_t funcs[] = {CMP_EXPAND()};
#undef CMP_EXPAND_FMT

#define CMP_EXPAND_FMT(n) [CMP_ENUM_NAME(n)] = CMP_FUNC_STR(n),
static const char *const func_strs[] = {CMP_EXPAND()};
#undef CMP_EXPAND_FMT

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

cmp_func_t cmp_get_func(int index)
{
    if (index >= 0 && index < ARRAY_SIZE(funcs))
        return funcs[index];
    return funcs[CMP_ENUM_NAME(0)];
}

const char *cmp_get_func_str(int index)
{
    if (index >= 0 && index < ARRAY_SIZE(func_strs))
        return func_strs[index];
    return func_strs[CMP_ENUM_NAME(0)];
}

int negstrcasecmp(const char *s1, const char *s2)
{
    return -strcasecmp(s1, s2);
}

int negstrcmp(const char *s1, const char *s2)
{
    return -strcmp(s1, s2);
}

/* Natural comparison */

/* For `strspn()` */

static const char digit[] = "0123456789";
static const char space[] = " \f\n\r\t\v";

/*
 * The digit comparison part of natural comparison.
 * `isdigit(**ps1) || isdigit(**ps2)` should hold.
 */
static int natstrcmp_digit(const char **ps1, const char **ps2)
{
    const char *p1;
    const char *p2;
    int diff;     // The difference of the first mismatch characters
    bool numcmp;  // Perform number comparison or string comparison

    *ps1 += strspn(*ps1, space);
    *ps2 += strspn(*ps2, space);

    if (!isdigit(**ps1)) {
        *ps2 += strspn(*ps2, digit);
        return 1;
    }
    if (!isdigit(**ps2)) {
        *ps1 += strspn(*ps1, digit);
        return -1;
    }

    p1 = *ps1;
    p2 = *ps2;
    *ps1 += strspn(*ps1, digit);
    *ps2 += strspn(*ps2, digit);

    diff = 0;
    numcmp = !(*p1 == '0' || *p2 == '0');
    for (;;) {
        for (;;) {
            if (isdigit(*p1) && isdigit(*p2)) {
                if (!diff) {
                    diff = *p1 - *p2;
                    if (diff)
                        break;
                }
            } else {
                /* strcmp/numcmp: Returns on end of either numbers */
                const int diff_len = isdigit(*p1) - isdigit(*p2);
                if (diff_len || !numcmp)
                    diff = diff_len;
                return diff;
            }

            ++p1;
            ++p2;
        }
        /* strcmp: Returns on first mismatch */
        if (!numcmp)
            return diff;
        ++p1;
        ++p2;
    }
}

/*
 * The basic implement of `natstrcmp()` and `natstrcasecmp()`.
 */
static int natstrcmp_base(const char *s1, const char *s2, bool ignore_case)
{
    const char *p1 = s1;
    const char *p2 = s2;

    while (*p1 || *p2) {
        int diff = 0;

        if (isdigit(*p1) || isdigit(*p2)) {
            diff = natstrcmp_digit(&p1, &p2); /* Compare digits */
        }
        if (!diff) {
            const char c1 = (ignore_case) ? tolower(*p1) : *p1;
            const char c2 = (ignore_case) ? tolower(*p2) : *p2;
            diff = c1 - c2;
        }

        if (diff || !*p1 || !*p2)
            return diff;

        ++p1;
        ++p2;
    }
    return 0;
}

int natstrcasecmp(const char *s1, const char *s2)
{
    return natstrcmp_base(s1, s2, true);
}

int natstrcmp(const char *s1, const char *s2)
{
    return natstrcmp_base(s1, s2, false);
}

int negnatstrcasecmp(const char *s1, const char *s2)
{
    return -natstrcasecmp(s1, s2);
}

int negnatstrcmp(const char *s1, const char *s2)
{
    return -natstrcmp(s1, s2);
}
