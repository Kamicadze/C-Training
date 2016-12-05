#include <stdio.h>
#include <errno.h>
#include <malloc.h>
#include <string.h>
#include "Map.h"
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>

//free map allocation and all her nodes 
void destructorMap(struct Map *self)
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


//adding new Node to map
void myAddNode(struct Map *self, char *data)
{
    int flag=0;
    //checking if there is any node in. If not add head
    if(NULL==self->head)
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
        newNode->value = 1;
        newNode->next = NULL;
        self->head = newNode;
    }
    else  //if there is any node check if it has same data as existing ones
    {

        struct Node *tmp = self->head;
        while(1)
        {
            int cmp=strcmp(tmp->data, data);
            if(0==cmp)
            {
                tmp->value+=1;
                flag=1;
                break;
            }
            if(NULL==tmp->next)
            {
                break;
            }
            else
            {
                tmp=tmp->next;
            }
        }
        if(0==flag) //if there was no data same as this just add new node at the end
        {
            struct Node *newNode;
            newNode=(struct Node*)malloc(sizeof(struct Node));
            if(NULL==newNode)
            {
                perror("Failed to allocate memory");
                exit(1);
            }
            newNode->data = (char*)malloc(strlen(data)*sizeof(char));
            int i=0;
            while(i<strlen(data))
            {
                newNode->data[i]=data[i];
                i++;
            }
            newNode->value = 1;
            newNode->next = NULL;

            tmp->next=newNode;
        }
    }
}

//Printing interiors of Map
void printMap(struct Map *self)
{
    FILE *outtxt;
    outtxt=fopen("output.txt","w");
    struct Node *tmp = self->head;
    while(NULL!=tmp)
    {
        fprintf(outtxt, "%s %d \n", tmp->data, tmp->value);
        tmp=tmp->next;
    }
    fclose(outtxt);
}

//Creating blank map
struct Map *constructMap(void) {
    struct Map *ret = malloc(sizeof(struct Map));
    ret->head=NULL;
    ret->addNode = myAddNode;
    return ret;   
};

//Read words from file and add them to map
void sort(struct Map *oMap, FILE *intxt)
{
    char *str=NULL;
    ssize_t read;
    size_t len=0;

    //read file line by line
    while(-1!=(read=getline(&str, &len, intxt)))
    {

        int wordStart=0;
        int wordEnd=0;
        int i;
        int strSize=0;
        for(i=0; i<read; i++)
        {
            str[i]=tolower(str[i]);
            if(97<=str[i] && 122>=str[i])
            {
                wordEnd=i;
            }
            else if(0<(wordEnd-wordStart))
            {
                strSize=wordEnd-wordStart+1;
                char cpStr[strSize];
                int j;
                for(j=0; j<strSize; j++)
                {
                    cpStr[j]=str[j+wordStart];
                }
                oMap->addNode(oMap, cpStr);

                wordStart=i+1;
                memset(cpStr, 0, strlen(cpStr));

            }
            else
            {
                wordStart=i+1;
            }

        }
        //free the pointer and set it fo null for getline to automaticly allocate memory for new line
        free(str);
        str=NULL;
    }
    free(str);
}

int main(int argc, char* argv[])
{

    //checking user passes correct number of arguments
    if(2!=argc)
    {
        perror("Wrong amount of arguments. Give just one file name.\n");
        return 1;
    }

    //file opening and checking if opened correctly
    FILE *intxt;
    intxt=fopen(argv[1],"r");
    if(NULL==intxt)
    {
        perror("Cannot open given file.\n");
        return 1;
    }


    struct Map *myMap=constructMap();

    sort(myMap, intxt);

    printMap(myMap);

    destructorMap(myMap);

    fclose(intxt);
    return 0;
}
