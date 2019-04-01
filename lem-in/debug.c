#include <stdio.h>
#include <dlfcn.h>

extern void abort();

void *malloc(int size) {
	void * (*ptr)(int);
	void * handle = (void*) -1;
	ptr = (void *) dlsym(handle, "malloc");
	if (ptr == NULL) {
		printf("Opps\n");
		abort();
	}
	void *alloc = (*ptr)(size);
	printf("Alloc = %p Size: %d\n", alloc, size);
	return alloc;
}

void *realloc(void *alloc, int size) {
	void * (*ptr)(void *, int);
	void * handle = (void*) -1;
	ptr = (void *) dlsym(handle, "malloc");
	if (ptr == NULL) {
		printf("Opps\n");
		abort();
	}
	alloc = (*ptr)(alloc, size);
	printf("Realloc = %p Size: %d\n", alloc, size);
	return alloc;
}

void free(void *alloc) {
	if (alloc == NULL)
		return;
	printf("free %p\n", alloc);
	void * (*ptr)(void *);
	void * handle = (void *) -1;
	ptr = (void *) dlsym(handle, "free");
	if (ptr == NULL)
		abort();

	(*ptr)(alloc);
}
