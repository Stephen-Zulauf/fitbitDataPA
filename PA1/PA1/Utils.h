#ifndef UTILS_H
#define UTILS_H

#define _CRT_SECURE_NO_WARNINGS

#define INPUTFILE "FitbitData.csv"
#define CLEANFILE "cleaned.csv"
#define OUTFILE "Results.csv"

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef enum sleep
{
	NONE = 0, ASLEEP = 1, AWAKE = 2, REALLYAWAKE = 3
} Sleep;

typedef struct fitbit
{
	char patient[10];
	char minute[9];
	double calories;
	double distance;
	unsigned int floors;
	unsigned int heartRate;
	unsigned int steps;
	Sleep sleepLevel;
} FitbitData;

typedef enum fields
{
	Patient = 0, 
	minute = 1, 
	calories = 2, 
	distance = 3,
	floors = 4,
	heartRate = 5,
	steps = 6,
	sleepLevel = 7

} Fields;

typedef struct cleanedFileToken {
	char target[6];
	Fields fieldOrder[8];
	char outputFile[20];
	int numLines;

}CleanedFileToken;

typedef struct sleepRange {
	char begin[9];
	char end[9];
	int level;
}SleepRange;

Fields getFieldFromString(char* str);

CleanedFileToken cleanCsv(char* inputFile);

CleanedFileToken ingestData(CleanedFileToken token, FitbitData* dataStorage);

#endif // !UTILS_H

