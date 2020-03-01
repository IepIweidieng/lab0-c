#include "compare.h"

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
