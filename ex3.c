/******************
Name: Gilad Bergfroind
ID: 331749978
Assignment: ex3
*******************/

#include <stdio.h>

#define NUM_OF_BRANDS 5
#define NUM_OF_TYPES 4
#define DAYS_IN_YEAR 365

// Global arrays for brands and types
char brands[NUM_OF_BRANDS][15] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][10] = {"SUV", "Sedan", "Coupe", "GT"};

// Function to display brand name given an index
void printBrandName(int index) {
    printf("%s", brands[index]);
}

// Function to display type name given an index
void printTypeName(int index) {
    printf("%s", types[index]);
}

// Function to display menu
void displayMenu() {
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1. Enter Daily Data For A Brand\n"
           "2. Populate A Day Of Sales For All Brands\n"
           "3. Provide Daily Stats\n"
           "4. Print All Data\n"
           "5. Provide Overall (simple) Insights\n"
           "6. Provide Average Delta Metrics\n"
           "7. exit\n");
}

// Function to check if a brand is valid
int isValidBrand(int brand) {
    return brand >= 0 && brand < NUM_OF_BRANDS;
}

// Function to check if sales values are valid (non-negative)
int isValidSales(int sales[NUM_OF_TYPES]) {
    for (int i = 0; i < NUM_OF_TYPES; i++) {
        if (sales[i] < 0) return 0;
    }
    return 1;
}

