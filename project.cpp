// STAFF SYSTEM
// Tala Almulla
// Sara Sultan Alzahrani
// Basmah aljishi
// Roaa alturaif
// Rawan Mohammed sahari
// Nada alharbi

#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
using namespace std;
// Report array for the statistical report
int report[6] = {0};

// Structer
struct company
{
    string name;
    string id;
    int age;
    string gender;
    int salary;
};

// Declaring file names and some values
string fName = "Data.txt";            // For input file
string bName = "Data_backup.txt";     // For a backup output file
string oName = "New_Data.txt";        // For an output file where the new data will be saved
string Rname = "Statical_Report.txt"; // For the stat report file
int NumOfEmployees = 0;               // current number of employees
const int limit = 100;                // array limit
company employees[limit];             // Array of struct

// Input file
void LoadData(string fName, company employees[])
{
    ifstream load; // load is the object
    load.open(fName);
    if (load.is_open())
    {
        int counter = 0;
        while (!load.eof())
        {
            getline(load, employees[counter].name);
            getline(load, employees[counter].id);
            load >> employees[counter].age;
            load.ignore(1);
            getline(load, employees[counter].gender);
            load >> employees[counter].salary;
            load.ignore(1);
            counter++;
        }
        NumOfEmployees = counter - 1;
        load.close();
    }
    else
    {
        cout << "Failed or File is not exist" << endl;
    }
}

// Copy the data into a backup file
void backup(string fName, string bName)
{
    ofstream To;
    ifstream From;
    To.open(bName, ios::out);
    From.open(fName, ios::in);
    string line;
    if (To.is_open() && From.is_open())
    {
        do
        {
            getline(From, line); // read from original file
            To << line << endl;  // write to backup file
        } while (!From.eof());
        To.close();
        From.close();
        cout << "File is Backed up seccefully" << endl;
    }
    else
        cout << "Error: failed to open or some files does not exist" << endl;
}

// Save the new data into a file
void saveData(string oName, company employees[])
{
    ofstream outputfile;
    outputfile.open(oName, ios::out);
    if (outputfile.is_open())
    {
        for (int i = 0; i < NumOfEmployees; i++)
        {
            outputfile << employees[i].name << endl;
            outputfile << employees[i].id << endl;
            outputfile << employees[i].age << endl;
            outputfile << employees[i].gender << endl;
            outputfile << employees[i].salary << endl;
        }
        outputfile.close();
        cout << "\nData Saved Successfully,Have a nice day\n";
    }
    else
        cout << "\nFailed,Please Try Again.\n";
}

// Stat report (needs re-numbering)
void statical_report()
{
    ofstream StatReport;
    time_t t;
    t = time(NULL); // return the date and time
    char *time = ctime(&t);
    StatReport.open(Rname, ios::app);
    if (StatReport.is_open())
    {
        StatReport << endl;
        StatReport << "The user asked to display data: " << report[0] << " times" << endl;
        StatReport << "The user asked to add data: " << report[1] << " times" << endl;
        StatReport << "The user asked to search for data: " << report[2] << " times" << endl;
        StatReport << "The user asked to update data: " << report[3] << " times" << endl;
        StatReport << "The user asked to sort data: " << report[4] << " times" << endl;
        StatReport << "The user asked to delete data: " << report[5] << " times" << endl;
        StatReport << "The Date and time of the last update: " << time << endl;
        StatReport.close();
    }
    else
        cout << "Failed to save the last modified data";
}

// Overloading "test" for add function and menu

int test(company employees[], string id, int NumOfEmployees)
{
    for (int i = 0; i < NumOfEmployees; i++)
        if (employees[i].id == id)
            return i;
    return -1;
}
bool test()
{
    char result;
    cout << "\nDo you want to use another service? (enter Y for yes and N for no): ";
    cin >> result;
    if (result == 'N' || result == 'n')
        return false;
    else if (result == 'Y' || result == 'y')
        return true;
    else
    {
        cout << "Wrong input,please try again";
        return test(); // recursion so the user can enter the value again
    }
}

// Welcome message
void welcome()
{
    cout << "\n\t\t Welcome to the company information system" << endl;
    cout << "Choose your preferred service from the menu and data will be automatically saved!" << endl;
    cout << "---------------------------------------------------------------------------------" << endl;
    cout << endl;
}

// Menu display
void menu()
{
    cout << "Enter your preferred service number: " << endl;
    cout << "\n 1- Add a new staff member \n 2- Search for a specific staff \n "
         << "3- Update staff info \n 4- Delete a staff \n 5- Sort employees \n "
         << "6- Display all employees \n And enter -1 if you're done! " << endl;
}

