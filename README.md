# qs
QueryString utility

A command line utility to encode or decode querystring (uri or sometimes called "percent" encoding)
it is also rfc 3986 compatible with slight modifications.

```
usage:
	./qs [-e|-d] [-s] [-q] [-E] [-f file] KEY="VALUE" ...
	-e	encode
	-d	decode
	-s	set environment variables
	-E	extract environment variables
	-f file	operate on file instead of key=value arguments or "-" for stdin.
```
