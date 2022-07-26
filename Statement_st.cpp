#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#define MAX(x, y) ( (x > y) ? (x) : (y) )



bool check_name(string name) {
	for(int i = 0; i < name.length(); i++) {
		if(!isalpha(name[i])) {
			cout << "Name could not contain symbols or digits\n-> ";
			cout << name <<"\n";
			return false;
		}
	}
	return true;
}


bool _is_alpha(string str) {
	for(int i = 0; i < str.length(); i++) {
		if(isalpha(str[i]) ){
			cout << "Сould not contain symbols\n-> ";
			cout << str <<'\n';
			return false;
		} 
	}
	return true;
}



bool check_date(string date) {
	string fail = "fail\n";
	if(date[2] != '.' && date[5] != '.') return false;
	try {
		if(_is_alpha(date)) {
			if(stoi(date.substr(0, 2)) > 29 && stoi(date.substr(3, 2)) == 2 || stoi(date.substr(0, 2)) > 31 && stoi(date.substr(3, 2)) != 2
	 		|| stoi(date.substr(3, 2)) > 12 || stoi(date.substr(3,2)) == 0 || stoi(date.substr(0, 2)) == 0 ) {
	 			cout << "incorrect date!\n";
	 			return false;
			 }
		}
		else {
			cout << date.substr(0, 10);
			return false;
		}
			
	}
	catch(string fail) {
		cout << fail;
	}
		
	return true;
}



void list (string path) {
	ifstream Statement;
	
	Statement.open(path);
	if(Statement.is_open()) {
		Statement.seekg(0, Statement.end);
		int length = Statement.tellg();
		Statement.seekg(0, Statement.beg);
		char* buffer = new char[length];
		
		Statement.read(buffer, length);
		Statement.close();
		
		cout.write(buffer, length);
		delete[] buffer;

	}
	else cout << "could not open the file";
}


void add(string path) {
	string name, l_name, date;
	double salary;
	ofstream statement(path, std::ios::app);
	
	if(statement.is_open()) {
		cout << "Enter name, last name, date(DD,MM,YYYY), salary\n";
		cin >> name >> l_name >> date >> salary;

		if(!check_date(date) || !check_name(name)  || !check_name(l_name) ){ // !check_name(name) 
			cout << "NO\n";
			return;
		} 
		statement << name << " " << l_name << " " << date << " " << salary << "\n";
		statement.close();
	}
	else cout << "Could not open file!";
}


struct statement {
	string path = "";
	
		bool Do(string Command) {
				if(Command == "list") {
					cout << "Our data : \n";
					list(path);
					return true;
				}
				if(Command == "add") {
					cout << "Adding...\n";
					add(path);
					return true;
				}
				if(Command == "exit") {
					cout <<"Exiting...\n";
					return false;
				}
			}
};

int main() {
	statement s;
	cout << "enter command [list] to read the file, [add] to add data\n";
	string command;
	cin >> command;
	s.Do(command);
	
}
