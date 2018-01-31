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
int listingRecords(char);
void generateIndexFile();
int findRecordNumber(char *);
int compareLetter(const void*,const void*);
void deleteAdressByPrimaryKey(int);
int controlDublicateValue(char [],char [],int);
void findAddressRecordByPrimaryKey(int,char [],char []);
void operationMenu(char[],char[],int);
void updateRecordByPrimaryKey();
void controlProgramFlag();
void generateIndexFileFromIndexFile();
void changeFlagValue();
void lastControlFlag();
void finalIndexMaker();
int searchArray(char [],char []);
void updateRamElement(int,char[],char []);
void deleteRamElement(int);
int listForFunction();

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

// findAddressRecordByPrimaryKey get seaching sturuct with the AddressINdex struct value reach indexNum of record file 
void findAddressRecordByPrimaryKey(int ADDRESSMAIN,char name[],char surname[]){
	// declarition of reading file
	FILE* inputFile;
    inputFile = fopen("AddressBook.dat","rb");

    AddressBook bufferRecord;
	
	//  SearchAddress.addressData.index num give record file address which one wantted for finding
	
	fseek(inputFile, ADDRESSMAIN, SEEK_SET);
	fread(&bufferRecord,sizeof(AddressBook),1,inputFile);
	printf("\n\nYour find value is found by primary key value");
	printf("\nname is %s, surname is %s, address is:%s  , Additionnotes : %s \n", bufferRecord.name, bufferRecord.surname, bufferRecord.address,bufferRecord.additionNotes);

  	fclose(inputFile);
}// end of findAddressRecordByPrimaryKey()


// this function inside the opetation menu function run needed method
void operationMenu(char name[],char surname[],int option){

	// searchArray return address of index into realted array value
	int searchAddress = searchArray(name,surname);


	if(searchAddress != 9999){
			
			// according to option this switch statement direct program.
			switch(option){
				
				case 2:
					// change index file flag value 1 - 0
					changeFlagValue();
					//updateRecordByPrimaryKey function get the searching address result then use this value updating index 
					updateRecordByPrimaryKey(searchAddress);
				break;
				
				case 3:
					// change index file flag value 1 - 0
					changeFlagValue();
					//Delete function get result valure for deleting operation
					deleteAdressByPrimaryKey(searchAddress);
				break;
				
				case 4:
					// change index file flag value 1 - 0
					changeFlagValue();
					// find value with primary key value 
					findAddressRecordByPrimaryKey(searchAddress,name,surname);
				break;
				
				case 5:

				break;
			}// end of switch
	
	}	
}// end of operationMenu


// deleteAdressByPrimaryKey function get searching result then according to this attribute deletre address
// every record file objects have removingFlag and that is default assing '*' ,if user delete value it is acctually not remove only change flah '+'
void deleteAdressByPrimaryKey(int SearchAddress){

	// declaraiton of file
	FILE* DeletingFile;
    DeletingFile = fopen("AddressBook.dat","r+b");

    // for the reachinf of record file information program nned to this value
    AddressBook bufferRecord;

	bufferRecord.removingFlag = '+';
	printf("\nDeleting operation complated succesfully !\n");
	
	deleteRamElement(SearchAddress);
	// 
	fseek(DeletingFile, SearchAddress , SEEK_SET);
	fwrite(&bufferRecord, sizeof(AddressBook),1,DeletingFile);	

	fclose(DeletingFile);
}// end of deleteAdressByPrimaryKey



