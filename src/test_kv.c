#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "kv.h"

#define RECORDS         500

void test_release() {
	printf("test_release started\n");
    struct kv *entry = malloc(sizeof(struct kv));
    entry->key = strdup("test_key");
    entry->value = strdup("test_value");
    release(entry);
	printf("test_release complete\n");
}

void test_length() {
	printf("test_length started\n");
    struct kv **array = malloc(2 * sizeof(struct kv *));
    array[0] = malloc(sizeof(struct kv));
    array[0]->key = strdup("a");
    array[0]->value = strdup("1");
    array[1] = NULL;
    assert(length(array) == 1);
    release(array[0]);
    free(array);
	printf("test_length stopped\n");
}

void test_push_pop() {
	printf("test_push_pop started\n");
    struct kv **array = malloc(sizeof(struct kv *));
    *array = NULL;

    printf("creating array\n");
	for (int i = 0; i < RECORDS; i++) {
        struct kv *entry = malloc(sizeof(struct kv));
        asprintf(&entry->key, "key_%d", i);
        asprintf(&entry->value, "value_%d", i);

		// printf("key='%s' value='%s'\n",entry->key,entry->value);

        push(&array, entry);
    }
    assert(length(array) == RECORDS);
    
	printf("popping array, backward\n");
    for (int i = RECORDS-1; i >= 0; i--) {
        struct kv *popped = pop(&array);
        
        char expected_key[32], expected_value[32];
        snprintf(expected_key, sizeof(expected_key), "key_%d", i);
        snprintf(expected_value, sizeof(expected_value), "value_%d", i);

        assert(strcmp(popped->key, expected_key) == 0);
        assert(strcmp(popped->value, expected_value) == 0);
        release(popped);
    }
	printf("array popped\n");
    assert(length(array) == 0);
    destroy(array);
	printf("test_push_pop stoppped\n");
}

void test_shift_unshift() {
	printf("test_shift_unshift started\n");

    struct kv **array = malloc(sizeof(struct kv *));
    *array = NULL;

    printf("creating array\n");
    for (int i = 0; i < RECORDS; i++) {
        struct kv *entry = malloc(sizeof(struct kv));
        // asprintf(&entry->key, "key_%d", i);
        // asprintf(&entry->value, "value_%d", i);
        if (asprintf(&entry->key, "key_%d", i) == -1) return;
        if (asprintf(&entry->value, "value_%d", i) == -1) return;

        shift(&array, entry);
    }
    assert(length(array) == RECORDS);
    
    printf("unshifting array\n");
    for (int i = RECORDS-1; i >= 0; i--) {
        struct kv *unshifted = unshift(&array);
        
        char expected_key[32], expected_value[32];
        snprintf(expected_key, sizeof(expected_key), "key_%d", i);
        snprintf(expected_value, sizeof(expected_value), "value_%d", i);

/*        printf("%s:%s == %s:%s\n",
            unshifted->key,unshifted->value,
            expected_key, expected_value
        ); */

        assert(strcmp(unshifted->key, expected_key) == 0);
        assert(strcmp(unshifted->value, expected_value) == 0);
        release(unshifted);
    }
    assert(length(array) == 0);
    free(array);
	printf("test_shift_unshift stopped\n");

}

void test_reverse() {
	printf("test_reverse started\n");

    struct kv **array = malloc(3 * sizeof(struct kv *));
    array[0] = malloc(sizeof(struct kv));
    array[1] = malloc(sizeof(struct kv));
    array[2] = NULL;

    array[0]->key = strdup("first");
    array[0]->value = strdup("1");
    array[1]->key = strdup("second");
    array[1]->value = strdup("2");

    reverse(array);
    assert(strcmp(array[0]->key, "second") == 0);
    assert(strcmp(array[1]->key, "first") == 0);
    
    release(array[0]);
    release(array[1]);
    free(array);
	printf("test_reverse stopped\n");

}

void test_split_join() {
	printf("test_split_join started\n");

    struct kv *pair = split("hello=world",1024, "=");
    assert(pair);
    assert(strcmp(pair->key, "hello") == 0);
    assert(strcmp(pair->value, "world") == 0);

    char *joined = join(pair, "=");
    assert(strcmp(joined, "hello=world") == 0);
    
    free(joined);
    release(pair);
	printf("test_split_join stopped\n");

}

void fuzz_test_split() {
	printf("fuzz_test_split started\n");

    char buffer[256];
    for (int i = 0; i < 1000; i++) {
        snprintf(buffer, sizeof(buffer), "fuzz_%d=fuzz_value_%d", i, i);
        struct kv *pair = split(buffer, 1024, "=");
        assert(pair);
        release(pair);
    }
	printf("fuzz_test_split stopped\n");

}

int main() {
    test_release();
    test_length();
    test_push_pop();
    test_shift_unshift();
    test_reverse();
    test_split_join();
    fuzz_test_split();
    printf("All tests passed!\n");
    return 0;
}
