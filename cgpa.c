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
