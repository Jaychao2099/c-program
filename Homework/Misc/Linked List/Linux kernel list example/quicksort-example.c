#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#include "common.h"

static uint16_t values[256];

static void list_qsort(struct list_head *head)
{
    struct list_head list_less, list_greater;
    struct listitem *pivot;
    struct listitem *item = NULL, *is = NULL;

    if (list_empty(head) || list_is_singular(head))
        return;
    
    // Initialize the two lists for less and greater elements
    INIT_LIST_HEAD(&list_less);
    INIT_LIST_HEAD(&list_greater);

    pivot = list_first_entry(head, struct listitem, list);
    list_del(&pivot->list);     // Remove pivot from the original list

    list_for_each_entry_safe(item, is, head, list) {        // Iterate through the list
        if (cmpint(&item->i, &pivot->i) < 0)
            list_move_tail(&item->list, &list_less);        // Move to the less list
        else
            list_move_tail(&item->list, &list_greater);     // Move to the greater list
    }

    // Recursively sort the less and greater lists
    list_qsort(&list_less);
    list_qsort(&list_greater);

    // Splice the lists back together
    // The pivot is added to the head of the list, followed by the less and greater lists
    list_add(&pivot->list, head);
    list_splice(&list_less, head);
    list_splice_tail(&list_greater, head);
}

void print_list(struct list_head *head)
{
    struct listitem *item = NULL;

    list_for_each_entry(item, head, list) {
        printf("%d ", item->i);
    }
    printf("\n");
}

int main()
{
    struct list_head testlist;
    struct listitem *item, *is = NULL;
    size_t i;

    random_shuffle_array(values, (uint16_t)ARRAY_SIZE(values));

    INIT_LIST_HEAD(&testlist);

    assert(list_empty(&testlist));

    for (i = 0; i < ARRAY_SIZE(values); i++)
    {
        item = (struct listitem *)malloc(sizeof(*item));
        assert(item);
        item->i = values[i];
        list_add_tail(&item->list, &testlist);
    }

    assert(!list_empty(&testlist));

    printf("Before sorting:\n");
    print_list(&testlist);

    qsort(values, ARRAY_SIZE(values), sizeof(values[0]), cmpint);
    list_qsort(&testlist);

    printf("After sorting:\n");
    print_list(&testlist);

    i = 0;
    list_for_each_entry_safe(item, is, &testlist, list)
    {
        assert(item->i == values[i]);
        list_del(&item->list);
        free(item);
        i++;
    }

    assert(i == ARRAY_SIZE(values));
    assert(list_empty(&testlist));

    return 0;
}