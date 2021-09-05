/*
Author: Gregory Ruta
Description: A student marks management program that reads and updates a file.
Created: 03/10/2020
Modified: 14/10/2020

NOTES
	1.	In the interests of code re-usability and legibility, I have created
		some extra 'helper' functions.

	2.	In functions that require the marks to be sorted, I have duplicated
		marksArray. Had I not done this, these functions would have sorted the
		original marksArray, thus altering the output of displayMarks from
		unsorted to sorted. A global constant ensures both original and
		duplicate arrays are of the same size.
*/

//preprocessor directives
#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>
#include <sstream>

//namespace declarations
using namespace std;

//prototype declarations (prescribed)
int readFile(ifstream&, int []);
int menu();
void displayMarks(int [], int);
double calculateMean(int [], int);
double calculateMedian(int [], int);
int findMinimum(int [], int);
int findMaximum(int [], int);
double findAverageForStudent(ifstream&, string);
int updateFile(ofstream&);

//prototype declarations (unprescribed - see Notes(1))
void openInput(ifstream&);
void openOutput(ofstream&);
void sortMinToMax(int [], int);
string getString(string);
bool isInt(string);

//global constants
const int NUMELS = 100; //number of elements in marksArray (see Notes(2))
const string MARKS_FILE = "./program_2_marks.txt"; //the program_2_marks.txt file location

int main()
{
	cout << "Welcome to Student Marks Management Program\n\n";
	
	ifstream inFile;
	ofstream outFile;
	int marksArray[NUMELS];

	//populate array and get number of marks
	int marksCount = readFile(inFile, marksArray);

	while (true)
	{
		int menuSelection = menu();
		switch (menuSelection)
		{
			case 1:
				displayMarks(marksArray, marksCount);
				break;
			case 2:
				cout << "Calculating the mean score...\nThe mean score is " << calculateMean(marksArray, marksCount) << endl;
				break;
			case 3:
				cout << "Calculating the median score...\nThe median score is " << calculateMedian(marksArray, marksCount) << endl;
				break;
			case 4:
				cout << "Finding the minimum score...\nThe minimum score is " << findMinimum(marksArray, marksCount) << endl;
				break;
			case 5:
				cout << "Finding the maximum score...\nThe maximum score is " << findMaximum(marksArray, marksCount) << endl;
				break;
			case 6:
				{
					string requestedID = getString("Enter student ID:\n");
					cout << "Finding average score for student...\n";
					double stuAvg = findAverageForStudent(inFile, requestedID);
					if (stuAvg == -1)
						cout << "Student with ID " + requestedID + " not found in the file!\n";
					else
						cout << "The average mark for student " + requestedID + " is " << stuAvg << endl;
					break;
				}
			case 7:
				{
					cout << "Updating the marks file...\n" << updateFile(outFile) << " scores added to the end of the file...\n";
					marksCount = readFile(inFile, marksArray);
					displayMarks(marksArray, marksCount);
					break;
				}
			case 8:
				cout << "Ending program!...\n";
				return 0;
			default:
				cout << "Invalid input! Enter a number between 1 and 8\n";
		}
	}
}

//read file
int readFile(ifstream& inFile, int arr[])
{
	cout << "Opening file...\n";

	openInput(inFile);

	cout << "Reading marks from the file...\n";

	int arrPos = 0;
	string line;
	while (getline(inFile, line))
	{
		//get number of grades for student
		int count = stoi(line);

		//ignore student id
		inFile.ignore(numeric_limits<streamsize>::max(), '\n');

		//for each grade, get it, add it to the array & increment arrPos
		for (int i = 0; i < count; ++i)
		{
			getline(inFile, line);
			arr[arrPos++] = stoi(line);
		}
	}

	//close file
	inFile.close();

	cout << "File contents have been read, array populated!\nTotal number of scores in file: " << arrPos << endl;

	//return number of marks
	return arrPos;
}

//menu
int menu()
{
	//create prompt
	stringstream prompt;
	prompt << "\n\n" << setw(15) << "Menu\n";
	prompt << setw(15) << "----\n";
	prompt << "1. Display marks\n";
	prompt << "2. Calculate mean\n";
	prompt << "3. Calculate median\n";
	prompt << "4. Find minimum\n";
	prompt << "5. Find maximum\n";
	prompt << "6. Find average for student\n";
	prompt << "7. Add new student data\n";
	prompt << "8. Quit program\n";
	prompt << "___________________________\n";
	prompt << "Enter your choice (1-8): ";
	
	//get user input
	string userInput = getString(prompt.str());

	//if user input is an integer, return it, else return -1 (-1 is failure)
	return isInt(userInput) ? stoi(userInput) : -1;
}

