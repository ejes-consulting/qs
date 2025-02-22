/* uri.c:  URI Encoding and Decoding                                        */
/* provides "percent" escaping based on RFC 3986 */
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* rfc_compliant:  enforce RFC 3986; defaults to false */
bool rfc_compliant=false;

/* should_encode:  helper function */
static bool should_encode(char c) {
	switch(c){
		case '-':
		case '_':
		case '.':
		case '~':
			return false;
		case '!':
		case '\'':
		case '(':
		case ')':
		case '*':
			if(rfc_compliant) return true;
			return false;
		default:
			if(isalnum(c)) return false;
	}
	return true;
}

/* encodeURIComponent:  basically javascripts encodeURIComponent function */
char *encodeURIComponent(const char *str, size_t length) {
	if (!str || length==0) return NULL;
	size_t len=strnlen(str,length);
	char *encoded=malloc(len*3+1);
	if(!encoded) return NULL;
	char *p=encoded;
	for(size_t i=0;i<len;i++){
		unsigned char c=(unsigned char)str[i];
		if(!should_encode(c)){
			*p++=c;
		} else {
			p+=sprintf(p,"%%%02X",c);
		}
	}
	*p='\0';
	return encoded;
}

/* decodeURIComponent:  basically javascripts decodeURIComponent function */
char *decodeURIComponent(const char *str, size_t length) {
	if (!str) return NULL;
	size_t len=strnlen(str,length);
	char *decoded=malloc(len+1);
	if(!decoded) return NULL;
	char *p=decoded;
	for(size_t i=0;i<len;i++) {
		if(str[i]=='%' && i+2<len 
				&& isxdigit(str[i+1])
				&& isxdigit(str[i+2])){
			int value;
			sscanf(str+i+1, "%2x", &value);
			*p++=(char)value;
			i+=2;
		} else {
			*p++=str[i];
		}
	}
	*p='\0';
	return decoded;
}

/* eof */