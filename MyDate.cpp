#include <iostream>
#include <string.h>
#include <fstream>

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
        setDate(other.getDay(), other.getMonth(), other.getYear());
    }

    // SECTION: HELPER FUNCTIONS------------------------------------------

    /*! A function to save the date into a file*/
    void save(ofstream& file){
        file.write((char*)&day, sizeof(int));
        file.write((char*)&month, sizeof(int));
        file.write((char*)&year, sizeof(int));

    }

    /*! A function to load the date from file*/
    void load(ifstream& file){
        file.read((char*)&day, sizeof(int));
        file.read((char*)&month, sizeof(int));
        file.read((char*)&year, sizeof(int));
    }

    /*! A function to add a day to current date. Includes validation*/
    void addDay(){
        // Adds a day
        day++;

        // Checks if the month is over and if yes it increments the month
        switch (month) {
            // Months with 31 days
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                if(day > 31){
                    day-=31;
                    month++;
                }
                break;
                // Months with 30 days
            case 4: case 6: case 9: case 11:
                if(day > 30){
                    day-=30;
                    month++;
                }
                break;
                // February
            case 2:
                // Leap year - there are 29 days in February
                if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0){
                    if(day > 29){
                        day-=29;
                        month++;
                    }
                }
                    // Not a leap year - 28 days in February
                else{
                    if(day > 28){
                        day-=28;
                        month++;
                    }
                }
                break;
        }

        // If the year is over it resets the months and increments the year
        if(month>12){
            month-=12;
            year++;
        }

        // Checks the date for problems
        if(!validateDate(day, month, year)){
            cout << "Something went wrong. Date is: ";
            print();
        }
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

    /*! This function returns the day of the week in a number form 0-Sunday, 1-Monday... etc.
     *  The logic for the function is from this article
     *  https://www.codespeedy.com/how-to-find-day-from-date-in-cpp/ */
    int getDayOfWeek()
    {
        static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
        year -= month < 3;
        return (year + year/4 - year/100 + year/400 + t[month-1] + day) % 7;
    }


    /*! A function for getting the date in YYYY-MM-DD format as char*
      - NOTE: The string has to be freed after use
    */
    char * getDateAsString() const {
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
        strcpy(str, year_string);
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

    /*! A function to print date into the console with YYYY-MM-DD formatting*/
    void print() const {
        char* string_date = getDateAsString();
        cout <<  string_date << endl;
        delete [] string_date;
    }

    // SECTION: OPERATORS--------------------------------------------------



    //! Overloading of the = operator
    void operator = (const MyDate& rhs){
        setDate(rhs.getDay(), rhs.getMonth(), rhs.getYear());
    }

    //! Overloading of the == operator
    bool operator==(const MyDate &rhs) const {
        return day == rhs.getDay() &&
               month == rhs.getMonth() &&
               year == rhs.getYear();
    }

    //! Overloading of the != operator
    bool operator!=(const MyDate &rhs) const {
        return !(rhs == *this);
    }

    //! Overloading of the < operator
    bool operator<(const MyDate &rhs) const {
        if (year < rhs.getYear())
            return true;
        if (rhs.getYear() < year)
            return false;
        if (month < rhs.getMonth())
            return true;
        if (rhs.month < getMonth())
            return false;
        return day < rhs.getDay();
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

    // SECTION: TESTS-----------------------------------------

    /*! Initializes date1. Then it initializes date2 by copying day1. Then it runs the following tests:
     * - Date change
     * - Leap year check
     * - Not a leap year check
     * - Wrong date check */
    static void initializationAndValidationTest(){
        MyDate date1 = MyDate(31, 10, 2022);
        cout << "date1: ";
        date1.print();

        MyDate date2 = MyDate(date1);
        cout << "date2 is copied from date1 and it's value is: ";
        date2.print();
        cout << endl;

        cout << "Changing date to 2022-05-06" << endl;
        date2.setDate(6, 5, 2022);
        cout << "date2: ";
        date2.print();
        cout << endl;

        cout << "Leap year check 2024-02-29" << endl;
        date2.setDate(29, 2, 2024);
        cout << "date2: ";
        date2.print();
        cout << endl;

        cout << "Changing the year to 2023. Should throw an error!!!" << endl;
        try {
            date2.setYear(2023);
        } catch (std::invalid_argument const& ex) {
            cout << "Exception caught: " << ex.what() << endl;
        }
        cout << "date2: ";
        date2.print();
        cout << endl;

        cout << "Changing date to 10000-13-42. Should throw an error!!!" << endl;
        try {
            date2.setDate(42, 13, 10000);
        } catch (std::invalid_argument const& ex) {
            cout << "Exception caught: " << ex.what() << endl;
        }
        cout << "date2: ";
        date2.print();
        cout << endl;
    }

    /*! Test for all operators. The function accepts two dates and runs tests on the operators of the class. */
    static void operatorsTest(const MyDate& date1, MyDate date2){
        cout << "== : " << ((date1==date2) ? "true" : "false") << endl;
        cout << "!= : " << ((date1!=date2) ? "true" : "false") << endl;
        cout << "> : " << ((date1>date2) ? "true" : "false") << endl;
        cout << "< : " << ((date1<date2) ? "true" : "false") << endl;
        cout << ">= : " << ((date1>=date2) ? "true" : "false") << endl;
        cout << "<= : " << ((date1<=date2) ? "true" : "false") << endl;

        cout << "Adding a day to date2: ";
        date2.addDay();
        date2.print();
    }

    static void saveAndLoadTest(){
        cout << "Saving date1 to file and loading it to date2:" << endl;
        ofstream file("Date.dat", ios::out | ios::binary);
        if(!file){
            throw invalid_argument("Couldn't open file");
        }
        MyDate date1 = MyDate(10, 12, 2021);
        date1.save(file);
        file.close();

        ifstream in("Date.dat", ios::in | ios::binary);
        if(!in){
            throw invalid_argument("Couldn't open file");
        }
        MyDate date2 = MyDate();
        date2.load(in);
        in.close();
        date2.print();
    }
};
