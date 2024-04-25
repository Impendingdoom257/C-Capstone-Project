/*
	Name: Patient Program (multifile Project)	
	Copyright: 2023	
	Author: Brian Cerda
	Date: 07/10/23 10:43
	Description: Multifile program version of the patient program done in CS37. This program uses a struct to generate the 
	information put in by the user. Then it prints a catalog of patients previously inputed with their name, condition, age, gender,
	Primary Doctor, referral doctor, Insurance Name, Insurance Status, copay, and balance.
*/
#include <iostream>
#include "PatientClassBrianCerdaCS37.h"
#include <vector>
#include <string.h>
#include <sstream>
#include <fstream>
#include <cctype>
using namespace std;
void menu(vector<Patient>);
bool validate(char);
void addPatient(vector<Patient>&);
void appPatient(Patient);
void inputRefDoc(Patient&);
void loadPatients(vector<Patient>&);
void editPatient(vector<Patient>&);
void editName(vector<Patient>&, int);
void editAge(vector<Patient>&, int);
void editCondition(vector<Patient>&, int);
void editGender(vector<Patient>&, int);
void editInsurStatus(vector<Patient>&, int);
void editInsurName(vector<Patient>&, int);
void editCopay(vector<Patient>&, int);
void editBalance(vector<Patient>&, int);
void editPrimaryDoc(vector<Patient>&, int);
void editRefDoc(vector<Patient>&, int);
void editDataBase(vector<Patient>);
void printPatients(vector<Patient>);
void errorMessage();
// Menu function that allows user to navigate to other functions. 
void menu(vector<Patient> current_Patient)
{
	int choice = 0;
	loadPatients(current_Patient);
	do{
		cout << "MAIN MENU"
			<< "\n______________________\n"
		 	<< "1)Add a new patient\n"
			<< "2)Edit existing patient information\n"
			<< "3)Print Patient Catalog\n"
			<< "4)Exit\n";
		cin >> choice;
		cin.ignore();
		if(choice==1)
		{	addPatient(current_Patient);	} 
		else if(choice==2)
		{	editPatient(current_Patient);	}
		else if(choice==3)
		{	printPatients(current_Patient);	}
		else if(choice < 1 || choice > 4)
		{	errorMessage();		}	
	}while(choice!=4);		 
}
//Loads in patients from PatientDataBase.txt into the vector for use.
void loadPatients(vector<Patient>& current_Patient)
{
	ifstream infile("PatientDataBase.txt");
	Patient new_Patient;
	string temp, space = " ", name, firstName, lastName, gender, condition, primaryDoc, insurName, refDoc;
	int age = 0;
	double copay = 0.00, balance = 0.00;
	while(getline(infile, temp))
	{
		istringstream fileLine(temp);
		fileLine >> firstName >> lastName >> age >> gender
				 >> condition >> insurName >> primaryDoc 
				>>  refDoc;
		refDoc.c_str();
		while(isdigit(refDoc[0]) == false)
		{
			new_Patient.setRefDoc(refDoc);
			fileLine >> refDoc;
			refDoc.c_str();	
		}
	fileLine >> copay >> balance;
	name = firstName;
	name.append(space);
	name.append(lastName);		 
	new_Patient.setName(name);
	new_Patient.setAge(age);
	new_Patient.setGender(gender);
	new_Patient.setCondition(condition);
	new_Patient.setPrimaryDoc(primaryDoc);
	new_Patient.setInsurName(insurName);
	new_Patient.setCopay(copay);
	new_Patient.setBalance(balance);
	current_Patient.push_back(new_Patient);
	}
	infile.close();
}
// Input function to add a patient
void addPatient(vector<Patient>& current_Patient)
{
	Patient new_Patient;
	char insured;
	string n, g, c, i, pD;
	double coP = 0.00;
	bool iS = false;
	int a = 0;
	cout << "\nPlease enter in the name of the new patient\n";
	getline(cin, n, '\n');
	cout << "\nPlease enter in " << n << "'s age.\n";
	cin >> a;
	cin.ignore();
	cout << "\nPlease enter in " << n << "'s gender.\n";
	getline(cin, g, '\n');
	cout << "\nPlease enter in " << n << "'s condition.\n";
	getline(cin, c, '\n');
	cout << "\nIs the patient insured?\nPlease enter Y for yes and N for no\n";
	cin >> insured;
	iS = validate(insured);
	cin.ignore();
	if(iS == true)
	{
		cout << "\nPlease enter the name of the insurance company.\n";
		getline(cin, i, '\n');
	}
	cout << "\nPlease enter the name of the primary doctor.\n";
	getline(cin, pD, '\n');
	cout << "\nPlease enter in the copay amount for the treatment.\n";
	cin >> coP;
	cin.ignore();
	new_Patient.setName(n);
	new_Patient.setAge(a);
	new_Patient.setGender(g);
	new_Patient.setCondition(c);
	new_Patient.setInsuredStatus(iS);
	new_Patient.setInsurName(i);
	new_Patient.setPrimaryDoc(pD);
	inputRefDoc(new_Patient);
	new_Patient.setCopay(coP);
	appPatient(new_Patient);
	current_Patient.push_back(new_Patient);
}
//Takes user inputs for referral doctors and stores them in new_Patient
void inputRefDoc(Patient& new_Patient)
 {
 	string temp1;
 	do{
 		cout << "\nPlease enter the name of the reference doctor for the patient.\n"
 			 << "Type 'done' when you are finished.\n";
		getline(cin, temp1, '\n');
		if(temp1 != "done")
		{ 	new_Patient.setRefDoc(temp1);	}
	 }while(temp1 != "done");
 } 
