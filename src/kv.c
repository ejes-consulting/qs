/* kv.c:  Key Value Store                                                   */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "kv.h"

/* destroy:  free and unallocate an array */
void destroy(struct kv **array){
	if(!array) return;
	for(int i=0;array[i]!=NULL;i++){
		release(array[i]);
	}
	free(array);
	return;
}

/* duplicate:  create a duplicate of an array */
struct kv **duplicate(struct kv **array){
	if(!array) return NULL;
	struct kv **value=NULL;
	for(int i=0;array[i]!=NULL;i++){
		value=realloc(value,(i+1)*sizeof(struct kv *));
		value[i]=malloc(sizeof(struct kv));
		value[i]->key=strdup(array[i]->key);
		value[i]->value=strdup(array[i]->value);
	}
	return value;
}

/* join:  join a kv structure by sep to create a string */
char *join(const struct kv *pair,const char *sep){
	int len=strlen(pair->key)+strlen(pair->value)+2;
	char *str=malloc(len);
	*str='\0';
	strncat(str,pair->key,len);
	strncat(str,sep,len);
	strncat(str,pair->value,len);
	return str;
}

/* length:  return the length of an array */
size_t length(struct kv **array) {
	if(!array) return 0;
	size_t i=0;
	while(array[i]!=NULL) i++;
	return i;
}

/* pop:  pop a value from the back of an array */
struct kv *pop(struct kv ***array) {
	size_t len=length(*array);
	if(len==0) return NULL;
	struct kv *value=(*array)[len - 1];
	(*array)[len-1]=NULL;
	struct kv **temp=realloc(*array,len*sizeof(struct kv *));
	if (temp || len==1) {
		*array=temp;
	}	
	return value;
}

/* push:  pushes a value to the back of an array */
void push(struct kv ***array, struct kv *value) {
	if(!array || !value) return;
	size_t len=length(*array);
	struct kv **temp=realloc(*array,(len+2)*sizeof(struct kv *));
	if(!temp) return;
	*array=temp;
	(*array)[len]=value;
	(*array)[len+1]=NULL;
	return;
}

/* release:  free a struct kv key value pair and the structure */
void release(struct kv *k){
	if(!k) return;
	free(k->key);
	free(k->value);
	free(k);
	return;
}

/* reverse:  reverses an array */
void reverse(struct kv **array) {
	if (!array || !*array) return;
	size_t len=length(array);
	for(size_t i=0,j=len-1; i<j; i++,j--){
		struct kv *tmp=array[i];
		array[i]=array[j];
		array[j]=tmp;
	}
	return;
}

/* shift:  add a value to the begining of an array */
void shift(struct kv ***array, struct kv *value) {
	reverse(*array);
	push(array,value);
	reverse(*array);
	return;
}

/* split:  split a string by sep and create a kv structure */
struct kv *split(const char *string,const size_t len,const char *sep){
	if (!string || strlen(string)<=0 || len<=0 || !sep || strlen(sep)<=0
			|| !*sep)
		return NULL;
	char *str=strndup(string,len);
	struct kv *pair=malloc(sizeof(struct kv));
	char *spl=strchr(str,sep[0]);
	if(spl==NULL) {
		free(str);
		release(pair);
		return NULL;
	}
	(*spl)='\0'; spl++;
	if(strlen(str)<=0){
		release(pair);
		return NULL;
	}
	pair->key=strndup(str,len);
	pair->value=strndup(spl,len);
	free(str);
	if(strlen(pair->key)<=0) {
		release(pair);
		return NULL;
	}
	if(strlen(pair->value)<=0){
		pair->value=strdup("");
	}
	return pair;
}

/* stack:  stack two arrays into one */
void stack(struct kv ***dest,struct kv **src){
	while(*src!=NULL){
		struct kv *value=unshift(&src);
		push(dest,value);
	}
	free(src);
	return;
}

/* unshift:  remove a value from the beginning of an array */
struct kv *unshift(struct kv ***array) {
	reverse(*array);
	struct kv *ret=pop(array);
	reverse(*array);
	return ret;
}

/* eof */