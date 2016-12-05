#include <stdio.h>
#include "List.h"
#include <stdlib.h>
#include <string.h>

//free list allocation and all her nodes 
void destructorList(struct List *self)
{
    destructorNode(self->head);
    free(self);
}

//requrently freeing all nodes and thier data
void destructorNode(struct Node *self)
{
    if(NULL!=self->next)
    {
        destructorNode(self->next);
    }
    free(self->data);
    free(self);
}


//adding new Node to list
void myAddNode(struct List *self, char *data)
{


    struct Node *newNode;
    newNode=(struct Node*)malloc(sizeof(struct Node));
    if(NULL==newNode)
    {
        perror("Failed to allocate memory");
        exit(1);
    }
    newNode->data = (char*)malloc(strlen(data)*sizeof(char));
    if(NULL==newNode->data)
    {
        perror("Failed to allocate memory");
        exit(1);
    }

    int i=0;
    while(i<strlen(data))
    {
        newNode->data[i]=data[i];
        i++;
    }
    newNode->next = NULL;

    //checking if there is any node in. If not add head
    if(NULL==self->head)
    {

        self->head = newNode;
    }

    else  //else add at the end
    {

        struct Node *tmp = self->head;
        while(NULL!=tmp->next)
        {
            tmp=tmp->next;
        }

        tmp->next=newNode;
    }
}

void templateWords(FILE *wordsTxt, struct List *myList)
{
    char *str=NULL;
    ssize_t read;
    size_t len=0;
    int delim=32;

    while(-1!=(read=getdelim(&str, &len, delim, wordsTxt)))
    {

        if(44==str[read-2])
        {
            str[read-2]='\0';
        }
        myList->addNode(myList, str);

        free(str);
        str=NULL;
    }
    free(str);
}

void compare(FILE *sentenceTxt, struct List *myList)
{
    int line=0;
    int flag=0;
    struct Node *tmp;
    FILE *outtxt;
    outtxt=fopen("output.txt", "w");
    char *word;
    char *str=NULL;
    ssize_t read;
    size_t len=0;

    int start=0;
    int end=0;
    char *pch;
    int i;

    //read file line by line
    while(-1!=(read=getline(&str, &len, sentenceTxt)))
    {
        line++;
        pch=strchr(str, 32);
        while(NULL!=pch)
        {
            end=pch-str;
            word=(char*)malloc((end-start)*sizeof(char));
            if(NULL==word)
            {
                perror("Failed to allocate memory");
                exit(1);
            }

            for(i=0; i<(end-start); i++)
            {
                word[i]=str[i+start];
            }
            tmp=myList->head;
            while(NULL!=tmp)
            {
                if((0==strcmp(word, tmp->data)) && (strlen(word)==(strlen(tmp->data))))
                {
                    flag=1;
                    break;
                }
                tmp=tmp->next;
            }
            if(0==flag)
            {
                fprintf(outtxt, "%d %s \n", line, word);
            }
            flag=0;
            start=end+1;
            free(word);
            word=NULL;

            pch=strchr(pch+1, 32);
        }
        if(start<read)
        {
            end=read-2;
            word=(char*)malloc((end-start)*sizeof(char));
            if(NULL==word)
            {
                perror("Failed to allocate memory");
                exit(1);
            }
            for(i=0; i<(end-start); i++)
            {
                word[i]=str[i+start];
            }
            tmp=myList->head;
            while(NULL!=tmp)
            {
                if((0==strcmp(word, tmp->data)) && (strlen(word)==(strlen(tmp->data))))
                {
                    flag=1;
                    break;
                }
                tmp=tmp->next;
            }
            if(0==flag)
            {
                fprintf(outtxt, "%d %s \n", line, word);
            }
            free(word);
        }
        free(str);
    }
    fclose(outtxt);
}

//Creating blank list
struct List *constructList(void) {
    struct List *ret = malloc(sizeof(struct List));
    if(NULL==ret)
    {
        perror("Failed to allocate memory");
        exit(1);
    }
    ret->head=NULL;
    ret->addNode = myAddNode;
    return ret;   
};

int main(int argc, char* argv[])
{

    //checking user passes correct number of arguments
    if(3!=argc)
    {
        perror("Wrong amount of arguments. Give just two files name.\n");
        return 1;
    }

    //file opening and checking if opened correctly
    FILE *wordsTxt;
    wordsTxt=fopen(argv[1],"r");
    if(NULL==wordsTxt)
    {
        perror("Cannot open given file.\n");
        return 1;
    }


    struct List *myList=constructList();

    templateWords(wordsTxt, myList);
    fclose(wordsTxt);


    FILE *sentenceTxt;
    sentenceTxt=fopen(argv[2], "r");
    if(NULL==sentenceTxt)
    {
        perror("Cannot open given file.\n");
        return 1;
    }
    compare(sentenceTxt, myList);

    destructorList(myList);

    fclose(sentenceTxt);
    return 0;
}
