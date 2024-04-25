/*
	Name: Patient Program (Header)
	Copyright: 2023
	Author: Brian Cerda
	Date: 08/10/23 20:28
	Description: Header program for PatientProject.cpp file that contains the class for ADT patient.
	Stores Name, Age, Gender, and Condition of patient. Allows for updates of said patient.
Add:
*/
#include <string>
#include <iostream>
#include <vector>
using namespace std;
class Patient
{
private:
	string name;
	int age;
	string gender;
	string condition;
	bool insured;
	string insurName;
	double copay;
	double balance;
	string primaryDoc;
	vector <string> refDoc;	
public:
	Patient();
	void setName(string);
	void setAge(int);
	void setGender(string);
	void setCondition(string);
	void setInsuredStatus(bool);
	void setInsurName(string);
	void setCopay(double);
	void setBalance(double);
	void setPrimaryDoc(string);
	void setRefDoc(string);
	void changeRefDoc(string, int);
	string getName();
	string getGender();
	string getCondition();
	int getAge();
	bool getInsuredStatus();		
	string getInsurName();
	double getCopay();
	double getBalance();
	string getPrimaryDoc();
	string getRefDoc(int);
	int getRefDocVecSize();
};

// Constructor function that sets condition to "Healthy" by default.
	Patient::Patient()
	{	
		condition = "Healthy";	
		balance = 0.00;
	}

// Setter functions for private variables.	
	void Patient::setName(string n)
	{	name = n;	}
	
	void Patient::setAge(int a)
	{	age = a;	}
	
	void Patient::setGender(string g)
	{	gender = g;	 }
	
	void Patient::setCondition(string c)
	{	condition = c;	}

	void Patient::setInsuredStatus(bool status)
	{	insured = status;	}
	
	void Patient::setInsurName(string iName)
	{	insurName = iName;	}
	
	void Patient::setCopay(double co)
	{	copay = co;		}
	
	void Patient::setBalance(double b)
	{	balance = b;		}
	
	void Patient::setPrimaryDoc(string pD)
	{	primaryDoc = pD;	}
	
	void Patient::setRefDoc(string rD)
	{	refDoc.push_back(rD);	}
	
	void Patient::changeRefDoc(string rD, int pos)
	{	refDoc[pos] = rD;	}
	
// Accessor functions for private variables.	
	string Patient::getName()
	{	return this->name;	}
	
	int Patient::getAge()
	{	return this->age;		}
	
	string Patient::getGender()
	{	return this->gender;	}
	
	string Patient::getCondition()
	{	return this->condition;	}
	
	bool Patient::getInsuredStatus()
	{	return this->insured;		}
	
	string Patient::getInsurName()
	{	return this->insurName;	}
	
	double Patient::getCopay()
	{	return this->copay;	}
	
	double Patient::getBalance()
	{	return this->balance;		}
	
	string Patient::getPrimaryDoc()
	{	return this->primaryDoc;		}
	
	string Patient::getRefDoc(int pos)
	{	return this->refDoc[pos];		}
	
	int Patient::getRefDocVecSize()
	{	return this->refDoc.size();	}