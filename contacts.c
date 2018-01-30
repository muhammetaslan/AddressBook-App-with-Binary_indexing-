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
void mainFunction(int);
void addNewRecord();


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

// All operation methods call by this function into the switch-case 
void mainFunction(int actionOption){

	// delete ,update function use this variable in searching
	//this switch statement operate choing funtion
	switch(actionOption){
		
		case 1:
			// this part of switch adding funtion
			printf(" \t##################### Adding New Record #####################\n");
			changeFlagValue();
			addNewRecord();
			break;
		
		case 2:
			// update operation accur there
			printf("\n");
			int checkValue1; 

			checkValue1 = listForFunction();

			if(checkValue1 == 1){

				printf(" \t####################### Update Record ######################\n");
				printf(" \n\tPlease don not use any SPACE and TURKISH characters in inputs\n");
				// get the user nema and surname for primary value
				char UpdName[20];
				char UpdSurname[25];
				printf("Please enter the name and surname that wantted to update\n");

				printf("Name : ");
				scanf("%s", UpdName);
				
				printf("Surname : ");
				scanf("%s", UpdSurname);
				//operation menu get key valu and user option
				operationMenu(UpdName,UpdSurname,actionOption);
			}//end of if	
			break;
		case 3:
				// in case 3 user enter primary key value binary search alhorithm search user input in index file 
				printf(" \t##################### Deleting Record ######################\n");
				printf(" \n\tPlease don not use any SPACE and TURKISH characters in inputs\n");
				
				char DelName[20];
				char DelSurname[25];
			
				printf("Please enter the name and surname that wantted to delete\n");
				// get the user nema and surname for primary value
				printf("Name : ");
				scanf("%s", DelName);
				
				printf("Surname : ");
				scanf("%s", DelSurname);
				// call this function inside the opetation menu function run needed method

				operationMenu(DelName,DelSurname,actionOption);

			break;
		case 4:
			printf("\n");
			int checkValue; 

			checkValue = listForFunction();

			if(checkValue == 1){
				
				printf(" \t#################### Find Record By Key ####################\n");
				printf(" \n\tPlease don not use any SPACE and TURKISH characters in inputs\n");
				printf("Please enter the name and surname for finding wantted record\n");
				
				char FindName[20];
				char FindSurname[25];

				printf("Name : ");
				scanf("%s", FindName);
				
				printf("Surname : ");
				scanf("%s", FindSurname);
				// call this function inside the opetation menu function run needed method
				operationMenu(FindName,FindSurname,actionOption);
			}// end of if
			break;
		case 5:
				printf(" \t#################### List Address Records ####################\n");
				char listingCharacter;

				printf("\nPlease enter first character for Listing match records : ");
				scanf("\n%c",&listingCharacter);
				// listingrecord function get the one character from user and then list matched value	
				listingRecords(listingCharacter);
			break;
		case 6:
				printf("Finishhh\n");	
				// at the end of the program these two funtion write index array into index file
				finalIndexMaker();
				lastControlFlag();
				printf("--->>>>>>>>>>>>>>>>>>> Closing The Address Book System <<<<<<<<<<<<<<<<<---\n");
				exit(1);
			break;
		default:
				// if the user enter invalid option program otamatically terminate there
				printf("<!!!!!!!!!!!!!!!!!!!!!!> Please Choice Valid Option 1-6 <!!!!!!!!!!!!!!!!!!!!>\n");
				exit(1);
			break;			
	}// end of switch

}// end of mainFuntion method



