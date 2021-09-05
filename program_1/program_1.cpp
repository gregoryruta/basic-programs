/*
Author: Gregory Ruta
Description: A looping menu program that calculates power and resistance based
on user input.
Created: 28/08/2020
Modified: 08/09/2020
*/

/* Notes: 
Menu number input validation process:

	1.	Get user input.

	2.	Insert user input into a stringstream.

	3.	If (1) the stringstream extracts to an arbitrary integer variable and
		(2) the stringstream then does not extract to an arbitrary string
		variable, then the input is legal.

			(1)	Catches strings that cannot be extracted as integers (e.g.
				"Two").

			(2)	Catches strings that can be extracted as integers but should
				not (i.e. "2x").

	4.	If validation passes, the selected menu number is what the user
		requested. If validation fails, the selected menu number is set to 0
		(an invalid option).

	5.	If validation passes and the selected menu number is not in fact a
		valid menu number, or if validation fails and it has been set to 0 in
		step 4, we fall through the switch statement to the 'default' error
		message. Otherwise, if validation passes and the selected menu number
		is a valid menu number, it will be caught by the switch statement.

Voltage & current input validation process:

	The validation process for the user's voltage and current input follows
	the same logic as steps 1, 2 and 3 above (except the placeholders are
	arbitrary double variables). A successful validation leads to the
	assignment of voltage or current. An unsuccessful validation leads to an
	an error message.
*/

#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

int main()
{
	cout << "Welcome to Power and Resistance Program" << endl;

	while (true) {

		string bin; // a string to discard stringstream contents
		
		// Prompt user
		cout << "\n\n" << setw(8) << "Menu" << endl;
		cout << setw(8) << "----" << endl;
		cout << "1. Calculate power" << endl;
		cout << "2. Calculate resistance" << endl;
		cout << "3. Quit program" << endl;
		cout << "_______________________" << endl;
		cout << "Enter your choice (1, 2 or 3): ";
		
		// Get user input & insert into stringstream
		string userInput;
		getline(cin, userInput);
		stringstream ss(userInput);
		
		// Validate user input (see Notes)
		int placeHolder;
		int menuSelection = (ss >> placeHolder && !(ss >> bin)) ? placeHolder : 0;

		// Proceed with menu selection
		switch (menuSelection)
		{
			case 1:
			case 2:

				double v, i, p, r; // voltage, current, power, resistance

				// Get voltage
				while (true) {
					
					// Prompt user
					cout << "Enter voltage: ";
					
					// Get user input & insert into stringstream
					string userInput;
					getline(cin, userInput);
					stringstream ss(userInput);

					// Validate user input (see Notes)
					double placeHolder;
					if (ss >> placeHolder && !(ss >> bin))
					{
						v = placeHolder;
						break;
					} else {
						cout << "Invalid input! Enter a number for voltage..." << endl;
					}
				}
				
				// Get current
				while (true) {

					// Prompt user
					cout << "Enter current: ";

					// Get user input & insert into stringstream
					string userInput;
					getline(cin, userInput);
					stringstream ss(userInput);

					// Validate user input (see Notes)
					double placeHolder;
					if (ss >> placeHolder && !(ss >> bin))
					{
						i = placeHolder;
						break;
					} else {
						cout << "Invalid input! Enter a number for current..." << endl;
					}
				}
				
				// Select equation and output solution
				if (menuSelection == 1)
				{
					p = v*i;
					cout << "Power = " << p << " Watts" << endl;
				} else {
					r = v/i;
					cout << "Resistance = " << r << " Ohms" << endl;
				}

				break;
			case 3:
				// Exit program
				cout << "Ending program!...\n" << endl;
				return 0;
			default:
				// Validation failed
				cout << "Invalid input! Enter a number between 1 and 3" << endl;
		}
	}
}