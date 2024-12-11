/******************
Name: Gilad Bergfroind
ID: 331749978
Assignment: ex3
*******************/

#include <stdio.h>

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define ADD_ONE  1
#define ADD_ALL  2
#define STATS  3
#define PRINT  4
#define INSIGHTS  5
#define DELTAS  6
#define DONE  7

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};

void displayMenu() {
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1. Enter Daily Data For A Brand\n"
           "2. Populate A Day Of Sales For All Brands\n"
           "3. Provide Daily Stats\n"
           "4. Print All Data\n"
           "5. Provide Overall (simple) Insights\n"
           "6. Provide Average Delta Metrics\n"
           "7. Exit\n");
}

void initializeSalesData(int salesData[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
    for (int i = 0; i < DAYS_IN_YEAR; i++) {
        for (int j = 0; j < NUM_OF_BRANDS; j++) {
            for (int k = 0; k < NUM_OF_TYPES; k++) {
                salesData[i][j][k] = 0;  // Initialize all sales data to 0
            }
        }
    }
}

int isValidSales(int sales[NUM_OF_TYPES]) {
    for (int i = 0; i < NUM_OF_TYPES; i++) {
        if (sales[i] < 0) return 0;
    }
    return 1;
}

int getValidBrand() {
    int brand;
    while (scanf("%d", &brand) && (brand < 0 || brand >= NUM_OF_BRANDS)) {
        printf("This brand is not valid\n");
    }
    return brand;
}

void getSalesForBrand(int sales[NUM_OF_TYPES]) {
    while (scanf("%d %d %d %d", &sales[0], &sales[1], &sales[2], &sales[3]) && !isValidSales(sales)) {
        printf("The sales are not valid\n");
    }
}

void updateSalesData(int salesData[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int dayCount[NUM_OF_BRANDS], int brand, int sales[NUM_OF_TYPES]) {
    for (int i = 0; i < NUM_OF_TYPES; i++) {
        salesData[dayCount[brand]][brand][i] = sales[i];
    }
    dayCount[brand]++;
}

void displayStats(int salesData[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int dayCount[NUM_OF_BRANDS]) {
    printf("What day would you like to analyze?\n");
    int day;
    while (scanf("%d", &day) && (day > dayCount[0] || day < 1)) {
        printf("Please enter a valid day.\nWhat day would you like to analyze?\n");
    }

    int totalSales = 0, brandSales[NUM_OF_BRANDS] = {0}, typeSales[NUM_OF_TYPES] = {0};

    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        for (int j = 0; j < NUM_OF_TYPES; j++) {
            totalSales += salesData[day - 1][i][j];
            brandSales[i] += salesData[day - 1][i][j];
            typeSales[j] += salesData[day - 1][i][j];
        }
    }

    int maxBrandSales = 0, maxBrandIndex = 0, maxTypeSales = 0, maxTypeIndex = 0;

    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        if (brandSales[i] > maxBrandSales) {
            maxBrandSales = brandSales[i];
            maxBrandIndex = i;
        }
    }

    for (int i = 0; i < NUM_OF_TYPES; i++) {
        if (typeSales[i] > maxTypeSales) {
            maxTypeSales = typeSales[i];
            maxTypeIndex = i;
        }
    }

    printf("In day number %d:\n"
           "The sales total was %d\n"
           "The best sold brand with %d sales was %s\n"
           "The best sold type with %d sales was %s\n",
           day, totalSales, maxBrandSales, brands[maxBrandIndex], maxTypeSales, types[maxTypeIndex]);
}

void printAllSales(int salesData[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int dayCount[NUM_OF_BRANDS]) {
    printf("***************\n");
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        printf("Sales for %s:\n", brands[i]);
        for (int j = 0; j < dayCount[0]; j++) {
            printf("Day %d- ", j + 1);
            for (int k = 0; k < NUM_OF_TYPES; k++) {
                printf("%s: %d ", types[k], salesData[j][i][k]);
            }
            printf("\n");
        }
    }
    printf("***************\n");
}

void provideInsights(int salesData[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int dayCount[NUM_OF_BRANDS]) {
    int totalBrandSales[NUM_OF_BRANDS] = {0}, totalTypeSales[NUM_OF_TYPES] = {0}, totalDaySales[DAYS_IN_YEAR] = {0};

    for (int i = 0; i < dayCount[0]; i++) {
        for (int j = 0; j < NUM_OF_BRANDS; j++) {
            for (int k = 0; k < NUM_OF_TYPES; k++) {
                totalBrandSales[j] += salesData[i][j][k];
                totalTypeSales[k] += salesData[i][j][k];
                totalDaySales[i] += salesData[i][j][k];
            }
        }
    }

    int bestBrandSales = 0, bestBrandIndex = 0;
    int bestTypeSales = 0, bestTypeIndex = 0;
    int bestDaySales = 0, bestDayIndex = 0;

    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        if (totalBrandSales[i] > bestBrandSales) {
            bestBrandSales = totalBrandSales[i];
            bestBrandIndex = i;
        }
    }

    for (int i = 0; i < NUM_OF_TYPES; i++) {
        if (totalTypeSales[i] > bestTypeSales) {
            bestTypeSales = totalTypeSales[i];
            bestTypeIndex = i;
        }
    }

    for (int i = 0; i < dayCount[0]; i++) {
        if (totalDaySales[i] > bestDaySales) {
            bestDaySales = totalDaySales[i];
            bestDayIndex = i;
        }
    }

    printf("The best-selling brand overall is %s: %d$\n"
           "The best-selling type of car is %s: %d$\n"
           "The most profitable day was day number %d: %d$\n",
           brands[bestBrandIndex], bestBrandSales, types[bestTypeIndex], bestTypeSales, bestDayIndex + 1, bestDaySales);
}

void calculateDeltas(int salesData[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int dayCount[NUM_OF_BRANDS]) {
    int delta[NUM_OF_BRANDS][DAYS_IN_YEAR] = {0};

    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        for (int j = 0; j < NUM_OF_TYPES; j++) {
            for (int k = 0; k < dayCount[0] - 1; k++) {
                delta[i][k] += salesData[k + 1][i][j] - salesData[k][i][j];
            }
        }
    }

    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        float avgDelta = 0.0;
        for (int j = 0; j < dayCount[0] - 1; j++) {
            avgDelta += delta[i][j];
        }
        avgDelta /= (dayCount[0] - 1);
        printf("Brand: %s, Average Delta: %.6f\n", brands[i], avgDelta);
    }
}

