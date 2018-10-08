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
{ int poz=0;
  while (n != NULL)
  {
	 if(n->data == x) return poz;
     n = n->next;
     poz++;
  }
  return -1;
}

int Find_poz(struct Node *n, int x)
{ int poz=0;
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
{ int poz=0;
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
    int poz=1, a;
    a=new_data;
    if (x==0)
    {
        Inser_start(&head, a);
        return;
    }
    while (n != NULL){
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

int main()
{
    head = NULL;
    Inser_start(&head, 8);
	inser_fin(&head, 9);
	inser_fin(&head, 2);
	printf ("%d \n", Find_poz(head, 1));
	printf ("%d \n", Find_val(head, 4));
	insertAfter_val(head, 7, 2);
	insertAfter_poz(head, 5, 1);
	insertOn_poz(head,10,2);
	printList(head);
    return 0;
}
