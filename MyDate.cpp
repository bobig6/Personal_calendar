#include <iostream>
#include <string.h>

using namespace std;

/*! This is a custom class created to hold the information about the date */
class MyDate{
    int day;       //! INT: Used for displaying the day in DD format
    int month;     //! INT: Used for displaying the month in MM format
    int year;      //! INT: Used for displaying the year in YYYY format

    // SECTION: VALIDATORS----------------------------------------------------------------------------

    /*! Validates days to be appropriate to the given month and year.
     * For the purpose of this project we will assume that a valid year is in the 1 - 9999 range. */
    bool validateDate(int new_days, int new_month, int new_year){
        // Check if day, month and year are valid number
        if(new_days < 1 || new_month < 1 || new_year < 1 || new_year > 9999) return false;

        switch (new_month) {
            // Months with 31 days
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                if(new_days > 31) return false;
                break;
            // Months with 30 days
            case 4: case 6: case 9: case 11:
                if(new_days > 30) return false;
                break;
            // February
            case 2:
                // Leap year - there are 29 days in February
                if((new_year % 4 == 0 && new_year % 100 != 0) || new_year % 400 == 0){
                    if(new_days > 29) return false;
                }
                // Not a leap year - 28 days in February
                else{
                    if(new_days > 28) return false;
                }
                break;
            // In all other cases the month is invalid
            default:
                return false;
        }

        // If every check has passed the date is correct
        return true;
    }

public:
    // SECTION: CONSTRUCTORS------------------------------------------------------------------------

    //! Constructor for MyDate class with day, month and year as input
    MyDate(int day, int month, int year){
        setDate(day, month, year);
    }

    //! Default constructor for MyDate class
    //!  - Sets the date to 2001-01-01
    MyDate(){
        setDate(1, 1, 2001);
    }

    //! Copy constructor for MyDate class
    MyDate(MyDate const &other){
        setDate(other.day, other.month, other.year);
    }

    // SECTION: GETTERS AND SETTERS------------------------------------------------

    //! Getter for the day
    int getDay() const {
        return day;
    }

    //! Getter for the month
    int getMonth() const {
        return month;
    }

    //! Getter for the year
    int getYear() const {
        return year;
    }

    //! Setter for the day with validation
    void setDay(int new_day) {
        if(!validateDate(new_day, month, year)){
            throw std::invalid_argument( "The day is invalid or not compatible with other arguments" );
        }
        this->day = new_day;
    }

    //! Setter for the month with validation
    void setMonth(int new_month) {
        if(!validateDate(day, new_month, year)){
            throw std::invalid_argument( "The month is invalid or not compatible with other arguments" );
        }
        this->month = new_month;
    }

    //! Setter for the year with validation
    void setYear(int new_year) {
        if(!validateDate(day, month, new_year)){
            throw std::invalid_argument( "The year is invalid or not compatible with other arguments" );
        }
        this->year = new_year;
    }

    //! Setter for day, month and year with validation
    void setDate(int new_day, int new_month, int new_year){
        if(!validateDate(new_day, new_month, new_year)){
            throw std::invalid_argument( "The given date is invalid" );
        }
        this->day = new_day;
        this->month = new_month;
        this->year = new_year;
    }

    /*! A function for getting the hour in HH:MM format as char*
      - NOTE: The string has to be freed after use
    */
    char* getDateAsString(){
        // Allocating new memory for the string
        char* str = new char[11];

        // Turning hours and minutes variables into strings
        char day_string[3];
        char month_string[3];
        char year_string[5];

        sprintf(day_string, "%d", day);
        sprintf(month_string, "%d", month);
        sprintf(year_string, "%d", year);

        // Formatting of the string
        strcat(str, year_string);
        strcat(str, "-");

        if(month < 10){
            strcat(str, "0");
        }
        strcat(str, month_string);
        strcat(str, "-");

        if(day < 10){
            strcat(str, "0");
        }
        strcat(str, day_string);

        return str;
    }

    // SECTION: OPERATORS--------------------------------------------------

    //! Overloading of the = operator
    void operator = (const MyDate& rhs){
        setDate(rhs.day, rhs.month, rhs.year);
    }

    //! Overloading of the == operator
    bool operator==(const MyDate &rhs) const {
        return day == rhs.day &&
               month == rhs.month &&
               year == rhs.year;
    }

    //! Overloading of the != operator
    bool operator!=(const MyDate &rhs) const {
        return !(rhs == *this);
    }

    //! Overloading of the < operator
    bool operator<(const MyDate &rhs) const {
        if (year < rhs.year)
            return true;
        if (rhs.year < year)
            return false;
        if (month < rhs.month)
            return true;
        if (rhs.month < month)
            return false;
        return day < rhs.day;
    }

    //! Overloading of the > operator
    bool operator>(const MyDate &rhs) const {
        return rhs < *this;
    }

    //! Overloading of the <= operator
    bool operator<=(const MyDate &rhs) const {
        return !(rhs < *this);
    }

    //! Overloading of the >= operator
    bool operator>=(const MyDate &rhs) const {
        return !(*this < rhs);
    }

};
