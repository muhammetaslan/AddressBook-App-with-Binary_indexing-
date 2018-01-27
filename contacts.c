// ******************************** muhammet aslan  *********************************
// declaraiion of  needed libraies
#include <stdio.h>  
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#define RECORD_COUNT 40

//AddressBook  struct deternine for record file keeping values fixed lenght
struct _AddressBook {
	char name[20];
	char surname[25];
	char address[50];
	char additionNotes[50];
	// removing flag determine for every single option flag assing default '+' if remove this flag will be '*' 	
	char removingFlag;
};

// AddressIndex struct include two value primary key of index file (name+surname) of record file and address of records
struct _AddressIndex
{
	char primaryKeyName[20];
	char primaryKeySurname[25];
	int indexNum;
};


typedef struct _AddressBook AddressBook;
typedef struct _AddressIndex AddressIndex;

// this structure using in binary search process
typedef struct _SearchReturnAddress
{
	AddressIndex addressData;
	int indexSearching;
} SearchReturnAddress;

typedef struct _AddressIndexContainer
{
	// Array of index file for using running time operation in the program
	AddressIndex index1[RECORD_COUNT];
	char programFlag;
} AddressIndexContainer;	

AddressIndexContainer addressContainer;

// adding function use this value for fist enterence allowed
int firstItemCheck = 1;
int indexFileValueNum = 0;

// declaration of program prototypes
void showMenu();


// +++++++++++++++++++++++++ main part of program. +++++++++++++++++++
int main(int argc,char *argv[]){
 	
 	// this function control the flag of program according to * or +
	controlProgramFlag();

	// show menu display program functino and according to this user input direct program.
	showMenu();
	
	// if the program can reach thişs function flag value change normally type.
	lastControlFlag();	
	
	return 0;

}// end of main


// showMenu funtion display program user interface then get action id then send to id into mainFuntion method
void showMenu(){

	// programcounter value keep how many times start program
	int programCounter = 0;
	// processCounter variable keep chosing function for each times of starting new option 
	int processCounter = 0;

	// demostrate program menu for each looping until user enter 6 for quit program 
	while(processCounter != 6){
	
		// This menu only for displaying beginning of the program.		
		if(programCounter == 0){
			printf("\n*******************--------^^^^^^^--------************************\n");
			printf("************||||>  Welcome Address Book System  <||||*************\n");
			printf("************_________________________________________************* \n");
		}// end of inner if
		changeFlagValue();	
		printf("\t\t(1) Add New Person Address Book \n");
		printf("\t\t(2) Update Address Book Record By ID \n");
		printf("\t\t(3) Delete Address Book Record by ID \n");
		printf("\t\t(4) Find Address Book Record by ID \n");
		printf("\t\t(5) List Address Book Records \n");
		printf("\t\t-------------------------------------\n");
		printf("\t\t(6) Quit The Address Book System \n");
		printf("\t\tPlease Select one... \n\n\t\t\t\t");
		// get option from user
		scanf("%d",&processCounter);
			
		// get the action with id then execute wantted function
		mainFunction(processCounter);
		
		programCounter++;
	}//end of while loop

}// end of the showMenu


