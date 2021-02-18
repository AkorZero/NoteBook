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
const string nameFile = "C:\\Users\\mrmin\\source\\repos\\NoteBook\\NoteBook\\NoteBook.dat";
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
	loadNoteBook(NoteBook);
	Show(NoteBook);
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
		if (task == "Show")
		{
			Show(NoteBook);
		}
		if (task == "Add") {
			if (personPrefix == "") {
				cout << "Input Name :";
				getline(cin, personName);
				cout << "Input Phone :";
				getline(cin, personPhone);
			}
			else {
				int found = personPrefix.find(';');
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
			if (addPerson(NoteBook, newPerson)) {
				cout << "Record added" << endl;
			}
			else {
				cout << "Record updated" << endl;
			}
		}

		if (task == "Exit")
		{
			saveNoteBook(NoteBook);
			break;
		}

		if (task == "SearchPhone")
		{
			if (personPrefix == "")
			{
				cout << "Input name: ";
				getline(cin, personPrefix);
			}
			int found = -1;
			bool foundPerson = false;
			while ((found = findPersonPhone(NoteBook, personPrefix, found + 1)) != -1)
			{
				NoteBook[found].printPerson();
				foundPerson = true;
				cout << endl;
			}
			if (!foundPerson)
			{
				cout << "Person not found 404: " << personPrefix << endl;
			}
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

void Show(vector <PersonPhone>& noteBook)
{
	/*for (int i = 0; i < noteBook.size(); i++)
	{
		noteBook[i].printPerson();
		cout << endl;
	}*/

	for (PersonPhone persona : noteBook)
	{
		persona.printPerson();
		cout << endl;
	}
}

void loadNoteBook(vector<PersonPhone>& noteBook)
{
	ifstream inFile(nameFile);
	if (!inFile.is_open())
	{
		cout << "File not found" << endl;
		return;
	}
	
	string text;
	PersonPhone newPersona;
	while (getline(inFile, text))
	{
		int poz = text.find(';');
		newPersona.personName = text.substr(0, poz);
		newPersona.personPhone = text.substr(poz + 1, text.length() - poz);
		noteBook.push_back(newPersona);
	}
	inFile.close();
}

void saveNoteBook(vector<PersonPhone>& noteBook)
{
	ofstream outFile(nameFile);
	for (PersonPhone persona : noteBook)
	{
		persona.printPerson(outFile);
	}
	outFile.close();

}

int findPersonPhone(vector<PersonPhone>& noteBook, string name, int poz)
{
	for (int i = poz; i < noteBook.size(); i++)
	{
		if (noteBook[i].personName.find(name) == 0)
		{
			return i;
		}
	}
	return -1;
}

bool addPerson(vector<PersonPhone>& noteBook, PersonPhone newPerson)
{
	int found = -1;
	while ((found = findPersonPhone(noteBook, newPerson.personName, found + 1)) != -1)
	{
		if (noteBook[found].personName == newPerson.personName)
		{
			noteBook[found] = newPerson;
			return false;
		}
	}
	noteBook.push_back(newPerson);
}