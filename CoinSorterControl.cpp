//Author: Jacob Forrest
//Date: November 5 2018

#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <string>
#include <sstream>

using namespace std;


int main()
{
	// Declare and initialize constants
	const double nickelWeightMin = 3.6;
	const double nickelWeightMax = 4.3;
	const double nickelDiameterMin = 20.2;
	const double nickelDiameterMax = 21.8;
	const int nickelCoinsPerRoll = 40;

	const double dimeWeightMin = 1.3;
	const double dimeWeightMax = 2.2;
	const double dimeDiameterMin = 17.3;
	const double dimeDiameterMax = 18.7;
	const int dimeCoinsPerRoll = 50;

	const double quarterWeightMin = 4.0;
	const double quarterWeightMax = 4.8;
	const double quarterDiameterMin = 22.8;
	const double quarterDiameterMax = 24.6;
	const int quarterCoinsPerRoll = 40;

	const double loonieWeightMin = 6.5;
	const double loonieWeightMax = 7.5;
	const double loonieDiameterMin = 25;
	const double loonieDiameterMax = 27;
	const int loonieCoinsPerRoll = 25;

	const double twonieWeightMin = 6.75;
	const double twonieWeightMax = 7.85;
	const double twonieDiameterMin = 26.9;
	const double twonieDiameterMax = 29.1;
	const int twonieCoinsPerRoll = 25;

	const int bentContainerMax = 100;
	const int otherContainerMax = 200;

	// Declare and initialize variable
	ifstream inputFile;
	ofstream outputFile;
	char inputName[1024] = { '\0' };
	char outputName[1024] = { '\0' };
	int numAttempts = 0;
	int numLines = 0;
	int weightSensor = 0;
	int diameterSensor = 0;
	string straightness = "a";
	string match = "b";
	int lineNumber = 0;
	double weightGrams = 0.0;
	double weightConversionRatio = 25.5;
	double diameterMM = 0.0;
	double diameterConversionRatio = 8.5;
	int numNickels = 0;
	int numDimes = 0;
	int numQuarters = 0;
	int numLoonies = 0;
	int numTwonies = 0;
	int nickelRolls = 0;
	int dimeRolls = 0;
	int quarterRolls = 0;
	int loonieRolls = 0;
	int twonieRolls = 0;
	int otherContainers = 0;
	int bentContainers = 0;
	double bentWeight = 0.0;
	double otherWeight = 0.0;
	int otherCoins = 0;
	int bentCoins = 0;
	int totalOtherCoins = 0;
	double totalWeightOtherCoins = 0.0;
	double totalWeightBentCoins = 0.0;
	string line;
	int linesCompleted = 0;
	istringstream sin;


	/*INPUT*/
	//Prompt for and read the filename of the file containing the input data
	cout << "Type the name of the input file containing sensor readings: \n";
	outputFile << "Type the name of the input file containing sensor readings: \n";
	cin >> inputName;

	//Open the input file containing the sensor readings
	inputFile.open(inputName);

	//Allow 2 attempts for correct input file name
	while (inputFile.fail() && numAttempts < 2)
	{
		cerr << "ERROR: File \"" << inputName << "\" could not be opened for input";
		cout << "\nType the name of the input file containing sensor readings: \n";

		cin >> inputName;
		numAttempts++;
		inputFile.open(inputName);
		if (inputFile.is_open())
		{
			break;
		}
	}

	//If third attempt fails then terminate program
	if (inputFile.fail())
	{
		cerr << "ERROR: File \"" << inputName << "\" could not be opened for input";
		cerr << "\nERROR: You exceeded maximum number of tries allowed \nwhile entering the input file name\n";
		return 1;
	}










	/*OUTPUT*/
	//Prompt for and read the file name of the output file
	cout << "Type the name of the output file which will hold the simulation results: \n";
	outputFile << "Type the name of the output file which will hold the simulation results: \n";
	cin >> outputName;

	//Open the output file to save the results of the simulation
	outputFile.open(outputName);

	//reset numAttempts
	numAttempts = 0;

	//Allow 2 attempts for correct output file name
	while (outputFile.fail() && numAttempts < 2)
	{
		cerr << "ERROR: File \"" << outputName << "\" could not be opened for output";
		cout << "\nType the name of the input file containing sensor readings: \n";
		outputFile << "\nType the name of the input file containing sensor readings: \n";

		cin >> outputName;
		numAttempts++;
		outputFile.open(outputName);
		if (outputFile.is_open())
		{
			break;
		}
	}

	//If third attempt fails then terminate program
	if (outputFile.fail())
	{
		cerr << "ERROR: File \"" << outputName << "\" could not be opened for output";
		cerr << "\nERROR: You exceeded maximum number of tries allowed \nwhile entering the output file name\n";
		return 2;
	}


	// Read the number of lines of data stated in the input file
	// (The first integer in the file, alone on the first line of the file)
	inputFile >> numLines;

	// Check if file is empty
	if (inputFile.eof())
	{
		cerr << "ERROR: Input data file is empty\n";
		inputFile.close();
		return 3;
	}

	// Check if the first character cannot be part of an integer
	if (!inputFile)
	{
		cerr << "ERROR: First piece of data in the file is not an integer\n";
		inputFile.close();
		return 4;
	}

	// Check if the number of sensor readings is out of range (<=0 or >5000)
	if (numLines <= 0 || numLines > 5000)
	{
		cerr << "ERROR: The number of sensor readings is out of range\n";
		inputFile.close();
		return 5;
	}




	//repeat actions "number of lines" times
	while (getline(inputFile, line) && linesCompleted <= numLines) //run the loop for each line in the file
	{
		istringstream sin(line); //put the contents of the line into a stringstream sin
		lineNumber++;
		linesCompleted++;
		// read weight measurement. If it cant be read check why
		if (!(sin >> weightSensor))
		{
			//check if blank line
			if (sin.eof())
			{
				lineNumber--;
				linesCompleted--;
				continue;
			}
			//Check if weight value cannot be part of an integer
			else
			{
				cerr << "Weight sensor value read on line " << lineNumber << " is not an integer";
				cerr << "\nSimulation terminated early: Please correct your data file\n";
				break;
			}
		}

		//read diamter sensor measurement. If it cant be read check why
		if (!(sin >> diameterSensor))
		{
			//Check if there is only one sensor reading on the present line of data
			if (sin.eof())
			{
				cerr << "ERROR: Weight sensor measurement only\nIgnoring line " << lineNumber << " of the input file\n";
				continue;
			}
			//Check if diameter value cannot be part of an integer
			else
			{
				cerr << "Diameter sensor value read on line " << lineNumber << " is not an integer";
				cerr << "\nSimulation terminated early: Please correct your data file\n";
				break;
			}
		}



		//read straightness measurement. If it cant be read it is missing
		else if (!(sin >> straightness))
		{
			//Check if there is only weight and diameter sensor reading on the present line of data
			cerr << "ERROR: Weight and diameter sensor measurements only\nIgnoring line " << lineNumber << " of the input file\n";
			continue;
		}
		//Check if the result of test to determine if coin is bent is valid
		else if (straightness != "usable" && straightness != "bent")
		{
			cerr << "ERROR: Result of test to determine if coin is bent at line " << lineNumber << " is invalid\nIgnoring this line of data\n";
			continue;
		}

		//read match measurement. if it cant be read it is missing
		else if (!(sin >> match))
		{
			cerr << "ERROR: Weight and diameter sensor measurements and bent string only\nIgnoring line " << lineNumber << " of the input file\n";
			continue;
		}
		//Check if the value of the image processing result is valid
		else if (match != "BothMatch" && match != "OneMatch" && match != "NoMatch")
		{
			cerr << "ERROR: image processing result at line " << lineNumber << " is invalid\nIgnoring this line of data\n";
			continue;
		}
		//Check if there is extra data at the end of the line of data
		else if (!(sin >> ws).eof())
		{
			cerr << "ERROR: Extra data at line " << lineNumber << ". Ignoring extra data\n";
		}
		//Check if the sensor reading is out of range (0<=sensor<=255)
		if (diameterSensor < 0 || diameterSensor > 255)
		{
			cerr << "ERROR: Sensor reading out of range, ignoring line " << lineNumber << " in the input file\n";
			continue;
		}
		//Check if the sensor reading is out of range (0<=sensor<=255)
		if (weightSensor < 0 || weightSensor > 255)
		{
			cerr << "ERROR: Sensor reading out of range, ignoring line " << lineNumber << " in the input file\n";
			continue;
		}

		//Determine what kind of coin the data represents
		//check if bent, perform actions for bent coin
		if (straightness == "bent")
		{
			weightGrams = (weightSensor / weightConversionRatio);
			if ((weightGrams + bentWeight) >= bentContainerMax)
			{
				bentContainers++;
				bentWeight = 0;
				cout << "The Coin Sorter has sent this coin to the bent coin container" << endl;
				cout << "This coint does not fit in the bent coin container" << endl;
				cout << "the bent coin container has now been replaced\nThe coin in the new bent coin container weighs ";

				outputFile << "The Coin Sorter has sent this coin to the bent coin container" << endl;
				outputFile << "This coint does not fit in the bent coin container" << endl;
				outputFile << "the bent coin container has now been replaced\nThe coin in the new bent coin container weighs ";

				bentWeight += weightGrams;
				totalWeightBentCoins += weightGrams;
				cout << bentWeight << " grams\n";

				outputFile << bentWeight << " grams\n";

				continue;
			}
			bentWeight += weightGrams;
			totalWeightBentCoins += weightGrams;
			cout << "The Coin Sorter has sent this coin to the bent coin container" << endl;
			cout << "The coins in the bent coin container now weigh " << fixed << right << setw(6) << setprecision(2) << bentWeight << " grams\n";

			outputFile << "The Coin Sorter has sent this coin to the bent coin container" << endl;
			outputFile << "The coins in the bent coin container now weigh " << fixed << right << setw(6) << setprecision(2) << bentWeight << " grams\n";

			continue;
		}
		else if (straightness == "usable")
		{
			weightGrams = (weightSensor / weightConversionRatio);
			diameterMM = 10 + (diameterSensor / diameterConversionRatio);
		}

		//check if nickel, perform actions for nickel
		if (match == "BothMatch" && ((weightGrams >= nickelWeightMin && weightGrams <= nickelWeightMax) && (diameterMM >= nickelDiameterMin && diameterMM <= nickelDiameterMax)))
		{
			if (numNickels == nickelCoinsPerRoll - 1)
			{
				nickelRolls++;
				numNickels = 0;
				cout << "The Coin Sorter has sent one coin to the nickels wrapper\n";
				cout << "The nickel wrapper is now full\nThe nickel wrapper has now been replaced\n";

				outputFile << "The Coin Sorter has sent one coin to the nickels wrapper\n";
				outputFile << "The nickel wrapper is now full\nThe nickel wrapper has now been replaced\n";


				continue;
			}
			numNickels++;
			cout << "The Coin Sorter has sent one coin to the nickels wrapper\nThere are now ";
			cout << numNickels << " coins in the nickels wrapper\n";

			outputFile << "The Coin Sorter has sent one coin to the nickels wrapper\nThere are now ";
			outputFile << numNickels << " coins in the nickels wrapper\n";

			continue;
		}

		//check if dime, perform actions for dime
		else if (match == "BothMatch" && ((weightGrams >= dimeWeightMin && weightGrams <= dimeWeightMax) && (diameterMM >= dimeDiameterMin && diameterMM <= dimeDiameterMax)))
		{
			if (numDimes == dimeCoinsPerRoll - 1)
			{
				dimeRolls++;
				numDimes = 0;
				cout << "The Coin Sorter has sent one coin to the dimes wrapper\n";
				cout << "The dime wrapper is now full\nThe dime wrapper has now been replaced\n";

				outputFile << "The Coin Sorter has sent one coin to the dimes wrapper\n";
				outputFile << "The dime wrapper is now full\nThe dime wrapper has now been replaced\n";


				continue;
			}
			numDimes++;
			cout << "The Coin Sorter has sent one coin to the dimes wrapper\nThere are now ";
			cout << numDimes << " coins in the dimes wrapper\n";

			outputFile << "The Coin Sorter has sent one coin to the dimes wrapper\nThere are now ";
			outputFile << numDimes << " coins in the dimes wrapper\n";

			continue;
		}

		//check if quarter, perform actions for quarter
		else if (match == "BothMatch" && ((weightGrams >= quarterWeightMin && weightGrams <= quarterWeightMax) && (diameterMM >= quarterDiameterMin && diameterMM <= quarterDiameterMax)))
		{
			if (numQuarters == quarterCoinsPerRoll - 1)
			{
				quarterRolls++;
				numQuarters = 0;
				cout << "The coin sorter has sent one coin to the quarters wrapper\n";
				cout << "The quarter wrapper is now full\nThe quarter wrapper has now been replaced\n";

				outputFile << "The coin sorter has sent one coin to the quarters wrapper\n";
				outputFile << "The quarter wrapper is now full\nThe quarter wrapper has now been replaced\n";


				continue;
			}
			numQuarters++;
			cout << "The Coin Sorter has sent one coin to the quarters wrapper\nThere are now ";
			cout << numQuarters << " coins in the quarters wrapper\n";

			outputFile << "The Coin Sorter has sent one coin to the quarters wrapper\nThere are now ";
			outputFile << numQuarters << " coins in the quarters wrapper\n";

			continue;
		}

		//check if loonie, perform actions for loonie
		else if (match == "BothMatch" && ((weightGrams >= loonieWeightMin && weightGrams <= loonieWeightMax) && (diameterMM >= loonieDiameterMin && diameterMM <= loonieDiameterMax)))
		{
			if (numLoonies == loonieCoinsPerRoll - 1)
			{
				loonieRolls++;
				numLoonies = 0;
				cout << "The Coin Sorter has sent one coin to the loonies wrapper\n";
				cout << "The loonie wrapper is now full\nThe loonie wrapper has now been replaced\n";

				outputFile << "The Coin Sorter has sent one coin to the loonies wrapper\n";
				outputFile << "The loonie wrapper is now full\nThe loonie wrapper has now been replaced\n";


				continue;
			}
			numLoonies++;
			cout << "The Coin Sorter has sent one coin to the loonies wrapper\nThere are now ";
			cout << numLoonies << " coins in the loonies wrapper\n";

			outputFile << "The Coin Sorter has sent one coin to the loonies wrapper\nThere are now ";
			outputFile << numLoonies << " coins in the loonies wrapper\n";

			continue;
		}

		//check if twonie, perform actions for twonie
		else if (match == "BothMatch" && ((weightGrams >= twonieWeightMin && weightGrams <= twonieWeightMax) && (diameterMM >= twonieDiameterMin && diameterMM <= twonieDiameterMax)))
		{
			if (numTwonies == twonieCoinsPerRoll - 1)
			{
				twonieRolls++;
				numTwonies = 0;
				cout << "The Coin Sorter has sent one coin to the toonies wrapper\n";
				cout << "The toonie wrapper is now full\nThe toonie wrapper has now been replaced\n";


				continue;
			}
			numTwonies++;
			cout << "The Coin Sorter has sent one coin to the toonies wrapper\nThere are now ";
			cout << numTwonies << " coins in the toonies wrapper\n";

			outputFile << "The Coin Sorter has sent one coin to the toonies wrapper\nThere are now ";
			outputFile << numTwonies << " coins in the toonies wrapper\n";

			continue;
		}

		//other, perform actions for other coins
		else
		{
			if ((weightGrams + otherWeight) >= otherContainerMax)
			{
				otherContainers++;
				otherWeight = 0;
				otherCoins = 0;
			}
			otherWeight += weightGrams;
			totalWeightOtherCoins += weightGrams;
			otherCoins++;
			totalOtherCoins++;
			cout << "The Coin Sorter has sent this coin to the other coin container" << endl;
			cout << "The coins in the other coin container now weigh " << fixed << right << setw(6) << setprecision(2) << otherWeight << " grams\n";

			outputFile << "The Coin Sorter has sent this coin to the other coin container" << endl;
			outputFile << "The coins in the other coin container now weigh " << fixed << right << setw(6) << setprecision(2) << otherWeight << " grams\n";

			continue;

		}
	}
	//check if the simulation completed early
	if (linesCompleted < numLines)
	{
		cerr << "ERROR: No more data\nSimulation completed early before line " << ++linesCompleted << " of input";
	}


	//SUMMARY
	cout << endl << endl << endl << endl;
	cout << "SUMMARY\n";
	cout << "The Coin Sorter made " << right << setw(3) << nickelRolls << " rolls of nickels.\n";
	cout << "    There are " << right << setw(2) << numNickels << " nickels in the partially full roll.\n";
	cout << "The Coin Sorter made " << right << setw(3) << dimeRolls << " rolls of dimes.\n";
	cout << "    There are " << right << setw(2) << numDimes << " dimes in the partially full roll.\n";
	cout << "The Coin Sorter made " << right << setw(3) << quarterRolls << " rolls of quarters.\n";
	cout << "    There are " << right << setw(2) << numQuarters << " quarters in the partially full roll.\n";
	cout << "The Coin Sorter made " << right << setw(3) << loonieRolls << " rolls of loonies.\n";
	cout << "    There are " << right << setw(2) << numLoonies << " loonies in the partially full roll.\n";
	cout << "The Coin Sorter made " << right << setw(3) << twonieRolls << " rolls of toonies.\n";
	cout << "    There are " << right << setw(2) << numTwonies << " toonies in the partially full roll.\n";
	cout << "The Coin Sorter processed " << right << setw(5) << totalOtherCoins << " other coins.\n";
	cout << "    The other coins completely filled " << right << setw(3) << otherContainers << " containers\n";
	cout << "    There were " << right << setw(2) << otherCoins << " other coins in the partially full container\n";
	cout << "    The total weight of the other coins was " << fixed << setprecision(3) << right << setw(9) << totalWeightOtherCoins << " grams\n";
	cout << "The Coin Sorter processed " << fixed << setprecision(4) << right << setw(11) << totalWeightBentCoins << " g of bent coins";

	outputFile << endl << endl << endl << endl;
	outputFile << "SUMMARY\n";
	outputFile << "The Coin Sorter made " << right << setw(3) << nickelRolls << " rolls of nickels.\n";
	outputFile << "    There are " << right << setw(2) << numNickels << " nickels in the partially full roll.\n";
	outputFile << "The Coin Sorter made " << right << setw(3) << dimeRolls << " rolls of dimes.\n";
	outputFile << "    There are " << right << setw(2) << numDimes << " dimes in the partially full roll.\n";
	outputFile << "The Coin Sorter made " << right << setw(3) << quarterRolls << " rolls of quarters.\n";
	outputFile << "    There are " << right << setw(2) << numQuarters << " quarters in the partially full roll.\n";
	outputFile << "The Coin Sorter made " << right << setw(3) << loonieRolls << " rolls of loonies.\n";
	outputFile << "    There are " << right << setw(2) << numLoonies << " loonies in the partially full roll.\n";
	outputFile << "The Coin Sorter made " << right << setw(3) << twonieRolls << " rolls of toonies.\n";
	outputFile << "    There are " << right << setw(2) << numTwonies << " toonies in the partially full roll.\n";
	outputFile << "The Coin Sorter processed " << right << setw(5) << totalOtherCoins << " other coins.\n";
	outputFile << "    The other coins completely filled " << right << setw(3) << otherContainers << " containers\n";
	outputFile << "    There were " << right << setw(2) << otherCoins << " other coins in the partially full container\n";
	outputFile << "    The total weight of the other coins was " << fixed << setprecision(3) << right << setw(9) << totalWeightOtherCoins << " grams\n";
	outputFile << "The Coin Sorter processed " << fixed << setprecision(4) << right << setw(11) << totalWeightBentCoins << " g of bent coins";


	return 0;
}