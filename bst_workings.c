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
	
void addsem(studentnode *s, int semno, subnode *subjects)
{
	semnode *temp = (semnode*)malloc(sizeof(semnode));
	temp->semno = semno;
	for(int i=0; i<SUBJECTS; i++)
		temp->sublist[i]=subjects[i];
	temp->sgpa = find_sgpa(subjects);
	temp->next=NULL;

	studentnode *pres = s;
	temp->next = pres->semhead;
	pres->semhead = temp;
}

char get_grade_S(int m)
{
	if(m>=90)
		return 'S'
	else if(m>=80)
		return 'A'
	else if(m>=70)
		return 'B'
	else if(m>=60)
		return 'C'
	else if(m>=50)
		return 'D'
	else if(m>=40)
		return 'E'
	else 
		return 'F'
}

studentnode add_new_student(tree *t,char *sname, int roll_no)
{
	studentnode *temp = create_snode(roll_no,sname);
	studentnode *pres = t->root, *prev = NULL;
	
	if(t->root ==NULL)
	    t->root=temp;
	else  
	{
	while(pres!=NULL)
		{
			prev=pres;
			if(roll_no>pres->roll_no)
				pres=pres->right; //move right
			else
				pres=pres->left; // move left;
		}
	if(roll_no>prev->roll_no) // attach temp to left or right of prev
        prev->right=temp;
	else
		prev->left=temp;
	}
	return temp;
}

void delete_a_history(studentnode *s)
{
	s->historylength--;
	for(int i=0;i<s->historylength;i++)
	{
		s->history[i]=s->history[i+1];
	}
}

void create_to_add(tree *t, char *sname, int roll_no, int semno, char **subjects, int *credits)
{
	studentnode *pres = t->root;
	int found=0,i;
	float oldmarks;
	/*if(pres==NULL)
	{
		pres = add_new_student(t,sname,roll_no);
	}*/
	while(pres!=NULL)
	{
		if(pres->roll_no==roll_no)
		{
			found=1;
			break;
		}
		else if(roll_no>pres->roll_no)
			pres = pres->right;
		else
			pres = pres->left;
	}
	if(!found)
	{
		pres = add_new_student(t,sname,roll_no);
	}

	found=0;
	semnode *present_sem = pres->semhead;
	while(present_sem!=NULL)
	{
		if(present_sem->semno==semno)
		{
			found=1;
			break;
		}
		present_sem = present_sem->next;
	}
	if(!found)
	{
		subnode subs[SUBJECTS];
		for(i=0;i<SUBJECTS;i++)
		{
			subs[i].credit = credits[i];
			strcpy(subs[i].name,subjects[i]);
			printf("Enter %s marks: ",subjects[i]);
			scanf("%d", &subs[i].marks);
			subs[i].grade = get_grade_S(subs[i].marks);
		}
		addsem(pres, semno, subs);
		present_sem=pres->semhead;
	}
	else 
		printf("Marks already exist. Use update to change them.\n");
	
}

void updatemarks(tree *t, int roll_no, int semno, char *subname, float marks)
{
	studentnode *pres = t->root;
	int found=0;
	float oldmarks;
	/*if(pres==NULL)
	{
		pres = add_new_student(t,sname,roll_no);
	}*/
	while(pres!=NULL)
	{
		if(pres->roll_no==roll_no)
		{
			found=1;
			break;
		}
		else if(roll_no>pres->roll_no)
			pres = pres->right;
		else
			pres = pres->left;
	}
	if(!found)
	{
		printf("Student doesn't exist. Use add marks to add a student.");
	}

	found=0;
	semnode *present_sem = pres->semhead;
	while(present_sem!=NULL)
	{
		if(present_sem->semno==semno)
		{
			found=1;
			break;
		}
		present_sem = present_sem->next;
	}
	if(!found)
	{
		printf("Sem doesn't exist. Use add marks to add a semester.");
	}

	found=0;
	for(int i=0;i<SUBJECTS;i++)
	{
		if(strcmp(present_sem->sublist[i]->name,subname)==0)
		{
			oldmarks = present_sem->sublist[i]->marks;	
			present_sem->sublist[i]->marks = marks;
			present_sem->sublist[i]->grade = get_grade_S(marks);	
			found=1;		
		}
	}

	if(found)
	{
		pres->historylength++;
		if(pres->historylength==(MAXHISTORY-1))
		{
			delete_a_history(pres);
		}
		historynode new;
		new.semno = semno;
		strcpy(new.subname,subname);
		new.oldmarks = oldmarks;
		new.newmarks = marks;

		pres->history[pres->historylength]= new;
	}
	else
		printf("Subject not found in the subject array\n");
}

