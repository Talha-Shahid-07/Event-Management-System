#include <iostream>	
#include <string>
#include <fstream>
using namespace std;

string LINE = "==========================================";

struct ticket
{
	double premiumTicketPrice, basicTicketPrice;
};

struct event
{
	string name, Mname, place, seats, date, ID, category;
	int time;
	ticket tickets;
};

struct attendee
{
	string name, phone_number, banking_info;
	event bookedEvents;
};

void admin_dashboard();
void manager_dashboard();
void customer_dashboard();

void add_event();
void modify_event();
void delete_event();
void list_of_events();
void Remove(int op);

void ticketBooking();
void delete_booking();
void viewattendeelist();
string view_user_booking();

void ask_login_admin();
void ask_login_manager();
void ask_login_user();
void Register(int op);
void Login(int op);
bool isUsernameTakenbymanager(const string& username);
bool isUsernameTakenbyuser(const string& username);
bool verification(string username, string password, int op);
bool event_is_booked(string id);


int main()
{
	ofstream admin_file;
	admin_file.open("admin.txt");
	if (!admin_file.is_open()) {
		cout << "Cannot create Admin File!";
		return 1;
	}
	admin_file << "admin password";
	admin_file.close();

	int login = 0;
	do {
		system("cls");
		cout << "\t\t" << LINE << "\n\t\t\tEvent Management System\n" << "\t\t" << LINE << endl;
		cout << "Hello there! Welcome to the Event Management System!" << endl;

		cout << "Please login to access the full features of this system!" << endl;
		cout << "1. Admin\n2. Manager \n3. User\n4. Exit\n--> "; cin >> login;
		if (cin.fail()) {
			// If the input is not an integer, clear the error flag and discard the input
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << LINE << "\nPlease enter an integer!\n" << LINE << endl;
			system("pause");
			continue;  // Restart the loop
		}
		system("cls");

		switch (login)
		{
		case 1:
		{
			ask_login_admin();
			break;
		}
		case 2:
		{
			ask_login_manager();
			break;
		}
		case 3:
			ask_login_user();
			break;
		case 4:
			break;
		default:
		{
			cout << LINE << "\nSelected option not Found! Please pick again...\n" << LINE << endl;
			system("pause");
			break;
		}
		}
	} while (login != 4);
}

void add_event()
{
	ticket tickets;
	event new_event;

	fstream file;
	file.open("Event Information.txt", ios::app);
	if (!file.is_open()) {
		system("cls");
		cout << LINE << "Event information file not opened!" << LINE << endl;
		file.close();
		system("pause");
		return;
	}

	cout << LINE << "\n     Once booked, cannot be deleted!\n" << LINE << endl;
	cout << "Enter Event ID(Cannot be the same as Previous ID's): "; cin >> new_event.ID;
	string id = "Event ID: " + new_event.ID;
	ifstream idcheck;
	idcheck.open("Event Information.txt");
	if (!idcheck.is_open()) {
		system("cls");
		cout << LINE << "Event information file not opened!" << LINE << endl;
		system("pause");
		return;
	}
	string line;
	while (getline(idcheck, line)) {
		if (line.find(id) != string::npos) {
			system("cls");
			cout << LINE << "Entered ID is already reserved for another event!" << LINE << endl;
			system("pause");
			return;
		}
		else
			continue;
	}
	cout << "Enter Manager Name: "; cin.ignore(); getline(cin, new_event.Mname);
	cout << "Enter Event Name: "; cin.ignore(); getline(cin, new_event.name);
	do {
		cout << "Enter Event Time (24 hr) Format: ";
		cin >> new_event.time;
		if (new_event.time < 0 || new_event.time > 24) {
			system("cls");
			cout << LINE << "Invalid format! Please re-enter..." << LINE << endl;
		}
		else {
			break;
		}
	} while (new_event.time < 0 || new_event.time > 24);

	cout << "Enter Event category: "; cin.ignore(); getline(cin, new_event.category);
	string date;
	do {
		cout << "Enter Event Date (DD/MM/YYYY) Format (Current Year): ";
		cin >> date;
		if (date.length() != 10 || date[2] != '/' || date[5] != '/' || date[6] != '2' || date[7] != '0' || date[8] != '2' || date[9] != '4') {
			system("cls");
			cout << LINE << "Invalid format! Please re-enter..." << LINE << endl;
		}
	} while (date.length() != 10 || date[2] != '/' || date[5] != '/');
	new_event.date = date;
	cout << "Enter Event Place: "; cin.ignore(); getline(cin, new_event.place);
	cout << "Enter the number of seats available: "; cin >> new_event.seats;
	cout << "Enter the Price for Basic tickets: "; cin >> tickets.basicTicketPrice;
	cout << "Enter the Price for Premium tickets: "; cin >> tickets.premiumTicketPrice;

	//Storing event information
	file << "\nEvent ID: " << new_event.ID << "\nManager Name: " << new_event.Mname << "\nEvent Name: " << new_event.name << "\nEvent Category: " << new_event.category << "\nEvent Time: " << new_event.time << "\nEvent Date: " << new_event.date << "\nEvent place: " << new_event.place << "\nNumber of seats available: " << new_event.seats << "\nBasic Ticket Price: " << tickets.basicTicketPrice << "\nPremium Ticket Price: " << tickets.premiumTicketPrice << "\n" << LINE << endl;
	file.close();

	system("cls");
	cout << LINE << "\nEvent added successfully!\n" << LINE << endl;
	system("pause");
}

