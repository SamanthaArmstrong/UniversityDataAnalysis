/******************************************************************************
 Title:      University and College Data Analysis      
 Programmer: Samantha Armstrong     
 Course:     CSCI 240     
 Instructor: Prof. Ringenberg     
 Due Date:   October 23, 2014     

 Description:	This program will analyze data about colleges and 
 Universities in Ohio, Indiana, and Michigan. All of the data will be
 displayed in a readable and organized way. This program will calculate
 the average tuition of each state, the average tuition for all private
 four year schools in OH with tuitions over 20,000, whether or not The
 University of Findlay is above or below this average, the name and 
 enrollment of the three schools with the highest tuition overall, and all 
 the schools in Cincinnati with tuitions below 18,000.
 **************************************************************************/

#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>
using namespace std;

int main() {
	//Task #1 variables
	const int MAX_SCHOOLS = 500;
	int numSchools = 0;

	string   state[MAX_SCHOOLS];	//state
	string    name[MAX_SCHOOLS];	//school name
	string    city[MAX_SCHOOLS];	//city
	int    tuition[MAX_SCHOOLS];	//tuition
	int enrollment[MAX_SCHOOLS];    //enrollment
	string   years[MAX_SCHOOLS];	//year (2 or 4)
	string    type[MAX_SCHOOLS];	//type (Public/private)

	//Task #2 variables
	int OHschools = 0; //number of schools in OH
	int INschools = 0; //number of schools in IN
	int MIschools = 0; //number of schools in MI

	int OHsum	  = 0;
	int INsum	  = 0;
	int MIsum	  = 0;

	double OHaverage;
	double INaverage;
	double MIaverage;

	//Task #3 variables
	int OHprivateSum     = 0;	
	int OHprivateSchools = 0;	//num Ohio priv 4 yr schools with tuition over 20000
	double OHprivateAvg;
	int FindlayTuition;

	//Task #4 variables
	int highestTuitionIndex			= 0;
	int secondHighestTuitionIndex	= 0;
	int thirdHighestTuitionIndex	= 0;

	//Task #5 variables
	const int MAX_SCH = 25;
	int cinSchCount = 0; //number of schools in Cincinatti with tuition below 18000

	string   cinSchName[MAX_SCH];	//school name
	int      cinSchCost[MAX_SCH];	//tuition


	//Task #1 Processing
	//input read from a file called "scool_data.txt"
	ifstream inFile("school_data.txt");

	//error message for input file
	if (!inFile){
		cout << "Could not open file." << endl;
		return 1;
	} //end if error

	//open output file
	ofstream outFile("school_output.txt");

	//error message for output file
	if (!outFile){
		cout << "Error reading output file." << endl;
    } //end if error

	//populate arrays
	while(getline(inFile, state[numSchools]) && (state[numSchools] != "***") 
		&& numSchools < MAX_SCHOOLS ){
		while(getline(inFile, name[numSchools]) && (name[numSchools] != "+++")){
			getline(inFile, city[numSchools]);
			inFile >> tuition[numSchools];
			inFile >> enrollment[numSchools];
			inFile.ignore();
			getline(inFile, years[numSchools]);
			inFile >> type[numSchools];
			inFile.ignore();

			state[numSchools + 1] = state[numSchools];

		numSchools++;
		
		} //end while each state
	}//end while input file

	//output and processing
	for (int i = 0; i < numSchools; i++){
		//Task #1 output
		outFile << left;
		outFile << setw(58) << name[i]  << setw(25) << city[i] << setw(4) << state[i];
		outFile << right;
		outFile << setw(7) << enrollment[i] << setw(7) << tuition[i] << "  " ;
		outFile << left;
		outFile << setw(8) << years[i] << setw(9) << type[i] << endl;

		//Task #2 Processing
		if (state[i] == "OH" && tuition[i] != -1){
			OHsum += tuition[i];
			OHschools++;
		}//end if

		else if (state[i] == "MI" && tuition[i] != -1){
			MIsum += tuition[i];
			MIschools++;
		}//end else

		else if (state[i] == "IN" && tuition[i] != -1){
			INsum += tuition[i];
			INschools++;
		}//end else

		//Task #3 processing
		if(state[i] == "OH" && tuition[i] > 20000 && years[i] == "4 Year" 
			&& type[i] == "Private"){
			OHprivateSum += tuition[i];
			OHprivateSchools++;
		}//end if

		if (name[i] == "The University of Findlay"){
			FindlayTuition = tuition[i];
		}//end if

		//Task #4 processing
		if(tuition[i] > tuition[highestTuitionIndex]){
			thirdHighestTuitionIndex = secondHighestTuitionIndex;
			secondHighestTuitionIndex = highestTuitionIndex;
			highestTuitionIndex = i;
		} //end if

		else if(tuition[i] > tuition[secondHighestTuitionIndex]){
				thirdHighestTuitionIndex = secondHighestTuitionIndex;
				secondHighestTuitionIndex = i;
		} //end else

		else if(tuition[i] > tuition[thirdHighestTuitionIndex]){
				thirdHighestTuitionIndex = i;
		}//end else

		//Task #5 processing
		if(city[i] == "Cincinnati" && tuition[i] < 18000){
			cinSchName[cinSchCount] = name[i];
			cinSchCost[cinSchCount] = tuition[i];
			cinSchCount++;
		}//end if

	} //end for loop

	//post processing and output
	outFile << "*****************************************************************************"
			<< "********************************************" << endl;
	outFile << endl;

	//Post processing for Task #2
	OHaverage = OHsum / OHschools;

	outFile << "The average tuition for each state is: " << endl;
	outFile << setw(12) << "Ohio: " << "$ " << OHaverage << endl;

	MIaverage = MIsum / MIschools;
	outFile << setw(12) << "Michigan: " << "$ " << MIaverage << endl;

	INaverage = INsum / INschools;
	outFile << setw(12) << "Indiana: " << "$ " << INaverage << endl;

	outFile << "*****************************************************************************"
			<< "********************************************" << endl;
	outFile << endl;

	//Post processing for Task #3
	OHprivateAvg = OHprivateSum / OHprivateSchools;
	outFile << "The average tuition for private 4 year schools in Ohio over $20,000 is: $" 
			<< OHprivateAvg << endl;

	if (FindlayTuition > OHprivateAvg){
		outFile << "The University of Findlay's tuition rate is above this average." << endl;
	}//end if

	else if (FindlayTuition < OHprivateAvg){
		outFile << "The University of Findlay's tuition rate is below this average." << endl;
	}//end else

	else if (FindlayTuition == OHprivateAvg){
		outFile << "The University of Findlay's tuition rate is average." << endl;
	}//end else

	outFile << "*****************************************************************************"
			<< "********************************************" << endl;
	outFile << endl;

	//Post processing for Task #4
	outFile << "Schools with the top three highest tuitions: " << endl;
	outFile << "1. " << setw(58) << name[highestTuitionIndex]		<< " $ " 
			<< tuition[highestTuitionIndex] << endl;
	outFile << "2. " << setw(58) << name[secondHighestTuitionIndex]	<< " $ " 
			<< tuition[secondHighestTuitionIndex] << endl;
	outFile << "3. " << setw(58) << name[thirdHighestTuitionIndex]	<< " $ " 
			<< tuition[thirdHighestTuitionIndex] << endl;

	outFile << "*****************************************************************************"
			<< "********************************************" << endl;
	outFile << endl;

	//Post processing for Task #5
	outFile << "There are " << cinSchCount 
			<< " schools in Cincinnati with a tuition less than $18,000." << endl << endl;
	
	for(int j = 0; j < cinSchCount; j++){
		outFile << left;
		outFile << setw(58) << cinSchName[j];
		outFile << right;
		outFile << "  " << "$" << setw(7) << cinSchCost[j] << endl;	
	} //end for loop

//Close the input file
	inFile.close();

//Close the output file
	outFile.close();
	
	return 0;
}//end main