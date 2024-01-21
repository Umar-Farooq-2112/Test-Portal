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

void Read_a_Question();
void Display_Questions();
void Display_Subjects();

void Display_Questions()           //   -----Displays the Questions of a difficulty level-----   //
{
    int subject, difficulty;
    system("cls");

    if (Number_of_Subject < 1)    //---Checks if any Subject is present---//
    {
        printf("______________________________________________________\n");
        printf("******************************************************\n");
        printf("\n\t\tNo Subject is Present!\n");
        printf("______________________________________________________\n");
        printf("******************************************************\n");
        return;
    }
subject_error:
    Display_Subjects();                       //---Display Subject Names and asks user to choose---//
    printf("Choose the Subject:  ");
    scanf("%d", &subject);
    getchar();

    if (subject < 1 || subject > Number_of_Subject)
    {
        printf("______________________________________________________\n");
        printf("******************************************************\n");

        printf("\n\n\tSubject not Found!!!\n\n");
        printf("______________________________________________________\n");
        printf("******************************************************\n");

        goto subject_error;
    }
    system("cls");
difficulty_error:
    printf("Choose the difficulty level:  ");       //---Asks User to choose difficulty level---//
    scanf("%d", &difficulty);
    getchar();
    if (difficulty < 1 || difficulty > 3)
    {
        printf("______________________________________________________\n");
        printf("******************************************************\n");

        printf("\n\t\tInvalid Input!!!\n");
        printf("______________________________________________________\n");
        printf("******************************************************\n");

        goto difficulty_error;
    }
    system("cls");
    if (Questions_Count[subject - 1][difficulty - 1] == 0)    //---Checks if any Question is present---//
    {
        printf("______________________________________________________\n");
        printf("******************************************************\n");

        printf("No Questions are Present here!!!\n");
        printf("______________________________________________________\n");
        printf("******************************************************\n");

        return;
    }

    for (int ques_no = 0; ques_no < Questions_Count[subject - 1][difficulty - 1]; ques_no++)   //---Prints all the Question in that subject and difficulty---//
    {
        printf("______________________________________________________\n");
        printf("******************************************************\n");
        printf("Question No %d:  ", ques_no + 1);
        puts(Question_Statements[subject - 1][difficulty - 1][ques_no]);

        printf("Correct Answer:  ");
        puts(Options_to_choose[subject - 1][difficulty - 1][ques_no][0]);

        printf("Other Options:  ");
        for (int j = 1; j < 4; j++)
        {
            puts(Options_to_choose[subject - 1][difficulty - 1][ques_no][j]);
        }
        printf("______________________________________________________\n");
        printf("******************************************************\n");
    }
}

void Read_a_Question()             //   -----Display a specific Question----------------------   //
{ /*This Functions ask for subject then difficulty level and then th e question number to dispalythat questions*/
    int subject, difficulty, ques_no;
    if (Number_of_Subject == 0) //---Checks if there is any subject or none---//
    {
        printf("No Subject is Present!\n");
        return;
    }
subject_error:

    Display_Subjects();
    printf("Enter the Subject:  "); //---Ask for the Subject---//
    scanf("%d", &subject);
    if (subject < 1 || subject > Number_of_Subject)
    {
        printf("______________________________________________________\n");
        printf("******************************************************\n");
        printf("\n\t\tSubject Not Found!!!\n\n");
        printf("______________________________________________________\n");
        printf("******************************************************\n");
        goto subject_error;
    }
    system("cls");
difficulty_error:
    printf("Enter the difficulty level:  "); //---Ask for the Difficulty level---//
    scanf("%d", &difficulty);
    if (difficulty < 1 || difficulty > 3)
    {
        printf("______________________________________________________\n");
        printf("******************************************************\n");
        printf("\n\t\tInvalid Input!!!\n");
        printf("______________________________________________________\n");
        printf("******************************************************\n");
        goto difficulty_error;
    }
    if (Questions_Count[subject - 1][difficulty - 1] < 1)
    {
        printf("______________________________________________________\n");
        printf("******************************************************\n\n\t");
        printf("No Questions is Present in this Section!!\n\n");
        printf("______________________________________________________\n");
        printf("******************************************************\n");
        return;
    }
    system("cls");
ques_error:
    printf("Questions Present:    %d \n", Questions_Count[subject - 1][difficulty - 1]);
    //---Ask for the Question Number while displaying the total Number of Questions---//
    printf("Enter the Question Number:  ");
    scanf("%d", &ques_no);
    getchar();
    if (ques_no < 1 || ques_no > Questions_Count[subject - 1][difficulty - 1])
    {
        printf("Invalid Input!!\n");
        goto ques_error;
    }

    printf("______________________________________________________\n");
    printf("******************************************************\n");
    printf("Question No %d:  ", ques_no);                                //---Prints Question Number---//
    puts(Question_Statements[subject - 1][difficulty - 1][ques_no - 1]); //---Prints Question---//

    printf("Correct Answer:  ");
    puts(Options_to_choose[subject - 1][difficulty - 1][ques_no - 1][0]); //---Prints Correct Options---//

    for (int j = 1; j < 4; j++)
    {
        puts(Options_to_choose[subject - 1][difficulty - 1][ques_no - 1][j]); //---Prints other Options---//
    }
    printf("______________________________________________________\n");
    printf("******************************************************\n");
}