void modify_event()
{
	ifstream read;
	ofstream temp;
	read.open("Event Information.txt");
	temp.open("temp.txt");
	if (!read.is_open() || !temp.is_open()) {
		system("cls");
		cout << LINE << "Error opening or creating files!" << LINE << endl;
		system("pause");
		return;
	}

	if (read.peek() == ifstream::traits_type::eof()) {
		system("cls");
		cout << LINE << "No events to modify!" << LINE << endl;
		system("pause");
		return;
	}

	list_of_events();

	string old, New;
	cout << "Enter the Information you want to update(Case Sensitive): "; cin.ignore(); getline(cin, old);
	cout << "Enter the Information you want to update it with: "; getline(cin, New);

	string line;
	bool found = false;
	while (getline(read, line)) {
		if (line.find(old) != string::npos) {
			found = true;
			line.replace(line.find(old), old.length(), New);
		}
		temp << line << endl;
	}
	read.close();
	temp.close();

	remove("Event Information.txt");
	rename("temp.txt", "Event Information.txt");
	if (!found) {
		system("cls");
		cout << LINE << "Event information not found!" << LINE << endl;
		system("pause");
	}
	else {
		cout << LINE << "\nEvent Information Updated Successfully!\n" << LINE << endl;
		system("pause");
	}
}

void delete_event()
{
	list_of_events();

	string ID, id;
	cout << LINE << "\nEnter the ID of the event you want to delete: "; cin >> id;
	ID = "Event ID: " + id;

	if (event_is_booked(ID)) {
		return;
	}

	ifstream read;
	ofstream temp;
	read.open("Event Information.txt");
	temp.open("temp.txt");
	if (!read.is_open() || !temp.is_open()) {
		system("cls");
		cout << LINE << "Error opening or creating files!" << LINE << endl;
		system("pause");
		return;
	}

	if (read.peek() == ifstream::traits_type::eof()) {
		system("cls");
		cout << LINE << "No events to delete!" << LINE << endl;
		system("pause");
		return;
	}

	string line;
	while (getline(read, line)) {
		if (line.find(ID) != string::npos) {
			while (getline(read, line) && line != LINE) {}
		}
		else
			temp << line << endl;
	}
	read.close();
	temp.close();

	remove("Event Information.txt");
	rename("temp.txt", "Event Information.txt");
	system("cls");

	cout << LINE << "\nEvent Information Deleted Successfully!\n" << LINE << endl;
	system("pause");
}

void list_of_events()
{
	ifstream read;
	read.open("Event Information.txt");
	if (!read.is_open()) {
		system("cls");
		cout << LINE << "Error opening event information file!" << LINE << endl;
		system("pause");
		return;
	}

	if (read.peek() == ifstream::traits_type::eof()) {
		system("cls");
		cout << LINE << "No events to display!" << LINE << endl;
		system("pause");
		return;
	}
	system("cls");
	cout << LINE << "List of events:" << LINE << endl;
	string line;
	while (getline(read, line)) // getline(cin,line);
	{
		if (line != LINE) {
			cout << line << endl;
		}
		else
			cout << LINE << endl;
	}
	read.close();
	system("pause");
}