void deletemarks(tree *t, int roll_no, int semno, char *subname, float marks)
{
	int choice;
	studentnode *pres = t->root;
	studentnode *prev = NULL;
	studentnode *p, *q, *temp;
	printf("Do you want to: \n1. Delete a semester \n2. Delete a student");
	scanf("%d",&choice);

	int found=0;
	while(pres!=NULL)
	{
		if(pres->roll_no==roll_no)
		{
			found=1;
			break;
		}
		prev=pres;
		if(roll_no>pres->roll_no)
			pres = pres->right;
		else
			pres = pres->left;
	}
	if(!found)
	{
		printf("Student doesn't exist.");
	}

	if(choice==1)
	{
		studentnode *q;
		if((pres->left==NULL)||(pres->right==NULL))
		{
			if(pres->left==NULL)
				q=pres->right; //get the right subtree , q will be NULL for leaf node
			else
				q=pres->left; // get the left subtree, q will be NULL for leaf node
			if(prev==NULL) //deleteing the root with one subtree
				t->root=q; //make q the new root
			else if(pres==prev->left)
			    prev->left=q;
			else
		        prev->right=q;
		}
		else//both subtrees present
		{
			  //find the inorder successor of curr
			  p=NULL; //parent of inorder succesor
		      temp=pres->right;
               while(temp->left!=NULL)
			  {
				  p=temp;
				  temp=temp->left;
			  }
			  //temp is the inorder successor
			  pres->data=temp->data; //copy value of temp to curr
             if(p!=NULL)
				 p->left=temp->right;
			  else
				 pres->right=temp->right;
		}
		semnode *trav = pres->semhead;
		semnode *t;
		while(trav!=NULL)
		{
			t=trav->next;
			free(trav);
			trav=t;
		}
		pres->semhead=NULL;  //kind of unneccessary
		free(pres);
	}
	else if(choice==2)
	{
	found=0;
	semnode *present_sem = pres->semhead;
	semnode *prev_sem - NULL;
	while(present_sem!=NULL)
	{
		if(present_sem->semno==semno)
		{
			found=1;
			break;
		}
		prev_sem=present_sem;
		present_sem = present_sem->next;
	}
	if(!found)
		printf("Sem doesn't exist.");
	else
	{
		if(prev_sem==NULL)
			pres->semhead = present_sem->next;
		else
			prev_sem->next=present_sem->next;
		free(present_sem);
	}
    }
}

void display_bst(tree *t)
{
	int i;
	semnode *pres;
	studentnode *root = t->root;
    if(root!=NULL)
	   {
		display_bst(root->left);
	    printf("Student name: %s  Roll no: %d\n",root->name, root->roll_no);
		pres=root->semhead;
		while(pres!=NULL)
		{
			printf("Semester %d:\n",pres->semno);
			for(i=0;i<SUBJECTS;i++)
				printf("%s marks: %d, grade: %c", pres->sublist[i]->name, pres->sublist[i]->marks, pres->sublist[i]->grade);
			printf("SGPA: %f",pres->sgpa);
			pres=pres->next;
		}
	    display_bst(root->right);
	   }
}