//Appends new patient to the PatientDataBase.txt 
void appPatient(Patient new_Patient)
{
	ofstream outfile("PatientDataBase.txt", ios::app);
	outfile << new_Patient.getName() << " " << new_Patient.getAge() << " "
		    << new_Patient.getGender() << " " << new_Patient.getCondition() << " ";
	if(new_Patient.getInsuredStatus() == true)
	{	outfile << new_Patient.getInsurName() << " "; 		}
	else
	{	outfile << "uninsured" << " ";		}
	outfile << new_Patient.getPrimaryDoc() << " ";
	for(int i = 0; i < new_Patient.getRefDocVecSize(); i++)
	{ outfile	<< new_Patient.getRefDoc(i) << " ";	} 
	outfile << new_Patient.getBalance() 
			<< new_Patient.getCopay() << "\n";
	outfile.close();		 	    
}
//Checks input to make sure it is either Y or N and returns a boolean value True for Y and False for N
bool validate(char insured)
{
	insured = toupper(insured);
	if(insured == 'Y')
	{	return true;	}
	else if(insured == 'N')
	{	return false;	}
	do{	
		errorMessage();		
		cout << "\nIs the patient insured?\nPlease enter Y for yes and N for no\n";
		cin >> insured;
		insured = toupper(insured);
	}while(insured != 'Y' || insured != 'N'); 
	errorMessage();
	return false;
}
// Input function to edit an entry to vector patient_Current.
void editPatient(vector<Patient>& current_Patient)
{
	int pos = 0, selection = 0;
	do{
		cout << "Please enter in 1 to edit name\n 2 to edit age\n 3 to edit condition\n"
			 << "4 to edit gender\n 5 to edit insurance status\n 6 to edit insurance name\n"
			 << "7 to edit copay\n 8 to edit the balance\n 9 to edit the primary doctor\n"
			 << "10 to edit the referral doctor(s)\n or 11 to exit\n\n";
		cin >> selection;
		if(selection > 0 && selection < 11)
		{
			printPatients(current_Patient);
			cout << "Please select an entry in the catalog you'd like to edit. Then enter in the correction.\n";
			cin >> pos;
			pos = pos - 1;
		}
		if(selection == 1)
		{	editName(current_Patient, pos);	}
		else if(selection == 2)
		{	editAge(current_Patient, pos);	}
		else if(selection == 3)
		{	editCondition(current_Patient, pos);		}
		else if(selection == 4)
		{	editGender(current_Patient, pos);	}
		else if(selection == 5)
		{	editInsurStatus(current_Patient, pos);	}
		else if(selection == 6)
		{	editInsurName(current_Patient, pos);	}
		else if(selection == 7)
		{	editCopay(current_Patient, pos);	}
		else if(selection == 8)
		{	editBalance(current_Patient, pos);	}
		else if(selection == 9)
		{	editPrimaryDoc(current_Patient, pos);	}
		else if(selection == 10)
		{	editRefDoc(current_Patient, pos);	}
		else if(selection < 0 || selection > 11)
		{	errorMessage(); }	 
	}while(selection != 11);
	editDataBase(current_Patient);	 
}
//Updates the patient database.
void editDataBase(vector<Patient> current_Patient)
{
	ofstream outfile("newDataBase.txt");
	for(int i = 0; i < current_Patient.size(); i++)
	{
		outfile << current_Patient[i].getName() << " " << current_Patient[i].getAge() << " "
				<< current_Patient[i].getGender() << " " << current_Patient[i].getCondition() << " "
				<< current_Patient[i].getPrimaryDoc() << " " << current_Patient[i].getInsurName() << " ";
				for(int j = 0; j < current_Patient[i].getRefDocVecSize(); j++)
				{	outfile << current_Patient[i].getRefDoc(j) << " ";		} 
		outfile	<< current_Patient[i].getCopay() << " "
				<< current_Patient[i].getBalance() << endl;	
	}
	outfile.close();
	remove("PatientDataBase.txt");
	rename("PatientDataBase.txt", "newDataBase.txt");
}
// Input function that edits a patient's name.
void editName(vector<Patient>& current_Patient, int pos)
{	
	string newName;
	cin >> newName;
	current_Patient[pos].setName(newName);
}
// Input function that edits a patient's age.
void editAge(vector<Patient>& current_Patient, int pos)
{
	int newAge = 0;
	cin >> newAge;
	current_Patient[pos].setAge(newAge);
}
// Input function that edits a patient's condition.
void editCondition(vector<Patient>& current_Patient, int pos)
{
	string newCond;
	cin >> newCond;
	current_Patient[pos].setCondition(newCond);
}
// Input function that edits a patient's gender.
void editGender(vector<Patient>& current_Patient, int pos)
{
	string newGender;
	cin >> newGender;
	current_Patient[pos].setGender(newGender);
}
//Edits the insurance status of a patient in the vector.
void editInsurStatus(vector<Patient>& current_Patient, int pos)
{
	bool status = false;
	bool validated = false;
	char choice;
	do{
		cout << "Please enter Y if patient is insured and N if they are not insured.\n";
		cin >> choice;
		choice = toupper(choice);
		if(choice == 'Y')
		{	
			status = true;
			validated = true;
			current_Patient[pos].setInsuredStatus(status);
			editInsurName(current_Patient, pos);	
		}
		else if(choice == 'N')
		{	
			validated = true;
			current_Patient[pos].setInsuredStatus(status);	
		}
		else
		{	errorMessage();	}
	}while(validated = false);
}
//Edits the name of the Insurance Company of the patient.
void editInsurName(vector<Patient>& current_Patient, int pos)
{
	string temp;
	cout << "Please enter the name of the insurance company.\n";
	getline(cin, temp);
	current_Patient[pos].setInsurName(temp);
}
//Edits the copay of the patient.
void editCopay(vector<Patient>& current_Patient, int pos)
{
	double copay = 0.00;
	cout << "Please enter the new copay.\n";
	cin >> copay;
	current_Patient[pos].setCopay(copay);
}
//Edits the balance of the patient.
void editBalance(vector<Patient>& current_Patient, int pos)
{
	double balance = 0.00;
	cout << "Please enter in the new balance.\n";
	cin >> balance;
	current_Patient[pos].setBalance(balance);
}
//Edits the primary doctor of the patient.
void editPrimaryDoc(vector<Patient>& current_Patient, int pos)
{
	string temp;
	cout << "Please enter the name of the Primary Doctor.\n";
	getline(cin, temp);
	current_Patient[pos].setPrimaryDoc(temp);
}
//Edits the names of the referral doctors.
void editRefDoc(vector<Patient>& current_Patient, int pos)
{
	string temp1;
	int choice = -1;
	do{
		cout << "Here is a list of the current referral doctors.\n";
		for(int i = 0; i < current_Patient[pos].getRefDocVecSize(); i++)
		{	cout << i+1 << ". " << current_Patient[pos].getRefDoc(i) << endl;	}
		cout << "Please enter the name of the referral doctors.\n"
			 << "When you are done, please type in 'done'.\n";
		getline(cin, temp1);
		if(temp1 != "done")
		{
			cout << "Please enter the number of the associated referral doctor you would like to edit.\n";
			cin >> choice;
			while(choice < 0 || choice > current_Patient[pos].getRefDocVecSize())
			{
				cout << "The number you entered was invaid\n Please try again.\n";
				cin >> choice;
			}
		}
	}while(temp1 != "done");
	current_Patient[pos].changeRefDoc(temp1, choice);
}
// Output function that prints out the entire vector for current_Patient.
void printPatients(vector<Patient> current_Patient)
{
	for(int i = 0; i < current_Patient.size(); i++)
	{
		cout << "\nList Number: " << i + 1 << " "
			 << "Name: " << current_Patient[i].getName() << "\n"
			 << " Age: " << current_Patient[i].getAge() << "\n"
			 << " Gender: " << current_Patient[i].getGender() << "\n"
			 << " Condition: " << current_Patient[i].getCondition() << "\n"
			 << " Insurance status: ";
		if(current_Patient[i].getInsuredStatus() == false)
		{	cout << current_Patient[i].getInsurName() << "\n";	}
		else 
		{	cout << "Insured by " << current_Patient[i].getInsurName() << "\n";		}
		cout << " Primary Doctor: " << current_Patient[i].getPrimaryDoc() << "\n"
			 << " Referral Doctor(s): ";
			 for(int j = 0; j < current_Patient[i].getRefDocVecSize();j++)
			 {	cout << current_Patient[i].getRefDoc(j) << " ";		}
		cout << "\n" << " Current Balance: " << current_Patient[i].getBalance() << "\n"
			 << " Current Copay: " << current_Patient[i].getCopay() << "\n";
	}
}
// Output function that prints an error message when an incorrect value is inputted.
void errorMessage()
{	cout << "\n\nThe value you entered was invalid, please try again.\n\n";		}
// Main
int main() 
{
	vector<Patient> current_patient;
	menu(current_patient);
	return 0;
}