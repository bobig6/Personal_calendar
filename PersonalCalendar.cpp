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

    int getAllByDate(Meeting* newMeetingList, const MyDate& date){
        int j = 0;
        for (int i = 0; i < current; ++i) {
            if(meetingList[i].getDate() == date){
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

    /*! A function to save the class into a binary file*/
    void save(ofstream& file){
        // Saving the size of the array, so we can later read it
        file.write((char *)&current, sizeof(int));

        for (int i = 0; i < current; ++i) {
            meetingList[i].save(file);
        }
    }

    /*! A function to load the class from a binary file*/
    void load(ifstream& file){
        // Getting the size of the array first
        int new_current = 0;
        file.read((char *)&new_current, sizeof(int));
        current = new_current;
        Meeting* buffer = new Meeting[current+1];
        for (int i = 0; i < current; ++i) {
            buffer[i].load(file);
        }
        setMeetingList(buffer, current, current*2);
        delete [] buffer;
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

        int s = buffer.current;

        for (int i = 0; i < s; ++i) {
            min = buffer.getEarliestMeeting();
            if(min.getDate() == date){
                result.addMeeting(min);
            }
            buffer.removeMeeting(min);
        }

        return result;

    }

    void updateAllWithName(char* new_name, Meeting new_meeting){
        for (int i = 0; i < current; ++i) {
            if(strcmp(meetingList[i].getName(), new_name) == 0){
                meetingList[i].setMeeting(new_meeting.getName(), new_meeting.getDescription(), new_meeting.getDate(), new_meeting.getStartHour(), new_meeting.getEndHour());
            }
        }
    }

    void updateAllByDateAndHour(const MyDate& new_date, const MyHour& new_start, const Meeting& new_meeting){
        for (int i = 0; i < current; ++i) {
            if(meetingList[i].getDate() == new_date && meetingList[i].getStartHour() == new_start){
                meetingList[i].setMeeting(new_meeting.getName(), new_meeting.getDescription(), new_meeting.getDate(), new_meeting.getStartHour(), new_meeting.getEndHour());
            }
        }
    }

    /*! This function finds a free hour in a given time period and duration*/
    Meeting findFreeHour(MyDate s_date, const MyDate& e_date, const MyHour& s_hour, const MyHour& e_hour,const MyHour& duration){
        if(s_date > e_date || s_hour > e_hour) throw invalid_argument("The time range given to findFreeHour() is invalid");

        while (s_date <= e_date){
            // Creating a new personal calendar containing only the meetings from the current date sorted
            PersonalCalendar daily = getDailyProgram(s_date);

            // If the daily is empty that means the whole day is free, so we return the first free hour
            if(daily.current == 0){
                return Meeting((char*)"Free Hour",
                               (char*)"This meeting contains free hour",
                               s_date,
                               s_hour,
                               s_hour + duration
                );
            }

            // Removing all the meetings that aren't in the hours' interval specified
            for (int i = 0; i < daily.current; ++i) {
                if(daily.meetingList[i].getStartHour() < s_hour || daily.meetingList[i].getStartHour() > e_hour){
                    daily.removeMeeting(daily.meetingList[i]);
                }
            }

            // Getting the first meeting for the day
            Meeting previous = daily.meetingList[0];

            // Checking if there is a free hour between s_hour and first meeting
            if((previous.getStartHour() - s_hour) >= duration){
                return Meeting((char*)"Free Hour",
                               (char*)"This meeting contains free hour",
                               s_date,
                               s_hour,
                               s_hour + duration
                );
            }

            // Checking if there are free hours between meetings
            for (int i = 0; i < daily.current; ++i) {
                if((daily.getMeetingList()[i].getStartHour() - previous.getEndHour()) >= duration){
                    return Meeting((char*)"Free Hour",
                                   (char*)"This meeting contains free hour",
                                   s_date,
                                   previous.getEndHour(),
                                   previous.getEndHour() + duration
                                   );
                }
                previous = daily.getMeetingList()[i];
            }

            // Checking if there is a free hour between last meeting and e_hour
            if((e_hour - previous.getEndHour()) >= duration){
                return Meeting((char*)"Free Hour",
                               (char*)"This meeting contains free hour",
                               s_date,
                               previous.getEndHour(),
                               previous.getEndHour() + duration
                );
            }

            // If no free hour is found we go to the next date
            s_date.addDay();
        }

        return {(char *) "No free hour",
                (char *) "There is no free hour in this time period",
                MyDate(),
                MyHour(),
                MyHour()
        };
    }

    /*! A function to make a busyness statistic and save it to a .txt file
     *  The function accepts start and end date and in that interval sorts the day of the week
     *  depending on the busyness. In the text file the hours are written as floats where the number after the
     *  decimal point are the minutes*/
    void workloadStatistic(MyDate s_date, MyDate e_date){
        char* fileName = new char[25];
        strcpy(fileName, "stats-");
        strcat(fileName, s_date.getDateAsString());
        strcat(fileName, ".txt");

        // Every element is a day of the week 0-Sunday, 1-Monday... etc.
        float days_of_week_load[7];

        // Setting every value in the array to 0
        for (int i = 0; i < 7; ++i) {
            days_of_week_load[i] = 0;
        }

        // Checking if the date is valid
        if(s_date > e_date) throw invalid_argument("The time range given to workloadStatistic() is invalid");

        while (s_date <= e_date){
            // Creating a new personal calendar containing only the meetings from the current date sorted
            PersonalCalendar daily = getDailyProgram(s_date);

            // If the daily is empty that means the whole day is free, so we dont add anything
            if(daily.current == 0){
                s_date.addDay();
                continue;
            }

            // For every meeting we add the hours that are busy
            for (int i = 0; i < daily.current; ++i) {
                MyHour duration = daily.getMeetingList()[i].getEndHour() - daily.getMeetingList()[i].getStartHour();
                float durInNum = duration.getHours() + 0.01*duration.getMinutes();
                days_of_week_load[s_date.getDayOfWeek()] += durInNum;
            }

            // Go to the next date
            s_date.addDay();
        }

        // Opening the file to write the changes
        ofstream dateFile;

        dateFile.open (fileName);
        dateFile << "Workload statistic: days of week sorted by busyness\n";

        // Creating array with the numbers of the days of week
        int indexes[7];
        for (int i = 0; i < 7; ++i) {
            indexes[i] = i;
        }

        // Bubble sort for the two arrays at the same time
        // This is needed because we need the day of the weeks to be sorted not the values
        for(int i=0;i<7;i++){
            for(int j=0;j<6-i;j++){
                if(days_of_week_load[j]<days_of_week_load[j+1]){
                    // Swapping elements in both arrays
                    float temp=days_of_week_load[j+1];
                    days_of_week_load[j+1]=days_of_week_load[j];
                    days_of_week_load[j]=temp;

                    int temp2=indexes[j+1];
                    indexes[j+1]=indexes[j];
                    indexes[j]=temp2;
                }
            }
        }

        // Putting the data into the text file
        for (int i = 0; i < 7; ++i) {
            switch (indexes[i]) {
                case 0: dateFile << "Sunday: " << days_of_week_load[i] << " hours" <<endl; break;
                case 1: dateFile << "Monday: " << days_of_week_load[i] << " hours" <<endl; break;
                case 2: dateFile << "Tuesday: " << days_of_week_load[i] << " hours" <<endl; break;
                case 3: dateFile << "Wednesday: " << days_of_week_load[i] << " hours" <<endl; break;
                case 4: dateFile << "Thursday: " << days_of_week_load[i] << " hours" <<endl; break;
                case 5: dateFile << "Friday: " << days_of_week_load[i] << " hours" <<endl; break;
                case 6: dateFile << "Saturday: " << days_of_week_load[i] << " hours" <<endl; break;
            }
        }

        dateFile.close();
        delete [] fileName;
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

    /*! Test for adding and removing elements:
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

    /*! Test for getting the first meeting in a list and getting the program for a specific date*/
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

    /*! Test for save and load functionality
     *   - Creates a personal calendar and adds 3 meetings to it
     *   - Prints and saves the calendar
     *   - Loads the calendar into a new object and prints it */
    static void saveAndLoadTest(){
        cout << "#Saving personalCalendar to file and loading it to personalCalendar1:" << endl;
        ofstream file("PersonalCalendar.dat", ios::out | ios::binary);
        if(!file){
            throw invalid_argument("Couldn't open file");
        }

        cout << "#Adding 3 meetings and saving them: " << endl;
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

        personalCalendar.save(file);

        file.close();

        ifstream in("PersonalCalendar.dat", ios::in | ios::binary);
        if(!in){
            throw invalid_argument("Couldn't open file");
        }
        PersonalCalendar personalCalendar1 = PersonalCalendar();
        personalCalendar1.load(in);
        in.close();
        cout << "#Loads the saved calendar: -----------------------------------------------" << endl;
        personalCalendar1.print();
    }

    /*! Test for update methods:
     *   - Creates personal calendar and books 2 meetings to it
     *   - Updates all meetings with a certain name
     *   - Updates all meetings with a certain date and hour*/
    static void updateTest(){
        cout << "#Adding 2 meetings and then updating them: " << endl;
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
        personalCalendar.print();

        personalCalendar.updateAllWithName((char*) "Anime Convention 2",
                                           Meeting(
                                                   (char*) "Regular Convention 2",
                                                   (char*)"Going to regular convention",
                                                   MyDate(23, 10, 2022),
                                                   MyHour(12, 15),
                                                   MyHour(15, 15)
                                           )
        );

        personalCalendar.updateAllByDateAndHour(MyDate(22, 10, 2022),
                                                MyHour(12, 0),
                                                Meeting(
                                                        (char*) "Regular",
                                                        (char*)"Going to regular convention",
                                                        MyDate(23, 10, 2022),
                                                        MyHour(12, 15),
                                                        MyHour(15, 15)
                                                )
        );
        personalCalendar.print();
    }

    /*! Test for the freeHour function
     *  - Creates a personal calendar with 3 meetings
     *  - Runs the findFreeHour() with 3 different time periods */
    static void freeHourTest(){
        PersonalCalendar personalCalendar = PersonalCalendar();
        personalCalendar.bookMeeting((char*) "Anime Convention 1",
                                     (char*)"Going to anime convention",
                                     MyDate(23, 10, 2022),
                                     MyHour(9, 0),
                                     MyHour(12, 0)
        );
        personalCalendar.bookMeeting((char*) "Anime Convention 2",
                                     (char*)"Going to anime convention",
                                     MyDate(23, 10, 2022),
                                     MyHour(12, 0),
                                     MyHour(15, 0)
        );

        personalCalendar.bookMeeting((char*) "Anime Convention 3",
                                     (char*)"Going to anime convention",
                                     MyDate(23, 10, 2022),
                                     MyHour(17, 0),
                                     MyHour(20, 0)
        );
        personalCalendar.print();

        cout << "Trying to find a free hour for 2022-10-23, 9:00 - 20:00 with duration 2:00:" << endl;

        Meeting freeHour = personalCalendar.findFreeHour(MyDate(23, 10, 2022),
                                                         MyDate(23, 10, 2022),
                                                         MyHour(9, 0),
                                                         MyHour(20, 0),
                                                         MyHour(2, 0));

        freeHour.print();
        cout<< endl << "Trying to find a free hour for 2022-10-23, 8:00 - 16:00 with duration 2:00:" << endl;

        Meeting freeHour2 = personalCalendar.findFreeHour(MyDate(23, 10, 2022),
                                                          MyDate(23, 10, 2022),
                                                          MyHour(8, 0),
                                                          MyHour(16, 0),
                                                          MyHour(2, 0));
        freeHour2.print();

        cout<< endl << "Trying to find a free hour for 2022-10-22 - 2022-10-23, 8:00 - 16:00 with duration 2:00:" << endl;

        Meeting freeHour3 = personalCalendar.findFreeHour(MyDate(22, 10, 2022),
                                                          MyDate(23, 10, 2022),
                                                          MyHour(8, 0),
                                                          MyHour(16, 0),
                                                          MyHour(2, 0));
        freeHour3.print();
    }

    /*! This function tests the workloadStatistic():
     *  - Creates personal calendar with 3 meetings
     *  - Runs the workloadStatistic() function*/
    static void workloadStatisticTest(){
        PersonalCalendar personalCalendar = PersonalCalendar();
        personalCalendar.bookMeeting((char*) "Anime Convention 1",
                                     (char*)"Going to anime convention",
                                     MyDate(22, 10, 2022),
                                     MyHour(9, 0),
                                     MyHour(15, 0)
        );
        personalCalendar.bookMeeting((char*) "Anime Convention 2",
                                     (char*)"Going to anime convention",
                                     MyDate(23, 10, 2022),
                                     MyHour(12, 0),
                                     MyHour(15, 0)
        );

        personalCalendar.bookMeeting((char*) "Anime Convention 3",
                                     (char*)"Going to anime convention",
                                     MyDate(24, 10, 2022),
                                     MyHour(17, 0),
                                     MyHour(20, 0)
        );

        personalCalendar.bookMeeting((char*) "Anime Convention 1",
                                     (char*)"Going to anime convention",
                                     MyDate(25, 10, 2022),
                                     MyHour(9, 16),
                                     MyHour(16, 0)
        );

        personalCalendar.print();

        personalCalendar.workloadStatistic(MyDate(22, 10, 2022), MyDate(25, 10, 2022));

    }

};


int main(){

}
