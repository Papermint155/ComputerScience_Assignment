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

void CheckInputBlank(char* str){
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
    FILE *file_path = fopen("userdata.bin", "rb"); // 'rb' = read binary
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
void GetMonthlyIncome(int user_idx, int month_idx){

}

void AddRecord(int user_idx) {
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
    printf("] %.2f%%"/*%% so ot can print %*/,percentage); //https://prepinsta.com/c-programming-language-tutorial/how-to-print-percentile-using-printf/
}

/* (Expected Dash board layout)
Hi xxx
--------------------------------------------------------------------------------------
Monthly Income :
Total Spending: 
--------------------------------------------------------------------------------------
Bar Graph
[]
--------------------------------------------------------------------------------------
Financial Status ,Gred , Kaomoji
--------------------------------------------------------------------------------------
Press Any key to Return


*/
void PrintDashBoard(){

}

void CalculateandPrintFinancialStatusandKaomoji(){

}

//Main function
int main (){
    while(1){

    }

    return 0;
}




