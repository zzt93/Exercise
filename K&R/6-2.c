//Fri Oct  1 13:47:53 CST 2010
//not implemented
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXLEN 100

struct bintree {
        char *word;
        int count;
        struct bintree *left;
        struct bintree *right;
};
static int getword(char *word, int n);
static struct bintree *addtree(struct bintree *root, char *word);
static void printtree(struct bintree *root);

int main(int argc, char *argv[])
{
        int n;
        char word[MAXLEN];
        struct bintree *root = NULL;
        n = atoi(argv[1]);
        while (getword(word, MAXLEN) != EOF)
                if (isalpha(word[0]))
                        //must use the return value here!
                        root = addtree(root, word);
        printtree(root);
        return(0);
}
//also another version
static void printtree(struct bintree *root)
{
        if (root->left)
                printtree(root->left);
        printf("%4d %s\n", root->count, root->word);
        if (root->right)
                printtree(root->right);
}


static struct bintree *addtree(struct bintree *root, char *word)
{
        int cond;
        if (root == NULL) {
                root = (struct bintree *) malloc(sizeof(struct bintree));
                root->word = (char *) malloc(strlen(word) + 1);
                strcpy(root->word, word);
                root->count = 1;
                root->left = root->right = NULL;
        } else {
                if ((cond = strcmp(word, root->word)) < 0)
                        //imp
                        root->left = addtree(root->left, word);
                else if(cond > 0)
                        root->right = addtree(root->right, word);
                else
                        root->count++;
        }
        return root;
}

static int getword(char *word, int n)
{
        int ch, pch, i = 0;
        while (isspace(ch = getc(stdin)))
                ;
        switch (ch) {
        case '"':
                while ((ch = getc(stdin)) != '"' && ch != EOF)
                        ;
                break;
        case '/':
                if ((ch = getc(stdin)) != '*') {
                        ungetc(ch, stdin);
                        word[0] = '*';
                        return word[0];
                } else
                        while ((ch = getc(stdin)) != EOF) {
                                if (pch == '*' && ch == '/') {
                                        word[0] = '*';
                                        return word[0];
                                }
                                pch = ch;
                        }
        }
        if (ch == EOF)
                return ch;
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

