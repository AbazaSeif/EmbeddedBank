
/* BTSCLIB.H */

#ifndef BTSCLIB_H
#define BTSCLIB_H

#ifdef __cplusplus
extern "C" {
#endif


/* for ctype.h */
extern const char _ctype[];

/* for errno.h */
extern int errno;


/* ctype.h */
extern int isalnum(int);
extern int isalpha(int);
extern int isascii(int);
extern int iscntrl(int);
extern int isdigit(int);
extern int isgraph(int);
extern int islower(int);
extern int isprint(int);
extern int ispunct(int);
extern int isspace(int);
extern int isupper(int);
extern int isxdigit(int);
extern int tolower(int);
extern int toupper(int);
extern int toascii(int);

/* string.h */
extern void *memcpy(void *, const void *, size_t);
extern void *memmove(void *, const void *, size_t);
extern char *strcpy(char *, const char *);
extern char *strncpy(char *, const char *, size_t);
extern char *strcat(char *, const char *);
extern char *strncat(char *, const char *, size_t);
extern int  memcmp(const void *, const void *, size_t);
extern int  strcmp(const char *, const char *);
extern int  strncmp(const char *, const char *, size_t);
extern void *memchr(const void *, int, size_t);
extern char *strchr(const char *, int);
extern size_t strcspn(const char *, const char *);
extern char *strpbrk(const char *, const char *);
extern char *strrchr(const char *, int);
extern size_t strspn(const char *, const char *);
extern char *strstr(const char *, const char *);
extern char *strtok(char *, const char *);
extern void *memset(void *, int, size_t);
extern size_t strlen(const char *);

/* stdlib.h */
extern long strtol(const char *str, char **endptr, int base);
extern int atoi(const char *);
extern long int atol(const char *);
extern int rand(void);
extern void srand(unsigned int);
extern int abs(int);
extern long int labs(long int);


#ifdef __cplusplus
}
#endif

#endif	/* BTSCLIB_H */

/* */
