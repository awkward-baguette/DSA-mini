#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "student.h"


int main()
{
  int i, roll_no, semno, marks;
  char sname[20];
  studentnode *student;
  subnode subjects[SUBJECTS];
  tree t;
  list_t p;
  int ch,n;
  init(&t);
  pinit(&p);
 
  while(1)
  {
      printf("\n1.To create a student");
      printf("\n2.To create a student and add marks");   
	  printf("\n3.To add semester to a student");   
      printf("\n4.To display the students");
      printf("\n5.To update marks of a student");
      printf("\n6.To delete a student/semester");
      printf("\n7.To find CGPA of a student");
      printf("\n8.To display n top performers");
      printf("\n9.To generate report card for a student");
      printf("\n10.exit\n");
      scanf("%d",&ch);
       switch(ch)
       {
        case 1 :	printf("\nEnter name and roll no.: ");
					getchar();
					fgets(sname, sizeof(sname), stdin);
					if (strlen(sname) > 0 && sname[strlen(sname) - 1] == '\n') {
        				sname[strlen(sname) - 1] = '\0'; 
    				}
					scanf("%d",&roll_no);
					add_new_student(&t,sname,roll_no);
					break;
					
        case 2:     printf("\nEnter name and roll no.: ");
					getchar();
					fgets(sname, sizeof(sname), stdin);
					if (strlen(sname) > 0 && sname[strlen(sname) - 1] == '\n') {
        				sname[strlen(sname) - 1] = '\0'; 
    				}
					scanf("%d",&roll_no);
					printf("\nEnter the semester number: ");
					scanf("%d", &semno);
					create_to_add(&t,sname,roll_no, semno, &p);
		            break; 

		case 3: 	printf("\nEnter roll no");
					scanf("%d",&roll_no);
					student = findstudent(&t, roll_no);
					if(student==NULL)
						printf("Student not found\n");
					else
					{
					printf("\nEnter sem no");
					scanf("%d",&semno);
					addsem(student, semno,&p);
					}
                	break;
					
      	case 4: 	display_bst(t.root);
                	break;

     	case 5:		printf("\nEnter roll no and sem no: ");
					scanf("%d %d",&roll_no,&semno);
					printf("\nEnter the subject name and the new marks: ");
					scanf("%s %d", sname, &marks);
					student = findstudent(&t,roll_no);
					if(student==NULL)
					{
						printf("Student doesn't exist. Use add marks to add a student.\n");
						break;
					}
					updatemarks(student, roll_no, semno, sname, marks);
                 	break;

      	case 6:   	printf("\nEnter roll no");
					scanf("%d",&roll_no);
					deletemarks(&t, roll_no,&p);
                 	break; 

      	case 7: 	printf("\nEnter roll no");
					scanf("%d",&roll_no);
					student = findstudent(&t,roll_no);
					if(student==NULL)
						printf("Student not found\n");
					else
						printf("The student's CGPA is: %f\n", compute_cgpa(student->semhead));
					break; 

       	case 8: 	printf("\nEnter no. of students to display: ");
					scanf("%d",&n);
	   				qdisplay(&p,n);
                 	break;

      	case 9:		printf("Enter the roll no: ");
                	scanf("%d",&roll_no);
                	student = findstudent(&t,roll_no);
					if(student==NULL)
						printf("Student not found\n");
					else
						performance_report(student);
                 	break; 
 
        case 10:		exit(0);
       }
    }
    return 0;
  }  