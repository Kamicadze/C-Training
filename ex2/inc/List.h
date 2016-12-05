struct List{
    void (*addNode)(struct List *self, char *data);
    struct Node *head;
};

struct Node{
    char *data;
    struct Node *next;
};

struct List *constructList(void);
void destructorList(struct List*);
void destructorNode(struct Node*);
