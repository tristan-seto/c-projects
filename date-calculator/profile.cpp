#include <iostream>
#include <string>

// Helper Function
bool checkDays(int m, int days, int year);

class Profile {
    private:
    std::string name;
    int year;
    int month;
    int day;
    int code;

    // Class Mutators
    int setCode(void);
    void setDate(void);
    void setYear(int);
    void setMonth(int);

    public:
    Profile(std::string n, int y, int m, int d){
        name = n;
        year = y;
        month = m;
        day = d;
        setCode();
    }

    Profile(std::string n, int c){
        name = n;
        code = c;
        setDate();
    }

    // Accessors:
    int getYear(void){
        return year;
    }

    int getMonth(void){
        return month;
    }

    int getDay(void){
        return day;
    }

    int getCode(void){
        return code;
    }

    // Functions
    int getDifference(const Profile&);
    Profile twoAverage(const Profile&);
    Profile operator+(const Profile&); // also a get average

};

int Profile::setCode(void){
    int c = year * 365 + (year / 4) - (year / 100) + (year / 400) + month * 28 + day;

        if(month == 2){
            if(((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)))){
                c++;
            }
        } else if(month == 4 || month == 6 || month == 9 || month == 11){
            c += 2;
        } else {
            c += 3;
        }
    code = c;
    return c;
}

void Profile::setDate(void){
    int num = code;
    setYear(num);
    setMonth(num);
    day = num;

    // Case if Day = 0, reset to December 31
    if(num == 0){
        day = 31;
        month = 12;
        year = year - 1;
    }
}

void Profile::setYear(int num){
    const int leap400 = (365 * 400 + 400 / 4 - 400 / 100 + 400 / 400);
    const int leap100 = (365 * 100 + 100 / 4 - 100 / 100);
    const int leap4 = 365 * 4 + 1;
    const int oneYear = 365;
    
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

    return;
}

void Profile::setMonth(int num){
    int m = 0;
    bool leap = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);

    for(m = 1; m <= 12 && checkDays(m,num,year); m++){
        if(m == 2 && leap){
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

}

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

// Function Implementations

int Profile::getDifference(const Profile& rhs){
    if(code > rhs.code){
        return code - rhs.code;
    } else {
        return rhs.code - code;
    }
}

Profile Profile::twoAverage(const Profile& rhs){
    int average = (code + rhs.code) / 2;
    std::string n = "Average of " + name + " and " + rhs.name;
    Profile avg(n, average);
    return avg;
}

Profile Profile::operator+(const Profile& rhs){
    return twoAverage(rhs);
}

// int main(){return 0;}
