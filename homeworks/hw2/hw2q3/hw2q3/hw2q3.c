#include <stdio.h>
#include <stdbool.h>

#define LEFT_AXIS 'L'
#define RIGHT_AXIS 'R'
#define UP_AXIS 'U'
#define DOWN_AXIS 'D'
#define SIZE 9

// Functions declarations
char inputIndicator();
char inputAxis();
bool isValidAxis(char axis);
void inputGrades(int grades[SIZE]);
void printHistogram(int grades[SIZE], char axis, char indicator);
void printUpHistogram(int grades[SIZE],
                      char indicator, int maxFrequency);
void printDownHistogram(int grade[SIZE],
                        char indicator, int maxFrequency);
void printLeftHistogram(int grades[SIZE],
                        char indicator, int maxFrequency);
void printRightHistogram(int grades[SIZE],
                         char indicator, int maxFrequency);
void printHistogramIndicator(int grade, int currentFrequency,
                             char indicator, bool columnSpace);
void printHorizontalAxis();
void printHorizontalLevel(int grade[SIZE],
                          int frequency, char indicator);
int getMaxValue(int grades[SIZE]);


int main() {
    char indicator = inputIndicator();
    char axis = inputAxis();

    int grades[SIZE] = {0};
    inputGrades(grades);

    printHistogram(grades, axis, indicator);

    return 0;
}

// Read desired histogram indicator from user
char inputIndicator() {
    char indicator = 0;
    printf("Please enter a character:\n");
    scanf(" %c", &indicator);

    return indicator;
}

// Read desired histogram axis from user
char inputAxis() {
    char axis = 0;

    do {
        printf("Please enter histogram axis:(U/D/R/L)\n");
        scanf(" %c", &axis);
    } while(!isValidAxis(axis));

    return axis;
}

// Returns true if the axis input provided is valid (U/D/R/L)
bool isValidAxis(char axis) {
    if(axis != LEFT_AXIS && axis != RIGHT_AXIS
    && axis != UP_AXIS && axis != DOWN_AXIS) {
        printf("Wrong direction, try again!\n");
        return false;
    }

    return true;
}

// Asks the user to insert grades
void inputGrades(int grades[SIZE]) {
    int grade = 0;
    printf("Please enter grades:\n");
    while(scanf("%d", &grade) == 1) {
        grades[grade-1]++;
    }
}

void printHistogram(int grades[SIZE], char axis, char indicator) {
    int maxFrequency = getMaxValue(grades);

    printf("Histogram:\n");
    switch (axis) {
        case DOWN_AXIS:
            printDownHistogram(grades, indicator, maxFrequency);
            break;
        case UP_AXIS:
            printUpHistogram(grades, indicator, maxFrequency);
            break;
        case LEFT_AXIS:
            printLeftHistogram(grades, indicator, maxFrequency);
            break;
        case RIGHT_AXIS:
            printRightHistogram(grades, indicator, maxFrequency);
            break;
        default:
            break;
    }
}

// Dedicated functions to print each histogram direction

void printUpHistogram(int grades[SIZE],
                      char indicator, int maxFrequency) {
    printHorizontalAxis();

    /* For each histogram frequency, print for each grade
     * an indicator if it's as common or more */
    for(int frequency = 1; frequency <= maxFrequency; frequency++) {
        printHorizontalLevel(grades, frequency, indicator);
    }
}

void printDownHistogram(int grades[SIZE],
                        char indicator, int maxFrequency) {
    /* Looping in descending order, for each histogram frequency,
     * print for each grade an indicator if it's as common or more */
    for(int frequency = maxFrequency; frequency > 0; frequency--) {
       printHorizontalLevel(grades, frequency, indicator);
    }

    printHorizontalAxis();
}

void printLeftHistogram(int grades[SIZE],
                        char indicator, int maxFrequency) {
    // For each grade print it and then its histogram graph (in a row)
    for(int i = 0; i < SIZE; i++) {
         printf("%d ", i+1);

         for(int frequency = 1; frequency <= maxFrequency; frequency++) {
             printHistogramIndicator(grades[i], frequency, indicator,
                                     frequency < maxFrequency);
         }

         printf("\n");
    }
}

void printRightHistogram(int grades[SIZE],
                         char indicator, int maxFrequency) {
    /* For each grade, loop the frequencies in descending order and
     * print an indicator accordingly */
    for(int i = 0; i < SIZE; i++) {
        for(int frequency = maxFrequency; frequency > 0; frequency--) {
            printHistogramIndicator(grades[i], frequency,
                                    indicator, frequency > 0);
        }

        printf("%d\n", i+1);
    }
}

// Prints either an indicator or a space according to the frequency
void printHistogramIndicator(int grade, int currentFrequency,
                             char indicator, bool columnSpace) {
    if (grade >= currentFrequency) {
        printf("%c", indicator);
    } else {
        printf(" ");
    }

    if(columnSpace) {
        printf(" ");
    }
}

// Prints horizontal axis (grades list) for "Up" and "Down" directions
void printHorizontalAxis() {
    for(int i = 0; i < SIZE; i++) {
        printf("%d", i+1);

        if(i < SIZE-1) {
            printf(" ");
        }
    }

    printf("\n");
}


// Prints a horizontal level of histogram per each grade
void printHorizontalLevel(int grades[SIZE],
                          int frequency, char indicator) {
    // Print an indicator for each grade if it's as frequent or more
    for(int i = 0; i < SIZE; i++) {
        printHistogramIndicator(grades[i], frequency,
                                indicator, i < SIZE-1);
    }

    printf("\n");
}

// Gets the max value in a grades array (i.e. the most common grade)
int getMaxValue(int grades[SIZE]) {
    int max = -1;
    for(int i = 0; i < SIZE; i++) {
        if(grades[i] > max) {
            max = grades[i];
        }
    }

    return max;
}

