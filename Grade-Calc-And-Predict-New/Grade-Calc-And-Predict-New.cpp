    /***************************************************************************/
   /*  Grade Calculator and Predictor Program! - By: Tom Stephens (30048598)  */
  /***************************************************************************/
 /*           University Assessment 3 - University of South Wales.          */
/***************************************************************************/

/*****************************************************************************************************************************************************************************************\
|    Client Brief 1: Grade Calculator and predictor for C++ Programming Module.                                                                                                           |
|    Write a simple application that can store multiple students’ names, student number& email address.                                                                                   |
|	 The application will store grades for the moduleand be able to predict the overall mark.The application should be able to:                                                           |
|        • Add a new student with their name, student number& email address.                                                                                                              |
|        • List the student’s names& student numbers with current total mark.                                                                                                             |
|        • Input marks for assignments, or update existing marks already in the application                                                                                               |
|        • Show the students marks for all 4 C++ assignments                                                                                                                              |
|        • Grade predictor : enter test grades into the 4 assignments to see what the overall mark is.                                                                                    |
|        • Show a list of all students in grade order, highest to lowest                                                                                                                  |
|        • Save data to a file                                                                                                                                                            |
|        • Read data from a file                                                                                                                                                          |
|        • Once marks for the first 3 assignments are in, the application will be able to tell the user the mark the student needs in the final assignment to achieve 70 % all together.  |
|    Data can be stored in a file called “studentmarks.txt”                                                                                                                               |
|    C++ programing is scored out of 100 % overall.                                                                                                                                       |
|        • Tutorial Exercises 1 is worth 10 % of the overall mark                                                                                                                         |
|        • Tutorial Exercises 2 is worth 20 % of the overall mark                                                                                                                         |
|        • Practical Coursework 3 is worth 30 % of the overall mark                                                                                                                       |
|        • Practical Coursework 4 is worth 40 % of the overall mark                                                                                                                       |
\*****************************************************************************************************************************************************************************************/

#include <iostream>
#include <algorithm>   //Only used once for 'std::all_of' in the validation functions.
#include <fstream>
#include <chrono>   // <---
#include <thread>   //  ^^^Not using for threading, just for sleep function.
#include <iomanip>
#include <sstream>
#include <ctime>    // <---
#include <time.h>   //  ^^^Both used for getting and formatting time and date.
#include <string>
#include <vector>

//Constant variables for 'FILE' stuff like name and the spacing between each data.
const std::string DEFAULT_FILE_NAME = "studentInfomation.txt";
const char DEFAULT_FILE_SPACING = '|';

//Defines and constant variables for the grades defults.
#define GRADES_AMMOUNT 4
const int gradePercent[GRADES_AMMOUNT] = { 10, 20, 30, 40 };
#define PREDICT_GRADE_FOR 70   //Define which sets the overall percent which the program will predict for.

//Defines for input validation,
#define MINIMUM_ENTERED_SIZE 2
#define STUDENT_NUM_SIZE 8

//Define for the defult email ending.
#define DEFAULT_EMAIL_END "@students.southwales.ac.uk"

//Class called 'Students' holds all the infomation about a student and each object will represent a induvidual student.
class Students
{
private:
	//Main variables to hold the students data within each object.
	std::string studentName;
	std::string studentNum;
	std::string studentEmail;
	int grades[GRADES_AMMOUNT];
	double overallMark = 0;
	std::string gradeHonours;
	std::string timeAdded;
	std::string dateAdded;
	double gradePrediction = 0;

	//Update functions which get ran by the constructors.
	void updateTime();
	void updateOverallMark();
	void updateGradeHonours();
	void generateEmail();
public:
	Students(int*, std::string, std::string);   //Defult constuctor used for adding a 'NEW' student.

	//Other constuctor used for adding existing students from file or updating an existing students.
	Students(std::string, std::string, double, std::string, double, int*, std::string, std::string, std::string);

	//Getters.
	std::string getStudentName();
	std::string getStudentNum();
	std::string getStudentEmail();
	int* getGradesPtr();
	double getOverallMark();
	std::string getGradeHonours();
	std::string getTimeAdded();
	std::string getDateAdded();
	double getGradePrediction();
};

//Class called 'FileInputOutput' which holds everything to do with inputing and output the files.
class FileInputOutput
{
private:
	std::ifstream inFile;
	std::ofstream outFile;

	std::string tempStudentName;
	std::string tempStudentNum;
	std::string tempStudentEmail;
	int* tempGrades = new int[GRADES_AMMOUNT];
	double tempOverallMark = 0;
	std::string tempGradeHonours;
	std::string tempTimeAdded;
	std::string tempDateAdded;
	double tempGradePrediction = 0;
public:
	FileInputOutput();
	~FileInputOutput();

	bool inputFile(std::vector<Students>&, std::string, char);
	bool outputFile(std::vector<Students>&, std::string, char);
	bool outputLogFile(std::string, const std::string&, const std::string&, std::string, std::string, const unsigned long int&);
};

//Class called 'Logger' which inherites the functions from 'FileInputOutput' class. Has functions to log different types of situations, like error, start, data change, etc.
class Logger : public FileInputOutput
{
private:
	const std::string DEFAULT_LOG_FILE_NAME = "gradeCalcLog.txt";
	std::string logMessage;
	std::string timeOfLog;
	std::string dateOfLog;
	unsigned long int counter;
public:
	Logger();   //Logger constructor.

	//Functions for different log errors.
	bool logError(const std::string&);
	bool logDataChange(const std::string&, std::string, std::string);
	bool logProgramStart();
	bool logProgramEnd();
	bool logFileInput(const std::string&, std::string);
	bool logFileOutput(const std::string&, std::string);
	void updateTimeDate();
};

//Class called 'MainFunctions' holds everything to do with the main program.
class MainFunctions
{
private:
	std::vector<Students> students;   //Vector of 'Students' class objects.
	bool fileDetected = false;
	int menuIndex = 0;
	size_t searchInListIndex = -1;

    std::string tempStudentName;
	std::string tempStudentNum;
	int* tempGrades = new int[GRADES_AMMOUNT];

	FileInputOutput inOutFile;
	Logger logger;

	void initProgram();
	void printMenu();
	void addStudent();
	void sortStudentsMenu();
	void saveFileMenu();
	void inputFileMenu();
	void exitMenu();
	void findStudentInList();
	bool sortStudents(std::vector<Students>&, bool);
	int findStudent(std::vector<Students>&, std::string);
	void updateStudentInfo();
	void listStudents(std::vector<Students>&);
	void listStudentsGrades(std::vector<Students>&);
	int findStudentNum(std::string&, std::vector<Students>&);

	std::string inputStudentName();
	std::string inputStudentNum();
	int* inputGradesPtr();
public:
	MainFunctions();
	~MainFunctions();
};