void ticketBooking() {

	ofstream ticketFile;
	ifstream read;
	read.open("Event Information.txt");
	ticketFile.open("Ticketing Information.txt", ios::app);
	if (!read.is_open() || !ticketFile.is_open()) {
		system("cls");
		cout << LINE << "Error opening or creating files" << LINE << endl;
		system("pause");
		return;
	}
	// Check if there are events available
	if (read.peek() == ifstream::traits_type::eof()) {
		system("cls");
		cout << LINE << "No events to book!" << LINE << endl;
		system("pause");
		return;
	}
	read.close();

	list_of_events();

	string ID;
	cout << LINE << "\nEnter the ID of the event you want to book a ticket for: ";
	cin >> ID;

	read.open("Event Information.txt");

	string line;
	bool found = false;
	while (getline(read, line)) {
		if (line.find("Event ID: " + ID) != string::npos) {
			// Event with the specified ID found
			found = true;
			break;
		}
	}
	if (!found) {
		system("cls");
		cout << LINE << "Invalid ID number! Booking cancelled..." << LINE << endl;
		system("pause");
		return;
	}

	// Create a new attendee
	attendee newAttendee;

	// Get attendee information
	cout << "Enter your name: ";
	cin.ignore(); getline(cin, newAttendee.name);

	cout << "Enter your phone number: ";
	cin >> newAttendee.phone_number;

	cout << "Enter your Banking Details: ";
	cin.ignore(); getline(cin, newAttendee.banking_info);

	// Prompt the user to select a ticket category
	int ticketCategory;
	cout << "Select the ticket category:\n1. Premium\n2. Basic\n--> ";
	cin >> ticketCategory;

	// Validate the ticket category
	if (ticketCategory < 1 || ticketCategory > 2) {
		system("cls");
		cout << LINE << "Invalid ticket category! Booking cancelled..." << LINE << endl;
		system("pause");
		return;
	}
	ticketFile << "\n";
	ticketFile << "Attendee Name: " << newAttendee.name << "\n";
	for (int i = 0; i < 2; i++) {
		getline(read, line);
		ticketFile << line << "\n";
	}
	ticketFile << "Phone Number: " << newAttendee.phone_number << "\n";
	ticketFile << "Banking Information: " << newAttendee.banking_info << "\n";
	ticketFile << "Ticket Category: " << (ticketCategory == 1 ? "Premium" : "Basic") << "\n";
	ticketFile << LINE << endl;
	ticketFile.close();

	// Display a confirmation message
	cout << LINE << "\nTicket booked successfully! Thank you for registering " << newAttendee.name << "!\n" << LINE << endl;
	system("pause");
}

void delete_booking()
{
	string delete_name = view_user_booking();

	if (delete_name == "false")
		return;

	ifstream read;
	ofstream temp;
	read.open("Ticketing Information.txt");
	temp.open("temp.txt");
	if (!read.is_open() || !temp.is_open()) {
		system("cls");
		cout << LINE << "Error opening or creating files!" << LINE << endl;
		system("pause");
		return;
	}

	if (read.peek() == ifstream::traits_type::eof()) {
		system("cls");
		cout << LINE << "No bookings to delete!" << LINE << endl;
		system("pause");
		return;
	}

	string check, name_of_event;
	bool found = false;
	cout << LINE << "\nEnter the Name of the event you want to cancel your booking for: "; getline(cin, name_of_event);
	check = "Event Name: " + name_of_event;


	string line;
	bool foundEvent = false;  // Flag to indicate if the event is found

	while (getline(read, line)) {
		if (line.find(check) != string::npos) {
			foundEvent = true;
			temp << line << endl;
			while (getline(read, line) && line != LINE) {
				if (line.find("Attendee Name: " + delete_name) != string::npos) {
					while (getline(read, line) && line != LINE) {}
					found = true;
					break;
				}
				else
					temp << line << endl;
			}
		}
		else {

			temp << line << endl;
		}
	}
	read.close();
	temp.close();

	remove("Ticketing Information.txt");
	rename("temp.txt", "Ticketing Information.txt");

	read.open("Ticketing Information.txt");
	temp.open("temp.txt");

	string name;
	while (getline(read, name)) {
		if (name.find("Attendee Name: " + delete_name) != string::npos) {
			found = true;
			// Skip the line by not writing it to the temp file
			while (getline(read, line) && line != LINE) {}
			continue;
		}
		temp << name << endl;  // Write the line to the temp file
	}

	read.close();
	temp.close();

	remove("Ticketing Information.txt");
	rename("temp.txt", "Ticketing Information.txt");

	system("cls");
	if (!found) {
		system("cls");
		cout << LINE << "\nBooking not found!\n" << LINE << endl;
		system("pause");
	}
	else {
		system("cls");
		cout << LINE << "\nEvent Booking Cancelled Successfully!\n" << LINE << endl;
		system("pause");
	}
}

