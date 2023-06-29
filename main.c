/* This program provides a menu of options to the user for adding, listing, searching, editing, and deleting records of taxpayers. 
The records are stored in an array of structures, and the tax to be paid is calculated based on the income of the taxpayer using the tax brackets. 
The user can add a new record by providing the name and income of the taxpayer, which is then added to the array along
Limited to store 100 Entries of Customer */


#include<stdio.h>
#include<string.h>
#include "color.h"

typedef struct income_tax_calculator{
    char first_name[50];
    char last_name[50];
    char mobile_num[10];
    float income;
    float tax;
}income;

void login(int *Verify);
void add(income *TaxPayer, int *numPayerS);
void list(income *TaxPayer, int numPayerS);
void search(income *TaxPayer, int numPayerS);
void edit(income *TaxPayer, int numPayerS);
void delete(income *TaxPayer, int *numPayerS);
void caltax(float income,float *tax);
void main(){
    int numPayerS=0; //Variable to count the entries of the TaxPayer in the database
    int choice; //To perform the operation
    income TaxPayer[100]; //Limited for 100 entries only
    int Verify=0; // variable to check if the password entered is correct or not
    login(&Verify); // Login/Authentication
    if(Verify==1){
    do { 
    	cyan();
        printf("\n\n");
        printf("------------------------------------\n");
        printf("\tIncome Tax Calculator\n");
        printf("------------------------------------\n");
        printf("\n1. Add New Record\n");
        printf("2. List All Records\n");
        printf("3. Search Record\n");
        printf("4. Edit Record\n");
        printf("5. Delete Record\n");
        printf("6. Exit\n");
        purple();
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        system("cls");
        switch(choice) {
            case 1:
                add(TaxPayer, &numPayerS);
                break;
            case 2:
                list(TaxPayer, numPayerS);
                break;
            case 3:
                search(TaxPayer, numPayerS);
                break;
            case 4:
                edit(TaxPayer, numPayerS);
                break;
            case 5:
                delete(TaxPayer, &numPayerS);
                break;
            case 6:
                system("cls");
	        	green();
	            printf("Exiting Program. Thank You!\n");
	            reset();
	            break;
            default:
            	system("cls");
	        	red();
                printf("Invalid choice.\n");
                reset();
            	break;
          }
    }while(choice!=6);
}
    red();
    printf("You have successfully exited the program...\n\n");
    reset();
}

void login(int *Verify) {
    char password[15];
    blue();
    printf("\nEnter Password: ");
    scanf("%s",&password);
    system("cls");
    FILE *pass;
    pass=fopen("Password.txt","r");
    char myString[15];
    fgets(myString,15,pass); 
    fclose(pass);
    if (strcmp(password, myString) == 0) {
    	green();
        printf("Login Successful!\n\n");
        *Verify=1; //Value changed as pass is true
        reset();
    } 
	else {
		red();
        printf("Wrong Password, Login Failed. Try Again!.\n");
		reset(); //else program is closed
    }
}
void add(income *TaxPayer, int *numPayerS) {
	yellow();
    income newTaxpayer; // We are creating a new Struct to take all the details and will store the details at the end in the araay created
    printf("Enter First name of Tax Payer: ");
    scanf("%s",newTaxpayer.first_name);
    printf("Enter Last name of Tax Payer: ");
    scanf("%s",newTaxpayer.last_name);
    printf("Enter Mobile Number of Tax Payer: ");
    scanf("%s",newTaxpayer.mobile_num);
    reset();
    if(strlen(newTaxpayer.mobile_num)!=10){ // Checking enter mobile no. is of 10 digits or not
    	system("cls");
    	red();
    	printf("Sorry, Mobile Number must be of 10 Digits!\nPlease Try Again.\n\n");
    	reset();
    	return;
	}
    int z;
    for(z=0;z<*numPayerS;z++){ //Loop to verify if entered mobile_number is not duplicate
    	if(strcmp(TaxPayer[z].mobile_num,newTaxpayer.mobile_num)==0){
    		system("cls");
    		red();
    		printf("Sorry, Entered Mobile No. is already Owned by other Tax Payer!\nPlease Try Again.\n\n");
    		reset();
    		return;
		}
	}
	yellow();
    printf("Enter income of taxpayer for the year: ");
    scanf("%f", &newTaxpayer.income);
    reset();
    if(newTaxpayer.income<0){  // Income must be +ve
    	system("cls");
    	red();
    	printf("Sorry, Income can't be negative!\nPlease Try Again.\n\n");
    	reset();
    	return;
	}
    caltax(newTaxpayer.income,&newTaxpayer.tax);
    TaxPayer[*numPayerS] = newTaxpayer;
    *numPayerS=*numPayerS+1;
    system("cls");
    green();
    printf("\nRecord added successfully!\n");
	reset();
}

void list(income *TaxPayer, int  numPayerS) {
    if (numPayerS==0){ //Checking if there is a value or not
    	red();
        printf("Record List is Empty!\n");
        reset();
    }
    else{
    green();
    printf("\nTaxpayer\t\tMobile Number\t\tIncome\t\t Tax to be Paid\n");
    reset();
    // Loop for printing all the details of the TaxPayers
    int i;
    for(i=0; i<numPayerS; i++) {
    	white();
        printf("%s %s\t\t%s\t\t%.2f\t\t%.2f\n", TaxPayer[i].first_name,TaxPayer[i].last_name,TaxPayer[i].mobile_num, TaxPayer[i].income, TaxPayer[i].tax);
        reset();
    }
    }
}

