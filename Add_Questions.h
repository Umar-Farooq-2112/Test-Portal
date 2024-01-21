#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
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

void Read_Subject_Names();
void Read_Length_of_Subject();
void Display_Subjects();
void Store_Length();
void Read_Number_of_Questions();
void Set_Counter();
void Read_Length();
void Read_Questions();
void Store_Questions_in_File();
void Replace_a_Question();
void Add_Questions();

void Add_Questions()              //   -----Adds new Questions------------------------------   //
{
    int difficulty;
    int subject;

Full_Questions_error:
subject_error:

    printf("0. TO go to menu\n");
    Display_Subjects();
    printf("\tChoose the Subject:  ");
    scanf("%d", &subject);   //---Asking for Subject---//
    getchar();     //---Discarding the Enter character to prevent to be stored in the stack---//
    if (subject == 0)
    {
        return;
    }
    if (subject < 1 || subject > Number_of_Subject)  //---Check if Subject is present---//
    {
        system("cls");
        printf("\n\n\t\tNo Subject Found!!!\n");
        goto subject_error;
    }
    system("cls");
difficulty_error:
    printf("\n\n\tChoose a Difficulty Level : 1, 2 or 3.\n");
    scanf("%d", &difficulty);         //---Asking for Difficulty level---//
    getchar();
    if (difficulty < 1 || difficulty > 3)    //---if Difficulty level is valid---//
    {
        system("cls");
        printf("\n\n\t\tInvalid Input!!!\n");
        goto difficulty_error;
    }

    if (Questions_Count[subject - 1][difficulty - 1] >= 500)  //---If More Questions can be stored or not limit is 500---//
    {
        system("cls");
        printf("\n\n\t\tThis Subejct is Already full!!\n\t\tChoose Another Subject");
        goto Full_Questions_error;
    }

addques:
    system("cls");
    printf("______________________________________________________\n");
    printf("******************************************************\n");
    printf("\n\nEnter the Question:  "); //---Asking user to enter the the question and soring it in array---//
    gets(Question_Statements[subject - 1][difficulty - 1][Questions_Count[subject - 1][difficulty - 1]]);
    Length_of_Questions[subject - 1][difficulty - 1][Questions_Count[subject - 1][difficulty - 1]] = strlen(Question_Statements[subject - 1][difficulty - 1][Questions_Count[subject - 1][difficulty - 1]]) + 1;
           //---Storing the Length of the question in an array---//
    printf("______________________________________________________\n");
    printf("******************************************************\n");
    for (int i = 0; i < Number_of_Options; i++)
    {
        //---Taking the Options of the Questions Input---//
        if (i == 0)
        {
            printf("\n\tEnter the correct option: "); 
        }
        else
        {
                printf("______________________________________________________\n");
    printf("******************************************************\n");
            printf("\tEnter the %d", i + 1);
            switch (i)
            {
            case 1:
            {
                printf("nd");
                break;
            }
            case 2:
            {
                printf("rd");
                break;
            }
            case 3:
            {
                printf("th");
                break;
            }
            }
            printf(" Option:  ");
        }
        gets(Options_to_choose[subject - 1][difficulty - 1][Questions_Count[subject - 1][difficulty - 1]][i]);
        Length_of_Options[subject - 1][difficulty - 1][Questions_Count[subject - 1][difficulty - 1]][i] = strlen(Options_to_choose[subject - 1][difficulty - 1][Questions_Count[subject - 1][difficulty - 1]][i]) + 1;
           //---Storing the Length of the Options in an array---//
    }
        printf("______________________________________________________\n");
    printf("******************************************************\n");

    Questions_Count[subject - 1][difficulty - 1] += 1;//---Increment the Number of Questions---//
system("cls");
error:
    printf("\n\n\t1.To add another question\n\t2. to end adding questions\n\tChoose:  ");
    int check;
    scanf("%d", &check);
    getchar();

    if (check == 1)
    {
        if (Questions_Count[subject - 1][difficulty - 1] >= 500)
        {
            Store_Questions_in_File();    //---Storing the Questions in the File---//
            printf("\n\tQuestion Svaed Successfully\n");
            printf("Memory full you cannot add more qustions!!\n");
            goto Full_Questions_error;
        }

        goto addques;
    }
    else if (check == 2)
    {
        Store_Questions_in_File();   //---Storing the Questions in the file---//
        return;
    }
    else
    {
        Store_Questions_in_File();
        printf("\n\tQuestion Svaed Successfully\n");
        printf("\n\tInvalid Operation!!\n");
        goto error;
    }
}

