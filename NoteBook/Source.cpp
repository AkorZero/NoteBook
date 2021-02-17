#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;
struct PersonPhone {
	string personName;
	string personPhone;
	void printPerson() {
		cout << " Name : " << personName
			<< " Phone : " << personPhone;
	}
	void printPerson(ostream& out) {
		out << personName << ";" << personPhone << endl;
	}
};
const string nameFile = "C:/NoteBook.dat";
void loadNoteBook(vector<PersonPhone>& noteBook);
void saveNoteBook(vector<PersonPhone>& noteBook);
bool addPerson(vector<PersonPhone>& noteBook, PersonPhone newPerson);
bool removePerson(vector<PersonPhone>& noteBook, string name);
int findPersonName(vector<PersonPhone>& noteBook, string phone, int poz);
int findPersonPhone(vector<PersonPhone>& noteBook, string name, int poz);
void Show(vector<PersonPhone>& noteBook);
void help();



int main() {

	vector<PersonPhone> NoteBook;
	string command, task, personPrefix, personName, personPhone;
	//PersonPhone newPerson;
	//loadNoteBook(NoteBook);
	//Show(NoteBook);
	help();
	while (true) {
		PersonPhone newPerson;
		cout << ">";
		getline(cin, command);
		int found = command.find(' ');
		if (found == string::npos) {
			task = command;
			personPrefix = "";
		}
		else {
			task = command.substr(0, found);
			personPrefix = command.substr(found + 1, command.size() - found);
		}
		if (task == "Add") {
			if (personPrefix == "") {
				cout << "Input Name :";
				getline(cin, personName);
				cout << "Input Phone :";
				getline(cin, personPhone);
			}
			else {
				int found = command.find(';');
				if (found == string::npos) {
					personName = personPrefix;
					cout << "Input Phone :";
					getline(cin, personPhone);
				}
				else {
					personName = personPrefix.substr(0, found);
					personPhone = personPrefix.substr(found + 2, command.size() - found - 1);
				}
			}
			newPerson = { personName,personPhone };
			newPerson.printPerson();
			/*if (addPerson(NoteBook, newPerson)) {
				cout << "Record added" << endl;
			}
			else {
				cout << "Record updated" << endl;
			}*/
		}


	}


	system("pause");
	return 0;
}
void help() {
	cout << "Command:" << endl;
	cout << "Add personName; personPhone" << endl;
	cout << "Remove personName" << endl;
	cout << "SearchPhone personName" << endl;
	cout << "SearchName personPhone" << endl;
	cout << "Show" << endl;
	cout << "Help" << endl;
	cout << "Exit" << endl;


}