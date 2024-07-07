#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_SUBJECTS 10
#define CLASS_SIZE 40
#define DATAFILE "student.dat"  //may be replaced with any filename.

// Constants for grade ranges
const double A_GRADE = 92.0;
const double B_PLUS_GRADE = 88.0;
const double B_GRADE = 84.0;
const double C_PLUS_GRADE = 80.0;
const double C_GRADE = 76.0;
const double D_GRADE = 72.0;
const double F_GRADE = 0.0;


typedef struct {
   char subject[15];
   double grade;
   int units;
   char letter[3];
   double QPE;
} SUBJECT;

typedef struct {
char ID[10];
char firstname[15];
char lastname[15];
char course[15];
SUBJECT mysubjects[MAX_SUBJECTS];
double QPI;
int S_count;
} STUDENT;

/*------------------------------------------------------*/

void Bubble(STUDENT a[], int n) {
    int i, j;
    STUDENT temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            int compare = strcmp(a[j].ID, a[j + 1].ID);
            if (compare > 0) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}


/*------------------------------------------------------*/

int ReadFile(STUDENT a[], int b) {
   int STUDENT_count = 0;
   FILE *sfile;
   if ((sfile = fopen(DATAFILE,"rb")) == NULL) {
printf("Creating new file...");
getchar(); // hold screen until key pressed
   }
   else {
fread(a,b,1,sfile);
STUDENT_count = a[CLASS_SIZE].S_count;
   }
   fclose(sfile);
   return(STUDENT_count);
} // ReadFile
/*------------------------------------------------------*/

void WriteFile(STUDENT a[], int S, int b) {
   FILE *sfile;
   a[CLASS_SIZE].S_count = S;
   sfile = fopen(DATAFILE,"wb");
   fwrite(a,b,1,sfile);
   fclose(sfile);
} //WriteFile
/*----------------------------------------------------*/

void AddSubject(STUDENT a[], int n, int S) {
   getchar();
   printf("\nsubject : ");
   scanf("%[^\n]",a[S].mysubjects[n].subject);
   printf("\ngrade : ");
   scanf("%lf",&a[S].mysubjects[n].grade);
   printf("\nunits : ");
   scanf("%d",&a[S].mysubjects[n].units);

 } // Add

/*------------------------------------------------------*/


void ClassList(STUDENT a[], int S) {
  int i;
  printf("\n-----------------------------------------------------------------------------\n");
  printf("\tID\tCourse\t\t\tLastName\tFirstName\tQPI");
  printf("\n-----------------------------------------------------------------------------\n");
  for (i = 0; i < S; i++) {
      printf("\t%s\t",a[i].ID);
      printf("%s\t",a[i].course);
      printf("\t%s\t",a[i].lastname);
      printf("\t%s\t",a[i].firstname);
      printf("\t%.2lf\t\n",a[i].QPI);

  } /* for */

  printf("\n-----------------------------------------------------------------------------\n");
}// ClassList

/*----------------------------------------------------------*/

int BinarySearch(STUDENT a[], char key[], int low, int high) {
    while (low <= high) {
        int mid = (low + high) / 2;
        int compare = strcmp(a[mid].ID, key);

        if (compare == 0) {
            return mid;  // Element found
        } else if (compare < 0) {
            low = mid + 1;  // Key may be in the right half
        } else {
            high = mid - 1;  // Key may be in the left half
        }
    }

    return -1;  // Element not found
}


/*--------------------------------------------------------------------------*/

void Search(STUDENT a[], int S) {
  int subjects_count, index, j;
  char ID[10];
  printf("\nSearch ID : ");
  scanf("%s",ID);

   printf("\n------------------------------------------------------------------------------\n");
  printf("\n\tSubject\t");
  printf("\t\t  Grade\t\t");
  printf("  Units\t\t");
  printf("  Letter Grade");
   printf("\n------------------------------------------------------------------------------\n");
  index = BinarySearch(a, ID, 0, S - 1);
  if (index >= 0) {
    subjects_count = a[index].S_count;
    for (j = 0; j < subjects_count; j++){
      printf("[%d]\t%-13s",j,a[index].mysubjects[j].subject);
      printf("\t\t%7.2lf",a[index].mysubjects[j].grade);
      printf("\t%5d   ",a[index].mysubjects[j].units);
      printf("\t%-5s\n",a[index].mysubjects[j].letter);
    }
    printf("\nYour QPI is %.2lf\n",a[index].QPI);
  } // if (index >=0)
  else printf("\nThe student is not in the class\n");
   printf("\n------------------------------------------------------------------------------\n");
}// Search

/*--------------------------------------------------------------------------*/

void ViewSubjects(STUDENT a[], int n, int S) {
  printf("\n------------------------------------------------------\n");
  printf("\nThere are %d subjects(s)\n\n",n);
  printf("\n\tSubject\t");
  printf("\t\t  Grade\t");
  printf("  Units\t");
  printf("  Letter Grade");
  printf("\n------------------------------------------------------\n");
  if (n != 0) {
    for (int i = 0; i < n; i++) {
      printf("[%d]\t%-13s",i,a[S].mysubjects[i].subject);
      printf("\t\t%7.2lf",a[S].mysubjects[i].grade);
      printf("\t%5d   ",a[S].mysubjects[i].units);
      printf("\t%-5s\n",a[S].mysubjects[i].letter);

    } /* for */
  printf("\nYour QPI is %.2lf\n",a[S].QPI);
  } /* if */
  else {
    printf("no subjects added");
  } /* else */

  printf("\n------------------------------------------------------\n");
}// ViewSubjects

