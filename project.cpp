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
string oName = "New_Data.txt";
int NumOfEmployees = 0; // current num of employees
const int limit = 1000;
company employees[limit]; // the array of structer

// adding the file data
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
        cout << "File is Backed up seccefully \n";
    }
    else
        cout << "Error: failed to open or some files does not exist \n";
}

// save in new file
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
            outputfile << employees[i].job << endl;
            outputfile << employees[i].salary << endl;
        }
        outputfile.close();
        cout << "\nData Saved Successfully.\n";
    }
    else
        cout << "\nFailed,Please Try Again.\n";
}

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

// delete
void DeleteData(company employees[], string id, int &NumOfEmployees) // if id was not found
{
    report[5]++;
    int index = -1;
    if (NumOfEmployees > 0)
    {
        index = search(employees, id, NumOfEmployees);
        report[1]--;
        if (index != -1)
        {
            for (int i = index; i < NumOfEmployees - 1; i++)
            {
                employees[i] = employees[i + 1];
            }
            NumOfEmployees--;
            cout << "The recored was deleted " << endl;
        }
    }
    else
        cout << " No record to delete ";
}

// updating info
void update(company employees[], string id, int NumOfEmployees)
{
    report[3]++;
    int index = -1;
    if (NumOfEmployees > 0)
    {
        index = search(employees, id, NumOfEmployees);
        report[1]--;
        if (index != -1)
        {
            cout << "The staff salary that was found at index: " << index << " is: " << employees[index].salary << endl;
            cout << "Enter the new salary: ";
            cin >> employees[index].salary;
            cout << "The salary was updated successfully! ";
            cout << "The staff job title that was found at index " << index << " is: " << employees[index].job << endl;
            cout << "Enter the new job title: ";
            cin >> employees[index].job;
            cout << "The job title was updated successfully! "; // add age
        }
        else
            cout << "ID was not found";
    }
    else
        cout << "There is no staff,try adding befor updating";
}

// sort
void sort(company employees[], int NumOfEmployees)
{
    report[4]++;
    company temp;
    if (NumOfEmployees < 2)
        cout << " There is nothing to be sort !! ";
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

// report (needs re-numbering)
void statical_report()
{
    ofstream StatReport;
    string Rname = "Statical_Report.txt";
    time_t t;
    t = time(NULL);
    char *time = ctime(&t); // search
    StatReport.open(Rname /* the use ? */, ios::app);
    if (StatReport.is_open())
    {
        StatReport << endl;
        StatReport << "The user ask to add data: " << report[1] << " times" << endl;
        StatReport << "The user ask to search data: " << report[2] << " times" << endl;
        StatReport << "The user ask to add Update data: " << report[3] << " times" << endl;
        StatReport << "The user ask to delete data: " << report[5] << " times" << endl;
        StatReport << "The user ask to sort data: " << report[4] << " times" << endl;
        StatReport << "The user ask to display data: " << report[0] << " times" << endl;
        StatReport << "The Date of Last update: " << time << endl;
        StatReport.close();
    }
    else
        cout << "Failed To Save Last Modifications!";
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
            z = search(employees, id, NumOfEmployees); // no need for z
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