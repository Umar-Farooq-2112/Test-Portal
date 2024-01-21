#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>


#define Maximum_Number_of_Questions 500
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

extern int Input_Answer[Maximum_Number_of_Questions];
extern char Names_of_Students[1000][Maximum_Length_of_Options];
extern int Length_of_Student_Names[1000];
extern int Students, time_min, time_hour, quiz_time_ms;
extern clock_t start_time;


void Read_Subject_Names();
void Read_Length_of_Subject();
void Display_Subjects();
void Store_Length();
void Read_Number_of_Questions();
void Set_Counter();
void Read_Length();
void Read_Questions();

void Read_Questions()             //   -----Reads the Questions from files and stores in array---------   //
{

    FILE *Questions = fopen("Question_Store.txt", "r");      //---Opens files in read mode---//
    FILE *Options = fopen("Options_File.txt", "r");

    for (int subject = 0; subject < Number_of_Subject; subject++)   //---Reads all the Questions and Options and stores them in a Multi dimensional array---//
    {

        for (int difficulty = 0; difficulty < 3; difficulty++)
        {
            for (int question_no = 0; question_no < Questions_Count[subject][difficulty]; question_no++)
            {
                fgets(Question_Statements[subject][difficulty][question_no], Length_of_Questions[subject][difficulty][question_no], Questions);

                for (int options_no = 0; options_no < Number_of_Options; options_no++)
                {
                    fgets(Options_to_choose[subject][difficulty][question_no][options_no], Length_of_Options[subject][difficulty][question_no][options_no], Options);
                }
            }
        }
    }

    fclose(Questions);
    fclose(Options);
}

void Read_Length()                //   -----Reads the Length of Questions and Options------------------   //
{
    FILE *Length_of_Opt = fopen("Length_of_Options.txt", "r");      //---Open Files in Read Mode---//
    FILE *Length_of_Ques = fopen("Length_of_Questions.txt", "r");

    for (int subject = 0; subject < Number_of_Subject; subject++)   //---Copy the Length of Questions and Options of all subjects in arrays---//
    {
        for (int difficulty = 0; difficulty < Number_of_Difficulty_levels; difficulty++)
        {
            for (int ques_no = 0; ques_no < Questions_Count[subject][difficulty]; ques_no++)
            {
                fscanf(Length_of_Ques, "%d", &Length_of_Questions[subject][difficulty][ques_no]);  //---Copy length of Questions in array---//

                for (int i = 0; i < Number_of_Options; i++)
                {
                    fscanf(Length_of_Opt, "%d", &Length_of_Options[subject][difficulty][ques_no][i]);    //---Copy length of Options in the array---//
                }
            }
        }
    }
    fclose(Length_of_Ques);
    fclose(Length_of_Opt);
}

void Read_Number_of_Questions()   //   -----Reads the Number of Questions in a difficulty level--------   //
{
    FILE *Counter = fopen("Questions_Count_File.txt", "r");      //---Open the file in read mode---//

    fscanf(Counter, "%d", &Number_of_Subject);       //---First read the Number of Subjects and store in the variable---//

    for (int subject = 0; subject < Number_of_Subject; subject++)
    {
        for (int difficulty = 0; difficulty < Number_of_Difficulty_levels; difficulty++)
        {
            fscanf(Counter, "%d", &Questions_Count[subject][difficulty]);    //---Read the Number of Questions and store in an array---//
        }
    }
    fclose(Counter);
}
void Set_Counter()                //   -----Stores the Number of Questions and Subjects in a file------   //
{
    FILE *Counter = fopen("Questions_Count_File.txt", "w");

    fprintf(Counter, "%d", Number_of_Subject);      //---Stores the Number of Subjects---//
    fputc('\n', Counter);          //---Move to next line---//

    for (int i = 0; i < Number_of_Subject; i++)
    {
        for (int j = 0; j < Number_of_Difficulty_levels; j++)
        {
            fprintf(Counter, "%d", Questions_Count[i][j]);   //---Store the Number of Questions in difficulty levels of all subjects---//
            fputc('\n', Counter);    //---Move to Next line to keep the lengths separated---//
        }
    }
    fclose(Counter);
}



void Store_Length()               //   -----Stores the Length of Questions and Options-----------------   // 
{
    FILE *Length_of_Opt = fopen("Length_of_Options.txt", "w");
    FILE *Length_of_Ques = fopen("Length_of_Questions.txt", "w");     //---Open the Files in write mode to clear the,---//

    for (int subject = 0; subject < Number_of_Subject; subject++)
    {
        for (int difficulty = 0; difficulty < Number_of_Difficulty_levels; difficulty++)
        {
            for (int ques_no = 0; ques_no < Questions_Count[subject][difficulty]; ques_no++)
            {
                fprintf(Length_of_Ques, "%d", Length_of_Questions[subject][difficulty][ques_no]);   //---Stroing the length of the Questions in file from array---//
                putc(' ', Length_of_Ques);
                for (int i = 0; i < Number_of_Options; i++)
                {
                    fprintf(Length_of_Opt, "%d", Length_of_Options[subject][difficulty][ques_no][i]);    //---Storing the Lengh of the options in the file ---//
                    putc(' ', Length_of_Opt);
                }
                putc('\n', Length_of_Opt);
            }
        }
    }
    fclose(Length_of_Ques);
    fclose(Length_of_Opt);
}

void Display_Subjects()           //   -----Display the Present Subject--------------------------------   //
{
    printf("______________________________________________________\n");
    printf("******************************************************\n");

    for (int i = 0; i < Number_of_Subject; i++)     //---Print all the Subjects using loop---//
    {
        printf("\t%d.   ", i + 1);
        puts(Subject_Names[i]);
    }
    printf("______________________________________________________\n");
    printf("******************************************************\n");

}


void Read_Length_of_Subject()     //   -----Copys the Length of Subject Names from files to arrays-----   //
{
    FILE *Names = fopen("Subject_Length.txt", "r");  //---Open File in Read Mode---//

    for (int subject = 0; subject < Number_of_Subject; subject++)   //---Read the Length of Subject Names---//
    {
        fscanf(Names, "%d", &Length_of_Subject_Names[subject]);
    }
}
void Read_Subject_Names()         //   -----Copys the Names of Subject names from files to arrays------   //
{
    FILE *Subject_Namex = fopen("Subject_Names.txt", "r"); //---Open the file in read mode---//
    for (int i = 0; i < Number_of_Subject; i++)   //---Copy Names of all Subjects in arrays---//
    {
        fgets(Subject_Names[i], Length_of_Subject_Names[i], Subject_Namex);
    }
}