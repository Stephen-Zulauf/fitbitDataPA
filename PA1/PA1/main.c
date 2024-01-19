#include "Utils.h"
#include "tasks.h"

int main() {


	/*tests*/
	int i;

	char input[] = "FitbitData.csv";

	CleanedFileToken token = cleanCsv(input);

	printf("target: %s\n", token.target);
	printf("output file: %s\n", token.outputFile);

	printf("Field order: ");
	for (i = 0; i < 8; i++) {
		printf("%d,", token.fieldOrder[i]);
	}
	printf("\n");

	return 0;
}