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

    int getAllByWordInName(Meeting* newMeetingList, char* word){
        int j = 0;
        for (int i = 0; i < current; ++i) {
            if(strstr(meetingList[i].getName(), word) != NULL){
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

    //! Returns the earliest meeting found in the calendar
    Meeting getEarliestMeeting(){
        // If the array is empty throws exception
        if(current <= 0) throw std::invalid_argument( "Meeting list is empty so minimal date cannot be found" );
        // Sets the first element as minimal
        Meeting* min = &meetingList[0];
        // Goes through all elements and if it finds an element that is smaller it sets it as a minimal
        for (int i = 0; i < current; ++i) {
            if(meetingList[i] < *min) min = &meetingList[i];
        }
        return *min;
    }

    // SECTION: HELPER FUNCTIONS----------------------------------------------------------

    //! A function to add a new meeting to the meeting list. Resizes the list if necessary
    void addMeeting(const Meeting& meeting){
        if(current >= size) resizeMeetingList();
        meetingList[current] = meeting;
        current++;
    }

    //! This function removes given element from the array
    bool removeMeeting(const Meeting& meeting){
        // Going through the whole array
        for (int i = 0; i < current; i++)
        {

            // Checking if the elements match
            if (meetingList[i] == meeting)
            {
                // Going through remaining elements
                for ( ; i < current - 1; i++)
                {
                    // Assign the next element to current location.
                    meetingList[i] = meetingList[i + 1];
                }

                // Remove the last element as it has been moved to previous index.
                meetingList[current - 1] = Meeting();
                current = current - 1;
                return true;
            }
        }
            return false;
    }


    //! A function to print the class
    void print(){
        cout << "Personal calendar: " << endl << endl;
        for (int i = 0; i < current; ++i) {
            meetingList[i].print();
            cout << endl;
        }
    }


    // SECTION: BUSINESS LOGIC------------------------------------------------

    //! Books a meeting with given name, description, date, startHour and endHour
    void bookMeeting(char* new_name, char* new_description, const MyDate& new_date, const MyHour& new_start, const MyHour& new_end){
        addMeeting(Meeting(new_name, new_description, new_date, new_start, new_end));
    }

    //! Removes the first meeting that it finds with the given name
    void removeMeetingByName(char* name){
        removeMeeting(getByName(name));
    }

    //! Removes the first meeting that it finds on a given date
    void removeMeetingByDate(MyDate date){
        removeMeeting(getByDate(date));
    }

    //! Removes the first meeting that it finds which has a certain word in it's description
    void removeMeetingByFirstMatchInDescription(char* word){
        removeMeeting(getFirstByWordInDescription(word));
    }

    //! Removes all meetings that have a certain word in their description
    void removeAllMeetingsWithWordInDescription(char* word){
        Meeting* buffer = new Meeting[current];
        int buff_size = getAllByWordInDescription(buffer, word);
        for (int i = 0; i < buff_size; ++i) {
            removeMeeting(buffer[i]);
        }
        delete [] buffer;
    }

    PersonalCalendar getDailyProgram(const MyDate& date){
        PersonalCalendar buffer = PersonalCalendar(*this);
        PersonalCalendar result = PersonalCalendar();

        Meeting min;

        for (int i = 0; i < buffer.current; ++i) {
            min = buffer.getEarliestMeeting();
            if(min.getDate() == date){
                result.addMeeting(min);
            }
            buffer.removeMeeting(min);
        }

        return result;

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
        cout << "------------------------------------------------" << endl;
        cout << "Getting all meetings which name contains Appointment" << endl;

        // Creating new personal calendar
        PersonalCalendar personalCalendar2 = PersonalCalendar();
        // Getting all the words and putting them in the personal calendar's array
        int p2_size = personalCalendar.getAllByWordInName(personalCalendar2.getMeetingList(), (char*)"Appointment");
        // Setting the current element number
        personalCalendar2.setCurrent(p2_size);
        personalCalendar2.print();

        cout << "------------------------------------------------" << endl;
        cout << "Getting the meeting with date 2022-02-04: " << endl;
        personalCalendar.getByDate(MyDate(4, 2, 2022)).print();
        cout << "------------------------------------------------" << endl;
        cout << "Getting the first meeting containing the word \"with\" in it's description:" << endl;
        personalCalendar.getFirstByWordInDescription((char*)"with").print();

        cout << "------------------------------------------------" << endl;
        cout << "Getting all meetings containing the word \"with\" in it's description and putting it into a calendar:" << endl;
        // Creating new personal calendar
        PersonalCalendar personalCalendar1 = PersonalCalendar();
        // Getting all the words and putting them in the personal calendar's array
        int cur = personalCalendar.getAllByWordInDescription(personalCalendar1.getMeetingList(), (char*)"with");
        // Setting the current element number
        personalCalendar1.setCurrent(cur);
        personalCalendar1.print();
    }

    //*! Test for adding and removing elements:
    //     - Creating personal calendar and two meetings: meeting1 and meeting2
    //     - Adding meeting1 and meeting2
    //     - Removing meeting1 and print
    //     - Removing meeting2 and print
    //     - Booking new meeting and adding meeting2 with different date
    //     - Remove meeting2 by date
    //     - Booking 2 more new meetings with same descriptions
    //     - Removing the first match by word in description
    //     - Adding meeting2 and removing all meetings with a match in description */
    static void addingAndRemovingElementsTest(){
        cout << "#Creating personal calendar and adding meeting1 and meeting2 to it: " << endl;
        PersonalCalendar personalCalendar = PersonalCalendar();
        Meeting meeting1 = Meeting();
        Meeting meeting2 = Meeting();
        meeting1.setName((char*)"meeting1");
        meeting2.setName((char*)"meeting2");

        personalCalendar.addMeeting(meeting1);
        personalCalendar.addMeeting(meeting2);

        personalCalendar.print();

        cout << "#Removing meeting1: " << endl;
        personalCalendar.removeMeetingByName((char*)"meeting1");
        personalCalendar.print();

        cout << "#Removing meeting2: " << endl;
        personalCalendar.removeMeetingByName((char*)"meeting2");
        personalCalendar.print();

        cout << "#Adding and changing meeting2 date to 2022-12-12" << endl;
        meeting2.setDate(MyDate(12, 12, 2022));
        personalCalendar.addMeeting(meeting2);
        cout << "#Book a new meeting by name, description, date, startHour and endHour" << endl;
        personalCalendar.bookMeeting((char*) "Anime Convention",
                                     (char*)"Going to anime convention",
                                     MyDate(21, 10, 2022),
                                     MyHour(12, 0),
                                     MyHour(15, 0)
                                     );
        personalCalendar.print();

        cout << "#Removing meeting2 by date: " << endl;
        personalCalendar.removeMeetingByDate(MyDate(12, 12, 2022));
        personalCalendar.print();

        cout << "#Adding 2 more meetings with word anime in description" << endl;
        personalCalendar.bookMeeting((char*) "Anime Convention 2",
                                     (char*)"Going to anime convention",
                                     MyDate(22, 10, 2022),
                                     MyHour(12, 0),
                                     MyHour(15, 0)
        );
        personalCalendar.bookMeeting((char*) "Anime Convention 3",
                                     (char*)"Going to anime convention",
                                     MyDate(23, 10, 2022),
                                     MyHour(12, 0),
                                     MyHour(15, 0)
        );
        personalCalendar.print();

        cout << "#Removing first meeting that contains word anime: " << endl;
        personalCalendar.removeMeetingByFirstMatchInDescription((char*)"anime");
        personalCalendar.print();

        cout << "#Adding meeting2 and removing all other meetings that contain word anime" << endl;
        personalCalendar.addMeeting(meeting2);
        personalCalendar.removeAllMeetingsWithWordInDescription((char*)"anime");
        personalCalendar.print();
    }

    //*! Test for getting the first meeting in a list and getting the program for a specific date*/
    static void getDailyProgramTest(){
        cout << "#Adding 3 meetings and returning the earliest of them: " << endl;
        PersonalCalendar personalCalendar = PersonalCalendar();
        personalCalendar.bookMeeting((char*) "Anime Convention 2",
                                     (char*)"Going to anime convention",
                                     MyDate(23, 10, 2022),
                                     MyHour(12, 0),
                                     MyHour(15, 0)
        );
        personalCalendar.bookMeeting((char*) "Anime Convention 3",
                                     (char*)"Going to anime convention",
                                     MyDate(22, 10, 2022),
                                     MyHour(12, 0),
                                     MyHour(15, 0)
        );

        personalCalendar.bookMeeting((char*) "Anime Convention 4",
                                     (char*)"Going to anime convention",
                                     MyDate(22, 10, 2022),
                                     MyHour(10, 0),
                                     MyHour(15, 0)
        );
        personalCalendar.print();
        cout << "#The earliest meeting is: " << endl;
        personalCalendar.getEarliestMeeting().print();

        cout << "#Adding 3 meetings and returning the daily program for 2022-10-22: " << endl;


        cout << "#Calendar for 2022-10-22" << endl;
        PersonalCalendar calendarForTheDay = personalCalendar.getDailyProgram(MyDate(22, 10, 2022));
        calendarForTheDay.print();
    }
};

int main(){
    cout << "Saving meeting1 to file and loading it to meeting2:" << endl;
    ofstream file("Meeting.dat", ios::out | ios::binary);
    if(!file){
        throw invalid_argument("Couldn't open file");
    }
    Meeting m = Meeting((char*)"pin", (char*)"go now", MyDate(12, 10, 2021), MyHour(14, 20), MyHour(13, 2));
    m.save(file);
    file.close();

    ifstream in("Meeting.dat", ios::in | ios::binary);
    if(!in){
        throw invalid_argument("Couldn't open file");
    }
    Meeting meeting2 = Meeting();
    meeting2.load(in);
    in.close();
    meeting2.print();
}
