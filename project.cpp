#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
using namespace std;
// stat report array
int report[6] = {0};

// structer
struct company
{
    string name;
    string id;
    int age;
    string gender;
    string job;
    int salary;
};

// declaring files and some values
string fName = "Data.txt";
string bName = "Data_backup.txt"; // backup secondary file where the changes will be saved
int NumOfEmployees = 0;           // current num of employees
const int limit = 100;
company employees[100]; // the array of structer

// adding the file data
void LoadData(company employees[])
{
    ifstream load; // load is the object
    load.open("Data.txt");
    if (load.is_open() == true)
    {
        int counter = 0;
        while (!load.eof())
        {
            getline(load, employees[counter].name);
            getline(load, employees[counter].id);
            load >> employees[counter].age;
            load.ignore(1);
            getline(load, employees[counter].gender);
            getline(load, employees[counter].job);
            load >> employees[counter].salary;
            load.ignore(1);
            counter++;
        }
        NumOfEmployees = counter - 1;
        load.close();
    }
    else
    {
        cout << "Failed -- or File is not exist\n";
    }
}

// copy to backup

// save in new file

// overloading test

int test(company employees[], string id, int NumOfEmployees) // for the add function
{
    for (int i = 0; i < NumOfEmployees; i++)
        if (employees[i].id == id)
            return i;
    return -1;
}
bool test()
{ // for exiting the menu
    char result;
    cout << "\nDo you want to use another service? (enter Y for yes and N for no): ";
    cin >> result;
    if (result == 'N' || result == 'n')
        return false;
    else if (result == 'Y' || result == 'y')
        return true;
    else
    {
        cout << "wrong input,please try again";
        return test(); // check if it will work
    }
}

// welcome
void welcome()
{
    cout << "\n\t\t Welcome to the company information system" << endl;
    cout << "Choose your preferred service from the menu and data will be automatically saved" << endl;
    cout << "---------------------------------------------------------------------------------" << endl;
    cout << endl;
}

// menu
void menu()
{
    cout << "Enter your preferred service number: " << endl;
    cout << "\n 1- Add a new staff member \n 2- Search for a specific staff \n "
         << "3- Update staff info \n 4- Delete a staff \n 5- Sort employees \n "
         << "6- Display all employees \n And enter -1 if you're done! " << endl;
}

// Display the data
void displayData(company employees[])
{
    report[0]++;
    for (int i = 0; i < NumOfEmployees; i++)
    {
        cout << "Name: " << employees[i].name << "\n";
        cout << "ID: " << employees[i].id << "\n";
        cout << "Age: " << employees[i].age << "\n";
        cout << "Gender: " << employees[i].gender << "\n";
        cout << "Job: " << employees[i].job << "\n";
        cout << "Salary: " << employees[i].salary << "\n";
    }
}

// adding a staff
void add(company employees[], int &NumOfEmployees)
{
    report[1]++;
    string id;
    cout << "Enter the new staff information: " << endl;
    cout << "ID:(5 integers only) ";
    cin >> id;
    while (test(employees, id, NumOfEmployees) >= 0)
    {
        cout << "This was used, try another one";
        cin >> id;
    }
    employees[NumOfEmployees].id = id;
    cout << "Enter Name: ";
    cin >> employees[NumOfEmployees].name;
    cout << "Enter Age: ";
    cin >> employees[NumOfEmployees].age;
    cout << "Enter gender: ";
    cin >> employees[NumOfEmployees].gender;
    cout << "Enter job: ";
    cin >> employees[NumOfEmployees].job;
    cout << "Enter salary: ";
    cin >> employees[NumOfEmployees].salary;
    cout << "staff: " << NumOfEmployees + 1 << endl;
    NumOfEmployees++;
}

// search for staff
int search(company employees[], string id, int NumOfEmployees)
{
    report[2]++;
    if (NumOfEmployees > 0)
    {
        for (int i = 0; i < NumOfEmployees; i++)
            if (employees[i].id == id)
                return i;
        return -1;
    }
    else
        cout << "There is no staff,try adding befor searching" << endl;
    return -1;
}

// updating info
void update(company employees[], string id, int NumOfEmployees)
{
    report[3]++;
    int index = -1;
    if (NumOfEmployees > 0)
    {
        index = search(employees, id, NumOfEmployees);
        report[2]--;
        if (index != -1)
        {
            cout << "The staff salary that was found at index: " << index << " is: " << employees[index].salary << endl;
            cout << "Enter the new salary: ";
            cin >> employees[index].salary;
            cout << "The salary was updated successfully! ";
            cout << "The staff job title that was found at index " << index << " is: " << employees[index].job << endl;
            cout << "Enter the new job title: ";
            cin >> employees[index].job;
            cout << "The job title was updated successfully! ";
        }
        else
            cout << "ID was not found";
    }
    else
        cout << "There is no staff,try adding befor updating";
}

int main()
{
    int limit;
    welcome();
    cout << "Enter the maximum number of staff: ";
    cin >> limit;
    company employees[limit];
    LoadData(employees);
    string id;
    int service, z;
    do
    {
        menu();
        cout << "\nEnter the service number: ";
        cin >> service;

        if (service == -1)
        {
            cout << endl
                 << "Have a nice day!" << endl;
            break;
        }
        switch (service)
        {
        case 1:
            add(employees, NumOfEmployees);
            break;
        case 2:
            cout << "\nEnter the employee id who you want to find: ";
            cin >> id;
            z = search(employees, id, NumOfEmployees);
            if (z == -1)
                break;
            else
            {
                cout << "\nEmployee Name: " << employees[z].name;
                cout << "\nEmployee ID: " << employees[z].id;
                cout << "\nEmployee Age: " << employees[z].age;
                cout << "\nEmployee gender: " << employees[z].gender;
                cout << "\nEmployee job: " << employees[z].job;
                cout << "\nEmployee salary: " << employees[z].salary;
                break;
            }
        case 3:
            cout << "\nEnter the employee id who you want to update their job or salary: ";
            cin >> id;
            update(employees, id, NumOfEmployees);
            break;
        case 6:
            displayData(employees);
            break;
        default:
            cout << "\nWrong input, please try again" << endl;
        }
    } while (test());
    // statical_report ();
    // DatatoFile(player);
    return 0;
}