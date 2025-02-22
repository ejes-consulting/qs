/* main.c:  Main qs "querystring" utility */
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aux.h"
#include "kv.h"
#include "uri.h"

/* mode:  undefined, encode or decode modes */
enum e_mode mode=UNDEFINED;
/* envrion:  act upon the environment */
bool environ=false;
/* quiet:  output to terminal */
bool quiet=false;

/* main:  it all begins here. */
int main(int argc,char *argv[],char *env[]){
	struct kv **array=NULL;

	if(argc==1)
		usage(argv[0]);

	for(int i=1;i<argc;i++){
		if(strcmp(argv[i],"-h")==0){
			usage(argv[0]);
		} else if(strcmp(argv[i],"-d")==0){
			mode=MDECODE;
		} else if(strcmp(argv[i],"-e")==0){
			mode=MENCODE;
		} else if(strcmp(argv[i],"-s")==0){
			environ=true;
		} else if(strcmp(argv[i],"-q")==0){
			quiet=true;
		} else if(strcmp(argv[i],"-E")==0){
			stack(&array,extract_environment(env));
		} else if(strcmp(argv[i],"-f")==0){
			FILE *fp;
			i++;
			if(strcmp(argv[i],"-")==0){
				fp=stdin;
			} else {
				fp=fopen(argv[i],"ro");
				if(!fp){
					fprintf(stderr,"Unable to open \"%s\" to read.\n",argv[i]);
					return EXIT_FAILURE;
				}
			}
			stack(&array,extract_file(fp));
			fclose(fp);
		} else {
			stack(&array,extract_string(argv[i]));
		}
	}

	if(array==NULL)
		return EXIT_SUCCESS;

	char ch='\0';

	for(int i=0;array[i]!=NULL;i++){
		ch='\0';
		switch(mode){
			case MENCODE:
				array[i]->key=encodeURIComponent(array[i]->key,strlen(array[i]->key));
				array[i]->value=encodeURIComponent(array[i]->value,strlen(array[i]->value));

				if(array[i+1]!=NULL) ch='&';
				break;
			case MDECODE:
				array[i]->key=decodeURIComponent(array[i]->key,strlen(array[i]->key));
				array[i]->value=decodeURIComponent(array[i]->value,strlen(array[i]->value));

				if(array[i+1]!=NULL) ch='\n';
				break;
			default:
				fprintf(stderr,"Invalid mode, cannot write \"%s=%s\"\n",array[i]->key,array[i]->value);
				return EXIT_FAILURE;
		}
		display(array[i],ch);
	}

	putchar('\n');

	destroy(array);
	return EXIT_SUCCESS;
}


/* eof */