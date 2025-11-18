#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "student.h"

void init(tree *t)
{
     t->root=NULL;
}	 

studentnode *create_snode(int r_no, char sname[])
{
	studentnode *node = (studentnode*)malloc(sizeof(studentnode));
	node->roll_no = r_no;
	strcpy(node->name,sname);
	node->semhead = NULL;
	node->left = node->right = NULL;
	//node->historylength = -1;
	return node;
}
	
void addsem(studentnode *s, int semno, list_t *p)
{
	int i;
	subnode subs[SUBJECTS];
	char subjects[SUBJECTS][20];
  	int credits[SUBJECTS];
	semnode *temp = (semnode*)malloc(sizeof(semnode));
	temp->semno = semno;
	
	for(i=0;i<SUBJECTS;i++)
	{
			printf("Enter the subject name and the credits: ");
			scanf("%s %d",subjects[i],&credits[i]);
	}
	for(i=0;i<SUBJECTS;i++)
	{
			temp->sublist[i].credit = credits[i];
			strcpy(temp->sublist[i].name,subjects[i]);
			printf("Enter %s marks: ",subjects[i]);
			scanf("%d", &temp->sublist[i].marks);
			temp->sublist[i].grade = get_grade(temp->sublist[i].marks);
	}

	temp->sgpa = find_sgpa(temp->sublist);
	temp->next=NULL;

	studentnode *pres = s;
	temp->next = pres->semhead;
	pres->semhead = temp;
	pqinsert(p, s);
}

studentnode *add_new_student(tree *t,char sname[], int roll_no)
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

/*void delete_a_history(studentnode *s)
{
	s->historylength--;
	for(int i=0;i<s->historylength;i++)
	{
		s->history[i]=s->history[i+1];
	}
}*/

studentnode *findstudent(tree *t, int roll_no)
{
	studentnode *pres = t->root;
	int found=0,i;

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
	if(found)
		return pres;
	else
		return NULL;
}

void create_to_add(tree *t, char sname[], int roll_no, int semno, list_t *p)
{
	studentnode *pres = t->root;
	int found=0,i;
	int oldmarks;
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
		addsem(pres, semno,p);
		present_sem=pres->semhead;
	}
	else 
	{
		printf("Marks already exist. Use update to change them.\n");
		return;
	}
}

void updatemarks(studentnode *s, int roll_no, int semno, char *subname, int marks)
{
	//studentnode *pres = t->root;
	int found=0;
	int oldmarks;
	/*if(pres==NULL)
	{
		pres = add_new_student(t,sname,roll_no);
	}*/
	/*while(pres!=NULL)
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
		printf("Student doesn't exist. Use add marks to add a student.\n");
		return;
	}*/

	found=0;
	semnode *present_sem = s->semhead;
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
		printf("Sem doesn't exist. Please add a semester first.\n");
		return;
	}

	found=0;
	for(int i=0;i<SUBJECTS;i++)
	{
		if(strcmp(present_sem->sublist[i].name,subname)==0)
		{
			oldmarks = present_sem->sublist[i].marks;	
			present_sem->sublist[i].marks = marks;
			present_sem->sublist[i].grade = get_grade(marks);	
			found=1;		
		}
	}

	/*if(found)
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
	}*/
	if(found)
		present_sem->sgpa = find_sgpa(present_sem->sublist);
	else
	{
		printf("Subject not found in the subject array\n");
		return;
	}
}

void deletemarks(tree *t, int roll_no,list_t *p)
{
	int choice, semno, i;
	studentnode *pres = t->root;
	studentnode *prev = NULL;
	semnode *prev_sem = NULL;
	studentnode *pr, *q, *temp;
	printf("Do you want to: \n1. Delete a student \n2. Delete a semester:  ");
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
		printf("Student doesn't exist.\n");
		return;
	}

	if(choice==1)
	{
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
			pr=NULL; //parent of inorder succesor
		    temp=pres->right;
            while(temp->left!=NULL)
			{
				  pr=temp;
				  temp=temp->left;
			  }
			  //temp is the inorder successor

			  pres->roll_no=temp->roll_no;
			  strcpy(pres->name,temp->name);
			  pres->semhead = temp->semhead; 
			  //pres->historylength=temp->historylength;
			  /*for(i=0; i<pres->historylength;i++)
			  {
				pres->history[i]=temp->history[i];
			  }*/
             if(pr!=NULL)
				 pr->left=temp->right;
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
		pqdelete(p, roll_no);
		free(pres);
	}
	else if(choice==2)
	{
	printf("Enter the semester number: ");
	scanf("%d",&semno);
	found=0;
	semnode *present_sem = pres->semhead;
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
	{
		printf("Sem doesn't exist.\n");
		return;
	}
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

void display_bst(studentnode *root)
{
	int i;
	semnode *pres;
    if(root!=NULL)
	   {
		display_bst(root->left);
		printf("\n");
	    printf("Student name: %s  Roll no: %d\n",root->name, root->roll_no);
		pres=root->semhead;
		while(pres!=NULL)
		{
			printf("Semester %d:\n",pres->semno);
			for(i=0;i<SUBJECTS;i++)
				printf("%s marks: %d, grade: %c\n", pres->sublist[i].name, pres->sublist[i].marks, pres->sublist[i].grade);
			printf("SGPA: %f\n",pres->sgpa);
			pres=pres->next;
		}
		printf("\n");
	    display_bst(root->right);
	   }
}

void display_backlog(tree *t)
{
	int i;
	semnode *pres;
	studentnode *root = t->root;
    if(root!=NULL)
	   {
		display_bst(root->left);
	    
		list=root->semhead->sublist;
		for(int i=0;i<SUBJECTS;i++){
			if(list[i]->backlog == 1)
				printf("Student name: %s  Roll no: %d has a backlog in %s\n",root->name, root->roll_no,list[i]->name);
		}
	    display_bst(root->right);
	   }
}


void display_counselling(tree *t)
{
	int i;
	semnode *pres;
	studentnode *root = t->root;
    if(root!=NULL)
	   {
		display_bst(root->left);
	    
		sem=root->semhead;
		float cgpa=compute_cgpa(sem);
		if(cgpa<6.5)
				printf("Student name: %s  Roll no: %d has a cgpa %f and needs to attend remedial classes and academic counseling\n",root->name, root->roll_no,cgpa);
	
	    display_bst(root->right);
	   }
}

