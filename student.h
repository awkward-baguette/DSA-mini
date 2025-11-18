// student.h
#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUBJECTS 6
#define MAXHISTORY 10

typedef struct subject {
    int credit;
    char name;
    int marks;
    char grade;
    int backlog;
} subnode;

typedef struct sem {
    int semno;
    subnode sublist[SUBJECTS];
    float sgpa;
    struct sem *next;
} semnode;

typedef struct gradehistory {
    int semno;
    char subname[20];
    int oldmarks;
    int newmarks;
    char oldgrade;
    char newgrade;
} historynode;

typedef struct snode {
    int roll_no;
    char name[50];
    semnode *semhead;
    historynode history[MAXHISTORY];
    int historylength;
    struct snode *left;
    struct snode *right;
} studentnode;

typedef struct tree {
    studentnode *root;
} tree;


void init(tree *t);
studentnode *create_snode(int r_no, char *sname);
void add_new_student(tree *t, char *sname, int roll_no);
void addsem(studentnode *s, int semno, subnode *subjects);
void delete_a_history(studentnode *s);
void create_to_add(tree *t, char *sname, int roll_no, int semno, char **subjects, int *credits);
void updatemarks(tree *t, int roll_no, int semno, char *subname, float marks);
void deletemarks(tree *t, int roll_no, int semno, char *subname, float marks);
void display_bst(tree *t);
float find_sgpa(subnode subjects[]);
float compute_cgpa(semnode *semhead);
char getgrade(int marks);
int getWeightage(char ch);
void addmarks(tree *t, char *sname, int roll_no, int semno, char *subname, float marks);

void init(tree *t);
void pinit(list_t *p);
char get_grade(int m);
int getWeightage(char ch);
float compute_cgpa(semnode *semhead);
float find_sgpa(subnode subjects[]);
void pqinsert(list_t*p, studentnode*s);
node_t pqdelete(list_t *ptr_list, int r_no);
studentnode *create_snode(int r_no, char sname[]);
void addsem(studentnode *s, int semno, list_t *p);
studentnode *add_new_student(tree *t,char sname[], int roll_no);
studentnode *findstudent(tree *t, int roll_no);
void create_to_add(tree *t, char sname[], int roll_no, int semno, list_t *p);
void updatemarks(studentnode *s, int roll_no, int semno, char *subname, int marks);
void deletemarks(tree *t, int roll_no,list_t *p);
void display_bst(studentnode *root);
void qdisplay(list_t *ptr_list,int n);
void performance_report(studentnode *s);


#endif

