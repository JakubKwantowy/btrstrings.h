#ifndef BTRSTRINGS_H
#define BTRSTRINGS_H

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Gets the length of a btrstring.
 * 
 * @param s String
 */
#define btrstrlen(s) ((s)->len)
/**
 * Declares a btrstring and initializes it with a C-string.
 * 
 * @param bs btrstring name
 * @param s C-string
 */
#define BTRSTRING(bs, s) BTRSTRING_T bs = btrstr2((s))
/**
 * Declares a btrstring and initializes it with a buffer and it's length.
 * 
 * @param s btrstring name
 * @param b buffer
 * @param l length
 */
#define BTRSTRING_LEN(s, b, l) BTRSTRING_T s = { .str = b, .len = l, .base = b }
/**
 * Null btrstring (when declaring btrstrings without a value initialize them with this).
 */
#define NULLSTR {0}

typedef struct BtrString {
    char *str;
    size_t len;
    char *base;
} BTRSTRING_T;

/**
 * Sets a btrstring to a C-string.
 * 
 * @param bs btrstring
 * @param s C-string
 */
extern void btrstr(BTRSTRING_T *bs, char *s);
/**
 * Creates a btrstring from a C-string and returns it.
 * 
 * @param s C-string
 */
extern BTRSTRING_T btrstr2(char *s);
/**
 * Converts a btrstring to a C-string.
 * 
 * @param bs btrstring
 * @param s C-string buffer
 * @param n C-string buffer size
 */
extern void btrtocstr(BTRSTRING_T *bs, char *s, size_t n);
/**
 * Frees a btrstring allocated with malloc.
 * The base of a btrstring is used.
 * 
 * @param s btrstring
 */
extern void btrfree(BTRSTRING_T *s);

/**
 * Removes n characters from the left of a btrstring.
 * 
 * @param s btrstring
 * @param n character count
 */
extern void btrsliceleft(BTRSTRING_T *s, size_t n);
/**
 * Removes n characters from the right of a btrstring.
 * 
 * @param s btrstring
 * @param n character count
 */
extern void btrsliceright(BTRSTRING_T *s, size_t n);
/**
 * Removes l characters from the left and r characters from the right of a btrstring.
 * 
 * @param s btrstring
 * @param l left character count
 * @param r right character count
 */
extern void btrslice(BTRSTRING_T *s, size_t l, size_t r);
/**
 * Removes all whitespace from the left of a btrstring.
 * 
 * @param s btrstring
 */
extern void btrtrimleft(BTRSTRING_T *s);
/**
 * Removes all whitespace from the right of a btrstring.
 * 
 * @param s btrstring
 */
extern void btrtrimright(BTRSTRING_T *s);
/**
 * Removes all whitespace from the left and right of a btrstring.
 * 
 * @param s btrstring
 */
extern void btrtrim(BTRSTRING_T *s);
/**
 * Slices a btrstring via a delimiter.
 * d contains the portion before the delimiter
 * s contains the portion after the delimiter
 * 
 * @param d destination btrstring
 * @param s source btrstring
 * @param de delimiter
 */
extern void btrslicebydelim(BTRSTRING_T *d, BTRSTRING_T *s, char de);
/**
 * Allocates a new btrstring with the data from a different btrstring.
 * 
 * @param d destination btrstring
 * @param s source btrstring
 */
extern size_t btrstrdup(BTRSTRING_T *d, BTRSTRING_T *s);
/**
 * Concatenates two string and allocates a third string that contains the data.
 * 
 * @param d destination btrstring
 * @param s1 source btrstring
 * @param s2 source btrstring
 */
extern size_t btrstrcat(BTRSTRING_T *d, BTRSTRING_T *s1, BTRSTRING_T *s2);
/**
 * Compares two btrstrings.
 * Returns 0 when they're equal.
 * Returns 1 when they're different.
 * 
 * @param s1 btrstring
 * @param s2 btrstring
 */
extern int btrstrcmp(BTRSTRING_T *s1, BTRSTRING_T *s2);

#ifdef BTRSTRINGS_IMPLEMENTATION