/*------------------------------------------------------*/

void Letter(STUDENT a[],int n, int S) {
int i=0;
while (i <= n) {
   if (a[S].mysubjects[i].grade >= A_GRADE && a[S].mysubjects[i].grade <= 100) {
   strcpy(a[S].mysubjects[i].letter,"A");
                    a[S].mysubjects[i].QPE = 4.0;}

        else if (a[S].mysubjects[i].grade >= B_PLUS_GRADE) {
   strcpy(a[S].mysubjects[i].letter,"B+");
                    a[S].mysubjects[i].QPE = 3.5;        }
        else if (a[S].mysubjects[i].grade >= B_GRADE) {
   strcpy(a[S].mysubjects[i].letter,"B");
                    a[S].mysubjects[i].QPE = 3.0;        }
        else if (a[S].mysubjects[i].grade >= C_PLUS_GRADE) {
   strcpy(a[S].mysubjects[i].letter,"C+");
                    a[S].mysubjects[i].QPE = 2.5;        }
        else if (a[S].mysubjects[i].grade >= C_GRADE) {
   strcpy(a[S].mysubjects[i].letter,"C");
                    a[S].mysubjects[i].QPE = 2.0;        }
    else if (a[S].mysubjects[i].grade >= D_GRADE) {
   strcpy(a[S].mysubjects[i].letter,"D");
                    a[S].mysubjects[i].QPE = 1.0;        }
        else{
        strcpy(a[S].mysubjects[i].letter,"F");
        a[S].mysubjects[i].QPE = 0.0;        }

        i++;
}
} // Letter

/*------------------------------------------------------*/

double QPI(STUDENT a[], int n, int S) {
int i=0;
int TU = 0;
double TQP=0.0;
while (i <= n) {
  TQP += (a[S].mysubjects[i].QPE * a[S].mysubjects[i].units);
  TU += a[S].mysubjects[i].units;
  i++;
}
a[S].QPI = TQP/TU;
return a[S].QPI;
} //QPI
/*----------------------------------------------------------*/

char Menu2(char choice) {
  do {
     getchar();
     getchar();
     printf("\n<< Subjects >>\n\n");
     printf("[A] Add Subject\n");
     printf("[V] View Subjects\n");
     printf("[B] Back to Student Menu \n\n");
     printf("enter letter of choice : ");
     choice = toupper(getchar());
  } while (choice !='A' && choice != 'V' &&
choice != 'B');
  return choice;
} // Menu2

/*----------------------------------------------------------*/

void SubjectsMenu(STUDENT a[],int count, int S) {
int quit = 0;
char choice = '\0';
while (!quit) {
     choice = Menu2(choice);
     switch (choice) {
case 'A' :
          if (count < MAX_SUBJECTS) {
                      AddSubject(a,count,S);
                      Letter(a,count,S);
                      a[S].QPI = QPI(a, count, S);
                      count++;
          }
          else printf("\nmax subjects added"); break;
case 'V' :
         ViewSubjects(a,count,S);
         break;
case 'B' : quit = 1;
     } /* switch (choice) */
   } /* !quit */
   a[S].S_count = count;
} //SubjectsMenu

/*----------------------------------------------------------*/

void AddStudent(STUDENT a[], int S) {
   int count = a[S].S_count;
   printf("\n ID: ");
   scanf("%s",a[S].ID);
   printf("\n Course: ");
   scanf("%s",a[S].course);
   printf("\nLast name: ");
   scanf("%s",a[S].lastname);
   printf("\nFirst name: ");
   scanf("%s",a[S].firstname);
   SubjectsMenu(a,count,S);
} // AddStudent

/*----------------------------------------------------------*/

char Menu1(char choice) {
  do {
     printf("\n<< ADDU Students QPI >>\n\n");
     printf("[A] Add Student\n");
     printf("[D] Display Class List\n");
     printf("[S] Search Student\n");
     printf("[Q] Quit Program\n\n");
     printf("enter letter of choice : ");
     choice = toupper(getchar());
  } while (choice !='A' && choice != 'S' && choice !='D' && choice != 'Q');
  return choice;
} // Menu1

/*----------------------------------------------------------*/

int StudentMenu(STUDENT a[],int S) {
int quit = 0;
char choice = '\0';
while (!quit) {
     choice = Menu1(choice);
     switch (choice) {
case 'A' : if (S < CLASS_SIZE) {
                    AddStudent(a,S);
                    S++;      }
           else printf("\nCLASS is ful.\n");
           break;
case 'D' : Bubble(a, S);
           ClassList(a,S);
   getchar(); getchar();
   break;
case 'S' : Search(a,S);
           getchar(); getchar();
           break;
case 'Q' : quit = 1;
     } /* switch (choice) */
   } /* !quit */
   return S;
} // StudentMenu

/*----------------------------------------------------------*/

int main(void) {
   int i, class_count = 0;
   STUDENT CLASS[CLASS_SIZE+1];
   for (i=0;i<CLASS_SIZE;++i) CLASS[i].S_count=0;
   int class_size = sizeof CLASS;
   class_count = ReadFile(CLASS,class_size);
   class_count = StudentMenu(CLASS,class_count);
   WriteFile(CLASS,class_count,class_size);
} // main