// get the SearchReturnAddress pointer via to this address SearchReturnAddress reach IndexBook sturuct value of indexNum
// index num determine address of record file record space via to indexNum determining address then record file value updating 
void updateRecordByPrimaryKey(int SearchAddress){

	// declarition of reading file
	FILE* updateFile;
    updateFile = fopen("AddressBook.dat","r+b");

    AddressBook bufferRecord;
	
	// declaration of local variable for updating operation
	char name[20];
	char surname[25];
	char address[50];
	char additionNotes[50];

	fseek(updateFile, SearchAddress, SEEK_SET);

	fread(&bufferRecord,sizeof(AddressBook),1,updateFile);
	// print the screen current values
	printf("\nYour record\n__________\nname : %s\nsurname : %s\naddress : %s\nadditionNotes : %s\n",bufferRecord.name,bufferRecord.surname,bufferRecord.address,bufferRecord.additionNotes);

	printf(" \n\t*************  Please Enter value for Updating *************");
	printf(" \n\n! Please don not use any SPACE and TURKISH characters in NAME AND SURNAME INPUTS !");
	printf(" \n! SPACE CHARACTER IS ALLOWED FOR ADDRESS AND NOTES INPUTS  !\n");
	// get new value then assing updating form into them
	printf("Please enter name :");
	scanf("%s", name);
	strcpy(bufferRecord.name,name);

	printf("Please enter surname :");	
	scanf("%s", surname);
	strcpy(bufferRecord.surname,surname);

	updateRamElement(SearchAddress,name,surname);

	printf("Please enter address :");
	int inputCounter1=0;
	while(fgets(address,sizeof(address),stdin) ){

		
		if(inputCounter1 == 1){
			break;
		}
		inputCounter1++;		
	}//end of while
	strcpy(bufferRecord.address,address);	



	printf("Please enter additionNotes :");
	int inputCounter=0;
	while(fgets(additionNotes,sizeof(additionNotes),stdin) ){

		
		if(inputCounter == 0){
			break;
		}
		inputCounter++;		
	}//end of while
	strcpy(bufferRecord.additionNotes,additionNotes);

	printf("\n\nUpdating operation complated succesfully !\n");

	fseek(updateFile, SearchAddress , SEEK_SET);
	fwrite(&bufferRecord, sizeof(AddressBook),1,updateFile);
	fclose(updateFile);
} // end of updateRecordByPrimaryKey


// this function read ındex file find the control flag and then direct which funciton is accured. 
void controlProgramFlag(){

	FILE *indexFileControl = fopen("IndexBook.dat","rb");

	int recordSize = findRecordNumber("AddressBook.dat");

	// program reach the program flag this fseek 
	// program control flag is end of the ındex file   >>>> last byte
	fseek(indexFileControl, -1, SEEK_END);

	fread(&addressContainer.programFlag,sizeof(addressContainer.programFlag),1,indexFileControl);

	printf("%c\n",addressContainer.programFlag);
	
	// if record file is no element beganning of the program index file should create from record file
	if(recordSize == 0){
		printf("\n!!! Program 's index file creating from record file for some unexpected situation OR fisrt time of program NO value in index file !!!!\n");
		generateIndexFile();
	}// end of if
	else{
		
		// according to flag value this switch statement determine index file situation .
		switch(addressContainer.programFlag){

			// 0 means program is finish priveous usage not close normally
			case '0':
			printf("\nProgram 's index file creating from record file for some unexpected situation !\n");
			generateIndexFile();
			break;
			// 1 measn program is finish normally
			case '1':
			printf("\nProgram 's index file creating from index file !");
			generateIndexFileFromIndexFile();
			break;
		}// end of switch
	
	}// end of else

	fclose(indexFileControl);

} // end of controlProgramFlag()