void viewattendeelist() {
	ifstream read;
	read.open("Ticketing Information.txt");
	if (!read.is_open()) {
		system("cls");
		cout << LINE << "Error opening or creating files!" << LINE << endl;
		system("pause");
		return;
	}

	if (read.peek() == ifstream::traits_type::eof()) {
		system("cls");
		cout << LINE << "No attendee's to display!" << LINE << endl;
		system("pause");
		return;
	}
	system("cls");
	cout << LINE << "List of Attendee's" << LINE << endl;
	string line;
	while (getline(read, line))
	{
		if (line != LINE)
			cout << line << endl;
		else
			cout << LINE << endl;
	}
	read.close();
	system("pause");
}

string view_user_booking() {
	ifstream read;
	read.open("Ticketing Information.txt");
	if (!read.is_open()) {
		system("cls");
		cout << LINE << "Error opening or creating files!" << LINE << endl;
		system("pause");
		return "Error opening or creating files!";
	}

	if (read.peek() == ifstream::traits_type::eof()) {
		system("cls");
		cout << LINE << "No events to display!" << LINE << endl;
		system("pause");
		return "No events to display!";
	}
	read.close();
	string name, line;
	bool found = false;
	cout << "Enter the name you registered with in the event: "; cin.ignore(); getline(cin, name);

	read.open("Ticketing Information.txt");
	while (getline(read, line)) {
		if (line.find("Attendee Name: " + name) != string::npos) {
			found = true;
			while (getline(read, line) && line != LINE) {
				cout << line << endl;
			}
			cout << LINE << endl;
		}
	}
	read.close();
	if (!found) {
		system("cls");
		cout << LINE << "\nAttendee not Found!\n" << LINE << endl;
		system("pause");
		return "false";
	}
	system("pause");
	return name;
}

void ask_login_admin()
{
	int op;
	do {
		system("cls");
		cout << "\t" << LINE << "\n\t\t\tSign In\n" << "\t" << LINE << endl;

		cout << "Welcome Mr. Admin! Please Login to continue:\n1.Login \n2.Exit\n--> "; cin >> op;
		if (cin.fail()) {
			// If the input is not an integer, clear the error flag and discard the input
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << LINE << "\nPlease enter an integer!\n" << LINE << endl;
			system("pause");
			continue;  // Restart the loop
		}
		switch (op)
		{
		case 1:
			Login(3);
			break;
		case 2:
			break;
		default:
		{
			cout << LINE << "\nSelected option not Found! Please pick again...\n" << LINE << endl;
			system("pause");
			break;
		}
		}
	} while (op != 2);

}

void ask_login_manager()
{
	int op;
	do {
		system("cls");
		cout << "\t" << LINE << "\n\t\t\tSign In\n" << "\t" << LINE << endl;

		cout << "Welcome Mr. Manager! Please select an option to continue: \n1.Register \n2.Login \n3.Exit\n--> "; cin >> op;
		if (cin.fail()) {
			// If the input is not an integer, clear the error flag and discard the input
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << LINE << "\nPlease enter an integer!\n" << LINE << endl;
			system("pause");
			continue;  // Restart the loop
		}
		switch (op)
		{
		case 1:
			Register(1);
			break;
		case 2:
			Login(1);
			break;
		case  3:
			break;
		default:
		{
			cout << LINE << "\nSelected option not Found! Please pick again...\n" << LINE << endl;
			system("pause");
			break;
		}
		}
	} while (op != 3);

}

void ask_login_user()
{
	int op;
	do {
		system("cls");
		cout << "\t" << LINE << "\n\t\t\tSign In\n" << "\t" << LINE << endl;

		cout << "Welcome! Please select an option to continue: \n1.Register \n2.Login \n3.Exit\n--> "; cin >> op;
		if (cin.fail()) {
			// If the input is not an integer, clear the error flag and discard the input
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << LINE << "\nPlease enter an integer!\n" << LINE << endl;
			system("pause");
			continue;  // Restart the loop
		}
		switch (op)
		{
		case 1:
			Register(2);
			break;
		case 2:
			Login(2);
			break;
		case 3:
			break;
		default:
		{
			cout << LINE << "\nSelected option not Found! Please pick again...\n" << LINE << endl;
			system("pause");
			break;
		}
		}
	} while (op != 3);

}

