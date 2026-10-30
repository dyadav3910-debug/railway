#include <iostream>
#include <string>
using namespace std;

struct Passenger {
    int seatNo;
    string name;
    int age;
    char gender;
    Passenger* next;
};

int* seats;
Passenger* head = NULL;
int totalSeats = 30;

void bookTicket() {
    int seat = -1;

    for (int i = 0; i < totalSeats; i++) {
        if (seats[i] == 0) {
            seat = i;
            break;
        }
    }

    if (seat == -1) {
        cout << "No seats available.\n";
        return;
    }

    Passenger* p = new Passenger;

    p->seatNo = seat + 1;

    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, p->name);

    cout << "Enter Age: ";
    cin >> p->age;

    cout << "Enter Gender (M/F): ";
    cin >> p->gender;

    p->next = head;
    head = p;

    seats[seat] = 1;

    cout << "Ticket booked! Seat No: " << seat + 1 << endl;
}

void cancelTicket() {
    int seat;
    cout << "Enter Seat Number: ";
    cin >> seat;

    if (seat < 1 || seat > totalSeats || seats[seat - 1] == 0) {
        cout << "Invalid or unbooked seat.\n";
        return;
    }

    Passenger* temp = head;
    Passenger* prev = NULL;

    while (temp != NULL && temp->seatNo != seat) {
        prev = temp;
        temp = temp->next;
    }

    if (temp != NULL) {
        if (prev == NULL)
            head = temp->next;
        else
            prev->next = temp->next;

        delete temp;
        seats[seat - 1] = 0;

        cout << "Ticket cancelled successfully.\n";
    }
}

void viewTrainStatus() {
    cout << "\nTrain Seat Status:\n";

    for (int i = 0; i < totalSeats; i++) {
        cout << "Seat " << i + 1 << ": ";

        if (seats[i] == 1)
            cout << "Booked";
        else
            cout << "Available";

        cout << endl;
    }
}

void viewPassengerList() {
    Passenger* temp = head;

    if (temp == NULL) {
        cout << "No passenger records found.\n";
        return;
    }

    cout << "\nPassenger List:\n";

    while (temp != NULL) {
        cout << "Seat No: " << temp->seatNo
             << " | Name: " << temp->name
             << " | Age: " << temp->age
             << " | Gender: " << temp->gender << endl;

        temp = temp->next;
    }
}

void freeMemory() {
    Passenger* temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        delete temp;
    }

    delete[] seats;
}

int main() {
    seats = new int[totalSeats]();

    int choice;

    do {
        cout << "\n===== Railway Reservation System =====\n";
        cout << "1. Book Ticket\n";
        cout << "2. Cancel Ticket\n";
        cout << "3. View Train Status\n";
        cout << "4. View Passenger List\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice) {
            case 1:
                bookTicket();
                break;

            case 2:
                cancelTicket();
                break;

            case 3:
                viewTrainStatus();
                break;

            case 4:
                viewPassengerList();
                break;

            case 5:
                freeMemory();
                cout << "Program exited successfully.\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
