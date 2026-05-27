//---Rule---

// Function = ThisIsExample 
// Variable = this_is_example
// Structure = thisIsExample

// Dont use Abbreviation, unless it is common 
// Descripe as detail as possible */ 

//---lib---
#include <stdio.h>
#include <stdlib.h> // fixed system cls
#include <string.h>
#include <math.h> // for isnan() function 
#include <conio.h> // getch() function

//Global Variable
int current_active_user = -1;
int registered_user = 0; 


// Structure (bug fixed the structure need to from lowest to highest)

struct expensesRecord
{
    char category_name[20];
    char expenses_description [50];
    double item_amount;
};

struct MonthlyData
{
    char month_name [20];
    double month_income;
    double total_spending;
    double category_totals[5]; // Food, Transport, Entertainment, Study, Bill&Expenses
    struct expensesRecord history[100];
    int record_count; // added record_count here , as if use sizeof() to read the struct the size is the full size ,not the size already with data
};

struct userStudent {
    int user_id;
    char user_name [50];
    char user_password[20];
    struct MonthlyData month[12];
    int current_month;
};

struct userStudent student_list[5];  

// Function
void ClearScreen(){
    system("cls");
    //clrscr(); cant use (got bug)
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

double CheckValidDouble(char *message){ // puting * to wrong (solve)
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

int SelectOption(char option[][30], int total_choice){ // havent conplete yet 
    int current_selection = 0; 
    int input;
    while(1){
        ClearScreen();
        printf("Please use Arrow key(Up and down to select)\n");//minor update forgot to put \n
        for(int i = 0; i < total_choice; i++){
            if (i == current_selection){
                printf("-> %s\n", option[i]);
            } else {
                printf("   %s\n", option[i]);
            }
        }
        int key_pressed = getch(); // force change to ascii
        if (key_pressed == 224) { // check the thing is it an unsign character https://stackoverflow.com/questions/13990600/how-to-detect-arrow-keys
            key_pressed = getch();
            if (key_pressed == 72) current_selection = (current_selection - 1 + total_choice) % total_choice; // code for up 
            if (key_pressed == 80) current_selection = (current_selection + 1) % total_choice; //code for down 
        } else if (key_pressed == 13) return current_selection; //code for enter 
    }
    /*Press down 
    0 + 1 = 1 % 3 = 1
    1 + 1 = 2 % 3 = 2
    2 + 1 = 3 % 3 = 0
    etc
    Press up
    0 - 1 + 3 = 2 % 3 = 2
    2 - 1 + 3 = 4 % 3 = 1
    1 - 1 + 3 = 3 % 3 = 0
    etc
    */
}

void SaveUserData (){
    //FILE *file_path = fopen("userdata.bin", "wb"); // 'wb' = write binary
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
    ClearScreen(); //added clear screen 
    if (registered_user >= 5) { //check the count < 5 , prevent overflow
        printf("Maximum user limit reached.\n"); // reject add account if already achieve the max number 
        getch(); //wait till the user want to proceed 
        return;
    }
    
    struct userStudent *new_student = &student_list[registered_user];
    char temp_input[150]; // Use a larger buffer to catch the overflow to let user enter over 50 

    //Username Loop (same logic as the name part)
    while (1) {
        printf("---Register New User--- (press 0 to cancel)\n"); // update the message to register new user
        printf("Username (Max 20): ");
        fgets(temp_input, sizeof(temp_input), stdin);

        // Check for Return/Cancel first
        if (strcmp(temp_input, "0\n") == 0) return; //if cancel then exit to main menu

        if (strchr(temp_input, '\n') == NULL) {
            printf("[!] Error: Username too long!\n");
            ClearInputBuffer();
            getch();
            ClearScreen();
            continue;
        }

        RemoveNewLine(temp_input);
        if (strlen(temp_input) >= 20 || CheckInputBlank(temp_input)) {
            printf("[!] Error: Username must be 1-19 characters.\n");
            getch();
            ClearScreen();//ClearScreen if error message
            continue;
        }
        strcpy(new_student->user_name, temp_input); 
        break;
    }

    //Password Loop 
    while (1) {
       printf("Password (Max 20): ");
        fgets(temp_input, sizeof(temp_input), stdin);

        if (strchr(temp_input, '\n') == NULL) {
            printf("[!] Error: Password too long!\n");
            ClearInputBuffer();
            getch();
            continue;
        }

        RemoveNewLine(temp_input);
        if (strlen(temp_input) >= 20 || CheckInputBlank(temp_input)) {
            printf("[!] Error: Password must be 1-19 characters.\n");
            ClearInputBuffer();
            getch();
            continue;
        }
        strcpy(new_student->user_password, temp_input); 
        break;
    }

    new_student->current_month = 0; //set the new student month index to 0 as he is new user
    registered_user++; //add the register user count 
    SaveUserData();
    printf("\nNew User Registration Success! \nPress any key to continue...");
    getch(); //wait till the user want to proceed ;
}

int UserLogin(){ // same logic as above so i direct use the code from register part and change the message and the logic of check username and password
    int user_index;
    char input_username[25], input_password[25]; // Use slightly larger buffers to detect
    ClearScreen();
    if(registered_user == 0){ // if no user in the system, then directly return to main menu
        printf("No user found. Please register first! \nPress any key to return...");
        getch();
        return -1; // return -1 to indicate login failure
    }
    //Username Loop (same logic as the name part)
    while (1) {
        printf("---Login--- (press 0 to cancel)\n"); // update the message to login
        printf("Username (Max 20): ");
        fgets(input_username, sizeof(input_username), stdin);

        // Check for Return/Cancel first
        if (strcmp(input_username, "0\n") == 0) return -1; //if cancel then exit to main menu

        if (strchr(input_username, '\n') == NULL) {
            printf("[!] Error: Username too long!\n");
            ClearInputBuffer();
            getch();
            ClearScreen();
            continue;
        }

        RemoveNewLine(input_username);
        if (strlen(input_username) >= 20 || CheckInputBlank(input_username)) {
            printf("[!] Error: Username must be 1-19 characters.\n");
            getch();
            ClearScreen();
            continue;
        }
        break;
    }

    //Password Loop 
    while (1) {
       printf("Password (Max 20): ");
        fgets(input_password, sizeof(input_password), stdin);

        if (strchr(input_password, '\n') == NULL) {
            printf("[!] Error: Password too long!\n");
            ClearInputBuffer();
            getch();
            continue;
        }

        RemoveNewLine(input_password);
        if (strlen(input_password) >= 20 || CheckInputBlank(input_password)) {
            printf("[!] Error: Password must be 1-19 characters.\n");
            continue;
        }
        break;
        ClearInputBuffer();
    }
    for (int i = 0; i < registered_user; i++) { //loop through the student list to find the username and the password got match??
        if (strcmp(input_username, student_list[i].user_name) == 0 && strcmp(input_password, student_list[i].user_password) == 0) {
            return i; // if have match return the index of the student in the array 
        }
    }
    printf("\n[!] Invalid login. \nPress any key to continue...");
    getch();
    return -1;
}
void GetMonthlyIncome(int user_index, int month_index){
    struct MonthlyData *selected_month = &student_list[user_index].month[month_index];
    if (selected_month->month_income == 0){

        while (1) {
            ClearScreen();
            printf("----- Monthly Income (Month %d) -----\n", month_index + 1);
            printf("Please enter the Month Name(eg. June): ");
            //fget(selected_month->month_name, 20, stdin);
            fgets(selected_month->month_name, sizeof(selected_month->month_name), stdin);
            RemoveNewLine(selected_month->month_name);

            if(!CheckInputBlank(selected_month->month_name)){
                break;
            }else{
                printf("[!] Error: Month name cannot be empty.\n");
                getch(); //let user have time the see the message
            }
        }
        selected_month->month_income = CheckValidDouble("Set Monthly Income: ");// debug missing asking value // move out of while loop

        SaveUserData();
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
    int category_choice = SelectOption(category_menu, 6); //pass the array to function, and told them we got how may array (String array in 2D array)
    
    if(category_choice == 0){
        return;
    }
    int adjusted_category_idx = category_choice - 1; // Correctly maps Food to 0, Transport to 1, etc later will use

    struct expensesRecord *new_record = &selected_month->history[selected_month->record_count]; //(here is the problem)
    strcpy(new_record->category_name, category_menu[category_choice]); // copy the string to the structure category_name , (fixed)

    while (1) {
        ClearScreen();  
        printf("Enter Item Description (Max 49 chars): ");
        fgets(new_record->expenses_description, sizeof(new_record->expenses_description), stdin);
        RemoveNewLine(new_record->expenses_description); //fixed the enter bug cause misallingmnet of the string
        if (new_record->expenses_description != NULL) { // check the value enter isnt a null value
            break;
        }
        if (strchr(new_record->expenses_description, '\n')) {//strchr: standard library function used to locate the first occurrence of a specific character within a null-terminated string (search the "/n" character in the Description)
            RemoveNewLine(new_record->expenses_description); //then pass it to this function to remove the "\n"
            if (strlen(new_record->expenses_description) == 0) { // check the string is it empty?
                printf("[!] Error: Description cannot be empty.\n"); // do if empty
                continue; // this call the function continue the while loop dont jump to the break below
            }
            break; // if all ok, break this loop
        } else {
            printf("[!] Error: Description too long! Please keep it under 50 characters.\n"); // if cant find the "\n" mean it has been cut off from the string array (another word the string is to long)
            ClearInputBuffer(); // clear the leftover data in the input memory
        }
    }
    new_record->item_amount = CheckValidDouble("Enter the amount for this item: $"); // get the amount and check is it valid or not

    selected_month->category_totals[adjusted_category_idx] += new_record->item_amount; 
    selected_month->total_spending += new_record->item_amount; // after get the amount, add it to the total spending
    selected_month->record_count++; // as one record get add, update the array count

    SaveUserData(); // save the data immediately after add record to prevent data lose
    printf("\nRecord added successfully! Press any key..."); //inform user
    getch(); //wait till the user want to proceed
}

void DisplayASCIIGraph(float percentage){
    int star_no = (int) (percentage/2.5);//too long the star (test)
    if (percentage < 0) percentage = 0;
    else if (isnan(percentage)) percentage = 0; // if the percentage is not a number (NaN), set it to 0
    //int star_no = (int) (percentage/5);
    printf("[");
    for (int i = 0; i < 40; i++){
        if (i < star_no){
            printf("*");
        }else{
            printf(" ");
        }
    }
    printf("] %.2f%%\n"/*%% so it can print %*/,percentage); //https://prepinsta.com/c-programming-language-tutorial/how-to-print-percentile-using-printf/
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
            printf("Excellent Surplus   |Grade: A || ($_$) Simply Lovely! | Budget left: %.2f\n", budget); //Ciallo～(∠・ω< )⌒☆ (Easter_egg)
        }else if(expense_percentage < 60.0){
            printf("Healthy Balance     |Grade: B || ( •⌄• )b Looking Good| Budget left: %.2f\n", budget); //Ciallo～(∠・ω< )⌒☆ (Easter_egg)
        }else if(expense_percentage < 75.0){
            printf("Modest Savings      |Grade: C || ( -_-) Be Careful... | Budget left: %.2f\n", budget); //Ciallo～(∠・ω< )⌒☆ (Easter_egg)
        }else if(expense_percentage < 90.0){
            printf("Modest Savings      |Grade: D || (;O口O) High Risk!   | Budget left: %.2f\n", budget); //Ciallo～(∠・ω< )⌒☆ (Easter_egg)
        }else{
            printf("Modest Savings      |Grade: F || (T _ T) Budget Crisis| Budget left: %.2f\n", budget); //Ciallo～(∠・ω< )⌒☆ (Easter_egg)
        };
    }else{
        printf("Somthing is wrong with the program!!\n");// for debug use
    }
    
}

void PrintDashBoard(int user_index, int month_index){
    struct MonthlyData *selected_month = &student_list[user_index].month[month_index];
    double warning_line = selected_month->month_income*0.15;
    float percentage;
    ClearScreen();
    printf("Hi, %s : Month : %s \n",student_list[user_index].user_name, selected_month->month_name);
    printf("--------------------------------------------------------------------------------------\n");
    printf("Monthly Income: %lf\n", selected_month->month_income);
    printf("Total Spending: %lf\n", selected_month->total_spending);
    printf("Percentage Spend: %.2f%%\n", (selected_month->total_spending/selected_month->month_income )*100);
    printf("--------------------------------------------------------------------------------------\n");
    printf("Bar Graph\n");
    char *cat_names[] = {"Food", "Transport", "Entertainment", "Study", "Bill&Expenses"}; // The category type
    for (int i = 0; i < 5; i++) {
        // Calculate category percentage of total spending 
        float spending_percentage = (selected_month->total_spending > 0) ? (selected_month->category_totals[i] / selected_month->total_spending) * 100 : 0; //condition ? (value_if_true):(value_if_false)
        printf("%-15s ", cat_names[i]); // print 15 space and the category name 
        DisplayASCIIGraph(spending_percentage); //call function 
    }
    printf("--------------------------------------------------------------------------------------\n");
    CalculateandPrintFinancialStatusandKaomoji(selected_month->total_spending,selected_month->month_income);
    //Ciallo～(∠・ω< )⌒☆ (Easter_egg)
    printf("--------------------------------------------------------------------------------------\n");
    printf("Transaction History\n");
    printf("No.|      Category      |                Description              | Flag|Amount   |\n"); // moveout 
    for (int i = 0; i < selected_month->record_count ;i++){
        struct expensesRecord *record = &selected_month->history[i];
        char noted = (record->item_amount > warning_line)? '!': ' '; 
        //(condition) ? if true : if false
        printf("%03d|%20s|%41s|%5c|%9.2f|\n", i+1, record->category_name, record->expenses_description, noted, record->item_amount);
        
    }

    if (selected_month->record_count == 0){
        printf("No record found in Month %s\n",selected_month->month_name);
    }
    printf("--------------------------------------------------------------------------------------\n");
    printf("Press Any key to Return");
    getch();

}

//Main function
int main (){
    LoadUserData(); //load the data when start the program
    char entry_option[3][30] = {"Login", "Register New User", "Exit"};
    int running = 1;

    while(running){ // check is 1 or not : 0 is false the the program will exit 
        int choice = SelectOption(entry_option, 3);
        if (choice == 0){ // this mean user choose login
            current_active_user = UserLogin();
            if (current_active_user != -1){ // if the login result is -1 mean the login fail, so only when it is not -1 then proceed to the dash board
                int logged_in = 1;
                //ClearInputBuffer();
                while(logged_in){
                    GetMonthlyIncome(current_active_user, student_list[current_active_user].current_month); // call function and pass the variable to it
                    char dash_menu[6][30] = {"Add Record","Dashboard", "Next Month", "History", "Logout"};
                    int dash_choice = SelectOption(dash_menu, 6);
                    if (dash_choice == 0) AddRecord(current_active_user);
                    else if (dash_choice == 1) PrintDashBoard(current_active_user, student_list[current_active_user].current_month);
                    else if (dash_choice == 2) student_list[current_active_user].current_month++;
                    else if (dash_choice == 3) {    
                        char history_menu[12][30];
                        int month_count = student_list[current_active_user].current_month + 1;
                        for(int i=0; i < month_count; i++) strcpy(history_menu[i], student_list[current_active_user].month[i].month_name);
                        int history_choice = SelectOption(history_menu, month_count);
                        PrintDashBoard(current_active_user, history_choice);
                    }
                    else if (dash_choice == 4) logged_in = 0;
                }
            }
         }else if(choice == 1){
            RegisterUser();
        }else if(choice == 2){
            running = 0;
         }
    }
    return 0;
}

//easter egge to pay tribute to fast inverse square root function in the game Quake III Arena (https://en.wikipedia.org/wiki/Fast_inverse_square_root)
// float Q_rsqrt(float number)
// {
//   long i;
//   float x2, y;
//   const float threehalfs = 1.5F;

//   x2 = number * 0.5F;
//   y  = number;
//   i  = * ( long * ) &y;                       // evil floating point bit level hacking
//   i  = 0x5f3759df - ( i >> 1 );               // what the fxxk?
//   y  = * ( float * ) &i;
//   y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//   // y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

//   return y;
// }