// get the record file read from address information it then generate index file.
void generateIndexFile(){

	// declariton of file pointer
	FILE *record_fp;
	FILE *index_fp;

	FILE *controlFile = fopen("IndexBook.dat","ab");

	AddressBook record;

	int positionOfRecord=0;
	// record_fp for read needed data for creating index file
	record_fp = fopen("AddressBook.dat","rb");
	// index_fp write index file from record file data
	index_fp = fopen("IndexBook.dat","wb");
	
	positionOfRecord = findRecordNumber("AddressBook.dat");

	printf("Byte size of record file : %d\n",positionOfRecord );

	int i = 0;  
	int j = 0;
	// while loop reach all record fiel index
	while( i < (positionOfRecord/146) ) {
		
		int size = sizeof(record);
		// fseek function always go to next value of amount array indexNum 
		fseek(record_fp, (size*i), SEEK_SET);
		
		fread(&record,sizeof(AddressBook),1,record_fp);
		
		if(record.removingFlag == '*'){
			// if the record ids  not removing this part if control this situation and assşng record info into index array 
			strcpy(addressContainer.index1[j].primaryKeyName,record.name) ;
			strcpy(addressContainer.index1[j].primaryKeySurname,record.surname);
			addressContainer.index1[j].indexNum = (146 * j); 
			j++;
			firstItemCheck++;
			indexFileValueNum++;
		}
		i++;
		
	}//end of while loop
	
	//sort the index file record according to alhabetic order
	qsort(addressContainer.index1, (positionOfRecord/146), sizeof(AddressIndex), compareLetter);
	
	if(positionOfRecord == 0){
	fseek(index_fp, 0, SEEK_SET);
	fwrite(&addressContainer,sizeof(AddressIndex),firstItemCheck,index_fp);

	}// end of if
	else{

	fseek(index_fp, 0, SEEK_SET);
	fwrite(&addressContainer,sizeof(AddressIndex),indexFileValueNum,index_fp);
	}// end of else

	// staticlly assinging the programFlag 1 value	
	addressContainer.programFlag = '1';
	// fseek function located program last character
	fseek(controlFile, 0, SEEK_END);
	//fwrite write program flag enof the file
	fwrite(&addressContainer.programFlag,sizeof(addressContainer.programFlag),1,controlFile);

	printf("\t\nIndex file records\n");
	int k;
	
	for (k = 0; k < indexFileValueNum; k++)
	{
		printf("%d -> %s : %s  : %d\n",k,addressContainer.index1[k].primaryKeyName,addressContainer.index1[k].primaryKeySurname,addressContainer.index1[k].indexNum);
	}

	
	fclose(index_fp);
	fclose(controlFile);
	fclose(record_fp);

} // end of generateIndexFile

// after the flag control , this function run if flag value is 1
void generateIndexFileFromIndexFile(){

	// declariton file pointer 
	FILE *indexFileMake = fopen("IndexBook.dat","rb");
	
	FILE *controlFileFromIndexFile = fopen("IndexBook.dat","ab");

	// for the geberaiton of index file adressindex is needed creation of new index file 
	AddressIndex innerIndex;

	int indexNumberOfIndexFile = 0;;

	indexNumberOfIndexFile = (findRecordNumber("IndexBook.dat")/52);
	
	printf("--- %d\n",indexNumberOfIndexFile);


	int i;
	for(i = 0 ;i < indexNumberOfIndexFile ; i++){

		fseek(indexFileMake,sizeof(innerIndex)*i,SEEK_SET);
		// fread from index file forgeetio n new index file
		fread(&innerIndex,sizeof(AddressIndex),1,indexFileMake);
		// if the record ids  not removing this part if control this situation and assşng record info into index array 
		strcpy(addressContainer.index1[i].primaryKeyName,innerIndex.primaryKeyName) ;
		strcpy(addressContainer.index1[i].primaryKeySurname,innerIndex.primaryKeySurname);
		addressContainer.index1[i].indexNum = innerIndex.indexNum; 
		indexFileValueNum++;
	}// end of for 

	//sort the index file record according to alhabetic order
	qsort(addressContainer.index1, indexNumberOfIndexFile, sizeof(AddressIndex), compareLetter);

	FILE *indexFileWrite = fopen("IndexBook.dat","wb");
	fseek(indexFileWrite,0,SEEK_SET);
	fwrite(&addressContainer,sizeof(AddressIndex),indexNumberOfIndexFile,indexFileWrite);

	addressContainer.programFlag = '1';

	fseek(controlFileFromIndexFile, 0, SEEK_END);
	// getiing informaiton write into index fiel acctually
	fwrite(&addressContainer.programFlag,sizeof(addressContainer.programFlag),1,controlFileFromIndexFile);

	fclose(indexFileWrite);
	fclose(indexFileMake);
	fclose(controlFileFromIndexFile);
}// end of generateIndexFileFromIndexFile()

