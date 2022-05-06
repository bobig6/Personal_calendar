#include <iostream>
#include "MyDate.cpp"
#include "MyHour.cpp"

using namespace std;

class Meeting{
    char* name;
    char* description;
    MyDate date;
    MyHour startHour;
    MyHour endHour;

public:
    // SECTION: CONSTRUCTORS--------------------------------------------------------
    //! Constructor for Meeting class with name, description, date, startHour and endHour as input
    Meeting(char* name, char* description, const MyDate& date, const MyHour& startHour, const MyHour& endHour){
        this->name = new char[strlen(name)];
        this->description = new char[strlen(description)];
        setName(name);
        setDescription(description);
        setDate(date);
        setStartHour(startHour);
        setEndHour(endHour);
    }

    //! Destructor for the Meeting class
    ~Meeting() {
        delete [] name;
        delete description;
    }


    // SECTION: GETTERS AND SETTERS-------------------------------------------------
    //! Getter for name field
    char *getName() const {
        return name;
    }

    //! Getter for description field
    char *getDescription() const {
        return description;
    }

    //! Getter for date field
    const MyDate &getDate() const {
        return date;
    }

    //! Getter for startHour field
    const MyHour &getStartHour() const {
        return startHour;
    }

    //! Getter for endHour field
    const MyHour &getEndHour() const {
        return endHour;
    }

    //! Setter for the name with memory handling
    void setName(char *new_name) {
        delete [] name;
        int size = strlen(new_name);
        name = new char[size + 1];
        strcpy(name, new_name);
    }

    //! Setter for the description with memory handling
    void setDescription(char *new_description) {
        delete [] description;
        int size = strlen(new_description);
        description = new char[size + 1];
        strcpy(description, new_description);
    }

    //! Setter for the date
    void setDate(const MyDate &new_date) {
        this->date = new_date;
    }

    //! Setter for the startHour
    void setStartHour(const MyHour &new_startHour) {
        this->startHour = new_startHour;
    }

    //! Setter for the endHour
    void setEndHour(const MyHour &new_endHour) {
        this->endHour = new_endHour;
    }

    /*! A print function for the Meeting class. Includes memory handling for the
     * strings of date, startHour and endHour*/
    void print(){
        cout << "Meeting \"" << name << "\": " << endl;
        cout << "Description: " << description << endl;
        cout << "Date: ";
        date.print();
        cout << "Starting hour: ";
        startHour.print();
        cout << "Ending hour: ";
        endHour.print();
    }

    // SECTION: TESTS-------------------------------------------------------

    /*! Test of initialization with correct values */
    static void initializationTest(){
        char* name = new char[20];
        char* description = new char[100];

        strcpy(name, "Appointment");
        strcpy(description, "Appointment with the doctor");

        Meeting meeting = Meeting(name,
                                  description,
                                  MyDate(24, 10, 2022),
                                  MyHour(10, 15),
                                  MyHour(12, 15));

        delete[] name;
        delete[] description;

        meeting.print();
    }
};