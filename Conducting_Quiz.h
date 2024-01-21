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

void delay(int number_of_seconds); //   -----Used to make animations-----------------------------   //

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

extern int Total_Questions_in_the_test;

void Read_Names();
void Store_Marks(int marks);
void Store_Names();
void Store_Total_Marks(int marks);

void test_question_specs();
void shuffle_ques(int Total_Questions);
void copy_array(int temp_ques[Maximum_Number_of_Subjects][Number_of_Difficulty_levels][Maximum_Number_of_Questions]);
void store_quiz_ques();
void shuffle_ans(int Total_Questions);
void copy_quiz_ans();
void Test_Functions(int question_nos[Maximum_Number_of_Questions], int No_of_Questions);
int Calculate_Marks(int No_of_Questions);
void Start_Test(int ques[Maximum_Number_of_Questions], int No_of_Questions);

void skip();


void test_question_specs()                                                                    // Test specifications/No of questions of each subject and each difficulty level
{                                                                                             // are asked from the user + the TIME of the test
time_label:
    printf("______________________________________________________\n");
    printf("******************************************************\n");

    printf("Enter the time for the test in the following manner: (hours, mins)\n");           // time of test asked
    scanf("%d %d", &time_hour, &time_min);
    if (time_hour < 0 || time_hour > 6 || time_min < 0 || time_min > 60)
    {
        printf("Invalid input!!!\n");
        goto time_label;
    }
    int Total_Questions;
    int k = 0;
questions_error:
    printf("______________________________________________________\n");
    printf("******************************************************\n");
    printf("Enter the Number of Questions(less than 500):  ");                                // Total questions in test asked
    scanf("%d", &Total_Questions);
    getchar();
    if (Total_Questions < 1 || Total_Questions > 500)
    {
        printf("Invalid Input!!!\n");
        goto questions_error;
    }
    int remaining_questions;
error:
    remaining_questions = Total_Questions;

    for (int i = 0; i < Number_of_Subject; i++)
    {
        for (int j = 0; j < Number_of_Difficulty_levels; j++)                                 //Types of questions are specified
        {
            printf("Remaining questions: %d\n", remaining_questions);
            printf("Enter the number of questions for %s, Difficulty level %d: ", Subject_Names[i], j + 1);
            scanf("%d", &Test_Specs[i][j]);
            getchar();
            system("cls");
            if (Test_Specs[i][j] > remaining_questions)
            {
                printf("Invalid Input");
                goto error;
            }
            remaining_questions -= Test_Specs[i][j];
            if (remaining_questions==0)
            {
                goto breakk;
            }
        }
    }
    
    breakk:
    if (remaining_questions != 0)                                                               //if the user accidently enters less types of questions than total questions 
    {
        printf("Only %d questions added.\n", Total_Questions - remaining_questions);
        Total_Questions -= remaining_questions;                                                 //total questions are then reduced to question types specified
    }

    Total_Questions_in_the_test=Total_Questions;

    Store_Total_Marks(Total_Questions);                                                         //Total marks of test are stored

    shuffle_ques(Total_Questions);                                                              //Indexes of random questions to use in test are stored
    store_quiz_ques();                                                                          //Randomly generated Questions are copied from Question_Statements array to
    shuffle_ans(Total_Questions);                                                               //the array that stores Questions to be used in test
    int Question_Numbers[Maximum_Number_of_Questions];                                          //For printing question number besides the question statement
    for (int i = 0; i < Total_Questions; i++)
    {
        Question_Numbers[i] = i;
    }
    Start_Test(Question_Numbers, Total_Questions);                                               //Conducts test
}
void shuffle_ques(int Total_Questions)
{
    srand((unsigned)time(0));
    bool Questions_check[Maximum_Number_of_Subjects][Number_of_Difficulty_levels][Maximum_Number_of_Questions] = {false};   //to check if a question has been repeated
    int temp_ques[Maximum_Number_of_Subjects][Number_of_Difficulty_levels][Maximum_Number_of_Questions];                    //to store indexes of questions for shuffling in else condition
    copy_array(temp_ques);                                                                                                  //for copying indexes of questions

    for (int i = 0; i < Number_of_Subject; i++)
    {
        for (int j = 0; j < Number_of_Difficulty_levels; j++)
        {

            if (Test_Specs[i][j] < (Questions_Count[i][j] / 2))                             //if no of questions in test are less than half of those stored then this condition
            {                                                                               //generates random indexes using rand() and that index is stored in Quiz_Question_No array
                int temp_ques_no;
                for (int k = 0; k < Test_Specs[i][j]; k++)
                {
                    do
                    {
                        temp_ques_no = rand() % Questions_Count[i][j];
                        if (!Questions_check[i][j][temp_ques_no])
                        {
                            Quiz_Ques_No[i][j][k] = temp_ques_no;
                            Questions_check[i][j][temp_ques_no] = true;
                            break;
                        }
                    } while (1);
                }
            }
            else                                                                          // if Questions required in test are greater than half of Questions stored then this condition
            {                                                                             // is used bcz it would take a long time for the program to randomly generate so many numbers
                int temp_ques_no;                                                         // if "IF" condition is used
                for (int l = Questions_Count[i][j] - 1; l > 0; l--)
                {
                    temp_ques_no = rand() % (l + 1);                                      // Fisher-Yates shuffle for randomly shuffling the temp_ques array containing indexes of all questions 
                    int temp = temp_ques[i][j][temp_ques_no];
                    temp_ques[i][j][temp_ques_no] = temp_ques[i][j][l];
                    temp_ques[i][j][l] = temp;
                }
                for (int k = 0; k < Test_Specs[i][j]; k++)
                {                                                               
                    Quiz_Ques_No[i][j][k] = temp_ques[i][j][k];                           // the random indexes are then stored in the Quiz_Ques_No array according to the specifications provided by the user
                }
            }
        }
    }
}
void copy_array(int temp_ques[Maximum_Number_of_Subjects][Number_of_Difficulty_levels][Maximum_Number_of_Questions])    //for copying indexes of all questions for shuffling all questions
{
    for (int i = 0; i < Number_of_Subject; i++)
    {
        for (int j = 0; j < Number_of_Difficulty_levels; j++)
        {
            for (int k = 0; k < Questions_Count[i][j]; k++)
            {
                temp_ques[i][j][k] = k;
            }
        }
    }
}
void store_quiz_ques()                                                                                                  //stores question statements for conducting test
{
    int question_no = 0;
    for (int i = 0; i < Number_of_Subject; i++)
    {
        for (int j = 0; j < Number_of_Difficulty_levels; j++)
        {
            for (int k = 0; k < Test_Specs[i][j]; k++)
            {
                strcpy(Quiz_array[question_no], Question_Statements[i][j][Quiz_Ques_No[i][j][k]]);
                question_no++;
            }
        }
    }
}
void shuffle_ans(int Total_Questions)                                                                                   //for shuffling options
{
    copy_quiz_ans();                                                                                                    //copies options of questions according to the sequence of questions in the quiz
    srand((unsigned)time(0));
    for (int i = 0; i < Total_Questions; i++)
    {
        char shuffle_option[Number_of_Options][Maximum_Length_of_Options];                                              //for temporarily storing randomly shuffled options so that they can be copied to Quiz_Ans_array
        bool options[Number_of_Options] = {false};                                                                      //for checking if the option index generated by rand() for each question is not repeated
        for (int j = 0; j < Number_of_Options; j++)
        {
            if (j == 0)                                                                                                 //as the correct ans was stored at the 0th index we do this so we can store its new index in the Quiz_Correct_Ans array
            {
                int correct_ans = rand() % Number_of_Options;                               
                options[correct_ans] = true;                                                                                
                Quiz_Correct_Ans[i] = correct_ans;
                strcpy(shuffle_option[correct_ans], Quiz_Ans_array[i][j]);
            }
            else                                                                                                        //for shuffling the other three options
            {
                int shuffle_ans;
                do
                {
                    shuffle_ans = rand() % Number_of_Options;
                    if (!options[shuffle_ans])
                    {
                        strcpy(shuffle_option[shuffle_ans], Quiz_Ans_array[i][j]);                                      //all the randomly generated options are stored in the shuffle_option array
                        options[shuffle_ans] = true;
                        break;
                    }

                } while (1);
            }
        }
        for (int j = 0; j < Number_of_Options; j++)
        {
            strcpy(Quiz_Ans_array[i][j], shuffle_option[j]);                                                           // the statements from the shuffle_option array are then copied to the Quiz_Ans_array to be displayed in the test    
        }
    }
}
void copy_quiz_ans(void)                                                                                            //copies options of questions according to the sequence of questions in the quiz            
{
    int question_no = 0;
    for (int i = 0; i < Number_of_Subject; i++)
    {
        for (int j = 0; j < Number_of_Difficulty_levels; j++)
        {
            for (int k = 0; k < Test_Specs[i][j]; k++)
            {
                for (int l = 0; l < Number_of_Options; l++)
                {
                    strcpy(Quiz_Ans_array[question_no][l], Options_to_choose[i][j][Quiz_Ques_No[i][j][k]][l]);
                }
                question_no++;
            }
        }
    }
}
void Start_Test(int ques[Maximum_Number_of_Questions], int No_of_Questions)                                 //Name of the student is asked and stored
{

    Read_Names();
    system("cls");
    printf("______________________________________________________\n");
    printf("******************************************************\n");
    printf("\n\tEnter Your Name:  ");
    gets(Names_of_Students[Students]);
    Length_of_Student_Names[Students] = strlen(Names_of_Students[Students]) + 1;
    Students++;
    Store_Names();
    quiz_time_ms = 1000 * ((time_hour * 3600) + (time_min * 60));
    start_time = clock();                                                                                  //Timer is started
    Test_Functions(ques, No_of_Questions);                                                                 //Quiz is started
}

