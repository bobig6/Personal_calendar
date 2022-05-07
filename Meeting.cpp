#include <iostream>
#include "MyDate.cpp"
#include "MyHour.cpp"

using namespace std;

class Meeting{
    char* name;           //! TEXT: A char array used for containing the name of the meeting
    char* description;    //! TEXT: A char array used for describing the meeting
    MyDate date;          //! DATE: A MyDate object used for keeping the date of the meeting
    MyHour startHour;     //! TIME: A MyHour object containing the starting hour
    MyHour endHour;       //! TIME: A MyHour object containing the ending hour

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

    //! Default constructor creates empty meeting object
    Meeting(){

        // Creating sample name and description to give to the set function
        char* new_name = new char[20];
        char* new_description = new char[100];

        strcpy(new_name, "Empty");
        strcpy(new_description, "");

        this->name = new char[strlen(new_name)];
        this->description = new char[strlen(new_description)];
        setMeeting(new_name,
                   new_description,
                  MyDate(),
                  MyHour(),
                  MyHour());

        delete[] new_name;
        delete[] new_description;
    }

    //! Copy constructor for the Meeting class
    Meeting(const Meeting &other){
        this->name = new char[strlen(other.getName())];
        this->description = new char[strlen(other.getDescription())];
        setMeeting(other.getName(), other.getDescription(), other.getDate(), other.getStartHour(), other.getEndHour());
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

    //! Setter for the meeting object. It gets all the arguments and sets them to the current object
    void setMeeting(char* new_name, char* new_description, const MyDate& new_date, const MyHour& new_startHour, const MyHour& new_endHour){
        setName(new_name);
        setDescription(new_description);
        setDate(new_date);
        setStartHour(new_startHour);
        setEndHour(new_endHour);
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

    // SECTION: OPERATORS---------------------------------------------------

    void operator = (const Meeting& rhs){
        setMeeting(rhs.getName(), rhs.getDescription(), rhs.getDate(), rhs.getStartHour(), getEndHour());
    }

    /*! Equality operator for the Meeting class.
     * Compares two meetings by all arguments. */
    bool operator==(const Meeting &rhs) const {
        return name == rhs.getName() &&
               description == rhs.getDescription() &&
               date == rhs.getDate() &&
               startHour == rhs.getStartHour() &&
               endHour == rhs.getEndHour();
    }

    /*! Overloading of the < operator.
     * It compares on date, startHour and endHour in this order*/
    bool operator<(const Meeting &rhs) const {
        if (date < rhs.getDate())
            return true;
        if (rhs.getDate() < date)
            return false;
        if (startHour < rhs.getStartHour())
            return true;
        if (rhs.getStartHour() < startHour)
            return false;
        return endHour < rhs.getEndHour();

    }

    /*! Overloading of the > operator. */
    bool operator>(const Meeting &rhs) const {
        return rhs < *this;
    }

    /*! Overloading of the <= operator. */
    bool operator<=(const Meeting &rhs) const {
        return !(rhs < *this);
    }

    /*! Overloading of the >= operator. */
    bool operator>=(const Meeting &rhs) const {
        return !(*this < rhs);
    }

    /*! Overloading of the != operator. */
    bool operator!=(const Meeting &rhs) const {
        return !(rhs == *this);
    }



    // SECTION: TESTS-------------------------------------------------------

    /*! Test of initialization with correct values */
    static void initializationTest(){
        char* test_name = new char[20];
        char* test_description = new char[100];

        strcpy(test_name, "Appointment");
        strcpy(test_description, "Appointment with the doctor");

        Meeting meeting = Meeting(test_name,
                                  test_description,
                                  MyDate(24, 10, 2022),
                                  MyHour(10, 15),
                                  MyHour(12, 15));

        delete[] test_name;
        delete[] test_description;

        meeting.print();

        cout << endl << "Testing constructors. Empty meeting: " << endl;
        Meeting empty = Meeting();
        empty.print();
        cout << endl << "Copying the meeting to new one and changing the date: New meeting: " << endl;
        Meeting empty1 = Meeting(empty);
        empty1.setDate(MyDate(23, 4, 2024));
        empty1.print();

    }

    /*! Test for all operators. The function accepts two meetings and runs tests on the operators of the class. */
    static void operatorsTest(const Meeting& meeting1, const Meeting& meeting2){
        cout << "== : " << ((meeting1==meeting2) ? "true" : "false") << endl;
        cout << "!= : " << ((meeting1!=meeting2) ? "true" : "false") << endl;
        cout << "> : " << ((meeting1>meeting2) ? "true" : "false") << endl;
        cout << "< : " << ((meeting1<meeting2) ? "true" : "false") << endl;
        cout << ">= : " << ((meeting1>=meeting2) ? "true" : "false") << endl;
        cout << "<= : " << ((meeting1<=meeting2) ? "true" : "false") << endl;
    }
};