bool isUsernameTakenbymanager(const string& username) {
	string storedname, storedpassword;
	fstream credentials;
	credentials.open("manager.txt", ios::in);
	while (credentials >> storedname >> storedpassword) {
		if (storedname == username) {
			credentials.close();
			return true; // Username exists
		}
	}
	credentials.close();
	return false; // Username doesn't exist
}

bool isUsernameTakenbyuser(const string& username) {
	string storedname, storedpassword;
	fstream credentials;
	credentials.open("user.txt", ios::in);
	while (credentials >> storedname >> storedpassword) {
		if (storedname == username) {
			credentials.close();
			return true; // Username exists
		}
	}
	credentials.close();
	return false; // Username doesn't exist
}

void Register(int op)
{
	cout << "\t" << LINE << "\n\t\t\tRegistration\n" << "\t" << LINE << endl;

	string username, password;
	bool istaken = false, registered = false;
	switch (op) {
	case 1: {
		do {
			cout << "Enter your Username: " << endl; cin >> username;
			if (isUsernameTakenbymanager(username)) {
				system("cls");
				cout << LINE << "\nUsername is already taken! Please choose a different one...\n" << LINE << endl;
				system("pause");
				istaken = true;
				return;
			}
		} while (istaken);
		cout << "Enter your Password(minimum 6 and maximum 10 characters): " << endl; cin >> password;
		if (password.length() >= 6 && password.length() <= 10) {
			fstream credentials;
			credentials.open("manager.txt", ios::app);
			if (!credentials.is_open())
			{
				system("cls");
				cout << LINE << "Error! Credentials file not opened..." << LINE << endl;
				credentials.close();
				return;
			}
			credentials << "\n" << username << " " << password;
			credentials.close();
			registered = true;
		}
		else
		{
			system("cls");
			cout << LINE << "\nPlease enter password in the specfied limit!\n" << LINE << endl;
		}
		break;
	}
	case 2: {
		do {
			cout << "Enter your Username: " << endl; cin >> username;
			if (isUsernameTakenbyuser(username)) {
				system("cls");
				cout << LINE << "\nUsername is already taken! Please choose a different one...\n" << LINE << endl;
				system("pause");
				istaken = true;
				return;
			}
		} while (istaken);
		cout << "Enter your Password(minimum 6 and maximum 10 characters): " << endl; cin >> password;
		if (password.length() >= 6 && password.length() <= 10) {
			fstream credentials;
			credentials.open("user.txt", ios::app);
			if (!credentials.is_open())
			{
				system("cls");
				cout << LINE << "Error! Credentails file not opened!" << LINE << endl;
				credentials.close();
				return;
			}
			credentials << "\n" << username << " " << password;
			credentials.close();
			registered = true;
		}
		else
		{
			system("cls");
			cout << LINE << "\nPlease enter the password within the specified limit!\n" << LINE << endl;
			system("pause");
		}
		break;
	}
	}
	if (registered)
		cout << LINE << "Registration Successfull!" << LINE << endl;

	system("pause");
	system("cls");
	return;
}

void Login(int op)
{
	cout << "\t" << LINE << "\n\t\t\tSign In\n" << "\t" << LINE << endl;

	string username, password;
	switch (op) {
	case 1: {
		cout << "Welcome Mr.Manager! Please enter your" << endl;
		cout << "Username: "; cin >> username;
		cout << "Password: "; cin >> password;

		if (verification(username, password, 1)) {
			cout << LINE << "\nLogged in Successfully!\n" << LINE << endl;
			system("pause");
			manager_dashboard();
		}
		else
		{
			cout << LINE << "\nInvalid Credentials!\n" << LINE << endl;
			system("pause");
			return;
		}
		break;
	}
	case 2: {
		cout << "Welcome! Please enter your" << endl;
		cout << "Username: "; cin >> username;
		cout << "Password: "; cin >> password;

		if (verification(username, password, 2)) {
			cout << LINE << "\nLogged in Successfully!\n" << LINE << endl;
			system("pause");
			customer_dashboard();
		}
		else
		{
			cout << LINE << "\nInvalid Credentials!\n" << LINE << endl;
			system("pause");
			return;
		}
		break;
	}
	case 3: {
		cout << "Welcome! Please enter your" << endl;
		cout << "Username: "; cin >> username;
		cout << "Password: "; cin >> password;

		if (verification(username, password, 3)) {
			cout << LINE << "\nLogged in Successfully!\n" << LINE << endl;
			system("pause");
			admin_dashboard();
		}
		else
		{
			cout << LINE << "\nInvalid Credentials!\n" << LINE << endl;
			system("pause");
			return;
		}
		break;
	}
	}
}