void Replace_a_Question()          //   -----Used to replace a specific question-------------   //
{
    int subject, difficulty, ques_no;
    int chk;

subject_error:
    printf("0. TO go to menu\n");
    Display_Subjects();      //---Display present Subjects---//
    printf("\tChoose the Subject:  ");

    scanf("%d", &subject);   //---Asking user to choose a step---//
    getchar();               //---Store and Discard the Enter character to prevent any error in the stack---//

    if (subject == 0)
    {
        return;
    }
    if (subject < 1 || subject > Number_of_Subject)  //---Check if subject is present---//
    {
        system("cls");
        printf("\n\n\t\tNo Subject Found!!!\n");
        goto subject_error;
    }

difficulty_error:
    printf("Press 0 to cancel.\n");
    printf("\n\n\tChoose a Difficulty Level : 1, 2 or 3.\n");
    scanf("%d", &difficulty);      //---Asking the Difficulty level---//
    if (difficulty == 0)
    {
        return;
    }
    if (difficulty < 1 || difficulty > 3)   //---Checking if the Difficulty level is present or not---//
    {
        system("cls");
        printf("\n\n\t\tInvalid Input!!!\n");   
        goto difficulty_error;
    }

Question_Editor:
ques_error:
    printf("Press 0 to cancel.\n");
    printf("\n\t\t Questions Present:  %d\n", Questions_Count[subject - 1][difficulty - 1]);
    printf("\t\tEnter the Question Number:  ");
cancel:
    scanf("%d", &ques_no);       //---Asking for Question Number---//
    getchar();
    if (ques_no == 0)
    {
        return;
    }
    if (ques_no < 1 || ques_no > Questions_Count[subject - 1][difficulty - 1])//---If Question Number is Present ot not---//
    {
        printf("\n\t\tInvalid Question Number!!\n");
        goto ques_error;
    }
    printf("______________________________________________________\n");
    printf("******************************************************\n");
    printf("Question No %d:  ", ques_no);
    puts(Question_Statements[subject - 1][difficulty - 1][ques_no - 1]);    //---Printing the Question and Options---//

    printf("Correct Answer:  ");
    puts(Options_to_choose[subject - 1][difficulty - 1][ques_no - 1][0]);

    for (int j = 1; j < 4; j++)
    {
        puts(Options_to_choose[subject - 1][difficulty - 1][ques_no - 1][j]);
    }
    printf("______________________________________________________\n");
    printf("******************************************************\n");
    printf("\tDo you want to change this Question?\n\t1. Yes\n\t2. No\n");
    int choose;
    scanf("%d", &choose);
    getchar();

    if (choose == 2)
    {
        printf("\tPress 0 to go to menu\n");
        printf("\n\tEnter Another Question Number: ");
        goto cancel;
    }
    else if (choose == 1)
    {
        //---Taking Input new Question---//
        system("cls");
        printf("______________________________________________________\n");
        printf("******************************************************\n");
        printf("Enter the Question: ");
        gets(Question_Statements[subject - 1][difficulty - 1][ques_no - 1]);
        Length_of_Questions[subject - 1][difficulty - 1][ques_no - 1] = strlen(Question_Statements[subject - 1][difficulty - 1][ques_no - 1]) + 1;
        printf("______________________________________________________\n");
        printf("******************************************************\n");

        printf("Enter the Correct Option:  ");

        gets(Options_to_choose[subject - 1][difficulty - 1][ques_no - 1][0]);
        Length_of_Options[subject - 1][difficulty - 1][ques_no - 1][0] = strlen(Options_to_choose[subject - 1][difficulty - 1][ques_no - 1][0]) + 1;
        printf("______________________________________________________\n");
        printf("******************************************************\n");
        printf("Enter other Options:  ");
        for (int i = 1; i < Number_of_Options; i++)
        {
            gets(Options_to_choose[subject - 1][difficulty - 1][ques_no - 1][i]);
            Length_of_Options[subject - 1][difficulty - 1][ques_no - 1][i] = strlen(Options_to_choose[subject - 1][difficulty - 1][ques_no - 1][i]) + 1;
        }
        printf("______________________________________________________\n");
        printf("******************************************************\n");
        system("cls");
    }
choice_error:
    printf("\n\t\t1. To edit another Quesstion\n\t\t2. Go to Menu");
    scanf("%d", &chk);
    getchar();

    switch (chk)
    {
    case 1:
    {
        system("cls");
        goto Question_Editor;
    }
    case 2:
    {
        system("cls");
        Store_Questions_in_File();//---Storing the Question in the File---//
        printf("Question Saved Successfully\n");
        return;//---End---//
    }
    default:
    {
        printf("Invalid Operation!!!\n");
        goto choice_error;
    }
    }
}
void Store_Questions_in_File()     //   -----Used to copy questions from arrays to files-----   //
{
    FILE *Questions = fopen("Question_Store.txt", "w");     //---Opening the Questions and Options file---//
    FILE *Options = fopen("Options_File.txt", "w");        //---Opening thw wirte mode to clear them before adding---//
    int difficulty;
    int subject;

    for (int subject = 0; subject < Number_of_Subject; subject++)    //---Putting all Questions&Options till last Subject---//
    {
        for (int difficulty = 0; difficulty < Number_of_Difficulty_levels; difficulty++) //---For all Difficulty Levels---//
        {

            for (int ques_no = 0; ques_no < Questions_Count[subject][difficulty]; ques_no++)  //---For the Number of Questions Present---//
            {
                fputs(Question_Statements[subject][difficulty][ques_no], Questions);   //---Puts Questions---//

                for (int option_no = 0; option_no < Number_of_Options; option_no++)    //---Putting all 4 options---//
                {
                    fputs(Options_to_choose[subject][difficulty][ques_no][option_no], Options);   //---Putting Options---//
                }
            }
        }
    }
    Store_Length();     //---Store the Length of the Questions and options in file---// 
    fclose(Questions);
    fclose(Options);
}