#include <stdio.h>
#include <bits/stdc++.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include<vector>  

using namespace std;


/*
	**Constants**
	
	FILE_NAME = to easily change file name
	SEAT_COLUMN = since its given i created a constant for this value
	SEAT_ROW = since its given i created a constant for this value
	MAX_INPUT = possible maximum input in this program
	ROW_ALPHA = it is a list of indicator for row of seats
	STANDARD_INPUT = it is for all the possible input for location of seats

*/

const string FILE_NAME = "reservation.txt";
const int SEAT_COLUMN = 4;
const int SEAT_ROW = 20;
const int MAX_INPUT = 100;
const char ROW_ALPHA[20] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T'};
const string STANDARD_INPUT[80] = { "A1",  "A2",  "A3",  "A4",
									"B1",  "B2",  "B3",  "B4",
									"C1",  "C2",  "C3",  "C4",
									"D1",  "D2",  "D3",  "D4",
									"E1",  "E2",  "E3",  "E4",
									"F1",  "F2",  "F3",  "F4",
									"G1",  "G2",  "G3",  "G4",
									"H1",  "H2",  "H3",  "H4",
									"I1",  "I2",  "I3",  "I4",
									"J1",  "J2",  "J3",  "J4",
									"K1",  "K2",  "K3",  "K4",
									"L1",  "L2",  "L3",  "L4",
									"M1",  "M2",  "M3",  "M4",
									"N1",  "N2",  "N3",  "N4",
									"O1",  "O2",  "O3",  "O4",
									"P1",  "P2",  "P3",  "P4",
									"Q1",  "Q2",  "Q3",  "Q4",
									"R1",  "R2",  "R3",  "R4",
									"S1",  "S2",  "S3",  "S4",
									"T1",  "T2",  "T3",  "T4"};
									
/*
	**Class Seat**
	
	status = it indicates the availability of the seat
	column = it holds the value of which column is seat located
	row = it holds the value of which row is seat located
	location = it holds a alphanumeric value which combination of row & column


*/									
class Seat {
	public:
		bool status;
		int column;
		char row;
		string location;
};


/*
	**Functions**
	
	void save_reservation(Seat seats[SEAT_ROW][SEAT_COLUMN]) = a function that saves the changes done by the user to the existing file. eg. cancellation of reservations
	void load_reservation(Seat seats[SEAT_ROW][SEAT_COLUMN]) = a function that loads the existing data in the FILE_NAME.
	void set_default(Seat seats[SEAT_ROW][SEAT_COLUMN]) = a function that set the default value of seats. It runs if the FILE_NAME did not exist.
	void display_seats(Seat seats[SEAT_ROW][SEAT_COLUMN]) = a function that display seats in 2D-matrix format. 20 x 4.
	void display_menu() = a function that display the commands and functions of the program.
	int choice_input() = a function that filters the input by the user.
	int reservation_input() = a function that filters the number of reservation that is needed by the user
	int read_reservation(string reservations[MAX_INPUT]) = a function that accepts the number of reservation of user 
	void create_reservation(Seat seats[SEAT_ROW][SEAT_COLUMN]) = a function that changes the seat status from 0 to 1
	bool seat_status(string reservations[MAX_INPUT], Seat seats[SEAT_ROW][SEAT_COLUMN], int input_length) = a function that return a bool type value if the seat/s location inputted is not taken.
	bool seat_input(string location) = a function that filter the seat location enter by the user. eg. A1 A2 A3
	bool cancel_status(string reservations[MAX_INPUT], Seat seats[SEAT_ROW][SEAT_COLUMN], int input_length) = a function that return a bool type value if the seat/s location inputted is taken. It is vice versa of seat_status()
	void cancel_reservation(Seat seats[SEAT_ROW][SEAT_COLUMN]) = a function that changes the seat status from 1 to 0
	int transfer_input(string target[MAX_INPUT], int input_length) = a function that filter the seats that are needed to transfer and its destination	
	void transfer_reservation(Seat seats[SEAT_ROW][SEAT_COLUMN]) = a function that transfer the taken seats to non-taken seats. In simple terms, we change the value of initial seats and transfer it to final seats. eg. A1 --> S1, A1 will become false and S1 become true.
	bool confirmation(string prompt) = a function that confirm the action done by the user


*/	

