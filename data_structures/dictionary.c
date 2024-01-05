#include <stddef.h>
#include <string.h>
#include <stdio.h>

#define HASHMAP_SIZE 64

struct aiv_dictionary_item
{
    const char *key;
    const char *value;
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

void aiv_dictionary_insert(struct aiv_dictionary *dictionary, const char *key, const char* value)
{
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    printf("hash of %s = %llu (index: %llu)\n", key, hash, index);

    if (dictionary->hashmap[index].key_len == 0)
    {
        dictionary->hashmap[index].key = key;
        dictionary->hashmap[index].key_len = key_len;
        dictionary->hashmap[index].value = value;
        printf("added %s at index %llu with value %s\n", key, index, value);
        return;
    }

    printf("COLLISION! for %s (index %llu), the key is already present in the dictionary\n", key, index);
}

void aiv_dictionary_find(struct aiv_dictionary *dictionary, const char *key)
{
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    printf("hash of %s = %llu (index: %llu)\n", key, hash, index);

    if (dictionary->hashmap[index].key_len > 0)
    {
        if (dictionary->hashmap[index].key_len == key_len && !memcmp(dictionary->hashmap[index].key, key, key_len))
        {
            printf("FOUND item with key %s at index %llu with value %s\n", key, index, dictionary->hashmap[index].value);
            return;
        }
    }
}

void aiv_dictionary_remove(struct aiv_dictionary *dictionary, const char *key)
{
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    if (dictionary->hashmap[index].key_len > 0) //first I need to find it
    {
        if (dictionary->hashmap[index].key_len == key_len && !memcmp(dictionary->hashmap[index].key, key, key_len))
        {
            dictionary->hashmap[index].key = 0; //delete the content of the cell 
            dictionary->hashmap[index].key_len = 0; //no need to free the memory because it's still part of the dictionary
            printf("Removed item with key %s at index %llu with value %s\n", key, index, dictionary->hashmap[index].value);
            return;
        }
    }
}

int main(int argc, char **argv)
{
    struct aiv_dictionary myDictionary;
    memset(&myDictionary, 0, sizeof(struct aiv_dictionary));
    

    aiv_dictionary_insert(&myDictionary, "Hello", "bucket");
    //aiv_dictionary_insert(&myDictionary, "Hello2", 100); //don't know how to make it accessible to every variable type
    //aiv_dictionary_insert(&myDictionary, "Test", 0b1001);
    //aiv_dictionary_insert(&myDictionary, "Foobar", -75);
    //aiv_dictionary_insert(&myDictionary, "Foobar", 76);

    aiv_dictionary_find(&myDictionary, "Test");

    aiv_dictionary_remove(&myDictionary, "Hello2");

    return 0;
}