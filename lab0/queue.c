/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q==NULL)
        return q;
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q==NULL)
        return;
    list_ele_t *p = q->head;
    while (p != NULL)
    {
        list_ele_t *tmp = p->next;
        free(p->value);
        free(p);
        p = tmp;
    }
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    /* What should you do if the q is NULL? */
    if (q == NULL)
        return false;
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    /* What if either call to malloc returns NULL? */
    if (newh == NULL)
        return false;

    /* Don't forget to allocate space for the string and copy it */
    int len=0;
    while (s[len]!='\0')
    {
        len++;
    }
    char * newstr;
    newstr = malloc(sizeof(char)*(len+1));
    if (newstr == NULL)
    {
        free(newh);
        return false;
    }
    for (int i=0;i<=len;++i){
        newstr[i] = s[i];
    }
    newh->value = newstr;
    newh->next = q->head;
    q->head = newh;
    if (q->tail == NULL)
        q->tail = newh;
    q->size++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL)
        return false;
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL)
        return false;
    int len=0;
    while (s[len]!='\0')
    {
        len++;
    }
    char * newstr;
    newstr = malloc(sizeof(char)*(len+1));
    if (newstr == NULL)
    {
        free(newh);
        return false;
    }
    for (int i=0;i<=len;++i){
        newstr[i] = s[i];
    }
    newh->value = newstr;
    newh->next = NULL;
    q->tail->next = newh;
    q->tail = newh;
    q->size++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if (q==NULL || q->head == NULL)
        return false;
    list_ele_t *delem = q->head;
    char* dstr = delem->value;
    q->head = q->head->next;
    q->size--;
    if (sp != NULL)
    {
        int i;
        for (i=0;i<bufsize-1;++i)
        {
            sp[i] = dstr[i];
            if (sp[i]=='\0')
                break;
        }
        if (i==bufsize-1)
            sp[i] = '\0';
    }
    free(delem);
    free(dstr);
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q==NULL)
        return 0;
    return q->size;
}


/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (q==NULL || q->head ==NULL)
        return;
    list_ele_t *p1 = q->head;
    q->tail = p1;
    list_ele_t *p2 = q->head->next;
    while (p2!=NULL)
    {
        list_ele_t *tmp = p2;
        p2 = p2->next;
        tmp->next = p1;
        p1 = tmp;
    }
    q->head->next = NULL;
    q->head = p1;
    return;
    /* You need to write the code for this function */
}

