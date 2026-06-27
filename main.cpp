#include <iostream>
#include <string>
#include <limits>
using namespace std;

int nextID = 1001;

struct Patient  //by default struct is public
{
    int id;
    string name;
    int age;
    string contact;
    string doctor;
    string date;
    string condition;
    bool served;

    Patient* next;

    Patient(string n, int a, string c,
        string d, string dt, string cond)
    {
        id = nextID++;
        name = n;
        age = a;
        contact = c;
        doctor = d;
        date = dt;
        condition = cond;
        served = false;
        next = NULL;
    }
};

class PatientList
{
public:

    Patient* head;

    PatientList()
    {
        head = NULL;
    }

    void addPatient(Patient* p)
    {
        if (head == NULL)
        {
            head = p;
        }
        else
        {
            Patient* temp = head;

            while (temp->next != NULL)
            {
                temp = temp->next;
            }

            temp->next = p;
        }
    }

    Patient* searchByID(int id)
    {
        Patient* temp = head;

        while (temp != NULL)
        {
            if (temp->id == id)
            {
                return temp;
            }

            temp = temp->next;
        }

        return NULL;
    }

    Patient* searchByName(string name)
    {
        Patient* temp = head;

        while (temp != NULL)
        {
            if (temp->name == name)
            {
                return temp;
            }

            temp = temp->next;
        }

        return NULL;
    }

    void deletePatient(int id)
    {
        if (head == NULL)
        {
            cout << "No Record Found\n";
            return;
        }

        if (head->id == id)
        {
            Patient* temp = head;
            head = head->next;
            delete temp;

            cout << "Record Deleted\n";
            return;
        }

        Patient* current = head;

        while (current->next != NULL &&
            current->next->id != id)
        {
            current = current->next;
        }

        if (current->next == NULL)
        {
            cout << "Patient Not Found\n";
            return;
        }

        Patient* temp = current->next;

        current->next = temp->next;

        delete temp;

        cout << "Record Deleted\n";
    }

    void displayAll()
    {
        if (head == NULL)
        {
            cout << "\nNo Records Found\n";
            return;
        }

        Patient* temp = head;

        while (temp != NULL)
        {
            cout << "\nID: " << temp->id;
            cout << "\nName: " << temp->name;
            cout << "\nAge: " << temp->age;
            cout << "\nContact: " << temp->contact;
            cout << "\nDoctor: " << temp->doctor;
            cout << "\nDate: " << temp->date;
            cout << "\nCondition: " << temp->condition;

            if (temp->served)
                cout << "\nStatus: Served";
            else
                cout << "\nStatus: Pending";

            cout << "\n----------------------\n";

            temp = temp->next;
        }
    }

    void displayPending()
    {
        Patient* temp = head;

        while (temp != NULL)
        {
            if (temp->served == false)
            {
                cout << "\nID: " << temp->id;
                cout << "\nName: " << temp->name;
                cout << "\nDoctor: " << temp->doctor;
                cout << "\nDate: " << temp->date;
                cout << "\n------------------\n";
            }

            temp = temp->next;
        }
    }

