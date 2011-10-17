//Fri Oct  1 16:50:02 CST 2010

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAXLEN 100

struct bitree 
{
        char *word;
        int count;
        struct bitree *left;
        struct bitree *right;
};
static int getword(char *word, int len);
static struct bitree *transtree(struct bitree *dest, const struct bitree *src);
static void printtree(const struct bitree *root);
static struct bitree *addtreestr(struct bitree *root, const char *word);
static struct bitree *addtreenum(struct bitree *root, const struct bitree *node);

int main(void)
{
        char word[MAXLEN];
        struct bitree *rootstr = NULL, *rootnum = NULL;
        
        while (getword(word, MAXLEN) != EOF)
                if (isalpha(word[0]))
                        rootstr = addtreestr(rootstr, word);
        printtree(rootstr);
        printf("--------------\n");
        rootnum = transtree(rootnum, rootstr); 
        printtree(rootnum);
        return(0);
}
//pay attention
static struct bitree *transtree(struct bitree *dest, const struct bitree *src)
{
        if (src != NULL) {
                dest = addtreenum(dest, src);
                transtree(dest, src->left);
                transtree(dest, src->right);
        }
        return dest;
}

static void printtree(const struct bitree *root)
{
        if (root != NULL) {
                printtree(root->left);
                printf("%s: %d\n", root->word, root->count);
                printtree(root->right);
        }
}


static struct bitree *addtreestr(struct bitree *root, const char *word)
{
        int cond;
        if (root == NULL) {
                root = (struct bitree *) malloc(sizeof(struct bitree));
                root->word = (char *) malloc(sizeof(char) * MAXLEN);
                strcpy(root->word, word);
                root->count = 1;
                root->right = root->left = NULL;
        } else {
                if ((cond = strcmp(word, root->word)) < 0)
                        root->left = addtreestr(root->left, word);
                else if (cond > 0)
                        root->right = addtreestr(root->right, word);
                else
                        root->count++;
        }
        return root;
}

static int getword(char *word, int len)
{
        int ch,i = 0;
        while (isspace(ch = getc(stdin)))
                ;
        if (ch == EOF)
                return ch;
        if (!isalpha(ch)) {
                word[0] = ch;
                return word[0];
        }
        do {
                word[i++] = ch;
        } while (isalpha(ch = getc(stdin)));
        word[i] = '\0';
        ungetc(ch, stdin);
        return ch;
}

static struct bitree *addtreenum(struct bitree *root, const struct bitree *node)
{
        int cond;
        if (root == NULL) {
                root = (struct bitree *) malloc(sizeof(struct bitree));
                root->word = (char *) malloc(sizeof(char) * MAXLEN);
                strcpy(root->word, node->word);
                root->count = node->count;
                root->right = root->left = NULL;
        } else {
                if ((cond = node->count - root->count) >= 0)
                        root->left = addtreenum(root->left, node);
                else
                        root->right = addtreenum(root->right, node);
        }
        return root;
}

                
        
        