void Test_Functions(int question_nos[Maximum_Number_of_Questions], int No_of_Questions)                     //Questions are displayed with their options
{                                                                                                           
    int No_of_skipped_ques = 0;
    int Skipped_Questions[Maximum_Number_of_Questions];
    int user_input;

    for (int ques_no = 0; ques_no < No_of_Questions; ques_no++)
    {
    Error:
        printf("______________________________________________________\n");
        printf("******************************************************\n");
        printf("Question No %d: ", ques_no + 1);
        puts(Quiz_array[question_nos[ques_no]]);

        for (int opt = 0; opt < Number_of_Options; opt++)
        {
            printf("%d. ", opt + 1);
            puts(Quiz_Ans_array[question_nos[ques_no]][opt]);
        }
        printf("0. To Skip the Question\n");                                                                //The user can skip a question 
                                                                                                            //All the skipped questions will be displayed once the user has gone through all of the questions 
        printf("Enter Your Answer:  ");
        if (clock() >= start_time + quiz_time_ms)
        {
            Store_Marks(Calculate_Marks(Total_Questions_in_the_test));
            return;
        }
        scanf("%d", &user_input);
        getchar();
        if (user_input == 0)
        {
            Skipped_Questions[No_of_skipped_ques] = question_nos[ques_no];
            No_of_skipped_ques++;
        }
        else if (user_input < 1 || user_input > 4)
        {
            system("cls");

            printf("Invalid Input!!!\n\n");
            goto Error;
        }
        else
        {
            Input_Answer[question_nos[ques_no]] = user_input - 1;
        }
        system("cls");
    }

    if (clock() >= start_time + quiz_time_ms || No_of_skipped_ques == 0)
    {
        Store_Marks(Calculate_Marks(Total_Questions_in_the_test));
        return;
    }

    skip();
    Test_Functions(Skipped_Questions, No_of_skipped_ques);                                              //Skipped questions are then displayed again by recursively calling the Test_Function 
                                                                                                        //Function is recursively called until no skipped questions are left
}
int Calculate_Marks(int No_of_Questions)                                                                // Marks of candidate are calculated by comparing the index of answers entered by candidate
{                                                                                                       // to those stored in Quiz_Correct_Ans 
    int marks = 0;
    for (int ques_no = 0; ques_no < No_of_Questions; ques_no++)
    {
        if (Quiz_Correct_Ans[ques_no] == Input_Answer[ques_no])
        {
            marks++;
        }
    }
    printf("Marks: %d\n", marks);                                                             //Marks obtained by student are displayed
    return marks;
}