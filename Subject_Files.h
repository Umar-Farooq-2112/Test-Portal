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

extern char Question_Statements[Maximum_Number_of_Subjects][Number_of_Difficulty_levels][Maximum_Number_of_Questions][Maximum_Length_of_Questions];
extern char Options_to_choose[Maximum_Number_of_Subjects][Number_of_Difficulty_levels][Maximum_Number_of_Questions][Number_of_Options][Maximum_Length_of_Options];
extern int Length_of_Questions[Maximum_Number_of_Subjects][Number_of_Difficulty_levels][Maximum_Number_of_Questions];
extern int Length_of_Options[Maximum_Number_of_Subjects][Number_of_Difficulty_levels][Maximum_Number_of_Questions][Number_of_Options];

extern int Questions_Count[Maximum_Number_of_Subjects][Number_of_Difficulty_levels];
extern char Subject_Names[Maximum_Number_of_Subjects][Maximum_Length_of_Subject_Names];
extern int Number_of_Subject;
extern int Length_of_Subject_Names[Maximum_Number_of_Subjects];

extern int Test_Specs[Maximum_Number_of_Subjects][Number_of_Difficulty_levels];
extern int Quiz_Ques_No[Maximum_Number_of_Subjects][Number_of_Difficulty_levels][Maximum_Number_of_Questions];
extern char Quiz_array[Maximum_Number_of_Questions][Maximum_Length_of_Questions];
extern int Quiz_Correct_Ans[Maximum_Number_of_Questions];
extern char Quiz_Ans_array[Maximum_Number_of_Questions][Number_of_Options][Maximum_Length_of_Options];

void Add_Subject();
void Edit_Subject_Names();
void Store_Subject_Names();
void Store_Length_of_Subject();
void Remove_Subject();
void Clear_All_Subject();

void Add_Subject()                 //   -----Adds a new Subject------------------------------------------   //
{
    int chk;
error:
    printf("______________________________________________________\n");
    printf("******************************************************\n");
    printf("Do you want to add a New Subject??\n\t 1.Yes\n\t2. No\n");
    scanf("%d", &chk);      //---Asking if he wants to add new subject---//
    getchar();

    if (chk == 1)
    {
        printf("______________________________________________________\n");
        printf("******************************************************\n");
        printf("Enter the Name of Subject:");   
        gets(Subject_Names[Number_of_Subject]);    //---Stroing the name of the subject in an array---//
        Length_of_Subject_Names[Number_of_Subject] = strlen(Subject_Names[Number_of_Subject]) + 1;  //---Storing length of Subject Name in an array---//
        Number_of_Subject++;                    //---Increment the NUmber of Subjects---//
        for (int difficulty = 0; difficulty < Number_of_Difficulty_levels; difficulty++)
        {
            Questions_Count[Number_of_Subject - 1][difficulty] = 0;   //---Initializing the Questions in each difficulty level to zero---//
        }

        Store_Subject_Names();          //---Storing the Name in the file---//
        Store_Length_of_Subject();      //---Storing the length of Suject name in file---//
        Set_Counter();                  //---Increment the Number of Subjects in file---//
        printf("______________________________________________________\n");
        printf("******************************************************\n");
        printf("Subject Added\n");             //---Subject added successfully ---//
        printf("______________________________________________________\n");
        printf("******************************************************\n");
    }
    else if (chk == 2)
    {
        return;
    }
    else
    {
        printf("Invalid Input!!!\n");
        goto error;
    }
}

void Edit_Subject_Names()          //   -----Used to edit the names of the Subjects----------------------   //
{
    int subject_no;
    int check;

subject_editor:
    Display_Subjects();         //---Display subjects to choose one of them---//

    printf("Which Subject Name do you want to Change:  ");
    scanf("%d", &subject_no);
    getchar();
    system("cls");
    printf("______________________________________________________\n");
    printf("******************************************************\n");
    printf("Enter the Name of the Subject:  ");        //---Asking to enter the new name of subject---//

    gets(Subject_Names[subject_no - 1]);
    Length_of_Subject_Names[subject_no - 1] = strlen(Subject_Names[subject_no - 1]) + 1;

    Store_Subject_Names();                //---Store the Name in files---//
    Store_Length_of_Subject();            //---Store the length of name in file---//
    system("cls");                        //---Clear Screen---//

    Display_Subjects();

error:
    printf("______________________________________________________\n");
    printf("******************************************************\n");
    printf("1. Change another subject name\n2. Go to menu\n");
    scanf("%d", &check);             //---Asking user if he want to edit another subject name---//
    switch (check)
    {
    case 1:
    {
        goto subject_editor;
        break;
    }
    case 2:
    {
        system("cls");
        return;
    }
    default:
    {
        printf("Invalid Input!!\n");
        goto error;
        break;
    }
    }
}
void Store_Subject_Names()         //   -----Stores the Names of Subjects from arrays to files-----------   //
{
    FILE *Subjects = fopen("Subject_Names.txt", "w");   //---Open in write mode---//

    for (int i = 0; i < Number_of_Subject; i++)
    {
        fputs(Subject_Names[i], Subjects);           //---Store the Names of the Subject in the file fom array---// 
    }
    fclose(Subjects);
}
void Store_Length_of_Subject()    //   -----Stores the Length of Subject Names from arrays to files-----   //
{
    FILE *Length_Subject = fopen("Subject_Length.txt", "w");   //---Open in write mode to clear file---//
    for (int i = 0; i < Number_of_Subject; i++)
    {
        fprintf(Length_Subject, "%d", Length_of_Subject_Names[i]);     //---Store the length of Subject Name in file from array---//
        fputc('\n', Length_Subject);
    }
    fclose(Length_Subject);
}

