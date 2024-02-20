#include <stddef.h>
#include <stdio.h>

#define AIV_LIST(x) &(x.list_item)

struct aiv_list_item
{
    struct aiv_list_item* next;
    unsigned int count; //the head keeps the items count (weird number)(not working)
};

struct aiv_list_item* aiv_list_get_tail(struct aiv_list_item* head)
{
    if(!head) //list is invalid (empty)
    {
        return NULL;
    }
    
    struct aiv_list_item* current_item = head;
    struct aiv_list_item* last_item = head;
    while(current_item)
    {
        last_item = current_item;
        current_item = current_item->next;
    }

    return last_item;
}

struct aiv_int_item
{
    struct aiv_list_item list_item;
    int value;
};

struct aiv_list_item* aiv_list_append(struct aiv_list_item** head, struct aiv_list_item* item)
{
    struct aiv_list_item* tail = aiv_list_get_tail(*head);
    if(!tail)
    {
        *head = item;
        (*head) = item;
    }
    else
    {
        tail->next = item;
        (*head)->count++;
    }
    item->next = NULL;
    return item;
}

struct aiv_list_item* aiv_list_pop(struct aiv_list_item** head)
{
    if(!(*head))
    {
        return NULL;
    }

    struct aiv_list_item* current_head = *head;
    const unsigned int current_count = current_head->count;
    *head = (*head)->next;
    if(*head)
    {
        (*head)->count = current_count - 1;
    }

    current_head->next = NULL;
    return current_head;
}

unsigned int aiv_list_lenght(struct aiv_list_item* head)
{
    return head->count;
}

struct aiv_list_item* aiv_list_remove(struct aiv_list_item** head, struct aiv_list_item* item)
{
    if(!(*head)) //if list doesn't exist return null
    {
        return NULL;
    }

    if(*head == item) //if the item to remove is the head
    {
        ((*head)->next)->count = (*head)->count - 1; //I make sure the new head has the list item count (-1 because I am removing the head)
        printf("Item removed (head)\n");
        return *head; //return the removed item
    }

    struct aiv_list_item* prev = *head;  //I prepare to cicle through the list storing bot the current and previous nodes
    struct aiv_list_item* curr = (*head)->next;

    while(curr) //cicle the whole list (when curr is null it means I got to the end of the list)
    {
        if(curr == item)
        {
            prev->next = curr->next; //link previous node with next node to keep the list together
            (*head)->count--; //update list item count
            printf("Item removed\n");
            return item; //return removed item
        }
        prev = curr; //update the nodes to check
        curr = curr->next;
    }
    //if I don't return in the while then the item is not in the list
    printf("Item not found\n");
    return NULL;
}

void aiv_list_invert (struct aiv_list_item** head) //not working
{
    //check if list is valid
    if(!(*head))
    {
        return;
    }
    //check if head is the only item in the list
    if(!((*head)->next))
    {
        return;
    }
    struct aiv_list_item* new_head = NULL;
    for(int i = 0; i < (*head)->count; i++)
    {
        struct aiv_list_item* current_item = aiv_list_get_tail(*head); //get last item from old list
        if(new_head)
        {
            aiv_list_append(&new_head, current_item); //if list already has a new head, append new item
        }
        else
        {
            new_head = current_item; //if list doesn't have new head make last item from previous list the new head
        }
        aiv_list_remove(head, current_item); //remove last item from old list to have a new tail
    }
    *head = new_head; //change the old list with the new one
}

int main(int argc, char** argv)
{
    struct aiv_list_item* head = NULL;


    struct aiv_int_item int_item;
    int_item.value = 100;
    aiv_list_append(&head, AIV_LIST(int_item));
    
    struct aiv_int_item int_item2;
    int_item2.value = 101;
    aiv_list_append(&head, AIV_LIST(int_item2));

    struct aiv_int_item int_item3;
    int_item3.value = 102;
    aiv_list_append(&head, AIV_LIST(int_item3));

    // printf("item count: %d\n", aiv_list_lenght(head));

    // printf("item 1: %d, item 2: %d, item 3: %d\n", int_item.value, int_item2.value, int_item3.value);

    // aiv_list_invert(&head);

    // printf("item 1: %d, item 2: %d, item 3: %d\n", int_item.value, int_item2.value, int_item3.value);

    struct aiv_list_item* item = aiv_list_remove(&head, AIV_LIST(int_item2));
    
    printf("item 1: %d, item 2: %d\n", int_item.value, int_item3.value);
    
    return 0;
}