// this function add new item the data file binary type
void addNewRecord(){

	FILE* fp;
	fp = fopen("AddressBook.dat", "ab");

	int positionOfRecord=0;
	
	// controş the file exist or not giving directories.
	if(!fp){
		printf("!!!!! File not exists !!!!!\n");
		return;
	}//end of else	

	AddressBook record;
	int recordSize= 0;
	int controlDublicate=0;

	recordSize = findRecordNumber("AddressBook.dat");
	// controş the file exist or not giving directories.
	if(recordSize > 0){

		firstItemCheck = 0;
	
	}else if(firstItemCheck == 0){

		firstItemCheck = 1;
	}// end of else

	// get the address book informatiobn from user 
	printf(" \n\n! Please don not use any SPACE and TURKISH characters in NAME AND SURNAME INPUTS !");
	printf(" \n! SPACE CHARACTER IS ALLOWED FOR ADDRESS AND NOTES INPUTS  !\n");
	positionOfRecord = ftell(fp);
	printf("\nPosition of record in record file : %d\n\n",positionOfRecord);

	printf("Please enter name :");
	scanf("%s", record.name);
	// user enter name value and at the same time this value assing into index array 
	strcpy(addressContainer.index1[indexFileValueNum].primaryKeyName,record.name) ;
			

	printf("Please enter surname :");	
	scanf("%s", record.surname);
	// user enter surname value and at the same time this value assing into index array 
	strcpy(addressContainer.index1[indexFileValueNum].primaryKeySurname,record.surname) ;
	
	addressContainer.index1[indexFileValueNum].indexNum = indexFileValueNum * 146;


	qsort(addressContainer.index1, indexFileValueNum, sizeof(AddressIndex), compareLetter);

	indexFileValueNum++;
	// controlDublicateValue return 0 or 1 according to dublicate values enterence
	controlDublicate = controlDublicateValue(record.name,record.surname,recordSize);

	// thsi if statement control the input values of name and surname is exist or not in the index file 
	// prevent dublicate enterence	
	if(controlDublicate || firstItemCheck ){
	
		printf("Please enter address :");
		// scanf function do nat aloe spacae character so program use fgets functoin there 
		int inputCounter1=0;
		while(fgets(record.address,sizeof(record.address),stdin) ){

			if(inputCounter1 == 1){
				break;
			}// end of if
			inputCounter1++;
			
		}//end of while
		

		printf("Please enter additionNotes :");
		// scanf function do nat aloe spacae character so program use fgets functoin there 
		int inputCounter=0;
		while(fgets(record.additionNotes,sizeof(record.additionNotes),stdin) ){

			if(inputCounter == 0){
				break;
			}
			inputCounter++;
					
		}//end of while
		

		record.removingFlag = '*';
		
		fseek(fp, 0, SEEK_SET);
	

		firstItemCheck = 0;
		// write the data into record file.
		fwrite(&record, sizeof(AddressBook),1,fp);
	
	}// end of else*/
	
	fclose(fp);

} // end of addNewRecord

// this function get fist character of primarykey value then seach in the index Array into RAM 
//if find the matches values send to address of record file read by this address finally print record on the screen 
int listingRecords(char fistCharacter)
{
	
	FILE* recordFile;
    // opn the AddressBook.dat file for reading records
    recordFile = fopen("AddressBook.dat","rb");
	
	int controlListing = 0 ; 
	int positionOfRecord = 0 ; 
	char tempString[20];

	AddressBook bufferRecord;
	// change the program flag value
	changeFlagValue();	
	positionOfRecord = findRecordNumber("AddressBook.dat");
	printf("%d\n",positionOfRecord );
	
	// this for loop list the matched elements
	int i;
	for(i = 0 ; i < (positionOfRecord/146) ; i++){

		strcpy(tempString,addressContainer.index1[i].primaryKeyName);	
		
		if(  tempString[0] == fistCharacter ){
			// fseek function always go to next value of amount array indexNum 
			fseek(recordFile,addressContainer.index1[i].indexNum , SEEK_SET);	
					
			fread(&bufferRecord,sizeof(AddressBook),1,recordFile);
			// this printf print the screen record value
			printf("\n%s %s, address is:%s  , Addition Notes : %s\n", bufferRecord.name, bufferRecord.surname, bufferRecord.address,bufferRecord.additionNotes);
			controlListing = 1;
		}// end of if

	}// end of for loop
	
	// if any values do not match input character retrun error message 
	if(controlListing == 0){
		printf("\n!!! Your input character does not match any primary Key value firts character !!\n");
		return 0;
	}//end of if

	return 1;
	fclose(recordFile);
}// end of listingRecords


// findRecordNumber function find number of record using with ftell() ; 
int findRecordNumber(char *AddressBk){

	FILE *record_fp1;

	int positionOfRecord=0;

	// this statement return value of record address 
	record_fp1 = fopen(AddressBk,"ab");
	positionOfRecord = ftell(record_fp1);

	return positionOfRecord;
}// end of findRecordNumber 


// this funtion compare to first character of string in the qsort();
int compareLetter(const void* a, const void* b){
	return (strcmp(((AddressIndex*)a)->primaryKeyName, ((AddressIndex*)b)->primaryKeyName));
}//end of compareLetter



// this function control the in enternece in data is dublicate or not 
int controlDublicateValue(char name[],char surname[],int size){

	int i;
	for(i = 0 ; i < (size/146) ; i++){
		
		if(strcmp(addressContainer.index1[i].primaryKeyName,name) == 0 && strcmp(addressContainer.index1[i].primaryKeySurname,surname) == 0 ){

			printf("Your input %s %s is using others users Please enter diffrent key value\n",name,surname);
			return 0;
			break;
		}//end of if
	}// end of for
	
	return 1;
}// end of controlDublicate


