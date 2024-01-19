#include "Utils.h"

CleanedFileToken cleanCsv(char* inputFile) {

	CleanedFileToken token;

	//assign cleaned file path
	char cleanedName[15] = "cleaned.csv";
	strcpy(token.outputFile, cleanedName);

	FILE* inFile = fopen(inputFile, "r");
	FILE* outFile = fopen(cleanedName, "w");

	if (inFile != NULL && outFile != NULL) {
		printf("created %s\n", cleanedName);
		printf("opened %s\n", inputFile);

		char buffer[100];
		
		//read first two lines and enter data into cleaned struct
		//get target ID
		fgets(buffer, 100, inFile);
		char* start = buffer;
		char* end = NULL;

		start = strchr(buffer, ',') + 1;
		strtok(start, ",");
		strcpy(token.target, start);
		
		//get field order enums
		fgets(buffer, 100, inFile);

		int i = 0;
		start = buffer;
		strtok(start, ",");
		while (start != NULL) {
			printf("%s\n", start);
			token.fieldOrder[i] = getFieldFromString(start);
			i++;
			start = strtok(NULL, ",");
		}

	}

	return token;

}
/*possible fields in string form:
Patient,minute,calories,distance,floors,heart,steps,sleep_level
Translations:
Patient = 0, minute = 1,calories = 2,distance = 3,floors = 4,heartRate = 5,steps = 6,sleepLevel = 7
*/
//TODO strip any '\n' before checking input
Fields getFieldFromString(char* str) {

	//copy into buffer to strip any new lines
	char buffer[20] ="\0";
	strcpy(buffer, str);
	char* newLine = strchr(buffer, '\n');
	if (newLine != NULL) {
		*newLine = '\0';
	}

	//compare strings return enum
	if (strcmp(buffer, "Patient") == 0) {
		return 0;
	}
	else if (strcmp(buffer, "minute") == 0) {
		return 1;
	}
	else if (strcmp(buffer, "calories") == 0) {
		return 2;
	}
	else if (strcmp(buffer, "distance") == 0) {
		return 3;
	}
	else if (strcmp(buffer, "floors") == 0) {
		return 4;
	}
	else if (strcmp(buffer, "heart") == 0) {
		return 5;
	}
	else if (strcmp(buffer, "steps") == 0) {
		return 6;
	}
	else if (strcmp(buffer, "sleep_level") == 0) {
		return 7;
	}
	else {
		printf("ERROR getFieldFromString-could not identify enum type\n");
		return 8;
	}
}