void save_reservation(Seat seats[SEAT_ROW][SEAT_COLUMN]);
void load_reservation(Seat seats[SEAT_ROW][SEAT_COLUMN]);
void set_default(Seat seats[SEAT_ROW][SEAT_COLUMN]);
void display_seats(Seat seats[SEAT_ROW][SEAT_COLUMN]);
void display_menu();
int choice_input();
int reservation_input();
int read_reservation(string reservations[MAX_INPUT]);
void create_reservation(Seat seats[SEAT_ROW][SEAT_COLUMN]);
bool seat_status(string reservations[MAX_INPUT], Seat seats[SEAT_ROW][SEAT_COLUMN], int input_length);
bool seat_input(string location);
bool cancel_status(string reservations[MAX_INPUT], Seat seats[SEAT_ROW][SEAT_COLUMN], int input_length);
void cancel_reservation(Seat seats[SEAT_ROW][SEAT_COLUMN]);	
int transfer_input(string target[MAX_INPUT], int input_length);	
void transfer_reservation(Seat seats[SEAT_ROW][SEAT_COLUMN]);		
bool confirmation(string prompt);					  


/*
	Main:
	
		- First, I created a 2D-array that contains object of Seat. Then, I created a file stream object that opens the file that stores the record of the seat reservations.
		  If the file is not exist or file exist but empty, we can set the default_value of the seat.status which is false. If the file is exist and not empty, we can load the file and save it to 2D array that we've created before.
		  
		  After setting up, I've created a game loop or a loop where the whole program circulates. Inside the game loop, it displays the commands and the functions that are needed to the program.
		  
		  [1] Display Seats - it displays the seats in 20 x 4 2D-matrix format. For simpler design, I used X as indicator if the seat is not taken and O if it is taken.
		  [2] Reserve Seats - it creates a reservation inside the array. If the specific index has status value of 0, it can be process. It is also accepts multiple input from the user.
		  [3] Cancel Seats - -it removes the reservation on specific number of seats. If the seats are taken or their value is 1 then it can be process
		  [4] Transfer Seats - it transfers the specific number of taken seats into the same number of seats with 0 status value.
		  [0] Exit - it terminates the program and it saves the progress of the program into text file.
		  
		  



*/


int main(){
	
	Seat seats[SEAT_ROW][SEAT_COLUMN];
	
	fstream save_file;
	save_file.open(FILE_NAME);
	
	save_file.seekp(0, ios::end);
	int spot = save_file.tellg();
		
	
	if(!save_file || spot == 0){
		set_default(seats);
	}
	else{
		load_reservation(seats);
	}

	
	while(true){
		
		display_menu();
		switch(choice_input()){
			
			
			case 1:
				display_seats(seats);
				break;
			case 2:
				create_reservation(seats);
				break;
			case 3:
				cancel_reservation(seats);
				break;
			case 4:
				transfer_reservation(seats);
				break;
			case 0:
				cout << endl <<endl << "Thank you for using our system!";
				save_reservation(seats);
				exit(0);
				
			default:
				cout << "Output: Out of range." << endl;
				break;
			
		}
		
	
	}

	
	
	return 0;
	
}


void save_reservation(Seat seats[SEAT_ROW][SEAT_COLUMN]){
	
	ofstream file(FILE_NAME);
	
	for(int i = 0; i < SEAT_ROW; i++){
			
		for(int j = 0; j < SEAT_COLUMN; j++){
			file << seats[i][j].status << " ";
		}
		file << "\n";
	}
	file.close();
}

void load_reservation(Seat seats[SEAT_ROW][SEAT_COLUMN]){
	ifstream save_file(FILE_NAME);
	
	for(int i = 0; i < SEAT_ROW; i++){
			
		for(int j = 0; j < SEAT_COLUMN; j++){
			seats[i][j].column = j + 1;
			seats[i][j].location = ROW_ALPHA[i] + to_string(j+1);
			seats[i][j].row = ROW_ALPHA[i];
			save_file >> seats[i][j].status;
		}
	}
	save_file.close();
	
}


void set_default(Seat seats[SEAT_ROW][SEAT_COLUMN]){

	for(int i = 0; i < SEAT_ROW; i++){
		for(int j = 0; j < SEAT_COLUMN; j++){
			seats[i][j].column = j + 1;
			seats[i][j].location = ROW_ALPHA[i] + to_string(j+1);
			seats[i][j].row = ROW_ALPHA[i];
			seats[i][j].status = false;
		}
	}
}


void display_seats(Seat seats[SEAT_ROW][SEAT_COLUMN]){
	cout << "\nSeats Overview" << endl <<endl;
	cout << "\t      COLUMN" << endl;
	cout << "\t  1    2    3    4   " << endl << endl;
	
	
	for(int i = 0; i < SEAT_ROW; i++){
		cout << "ROW" << right << setw(3) << seats[i][0].row; ;
		for(int j = 0; j < SEAT_COLUMN; j++){
			if(seats[i][j].status){
				cout << "    O";
				continue;
			}
			cout << "    X";
			
		}
		cout << endl;
	}
	cout << endl <<endl;
}