// Function to handle daily data input for a brand
void enterDailyDataForBrand(int salesData[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int dayCount[NUM_OF_BRANDS], int *currentDay) {
    int brand, sales[NUM_OF_TYPES];
    
    printf("Enter brand index and sales data (brand SUV Sedan Coupe GT): ");
    scanf("%d", &brand);
    
    if (!isValidBrand(brand)) {
        printf("This brand is not valid\n");
        return;
    }
    
    // Read sales data
    scanf("%d %d %d %d", &sales[0], &sales[1], &sales[2], &sales[3]);
    
    if (!isValidSales(sales)) {
        printf("Invalid sales data\n");
        return;
    }
    
    // Insert data into the sales array
    for (int i = 0; i < NUM_OF_TYPES; i++) {
        salesData[*currentDay][brand][i] = sales[i];
    }
    
    dayCount[brand]++;
}

// Function to populate a day of sales for all brands
void populateDayOfSales(int salesData[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int dayCount[NUM_OF_BRANDS], int *currentDay) {
    int completedBrands[NUM_OF_BRANDS] = {0};
    int allBrandsCompleted = 0;
    
    // Print brands that need data
    printf("No data for brands ");
    int first = 1;
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        if (dayCount[i] == 0) {
            if (!first) printf(", ");
            printf("%s", brands[i]);
            first = 0;
        }
    }
    printf("\nPlease complete the data\n");
    
    while (!allBrandsCompleted) {
        int brand, sales[NUM_OF_TYPES];
        
        printf("Enter brand index and sales data (brand SUV Sedan Coupe GT): ");
        scanf("%d", &brand);
        
        if (!isValidBrand(brand)) {
            printf("This brand is not valid\n");
            
            // Reprint brands that still need data
            printf("No data for brands ");
            first = 1;
            for (int i = 0; i < NUM_OF_BRANDS; i++) {
                if (dayCount[i] == 0) {
                    if (!first) printf(", ");
                    printf("%s", brands[i]);
                    first = 0;
                }
            }
            printf("\nPlease complete the data\n");
            continue;
        }
        
        // Check if brand already has data for this day
        if (completedBrands[brand]) {
            printf("This brand is already completed\n");
            continue;
        }
        
        // Read sales data
        scanf("%d %d %d %d", &sales[0], &sales[1], &sales[2], &sales[3]);
        
        if (!isValidSales(sales)) {
            printf("Invalid sales data\n");
            continue;
        }
        
        // Insert data into the sales array
        for (int i = 0; i < NUM_OF_TYPES; i++) {
            salesData[*currentDay][brand][i] = sales[i];
        }
        
        completedBrands[brand] = 1;
        dayCount[brand]++;
        
        // Check if all brands are completed
        allBrandsCompleted = 1;
        for (int i = 0; i < NUM_OF_BRANDS; i++) {
            if (dayCount[i] == 0) {
                allBrandsCompleted = 0;
                break;
            }
        }
    }
    
    // Increment current day when all brands are completed
    (*currentDay)++;
}

// Function to provide daily stats
void provideDailyStats(int salesData[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int dayCount[NUM_OF_BRANDS]) {
    int day;
    
    printf("What day would you like to analyze?\n");
    scanf("%d", &day);
    
    // Validate day input
    while (day < 0 || day >= dayCount[0]) {
        printf("Please enter a valid day.\nWhat day would you like to analyze?\n");
        scanf("%d", &day);
    }
    
    int totalSales = 0;
    int brandSales[NUM_OF_BRANDS] = {0};
    int typeSales[NUM_OF_TYPES] = {0};
    
    // Calculate sales
    for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
        for (int type = 0; type < NUM_OF_TYPES; type++) {
            int sales = salesData[day][brand][type];
            totalSales += sales;
            brandSales[brand] += sales;
            typeSales[type] += sales;
        }
    }
    
    // Find best brand and type
    int bestBrand = 0, bestType = 0;
    for (int i = 1; i < NUM_OF_BRANDS; i++) {
        if (brandSales[i] > brandSales[bestBrand]) {
            bestBrand = i;
        }
    }
    
    for (int i = 1; i < NUM_OF_TYPES; i++) {
        if (typeSales[i] > typeSales[bestType]) {
            bestType = i;
        }
    }
    
    // Print results
    printf("In day number %d:\n"
           "The sales total was %d\n"
           "The best sold brand with %d sales was %s\n"
           "The best sold type with %d sales was %s\n", 
           day, totalSales, brandSales[bestBrand], brands[bestBrand], 
           typeSales[bestType], types[bestType]);
}

// Function to print entire dataset
void printEntireDataset(int salesData[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int dayCount[NUM_OF_BRANDS]) {
    printf("*****************************************\n");
    
    for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
        printf("Sales for %s:\n", brands[brand]);
        
        for (int day = 0; day < dayCount[brand]; day++) {
            printf("Day %d- ", day);
            for (int type = 0; type < NUM_OF_TYPES; type++) {
                printf("%s: %d ", types[type], salesData[day][brand][type]);
            }
            printf("\n");
        }
    }
    
    printf("*****************************************\n");
}

// Function to provide overall insights
void provideOverallInsights(int salesData[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int dayCount[NUM_OF_BRANDS]) {
    int brandTotalSales[NUM_OF_BRANDS] = {0};
    int typeTotalSales[NUM_OF_TYPES] = {0};
    int dayTotalSales[DAYS_IN_YEAR] = {0};
    
    // Calculate total sales for brands, types, and days
    for (int day = 0; day < dayCount[0]; day++) {
        for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
            for (int type = 0; type < NUM_OF_TYPES; type++) {
                int sales = salesData[day][brand][type];
                brandTotalSales[brand] += sales;
                typeTotalSales[type] += sales;
                dayTotalSales[day] += sales;
            }
        }
    }
    
    // Find best brand
    int bestBrand = 0;
    for (int i = 1; i < NUM_OF_BRANDS; i++) {
        if (brandTotalSales[i] > brandTotalSales[bestBrand]) {
            bestBrand = i;
        }
    }
    
    // Find best type
    int bestType = 0;
    for (int i = 1; i < NUM_OF_TYPES; i++) {
        if (typeTotalSales[i] > typeTotalSales[bestType]) {
            bestType = i;
        }
    }
    
    // Find most profitable day
    int bestDay = 0;
    for (int i = 1; i < dayCount[0]; i++) {
        if (dayTotalSales[i] > dayTotalSales[bestDay]) {
            bestDay = i;
        }
    }
    
    // Print insights
    printf("The best-selling brand overall is %s: %d$\n"
           "The best-selling type of car is %s: %d$\n"
           "The most profitable day was day number %d: %d$\n", 
           brands[bestBrand], brandTotalSales[bestBrand], 
           types[bestType], typeTotalSales[bestType], 
           bestDay + 1, dayTotalSales[bestDay]);
}

// Function to calculate average deltas
void calculateAverageDeltas(int salesData[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int dayCount[NUM_OF_BRANDS]) {
    for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
        double totalDelta = 0.0;
        int prevDayTotal = 0;
        
        // Calculate initial day total
        for (int type = 0; type < NUM_OF_TYPES; type++) {
            prevDayTotal += salesData[0][brand][type];
        }
        
        // Calculate deltas
        for (int day = 1; day < dayCount[brand]; day++) {
            int currentDayTotal = 0;
            for (int type = 0; type < NUM_OF_TYPES; type++) {
                currentDayTotal += salesData[day][brand][type];
            }
            
            totalDelta += (currentDayTotal - prevDayTotal);
            prevDayTotal = currentDayTotal;
        }
        
        // Calculate average delta
        double avgDelta = (dayCount[brand] > 1) ? (totalDelta / (dayCount[brand] - 1)) : 0;
        
        printf("Brand: %s, Average Delta: %.6f\n", brands[brand], avgDelta);
    }
}

int main() {
    // Initialize 3D array with -1
    int salesData[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    for (int day = 0; day < DAYS_IN_YEAR; day++) {
        for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
            for (int type = 0; type < NUM_OF_TYPES; type++) {
                salesData[day][brand][type] = -1;
            }
        }
    }
    
    // Initialize day counter and brand counters
    int currentDay = 0;
    int dayCount[NUM_OF_BRANDS] = {0};
    
    // Welcome message
    printf("Hello! Welcome to the Cars Data Cube!\n");
    
    // Main program loop
    while (1) {
        // Display menu
        displayMenu();
        
        // Get user choice
        int choice;
        scanf("%d", &choice);
        
        // Process user choice
        switch (choice) {
            case 1:
                enterDailyDataForBrand(salesData, dayCount, &currentDay);
                break;
            case 2:
                populateDayOfSales(salesData, dayCount, &currentDay);
                break;
            case 3:
                provideDailyStats(salesData, dayCount);
                break;
            case 4:
                printEntireDataset(salesData, dayCount);
                break;
            case 5:
                provideOverallInsights(salesData, dayCount);
                break;
            case 6:
                calculateAverageDeltas(salesData, dayCount);
                break;
            case 7:
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid input\n");
                continue;
        }
    }
    
    return 0;
}