bool verification(string username, string password, int op)
{
	switch (op) {
	case 1:
	{
		string storedname, storedpassword;
		fstream credentials;
		credentials.open("manager.txt", ios::in);
		if (!credentials.is_open())
		{
			cout << "Error! Cannot open the file." << endl;
			credentials.close();
			return false;
		}
		while (credentials >> storedname >> storedpassword)
		{
			if (storedname == username && storedpassword == password)
			{
				credentials.close();
				return true;
			}
		}
		credentials.close();
		return false;
		break;
	}
	case 2:
	{
		string storedname, storedpassword;
		fstream credentials;
		credentials.open("user.txt", ios::in);
		if (!credentials.is_open())
		{
			cout << "Error! Cannot open the file." << endl;
			credentials.close();
			return false;
		}
		while (credentials >> storedname >> storedpassword)
		{
			if (storedname == username && storedpassword == password)
			{
				credentials.close();
				return true;
			}
		}
		credentials.close();
		return false;
		break;
	}
	case 3:
	{
		string storedname, storedpassword;
		fstream credentials;
		credentials.open("admin.txt", ios::in);
		if (!credentials.is_open())
		{
			cout << "Error! Cannot open the file." << endl;
			credentials.close();
			return false;
		}
		while (credentials >> storedname >> storedpassword)
		{
			if (storedname == username && storedpassword == password)
			{
				credentials.close();
				return true;
			}
		}
		credentials.close();
		return false;
		break;
	}
	}
}

bool event_is_booked(string id)
{
	ifstream read, booked;
	read.open("Event Information.txt");
	booked.open("Ticketing Information.txt");
	if (!read.is_open() || !booked.is_open()) {
		system("cls");
		cout << LINE << "Error opening or creating files!" << LINE << endl;
		system("pause");
		return true;
	}

	if (read.peek() == ifstream::traits_type::eof()) {
		system("cls");
		cout << LINE << "No events to delete!" << LINE << endl;
		system("pause");
		return true;
	}
	read.close();
	read.open("Event Information.txt");
	string line, event_name;
	bool found = false;
	while (getline(read, line)) {
		if (line.find(id) != string::npos) {
			found = true;
			while (getline(read, line))
				if (line.find("Event Name: ") != string::npos) {
					event_name = line;
					break;
				}
			break;
		}
	}
	read.close();
	if (!found) {
		cout << LINE << "\nEvent not found!\n" << LINE << endl;
		system("pause");
		return true;
	}
	while (getline(booked, line)) {
		if (line == event_name) {
			cout << LINE << "\nEvent is booked! Deletion Cancelled...\n" << LINE << endl;
			system("pause");
			return true;
		}
	}
	booked.close();
	return false;
}

void admin_dashboard()
{
	int op;
	do {
		system("cls");
		cout << "\t" << LINE << "\n\t\t\tAdmin Dashboard\n" << "\t" << LINE << endl;
		cout << "Welocme Mr.Admin. What would you like to do today!" << endl;
		cout << "1. Show the list of available events \n2. Delete an event\n3. View attendee list.\n4. Remove Manager\n5. Remove User \n6. Exit\n--> "; cin >> op;
		if (cin.fail()) {
			// If the input is not an integer, clear the error flag and discard the input
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << LINE << "\nPlease enter an integer!\n" << LINE << endl;
			system("pause");
			continue;  // Restart the loop
		}
		switch (op)
		{

		case 1:
			list_of_events();
			break;
		case 2:
			delete_event();
			break;
		case 3:
			viewattendeelist();
			break;
		case 4:
			Remove(1);
			break;
		case 5:
			Remove(2);
			break;
		case 6:
			break;
		default:
		{
			cout << LINE << "\nSelected option not found! Pick again...\n" << LINE << endl;
			system("pause");
			break;
		}
		}
	} while (op != 6);
}