void display_menu(){
	
	cout << "Airline Seat Reservation System" << endl << endl;
	cout << "[1] Display Seats" << endl;
	cout << "[2] Reserve Seat/s" << endl;
	cout << "[3] Cancel Reservation/s" << endl;
	cout << "[4] Transfer Seat/s" << endl;
	cout << "[0] Exit" << endl << endl;
	

	
}


int choice_input(){
	
	
	char buffer[100];
	cout << "Choice: ";
	int n = scanf("%s", buffer);
	if (n < 0 || n > 4){
		
		cout << "Output: Out of range." << endl;
		choice_input();
	}

	
	char *end;
	long choice = strtol(buffer, &end, 10); 
	if (end == buffer || *end != '\0' || errno == ERANGE){
		cout << "Output: Invalid Input!" << endl;
		choice_input();
	}

	
	return choice;
}


int reservation_input(){
	
	
	char buffer[100];
	cout << "How many do you want? ";
	int n = scanf("%s", buffer);
	if (n < 0 || n > MAX_INPUT){
		
		cout << "Output: Out of range." << endl;
		reservation_input();
	}

	
	char *end;
	long choice = strtol(buffer, &end, 10); 
	if (end == buffer || *end != '\0' || errno == ERANGE){
		cout << "Output: Invalid Input!" << endl;
		reservation_input();
	}

	
	return choice;
}

bool seat_input(string location){
	if (find(begin(STANDARD_INPUT), std::end(STANDARD_INPUT), location) != std::end(STANDARD_INPUT)){
		return true;
	}
	return false;
}

int read_reservation(string reservations[MAX_INPUT]){
	
	int input_length;
	string temp;
	int i = 0;
	
	input_length = reservation_input();
	
	while(i < input_length){
		cout << "Enter the location of seats: ";
		cin >> temp;
		temp[0] = toupper(temp[0]);
		

		if(seat_input(temp)){
			reservations[i] = temp;
			i++;
		}
		else{
			cout << "Output: " << temp << " is invalid!" << endl;
		}
	}

	sort(reservations, reservations + input_length);
	
	return input_length;

}

bool seat_status(string reservations[MAX_INPUT], Seat seats[SEAT_ROW][SEAT_COLUMN], int input_length){
	
	int k = 0;
	int i = 0;
	int count_error = 0;
	vector<string> not_available; 
	
	while(k < input_length){
		for(int j = 0; j < SEAT_COLUMN; j++){
			if((reservations[k] == seats[i][j].location) && (seats[i][j].status == false)){
				k++;
			}
			else if((reservations[k] == seats[i][j].location) && (seats[i][j].status == true)){
				not_available.push_back(reservations[k]);
				k++;
				count_error++;
				
			}
		}
		i++;
	}
		
	if(count_error > 0){
		
		//Printing not available
		for(vector<string>::iterator i = not_available.begin(); i != not_available.end(); ++i){
			cout << "Output: " << *i << " is already taken! "<< endl;
		}
		
		return false;
	}
	return true;
}

void create_reservation(Seat seats[SEAT_ROW][SEAT_COLUMN]){
	string reservations[MAX_INPUT];
	int input_length = read_reservation(reservations);
	
	bool availability = seat_status(reservations,seats,input_length);
	
	int k = 0;
	int i = 0;
	
	string origin("");
	
	for (int i = 0; i < input_length; i++){
		if(i + 1 == input_length){
			origin +=  reservations[i];
		}
		else{
			origin +=  reservations[i] + ",";
		}
	}
	
	string prompt = "Do you want to make a reservation at [" + origin + "]? [Y/N]: ";

	
	
	if (availability){
		if(!confirmation(prompt)){
			cout << "Output: Returning to menu." <<endl<<endl;
			return;
		}
		while(k < input_length){
			for(int j = 0; j < SEAT_COLUMN; j++){
				if(reservations[k] == seats[i][j].location){
					seats[i][j].status = true;
					k++;
				}
				
			}
			i++;
		}
		cout << "Output: Reservation success!" << endl;
		cout << "Output: Returning to menu." <<endl<<endl;
	}
	else{
		cout << "Output: Reservation not available!" << endl;
		cout << "Output: Returning to menu." <<endl<<endl;
	}
	
	
}
bool cancel_status(string reservations[MAX_INPUT], Seat seats[SEAT_ROW][SEAT_COLUMN], int input_length){
	
	int k = 0;
	int i = 0;
	int count_error = 0;
	vector<string> not_available; 
	
	while(k < input_length){
		for(int j = 0; j < SEAT_COLUMN; j++){
			
			if((reservations[k] == seats[i][j].location) && (seats[i][j].status == true)){
				k++;
				
			}
			
			else if((reservations[k] == seats[i][j].location) && (seats[i][j].status == false)){

				not_available.push_back(reservations[k]);
				k++;
				count_error++;
			}
		}
		i++;
	}
		
	if(count_error > 0){
		
		//Printing not available
		for(vector<string>::iterator i = not_available.begin(); i != not_available.end(); ++i){
			cout << "Output: " << *i << " has empty reservation! "<< endl;
		}
		
		return false;
	}
	return true;
}

