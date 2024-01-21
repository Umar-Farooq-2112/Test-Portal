#pragma warning(disable : 4996)          //   -----To Prevent Error in the Visual Studio-----   //

                                // -----Header Files----- //

#include <stdio.h>     //   -----Standard Input/Output Library----- ---------------------------------------  //
#include <stdlib.h>    //   -----Standard Library for srand,exit and many other functions-----------------   // 
#include <stdbool.h>   //   -----Standard Library for Bool Operations-------------------------------------   //
#include <string.h>    //   -----Standard Library for String Operations-----------------------------------   //
#include <time.h>      //   -----Standrd Library for Time Operations like Delay and Timer during test-----   //

                                // -----External Files Used in the Program----- // 
#include "Add_Questions.h"         //   -----External File for Questions addition and replacement functions------------------   //
#include "Basic_Functions.h"       //   -----File that stores major functions used frequently in many other files------------   //
#include "Conducting_Quiz.h"       //   -----File containing functions for conductiong tests---------------------------------   //
#include "Display_Functions.h"     //   -----Contains functions for displaying questions or any questions--------------------   //
#include "Intro.h"                 //   -----Contains function for displaying intro only once when the program starts--------   //
#include "Marks.h"                 //   -----Containg functions to store or clear marks from the external files--------------   //
#include "Menu.h"                  //   -----Contains function Display and call the Menu-------------------------------------   // 
#include "Subject_Files.h"         //   -----Contains functions for adding editing or removing subjects----------------------   // 
#include "End_Test.h"              //   -----Contains function to display the end of the test--------------------------------   //
#include "skip.h"                  //   -----Contains function to display test when the user jumps to skipped questions------   //

                                // -----Macros Used in the Program----- //
#define Maximum_Number_of_Questions 500               //   -----One difficulty level can have maximum of 500 Questions-----   //
#define Maximum_Length_of_Questions 500               //   -----Maximum length of a question can be 500 characters---------   //
#define Maximum_Length_of_Options 100                 //   -----Maximum length of optipns can be 100 characters------------   //
#define Number_of_Options 4                           //   -----The Number of Options for a Question is 4------------------   //
#define Maximum_Number_of_Subjects 50                 //   -----Maximum Number of subject you can add is 50----------------   //
#define Maximum_Length_of_Subject_Names 50            //   -----Maximum Length of Subject Names can be 50 Characters-------   //
#define Number_of_Difficulty_levels 3                 //   -----Number of Difficulty levels for a Subject is 3-------------   //

                                // -----Global Arrays,String and Variables Used in the Program----- //

char Question_Statements[Maximum_Number_of_Subjects][Number_of_Difficulty_levels][Maximum_Number_of_Questions][Maximum_Length_of_Questions];
        //   -----Stores all the questions according to subject and difficulty levels in different dimensions-----------------   //
char Options_to_choose[Maximum_Number_of_Subjects][Number_of_Difficulty_levels][Maximum_Number_of_Questions][Number_of_Options][Maximum_Length_of_Options];
        //   -----Stores all the options according to subject and difficulty levels and questions in different dimensions-----   //
int Length_of_Questions[Maximum_Number_of_Subjects][Number_of_Difficulty_levels][Maximum_Number_of_Questions];
        //   -----Stores the Length of the Questions--------------------------------   //
int Length_of_Options[Maximum_Number_of_Subjects][Number_of_Difficulty_levels][Maximum_Number_of_Questions][Number_of_Options];
        //   -----Stores the Length of the Options----------------------------------   //
int Questions_Count[Maximum_Number_of_Subjects][Number_of_Difficulty_levels];
        //   -----Stores the number of Questions in different difficulty levels-----   //
char Subject_Names[Maximum_Number_of_Subjects][Maximum_Length_of_Subject_Names];
        //   -----Stores the Names of Subjects--------------------------------------   //
int Number_of_Subject;
        //   -----Stores the Present Number of Subjects-----------------------------   //
int Length_of_Subject_Names[Maximum_Number_of_Subjects];
        //   -----Stores the Length of the Subject Names----------------------------   //
int Test_Specs[Maximum_Number_of_Subjects][Number_of_Difficulty_levels];
        //   -----Stores the Number of Questions from Different Difficult levels for the quiz---------------------------   // 
