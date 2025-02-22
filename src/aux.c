/* aux.c:  auxillery functions */
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aux.h"

/* mode:  undefined, encode or decode modes */
extern enum e_mode mode;
/* envrion:  act upon the environment */
extern bool environ;
/* quiet:  output to terminal */
extern bool quiet;
 
/* display:  dispaly a key value pair, and seperate it by "sep" character */
void display(struct kv *kv,char sep){
	if(!quiet){
		printf("%s=%s",kv->key,kv->value);
		if(sep!='\0') {
			putchar(sep);
		}
	}
	if(environ){
		setenv(kv->key,kv->value,true);
	}
	return;
}

/* extract_environment:  extract a key-value pair array from the environment */
struct kv **extract_environment(char *env[]){
	struct kv **array=NULL;
	for(int i=0;env[i]!=NULL;i++){
		push(&array,split(env[i],strlen(env[i]),"="));
	}
	return array;
}

/* extract_file:  extract a key-value pair array from a file pointer */
struct kv **extract_file(FILE *fp){
	struct kv **array=NULL;
	char buffer[LINE_MAX];
	char **strings=NULL;

	while(!feof(fp)){
		fgets(buffer,LINE_MAX,fp);
		stack(&array,extract_string(buffer));
	}
	return array;
}

/* extract_string:  extract a key-value pair from a string */
struct kv **extract_string(char *string){
	char **strings=NULL;
	struct kv **array=NULL;
	switch(mode){
		case MENCODE:
			push(&array,split(string,strlen(string),"="));
			break;
		case MDECODE:
			strings=split_amp(string);
			for(int i=0;strings[i]!=NULL;i++){
				push(&array,split(strings[i],strlen(strings[i]),"="));
				free(strings[i]);
			}
			free(strings);
			break;
		default:
			fprintf(stderr,"Invalid mode, unable to extract \"%s\"\n",string);
			exit(EXIT_FAILURE);
			noreturn;

	}
	return array;
}

/* split_amp:  split an ampersand joined string */
char **split_amp(const char *str){
	if(!str) return NULL;

	int count=1;
	for(const char *p=str;*p;p++)
		if(*p=='&') count++;

	char **result=calloc(count+1,sizeof(char *));
	if(!result) return NULL;

	char *copy=strdup(str);
	if(!copy){
		free(result);
		return NULL;
	}
	
	int i=0;
	char *token=strtok(copy,"&");
	while(token){
		result[i]=strdup(token);
		if(!result[i]){
			for(int j=0;j<i;j++)
				free(result[j]);
			free(result);
			free(copy);
			return NULL;
		}
		i++;
		token=strtok(NULL,"&");
	}

	result[i]=NULL;
	
	free(copy);
	return result;
}

/* usage:  display usage and exit */
void usage(char *name){
	fprintf(stderr,
	"usage:\n\t%s [-e|-d] [-s] [-q] [-E] [-f file] KEY=\"VALUE\" ...\n"
		"\t""-e""\tencode\n"
		"\t""-d""\tdecode\n"
		"\t""-s""\tset environment variables\n"
		"\t""-E""\tExtract environment variables\n"
		"\t""-f"" file\toperate on file instead of key=value arguments or \"-\" for stdin.\n",
	name);
	exit(EXIT_FAILURE);
	noreturn;
}

/* eof */