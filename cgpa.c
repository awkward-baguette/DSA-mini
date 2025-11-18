float compute_cgpa(semnode *semhead) {
    if (semhead == NULL)
        return 0.0;  

    float total_sgpa = 0.0;
    int sem_count = 0;

    semnode *temp = semhead;
    while (temp != NULL) {
        total_sgpa += temp->sgpa;  
        sem_count++;               
        temp = temp->next;          
    }

    if (sem_count == 0)
        return 0.0;
    return total_sgpa / sem_count;  
}

float find_sgpa(subnode subjects[]){
    float sgpa=0;
    float total_credits = 0.0;
    for(int i=0;i<SUBJECTS;i++){
        subnode* subject=&subjects[i];
        subject->grade=getgrade(subject->marks);
        if(subject->grade!='F')
            sgpa += getWeightage(subject->grade)*(subject->credit);
        else
            subject->backlog=1;
        total_credits += subject->credit;
      }
     return sgpa/total_credits;
    
}
char getgrade(int marks){
   if(marks>=90)
    return 'A';
   else if(marks<90 && marks>=80)
    return 'B';
   else if(marks>=70)
    return 'C';
   else if(marks>=60)
    return 'D';
   else if(marks>=50)
    return 'E';
   else
    return 'F';
}

int getWeightage(char ch){
    switch(ch){
        case 'A':
            return 10;
        case 'B':
            return 9;
        case  'C':
            return 8;
        case  'D':
            return 7;
        case  'E':
            return 6;
            
        case  'F':
            return -1;
      }     
}

void performance_report(studentnode *s)
{
	int semno,reval;
	subnode subject;
	printf("--Student report of %s, roll no: %d--\n", s->name, s->roll_no);
	printf("Which semester would you like to access?  ");
	scanf("%d",&semno);
	semnode *pres = s->semhead;
	while(pres!=NULL)
	{
		if(pres->semno==semno)
			break;
		pres=pres->next;
	}
	if(pres!=NULL)
	{
		printf("\nSemester %d scorecard\n",semno);
		for(int i=0;i<SUBJECTS;i++)
		{
			subject = pres->sublist[i];
			printf("%s: marks: %d grade: %c\n",subject.name,subject.marks,subject.grade);
		}
		printf("SGPA: %f\n", pres->sgpa);
		printf("-----------end of report----------\n");
	}
	else
	{
		printf("Sorry, semester not found.\n");
	}
	printf("Current CGPA: %f\n\n",compute_cgpa(s->semhead));
	printf("Would you like to apply for re-eval (1- yes, 0- no) ?  ");
	scanf("%d",&reval);
	if(reval)
	{
		char sub[20];
		int n, newmarks;
		printf("Which semester number are you changing?  ");
		scanf("%d",&semno);
		printf("How many subjects are you changing?  ");
		scanf("%d",&n);
		for(int i=0;i<n;i++)
		{
			printf("Enter subject name and the new marks: ");
			scanf("%s %d",sub,&newmarks);
			updatemarks(s, s->roll_no,semno, sub, newmarks);
		}
		performance_report(s);
	}
	else
	{
		return;
	}

}
