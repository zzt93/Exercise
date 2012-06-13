#ifndef _SORT_H_
#define _SORT_H_

#define L(x) x * 2 + 1
#define R(x) x * 2 + 2
#define P(x) (x - 1) / 2


static inline void genfile(char *filename, int size)
{
        FILE *fp = fopen(filename, "w+");
        srand((unsigned) time(NULL));
        for (int i = 0; i < size; i++)
                fputc((97 + rand() % 26), fp);
        fclose(fp);
}

static inline void writefile(char *data, int size)
{
        FILE *fp = fopen("out", "w+");
        for (int i = 0; i < size; i++)
                fputc(data[i], fp);
        fclose(fp);
        free(data);
}

static inline int readfile(char *filename, char **data)
{
        FILE *fp = fopen(filename, "r");
        fseek(fp, 0, SEEK_END);
        int filesize = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        *data = (char *) malloc(filesize);
        for (int i = 0; i < filesize; i++)
                (*data)[i] = fgetc(fp);
        fclose(fp);
        return filesize;
}
        
      
static inline void exchange(char *a, char *b)
{
        char t = *a;
        *a = *b;
        *b = t;
}
                




#endif
