#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>


#define Maximum_Number_of_Questions 500 // maximum number of questions for individual difficulty level
#define Maximum_Length_of_Questions 500
#define Maximum_Length_of_Options 100
#define Number_of_Options 4
#define Maximum_Number_of_Subjects 50
#define Maximum_Length_of_Subject_Names 50
#define Number_of_Difficulty_levels 3

void Clear_Marks();
void Display_Results();
void Read_Names();
void Store_Marks(int marks);
void Store_Names();
void Store_Total_Marks(int marks);

extern char Names_of_Students[1000][Maximum_Length_of_Options];
extern int Length_of_Student_Names[1000];
extern int Students;



void Store_Marks(int marks)        //   -----Stores the Marks of the Test in the Files---------------------   //
{
    FILE *Marks = fopen("Resulting_Marks.txt", "a");       //---Open File In append mode---//
    fprintf(Marks, "%d", marks);        //---Store the Marks---//
    fputc('\n', Marks);
    fclose(Marks);                   //---Close the File---//
}
void Store_Names()                 //   -----Stores the Names of the Students in the Files-----------------   //
{
    FILE *Names_File = fopen("Names_of_Students.txt", "w");
    FILE *Name_Len = fopen("Length_of_Names.txt", "w");          //---Open files in write mode to clear them---//
    fprintf(Name_Len, "%d", Students);
    fputc('\n', Name_Len);
    for (int i = 0; i < Students; i++)
    {
        fputs(Names_of_Students[i], Names_File);              //---Store the Names in the file from array---//
        fprintf(Name_Len, "%d", Length_of_Student_Names[i]);  //---Store the Length of the Names from array to file---//
        fputc('\n', Name_Len);
    }
    fclose(Names_File);
    fclose(Name_Len);           //---Close the File---//
}
void Read_Names()                 //   -----Copies the Names of the Students from the Files to arrays-----   //
{
    FILE *Names_File = fopen("Names_of_Students.txt", "r");
    FILE *Name_Len = fopen("Length_of_Names.txt", "r");         //---Open Files in Read Mode---//

    fscanf(Name_Len, "%d", &Students);      //---Read Number of Students---//

    for (int i = 0; i < Students; i++)
    {
        fscanf(Name_Len, "%d", &Length_of_Student_Names[i]);   //---Read the Length of Student Names---//
        fgets(Names_of_Students[i], Length_of_Student_Names[i], Names_File);  //---Read the Names of Students---//
    }
    fclose(Names_File);
    fclose(Name_Len);
}
void Display_Results()             //   -----Display the Results of Tests Conducted------------------------   //
{
    int marks[1000];
    int total_marks_[1000];

    Read_Names();
    FILE *Total_Marks = fopen("Total_Marks.txt","r");     //---Open Files in read Mode---//
    FILE *Marks = fopen("Resulting_Marks.txt", "r");
    for (int student = 0; student < Students; student++)
    {
        fscanf(Total_Marks,"%d",&total_marks_[student]);     //---Read and Copy the Total Marks in an array---//
        fscanf(Marks, "%d", &marks[student]);                //---Read and copy the Obtained marks in an array---//
    }
    printf("Total Marks\t\tMarks\t\tName of Student\n");
    for (int student = 0; student < Students; student++)     //---Display the Result---//
    {
        printf("%d\t\t\t%d\t\t%s\n", total_marks_[student],marks[student], Names_of_Students[student]);
    }
    fclose(Marks);
}
void Clear_Marks()                 //   -----Clears the Marks and names from the files---------------------   //
{
    int chk;

input_error:
    printf("Are you sure you want to clear all Marks??\n1. Yes\n2. No\n");
    scanf("%d", &chk);
    getchar();
    system("cls");
    if (chk == 2)
    {
        return;
    }
    else if (chk < 1 || chk > 2)
    {
        printf("Invalid Input!!!\n");
        goto input_error;
    }
                //---Open All Files in Write Mode to clear them---//
    FILE *Total_Marks=fopen("Total_Marks.txt","w");    
    FILE *Marks = fopen("Resulting_Marks.txt", "w");
    FILE *Names = fopen("Names_of_Students.txt", "w");
    fclose(Marks);
    fclose(Names);
    fclose(Total_Marks);

                //---In this File Put 0 so that the program knows that there are 0 records/results stored---//
    FILE *Counter = fopen("Length_of_Names.txt", "w");
    fprintf(Counter, "%d", 0);
    fputc('\n', Counter);
    fclose(Counter);
    printf("Now the program will terminate to complete clearing the marks\n");
    exit(0);      //Exit program to refresh the whole arrays having names 
}
void Store_Total_Marks(int marks)  //   -----Stores the Total Marks in the File----------------------------   //
{
    FILE *Marks = fopen("Total_Marks.txt", "a");    //---Open file in append mode to continue adding marks---//
    fprintf(Marks, "%d", marks);            //---Put Makrs in File---//
    fputc('\n', Marks);                     //---Go to next line---//
    fclose(Marks);
}