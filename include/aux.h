/* aux.h:  auxillery functions                                              */
#include "kv.h"

#ifndef AUX_H
#define AUX_H

/* noreturn:  tell the compiler that this branch never returns */
#define noreturn		__builtin_unreachable()

/* e_mode:  modes -- undefined, encode or decode modes */
enum e_mode { UNDEFINED, MENCODE, MDECODE };

/* display:  dispaly a key value pair, and seperate it by "sep" character */
extern void display(struct kv *kv,char sep);

/* extract_environment:  extract a key-value pair array from the environment */
extern struct kv **extract_environment(char *env[]);

/* extract_file:  extract a key-value pair array from a file pointer */
extern struct kv **extract_file(FILE *fp);

/* extract_string:  extract a key-value pair from a string */
extern struct kv **extract_string(char *string);

/* split_amp:  split an ampersand joined string */
extern char **split_amp(const char *str);

/* usage:  display usage and exit */
extern void usage(char *name);

#endif /* AUX_H */
/* eof */