#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int data;
    struct Node *next;
} *head, *tail;


void printList(struct Node *n)
{
    while (n != NULL)
    {
        printf(" %d ", n->data);
        n = n->next;
    }
}

void Inser_start(struct Node** head_ref, int new_data)
{
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->data  = new_data;
    if ((*head_ref) == NULL)
    {
        (*head_ref) = new_node;
        (*head_ref)->next=NULL;
        tail=new_node;
        return;
    }
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void inser_fin(struct Node** head_ref, int new_data)
{
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->data  = new_data;
    new_node->next = NULL;
    if (*head_ref == NULL)
    {
        *head_ref = new_node;
        tail=new_node;
        return;
    }
    tail->next = new_node;
    tail=new_node;
    return;
}

int Find_val(struct Node *n, int x)
{ int poz=1;
    while (n != NULL)
    {
        if(n->data == x) return poz;
        n = n->next;
        poz++;
    }
    return -1;
}

int Find_poz(struct Node *n, int x)
{ int poz=1;
    while (n != NULL)
    {
        if(poz == x) return (n->data);
        n = n->next;
        poz++;
    }
    return -1;
}

void insertAfter_val(struct Node *n, int new_data, int x)
{
    while (n != NULL)
    {
        if(n->data == x)
        { if (n->next==NULL)
            {
                struct Node* new_node =(struct Node*) malloc(sizeof(struct Node));
                new_node->data  = new_data;
                new_node->next = n->next;
                n->next = new_node;
                inser_fin(&head, new_data);
            }

            else {
                struct Node* new_node =(struct Node*) malloc(sizeof(struct Node));
                new_node->data  = new_data;
                new_node->next = n->next;
                n->next = new_node;
                return;
            }
        }
        n = n->next;
    }
}

void insertAfter_poz(struct Node *n, int new_data, int x)
{ int poz=1;
    while (n != NULL)
    {
        if(poz == x)
        { if (n->next==NULL)
            {
                struct Node* new_node =(struct Node*) malloc(sizeof(struct Node));
                new_node->data  = new_data;
                new_node->next = n->next;
                n->next = new_node;
                inser_fin(&head, new_data);
            }

            else {
                struct Node* new_node =(struct Node*) malloc(sizeof(struct Node));
                new_node->data  = new_data;
                new_node->next = n->next;
                n->next = new_node;
                return;
            }
        }
        poz++;
        n = n->next;
    }
}

void insertOn_poz(struct Node *n, int new_data, int x)
{
    int poz=2, a;
    a=new_data;
    while (n != NULL){
        if (x==1)
        {
            Inser_start(&head, a);
            return;
        }
        if(poz == x)
        {
            struct Node* new_node =(struct Node*) malloc(sizeof(struct Node));
            new_node->data  = new_data;
            new_node->next = n->next;
            n->next = new_node;
            return;
        }
        poz++;
        n = n->next;
    }
}

void delete_val(struct Node **head_ref, int k)
{
    struct Node* temp = *head_ref, *prev;
    if (temp != NULL && temp->data == k)
    {
        *head_ref = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->data != k)
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return;
    if (temp == tail) tail = prev;
    prev->next = temp->next;
    free(temp);
}

void delete_poz(struct Node **head_ref, int p)
{  int i;
    if (*head_ref == NULL)
        return;
    struct Node* temp = *head_ref;
    if (p == 1)
    {
        *head_ref = temp->next;
        free(temp);
        return;
    }
    for (i=1; temp!=NULL && i<p-1; i++)
        temp = temp->next;
    if (temp == NULL || temp->next == NULL)
        return;
    struct Node *next = temp->next->next;
    if (temp->next == tail) tail = temp;
    free(temp->next);
    temp->next = next;
}

int main()
{
    head = NULL;

    printList(head);
    Inser_start(&head, 1);
    Inser_start(&head, 2);
    Inser_start(&head, 3);
//	printList(head);
    inser_fin(&head, 4);
//	printList(head);
//	printf("\n");
/*	printf ("%d \n", Find_val(head, 5));
	printf ("%d \n", Find_val(head, 1));
	printf ("%d \n", Find_poz(head, 5));
	printf ("%d \n", Find_poz(head, 3));
*/
    delete_poz(&head, 1);
    //printList(head);
    delete_poz(&head, 1);
    //printList(head);
    delete_val(&head, 4);
//	printList(head);
    inser_fin(&head, 5);
    printList(head);
/*	delete_val(&head, 1);
    delete_poz(&head, 1);
    printList(head);
	printf(" \n");
	inser_fin(&head, 8);
     printList(head);
	printf(" \n");
  */  return 0;
}
