#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#define N 51
#define MAX_GRADE 100
#define MIN_GRADE 0
#define MAX_STD 10

// Functions declarations
void printGradesOpening();
void printOldGrades(double grades[N], int gradesNum);
void calcAndPrintGradesStats(double grades[N],
                             int gradesNum, bool printOld);
void printOldGradesStats(double min, double max,
                         double mean, double std);
void printNewGradesStats(double min, double max,
                         double mean, double std);
void printNewGrades(double grades[N], int gradesNum);
double minMaxGrades(double grades[N], int gradesNum, bool isMin);
double meanGrades(double grades[N], int gradesNum);
double stdGrades(double grades[N], int gradesNum, double mean);
void printGrades(double grades[N], int gradesNum);
void updateGrades(double grades[N], int gradesNum,
                  double predictedMean, double maxStd);
int gradesInput(double grades[N]);
double absValue(double value);
double maxGrade(double grades[N], int gradesNum);
double minGrade(double grades[N], int gradesNum);

int main() {
    printGradesOpening();

    double grades[N] = {0};
    int gradesNum = gradesInput(grades);
    // Gets the predicted mean value (the last value inserted)
    double predictedMean = grades[gradesNum];

    printOldGrades(grades, gradesNum);
    calcAndPrintGradesStats(grades, gradesNum, true);

    updateGrades(grades, gradesNum, predictedMean, MAX_STD);

    printNewGrades(grades, gradesNum);
    calcAndPrintGradesStats(grades, gradesNum, false);
}


// Prints an opening message for the program
void printGradesOpening() {
    printf("Please enter the grades of the examinees");
    printf(" followed by the expected mean\n");
}

// Prints the inserted grades before update
void printOldGrades(double grades[N], int gradesNum){
    printf("Old grades: ");
    printGrades(grades, gradesNum);
}

/* Calculates and prints either the grades
 * before update(old) or after it(new) */
void calcAndPrintGradesStats(double grades[N],
                             int gradesNum, bool printOld) {
    double min = minMaxGrades(grades, gradesNum, true);
    double max = minMaxGrades(grades, gradesNum, false);
    double mean = meanGrades(grades, gradesNum);
    double std = stdGrades(grades, gradesNum, mean);

    if(printOld) {
        printOldGradesStats(min, max, mean, std);
    }
    else {
        printNewGradesStats(min, max, mean, std);
    }
}

// Prints grades stats before update
void printOldGradesStats(double min, double max,
                              double mean, double std) {
    printf("Old minimum grade: %.1f\n", min);
    printf("Old maximum grade: %.1f\n", max);
    printf("Old mean: %.1f\n", mean);
    printf("Old standard deviation: %.1f\n",std);
}

// Prints grades stats after update
void printNewGradesStats(double min, double max,
                              double mean, double std) {
    printf("New minimum grade: %.1f\n", min);
    printf("New maximum grade: %.1f\n", max);
    printf("New mean: %.1f\n", mean);
    printf("New standard deviation: %.1f\n", std);
}

// Prints grades after update
void printNewGrades(double grades[N], int gradesNum) {
    printf("New grades: ");
    printGrades(grades, gradesNum);
}

// Returns either min or max value in a grades array,
double minMaxGrades(double grades[N], int gradesNum, bool isMin) {
    if(isMin) {
        return minGrade(grades, gradesNum);
    }

    return maxGrade(grades, gradesNum);
}

// Calculates and returns the mean value of grades
double meanGrades(double grades[N], int gradesNum) {
    double sum = 0;
    for(int i = 0; i < gradesNum; i++) {
        sum = sum + grades[i];
    }

    return sum / gradesNum;
}

// Calculates and returns the standard deviation of grades
double stdGrades(double grades[N], int gradesNum, double mean) {
    double sum = 0;

    // Sums the grades diffs from mean value(sigma notation)
    for(int i = 0; i < gradesNum; i++) {
        sum = sum + (grades[i] - mean)*(grades[i] - mean);
    }

    // Calculates and returns the std deviation
    return sqrt((1.0/gradesNum)*sum);
}

// Prints a list of grades from an array
void printGrades(double grades[N], int gradesNum) {
    for(int i = 0; i < gradesNum; i++) {
        printf("%.1f", grades[i]);
        if(i < gradesNum-1) {
            printf(" ");
        }
    }

    printf("\n");
}

/* Updates the grades according to the predicted mean value and
 * the max standard deviation constant */
void updateGrades(double grades[N], int gradesNum,
                  double predictedMean, double maxStd) {

    double currentMean = meanGrades(grades, gradesNum);
    double currentStd = stdGrades(grades, gradesNum, currentMean);

    // Update grades if the conditions are met (steps 1+2)
    if(currentStd > maxStd) {
        for(int i = 0; i < gradesNum; i++) {
            grades[i] = grades[i] * (maxStd/currentStd);
        }

        // Recalculate mean after step 1 update
        currentMean = meanGrades(grades, gradesNum);
    }

    if(absValue(currentMean - predictedMean) > 1) {
        for(int i = 0; i < gradesNum; i++) {
            grades[i] = grades[i] - currentMean + predictedMean;
        }
    }
}

// Returns the absolute value of a given number
double absValue(double value) {
    if(value < 0) {
        return -value;
    }

    return  value;
}

/* Reads students' grades from user input and returns the number
   of grades */
int gradesInput(double grades[N]) {
    double grade;
    int counter = 0;

    while(scanf("%lf", &grade) != EOF) {
        grades[counter] = grade;
        counter ++;
    }

    return counter-1;
}

// Finds the minimum grade in a grades array
double minGrade(double grades[N], int gradesNum) {
    double min = MAX_GRADE + 1;
    for(int i = 0; i < gradesNum; i++) {
        if(grades[i] < min) {
            min = grades[i];
        }
    }

    return min;
}

// Finds the maximum grade in a grades array
double maxGrade(double grades[N], int gradesNum) {
    double max = MIN_GRADE - 1;
    for(int i = 0; i < gradesNum; i++) {
        if(grades[i] > max) {
            max = grades[i];
        }
    }

    return max;
}

