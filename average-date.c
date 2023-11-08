#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Author: Tristan Seto
// Date: 2023-02-28
// Description: The program takes in a pre-determined number of dates and calculates the average date given them.
// Quirks: The program works only for dates after January 1, 1600, and will only calculate the average for less than 20 dates.
/*  Disclaimer: This is my first major project outside of school before completing my first programming course.
    Originally called, "Birthday Average Calculator," this program does not contain data structures or classes and is purely
    based on knowledge from the first half of APS 105 S – which includes arrays and uses an introductory experiment to dynamic memory allocation.
    The following program is not perfect and may have small quirks in the code as I attempted to navigate the edge cases as best as I could
    with the knowledge I had at the time. As of November 2023, I am working on improving the average birthday calculator (with a new name)
    in C++ using classes and object-oriented programming, and hope to include more features to birthdays, such as a function for differences
    between dates as well as a storage of multiple dates and selective averages.
*/
// Original Title: birthday-avg.c

bool validateBirthday(int, int, int);
void dateToNum(int[],int[],int[],int,int[]);
int average(int[], int);
void numToDate(int,int*,int*,int*);
bool checkDays(int, int, int);

int main(void){
    int size = 0;
    int * birthyear = NULL;
    int * birthmonth = NULL;
    int * birthday = NULL;
    int * nums = NULL;

    // Take in # of dates to average from user; Only less than 20.
    do{
        printf("Enter number of people: ");
        scanf("%d",&size);
    } while(size > 20 || size < 1);

    // Dynamically allocate arrays for each component of the date
    birthday = (int*) malloc(size * sizeof(int));
    birthmonth = (int*) malloc(size * sizeof(int));
    birthyear = (int*) malloc(size * sizeof(int));
    nums = (int*) malloc(size * sizeof(int)); // Array that will store the date code use for calculation

    // Take in date input from user
    for(int i = 0; i < size; i++){
        printf("\nEnter person %d's birth year: ",i + 1);
        scanf("%d", &birthyear[i]);
        printf("Enter person %d's birth month: ",i + 1);
        scanf("%d", &birthmonth[i]);
        printf("Enter person %d's birth date: ",i + 1);
        scanf("%d", &birthday[i]);

        // For invalid birthdays:
        if(!validateBirthday(birthyear[i],birthmonth[i],birthday[i])){
            printf("\nInvalid birthdate, please enter another birthdate.\n");
            i--;
        }
    }
    // convert Year to Year - 1600 for simplicity
    for(int i = 0; i < size; i++){
        birthyear[i] = birthyear[i] - 1600;
    } // (less bits for common dates in the 2000s, however program will not work for negative years)

    // Send arrays of years, months and days and convert them to codes:
    dateToNum(birthyear, birthmonth, birthday, size, nums);

    // Calculate the average of the codes:
    int avg = average(nums, size);

    // Declare and reverse engineer the average into a year, month and day with the given code
    int avgYear = 0, avgMonth = 0, avgDay = 0;
    numToDate(avg, &avgYear, &avgMonth, &avgDay);

    // revert Year back to Year + 1600;
    avgYear = avgYear + 1600;

    // print the average to the user
    printf("\nThe average date is %d/%d/%d.\n\n",avgYear,avgMonth,avgDay);

    // free all dynamic memory allocated space and set all pointers to NULL.
    free(birthday);
    free(birthmonth);
    free(birthyear);
    birthday = NULL;
    birthmonth = NULL;
    birthyear = NULL;
    return 0;
}


bool validateBirthday(int year,int month,int day){
    bool valid = true;

    // Program will not work on dates before 1600
    // Month and day must not exceed December 31.
    if(year < 1600 || month > 12 || day > 31){
        valid = false;
    } else // Note specific cases for different months, i.e. February 30th, April 31st, November 31st, etc.
    if((month == 2 && day > 29)|| (month % 2 == 0 && month < 7 && day > 30) || (month % 2 == 1 && month > 7 && day > 30)){
        valid = false;
    }

    // Note the leap day February 29th is only valid depending on the year
    if(month == 2 && day == 29){
        if(year % 400 == 0){
            valid = true;
        } else if(year % 100 == 0){
            valid = false;
        } else if(year % 4 != 0){
            valid = false;
        }
    }

    return valid;
}

// Function converts the year, month and days in the array to an array of codes
void dateToNum(int year[], int month[], int day[],int size,int num[]){
    int convert = 0;
    
    for(int i = 0; i < size; i++){
        // add year & leap day
        convert = year[i] * 365 + year[i] / 4 - year[i] / 100 + year[i] / 400;
        // add month
        convert = convert + (month[i] - 1) * 28;

        for(int m = 1; m < month[i]; m++){
            if(m == 2 && year[i] % 4 == 0 && (year[i] % 100 != 0 || year[i] % 400 == 0)){
                convert = convert + 1;
            } else if(m == 2){
            } else if((m % 2 == 0 && m < 7) || (m % 2 == 1 && m > 7)){
                convert = convert + 2;
            } else {
                convert = convert + 3;
            }
        }

        // add days
        convert = convert + day[i];

        num[i] = convert;
        convert = 0;
    }

}

// Calculates the average of the codes in the array
int average(int data[], int size){
    int averageNum = 0;
    int sum = 0;
    
    for(int i = 0; i < size; i++){
        sum = sum + data[i];
    }
    
    averageNum = sum / size;

    return averageNum;
}

// Converts a code back into date
void numToDate(int num, int* avgYear, int* avgMonth, int* avgDay){
    int year = 0, month = 0, day = 0;
    const int leap400 = (365 * 400 + 400 / 4 - 400 / 100 + 400 / 400);
    const int leap100 = (365 * 100 + 100 / 4 - 100 / 100);
    const int leap4 = 365 * 4 + 1;
    const int oneYear = 365;
    
    // years
    if(num / leap400 > 0){
        year = num / leap400 * 400;
        num = num % leap400;
    }

    if(num / leap100 > 0){
        year = year + num / leap100 * 100;
        num = num % leap100;
    }

    if(num / leap4 > 0){
        year = year + num / leap4 * 4;
        num = num % leap4;
    }

    if(num == 366){
        year = year + num / (oneYear + 1);
        num = num % (oneYear + 1);
    } else if(num != 365){
        year = year + num / oneYear;
        num = num % oneYear;
    }

    // months
    int m = 0;

    for(m = 1; m <= 12 && checkDays(m,num,year); m++){
        if(m == 2 && year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)){
            num = num - 29;
        } else if(m == 2){
            num = num - 28;
        } else if((m % 2 == 0 && m < 7) || (m % 2 == 1 && m > 7)){
            num = num - 30;
        } else {
            num = num - 31;
        }
    }
    month = m;

    //days

    day = num;

    // Last day of the year, given the nature of the modulo operator, should be converted back from January 0, Year X+1 to December 31, Year X:
    if(num == 0){
        day = 31;
        month = 12;
        year = year - 1;
    }

    // assign to values

    * avgYear = year;
    * avgMonth = month;
    * avgDay = day;
    
}

// Check days of a year
bool checkDays(int m, int days, int year){
    bool valid = false;

    if(m == 2 && days > 29){
        valid = true;
    } else if(m == 2 && days == 29){
        if(year % 400 == 0){
            valid = false;
        } else if(year % 4 == 0 && year % 100 != 0){
            valid = false;
        } else {
            valid = true;
        }
    } else if(((m % 2 == 0 && m < 7) || (m % 2 == 1 && m > 7)) && days > 30){
        valid = true;
    } else if(days > 31){
        valid = true;
    }

    return valid;
}