//display marks
void displayMarks(int arr[], int count)
{
	cout << "Displaying marks from the array...\n";

	//print each mark & alter output if last mark is reached
	for (int i = 0; i < count; ++i)
		cout << arr[i] << (i < count - 1 ? " " : "\nDone!");
}

//calculate mean
double calculateMean(int arr[], int count)
{
	//sum all marks
	int sum = 0;
	for (int i = 0; i < count; ++i)
		sum += arr[i];
	
	//return mean
	return sum / (double)count;
}

//calculate median
double calculateMedian(int arr[], int count)
{
	//duplicate array for sorting (see Notes)
	int arrSorted[NUMELS];
	for (int i = 0; i < count; ++i)
		arrSorted[i] = arr[i];

	//sort the copy
	sortMinToMax(arrSorted, count);

	//get median
	double median;
	if (count % 2 == 0) //if array is even
		median = (arrSorted[count / 2 - 1] + arrSorted[count / 2]) / (double)2;
	else //array is odd
		median = arrSorted[count / 2];

	//return median
	return median;
}

//find minimum
int findMinimum(int arr[], int count)
{
	//duplicate array for sorting (see Notes)
	int arrSorted[NUMELS];
	for (int i = 0; i < count; ++i)
		arrSorted[i] = arr[i];

	//sort the copy
	sortMinToMax(arrSorted, count);

	//return minimum
	return arrSorted[0];
}

//find maximum
int findMaximum(int arr[], int count)
{
	//duplicate array for sorting (see Notes)
	int arrSorted[NUMELS];
	for (int i = 0; i < count; ++i)
		arrSorted[i] = arr[i];

	//sort the copy
	sortMinToMax(arrSorted, count);

	//return maximum
	return arrSorted[count - 1];
}

//find average for a student
double findAverageForStudent(ifstream& inFile, string stuId)
{
	//open file
	openInput(inFile);

	cout << "Reading marks from the file...\n";

	string line;
	while (getline(inFile, line))
	{
		//get number of grades for student
		int count = stoi(line);

		//get student id
		getline(inFile, line);

		//if there is a student id match, sum student's marks, close file, return average
		if (line == stuId)
		{
			int sumMarks = 0;
			for (int i = 0; i < count; ++i)
			{
				getline(inFile, line);
				sumMarks += stoi(line);
			}
			//close file
			inFile.close();
			return sumMarks / (double)count;
		}
		else //else ignore unmatched student's marks
			for (int i = 0; i < count; ++i)
				inFile.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	//close file
	inFile.close();

	//if we reach this point, no matches were found (-1 is failure)
	return -1;
}

//update file with new student id and marks
int updateFile(ofstream& outFile)
{
	//open file
	openOutput(outFile);

	//get student id
	string stuId = getString("Enter student id:\n");

	//get score count
	string prompt = "Enter number of scores to add:\n";
	string alert = "Invalid Input! Please enter a number of scores\n";
	string scoreCount = getString(prompt);
	while (!isInt(scoreCount))
		scoreCount = getString(alert + prompt);

	//write score count
	outFile << scoreCount << endl;

	//write student id
	outFile << stuId << endl;

	//get scores & write them
	for (int i = 0; i < stoi(scoreCount); ++i)
	{
		string prompt = "Enter score: ";
		string alert = "Invalid Input! Please enter a score\n";
		string score = getString(prompt);
		while (!isInt(score))
			score = getString(alert + prompt);
		outFile << score << endl;
	}

	//close file
	outFile.close();

	//return score count
	return stoi(scoreCount);
}

//open input file
void openInput(ifstream& inFile)
{
	//open file
	inFile.open(MARKS_FILE);

	//if file fails to open, gracefully exit
	if (inFile.fail())
	{
		cout << "Error opening program_2_marks.txt file. Qutting program...\n";
		exit(1);
	}

	cout << "File opened for reading...\n";
}

//open output file
void openOutput(ofstream& outFile)
{
	//open file in append mode
	outFile.open(MARKS_FILE, ios::app);

	//if file fails to open, gracefully exit
	if (outFile.fail())
	{
		cout << "Error opening program_2_marks.txt file. Qutting program...\n";
		exit(1);
	}

	cout << "File opened for writing...\n";
}

//sort array from min to max
void sortMinToMax(int arr[], int count)
{
	//bubble sort
	for (int i = 0; i < count - 1; ++i)
		for (int j = 0; j < count; ++j)
			if (arr[j] < arr[j - 1])
				swap(arr[j], arr[j - 1]);
}

//prompt user and get input
string getString(string output)
{
	cout << output;
	string input;
	getline(cin, input);
	return input;
}

//check if string is integer
bool isInt(string str)
{
	string bin; //string to discard stringstream contents

	//insert string into stringstream
	stringstream ss(str);
	
	//validate user input
	int placeHolder;
	return (ss >> placeHolder && !(ss >> bin)) ? true : false;
}
