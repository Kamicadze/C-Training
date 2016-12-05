struct List{
    void (*addNode)(struct List *self, int data);
    struct Node *head;
    int size;
};

struct Node{
    int data;
    int lvl;
    struct Node *next;
};

struct List *constructList(void);
void destructorList(struct List*);
void destructorNode(struct Node*);
