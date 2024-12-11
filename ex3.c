/******************
Name:
ID:
Assignment: ex3
*******************/

#include <stdio.h>
#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define addOne  1
#define addAll  2
#define stats  3
#define print  4
#define insights  5
#define deltas  6
#define done  7

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};

// Initialize the sales data to -1 using a different approach
void initializeSales(int sales[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
    for (int day = 0; day < DAYS_IN_YEAR; day++) {
        for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
            for (int type = 0; type < NUM_OF_TYPES; type++) {
                *(sales[day][brand] + type) = -1; // Using pointer arithmetic
            }
        }
    }
}

// Get maximum value and index using a different approach
void getMax(int array[], int length, int *maxValue, int *maxIndex) {
    *maxValue = array[0];
    *maxIndex = 0;
    for (int i = 1; i < length; i++) {
        if (array[i] > *maxValue) {
            *maxValue = array[i];
            *maxIndex = i;
        }
    }
}

// Sum all elements in an array using recursion
int sumArray(int array[], int length) {
    int total = 0;
    for (int i = 0; i < length; i++) {
        total += array[i];
    }
    return total;

// Validate all sales are positive with a single loop
int validateSales(int sales[], int length) {
    for (int i = 0; i < length; i++) {
        if (sales[i] < 0) {
            return 0; // Found a negative number
        }
    }
    return 1; // All sales are valid
}

// Get a valid brand index using a loop to filter invalid input
int getValidBrandIndex() {
    int brand;
    while (1) {
        scanf("%d", &brand);
        if (brand >= 0 && brand < NUM_OF_BRANDS) {
            break;
        }
        printf("This brand is not valid\n");
    }
    return brand;
}

// Check if a value exists in an array using a different logic
int hasValue(int array[], int length, int value) {
    int found = 0;
    for (int i = 0; i < length; i++) {
        if (array[i] == value) {
            found = 1;
            break;
        }
    }
    return found;
}

// Update sales data using a different approach
void addSales(int salesData[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int brandDays[NUM_OF_BRANDS], int brandIndex, int sales[]) {
    int currentDay = brandDays[brandIndex];
    for (int i = 0; i < NUM_OF_TYPES; i++) {
        *(salesData[currentDay][brandIndex] + i) = sales[i]; // Using pointer arithmetic
    }
    brandDays[brandIndex]++;
}

// Print sales data in a different format
void displaySales(int salesData[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int brandDays[NUM_OF_BRANDS]) {
    printf("------ Sales Data ------\n");
    for (int b = 0; b < NUM_OF_BRANDS; b++) {
        printf("Brand: %s\n", brands[b]);
        for (int d = 0; d < brandDays[b]; d++) {
            printf("Day %d -> ", d + 1);
            for (int t = 0; t < NUM_OF_TYPES; t++) {
                printf("%s: %d ", types[t], salesData[d][b][t]);
            }
            printf("\n");
        }
        printf("\n");
    }
    printf("------------------------\n");
}

// Provide insights using different logic
void computeInsights(int salesData[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int brandDays[NUM_OF_BRANDS]) {
    int brandTotals[NUM_OF_BRANDS] = {0}, typeTotals[NUM_OF_TYPES] = {0}, dayTotals[DAYS_IN_YEAR] = {0};
    int maxBrand = 0, maxType = 0, maxDay = 0, maxBrandIndex, maxTypeIndex, maxDayIndex;

    for (int d = 0; d < brandDays[0]; d++) {
        for (int b = 0; b < NUM_OF_BRANDS; b++) {
            for (int t = 0; t < NUM_OF_TYPES; t++) {
                brandTotals[b] += salesData[d][b][t];
                typeTotals[t] += salesData[d][b][t];
                dayTotals[d] += salesData[d][b][t];
            }
        }
    }

    getMax(brandTotals, NUM_OF_BRANDS, &maxBrand, &maxBrandIndex);
    getMax(typeTotals, NUM_OF_TYPES, &maxType, &maxTypeIndex);
    getMax(dayTotals, brandDays[0], &maxDay, &maxDayIndex);

    printf("Top Brand: %s with %d\n", brands[maxBrandIndex], maxBrand);
    printf("Top Type: %s with %d\n", types[maxTypeIndex], maxType);
    printf("Top Day: Day %d with %d\n", maxDayIndex + 1, maxDay);
}

// Main program remains the same
int main() {
    int salesData[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    initializeSales(salesData);

    int brandDays[NUM_OF_BRANDS] = {0};
    int userChoice;

    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
    scanf("%d", &userChoice);

    while (userChoice != done) {
        switch (userChoice) {
            case addOne: {
                int brand = getValidBrandIndex();
                int sales[NUM_OF_TYPES];
                do {
                    printf("Enter sales data (SUV Sedan Coupe GT): ");
                    scanf("%d %d %d %d", &sales[0], &sales[1], &sales[2], &sales[3]);
                } while (!validateSales(sales, NUM_OF_TYPES));
                addSales(salesData, brandDays, brand, sales);
                break;
            }
            case print:
                displaySales(salesData, brandDays);
                break;
            case insights:
                computeInsights(salesData, brandDays);
                break;
            default:
                printf("Invalid input\n");
        }
        printf("Enter your choice: ");
        scanf("%d", &userChoice);
    }
    printf("Goodbye!\n");
    return 0;
}