void btrstr(BTRSTRING_T *bs, char *s) {
    bs->base = s;
    bs->str = s;
    bs->len = strlen(s);
}

BTRSTRING_T btrstr2(char *s) {
    BTRSTRING_T bs;

    bs.base = s;
    bs.str = s;
    bs.len = strlen(s);

    return bs;
}

void btrtocstr(BTRSTRING_T *bs, char *s, size_t n) {
    if(bs->str == NULL) return;
    size_t l = btrstrlen(bs);
    if(l > n - 1) l = n - 1;
    for(size_t i=0;i<l;i++) {
        s[i] = bs->str[i];
    }
    s[l] = 0;
}

void btrfree(BTRSTRING_T *s) {
    if(s->base == NULL) return;
    free(s->base);
    s->base = NULL;
    s->str = NULL;
    s->len = 0;
}

void btrsliceleft(BTRSTRING_T *s, size_t n) {
    if(s->str == NULL) return;
    if(s->len < n) n = btrstrlen(s);
    if(n == 0) return;
    s->str += n;
    s->len -= n;
}

void btrsliceright(BTRSTRING_T *s, size_t n) {
    if(s->str == NULL) return;
    if(s->len < n) n = btrstrlen(s);
    if(n == 0) return;
    s->len -= n;
}

void btrslice(BTRSTRING_T *s, size_t l, size_t r) {
    if(s->str == NULL) return;
    btrsliceleft(s, l);
    btrsliceright(s, r);
}

size_t btrstrdup(BTRSTRING_T *d, BTRSTRING_T *s) {
    if(s->str == NULL) return 0;

    d->len = btrstrlen(s);
    if(s->len == 0) return 0;
    char *st = malloc(btrstrlen(s));
    if(st == NULL) return 0;
    d->base = st;
    d->str = st;

    for(size_t i=0;i<btrstrlen(s);i++)
        st[i] = s->str[i];

    return btrstrlen(s);
}

size_t btrstrcat(BTRSTRING_T *d, BTRSTRING_T *s1, BTRSTRING_T *s2) {
    if(s1->str == NULL) return 0;
    if(s2->str == NULL) return 0;

    size_t l = btrstrlen(s1) + btrstrlen(s2);
    d->len = l;
    if(l == 0) return 0;
    char *s = malloc(l);
    if(s == NULL) return 0;
    d->base = s;
    d->str = s;

    for(size_t i=0;i<btrstrlen(s1);i++)
        s[i] = s1->str[i];

    for(size_t i=0;i<btrstrlen(s2);i++)
        s[i + btrstrlen(s1)] = s2->str[i];

    return l;
}

void btrtrimleft(BTRSTRING_T *s) {
    if(s->str == NULL) return;
    while(btrstrlen(s) && isspace(s->str[0]))
        btrsliceleft(s, 1);
}

void btrtrimright(BTRSTRING_T *s) {
    if(s->str == NULL) return;
    while(btrstrlen(s) && isspace(s->str[s->len-1]))
        btrsliceright(s, 1);
}

void btrtrim(BTRSTRING_T *s) {
    btrtrimleft(s);
    btrtrimright(s);
}

void btrslicebydelim(BTRSTRING_T *d, BTRSTRING_T *s, char de) {
    if(s->str == NULL) return;
    size_t i = 0;
    while(i < btrstrlen(s) && s->str[i] != de) i++;
    
    if(i < btrstrlen(s)) {
        d->base = s->base;
        d->str = s->str;
        d->len = i;

        btrsliceleft(s, i + 1);
        return;
    }

    *d = *s;
    s->len = 0;
}

int btrstrcmp(BTRSTRING_T *s1, BTRSTRING_T *s2) {
    if(btrstrlen(s1) != btrstrlen(s2)) return 1;
    if(s1->str == s2->str) return 0;
    if(s1->str == NULL) return 1;
    if(s2->str == NULL) return 1;
    
    for(size_t i=0;i<btrstrlen(s1);i++) 
        if(s1->str[i] != s2->str[i]) return 1;

    return 0;
}

#endif

#endif
