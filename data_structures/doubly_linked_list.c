#include <stddef.h>
#include <stdio.h>

struct list_item
{
    struct list_item* prev;
    struct list_item* next;
};

struct list_item* list_get_tail(struct list_item* head)
{
    if(!head)
    {
        return NULL;
    }

    struct list_item* prev_item = head;
    struct list_item* curr_item = head->next;
    while(curr_item)
    {
        prev_item = curr_item;
        curr_item = curr_item->next;
    }

    return prev_item;
}

struct list_item* list_append(struct list_item** head, struct list_item* item)
{
    struct list_item* tail = list_get_tail(*head);
    if (!tail)
    {
        *head = item;
    }
    else
    {
        tail->next = item;
    }
    item->prev = tail;
    item->next = NULL;
    return item;
}

struct list_item* list_remove(struct list_item* item)
{
    if(!item)
    {
        printf("Unable to remove item\n");
        return NULL;
    }
    (item->prev)->next = item->next;
    (item->next)->prev = item->prev;

    item->next = NULL;
    item->prev = NULL;

    return item;
}

struct list_item* list_insert_before(struct list_item* item, struct list_item* itemToInsert)
{
    if(!item || !itemToInsert)
    {
        printf("Error: one of the items is null\n");
        return NULL;
    }
    if(item->prev) //if the selected item already has a previous I need to change its link as well (of the prev)
    {
        (item->prev)->next = itemToInsert;
        itemToInsert->prev = item->prev;
    }
    
    item->prev = itemToInsert;
    itemToInsert->next = item;

    printf("Item added correctly\n");

    return itemToInsert;
}

struct list_item* list_insert_after(struct list_item* item, struct list_item* itemToInsert)
{
    if(!item || !itemToInsert)
    {
        printf("Error: one of the items is null\n");
        return NULL;
    }
    if(item->next)
    {
        (item->next)->prev = itemToInsert;
        itemToInsert->next = item->next;
    }

    item->next = itemToInsert;
    itemToInsert->prev = item;
    
    printf("Item added correctly\n");

    return itemToInsert;
}

int main(int argc, char** argv)
{
    struct list_item* head = NULL;

    struct list_item item1;
    list_append(&head, &item1);

    struct list_item item2;
    list_append(&head, &item2);

    struct list_item item3;
    list_append(&head, &item3);

    list_remove(&item3);
    
    struct list_item item4;

    list_insert_before(&item3, &item4);

    struct list_item item5;

    list_insert_after(&item2, &item5);

    return 0;
}