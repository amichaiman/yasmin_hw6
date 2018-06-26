//
// Created by amichai on 26/06/18.
//

#ifndef UNTITLED22_SET_H
#define UNTITLED22_SET_H
#define MAX_SET_SIZE 1000

typedef enum {FALSE,TRUE} Boolean;
typedef enum {SUCCESS=1,FAILURE=-1} Result;
typedef void* Element;
typedef struct set_rec {
    Element elem[MAX_SET_SIZE];
    int n_elem; /* set size */
    int last; /* index of last element */
    int curr; /* index of current element */
    Boolean (*cmp)(Element,Element);
    Element (*cpy)(Element);
    char* (*lbl)(Element);
    void (*fre)(Element);
}* Set;
/* Initializes the Set; sets the maximal capacity to MAX_SET_SIZE
1
 Returns a pointer to a record on the HEAP, or NULL if fails.
 Requires auxiliary functions:
cmp : testing whether two elements are identical
cpy : copying an element to the Heap
lbl: providing a string that labels an element
fre : deleting an element and freeing its memory */
Set SetCreate (Boolean (*cmp)(Element,Element),
               Element (*cpy (Element)), char* (*lbl)(Element),
               void (*fre)(Element));


/* Inserts a copy of the element to the set.
Returns SUCCESS when added or already exists or FAILURE when the
set is full.*/
Result SetAdd (Set,Element);


/* Removes a given element from the set. If accomplished, returns
SUCCESS; otherwise, when the element does not exist, it returns
FAILURE */
Result SetRemove (Set,Element);


/* Checks whether a given element exists within the set. */
Boolean SetIsIn (Set,Element);


/* Checks whether the set is empty. */
Boolean SetIsEmpty (Set,Element);


/* Calculates the intersection of two given sets in the form of a
result set.
Returns a pointer to the result on the HEAP, or NULL if fails.*/
Set SetIntersection (Set,Set);


/* Calculates the union of two given sets in the form of a result set.
Returns a pointer to the result on the HEAP, or NULL if fails.*/
Set SetUnion (Set,Set);


/* Prints the content of the set based on the provided labeling
function. */
void SetPrint(Set s);


/* Releases all the resources of the set */
void SetDestroy (Set s);

#endif //UNTITLED22_SET_H
