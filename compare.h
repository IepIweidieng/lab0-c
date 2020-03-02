#ifndef LAB0_COMPARE_H
#define LAB0_COMPARE_H

#include <string.h>  /* strcmp */
#include <strings.h> /* strcasecmp */

typedef int (*cmp_func_t)(const char *s1, const char *s2);

cmp_func_t cmp_get_func(int index);
const char *cmp_get_func_str(int index);

/* Name of the comparison functions */
#define CMP_FUNC_NAME_0 strcasecmp
#define CMP_FUNC_NAME_1 strcmp
#define CMP_FUNC_NAME_2 negstrcasecmp
#define CMP_FUNC_NAME_3 negstrcmp

/* Function name of the comparison functions */
#define CMP_FUNC_NAME(index) CMP_FUNC_NAME_##index
#define CMP_FUNC_STR(index) CMP_STR(CMP_FUNC_NAME(index))
/* Enumeration name of the comparison functions */
#define CMP_ENUM_NAME(index) CMP_CAT(k_, CMP_FUNC_NAME_##index)

/* Concatenate with expansion */
#define CMP_CAT(x, ...) CMP_CAT_NOEXPAND(x, __VA_ARGS__)
#define CMP_CAT_NOEXPAND(x, ...) x##__VA_ARGS__

/* Stringify with expansion */
#define CMP_STR(...) CMP_STR_NOEXPAND(__VA_ARGS__)
#define CMP_STR_NOEXPAND(...) #__VA_ARGS__

/* Define macro `CMP_EXPAND_FMT(n)` first and then invoke `CMP_EXPAND()` */

#define CMP_EXPAND() \
    CMP_EXPAND_FMT(0) CMP_EXPAND_FMT(1) CMP_EXPAND_FMT(2) CMP_EXPAND_FMT(3)

#define CMP_EXPAND_FMT(n) CMP_ENUM_NAME(n) = n,
typedef enum { CMP_EXPAND() } cmp_idx_t;
#undef CMP_EXPAND_FMT

int negstrcasecmp(const char *s1, const char *s2);
int negstrcmp(const char *s1, const char *s2);

#endif /* LAB0_COMPARE_H */