int main() {
    int salesData[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    int dayCount[NUM_OF_BRANDS] = {0};
    int choice;

    initializeSalesData(salesData);

    displayMenu();
    scanf("%d", &choice);

    while (choice != DONE) {
        switch (choice) {
            case ADD_ONE: {
                int brand = getValidBrand();
                int sales[NUM_OF_TYPES];
                printf("Enter sales data for %s:\n", brands[brand]);
                getSalesForBrand(sales);
                updateSalesData(salesData, dayCount, brand, sales);
                break;
            }
            case ADD_ALL: {
                printf("Enter sales data for all brands:\n");
                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    int sales[NUM_OF_TYPES];
                    printf("Enter sales for %s: ", brands[i]);
                    getSalesForBrand(sales);
                    updateSalesData(salesData, dayCount, i, sales);
                }
                break;
            }
            case STATS:
                displayStats(salesData, dayCount);
                break;
            case PRINT:
                printAllSales(salesData, dayCount);
                break;
            case INSIGHTS:
                provideInsights(salesData, dayCount);
                break;
            case DELTAS:
                calculateDeltas(salesData, dayCount);
                break;
            default:
                break;
        }

        displayMenu();
        scanf("%d", &choice);
    }

    printf("Goodbye!\n");
    return 0;
}
