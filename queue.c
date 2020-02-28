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
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    q->head = q->head->next;
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
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}