void cancel_reservation(Seat seats[SEAT_ROW][SEAT_COLUMN]){
	string remove[MAX_INPUT];
	int input_length_remove = read_reservation(remove);
	
	bool availability = cancel_status(remove,seats,input_length_remove);
	
	int k = 0;
	int i = 0;
	
	string origin("");
	
	for (int i = 0; i < input_length_remove; i++){
		if(i + 1 == input_length_remove){
			origin +=  remove[i];
		}
		else{
			origin +=  remove[i] + ",";
		}
		
	}
	
	string prompt = "Do you want to cancel you reservation at [" + origin + "]? [Y/N]: ";
	
	if (availability){
		if(!confirmation(prompt)){
			cout << "Output: Returning to menu." <<endl<<endl;
			return;
		}
		while(k < input_length_remove){
			for(int j = 0; j < SEAT_COLUMN; j++){
				if(remove[k] == seats[i][j].location){
					seats[i][j].status = false;
					k++;
				}
				
			}
			i++;
		}
		cout << "Output: Cancellation success!" << endl;
		cout << "Output: Returning to menu." <<endl<<endl;
	}
	else{
		cout << "Output: The seat is empty!" << endl;
		cout << "Output: Returning to menu." <<endl<<endl;
	}
		
}



int transfer_input(string target[MAX_INPUT], int input_length){
	string temp;
	int i = 0;
	
	
	while(i < input_length){
		cout << "Enter the location where you want to transfer: ";
		cin >> temp;
		temp[0] = toupper(temp[0]);
		

		if(seat_input(temp)){
			target[i] = temp;
			i++;
		}
		else{
			cout << "Output: " << temp << " is invalid!" << endl;
		}
	}

	sort(target, target + input_length);
	
	return input_length;
}



void transfer_reservation(Seat seats[SEAT_ROW][SEAT_COLUMN]){
	string initial_seats[MAX_INPUT];
	string target_seats[MAX_INPUT];
	
	int input_length_origin = read_reservation(initial_seats);
	int input_length_destination = transfer_input(target_seats,input_length_origin);
	
	bool availability_origin = cancel_status(initial_seats,seats,input_length_origin);
	bool availability_destination = seat_status(target_seats,seats,input_length_destination);
	
	
	int k = 0;
	int l = 0;
	int i = 0;
	
	string origin(""), target("");
	
	for (int i = 0; i < input_length_origin; i++){
		if(i + 1 == input_length_origin){
			origin +=  initial_seats[i];
			target += target_seats[i];
		}
		else{
			origin +=  initial_seats[i] + ",";
			target += target_seats[i] + ",";
		}
		
	}
	
	string prompt = "Do you want to transfer [" + origin + "] --> [" + target + "]? [Y/N]: ";

	
	if (availability_origin && availability_destination){
			
		if(!confirmation(prompt)){
			cout << "Output: Returning to menu." <<endl<<endl;
			return;
		}
		while(k < input_length_origin || l < input_length_destination){
			for(int j = 0; j < SEAT_COLUMN; j++){
				if(initial_seats[k] == seats[i][j].location){
					seats[i][j].status = false;
					k++;
				}
				if(target_seats[l] == seats[i][j].location){
					seats[i][j].status = true;
					l++;
				}
				
			}
			i++;
		}
		cout << "Output: Transfer success!" << endl;
		cout << "Output: Returning to menu." <<endl<<endl;
	}
	else{
		cout << "Output: Transfer not available!" << endl;
		cout << "Output: Returning to menu." <<endl<<endl;
	}
	
	
	
	
}


bool confirmation(string prompt){
	char confirm;
	while(true){
		cout << prompt;
		cin >> confirm;
		if(toupper(confirm) == 'Y'){
			return true;
		}
		else if(toupper(confirm) == 'N'){
			break;
		}
		else{
			cout << "Invalid Input!" <<endl;
		}
	}
	return false;
	
	
}
	