    void sortByDate()
    {
        if (head == NULL || head->next == NULL)
            return;

        // Simple bubble sort by swapping nodes
        bool swapped;
        Patient* ptr1;
        Patient* lptr = NULL;

        do {
            swapped = false;
            ptr1 = head;
            while (ptr1->next != lptr) {
                if (ptr1->date > ptr1->next->date) {
                    // Swap data
                    swap(ptr1->id, ptr1->next->id);
                    swap(ptr1->name, ptr1->next->name);
                    swap(ptr1->age, ptr1->next->age);
                    swap(ptr1->contact, ptr1->next->contact);
                    swap(ptr1->doctor, ptr1->next->doctor);
                    swap(ptr1->date, ptr1->next->date);
                    swap(ptr1->condition, ptr1->next->condition);
                    swap(ptr1->served, ptr1->next->served);
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1; //it tells us that that nodes at and after lptr are already sorted
        } while (swapped);

        cout << "\nRecords Sorted Successfully\n";
    }
};

struct QueueNode 
{
    int patientID;
    QueueNode* next;

    QueueNode(int id)
    {
        patientID = id;
        next = NULL;
    }
};

class AppointmentQueue
{
public:

    QueueNode* front;
    QueueNode* rear;

    AppointmentQueue()
    {
        front = NULL;
        rear = NULL;
    }

    void enqueue(int id)
    {
        QueueNode* newNode = new QueueNode(id);
        if (front == NULL)
        {
            front = rear = newNode;
        }
        else
        {
            rear->next = newNode; //currently there is data in rear so the empty node is after rear 
            rear = newNode;
        }
    }

    int dequeue()
    {
        if (front == NULL)
        {
            return -1;
        }

        QueueNode* temp = front;

        int id = temp->patientID;

        front = front->next;

        if (front == NULL)//one element in the queue
        {
            rear = NULL;
        }

        delete temp;
        return id;
    }

    void displayQueue(PatientList& list)
    {
        if (front == NULL)
        {
            cout << "\nQueue Empty\n";
            return;
        }

        QueueNode* temp = front;

        cout << "\nToday's Queue\n";

        while (temp != NULL)
        {
            Patient* p = list.searchByID(temp->patientID);

            if (p != NULL)
            {
                cout << "ID: " << p->id;
                cout << "  Name: " << p->name;
                cout << endl;
            }

            temp = temp->next;
        }
    }
};

// Simplified input functions - NO cin.ignore() inside
string getInput(string message)
{
    string value;
    cout << message;
    getline(cin, value);
    return value;
}

int getInt(string message)
{
    int value;
    cout << message;
    cin >> value;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

string getCondition()
{
    int choice;
    cout << "\n1. Emergency";
    cout << "\n2. Normal";
    cout << "\nChoose: ";
    cin >> choice;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choice == 1)
        return "Emergency";
    return "Normal";
}

void displayPatient(Patient* p)
{
    cout << "\nPatient Details\n";
    cout << "ID: " << p->id << endl;
    cout << "Name: " << p->name << endl;
    cout << "Age: " << p->age << endl;
    cout << "Contact: " << p->contact << endl;
    cout << "Doctor: " << p->doctor << endl;
    cout << "Date: " << p->date << endl;
    cout << "Condition: " << p->condition << endl;

    if (p->served)
        cout << "Status: Served\n";
    else
        cout << "Status: Pending\n";
}

void generateReport(PatientList& list)
{
    int total = 0, emergency = 0, normal = 0, served = 0;
    Patient* temp = list.head;

    while (temp != NULL)
    {
        total++;
        if (temp->condition == "Emergency")
            emergency++;
        else
            normal++;

        if (temp->served)
            served++;

        temp = temp->next;
    }

    cout << "\n===== CLINIC REPORT =====\n";
    cout << "Total Patients : " << total << endl;
    cout << "Emergency      : " << emergency << endl;
    cout << "Normal         : " << normal << endl;
    cout << "Served         : " << served << endl;
    cout << "Pending        : " << total - served << endl;
}

void loadSampleData(PatientList& list, AppointmentQueue& queue)
{
    Patient* p1 = new Patient("Ali", 25, "03001234567", "Dr Ayesha", "2026-06-15", "Emergency");
    Patient* p2 = new Patient("Sara", 22, "03111234567", "Dr Bilal", "2026-06-16", "Normal");
    Patient* p3 = new Patient("Ahmed", 30, "03221234567", "Dr Ayesha", "2026-06-17", "Normal");

    list.addPatient(p1);
    list.addPatient(p2);
    list.addPatient(p3);

    queue.enqueue(p1->id);
    queue.enqueue(p2->id);
    queue.enqueue(p3->id);
}

void showMenu()
{
    cout << "\n";
    cout << "===== CLINIC APPOINTMENT SCHEDULER =====\n";
    cout << "1. Add Patient\n";
    cout << "2. Delete Patient\n";
    cout << "3. Search Patient By ID\n";
    cout << "4. Search Patient By Name\n";
    cout << "5. Update Patient\n";
    cout << "6. Display All Patients\n";
    cout << "7. Display Pending Patients\n";
    cout << "8. View Appointment Queue\n";
    cout << "9. Serve Next Patient\n";
    cout << "10. Sort By Date\n";
    cout << "11. Generate Report\n";
    cout << "0. Exit\n";
    cout << "Enter Choice: ";
}

int main()
{
    PatientList list;
    AppointmentQueue queue;
    loadSampleData(list, queue);

    int choice;

    do
    {
        showMenu();
        cin >> choice;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
        {
            cout << "\nAdd New Patient\n";

            string name = getInput("Enter Name: ");
            int age = getInt("Enter Age: ");
            string contact = getInput("Enter Contact: ");
            string doctor = getInput("Enter Doctor Name: ");
            string date = getInput("Enter Date (YYYY-MM-DD): ");
            string condition = getCondition();

            Patient* p = new Patient(name, age, contact, doctor, date, condition);
            list.addPatient(p);
            queue.enqueue(p->id);

            cout << "\nPatient Added Successfully\n";
            cout << "Appointment ID: " << p->id << endl;
            break;
        }

        case 2:
        {
            int id = getInt("Enter ID: ");
            list.deletePatient(id);
            break;
        }

        case 3:
        {
            int id = getInt("Enter ID: ");
            Patient* p = list.searchByID(id);
            if (p != NULL)
                displayPatient(p);
            else
                cout << "\nPatient Not Found\n";
            break;
        }

        case 4:
        {
            string name = getInput("Enter Name: ");
            Patient* p = list.searchByName(name);
            if (p != NULL)
                displayPatient(p);
            else
                cout << "\nPatient Not Found\n";
            break;
        }

        case 5:
        {
            int id = getInt("Enter Patient ID: ");
            Patient* p = list.searchByID(id);

            if (p == NULL)
            {
                cout << "\nPatient Not Found\n";
                break;
            }

            cout << "\nUpdate Menu\n";
            cout << "1. Contact\n";
            cout << "2. Doctor\n";
            cout << "3. Date\n";

            int option = getInt("Choose Option: ");

            if (option == 1)
                p->contact = getInput("New Contact: ");
            else if (option == 2)
                p->doctor = getInput("New Doctor: ");
            else if (option == 3)
                p->date = getInput("New Date: ");

            cout << "\nRecord Updated Successfully\n";
            break;
        }

        case 6:
            list.displayAll();
            break;

        case 7:
            list.displayPending();
            break;

        case 8:
            queue.displayQueue(list);
            break;

        case 9:
        {
            int id = queue.dequeue();
            if (id == -1)
                cout << "\nQueue Empty\n";
            else
            {
                Patient* p = list.searchByID(id);
                if (p != NULL)
                {
                    p->served = true;
                    cout << "\nNow Serving: " << p->name << endl;
                }
            }
            break;
        }

        case 10:
            list.sortByDate();
            break;

        case 11:
            generateReport(list);
            break;

        case 0:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice\n";
        }

    } while (choice != 0);

    // Clean up memory
    Patient* temp = list.head;
    while (temp != NULL)
    {
        Patient* del = temp;
        temp = temp->next;
        delete del;
    }
}
