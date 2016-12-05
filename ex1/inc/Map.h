#include <stdio.h>

struct Map{
    void (*addNode)(struct Map *self, char *data);
    struct Node *head;
};

struct Node{
    char *data;
    int value;
    struct Node *next;
};

struct Map *constructMap(void);
void destructorMap(struct Map*);
void destructorNode(struct Node*);
