#include "Utils.h"
#include "tasks.h"

int main() {

	/*declare main array for structs*/
	FitbitData dataStorage[1480];

	/*clean the original data and write to clean file*/
	CleanedFileToken token = cleanCsv(INPUTFILE);
	printf("output file: %s\n", token.outputFile);
	printf("target: %s\n", token.target);

	/*Ingest data from cleaned file to array and set token*/
	token = ingestData(token, dataStorage);

	/*calculate Totals and write output file*/
	compTotals(token, dataStorage);


	/*tests*/

	//int i;

	//char input[] = INPUTFILE;

	//CleanedFileToken token = cleanCsv(input);
	//printf("output file: %s\n", token.outputFile);
	//printf("target: %s\n", token.target);
	//

	//printf("Field order: ");
	//for (i = 0; i < 8; i++) {
	//	printf("%d,", token.fieldOrder[i]);
	//}
	//printf("\n");

	//FitbitData dataStorage[1480];

	//token = ingestData(token, dataStorage);

	//compTotals(token, dataStorage);

	/*
	char patient[10];
	char minute[9];
	double calories;
	double distance;
	unsigned int floors;
	unsigned int heartRate;
	unsigned int steps;
	Sleep sleepLevel;
	*/
	/*for (i = 638; i < 644; i++) {
		printf("----------\n");
		printf("Patient: %s\n", dataStorage[i].patient);
		printf("minute: %s\n", dataStorage[i].minute);
		printf("calories: %lf\n", dataStorage[i].calories);
		printf("distance: %lf\n", dataStorage[i].distance);
		printf("floors: %d\n", dataStorage[i].floors);
		printf("heartrate: %d\n", dataStorage[i].heartRate);
		printf("steps: %d\n", dataStorage[i].steps);
		printf("sleep level: %d\n", dataStorage[i].sleepLevel);
		printf("----------\n");
	}*/
	



	return 0;
}