int Quiz_Ques_No[Maximum_Number_of_Subjects][Number_of_Difficulty_levels][Maximum_Number_of_Questions];
        //   -----Stores the Indexes of Questions for the Quiz (Indexes according to the Question_Statements array)-----   //
char Quiz_array[Maximum_Number_of_Questions][Maximum_Length_of_Questions];
        //   -----Stores the Statements of the Questions in accordance of showing them in the test----------------------   //
int Quiz_Correct_Ans[Maximum_Number_of_Questions];
        //   -----Stores the Index of Correct Answers the for the Quiz--------------   //
char Quiz_Ans_array[Maximum_Number_of_Questions][Number_of_Options][Maximum_Length_of_Options];
        //   -----Stores the Options of the Quiz------------------------------------   //
int Input_Answer[Maximum_Number_of_Questions];
        //   -----Stores the Answers entered by the User----------------------------   //
char Names_of_Students[1000][Maximum_Length_of_Options];
        //   -----Stores the Names of Students in the Files that had quizzes--------   //
int Length_of_Student_Names[1000];
        //   -----Stores the Length of Student Names--------------------------------   //
int Students, time_min;
        //   -----Number of Students in the Files whose Marks are Present-----------   //
int time_hour, quiz_time_ms;
        //   -----Time for the Quiz Hours and Minutes-------------------------------   //
clock_t start_time;

int Total_Questions_in_the_test;

                                // -----Prototypes of all the Functions used the Program----- //

                                         // -----Basic_Functions.h-----   //
void Display_Subjects();           //   -----Display the Present Subject--------------------------------   //
void Set_Counter();                //   -----Stores the Number of Questions and Subjects in a file------   //
void Read_Length_of_Subject();     //   -----Copys the Length of Subject Names from files to arrays-----   //
void Read_Subject_Names();         //   -----Copys the Names of Subject names from files to arrays------   //
void Read_Length();                //   -----Reads the Length of Questions and Options------------------   //
void Store_Length();               //   -----Stores the Length of Questions and Options-----------------   // 
void Read_Questions();             //   -----Reads the Questions from files and stores in array---------   //
void Read_Number_of_Questions();   //   -----Reads the Number of Questions in a difficulty level--------   //

                                         // -----Add_Questions.h-----   //
void Add_Questions();              //   -----Adds new Questions------------------------------   //
void Replace_a_Question();         //   -----Used to replace a specific question-------------   //
void Store_Questions_in_File();    //   -----Used to copy questions from arrays to files-----   //

                                         // -----Display_Function.h-----   //
void Display_Questions();          //   -----Displays the Questions of a difficulty level-----   //
void Read_a_Question();            //   -----Display a specific Question----------------------   //

                                         // -----Intro.h-----   //
void start_program();              //   -----Display the Intro only once when program starts-----   //
void delay(int number_of_seconds); //   -----Used to make animations-----------------------------   //

                                         // -----skip.h-----   //
void skip();                        //   -----Display that user is jumping to skipped questions-----   //

                                         // -----Marks.h-----   //
void Read_Names();                 //   -----Copies the Names of the Students from the Files to arrays-----   //
void Store_Names();                //   -----Stores the Names of the Students in the Files-----------------   //
void Store_Marks(int marks);       //   -----Stores the Marks of the Test in the Files---------------------   //
void Display_Results();            //   -----Display the Results of Tests Conducted------------------------   //
void Clear_Marks();                //   -----Clears the Marks and names from the files---------------------   //
void Store_Total_Marks(int marks); //   -----Stores the Total Marks in the File----------------------------   //

                                         // -----End_Test.h-----   //
void End_Test();                   //   -----Displays that test has ended-----   //

                                         // -----Menu.h-----   //
int menu();                        //   -----Displays the Menu Function-----   //

                                         // -----Subject_Files.h-----   //
void Add_Subject();                //   -----Adds a new Subject------------------------------------------   //
void Edit_Subject_Names();         //   -----Used to edit the names of the Subjects----------------------   //
void Store_Subject_Names();        //   -----Stores the Names of Subjects from arrays to files-----------   //
void Store_Length_of_Subject();    //   -----Stores the Length of Subject Names from arrays to files-----   //
void Remove_Subject();             //   -----Removes a Subjects Completely from all the Files------------   //
void Clear_All_Subject();          //   -----Removes all the Subjects from all files---------------------   //


                                         // -----Conductiong_Quiz.h-----   //