// this function change program's flag value 0 to 1 ıf the program is termimanate formally.
void lastControlFlag(){

	FILE *lastChange = fopen("IndexBook.dat","ab");

	addressContainer.programFlag = '1';

	fseek(lastChange, 0, SEEK_END);

	fwrite(&addressContainer.programFlag,sizeof(addressContainer.programFlag),1,lastChange);

	fclose(lastChange);


} // end of lastControlFlag

// this function change the flag value time to operation inside the function 1 to 0 for situation control.
void changeFlagValue(){

	FILE *changeFlag = fopen("IndexBook.dat","ab");

	addressContainer.programFlag = '0';

	fseek(changeFlag, 0, SEEK_END);

	fwrite(&addressContainer.programFlag,sizeof(addressContainer.programFlag),1,changeFlag);

	fclose(changeFlag);
}// end of changeFlagValue()


// this funtion get the RAM value of index records according to these array value write indexfile end of the file
void finalIndexMaker(){

	FILE *finalIndex = fopen("IndexBook.dat","wb");

	// finally user want to exit press exit option this function runs and write all index array into index file
	fseek(finalIndex, 0, SEEK_SET);
	fwrite(&addressContainer.index1,sizeof(AddressIndex),indexFileValueNum,finalIndex);

	fclose(finalIndex);
} // end of finalINdexMakaer


// this funtion search RAM index value matches or not with user input
int searchArray(char prName[],char prSurname[]){

int controlTemp = 0; 


int i;
for(i = 0; i < indexFileValueNum ; i++){

	// compare all RAM index value with user input
	if(strcmp(addressContainer.index1[i].primaryKeyName,prName) == 0 && strcmp(addressContainer.index1[i].primaryKeySurname,prSurname) == 0)
	{	controlTemp = 1;
		return addressContainer.index1[i].indexNum;
	}// end of if
		
}	// end of for

// is statement control the control temp value for matcing result
if(controlTemp == 0){
	printf("\n !! Your Key inputs do not match any index rexord !!\n");
	return 9999;
}// end of if
else if(controlTemp == 1){
	printf("\n !! Seaching result is success your key is %s %s  \n",prName,prSurname );
}// end od else if


}// end of searchArray


// this function update index1 struct array value according to updating operation
void updateRamElement(int addresOfUpdate,char name[],char surname[]){

	int i ;
	for (i = 0; i < indexFileValueNum; i++)
	{	
		// compare search index address value with index value into ram 
		if(addresOfUpdate == addressContainer.index1[i].indexNum){

			strcpy(addressContainer.index1[i].primaryKeyName,name);
			strcpy(addressContainer.index1[i].primaryKeySurname,surname);
		}// end of if

	}// end of for .

}// end od uopdateRamElement

// this function delete index1 struct array value according to deleting operation
void deleteRamElement(int addressOfDeleting){

	char temp[] ="*";
	
	int i;
	for (i = 0; i < indexFileValueNum; i++)
	{
		// compare search index address value with index value into ram 
		if(addressOfDeleting == addressContainer.index1[i].indexNum){	
			// assing the same value for each values accepts removing.
			strcpy(addressContainer.index1[i].primaryKeyName,temp);
			strcpy(addressContainer.index1[i].primaryKeySurname,temp);
			// for the deletion operation this function assing special number for indexNum
			addressContainer.index1[i].indexNum = 7777; 
		}// end of if

	}// end of for 

	

}// end of deleteRamElement() 


// findrecordbyid abd update function require the listing variable before the run this function list related element according to one character.
int listForFunction(){

	int controlTemp;
	// get the onecharacter from user for comaparing 
	printf("\nPlease enter first character for Listing match records : ");
	char listingCharacter2;
	scanf("\n%c",&listingCharacter2);
	controlTemp = listingRecords(listingCharacter2);
	printf("\n\n");

	return controlTemp;
}// end of listForFunction
