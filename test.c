#define BTRSTRINGS_IMPLEMENTATION
#include "btrstrings.h"

#include <stdio.h>

int main() {
    FILE *f = fopen(__FILE__, "r");
    if(f == NULL) return 1;

    fseek(f, 0, SEEK_END);
    size_t len = ftell(f);
    char *buf = malloc(len);
    rewind(f);
    fread(buf, 1, len, f);

    fclose(f);

    int totallines = 1;
    for(size_t i=0;i<len;i++) 
        if(buf[i] == '\n') totallines++;

    int log10 = 0;
    while(totallines) {
        totallines /= 10;
        log10++; 
    }

    BTRSTRING(str_stdio, "#include <stdio.h>");

    BTRSTRING_LEN(lines, buf, len);
    int linecount = 0;
    while(lines.len) {
        linecount++;
        BTRSTRING_T line = NULLSTR;
        btrslicebydelim(&line, &lines, '\n');
        printf("%*d | %.*s\n", log10, linecount, (int) line.len, line.str);
        btrtrim(&line);
        int cmp_stdio = btrstrcmp(&line, &str_stdio);
        if(!cmp_stdio) 
            printf("%*d | // We're importing stdio here!\n", log10, linecount);
    }

    btrfree(&lines);

    return 0;
}
