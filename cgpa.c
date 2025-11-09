



float find_sgpa(subnode subjects[]){
    float sgpa=0;
    float total_credits = 0.0;
    for(int i=0;i<SUBJECTS;i++){
        subnode* subject=&subjects[i];
        subject->grade=getgrade(subject->marks);
        if(subject->grade!='F')
            sgpa += getWeightage(subject->grade)*(subject->credit);
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
