/* uri.h:  URI Encoding and Decoding                                        */
/* provides "percent" escaping based on RFC 3986 */
#include <stdbool.h>
#include <stddef.h>

#ifndef URI_H
#define URI_H

/* rfc_compliant:  enforce RFC 3986; defaults to false */
extern bool rfc_compliant;

/* encodeURIComponent:  basically javascripts encodeURIComponent function */
extern char *encodeURIComponent(const char *str, size_t length);

/* decodeURIComponent:  basically javascripts decodeURIComponent function */
extern char *decodeURIComponent(const char *str, size_t length);

#endif /* URI_H */
/* eof */