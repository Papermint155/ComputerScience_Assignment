//---Rule---

// Function = ThisIsExample 
// Variable = this_is_example
// Structure = thisIsExample

// Dont use Abbreviation, unless it is common 
// Descripe as detail as possible */ 

//---lib---
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <conio.h> // getch() function

//Global Variable
int current_active_user = -1;
int registered_user = 0; 


// Structure
struct userStudent student_list[5];  

struct userStudent {
    int user_id;
    char user_name [50];
    char user_password[20];
    struct MonthlyData month[12];
    int current_month;
};

struct MonthlyData
{
    char month_name [20];
    double month_income;
    double total_spending;
    struct expensesRecord history[100];
    int record_count; // added record_count here , as if use sizeof() to read the struct the size is the full size ,not the size already with data
};

struct expensesRecord
{
    char category_name[20];
    char expenses_description [50];
    double item_amount;
};

// Function
void ClearScreen(){
    clrscr();
    // printf("\033[H\033[2J"); This method not working (By printing a lot of new line)
    // fflush(stdout); 
}

void RemoveNewLine(char* str){
    str[strcspn(str, "\n")] = '\0';
}

void ClearInputBuffer() { //Clear the memory that used to store the input temperory
    int c;
    while ((c = getchar()) != '\n'); // Discard characters remaining in the input buffer to prevent skipping next input
}

int CheckInputBlank(char* str){ //debug at here, forgot it will return int 
    if (strlen(str) == 0){
        return 1; // 1 = true 
    } 
    for (int i = 0; str[i] != '\0'; i++) { // looping until the null pointer behind the string
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n') return 0; // ' ' <- space, '\t' <- tab, '\n' <- newline char
    }
    return 1;
}

double CheckValidDouble(char* message){
    double value; 
    while (1){
        printf("%s", message);
        if (scanf("%lf",&value) == 1 && value > 0){
            ClearInputBuffer();
            return value;
        } else {
            printf("Please enter a valid positive number for this");
            ClearInputBuffer();
        }
    }
    return value;
}

int SelectOption(char option[][30], int total_choice){
    int current_selection = 0; 
    int input;
    while(1){
        ClearScreen();
        printf("Please use Arrow key(Up and down to select)");

    }
}

void SaveUserData (){
    FILE *file_path = fopen("userdata.bin", "wb"); // 'wb' = write binary
    FILE *file_path = fopen("userdata.txt", "w"); // 'wb' = write binary
    if (file_path == NULL) {//check weather it is no file 
        printf("[!] Error saving data!\n"); //if cant save , print error data
        return;
    }
    // Save the count of users first
    fwrite(&registered_user, sizeof(int), 1, file_path);
    // Save the entire array of student profiles
    fwrite(student_list, sizeof(struct userStudent), 5, file_path);
    fclose(file_path);
}
/* Reference code (https://www.geeksforgeeks.org/c/how-to-write-struct-to-a-binary-file-in-c/)
 // Open a file in binary write mode
    FILE* file = fopen("person_data.bin", "wb");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Write the struct data to the file
    size_t num_written
        = fwrite(&person, sizeof(struct Person), 1, file);
    if (num_written != 1) {
        perror("Error writing to file");
        fclose(file);
        return 1;
    }

    // Close the file
    fclose(file);

    printf("Struct data written to Binary file "
           "successfully.\n");

*/


void LoadUserData(){
    //FILE *file_path = fopen("userdata.bin", "rb"); // 'rb' = read binary , if this can be use in the securuty
    FILE *file_path = fopen("userdata.txt", "r"); // use txt file for visualise the data in it 
    if (file_path == NULL) { // check weather it is no file 
        return; // No file yet, just return without value to exit the funtion
    }
    fread(&registered_user, sizeof(int), 1, file_path); //size_t fread(void *ptr, size_t size, size_t count, FILE *stream) <- the syntax
    fread(student_list, sizeof(struct userStudent), 5, file_path); // read the file according to section ( sizeof(struct userProfile)), read 5 time, and read from file-path then save to student_list
    fclose(file_path);
}
/* Reference code (Other) https://www.geeksforgeeks.org/c/how-to-read-struct-from-binary-file-in-c/
// open the file in rb mode
    FILE* file = fopen("employee_data.bin", "rb");

    // check if the file was successfully opened
    if (file == NULL) {
        perror("Error opening file"); //this is deleted to let the program dont prompt the error (as it is bad to prompt error in first entry)
        return 1;
    }

    // Define the struct
    Employee employee;

    // Read the structs present in the file
    while (fread(&employee, sizeof(Employee), 1, file)
           == 1) {
        // Process the read data (e.g., print or manipulate)
        printf("Employee ID: %d, Name: %s, Salary: %.2f\n",
               employee.id, employee.name, employee.salary);
    }
    // close the file
    fclose(file);
    return 0;
*/
void RegisterUser(){

}

