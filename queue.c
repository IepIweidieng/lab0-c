#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (q) {
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (!q)
        return;

    /* Free queue elements */
    for (list_ele_t *k = q->head; k;) {
        list_ele_t *const next = k->next;
        free(k->value);
        free(k);
        k = next;
    }
    /* Free queue structure */
    free(q);
}

/*
 * Return `NULL` if could not allocate space.
 * Return non-`NULL` if successful.
 * Argument `s` points to the string to be stored and should not be `NULL`.
 * Note: `newh->next` will not be initialized.
 */
static list_ele_t *ele_alloc(const char *s)
{
    /* Don't forget to allocate space for the string and copy it */
    list_ele_t *const newh = malloc(sizeof(list_ele_t));
    if (newh) {
        const size_t len = strlen(s) + 1;
        newh->value = malloc(len);
        if (newh->value) {
            memcpy(newh->value, s, len);
        } else {
            /* What if either call to malloc returns NULL? */
            free(newh);
            return NULL;
        }
    }
    return newh;
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    if (!q)
        return false;

    newh = ele_alloc(s);
    if (newh) {
        newh->next = q->head;
        q->head = newh;
        if (!q->tail)  // The tail will appear
            q->tail = newh;
        ++q->size;
        return true;
    }
    return false;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    list_ele_t *newh;
    if (!q)
        return false;

    newh = ele_alloc(s);
    if (newh) {
        newh->next = NULL;
        if (!q->head)  // The head will appear
            q->head = newh;
        else if (q->tail)  // The original tail will be appended
            q->tail->next = newh;
        q->tail = newh;
        ++q->size;
        return true;
    }
    return false;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    list_ele_t *node;
    if (!q || !q->head)
        return false;

    node = q->head;
    if (sp && bufsize) {
        const size_t len = strnlen(node->value, bufsize - 1);
        memcpy(sp, node->value, len + 1);
        if (len + 1 == bufsize)
            sp[len] = '\0';
    }
    free(node->value);

    q->head = q->head->next;
    if (node == q->tail)  // The tail will disappear
        q->tail = NULL;
    free(node);

    --q->size;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    return (q) ? q->size : 0;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    list_ele_t *prev;

    if (!q || !q->head)
        return;

    /* Re-assign `k->next` */
    prev = NULL;
    for (list_ele_t *k = q->head; k;) {
        list_ele_t *const next = k->next;
        k->next = prev;
        prev = k;
        k = next;
    }
    /* `prev` is now the original tail */

    /* Swap `head` and `tail` */
    q->tail = q->head;
    q->head = prev;
}

typedef struct {
    list_ele_t *head;
    list_ele_t *tail;
} list_span_t;

/*
 * Sort `len` elements start with `head` in ascending order using merge sort
 * No effect if `head` is `NULL` or its member `next` is `NULL`.
 * The function reduces to insertion sort when `len` < 4
 */
static list_span_t ele_sort(list_ele_t *head, size_t len)
{
    list_ele_t *left;
    list_ele_t *right;
    list_ele_t *merge;

    if (!head || !head->next)
        return (list_span_t){head, head};

    left = right = head;
    for (size_t k = 1, n = len / 2; k < n && right; ++k)
        right = right->next;
    if (right) {
        list_ele_t *const next = right->next;
        right->next = NULL;
        right = next;
    }

    {
        const list_span_t left_res = ele_sort(left, len / 2);
        left = left_res.head;
        if (!right)  // `left` is the head of the sorted list
            return left_res;
    }
    right = ele_sort(right, len / 2 + len % 2).head;

    /* Now `left` and `right` are both the head of a non-`NULL` sorted list */
    {
        /* Set up the beginning of the merged list */
        list_ele_t **const phead =
            (strcmp(left->value, right->value) < 0) ? &left : &right;
        merge = head = *phead;
        *phead = (*phead)->next;
    }

    while (left || right) {
        if (!right || (left && strcmp(left->value, right->value) < 0)) {
            /* `left` should be linked from `merge` */
            merge->next = left;
            left = left->next;
        } else {
            /* `right` should be linked from `merge` */
            merge->next = right;
            right = right->next;
        }
        merge = merge->next;
    }

    return (list_span_t){head, merge};
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    list_span_t span;
    if (!q || !q->head || !q->head->next)
        return;

    span = ele_sort(q->head, q->size);
    q->head = span.head;
    q->tail = span.tail;
}
