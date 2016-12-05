#include <stdio.h>
#include "List.h"
#include <malloc.h>
#include <stdlib.h>

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
//    free(self->data);
    free(self);
}


//adding new Node to list
void myAddNode(struct List *self, int data)
{


    struct Node *newNode;
    newNode=(struct Node*)malloc(sizeof(struct Node));
    if(NULL==newNode)
    {
        perror("Failed to allocate memory");
        exit(1);
    }
    newNode->data = data; 
    /*newNode->data = (char*)malloc(strlen(data)*sizeof(char));
    if(NULL==newNode->data)
    {
        perror("Failed to allocate memory");
        exit(1);
    }*/
    /*
    int i=0;
    while(i<strlen(data))
    {
        newNode->data[i]=data[i];
        i++;
    }*/
    newNode->next = NULL;
    self->size++;
    newNode->lvl=self->size;


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

void set(FILE *file, struct List *myList)
{
    int digit=0;
    int c=0;
    
    while(EOF!=c)
    {
        c=fgetc(file);
        if(44==c || 125==c)
        {
            myList->addNode(myList, digit);
            digit=0;
        }
        else if(123==c)
        {
            //skip
        }
        else
        {
            digit=digit*10+(c-48);
        }
        
    }
    fclose(file);
}

void print(struct List *myList)
{
    FILE *outtxt;
    int levels=myList->size;
    outtxt=fopen("output.txt", "w");
    struct Node *tmp=myList->head;
    struct Node *tmp2;
    fprintf(outtxt, "{}");
    int i;
    int j;
    int h;
    for(i=1; i<=levels; i++)
    {

        while(NULL!=tmp)
        {
            if(1==i)
            {
                fprintf(outtxt, ",{%d}", tmp->data);
                tmp=tmp->next;
            }
            else
            {
                if(tmp->lvl>levels-i+1)
                {
                    break;
                }
                tmp2=tmp->next;
                for(j=0;j<=levels-i;j++)
                {
                    if(NULL==tmp2)
                    {
                        break;
                    }
                    fprintf(outtxt, "{%d",tmp->data);
                    for(h=1; h<i; h++)
                    {
                        if(NULL==tmp2)
                        {
                            break;
                        }
                        fprintf(outtxt, ",%d", tmp2->data);
                        tmp2=tmp2->next;
                    }
                    fprintf(outtxt, "}");



                }


                tmp=tmp->next;



            }
        }
        tmp=myList->head;


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
    ret->size=0;
    ret->addNode = myAddNode;
    return ret;   
};

int main(int argc, char* argv[])
{

    //checking user passes correct number of arguments
    if(2!=argc)
    {
        perror("Wrong amount of arguments. Give just two files name.\n");
        return 1;
    }

    //file opening and checking if opened correctly
    FILE *setTxt;
    setTxt=fopen(argv[1],"r");
    if(NULL==setTxt)
    {
        perror("Cannot open given file.\n");
        return 1;
    }


    struct List *myList=constructList();

    set(setTxt, myList);

    print(myList);

    destructorList(myList);

    return 0;
}
