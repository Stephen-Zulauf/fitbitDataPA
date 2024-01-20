#include "Utils.h"

//void clearBuffer(char* buffer, int size) {
//	int i;
//
//	for (i = 0; i < size; i++) {
//		buffer[i] = '\0';
//	}
//}



CleanedFileToken cleanCsv(char* inputFile) {

	CleanedFileToken token;

	//assign cleaned file path
	strcpy(token.outputFile, CLEANFILE);

	FILE* inFile = fopen(inputFile, "r");
	FILE* outFile = fopen(CLEANFILE, "w");

	if (inFile != NULL && outFile != NULL) {
		printf("created %s\n", CLEANFILE);
		printf("opened %s\n", inputFile);

		char buffer[200] = "\0";
		char subBuffer[100] = "\0";
		char lastTime[20] = "\0";

		/*read first two lines and enter data into cleaned struct*/

		//get target ID
		fgets(buffer, 150, inFile);
		char* start = buffer;

		start = strchr(buffer, ',') + 1;
		strtok(start, ",");
		strcpy(token.target, start);
		
		//get field order enums
		fgets(buffer, 150, inFile);
		
		int i = 0;
		start = buffer;
		strtok(start, ",");
		while (start != NULL) {
			//printf("%s\n", start);
			token.fieldOrder[i] = getFieldFromString(start);
			i++;
			start = strtok(NULL, ",");
		}

		/*begin copy*/

		//get each line into buffer
		while (fgets(buffer, 150, inFile) != NULL) {

			start = buffer;

			//check for missing feilds and replace with #
			while (*start != '\0') {
				if (*start == ',' && *(start + 1) == ',') {
					strcpy(subBuffer, start + 1);
					*(start + 1) = '#';
					*(start + 2) = ',';
					start += 3;
					strcpy(start, subBuffer);

				}else if (*start == ',' && *(start + 1) == '\n') {
					strcpy(subBuffer, start + 1);
					*(start + 1) = '#';
					start += 2;
					strcpy(start, subBuffer);

				}
				else {
					start += 1;
				}
			}
			
			//reset start of buffer and toke it
			start = buffer;
			strtok(buffer, ",");

			//check if target field is correct.
			if (strcmp(start, token.target) == 0) {

				//check time field for dupe
				start = strtok(NULL, ",");

				if (strcmp(start, lastTime) != 0) {
					strcpy(lastTime, start);

					//write target
					fputs(token.target, outFile);
					fputs(",", outFile);

					while (start != NULL) {

						//copy field into subBuffer
						strcpy(subBuffer, start);

						//check if missing field write -1 to field)
						if (*subBuffer == '#') {
							fputs("-1", outFile);
							fputs(",", outFile);
							start = strtok(NULL, ",");
						}
						else {
							//eliminate new lines
							char* newLine = strchr(subBuffer, '\n');
							if (newLine != NULL) {
								*newLine = '\0';
							}

							//write field to cleaned line
							fputs(subBuffer, outFile);
							fputs(",", outFile);
							start = strtok(NULL, ",");
						}

					}
					fputs("\n", outFile);

				}

			}
			
		}

		fclose(inFile);
		fclose(outFile);
		
	}
	else {
		printf("ERROR CleanCSV- couldnt open either input or output file\n");
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

FitbitData* ingestData(CleanedFileToken token, FitbitData* dataStorage) {

	char buffer[200] = "\0";
	int i = 0;
	char* temp;

	FILE* inFile = fopen(token.outputFile, "r");

	if (inFile != NULL) {
		while (fgets(buffer, 150, inFile) != NULL) {
			char* start = buffer;

			//check if reading null line before EOF
			if (start != NULL) {
				strtok(buffer, ",");

				strcpy(dataStorage[i].patient, start);
				start = strtok(NULL, ",");

				strcpy(dataStorage[i].minute, start);
				start = strtok(NULL, ",");

				dataStorage[i].calories = strtod(start, &temp);
				start = strtok(NULL, ",");

				dataStorage[i].distance = strtod(start, &temp);
				start = strtok(NULL, ",");

				dataStorage[i].floors = atoi(start);
				start = strtok(NULL, ",");

				dataStorage[i].heartRate = atoi(start);
				start = strtok(NULL, ",");

				dataStorage[i].steps = atoi(start);
				start = strtok(NULL, ",");

				dataStorage[i].sleepLevel = atoi(start);

				i++;
			}
		}
		fclose(inFile);
		printf("Ingested lines: %d\n", i);
	}
	else {
		printf("ERROR Ingest: could not open cleaned csv file\n");
	}

	

	return dataStorage;
}