struct tm currentDateTime();
std::string getFormattedTime24(const std::string&);
std::string getFormattedDate(const std::string&);
std::string formatNum(int, int, char);
bool isFullNumber(std::string&);
bool isCharInside(char, std::string&);
bool isNumberInside(std::string&);
bool isCharAtIndex(char, int, std::string&);
std::string arrayToString(int*, const int&, const char);

int main()
{
	MainFunctions main;   //Creates a 'MainFunctions' object called 'main' to initiate the program.
}

  /**********************************************************/
 /*  Functions that are within the 'MainFunctions' class.  */
/**********************************************************/

//MainFunctions constuctor and deconstuctor.
MainFunctions::MainFunctions()
{
	initProgram();
}

MainFunctions::~MainFunctions()
{
	students.clear();
	delete[]tempGrades;
}

//initProgram function within the 'MainFunctions' class, is the first function that will run when this program is started. 
void MainFunctions::initProgram()
{
	this->logger.logProgramStart();
	this->fileDetected = this->inOutFile.inputFile(this->students, DEFAULT_FILE_NAME, DEFAULT_FILE_SPACING);   //Trys to input the data from the file at the begining of the program.
	this->logger.logFileInput("Attemted file input", DEFAULT_FILE_NAME);
	printMenu();
}