void Remove_Subject()              //   -----Removes a Subjects Completely from all the Files------------   //
{
    int subject_to_remove;
    Display_Subjects();
    printf("Which Subject do you want to remove??");
    scanf("%d", &subject_to_remove);
    getchar();
    system("cls");
    subject_to_remove--;

    FILE *Questions = fopen("Question_Store.txt", "w");    //---Open all Files in write mode to clear them---//
    FILE *Options = fopen("Options_File.txt", "w");
    FILE *Questions_Counter_File = fopen("Questions_Count_File.txt", "w");
    FILE *Ques_Length = fopen("Length_of_Questions.txt", "w");
    FILE *Opt_Length = fopen("Length_of_Options.txt", "w");

    fprintf(Questions_Counter_File, "%d", (Number_of_Subject - 1));
    fputc('\n', Questions_Counter_File);

    for (int subject = 0; subject < Number_of_Subject; subject++)
    {

        for (int difficulty = 0; difficulty < Number_of_Difficulty_levels; difficulty++)
        {

            if (subject == subject_to_remove)      //---Store everything in the file from arrays but not for that subject to be removed---//
            {
                break;
            }

            fprintf(Questions_Counter_File, "%d", Questions_Count[subject][difficulty]);
            fputc(' ', Questions_Counter_File);

            for (int ques_no = 0; ques_no < Questions_Count[subject][difficulty]; ques_no++)
            {
                fputs(Question_Statements[subject][difficulty][ques_no], Questions);

                fprintf(Ques_Length, "%d", Length_of_Questions[subject][difficulty][ques_no]);
                fputc(' ', Ques_Length);

                for (int i = 0; i < Number_of_Options; i++)
                {
                    fputs(Options_to_choose[subject][difficulty][ques_no][i], Options);
                    fprintf(Opt_Length, "%d", Length_of_Options[subject][difficulty][ques_no][i]);
                    fputc(' ', Opt_Length);
                }
            }
        }
        fputc('\n', Questions_Counter_File);
        fputc('\n', Opt_Length);                   
        fputc('\n', Ques_Length);
    }

    fclose(Questions);
    fclose(Options);
    fclose(Questions_Counter_File);       //---Closing the Files---//
    fclose(Ques_Length);
    fclose(Opt_Length);

    FILE *Subj_Length = fopen("Subject_Length.txt", "w");
    FILE *Subj_Name = fopen("Subject_Names.txt", "w");

    for (int subject = 0; subject < Number_of_Subject; subject++)
    {
        if (subject == subject_to_remove)  //---Store the Subject names and their lengths in file of all subjects except the one to be removed---//
        {
            continue;
        }

        fprintf(Subj_Length, "%d", Length_of_Subject_Names[subject]);
        fputc('\n', Subj_Length);

        fputs(Subject_Names[subject], Subj_Name);
    }

    fclose(Subj_Name);
    fclose(Subj_Length);

exit(0);      //---Exit to clear the arrays---//
}

void Clear_All_Subject()          //   -----Removes all the Subjects from all files---------------------   //
{
    int chk;
input_error:
    printf("Are you sure you want to clear all subjects??\n");
    printf("1. Yes\n2. No\n");
    scanf("%d", &chk);
    getchar();
    system("cls");    //---Clear Screen---//

    if (chk == 2)
    {
        return;
    }
    else if (chk < 1 || chk > 2)
    {
        printf("Invalid Input!!!\n");
        goto input_error;
    }

    FILE *Questions = fopen("Question_Store.txt", "w");
    FILE *Options = fopen("Options_File.txt", "w");
    FILE *Subj_Len = fopen("Subject_Length.txt", "w");     //---Open all files in write mode to clear them---//
    FILE *Subj_Names = fopen("Subject_Names.txt", "w");
    FILE *Length_of_Opt = fopen("Length_of_Options.txt", "w");
    FILE *Length_of_Ques = fopen("Length_of_Questions.txt", "w");
    FILE *Ques_Count = fopen("Questions_Count_File.txt", "w");

    fprintf(Ques_Count, "%d", 0);     //---Store 0 to tell the program that there are 0 current subjects---//
    fputc('\n', Ques_Count);

    fclose(Questions);
    fclose(Options);
    fclose(Subj_Len);
    fclose(Subj_Names);             //---Close all the Files---//
    fclose(Length_of_Opt);
    fclose(Length_of_Ques);
    fclose(Ques_Count);

    printf("Now the program will terminate to complete clearing all the subjects\n");
    exit(0);              //---Exit to clear all the array---//
}
