#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define SUBJECTS 6
#define MAXHISTORY 10

typedef struct subject{
    int credit;
    char name;
    int marks;
    char grade;
}subnode;

typedef struct sem{
    int semno;
    subnode sublist[SUBJECTS];
    float sgpa;
    struct sem* next;
}semnode;

typedef struct gradehistory{
    int semno;
    char subname[20];
    int oldmarks;
    int newmarks;
    char oldgrade;
    char newgrade;
}historynode;

typedef struct snode
{
  int roll_no;
  char name[50];
  semnode *semhead;
  historynode history[MAXHISTORY];
  int historylength;
  struct tnode *left;
  struct tnode *right;
}studentnode;


typedef struct tree
{
	studentnode *root;
}tree;
  
void init(tree *t)
{
     t->root=NULL;
}	 

studentnode *create_snode(int r_no, char *sname)
{
	studentnode *node = (studentnode*)malloc(sizeof(studentnode));
	node->roll_no = r_no;
	strcpy(node->name,sname);
	node->semhead = node->left = node->right = NULL;
	node->historylength = -1;
	return node;
}
	
void addsem(tree *t, int semno, subnode *subjects)
{
	semnode *temp = (semnode*)malloc(sizeof(semnode));
	temp->semno = semno;
	for(int i=0; i<SUBJECTS; i++)
		temp->sublist[i]=subjects[i];
	temp->sgpa = find_sgpa(subjects);
	temp->next=NULL;

	if(t->root==NULL)
	{
		printf("Please create a student first\n");
		return;
	}

	studentnode *pres = t->root;
	temp->next = pres->semhead;
	pres->semhead = temp;
}

void add_new_student(tree *t,char *sname, int roll_no)
{
	studentnode *temp = create_snode(roll_no,sname);
	studentnode *pres = t->root, *prev = NULL;
	
	if(t->root ==NULL) //if empty tree ?
	    t->root=temp;
	else  
	{
	while(pres!=NULL)
		{
			prev=pres;
			if(roll_no>pres->r_no)
				pres=pres->right; //move right
			else
				pres=pres->left; // move left;
		}
	if(x>prev->data) // attach temp to left or right of prev
        prev->right=temp;
	else
		prev->left=temp;
	}

}

void addmarks(tree *t,char *sname, int roll_no, int semno, char *subname, float marks)
{
	studentnode *pres = t->root;
	if(pres==NULL)
	{
		
	}


	/*typedef struct subject{
    int credit;
    char name;
    int marks;
    char grade;
}subnode;*/



	pres->historylength++;
	if(pres->historylength==(MAXHISTORY-1))
	{
		delete_a_history(pres);
	}
	pres->history[pres->historylength]= 
}