void test_question_specs();                       //   -----Inputs the number of questions from each subject and difficulty levels from the user-----   //
void shuffle_ques(int Total_Questions);           //   -----Shuffle the Questions in a specific Condition--------------------------------------------   //
void copy_array(int temp_ques[Maximum_Number_of_Subjects][Number_of_Difficulty_levels][Maximum_Number_of_Questions]);  //   -----Copies the Number of Questions in an array-----   //
void store_quiz_ques();                           //   -----Copys the Questions for ine quiz in the quiz array---------------------------------------   //
void shuffle_ans(int Total_Questions);            //   -----Shuffles the Answers of the options for the quiz-----------------------------------------   //
void copy_quiz_ans();                             //   -----Copys the Quiz Answer's Indexes in an array----------------------------------------------   //
void Test_Functions(int question_nos[Maximum_Number_of_Questions], int No_of_Questions);       //   -----Used to Start the Test & Ask Name-----------   // 
int Calculate_Marks(int No_of_Questions);                                                      //   -----Calcultes the Marks after test--------------   //
void Start_Test(int ques[Maximum_Number_of_Questions], int No_of_Questions);                   //   -----Used to Conduct the test--------------------   //


int main()     //    Main Function    //
{
    int menu_call;
    start_program();              // Present the intro present in Intro.h file //
    system("cls");                // clears the screen after the intro for further tasks //
    Read_Number_of_Questions();   // Reads the Number of Questions Stored in the Files by file handling //
    Read_Length();                // Reads the length of questions and their options using file handling operations //
    Read_Questions();             // Reads the questions/options and from files by file handling operations and stores them in multi dimensional arrays and strings //
    Read_Length_of_Subject();     // Reads the Length of Subjects already present //
    Read_Subject_Names();         // Reads the Names of the Subejcts already present //

    while (1)
    {
        menu_call = menu();     //    Calling the Menu Function in Menu.h file    // 

        switch (menu_call)
        {
        case 1:                // User choose to take a quiz //
        {
            test_question_specs();   // Calls for conducting test //
            End_Test();              // Displays the end test screen //
            exit(0);                 // Exits the program after the test ends //
            break;
        }
        case 2:                // user chooses to add questions in the already present subjects //
        {
            Add_Questions();         // Calls functions to add questions to bank //
            Set_Counter();           // Stores the length of QUestions and options in the file using File Handling operations
            break;
        }
        case 3:                // User chooses to Display Questions of any subject at a specific difficulty  //
        {
            Display_Questions();     // Displays all the questions of a speciifc difficulty level of a specific subject //
            break;
        }
        case 4:                // User chooses to read/display a specific questions //
        {
            Read_a_Question();       // Displays a specific Question according to the question number the user enters //
            break;
        }
        case 5:                // user chooses to replace/ change a specific question from the question bank //
        {
            Replace_a_Question();    // Calls the function to replace a specific questions by another //
            break;
        }
        case 6:                // user chooses to display the list of present subjects //
        {
            Display_Subjects();      // Calls the function to display the present subjects //
            break;
        }
        case 7:                // user chooses to change an already subject's nme //
        {
            Edit_Subject_Names();    //  Calls the function to edit the subject names //
            break;
        }
        case 8:                // user chooses to add a new subject //
        {
            Add_Subject();           // Calls the function to add a new subject //
            break;
        }
        case 9:                // user chooses to completely remove a specific subject from the qustions bank //
        {
            Remove_Subject();        // Calls the Function to remove a specific subject //
            break;
        }
        case 10:               // user chooses to completely empty the questions bank and remove all the questions/options and subjects //
        {
            Clear_All_Subject();      // Calls the Function to remove all the present subject //
            break;
        }
        case 11:               // user chooses to view the rsults of the tests conducted //
        {
            Display_Results();        // Calls the funtion to display the results of tests conducted // 
            break;
        }
        case 12:               // user chooses to clear the marks of previously conducted tests  //
        {
            Clear_Marks();            // Calls the function to clear all the present marks and names //
            break;
        }
        case 13:               // user chooses to end the program //
        {
            exit(0);                  // Exits the program //
        }
        default:               // user inputs an invalid operation to perform that is not present //
        {
            printf("Invalid Input!!!\n");   // Invalid Operation display //
            break;
        }
        }
        printf("Press Enter to go to Menu\n");    // after any function user is asked to go to menu here before clearing the screen and going to menu //
        getchar();             // Stores and discard the Enter pressed // 
    }
}