void search(income *TaxPayer, int numPayerS) {
	if(numPayerS==0) {
		system("cls");
		red();
		printf("Record List is empty!\n");
		reset();
		return;
	}
    char num[10];
    int found = 0; // Variable to check if the name exists or not
    purple();
    printf("\nPlease Enter the Mobile Number of the Taxpayer to search: ");
    scanf("%s", num);
    reset();
    if(strlen(num)!=10){
    	system("cls");
    	red();
    	printf("Sorry, Mobile Number must be of 10 Digits!\nPlease Try Again.\n\n");
    	reset();
    	return;
	}
    int i;
    system("cls");
    for(i=0; i<numPayerS; i++) { 
    if(strcmp(TaxPayer[i].mobile_num,num)==0) { //Prinitng details of the record found
    	green();
    	printf("\nRecord Found!");
    	reset();
    	white();
        printf("\nTaxpayer: %s %s\nMobile Number: %s\nIncome: %.2f\nTax to be Paid: %.2f\n", TaxPayer[i].first_name,TaxPayer[i].last_name,TaxPayer[i].mobile_num, TaxPayer[i].income, TaxPayer[i].tax);
        reset();
		found = 1;
        break;
    }
}
if(found==0) {
	system("cls");
	red();
    printf("\nRecord not found!\n");
    reset();
}
}

void edit(income *TaxPayer, int numPayerS) {
	char num[10];
	int found=0;
	if(numPayerS==0) {
		system("cls");
		red();
		printf("Record List is empty!\n");
		reset();
		return;
	}
	purple();
	printf("\nPlease Enter the Mobile Number of the Taxpayer to edit: ");
    scanf("%s", num);
    reset();
    if(strlen(num)!=10){
    	system("cls");
    	red();
    	printf("Sorry, Mobile Number must be of 10 Digits!\nPlease Try Again.\n\n");
    	reset();
    	return;
	}
    int i;
    float new_income;
    system("cls");
    for(i=0; i<numPayerS; i++) {
    if(strcmp(TaxPayer[i].mobile_num,num)==0)  {
    	green();
    	printf("\nRecord Found!");
    	reset();
    	white();
        printf("\nTaxpayer: %s %s\nMobile Number: %s\nIncome: %.2f\nTax to be Paid: %.2f\n", TaxPayer[i].first_name,TaxPayer[i].last_name,TaxPayer[i].mobile_num, TaxPayer[i].income, TaxPayer[i].tax);
		reset();
		yellow();
		printf("\nEnter new income for the taxpayer: ");
        scanf("%f", &new_income);
        reset();
        if(new_income<0){ // Income must be +ve
    	system("cls");
    	red();
    	printf("Sorry, Income can't be negative!\nPlease Try Again.\n\n");
    	reset();
    	return;
	}
		TaxPayer[i].income=new_income; //Assigning value to the indice of income
        caltax(TaxPayer[i].income,&TaxPayer[i].tax);
        system("cls");
        green();
        printf("\nRecord updated successfully!\n");
        reset();
        found = 1;
        break;
    }
}
if(found==0) {
	system("cls");
	red();
    printf("\nRecord not found!\n");
    reset();
}
}

void delete(income *TaxPayer, int *numPayerS) {
	char num[10];
	int found=0;
	if(*numPayerS==0) {
		system("cls");
		red();
		printf("Record List is empty!\n");
		reset();
		return;
	}
	purple();
	printf("\nPlease Enter the Mobile Number of the Taxpayer to delete: ");
    scanf("%s", num);
    reset();
    if(strlen(num)!=10){
    	system("cls");
    	red();
    	printf("Sorry, Mobile Number must be of 10 Digits!\nPlease Try Again.\n\n");
    	reset();
    	return;
	}
    int i;
    system("cls");
    for(i=0; i<*numPayerS; i++) {
    if(strcmp(TaxPayer[i].mobile_num,num)==0)  {
    	green();
    	printf("\nRecord Found!");
    	reset();
    	white();
        printf("\nTaxpayer: %s %s\nMobile Number: %s\nIncome: %.2f\nTax to be Paid: %.2f\n", TaxPayer[i].first_name,TaxPayer[i].last_name,TaxPayer[i].mobile_num, TaxPayer[i].income, TaxPayer[i].tax);        // Loop to shift the value at the previous indice as the element is Found
        reset();
		int j;
        for(j=i; j<(*numPayerS)-1; j++) { //Removing the indice of the data that need to be deleted
            TaxPayer[j] = TaxPayer[j+1];
        }
        *numPayerS=*numPayerS-1;
        green();
        printf("\nRecord deleted successfully!\n");
        reset();
        found = 1;
        break;
    }
}
if(found==0) {
	system("cls");
	red();
    printf("\nRecord not found!\n");
    reset();
}
}
void caltax(float income,float *tax){
    // We will find the tax of the user using tax brackets
    if (income <= 250000) {
        *tax = 0;
    } else if (income > 250000 && income <= 500000) {
        *tax = (income - 250000) * 0.05;
    } else if (income > 500000 && income <= 1000000) {
        *tax = (income - 500000) * 0.2 + 12500;
    } else {
        *tax = (income - 1000000) * 0.3 + 112500;
    }
}
