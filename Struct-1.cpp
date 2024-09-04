/******************************************************************************
Marcus Gill                                                                     
CS 111                                                                          
Assigment 3 - struct.cpp                                                    
11-19-23                                                                         

Make a program that will do the following.
Download the input file, employees.dat, 
Assume this input file contains an unknown number of lines/employees. Each line contains information about an employee - first name, last name, gender, hourly rate, employee id, and age. Assume the number of lines/employees never exceeds 100.
                                                                                

******************************************************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>

using namespace std;

const int SIZE = 100; // Renamed MAX_EMPLOYEES to SIZE

// Define the Employee struct
struct Employee {
  string fName;
  string lName;
  char gender;
  double hourlyRate;
  int id;
  int age;
};

// Function prototypes
int readData(Employee mAr[], Employee fAr[], int& mi, int& fi);
void printEmployee(const Employee& emp);
void printAllEmp(const Employee arr[], int size);
void outfileArray(const Employee arr[], int size);
Employee findOldestMale(const Employee mAr[], int mi);
void giveRaise(Employee arr[], int size, double percentRaise);
void giveRaiseToOneEmployee(Employee& emp, double percentRaise);
void combineArray(const Employee mAr[], const Employee fAr[], Employee allEmp[], int totalEmployees);
void findEmp(const Employee arr[], int totalEmployees);
void sortEmployees(Employee arr[], int totalEmployees);

int main() {
  Employee mAr[SIZE];
  Employee fAr[SIZE];
  Employee allEmp[SIZE * 2];

  int mi = 0;
  int fi = 0;
  int totalEmployees = readData(mAr, fAr, mi, fi);

  cout << "------------------------------ readData() ------------------------------" << endl;

  cout << "There are " << mi << " male and " << fi << " female employees." << endl;

  cout << "------------------------------ printEmployee() ------------------------------" << endl;
  printEmployee(fAr[0]);  // Print details of the first employee in the female array

  cout << "------------------------------ printEmployee() ------------------------------" << endl;
  printEmployee(mAr[0]);  // Print details of the first employee in the male array

  cout << "------------------------------ printAllEmp() ------------------------------" << endl;
  printAllEmp(mAr, mi);  // Print details of all male employees

  cout << "------------------------------ printAllEmp() ------------------------------" << endl;
  printAllEmp(fAr, fi);  // Print details of all female employees

  cout << "------------------------------ outfileArray() ------------------------------" << endl;
  outfileArray(mAr, mi);  // output file name

  cout << "------------------------------ findOldest() ------------------------------" << endl;
  Employee oldestMale = findOldestMale(mAr, mi);
  cout << oldestMale.fName;

 
  cout << "\n------------------------------ giveRaise() ------------------------------" << endl;
  giveRaise(fAr, fi, 5.5);
  printAllEmp(fAr, fi);  // Print details of all female employees after giving a raise

  cout << "------------------------------ giveRaise() ------------------------------" << endl;
  giveRaise(mAr, mi, 5.0);
  printAllEmp(mAr, mi);  // Print details of all male employees after giving a raise

  cout << "------------------------------ giveRaiseToOneEmployee() ------------------------------" << endl;
  giveRaiseToOneEmployee(fAr[1], 2.0);
  printEmployee(fAr[1]);  // Print details of the second employee in the female array after giving a raise

  cout << "------------------------------ giveRaiseToOneEmployee() ------------------------------" << endl;
  giveRaiseToOneEmployee(mAr[0], 50.0);
  printEmployee(mAr[0]);  // Print details of the first employee in the male array after giving a raise

  cout << "------------------------------ combineArray() ------------------------------" << endl;
  for (int i = 0; i < totalEmployees  * 2; ++i) {
    allEmp[i] = Employee();  
  }

  combineArray(mAr, fAr, allEmp, mi);  // Pass mi as the size of the male array

  // Print details of all employees in the combined array
  printAllEmp(allEmp, mi + fi);  // mi + fi is the total number of employees


  cout << "------------------------------ findEmp() ------------------------------" << endl;
  findEmp(allEmp, totalEmployees);

  cout << "------------------------------ findEmp() ------------------------------" << endl;
  findEmp(allEmp, totalEmployees);
 
 cout << "------------------------------ sortEmployees() ------------------------------" << endl;
  sortEmployees(allEmp, totalEmployees);
  printAllEmp(allEmp, totalEmployees);  

  return 0;
}

int readData(Employee mAr[], Employee fAr[], int& mi, int& fi) {
  mi = 0;
  fi = 0;

  ifstream fin("employees.dat");

  if (!fin) {
    cout << "Cannot open the input file." << endl;
    return 0; // Return 0 to indicate failure
  }

  Employee temp;

  while (fin >> temp.fName >> temp.lName >> temp.gender >> temp.hourlyRate >> temp.id >> temp.age) {
    if (temp.gender == 'M') {
      mAr[mi] = temp;
      mi++;
    } else if (temp.gender == 'F') {
      fAr[fi] = temp;
      fi++;
    }
  }

  fin.close(); // Close the input file
  return mi + fi; // Return the total number of employees
}

void printEmployee(const Employee& emp) {
  cout << left << setw(10) << emp.fName << left << setw(10) << emp.lName << left << setw(10) << emp.gender
       << left << setw(10) << fixed << setprecision(2) << emp.hourlyRate << left << setw(10) << emp.id
       << left << setw(10) << emp.age << endl;
}

void printAllEmp(const Employee arr[], int totalEmployees) {
  for (int i = 0; i < totalEmployees; i++) {
    printEmployee(arr[i]);
  }
}

void outfileArray(const Employee arr[], int totalEmployees) {
  string filename;
  cout << "Enter the output file name: ";
  cin >> filename;

  ofstream fout(filename.c_str());
  if (!fout) {
    cout << "Error opening output file." << endl;
    return;
  }

  for (int i = 0; i < totalEmployees; ++i) {
    fout << arr[i].lName << ", " << arr[i].fName << endl;
  }

  fout.close();
}

Employee findOldestMale(const Employee mAr[], int mi) {
  Employee oldestMale = mAr[0];

  for (int i = 1; i < mi; ++i) {
    if (mAr[i].age > oldestMale.age) {
      oldestMale = mAr[i];
    }
  }

  return oldestMale;
}

void giveRaise(Employee arr[], int totalEmployees, double percentRaise) {
  for (int i = 0; i < totalEmployees; i++) {
    arr[i].hourlyRate *= (1 + percentRaise / 100.0);
  }
}

void giveRaiseToOneEmployee(Employee& emp, double percentRaise) {
  emp.hourlyRate *= (1 + percentRaise / 100.0);
}

void combineArray(const Employee mAr[], const Employee fAr[], Employee allEmp[], int totalEmployees) {
  for (int i = 0; i < totalEmployees; ++i) {
    allEmp[i] = mAr[i];
  }

  for (int j = 0; j < totalEmployees; ++j) {
    allEmp[totalEmployees + j] = fAr[j];
  }
}


void findEmp(const Employee arr[], int totalEmployees) {
  int idToFind;
  cout << "Enter the employee id: ";
  cin >> idToFind;

  bool found = false;

  for (int i = 0; i < totalEmployees; i++) {
    if (arr[i].id == idToFind) {
      printEmployee(arr[i]);
      found = true;
      break;
    }
  }

  if (!found) {
    cout << "There is no employee with ID " << idToFind << "." << endl;
  }
}

void sortEmployees(Employee arr[], int totalEmployees) {
  for (int i = 0; i < totalEmployees - 1; i++) {
    for (int j = 0; j < totalEmployees - i - 1; j++) {
      if (arr[j].fName > arr[j + 1].fName || (arr[j].fName == arr[j + 1].fName && arr[j].hourlyRate > arr[j + 1].hourlyRate)) {
        swap(arr[j], arr[j + 1]);
      }
    }
  }
}
