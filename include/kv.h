/* kv.h:  Key Value Store                                                   */
#include <stddef.h>
 
#ifndef KV_H
#define KV_H

struct kv {
	char *key;
	char *value;
};

/* destroy:  free and unallocate an array */
extern void destroy(struct kv **array);

/* duplicate:  create a duplicate of an array */
extern struct kv **duplicate(struct kv **array);

/* join:  join a kv structure by sep to create a string */
extern char *join(const struct kv *pair,const char *sep);

/* length:  return the length of an array */
extern size_t length(struct kv **array);

/* pop:  pop a value from the back of an array */
extern struct kv *pop(struct kv ***array);

/* push:  pushes a value to the back of an array */
extern void push(struct kv ***array, struct kv *value);

/* release:  free a struct kv key value pair and the structure */
extern void release(struct kv *k);

/* reverse:  reverses an array */
extern void reverse(struct kv **array);

/* shift:  add a value to the begining of an array */
extern void shift(struct kv ***array, struct kv *value);

/* split:  split a string by sep and create a kv structure */
extern struct kv *split(const char *string,const size_t len,const char *sep);

/* stack:  stack two arrays into one */
extern void stack(struct kv ***dest,struct kv **src);

/* unshift:  remove a value from the beginning of an array */
extern struct kv *unshift(struct kv ***array);

#endif /* KV_H */
/* eof */