//printMenu function within the 'MainFunctions' class, prints the main menu of the program and calls all the functions needed from it.
void MainFunctions::printMenu()
{
	while (1)
	{
		std::cout << "\033[36m\033[4m\033[1m\033[5mStudent Grade Calculator (By: Tom Stephens - 30048598)!\033[0m\n\n"
			<< "\033[36m\033[3m\033[1m* \033[0m\033[1mFile input was "
			<< ((this->fileDetected == true) ? "successful! " + std::to_string(this->students.size()) + " Students Data!\033[0m\n\n" : "not successful!\033[0m\n\n")   //Will say if file input was successful and ammount of students data in program.
			<< "\033[36m\033[3m\033[1m1 - \033[0m\033[1mAdd Student.\033[0m\n"
			<< "\033[36m\033[3m\033[1m2 - \033[0m\033[1mList Student Grades.\033[0m\n"
			<< "\033[36m\033[3m\033[1m3 - \033[0m\033[1mList All Student Data.\033[0m\n"
			<< "\033[36m\033[3m\033[1m4 - \033[0m\033[1mSearch for student.\033[0m\n"
			<< "\033[36m\033[3m\033[1m5 - \033[0m\033[1mEdit Student.\033[0m\n"
			<< "\033[36m\033[3m\033[1m6 - \033[0m\033[1mSort Students.\033[0m\n"
			<< "\033[36m\033[3m\033[1m7 - \033[0m\033[1mSave Data to file.\033[0m\n"
			<< "\033[36m\033[3m\033[1m8 - \033[0m\033[1mInput Data from file.\033[0m\n"
			<< "\033[36m\033[3m\033[1m0 - \033[0m\033[1mExit the program.\033[0m\n"
			<< "\033[36m\033[3m\033[1m\nPlease enter a number:\033[0m\n";

		bool correct = false;
		do
		{
			std::cin >> this->menuIndex;
			if (!std::cin.fail() && this->menuIndex >= 0 && this->menuIndex <= 8)
			{
				correct = true;
			}
			else if (!correct)
			{
				correct = false;
				std::cerr << "\033[31m\033[3mINVALID INPUT ENTERED!\033[0m\n";
				this->logger.logError("Invalid input entered at menu selection");
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		} while (!correct);

		//Switch statment for the main menu will call the different functions from within each case.
		switch (menuIndex)
		{
		case 0:
			system("cls");   //Clears console screen.
			exitMenu();
			break;
		case 1:
			system("cls");   //Clears console screen.
			addStudent();
			break;
		case 2:
			system("cls");   //Clears console screen.
			listStudentsGrades(this->students);
			break;
		case 3:
			system("cls");   //Clears console screen.
			listStudents(this->students);
			break;
		case 4:
			system("cls");
			findStudentInList();
			break;
		case 5:
			system("cls");   //Clears console screen.
			updateStudentInfo();
			break;
		case 6:
			system("cls");   //Clears console screen.
			sortStudentsMenu();
			break;
		case 7:
			system("cls");   //Clears console screen.
			saveFileMenu();
			break;
		case 8:
			system("cls");   //Clears console screen.
			inputFileMenu();
			break;
		}
		system("cls");   //Clears console screen.
	}
}

//exitMenu function within the 'MainFunctions' class, which create a user interface to ask the users if they would like to save the student data before they exit.
void MainFunctions::exitMenu()
{
	char saveData;
	std::cout << "\033[36m\033[1mExit Student Grade Calculator\033[0m\n" << "\n\033[36m\033[3m\033[1m* \033[0m\033[1mWould you like to save the student data? Enter 'y' or 'n'.\033[0m\n";
	do
	{
		std::cin >> saveData;
	} while (std::toupper(saveData) != 'Y' && std::toupper(saveData) != 'N');

	if (std::toupper(saveData) == 'Y')
	{
		bool succesful = this->inOutFile.outputFile(this->students, DEFAULT_FILE_NAME, DEFAULT_FILE_SPACING);   //Outputs a file with all the data when the program ends.
		this->logger.logFileOutput("Attempted file output", DEFAULT_FILE_NAME);
		if (succesful)
		{
			std::cout << "\033[36m\033\n[1m* Saved file succesfully (Called: " << DEFAULT_FILE_NAME << ") will exit in 3 seconds.\033[0m\n";
		}
		else if (!succesful)
		{
			std::cerr << "\033[31m\033[3mERROR SAVING FILE!\033[0m\n";
			logger.logError("Error saving file in exit menu");
		}

		std::this_thread::sleep_for(std::chrono::seconds(3));   //Sleeps the program for 3 seconds.
		this->logger.logProgramEnd();
		exit(0);
	}
	else if (std::toupper(saveData) == 'N') {
		this->logger.logProgramEnd();
		exit(0);
	}
}

//sortStudentsMenu function within the 'MainFunctions' class, which create a user interface to ask the users if they would like to sort into accending or decending order.
void MainFunctions::sortStudentsMenu()
{
	char sortOrder;
	std::cout << "\033[36m\033[1mWould you like to sort in 'accending order' or 'decending order'.\033[0m\n" << "\033[36m\033[3m\033[1m* \033[0m\033[1mType 'A' for accending and 'd' decending order!\033[0m\n";
	do
	{
		std::cin >> sortOrder;
	} while (std::toupper(sortOrder) != 'A' && std::toupper(sortOrder) != 'D');

	bool succesful = sortStudents(this->students, (std::toupper(sortOrder) == 'A') ? true : false);
	if (succesful == true)
	{
		std::cout << "\033[36m\033\n[1m* Sorted the students into " << (sortOrder ? "accending order" : "decending order") << ".\033[0m\n";
		this->logger.logDataChange((sortOrder ? "Attempted to sort data into accending" : "Attempted to sort data into deaccending"), "Unsorted", "Sorted");
	}
	else
	{
		std::cerr << "\033[31m\033[3mFAILED TO SORT STUDENTS!\033[0m\n";
		this->logger.logError("Failed to sort students");
	}

	std::this_thread::sleep_for(std::chrono::seconds(3));   //Sleeps the program for 3 seconds.
}

//saveFileMenu function within the 'MainFunctions' class, which create a user interface to ask the user name of the file and the file spacing for the file they would like to save.
void MainFunctions::saveFileMenu()
{
	std::string fileName;
	char fileSpacing;

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "\033[36m\033[1mSave Student Infomation!\033[0m\n" << "\n\033[36m\033[3m\033[1m1 - \033[0m\033[1mFile Name (E.g. studentmarks):\033[0m\n";
	std::getline(std::cin, fileName);

	std::cout << "\n\033[36m\033[3m\033[1m1 - \033[0m\033[1mFile Spacing (E.g. '|'):\033[0m\n";
	std::cin.get(fileSpacing);

	fileName.insert(fileName.size(), ".txt");

	bool succesful = this->inOutFile.outputFile(this->students, fileName, fileSpacing);
	this->logger.logFileOutput("Attempted file output", DEFAULT_FILE_NAME);
	if (succesful)
	{
		std::cout << "\033[36m\033\n[1m* Saved file succesfully (Called: " << fileName << ").\033[0m\n";
	}
	else if (!succesful)
	{
		std::cerr << "\033[31m\033[3mERROR SAVING FILE!\033[0m\n";
		logger.logError("Error saving file in save file menu");
	}

	std::this_thread::sleep_for(std::chrono::seconds(3));   //Sleeps the program for 3 seconds.
}

//inputFileMenu function within the 'MainFunctions' class, which create a user interface to ask the user the name of the file and file spacing that they would like to input.
void MainFunctions::inputFileMenu()
{
	std::string fileName;
	char fileSpacing;

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "\033[36m\033[1mInput Student Infomation!\033[0m\n" << "\n\033[36m\033[3m\033[1m1 - \033[0m\033[1mFile Name (E.g. studentmarks):\033[0m\n";
	std::getline(std::cin, fileName);

	std::cout << "\n\033[36m\033[3m\033[1m1 - \033[0m\033[1mFile Spacing (E.g. '|'):\033[0m\n";
	std::cin.get(fileSpacing);

	students.clear();
	fileName.insert(fileName.size(), ".txt");

	bool succesful = this->inOutFile.inputFile(this->students, fileName, fileSpacing);
	this->logger.logFileInput("Attempted file input", fileName);
	if (succesful)
	{
		std::cout << "\033[36m\033\n[1m* Inputted file succesfully (Called: " << fileName << ").\033[0m\n";
	}
	else if (!succesful)
	{
		std::cerr << "\033[31m\033[3mERROR INPUTING FILE!\033[0m\n";
		this->logger.logError("Failed to input file in input file menu");
	}

	std::this_thread::sleep_for(std::chrono::seconds(3));   //Sleeps the program for 3 seconds.
}

//addStudent function within the 'MainFunctions' class, will add a student to the 'Students' vector and calls the functions to get each input.
void MainFunctions::addStudent()
{
	char addAnother;
	do
	{
		std::cout << "\033[36m\033[1mAdd Student Infomation!\033[0m\n";

		Students temp(inputGradesPtr(), inputStudentNum(), inputStudentName());   //Creates a tempuary object and calls the functions from within to input the data for the student.
		this->students.push_back(temp);   //Pushes the tempuary object to the back of the vector.

		std::cout << "\033[36m\033[3m\033[1m\nWould you like to add another (E.g. 'y' or 'n'):\033[0m\n";
		do
		{
			std::cin >> addAnother;
		} while (std::toupper(addAnother) != 'Y' && std::toupper(addAnother) != 'N');
		system("cls");
	} while (std::toupper(addAnother) == 'Y');
}

//inputStudentName function within the 'MainFunctions' class, which gets the entered name and validates the input to check if there no numbers and it has a space. Returns name as string.
std::string MainFunctions::inputStudentName()
{
	bool correct = false;
	std::cout << "\n\033[36m\033[3m\033[1m1 - \033[0m\033[1mStudent Name (E.g. First Name Last Name):\033[0m\n";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	do
	{
		correct = false;
		std::getline(std::cin, this->tempStudentName);
		if (!isCharAtIndex(' ', this->tempStudentName.size() - 1, this->tempStudentName) && !isNumberInside(this->tempStudentName) && this->tempStudentName.size() > MINIMUM_ENTERED_SIZE && isCharInside(' ', this->tempStudentName))
		{
			correct = true;
		}
		else if (!correct) {
			correct = false;
			std::cerr << "\033[31m\033[3mINVALID INPUT ENTERED!\033[0m\n";
			this->logger.logError("Invailid input entered when entering student name");
		}
	} while (!correct);
	return this->tempStudentName;
}

//inputStudentNum function within the 'MainFunctions' class, which gets the entered student number and validates it by checking if it is a number and lengh is 8. Returns number as string.
std::string MainFunctions::inputStudentNum()
{
	bool correct = false;
	std::cout << "\n\033[36m\033[3m\033[1m2 - \033[0m\033[1mStudent " << STUDENT_NUM_SIZE << "-Digit Number (E.g. 10057890) :\033[0m\n";
	do
	{
		correct = false;
		std::cin >> this->tempStudentNum;
		if (isFullNumber(this->tempStudentNum) && findStudentNum(this->tempStudentNum, this->students) == -1 && this->tempStudentNum.size() == STUDENT_NUM_SIZE)
		{
			correct = true;
		}
		else if (!correct)
		{
			correct = false;
			std::cerr << "\033[31m\033[3mINVALID INPUT ENTERED!\033[0m\n";
			this->logger.logError("Invailid input entered when entering student number");
		}
	} while (!correct);
	return this->tempStudentNum;
}

//inputGradesPtr function within the 'MainFunctions' class, gets the entered grades, validates the input by making sure it is number and between 0 and 100. Returns a pointer to the first grade.
int* MainFunctions::inputGradesPtr()
{
	bool correct = false;
	for (short unsigned int i = 0; i < GRADES_AMMOUNT; i++)
	{
		if (i == 3)
		{
			char predict;
			//Asks the user if they would like to predict the grade for grade three. If so sets the grade to '-1'.
			std::cout << "\n\033[36m\033[1mWould you like to predict the grade for assessment 4 (E.g. 'y' or 'n'):\033[0m\n";

			do
			{
				std::cin >> predict;
			} while (std::toupper(predict) != 'Y' && std::toupper(predict) != 'N');

			if (std::toupper(predict) == 'Y')
			{
				*(tempGrades + i) = -1;
				return &tempGrades[0];
			}
		}

		std::cout << "\n\033[36m\033[3m\033[1m4." << i + 1 << " - \033[0m\033[1mStudent Grade (E.g. 78):\033[0m\n";
		do
		{
			correct = false;
			std::cin >> *(this->tempGrades + i);

			if ((!std::cin.fail() && *(this->tempGrades + i) >= 0 && *(this->tempGrades + i) <= 100) || *(this->tempGrades + i) == -1)
			{
				correct = true;
			}
			else if (!correct)
			{
				correct = false;
				std::cerr << "\033[31m\033[3mINVALID INPUT ENTERED!\033[0m\n";
				this->logger.logError("Invailid input entered when entering student grades");
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		} while (!correct);
	}
	return &this->tempGrades[0];
}

//findStudentInList function within the 'MainFunctions' class, allows user to find a student via the name or number and will highlight it in the list's menu.
void MainFunctions::findStudentInList() 
{
	std::string temp;
	bool correct = false;

	//Header for the user interface and input validation for the entered name or number.
	std::cout << "\033[36m\033[1mSearch for student in list!\033[0m\n\n"
		<< "\033[36m\033[3m\033[1m* - \033[0m\033[1mEnter Student Name or Student Number (E.g. 'First Name Last Name' or '10057890'):\033[0m\n";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	do
	{
		correct = false;
		std::getline(std::cin, temp);
		if (isFullNumber(temp) && temp.size() == STUDENT_NUM_SIZE || !isNumberInside(temp) && isCharInside(' ', temp) && temp.size() > MINIMUM_ENTERED_SIZE)
		{
			correct = true;
		}
		else if (!correct)
		{
			correct = false;
			std::cerr << "\033[31m\033[3mINVALID INPUT ENTERED!\033[0m\n";
			this->logger.logError("Invalid input entered in search for student menu");
		}
	} while (!correct);

	//Either uses a serch function for the name or a serch function for number and both will return the index were it was locatted.
	this->searchInListIndex = (isFullNumber(temp)) ? findStudentNum(temp, this->students) : (!isNumberInside(temp) && isCharInside(' ', temp)) ? findStudent(this->students, temp) : -1;

	if (this->searchInListIndex != -1) 
	{
		std::cout << "\n\033[36m\033[3m\033[1m* - \033[0m\033[1mFound student at line " << this->searchInListIndex + 1 << "!\033[0m\n" << "\n\033[36m\033[1m* - Student will be highlighted in the list's menu!\033[0m\n";
		std::this_thread::sleep_for(std::chrono::seconds(3));   //Sleeps the program for 3 seconds.
	}
	else if (this->searchInListIndex == -1) 
	{
		std::cerr << "\033[31m\033[3m\nFAILED TO FIND STUDENT!\033[0m\n";
		this->logger.logError("Failed to find student in search for student menu");
		std::this_thread::sleep_for(std::chrono::seconds(3));   //Sleeps the program for 3 seconds.
	}
}

//updateStudentInfo function within the 'MainFunctions' class, will create a user interface and ask the user to enter the student number or email that they would like to find.
// If student is found will then ask them what piece of data they would like to update and then gets the entered infomation and updates the student.
void MainFunctions::updateStudentInfo()
{
	std::string temp;
	bool correct = false;
	int studentIndex = -1;

	//Header for the user interface and input validation for the entered name or number.
	std::cout << "\033[36m\033[1mUpdate Student Infomation!\033[0m\n\n"
		<< "\033[36m\033[3m\033[1m* - \033[0m\033[1mEnter Student Name or Student Number (E.g. 'First Name Last Name' or '10057890'):\033[0m\n";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	do
	{
		correct = false;
		std::getline(std::cin, temp);
		if (isFullNumber(temp) && temp.size() == STUDENT_NUM_SIZE || !isNumberInside(temp) && isCharInside(' ', temp) && temp.size() > MINIMUM_ENTERED_SIZE)
		{
			correct = true;
		}
		else if (!correct)
		{
			correct = false;
			std::cerr << "\033[31m\033[3mINVALID INPUT ENTERED!\033[0m\n";
			this->logger.logError("Invalid input entered in update menu");
		}
	} while (!correct);

	//Either uses a serch function for the name or a serch function for number and both will return the index were it was locatted.
	studentIndex = (isFullNumber(temp)) ? findStudentNum(temp, this->students) : (!isNumberInside(temp) && isCharInside(' ', temp)) ? findStudent(this->students, temp) : -1;

	//Header for the user interface and input validation for the entered number corresponding to which field they would like to update. Will only run if 'studentIndex' is not equal to '-1'.
	if (studentIndex != -1) {
		std::cout << "\n\033[36m\033[3m\033[1m* - \033[0m\033[1mFound student at line " << studentIndex + 1 << "!\033[0m\n"
			<< "\n\033[36m\033[3m\033[1m1 - \033[0m\033[1mStudent Name.\033[0m\n"
			<< "\033[36m\033[3m\033[1m2 - \033[0m\033[1mStudent Number.\033[0m\n"
			<< "\033[36m\033[3m\033[1m3 - \033[0m\033[1mStudent Grades.\033[0m\n"
			<< "\033[36m\033[3m\033[1m4 - \033[0m\033[1mExit Update.\033[0m\n\n"
			<< "\033[36m\033[3m\033[1m* - \033[0m\033[1mEnter what you would like to update:\033[0m\n";

		int updateMenuIndex = 0;
		bool correct = false;
		do
		{
			std::cin >> updateMenuIndex;
			if (!std::cin.fail() && updateMenuIndex >= 1 && updateMenuIndex <= 4)
			{
				correct = true;
			}
			else if (!correct)
			{
				correct = false;
				std::cerr << "\033[31m\033[3mINVALID INPUT ENTERED!\033[0m\n";
				this->logger.logError("Invalid input entered in update menu");
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		} while (!correct);

		//Gets the infomation currently stored and saves in tempuary variables.
		this->tempStudentName = this->students[studentIndex].getStudentName();
		this->tempStudentNum = this->students[studentIndex].getStudentNum();
		for (short unsigned int i = 0; i < GRADES_AMMOUNT; i++)
		{
			this->tempGrades[i] = *(this->students[studentIndex].getGradesPtr() + i);
		}

		//Outputs the current student data to the console.
		std::cout << "\n\033[36m\033[3m\033[1m* - \033[0m\033[36m\033[1mCurrent Data: \033[0m\033[1m" << this->tempStudentName << "\033[36m, \033[0m\033[1m" << this->tempStudentNum << "\033[36m, \033[0m\033[1m" << arrayToString(this->students[studentIndex].getGradesPtr(), GRADES_AMMOUNT, ' ') << "\033[36m. \033[0m\n";
		std::this_thread::sleep_for(std::chrono::seconds(2)); //Sleeps the program for 2 seconds.

		if (updateMenuIndex == 4) { return; };   //Exits update menu if 'updateMenuIndex' is equal to four.

		//Figures out which member data will be updated and creates a copy of it for logging purposes.
		std::string dataLogCopy = ((updateMenuIndex == 1) ? tempStudentName : (updateMenuIndex == 2) ? tempStudentNum : (updateMenuIndex == 3) ? arrayToString(&tempGrades[0], GRADES_AMMOUNT, ' ') : "NULL");

		//The tempuary object which which for each passed in data will either call the function to get new data or just equal it to what was in there before.
		Students temp((updateMenuIndex == 3) ? inputGradesPtr() : &this->tempGrades[0], (updateMenuIndex == 2) ? inputStudentNum() : this->tempStudentNum, (updateMenuIndex == 1) ? inputStudentName() : this->tempStudentName);
		std::swap(this->students[studentIndex], temp);   //Swaps the tempuary object with the one that at the location of the 'studentIndex'.

		std::cout << "\033[36m\033\n[1m* Updated student succesfully at line " << studentIndex + 1 << ".\033[0m\n";
		this->logger.logDataChange("Updated student in update menu", dataLogCopy, ((updateMenuIndex == 1) ? this->students[studentIndex].getStudentName() : (updateMenuIndex == 2) ? this->students[studentIndex].getStudentNum() : (updateMenuIndex == 3) ? arrayToString(this->students[studentIndex].getGradesPtr(), GRADES_AMMOUNT, ' ') : "NULL"));

		std::this_thread::sleep_for(std::chrono::seconds(3));   //Sleeps the program for 3 seconds.
	}
	else if (studentIndex == -1)
	{
		std::cerr << "\033[31m\033[3m\nFAILED TO UPDATE STUDENT!\033[0m\n";
		this->logger.logError("Failed to update student in update menu");
		std::this_thread::sleep_for(std::chrono::seconds(3));   //Sleeps the program for 3 seconds.
	}
}

//chackStudentNum function within the 'MainFunctions' class, checks if the student number entered is already inside an object or allocated to a student.
int MainFunctions::findStudentNum(std::string& tempStudentNum, std::vector<Students>& students)
{
	for (size_t i = 0; i < students.size(); i++)
	{
		if (students[i].getStudentNum() == tempStudentNum)
		{
			return i;
		}
	}
	return -1;
}

//sortStudents function within the 'MainFunctions' class, will sort the students into accending or decending order using the grade average.
bool MainFunctions::sortStudents(std::vector<Students>& students, bool accendingOrder)
{
	double temp = 0;
	size_t i1 = 0;
	int i2 = 0;

	//Uses an 'insertion' sort algorithum to sort the students via there overall mark.
	for (i1 = 1; i1 < students.size(); i1++)
	{
		temp = students[i1].getOverallMark();
		i2 = i1 - 1;

		while (i2 >= 0 && (accendingOrder ? students[i2].getOverallMark() > temp : students[i2].getOverallMark() < temp))
		{
			std::swap(students[i2 + 1], students[i2]);
			i2 = i2 - 1;
		}
	}
	return (i1 == students.size()) ? true : false;
}

//findStudent function within the 'MainFunctions' class, will find a students name location within the vector of 'Students' objects.
int MainFunctions::findStudent(std::vector<Students>& students, std::string studentName)
{
	for (size_t i = 0; i < students.size(); i++)
	{
		if (students[i].getStudentName() == studentName)
		{
			return i;
		}
	}
	return -1;
}

//listStudents function within the 'MainFunctions' class, will list all the students infomation into the console.
void MainFunctions::listStudents(std::vector<Students>& students)
{
	char exit;
	do
	{
		std::cout << "\033[36m\033[1mNum | Student Name                 | Student Num | Student Email (students.southwales.ac.uk) | Time Added | Date Added |\033[0m\n";

		for (size_t i = 0; i < students.size(); i++)
		{
			std::cout << ((this->searchInListIndex == i) ? "\033[1m\033[43m" : "\033[1m") << formatNum(i + 1, 4, '0') << ((this->searchInListIndex == i) ? "\033[36m| \033[0m\033[43m" : "\033[36m| \033[0m")
				<< std::left << std::setw(29) << students[i].getStudentName() << ((this->searchInListIndex == i) ? "\033[36m\033[1m| \033[0m\033[43m" : "\033[36m\033[1m| \033[0m") << std::left << std::setw(12)
				<< students[i].getStudentNum() << ((this->searchInListIndex == i) ? "\033[36m\033[1m| \033[0m\033[43m" : "\033[36m\033[1m| \033[0m") << std::left << std::setw(42) << students[i].getStudentEmail()
				<< ((this->searchInListIndex == i) ? "\033[36m\033[1m| \033[0m\033[43m" : "\033[36m\033[1m| \033[0m") << std::left << std::setw(11) << getFormattedTime24(students[i].getTimeAdded())
				<< ((this->searchInListIndex == i) ? "\033[36m\033[1m| \033[0m\033[43m" : "\033[36m\033[1m| \033[0m") << std::left << std::setw(11) << getFormattedDate(students[i].getDateAdded())
				<< "\033[36m\033[1m|\033[0m\n";
		}

		std::cout << "\n\033[36m\033[1mWould you like to exit the list menu (E.g. 'y'):\033[0m\n";
		do
		{
			std::cin >> exit;
		} while (std::toupper(exit) != 'Y');

	} while (std::toupper(exit) != 'Y');
}

//listStudents function within the 'MainFunctions' class, will list all the students grades into the console.
void MainFunctions::listStudentsGrades(std::vector<Students>& students)
{
	char exit;
	do
	{
		std::cout << "\033[36m\033[1mNum | Student Name             | Student Num | M1,M2,M3,M4 (%) | OvM(%) | Grade (Honours)      | Grade in 'M4' for 70% |\033[0m\n";

		for (size_t i0 = 0; i0 < students.size(); i0++)
		{
			std::cout << ((this->searchInListIndex == i0) ? "\033[43m\033[1m" : "\033[1m") << formatNum(i0 + 1, 4, '0') << std::fixed << std::setprecision(1) << ((this->searchInListIndex == i0) ? "\033[36m| \033[0m\033[43m" : "\033[36m| \033[0m") 
				<< std::left << std::setw(25) << students[i0].getStudentName() << ((this->searchInListIndex == i0) ? "\033[36m\033[1m| \033[0m\033[43m" : "\033[36m\033[1m| \033[0m") << std::left << std::setw(12) << students[i0].getStudentNum() 
				<< ((this->searchInListIndex == i0) ? "\033[36m\033[1m|\033[0m\033[43m" : "\033[36m\033[1m|\033[0m");

			for (size_t i1 = 0; i1 < GRADES_AMMOUNT; i1++)
			{
				std::cout << " " << ((*(students[i0].getGradesPtr() + i1) == -1) ? "N/A" : formatNum(*(students[i0].getGradesPtr() + i1), 3, ' '));
			}

			std::ostringstream stream;
			stream << std::fixed << std::setprecision(1) << ((students[i0].getGradePrediction() == -1) ? 0 : ((students[i0].getGradePrediction() < 100) ? students[i0].getGradePrediction() : 0)) 
				<< ((students[i0].getGradePrediction() < 0) ? "% all marks added!" : ((students[i0].getGradePrediction() < 100) ? "% needed in 'M4'!" : ((students[i0].getGradePrediction() > 100) ? "% cant get " + std::to_string(PREDICT_GRADE_FOR) + "% Ov!" : "% ERROR!")));

			std::cout << std::left << std::setw(1) << "" << ((this->searchInListIndex == i0) ? "\033[36m\033[1m| \033[0m\033[43m" : "\033[36m\033[1m| \033[0m") << std::left << std::setw(7) << students[i0].getOverallMark() 
				<< ((this->searchInListIndex == i0) ? "\033[36m\033[1m| \033[0m\033[43m" : "\033[36m\033[1m| \033[0m") << std::left << std::setw(21) << students[i0].getGradeHonours() << std::left << std::setw(15) 
				<< ((this->searchInListIndex == i0) ? "\033[36m\033[1m| \033[0m\033[43m" : "\033[36m\033[1m| \033[0m") << std::left << std::setw(22) << stream.str() 
				<< ((this->searchInListIndex == i0) ? "\033[36m\033[1m|\033[43m\033[0m\n" : "\033[36m\033[1m|\033[0m\n");
		}
		this->searchInListIndex = -1;

		std::cout << "\n\033[36m\033[1mWould you like to exit the list menu (E.g. 'y'):\033[0m\n";
		do
		{
			std::cin >> exit;
		} while (std::toupper(exit) != 'Y');

	} while (std::toupper(exit) != 'Y');
}

  /************************************************************/
 /*  Functions that are within the 'FileInputOutput' class.  */
/************************************************************/

//FileInputOutput constructors and deconstuctors.

FileInputOutput::FileInputOutput() { }

FileInputOutput::~FileInputOutput() 
{
	delete[]tempGrades;
}

//inputFile function within the 'MainFunctions' class, loops through a file and gets all the different
// students infomation and puts into the 'Students' vector of objects (each object being a induvidual student).
bool FileInputOutput::inputFile(std::vector<Students>& students, std::string fileName, char fileSpacing)
{
	this->inFile.open(fileName, std::ios::in);

	if (!this->inFile || this->inFile.fail())
	{
		return false;
	}
	else
	{
		bool endOfFile = false;
		//Used a custom 'endOfFile' check as the usally 'eof' wasnt working for my file input implementation.
		while (!endOfFile || !this->inFile.eof()) 
		{
			endOfFile = (this->inFile.peek() == -1) ? true : false;

			//File input will get everything in as strings and covert it to the different data types needed. 
			if (!endOfFile || !this->inFile.eof()) 
			{
				std::string num;
				num.clear();

				//Inputs all the data within the file into tempuary variables.
				std::getline(this->inFile, this->tempStudentName, fileSpacing);
				std::getline(this->inFile, this->tempStudentNum, fileSpacing);
				std::getline(this->inFile, this->tempStudentEmail, fileSpacing);

				for (short unsigned int i = 0; i < GRADES_AMMOUNT; i++)
				{
					std::getline(this->inFile, num, fileSpacing);
					*(this->tempGrades + i) = (num != "N/A") ? std::stoi(num) : -1;
				}

				std::getline(this->inFile, num, fileSpacing);
				this->tempOverallMark = std::stod(num);

				std::getline(this->inFile, this->tempGradeHonours, fileSpacing);

				std::getline(this->inFile, num, fileSpacing);
				this->tempGradePrediction = (num != "N/A") ? std::stod(num) : -1;

				std::getline(this->inFile, this->tempTimeAdded, fileSpacing);
				std::getline(this->inFile, this->tempDateAdded);

				//Creates a tempuary object with these tempuary variables and pushes this object to the back of the vector of 'Students' objects.
				Students temp(this->tempDateAdded, this->tempTimeAdded, this->tempGradePrediction, this->tempGradeHonours, this->tempOverallMark, &this->tempGrades[0], this->tempStudentEmail, this->tempStudentNum, this->tempStudentName);
				students.push_back(temp);
			}
		}
	}
	this->inFile.close();
	return true;
}

//outputFile function within the 'MainFunctions' class, loops through the 'Students' vector of objects and
// outputs all the induvidal students into a .txt file.
bool FileInputOutput::outputFile(std::vector<Students>& students, std::string fileName, char fileSpacing)
{
	int* gradesPtr;
	this->outFile.open(fileName, std::ios::out);

	if (this->outFile.fail())
	{
		return false;
	}
	else
	{
		for (size_t i = 0; i < students.size(); i++)
		{
			gradesPtr = students[i].getGradesPtr();

			this->outFile << students[i].getStudentName() << fileSpacing << students[i].getStudentNum() << fileSpacing << students[i].getStudentEmail() << fileSpacing;

			for (short unsigned int i = 0; i < GRADES_AMMOUNT; i++)
			{
				this->outFile << ((*(gradesPtr + i) < 0) ? "N/A" : formatNum(*(gradesPtr + i), 3, '0')) << fileSpacing;
			}
			this->outFile << students[i].getOverallMark() << fileSpacing << students[i].getGradeHonours() << fileSpacing << ((students[i].getGradePrediction() < 0) ? "N/A" : std::to_string(students[i].getGradePrediction())) 
				<< fileSpacing << getFormattedTime24(students[i].getTimeAdded()) << fileSpacing << getFormattedDate(students[i].getDateAdded()) << "\n";
		}
	}
	this->outFile.close();
	return true;
}

//outputLogFile function within the 'FileInputOutput' class, will out a log message to the log file with the data and time.
bool FileInputOutput::outputLogFile(std::string fileName, const std::string& logType, const std::string& logMessage, std::string timeOfLog, std::string dateOfLog, const unsigned long int& counter)
{
	this->outFile.open(fileName, std::ios::app);

	if (this->outFile.fail())
	{
		return false;
	}
	else 
	{
		this->outFile << formatNum(counter, 4, '0') << ". " << logType << " (" << logMessage << ") " << getFormattedTime24(timeOfLog) << " " << getFormattedDate(dateOfLog) << "\n";
	}
	this->outFile.close();
	return true;
}

  /***************************************************/
 /*  Functions that are within the 'Logger' class.  */
/***************************************************/

//Logger class constructor.
Logger::Logger() { this->counter = 0; }

//logError function within the 'Logger' class, will log an error to the text file.
bool Logger::logError(const std::string& reason)
{
	updateTimeDate();
	this->counter++;
	return this->outputLogFile(this->DEFAULT_LOG_FILE_NAME, "ERROR", reason, this->timeOfLog, this->dateOfLog, this->counter);

}

//logDataChange function within the 'Logger' class, will log any data change to the text file.
bool Logger::logDataChange(const std::string& reason, std::string oldData, std::string newData)
{
	updateTimeDate();
	this->counter++;
	return this->outputLogFile(this->DEFAULT_LOG_FILE_NAME, "DATA CHANGE", reason + " (OLD = " + oldData + ", NEW = " + newData + ")", this->timeOfLog, this->dateOfLog, this->counter);
}

//logProgramStart function within the 'Logger' class, will log the program start to the text file.
bool Logger::logProgramStart()
{
	updateTimeDate();
	this->counter++;
	return this->outputLogFile(this->DEFAULT_LOG_FILE_NAME, "START", "Program started at", this->timeOfLog, this->dateOfLog, this->counter);
}

//logProgramEnd function within the 'Logger' class, will log the program end to the text file.
bool Logger::logProgramEnd()
{
	updateTimeDate();
	this->counter++;
	return this->outputLogFile(this->DEFAULT_LOG_FILE_NAME, "END", "Program ended at", this->timeOfLog, this->dateOfLog, this->counter);
}

//logFileIndput function within the 'Logger' class, will log any file input to the text file.
bool Logger::logFileInput(const std::string& reason, std::string fileName)
{
	updateTimeDate();
	this->counter++;
	return this->outputLogFile(this->DEFAULT_LOG_FILE_NAME, "FILE INPUT", reason + " (" + fileName + ")", this->timeOfLog, this->dateOfLog, this->counter);
}

//logFileOutput function within the 'Logger' class, will log the any file output to the text file.
bool Logger::logFileOutput(const std::string& reason, std::string fileName)
{
	updateTimeDate();
	this->counter++;
	return this->outputLogFile(this->DEFAULT_LOG_FILE_NAME, "FILE OUTPUT", reason + " (" + fileName + ")", this->timeOfLog, this->dateOfLog, this->counter);
}

//updateTimeDate function within the 'Logger' class, will update the time and date and format them into two strings.
void Logger::updateTimeDate() 
{
	struct tm currentTime = currentDateTime();
	this->timeOfLog.clear();
	this->dateOfLog.clear();

	this->timeOfLog.insert(this->timeOfLog.size(), std::to_string(currentTime.tm_hour));
	this->timeOfLog.push_back(':');
	this->timeOfLog.insert(this->timeOfLog.size(), std::to_string(currentTime.tm_min));
	this->timeOfLog.push_back(':');
	this->timeOfLog.insert(this->timeOfLog.size(), std::to_string(currentTime.tm_sec));

	this->dateOfLog.insert(this->dateOfLog.size(), std::to_string(currentTime.tm_mon + 1));
	this->dateOfLog.push_back('/');
	this->dateOfLog.insert(this->dateOfLog.size(), std::to_string(currentTime.tm_mday));
	this->dateOfLog.push_back('/');
	this->dateOfLog.insert(this->dateOfLog.size(), std::to_string(currentTime.tm_year + 1900));
}

  /*****************************************************/
 /*  Functions that are within the 'Students' class.  */
/*****************************************************/

//Students class constuctors.

//The defult constructor which is used for adding a new student.
Students::Students(int* gradesPtr, std::string studentNum, std::string studentName)
{
	this->studentName = studentName;
	this->studentNum = studentNum;

	for (short unsigned int i = 0; i < GRADES_AMMOUNT; i++)
	{
		this->grades[i] = *(gradesPtr + i);
	}
	updateTime();
	updateOverallMark();
	updateGradeHonours();
	generateEmail();
}

//The secondary constructor which is used to updating a student or inputing the students from a file.
Students::Students(std::string dateAdded, std::string timeAdded, double gradePrediction, std::string gradeHonours, double overallMark, int* gradesPtr, std::string studentEmail, std::string studentNum, std::string studentName)
{
	this->studentName = studentName;
	this->studentNum = studentNum;
	this->studentEmail = studentEmail;

	for (short unsigned int i = 0; i < GRADES_AMMOUNT; i++)
	{
		this->grades[i] = *(gradesPtr + i);
	}

	this->overallMark = overallMark;
	this->gradeHonours = gradeHonours;
	this->gradePrediction = gradePrediction;
	this->timeAdded = timeAdded;
	this->dateAdded = dateAdded;

	//Dont need to call these everytime it grabs data from file.
	//updateOverallMark();
	//updateGradeHonours();
	//generateEmail();
};

//Get functions within the 'Students' class, to access the variables.
std::string Students::getStudentName()
{
	return this->studentName;
}

std::string Students::getStudentNum()
{
	return this->studentNum;
}

std::string Students::getStudentEmail()
{
	return this->studentEmail;
}

int* Students::getGradesPtr()
{
	return &this->grades[0];
}

double Students::getOverallMark()
{
	return this->overallMark;
}

std::string Students::getGradeHonours()
{
	return this->gradeHonours;
}

std::string Students::getTimeAdded()
{
	return this->timeAdded;
}

std::string Students::getDateAdded()
{
	return this->dateAdded;
}

double Students::getGradePrediction() 
{
	return this->gradePrediction;
}

//generateEmail within 'Students' class, will automatically generate the students email using the student number.
void Students::generateEmail()
{
	this->studentEmail.clear();
	this->studentEmail.insert(this->studentEmail.size(), this->studentNum);
	this->studentEmail.insert(this->studentEmail.size(), DEFAULT_EMAIL_END);
}

//updateTime function within 'Students' class, will get the current time and create a string for the time and a string for the date.
void Students::updateTime()
{
	struct tm currentTime = currentDateTime();

	this->timeAdded.insert(this->timeAdded.size(), std::to_string(currentTime.tm_hour));
	this->timeAdded.push_back(':');
	this->timeAdded.insert(this->timeAdded.size(), std::to_string(currentTime.tm_min));
	this->timeAdded.push_back(':');
	this->timeAdded.insert(this->timeAdded.size(), std::to_string(currentTime.tm_sec));

	this->dateAdded.insert(this->dateAdded.size(), std::to_string(currentTime.tm_mon + 1));
	this->dateAdded.push_back('/');
	this->dateAdded.insert(this->dateAdded.size(), std::to_string(currentTime.tm_mday));
	this->dateAdded.push_back('/');
	this->dateAdded.insert(this->dateAdded.size(), std::to_string(currentTime.tm_year + 1900));
}

//updateOverallMark function within the 'Students' class, will calculate the overall mark using percentages declered at start of program.
void Students::updateOverallMark()
{
	this->overallMark = 0;
	this->gradePrediction = 0;

	if (this->grades[GRADES_AMMOUNT - 1] < 0)
	{
		//Will run this if grade three is equal to '-1'. '-1' is the way the program detects if it needs to predict the grade.
		for (short unsigned int i1 = 0; i1 < GRADES_AMMOUNT - 1; i1++) 
		{
			this->overallMark += static_cast<double>(this->grades[i1]) * (static_cast<double>(gradePercent[i1]) / 100);
		}
		this->gradePrediction = (PREDICT_GRADE_FOR - this->overallMark) * (100 / static_cast<double>(gradePercent[GRADES_AMMOUNT - 1]));
	} 
	else if (!(this->grades[GRADES_AMMOUNT - 1] < 0))
	{
		//Will run this if grade three is not equal to '-1'.
		for (short unsigned int i2 = 0; i2 < GRADES_AMMOUNT; i2++) 
		{
			this->overallMark += static_cast<double>(this->grades[i2]) * (static_cast<double>(gradePercent[i2]) / 100);
		}
	}
	//Final check to make sure the 'gradePrediction' and 'overallMark' was calculated correctly.
	this->gradePrediction = (this->gradePrediction <= 0) ? -1 : this->gradePrediction;
	this->overallMark = (this->overallMark < 0 || this->overallMark > 100) ? NULL : this->overallMark;
}

//predictGrade function within the 'Students' class will predict the students grade from the calculated overall mark.
void Students::updateGradeHonours()
{
	int overallMark = this->overallMark;

	if (overallMark <= 100 && overallMark >= 70)
	{
		this->gradeHonours = "First Class";
	}
	else if (overallMark <= 69 && overallMark >= 60)
	{
		this->gradeHonours = "Upper Second-Class";
	}
	else if (overallMark <= 59 && overallMark >= 50)
	{
		this->gradeHonours = "Lower Second-Class";
	}
	else if (overallMark <= 49 && overallMark >= 40)
	{
		this->gradeHonours = "Third Class";
	}
	else
	{
		this->gradeHonours = "Fail";
	}
}

  /*************************************************/
 /*   Global Functions - Dont need to be local.   */
/*************************************************/

//getFormattedTime24 function returns a string with the time in the correct 24-Hour format (HH:MM:SS).
std::string getFormattedTime24(const std::string& timeString)
{
	std::tm tm;
	char tempTime[10];

	std::istringstream stream(timeString);
	stream >> std::get_time(&tm, "%H:%M:%S");
	std::strftime(tempTime, sizeof(tempTime), "%H:%M:%S", &tm);

	return std::string(tempTime);
}

//getFormattedDate function returns a string with the date in the correct format (DD/MM/YY).
std::string getFormattedDate(const std::string& dateString)
{
	std::tm tm;
	char tempDate[10];

	std::istringstream stream(dateString);
	stream >> std::get_time(&tm, "%m/%d/%Y");
	std::strftime(tempDate, sizeof(tempDate), "%D", &tm);

	return std::string(tempDate);
}

//formatNum function returns a string of a formatted passed in mumber. Will insert a passed in digit in the front of the number to a desired passed in length.
std::string formatNum(int num, int length, char insertChar) {
	std::string temp(std::to_string(num));
	std::string str(1, insertChar);

	for (size_t i = 0; i < length; i++) 
	{
		temp = temp.size() != length ? temp.insert(0, str) : temp;
	}
	return temp;
}

//inputNumber function will make sure all characters are digits.
bool isFullNumber(std::string& tempNum)
{
	return std::all_of(tempNum.begin(), tempNum.end(), ::isdigit);   //<---Algorithum header file used here.
}

//isNumberInside function will check if one of the digits within a string is a number.
bool isNumberInside(std::string& tempChar)
{
	const char numbers[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	for (size_t i = 0; i < 10; i++)
	{
		if (tempChar.find(numbers[i]) != std::string::npos)
		{
			return true;
		}
	}
	return false;
}

//isCharInside function will check if one of the digits within a string is a certain character that is passed in as a parameter.
bool isCharInside(char c, std::string& characters)
{
	size_t found = 0;
	return (found = characters.find(c) != std::string::npos) ? true : false;
}

//isCharAtIndex function will check to see if a passed in character is at an index in the string.
bool isCharAtIndex(char c, int index, std::string& str) 
{
	return (str.find(c) == index) ? true : false;
}

//currentDateTime function will get the current date and time and return it using a 'struct tm'.
struct tm currentDateTime()
{
	struct tm currentTime;
	time_t now = time(NULL);
	localtime_s(&currentTime, &now);
	return currentTime;
}

//arrayToString function takes in a pointer to an array and will loop though the array and put all the array data into a string with a desired character inbetween each bit of data.
std::string arrayToString(int* ptr, const int& arraySize, const char charBetween)
{
	std::string temp;

	for (size_t i = 0; i < arraySize; i++) 
	{
		temp += std::to_string(*(ptr + i));
		temp += charBetween;
	}
	return temp;
}

  /******************************************/
 /*   Code that didnt end up being used.   */
/******************************************/

/*
//inputStudentEmail function within the 'MainFunctions' class, inputs the entered email, validates it and checks for '@' and '.'. Returns the email as a string.
std::string MainFunctions::inputStudentEmail()
{
	bool correct = false;
	std::cout << "\n\033[36m\033[3m\033[1m3 - \033[0m\033[1mStudent Email (E.g. 10057890@students.southwales.ac.uk):\033[0m\n";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	do
	{
		correct = false;
		std::getline(std::cin, this->tempStudentEmail);
		if (isCharInside('@', this->tempStudentEmail) && isCharInside('.', this->tempStudentEmail) && this->tempStudentEmail.size() > MINIMUM_ENTERED_SIZE)
		{
			correct = true;
		}
		else if (!correct)
		{
			correct = false;
			std::cerr << "\033[31m\033[3mINVALID INPUT ENTERED!\033[0m\n";
		}
	} while (!correct);
	return this->tempStudentEmail;
}
*/
/*
bool FileInputOutput::outputSingleLine(Students& students, std::string fileName, char fileSpacing) {
	int* gradesPtr;

	if (!this->inFile || this->inFile.fail())
	{
		return false;
	}
	else
	{
		this->outFile.open(fileName);

		gradesPtr = students.getGradesPtr();

		this->outFile << students.getStudentName() << fileSpacing << students.getStudentNum() << fileSpacing << students.getStudentEmail() << fileSpacing;

		for (short unsigned int i = 0; i < GRADES_AMMOUNT; i++)
		{
			this->outFile << *(gradesPtr + i) << fileSpacing;
		}
		this->outFile << students.getOverallMark() << fileSpacing << students.getGradePrediction() << fileSpacing << getFormattedTime24(students.getTimeAdded()) << fileSpacing << getFormattedDate(students.getDateAdded()) << "\n";
	}
	this->outFile.close();
	return true;
}
*/