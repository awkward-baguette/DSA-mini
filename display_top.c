#include <stdio.h>
#include <stdlib.h>


struct node
{
	int key;
	float pty_cgpa;
	struct node *link;
};
typedef struct node node_t;

struct list
{
	node_t *head;
};
typedef struct list list_t;

void pqinsert(list_t*p,studentnode*s){
    int r_no=s->roll_no;
    float cgpa=compute_cgpa(s->semhead);
    node_t *temp,*pres,*prev;
    pres=p->head;
    prev=NULL;
    temp=(node_t*)malloc(sizeof(node_t));
		temp->key = r_no;
        temp->pty_cgpa=cgpa;
        temp->link=NULL;
    if(p->head==NULL){
        p->head=temp;
    }
    else{ 
        while ((pres!=NULL) && (pres->pty_cgpa>=cgpa)){
            prev=pres;
            pres=pres->link; 
        }
        if(pres==NULL){
            prev->link=temp;
        }
        else if(prev==NULL){
            temp->link=pres;
            p->head=temp;
        }
        else{
            temp->link=pres;
            prev->link=temp;
        }
    }
}

node_t pqdelete(list_t *ptr_list)
{
	node_t temp, *pres;
	if(ptr_list->head==NULL)
	{
		printf("Empty queue..Cannot delete");
		temp.key=-1;
		temp.pty_cgpa=-1;
	}
	else
	{
	  pres=ptr_list->head;
	  temp.key= pres->key;
	  temp.pty_cgpa=pres->pty_cgpa;
	  if(pres->link==NULL) 
		  ptr_list->head =NULL;
	  else
		   ptr_list->head=pres->link; 
	   free(pres);
       return temp;
	}
}	

void qdisplay(list_t *ptr_list, studentnode*s)
 {
	    node_t *pres;
	    pres = ptr_list->head;

    	if(pres==NULL) //if empty list
	       printf("\nThe list is empty\n");
	   else
 	     {		
    	   printf("\n");
	      while(pres!=NULL)
	     {
		    printf("name= %s->",s->name);
			printf("cgpa = %d->",pres->pty_cgpa);
			printf("\n");
		    pres=pres->link;
	      }
	}
 }