// Display data
void displayData(company employees[])
{
    report[0]++;
    for (int i = 0; i < NumOfEmployees; i++)
    {
        cout << "Name: " << employees[i].name << endl;
        cout << "ID: " << employees[i].id << endl;
        cout << "Age: " << employees[i].age << endl;
        cout << "Gender: " << employees[i].gender << endl;
        cout << "Salary: " << employees[i].salary << endl;
    }
}

// Adding a staff
void add(company employees[], int &NumOfEmployees)
{
    report[1]++;
    string id;
    cout << "Enter the new staff information: " << endl;
    cout << "ID (5 integers only): ";
    cin >> id;
    while (test(employees, id, NumOfEmployees) >= 0)
    {
        cout << "This id was used, try another one: ";
        cin >> id;
    }
    employees[NumOfEmployees].id = id;
    cout << "Enter Name: ";
    cin >> employees[NumOfEmployees].name;
    cout << "Enter Age: ";
    cin >> employees[NumOfEmployees].age;
    cout << "Enter gender: ";
    cin >> employees[NumOfEmployees].gender;
    cout << "Enter salary: ";
    cin >> employees[NumOfEmployees].salary;
    cout << "staff: " << NumOfEmployees + 1 << endl;
    NumOfEmployees++;
}

// Search for staff
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
        cout << "There is no staff,try adding befor searching!" << endl;
    return -1;
}

// Updating info
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
            cout << "The staff age that was found at index " << index << " is: " << employees[index].age << endl;
            cout << "Enter the new age: ";
            cin >> employees[index].age;
            cout << "The age was updated successfully! ";
        }
        else
            cout << "ID was not found";
    }
    else
        cout << "There is no staff,try adding befor updating";
}

// Sort
void sort(company employees[], int NumOfEmployees)
{
    report[4]++;
    company temp;
    if (NumOfEmployees < 2)
        cout << " There is nothing to be sorted! ";
    else
    {
        for (int i = 0; i < NumOfEmployees - 1; i++)
            for (int j = 0; j < NumOfEmployees - 1; j++)
                if (employees[j].salary > employees[j + 1].salary)
                {
                    temp.salary = employees[j].salary;
                    employees[j].salary = employees[j + 1].salary;
                    employees[j + 1].salary = temp.salary;
                }
        cout << "Recored has been sorted by salary successfully!";
    }
}

// Delete
void DeleteData(company employees[], string id, int &NumOfEmployees)
{
    report[5]++;
    int index = -1;
    if (NumOfEmployees > 0)
    {
        index = search(employees, id, NumOfEmployees);
        report[2]--;
        if (index != -1)
        {
            for (int i = index; i < NumOfEmployees - 1; i++)
            {
                employees[i] = employees[i + 1];
            }
            NumOfEmployees--;
            cout << "The recored was deleted " << endl;
        }
        else
            cout << "ID was not found" << endl;
    }
    else
        cout << "No record to delete";
}

int main()
{
    int limit_user;
    welcome();
    cout << "Enter the maximum number of staff: ";
    cin >> limit_user;
    company employees[limit_user];
    LoadData(fName, employees);
    backup(fName, bName);
    string id;
    int service, MainIndex;
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
            MainIndex = search(employees, id, NumOfEmployees);
            if (MainIndex == -1)
            {
                cout << "We didn't finde an employee with the entered data" << endl;
                break;
            }
            else
            {
                cout << "\nEmployee Name: " << employees[MainIndex].name;
                cout << "\nEmployee ID: " << employees[MainIndex].id;
                cout << "\nEmployee Age: " << employees[MainIndex].age;
                cout << "\nEmployee gender: " << employees[MainIndex].gender;
                cout << "\nEmployee salary: " << employees[MainIndex].salary;
                break;
            }
        case 3:
            cout << "\nEnter the employee id who you want to update their job or salary: ";
            cin >> id;
            update(employees, id, NumOfEmployees);
            break;
        case 4:
            cout << "Enter the id for the player to delete it: ";
            cin >> id;
            DeleteData(employees, id, NumOfEmployees);
            break;
        case 5:
            sort(employees, NumOfEmployees);
            break;
        case 6:
            displayData(employees);
            break;
        default:
            cout << "\nWrong input, please try again" << endl;
        }
    } while (test());
    statical_report();
    saveData(oName, employees);
    return 0;
}