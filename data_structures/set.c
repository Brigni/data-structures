#include <stddef.h>
#include <string.h>
#include <stdio.h>

#define HASHMAP_SIZE 64

struct aiv_dictionary_item
{
    const char *key;
    size_t key_len;
};

struct aiv_dictionary
{
    struct aiv_dictionary_item hashmap[HASHMAP_SIZE];
};

size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;

    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }

    return hash;
}

void aiv_set_insert(struct aiv_dictionary *set, const char *key)
{
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    printf("hash of %s = %llu (index: %llu)\n", key, hash, index);

    if (set->hashmap[index].key_len == 0)
    {
        set->hashmap[index].key = key;
        set->hashmap[index].key_len = key_len;
        printf("added %s at index %llu\n", key, index);
        return;
    }

    printf("COLLISION! for %s (index %llu), the key is already present in the set\n", key, index);
}

void aiv_set_find(struct aiv_dictionary *set, const char *key)
{
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    printf("hash of %s = %llu (index: %llu)\n", key, hash, index);

    if (set->hashmap[index].key_len > 0)
    {
        if (set->hashmap[index].key_len == key_len && !memcmp(set->hashmap[index].key, key, key_len))
        {
            printf("FOUND %s at index %llu\n", key, index);
            return;
        }
    }
}

void aiv_set_remove(struct aiv_dictionary *set, const char *key)
{
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    if (set->hashmap[index].key_len > 0) //first I need to find it
    {
        if (set->hashmap[index].key_len == key_len && !memcmp(set->hashmap[index].key, key, key_len))
        {
            set->hashmap[index].key = 0; //delete the content of the cell 
            set->hashmap[index].key_len = 0; //no need to free the memory because it's still part of the set
            printf("Removed item with key %s at index %llu\n", key, index);
            return;
        }
    }
}

int main(int argc, char **argv)
{
    struct aiv_dictionary myset;
    memset(&myset, 0, sizeof(struct aiv_dictionary));
    /*
    myset.hashmap[0].key = NULL;
    myset.hashmap[0].key_len = 0;
    myset.hashmap[1].key = NULL;
    myset.hashmap[1].key_len = 0;
    myset.hashmap[2].key = NULL;
    myset.hashmap[2].key_len = 0;*/

    aiv_set_insert(&myset, "Hello");
    aiv_set_insert(&myset, "Hello2");
    aiv_set_insert(&myset, "Test");
    aiv_set_insert(&myset, "Foobar");
    aiv_set_insert(&myset, "Foobar");
    aiv_set_insert(&myset, "XYZ");
    aiv_set_insert(&myset, "AAAAAA");
    aiv_set_insert(&myset, "AAAAAa");

    aiv_set_find(&myset, "XYZ");

    aiv_set_remove(&myset, "Hello2");

    return 0;
}