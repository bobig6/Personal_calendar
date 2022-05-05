#include <iostream>
#include <string.h>

using namespace std;

/*! This is a custom class created to hold the information about the hour */
class MyHour{
    int hours;       //! INT: Used for displaying the hours in 24h format
    int minutes;     //! INT: Used for displaying the minutes in decimal format

    //! Validates minutes to be in the 0-59 range
    bool validateMinutes(int new_minutes){
        return new_minutes>=0 && new_minutes<60;
    }

    //! Validates hours to be in the 0-23 range
    bool validateHours(int new_hour){
        return new_hour>=0 && new_hour<24;
    }


public:
    // SECTION: CONSTRUCTORS---------------------------------------

    //! Constructor for MyHour class with hour and minutes as input
    MyHour(int hours, int minutes){
        setHours(hours);
        setMinutes(minutes);
    }

    //! Constructor for MyHour class only with hour as input
    //!  - Sets minutes to :00
    MyHour(int hours){
        setHours(hours);
        setMinutes(0);
    }

    //! Default constructor for MyHour class
    //!  - Sets the hour to 00:00
    MyHour(){
        setHours(0);
        setMinutes(0);
    }


    // SECTION: GETTERS AND SETTERS---------------------------------------

    //! Getter for hours field
    int getHours() const {
        return hours;
    }

    //! Getter for minutes field
    int getMinutes() const {
        return minutes;
    }

    //! Setter for hours field
    //! - Also validates field to be in the 0-23 range
    void setHours(int new_hours) {
        if(!validateHours(new_hours)){
            throw std::invalid_argument( "Hour is not in 0-23 range" );
        }
        this->hours = new_hours;
    }


    //! Setter for minutes field
    //! - Also validates field to be in the 0-59 range
    void setMinutes(int new_minutes) {
        if(!validateMinutes(new_minutes)){
            throw std::invalid_argument( "Minutes are not in 0-59 range" );
        }
        this->minutes = new_minutes;
    }

    /*! A function for getting the hour in HH:MM format as char*
      - NOTE: The string has to be freed after use
    */
    char* getHourAsString(){
        // Allocating new memory for the string
        char* str = new char[6];

        // Turning hours and minutes variables into strings
        char hours_string[3];
        char minutes_string[3];

        sprintf(hours_string, "%d", hours);
        sprintf(minutes_string, "%d", minutes);

        // Formatting of the string
        if(hours<10){
            strcat(str, "0");
        }
        strcat(str, hours_string);

        strcat(str, ":");

        if(minutes<10){
            strcat(str, "0");
        }
        strcat(str, minutes_string);

        return str;
    }

    // SECTION: TESTS----------------------------------

    //! Test of initialization with input 20:59
    static void initializationTestPositive(){
        MyHour hour = MyHour(20, 59);
        cout << hour.getHourAsString() << endl;
    }

    //! Test of initialization with input 30:59
    static void initializationTestNegative(){
        MyHour hour = MyHour(30, 59);
        cout << hour.getHourAsString() << endl;
    }
};
