#include <iostream>
#include "Meeting.cpp"

using namespace std;

class PersonalCalendar{
    Meeting* meetingList;     //! MEETING: An array that contains all the meetings
    int current;              //! INT: The number of the current meeting. Used to keep the number of meetings in the calendar
    int size;                 //! INT: Contains the size of the array

    //! A function to resize the meeting list
    void resizeMeetingList() {
        // Creating a buffer to hold the info
        Meeting* buff = new Meeting[size];
        for (int i = 0; i < size; ++i) {
            buff[i] = meetingList[i];
        }

        // Resizing the array
        delete [] meetingList;
        size *= 2;
        meetingList = new Meeting[size];

        // Returning the data to the array
        for (int i = 0; i < current; ++i) {
            meetingList[i] = buff[i];
        }
        delete [] buff;
    }

public:
    // SECTION: CONSTRUCTORS------------------------------------------------------------------

    //! Constructor with all parameters for PersonalCalendar class
    PersonalCalendar(Meeting *meetingList, int current, int size) :current(current), size(size) {
        this->meetingList = new Meeting[size];
        setMeetingList(meetingList, current, size);
    }

    //! Default constructor for PersonalCalendar class. Creates meeting list with size 10
    PersonalCalendar(){
        this->size = 10;
        this->current = 0;
        this->meetingList = new Meeting[this->size];
    }

    //! Copy constructor for the PersonalCalendar class
    PersonalCalendar(const PersonalCalendar &other){
        setSize(other.size);
        setCurrent(other.current);
        meetingList = new Meeting[other.size];
        setMeetingList(other.meetingList, other.current, other.size);
    }

    //! Destructor for PersonalCalendar class
    ~PersonalCalendar() {
        delete [] meetingList;
    }




    // SECTION: GETTERS AND SETTERS-----------------------------------------------------------
    //! Getter for the meeting array
    Meeting *getMeetingList() const {
        return meetingList;
    }

    //! Getter for the current element number
    int getCurrent() const {
        return current;
    }

    //! Getter for the size of the array
    int getSize() const {
        return size;
    }

    //! Getter for meeting by name. NOTE: Throws invalid_argument exception
    Meeting getByName(char* new_name){
        for (int i = 0; i < current; ++i) {
            if(strcmp(meetingList[i].getName(), new_name) == 0){
                return meetingList[i];
            }
        }
        throw std::invalid_argument( "Meeting not found" );
    }


    //! Getter for meeting by date. NOTE: Throws invalid_argument exception
    Meeting getByDate(const MyDate& date){
        for (int i = 0; i < current; ++i) {
            if(meetingList[i].getDate() == date){
                return meetingList[i];
            }
        }
        throw std::invalid_argument( "Meeting not found" );
    }


    //! Getter for first matched meeting by word in the description. NOTE: Throws invalid_argument exception
    Meeting getFirstByWordInDescription(char* word){
        for (int i = 0; i < current; ++i) {
            if(strstr(meetingList[i].getDescription(), word) != NULL){
                return meetingList[i];
            }
        }
        throw std::invalid_argument( "Meeting not found" );
    }

    //! Getter for all meeting which description contain a given word. NOTE: Returns the number of matches
    int getAllByWordInDescription(Meeting* newMeetingList, char* word){
        int j = 0;
        for (int i = 0; i < current; ++i) {
            if(strstr(meetingList[i].getDescription(), word) != NULL){
                newMeetingList[j] = meetingList[i];
                j++;
            }
        }
        return j;
    }

    //! Setter for the meeting list
    void setMeetingList(Meeting *newMeetingList, int new_current, int new_size) {
        delete [] this->meetingList;
        this->meetingList = new Meeting[new_size];
        for (int i = 0; i < new_current+1; ++i) {
            this->meetingList[i] = newMeetingList[i];
        }
    }

    //! Setter for the current element number
    void setCurrent(int new_current) {
        this->current = new_current;
    }

    //! Setter for the size of the array
    void setSize(int new_size) {
        this->size = new_size;
    }

    //! A function to add a new meeting to the meeting list. Resizes the list if necessary
    void addMeeting(const Meeting& meeting){
        if(current >= size) resizeMeetingList();
        meetingList[current] = meeting;
        current++;
    }

    //! A function to print the class
    void print(){
        cout << "Personal calendar: " << endl << endl;
        for (int i = 0; i < current; ++i) {
            meetingList[i].print();
            cout << endl;
        }
    }

    // SECTION: TESTS---------------------------------------------------------

    /*! Test for initialization and get methods of the Personal calendar
     * - Creates empty calendar
     * - Creates a meeting with pre-initialized name and description and adds it to the list
     * - Creates a meeting with const string as arguments and adds it to the list
     * - Adds 9 more meetings with different date and startHour
     * - Getting meetings by name, date and word in description
     * - Creates a new calendar and adds all the meetings from the previous one with a certain word in them */
    static void initializationAndGetTest(){
        // Creating empty calendar
        PersonalCalendar personalCalendar = PersonalCalendar();

        // Creating test strings to put in the array as name and desc of the meeting
        char* test_name = new char[20];
        char* test_description = new char[100];

        strcpy(test_name, "Appointment");
        strcpy(test_description, "Appointment with the doctor");

        // Creating sample meeting
        Meeting meeting = Meeting(test_name,
                                  test_description,
                                  MyDate(24, 10, 2022),
                                  MyHour(10, 15),
                                  MyHour(12, 15));

        delete[] test_name;
        delete[] test_description;

        // Adding the meeting to the array
        personalCalendar.addMeeting(meeting);


        // Creating second meeting and adding it
        Meeting m = Meeting((char*)"pin", (char*)"go now", MyDate(), MyHour(), MyHour());
        personalCalendar.addMeeting(m);

        // Adding 9 more meetings to make the array resize itself
        for (int i = 1; i <= 9; ++i) {
            meeting.setStartHour(MyHour(i, 0));
            meeting.setDate(MyDate(i, 2, 2022));
            personalCalendar.addMeeting(meeting);
        }

        // Printing the calendar
        personalCalendar.print();

        cout<< "------------------------------" << endl;

        cout << "Getting the meeting with name pin: " << endl;
        personalCalendar.getByName((char*)"pin").print();
        cout << endl;
        cout << "Getting the meeting with date 2022-02-04: " << endl;
        personalCalendar.getByDate(MyDate(4, 2, 2022)).print();
        cout << endl;
        cout << "Getting the first meeting containing the word \"with\" in it's description:" << endl;
        personalCalendar.getFirstByWordInDescription((char*)"with").print();

        cout << endl;
        cout << "Getting all words containing the word \"with\" in it's description and putting it into a calendar:" << endl;
        // Creating new personal calendar
        PersonalCalendar personalCalendar1 = PersonalCalendar();
        // Getting all the words and putting them in the personal calendar's array
        int cur = personalCalendar.getAllByWordInDescription(personalCalendar1.getMeetingList(), (char*)"with");
        // Setting the current element number
        personalCalendar1.setCurrent(cur);
        personalCalendar1.print();
    }
};

int main(){


}