int UserLogin(){

}
void GetMonthlyIncome(int user_index, int month_index){
    struct MonthlyData *selected_month = &student_list[user_index].month[month_index];
    if (selected_month->month_income == 0){
        while (1)
        {
            ClearScreen();
            printf("\n ----- Monthly Income (Month %d) -----\n", month_index + 1);
            printf("Please enter the Month Name(eg. June): ");
            //fget(selected_month->month_name, 20, stdin);
            fget(selected_month->month_name, sizeof(selected_month->month_name), stdin);
            RemoveNewLine(selected_month->month_name);

            if(!CheckInputBlank(selected_month->month_name)){
                break;
            }else{
                printf("Monthly Income only can be a positive and non-zero rational number");
                getch(); //let user have time the see the message
            }
        }
    }
}

void AddRecord(int user_index) {
    int month_index = student_list[user_index].current_month;
    struct MonthlyData *selected_month = &student_list[user_index].month[month_index];

    if (selected_month->record_count > 100){
        printf("The database space is fully oppucied");
        getch();
        return;
    }

    char category_menu[6][30] = {"Back/Return", "Food", "Transport", "Entertainment", "Study", "Bill&Expenses"};// 2D array, first [] is save how may string in the array , second [] is string array.
    int category_choice = SelectMenuOption(category_menu, 6); //pass the array to function, and told them we got how may array (String array in 2D array)
    
    if(category_choice == 0){
        return;
    }
    int adjusted_category_idx = category_choice - 1; // Correctly maps Food to 0, Transport to 1, etc later will use

    struct expenseRecord *new_record = &selected_month->history[selected_month->record_count]; 
    //strcpy(new_record->category_name, category_menu[category_choice]); // copy the string to the structure category_name
    // wait to fix
    

}

void DisplayASCIIGraph(float percentage){
    int star_no = (int) (percentage/2.5);//too long the star
    int star_no = (int) (percentage/5);
    printf("[");
    for (int i = 0; i < 20; i++){
        if (i < star_no){
            printf("*");
        }else{
            printf(" ");
        }
    }
    printf("] %.2f%%"/*%% so it can print %*/,percentage); //https://prepinsta.com/c-programming-language-tutorial/how-to-print-percentile-using-printf/
}

/* (Planning Dash board layout)
Hi xxx
--------------------------------------------------------------------------------------
Monthly Income :
Total Spending: 
Percentage Spend:
--------------------------------------------------------------------------------------
Bar Graph
[]
--------------------------------------------------------------------------------------
Financial Status ,Gred , Kaomoji
--------------------------------------------------------------------------------------
Transcation History
--------------------------------------------------------------------------------------
Press Any key to Return


*/

void CalculateandPrintFinancialStatusandKaomoji(double total_spending, double monthly_income){
    double expense_percentage = (total_spending/monthly_income)*100;
    float budget = monthly_income - total_spending;
    if(expense_percentage >= 0){
        if (expense_percentage < 40.0){
            printf("Excellent Surplus   |Grade: A || ($_$) Simply Lovely! | Budget left: %.2f", budget);
        }else if(expense_percentage < 60.0){
            printf("Healthy Balance     |Grade: B || ( •⌄• )b Looking Good| Budget left: %.2f", budget);
        }else if(expense_percentage < 75.0){
            printf("Modest Savings      |Grade: C || ( -_-) Be Careful... | Budget left: %.2f", budget);
        }else if(expense_percentage < 90.0){
            printf("Modest Savings      |Grade: D || (;O口O) High Risk!   | Budget left: %.2f", budget);
        }else{
            printf("Modest Savings      |Grade: F || (T _ T) Budget Crisis| Budget left: %.2f", budget);
        };
    }else{
        printf("Somthing is wrong with the program!!");// for debug use
    }
    
}

void PrintDashBoard(int user_index, int month_index){
    struct MonthlyData *selected_month = &student_list[user_index].month[month_index];
    double warning_line = selected_month->month_income*0.15;
    float percentage;
    printf("Hi, %s : Month : %s \n",student_list[user_index].user_name, selected_month->month_name);
    printf("--------------------------------------------------------------------------------------\n");
    printf("Monthly Income: %lf\n", selected_month->month_income);
    printf("Total Spending: %lf\n", selected_month->total_spending);
    printf("Percentage Spend: %.2f%%\n", (selected_month->total_spending/selected_month->month_income));
    printf("--------------------------------------------------------------------------------------\n");
    DisplayASCIIGraph(percentage);
    printf("--------------------------------------------------------------------------------------\n");
    CalculateandPrintFinancialStatusandKaomoji(selected_month->total_spending,selected_month->month_income);
    printf("--------------------------------------------------------------------------------------\n");
    printf("Transaction History\n");
    for (int i = 0; i < selected_month->record_count ;i++){
        struct expensesRecord *record = &selected_month->history[i];

        char noted = (record->item_amount > warning_line)? '  !  ': '     '; 
        //(condition) ? if true : if false

        printf("No.|      Category      |                Description              | Flag|Amount");
        printf("%03d|%-20s|%-20.20s|%c|%-6.2f|", i, record->category_name, record->expenses_description, noted, record->item_amount);
        
    }

    if (selected_month->record_count == 0){
        printf("No record found in Month %s",selected_month->month_name);
    }
    printf("--------------------------------------------------------------------------------------\n");
    printf("Press Any key to Return");
    getch();

}

//Main function
int main (){
    while(1){

    }

    return 0;
}




