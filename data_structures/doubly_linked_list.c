#include <stddef.h>
#include <stdio.h>

struct list_item
{
    struct list_item* prev;
    struct list_item* next;
    int value; //added for testing 
};

struct list_item* list_get_tail(struct list_item* head)
{
    if(!head)
    {
        return NULL;
    }

    struct list_item* prev_item = head; //can use only one item, check only when next item is not null (?)
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

    if(!item->next)//if item is tail
    {
        (item->prev)->next = NULL;
        printf("Removed tail\n");
    }
    else if(!item->prev) //item is head
    {
        (item->next)->prev = NULL;
        printf("Removed head\n");
    }
    else
    {
        (item->prev)->next = item->next;
        (item->next)->prev = item->prev;
    }

    item->next = NULL;
    item->prev = NULL;

    printf("Item removed\n");

    return item;
}

struct list_item* list_insert_before(struct list_item* item, struct list_item* itemToInsert)
{
    if(!item->next && !item->prev)
    {
        printf("Invalid item (item is not in a list)\n");
        return NULL;
    }
    if(!item || !itemToInsert)
    {
        printf("Error: one of the items is null\n");
        return NULL;
    }
    
    if(item->prev) //item is not head
    {
        itemToInsert->prev = item->prev;
        (item->prev)->next = itemToInsert;
    }
    else
    {
        itemToInsert->prev = NULL;
    }

    itemToInsert->next = item;
    item->prev = itemToInsert;

    printf("Item added correctly\n");

    return itemToInsert;
}

struct list_item* list_insert_after(struct list_item* item, struct list_item* itemToInsert)
{
    if(!item->next && !item->prev)
    {
        printf("Invalid item (item is not in a list)\n");
        return NULL;
    }
    if(!item || !itemToInsert)
    {
        printf("Error: one of the items is null\n");
        return NULL;
    }

    if(item->next) //if item is not tail
    {
        itemToInsert->next = item->next;
        (item->next)->prev = itemToInsert;
    }
    else
    {
        itemToInsert->next = NULL;
    }
    
    itemToInsert->prev = item;
    item->next = itemToInsert;

    printf("Item added correctly\n");

    return itemToInsert;
}

void print_list(struct list_item* head)
{
    struct list_item* curr = head;
    while(curr)
    {
        printf("value: %d\n", curr->value);
        curr = curr->next;
    }
}

int main(int argc, char** argv)
{
    struct list_item* head = NULL;

    struct list_item item1;
    list_append(&head, &item1);
    item1.value = 1;

    struct list_item item2;
    list_append(&head, &item2);
    item2.value = 2;

    struct list_item item3;
    list_append(&head, &item3);
    item3.value = 3;

    print_list(head);

    list_remove(&item3);
    print_list(head);
    
    struct list_item item4;
    item4.value = 4;

    list_insert_before(&item2, &item4);
    
    struct list_item item5;
    item5.value = 5;

    list_insert_after(&item2, &item5);
    print_list(head);

    return 0;
}