void manager_dashboard()
{
	int op;
	do {
		system("cls");
		cout << "\t" << LINE << "\n\t\t\tManager Dashboard\n" << "\t" << LINE << endl;
		cout << "Welocme Mr.Manager.what would you like to do today!" << endl;
		cout << "1. Show the list of available events \n2. Add an Event \n3. Modify an existing Event \n4. Delete an event\n5. View attendee list.\n6.Exit\n--> "; cin >> op;
		if (cin.fail()) {
			// If the input is not an integer, clear the error flag and discard the input
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << LINE << "\nPlease enter an integer!\n" << LINE << endl;
			system("pause");
			continue;  // Restart the loop
		}
		switch (op)
		{

		case 1:
			list_of_events();
			break;
		case 2:
			add_event();
			break;
		case 3:
			modify_event();
			break;
		case 4:
			delete_event();
			break;
		case 5:
			viewattendeelist();
			break;
		case 6:
			break;
		default:
		{
			cout << LINE << "\nSelected option not found! Pick again...\n" << LINE << endl;
			system("pause");
			break;
		}
		}
	} while (op != 6);
}

void customer_dashboard()
{
	int x;
	do
	{
		system("cls");
		cout << "\t" << LINE << "\n\t\t\tUser Dashboard\n" << "\t" << LINE << endl;
		cout << "Welcome! What would you like to do?" << endl;
		cout << "1. Show the list of available events\n2. Ticketing\n3. Show your booked Events\n4. Delete your Booking\n5. Exit\n--> ";
		cin >> x;
		if (cin.fail()) {
			// If the input is not an integer, clear the error flag and discard the input
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << LINE << "\nPlease enter an integer!\n" << LINE << endl;
			system("pause");
			continue;  // Restart the loop
		}
		switch (x) {
		case 1:
			list_of_events();
			break;
		case 2:
			ticketBooking();
			break;
		case 3:
			view_user_booking();
			break;
		case 4:
			delete_booking();
			break;
		case 5:
			break;
		default:
		{
			cout << LINE << "\nSelected option not found! Pick again...\n" << LINE << endl;
			system("pause");
			break;
		}
		}
	} while (x != 5);
}

void Remove(int op)
{
	ifstream read;
	ofstream temp;
	switch (op)
	{
	case 1:
	{
		read.open("manager.txt");
		temp.open("temp.txt");
		if (!read.is_open() || !temp.is_open()) {
			system("cls");
			cout << LINE << "Error opening or creating files!" << LINE << endl;
			system("pause");
			return;
		}

		if (read.peek() == ifstream::traits_type::eof()) {
			system("cls");
			cout << LINE << "No managers to remove!" << LINE << endl;
			system("pause");
			return;
		}

		string username;
		bool found = false;
		cout << "Enter the Username of the Manager you want to remove: "; cin >> username;

		string line;
		while (getline(read, line)) {
			if (line.find(username) != string::npos) {
				found = true;
			}
			else
				temp << line << endl;
		}
		read.close();
		temp.close();

		remove("manager.txt");
		rename("temp.txt", "manager.txt");
		system("cls");
		if (!found) {
			cout << LINE << "\nManager Not Found!\n" << LINE << endl;
			system("pause");
		}
		else {
			cout << LINE << "\nManager removed Successfully!\n" << LINE << endl;
			system("pause");
		}
		break;
	}
	case 2: {
		read.open("user.txt");
		temp.open("temp.txt");
		if (!read.is_open() || !temp.is_open()) {
			system("cls");
			cout << LINE << "Error opening or creating files!" << LINE << endl;
			system("pause");
			return;
		}

		if (read.peek() == ifstream::traits_type::eof()) {
			system("cls");
			cout << LINE << "No users to remove!" << LINE << endl;
			system("pause");
			return;
		}

		string username;
		bool found = false;
		cout << "Enter the Username of the User you want to remove: "; cin >> username;

		string line;
		while (getline(read, line)) {
			if (line.find(username) != string::npos) {
				found = true;
			}
			else
				temp << line << endl;
		}
		read.close();
		temp.close();

		remove("user.txt");
		rename("temp.txt", "user.txt");
		system("cls");
		if (!found) {
			cout << LINE << "\nUser Not Found!\n" << LINE << endl;
			system("pause");
		}
		else {
			cout << LINE << "\nUser removed Successfully!\n" << LINE << endl;
			system("pause");
		}
		break;
	}
	}

}