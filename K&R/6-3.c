//Fri Oct  1 15:13:59 CST 2010

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAXLEN 100

struct bintree {
        char *word;
        char *list;
        struct bintree *left;
        struct bintree *right;
};

static struct bintree *addtree(struct bintree *root, char *words, int line);
static int getwords(char *word, int *line, int len);
static void printtree(struct bintree *root);

int main(void)
{
        struct bintree *root = NULL;
        char wd[MAXLEN];
        int line = 1;
        while (getwords(wd, &line, MAXLEN) != EOF)
                if (isalpha(wd[0]))
                        root = addtree(root, wd, line);
        printtree(root);
        return(0);
}

static void printtree(struct bintree *root)
{
        if (root != NULL) {
                printtree(root->left);
                printf("%s: %s\n", root->word, root->list);
                printtree(root->right);
        }
}


static struct bintree *addtree(struct bintree *root, char *words, int line)
{
        int cond;
        char stmp[MAXLEN];
        if (root == NULL) {
                root = (struct bintree *) malloc(sizeof(struct bintree));
                root->word = (char *) malloc(strlen(words));
                strcpy(root->word, words);
                root->list = (char *) malloc(sizeof(char) * 100);
                sprintf(root->list, "%d, ", line);
        } else {
                if ((cond = strcmp(words, root->word)) < 0)
                        root->left = addtree(root->left, words, line);
                else if(cond > 0)
                        root->right = addtree(root->right, words, line);
                else {
                        sprintf(stmp, "%d, ", line);
                        strcat(root->list, stmp);
                }
        }
        return root;
}

static int getwords(char *word, int *line, int len)
{
        int ch, i = 0;
        while (isspace(ch = getc(stdin)) && ch != '\n')
                ;
        if (ch == EOF)
                return ch;
        if (ch == '\n') {
                //once mistake here
                (*line)++;
                return ch;
        }
        if (!isalpha(ch)) {
                word[0] = ch;
                return ch;
        }
        do {
                word[i++] = ch;
        } while (isalnum(ch = getc(stdin)));
        word[i] = '\0';
        ungetc(ch, stdin);
        return word[0];
}

        
        
        
