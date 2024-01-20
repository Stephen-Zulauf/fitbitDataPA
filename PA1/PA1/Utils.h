#ifndef UTILS_H
#define UTILS_H

#define _CRT_SECURE_NO_WARNINGS

#define INPUTFILE "FitbitData.csv"
#define CLEANFILE "cleaned.csv"
#define OUTFILE "output.txt"

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

}CleanedFileToken;

Fields getFieldFromString(char* str);

//void clearBuffer(char* buffer, int size);

CleanedFileToken cleanCsv(char* inputFile);

FitbitData* ingestData(CleanedFileToken token, FitbitData* dataStorage);

#endif // !UTILS_H

