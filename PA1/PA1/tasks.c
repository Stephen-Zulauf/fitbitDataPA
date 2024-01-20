#include "tasks.h"

void compTotals(CleanedFileToken token, FitbitData* dataStorage) {
	FILE* outFile = fopen(OUTFILE, "w");

	if (outFile != NULL) {

		/*Comp totals*/

		int i;
		double sumCalories = 0;
		double sumDistance = 0;
		int sumFloors = 0;
		int sumSteps = 0;
		double avgHeart = 0;
		int largestSteps = 0;
		int worstSleep = 0;

		for (i = 0; i < token.numLines; i++) {
			if (dataStorage[i].calories >= 0) {
				sumCalories += dataStorage[i].calories;
			}
			if (dataStorage[i].distance >= 0) {
				sumDistance += dataStorage[i].distance;
			}
			if (dataStorage[i].floors >= 0) {
				sumFloors += dataStorage[i].floors;
			}
			if (dataStorage[i].steps >= 0) {
				sumSteps += dataStorage[i].steps;
			}

		}

		/*Average heart rate*/

		for (i = 0; i < token.numLines; i++) {
			unsigned int sumHR = 0;
			unsigned int sumHRsIndex = 0;

			if (dataStorage[i].heartRate >= 0) {
				sumHR += dataStorage[i].heartRate;
				sumHRsIndex += 1;
			}
			avgHeart = (sumHR / sumHRsIndex);
		}

		/*Max Steps*/
		char stepsMinutes[500] = "\0";
		int stepsEntries = 0;
		char* start = stepsMinutes;

		for (i = 0; i < token.numLines; i++) {
			if (dataStorage[i].steps > largestSteps) {
				largestSteps = dataStorage[i].steps;
			}

		}
		for (i = 0; i < token.numLines; i++) {

			if (dataStorage[i].steps == largestSteps) {
				strcpy(start, dataStorage[i].minute);
				while (*start != NULL) {
					start += 1;
				}
				*start = ',';
				start += 1;
				stepsEntries += 1;
			}

		}

		/*longest consecutive range of poor sleep*/
		SleepRange ranges[50];
		int rangesCount = 0;

		for (i = 0; i < 50; i++) {
			ranges[i].level = 0;
		}

		for (i = 0; i < token.numLines; i++) {
			if (dataStorage[i].sleepLevel > 1) {
				strcpy(ranges[rangesCount].begin, dataStorage[i].minute);
				while (dataStorage[i].sleepLevel > 1) {
					ranges[rangesCount].level += dataStorage[i].sleepLevel;
					i++;
				}
				strcpy(ranges[rangesCount].end, dataStorage[i - 1].minute);
				rangesCount += 1;
			}
		}

		for (i = 0; i < rangesCount; i++) {
			if (ranges[i].level > worstSleep) {
				worstSleep = ranges[i].level;
			}

		}

		/*write to output file*/
		fputs("Total Calories,Total Distance,Total Floors,Total Steps, Avg Heartrate, Max Steps(minute(s)), Sleep\n", outFile);
		fprintf(outFile, "%.2f,", sumCalories);
		fprintf(outFile, "%.2f,", sumDistance);
		fprintf(outFile, "%d,", sumFloors);
		fprintf(outFile, "%d,", sumSteps);
		fprintf(outFile, "%.2f,", avgHeart);
		fprintf(outFile, "%d", largestSteps);
		start = stepsMinutes;
		strtok(stepsMinutes, ",");
		for (i = 0; i < stepsEntries; i++) {
			fprintf(outFile, "(");
			fputs(start, outFile);
			fprintf(outFile, ")");
			start = strtok(NULL, ",");
		}
		fprintf(outFile, ",");
		fprintf(outFile, "%d", worstSleep);
		for (i = 0; i < rangesCount; i++) {
			if (ranges[i].level == worstSleep) {
				fprintf(outFile, "(");
				fputs(ranges[i].begin, outFile);
				fprintf(outFile, "-");
				fputs(ranges[i].end, outFile);
				fprintf(outFile, ")");
			}
		}
		fprintf(outFile, "\n");
		
		fclose(outFile);

		/*Print Data to screen*/
		printf("\n");
		printf("|-------------------------------------|\n");
		printf("Total Calories: %.2f\n", sumCalories);
		printf("Total Distance: %.2f\n", sumDistance);
		printf("Total Floors: %d\n", sumFloors);
		printf("Total Steps: %d\n", sumSteps);
		printf("Average Heart Rate: %.2f\n", avgHeart);
		printf("Most steps in 1 minute: %d\n", largestSteps);
		printf("Worst sleep level: %d", worstSleep);
		for (i = 0; i < rangesCount; i++) {
			if (ranges[i].level == worstSleep) {
				printf("(");
				printf("%s",ranges[i].begin);
				printf("-");
				printf("%s", ranges[i].end);
				printf(")");
			}
		}
		printf("\n");
		printf("|-------------------------------------|\n");

	}
	else {
		printf("ERROR compTotals- couldn't open output file");
	}
	
}