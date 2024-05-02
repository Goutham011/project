#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // For exit()

using namespace std;

// Structure to represent a time slot
struct TimeSlot {
    string day;
    string time;

    TimeSlot(const string& day, const string& time)
        : day(day), time(time) {}
};

// Class to represent a doctor
class Doctor {
public:
    string code;
    string name;
    string specialization;
    vector<TimeSlot> availableSlots;

    Doctor(const string& code, const string& name, const string& specialization)
        : code(code), name(name), specialization(specialization) {}

    void addAvailableSlot(const string& day, const string& time) {
        availableSlots.push_back(TimeSlot(day, time));
    }
};

// Class to represent a user
class User {
public:
    string name;
    string roll;
    string phoneNumber;
    string password;

    User(const string& name, const string& roll, const string& phoneNumber, const string& password)
        : name(name), roll(roll), phoneNumber(phoneNumber), password(password) {}
};

// Class to represent an appointment
class Appointment {
public:
    string doctorCode;
    string patientName;
    string patientRoll;
    string appointmentTime;

    Appointment(const string& doctorCode, const string& patientName, const string& patientRoll, const string& appointmentTime)
        : doctorCode(doctorCode), patientName(patientName), patientRoll(patientRoll), appointmentTime(appointmentTime) {}
};

// Class to represent appointment management system
class AppointmentManagementSystem {
private:
    vector<Doctor> doctors;
    vector<User> users;
    vector<Appointment> appointments;

public:
    // Function prototypes
    void signUp();
    void userLogin();
    void adminLogin();
    void viewDoctorsList();
    void bookAppointment(const User& user);
    void viewBookedAppointments(const User& user);
    void viewAppointments(const string& doctorCode);

    // Constructor to initialize data
    AppointmentManagementSystem() {
        // Populate doctors data
        Doctor smith("D001", "Dr. Smith", "General Physician");
        smith.addAvailableSlot("Monday", "9:00 AM - 5:00 PM");
        doctors.push_back(smith);

        Doctor johnson("D002", "Dr. Johnson", "Dermatologist");
        johnson.addAvailableSlot("Tuesday", "10:00 AM - 6:00 PM");
        doctors.push_back(johnson);

        Doctor williams("D003", "Dr. Williams", "Pediatrician");
        williams.addAvailableSlot("Wednesday", "8:00 AM - 4:00 PM");
        doctors.push_back(williams);

        Doctor brown("D004", "Dr. Brown", "Cardiologist");
        brown.addAvailableSlot("Thursday", "11:00 AM - 7:00 PM");
        doctors.push_back(brown);

        Doctor jones("D005", "Dr. Jones", "Orthopedic Surgeon");
        jones.addAvailableSlot("Friday", "7:00 AM - 3:00 PM");
        doctors.push_back(jones);
    }
};

void AppointmentManagementSystem::signUp() {
    string name, roll, phoneNumber, password;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter roll: ";
    cin >> roll;
    cout << "Enter phone number: ";
    cin >> phoneNumber;
    cout << "Create password: ";
    cin >> password;

    users.push_back(User(name, roll, phoneNumber, password));
    cout << "User signed up successfully!" << endl;
}

void AppointmentManagementSystem::userLogin() {
    string roll, password;
    cout << "Enter roll: ";
    cin >> roll;
    cout << "Enter password: ";
    cin >> password;

    bool found = false;
    for (const User& user : users) {
        if (user.roll == roll && user.password == password) {
            found = true;
            cout << "Login successful!" << endl;
            // Display user functionalities
            while (true) {
                cout << "User Functionalities:" << endl;
                cout << "1. View doctors list" << endl;
                cout << "2. Book an appointment" << endl;
                cout << "3. View booked appointments" << endl;
                cout << "4. Logout" << endl;
                cout << "Choose an option: ";

                int choice;
                cin >> choice;

                switch (choice) {
                    case 1:
                        viewDoctorsList();
                        break;
                    case 2:
                        bookAppointment(user);
                        break;
                    case 3:
                        viewBookedAppointments(user);
                        break;
                    case 4:
                        cout << "Logging out..." << endl;
                        return;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                }
            }
        }
    }

    if (!found) {
        cout << "Invalid roll or password. Please try again." << endl;
    }
}

void AppointmentManagementSystem::adminLogin() {
    string name, password;
    cout << "Enter admin name: ";
    cin >> name;
    cout << "Enter admin password: ";
    cin >> password;

    if (name == "admin" && password == "admin") {
        cout << "Admin login successful!" << endl;
        // Display admin functionalities
        while (true) {
            cout << "Admin Functionalities:" << endl;
            cout << "1. View doctors list" << endl;
            cout << "2. View appointments for a doctor" << endl;
            cout << "3. Logout" << endl;
            cout << "Choose an option: ";

            int choice;
            cin >> choice;

            switch (choice) {
                case 1:
                    viewDoctorsList();
                    break;
                case 2: {
                    cout << "Enter the code of the doctor: ";
                    string doctorCode;
                    cin >> doctorCode;
                    viewAppointments(doctorCode);
                    break;
                }
                case 3:
                    cout << "Logging out..." << endl;
                    return;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        }
    } else {
        cout << "Invalid admin name or password. Please try again." << endl;
    }
}


void AppointmentManagementSystem::viewDoctorsList() {
    cout << "Doctors list:" << endl;
    for (const Doctor& doctor : doctors) {
        cout << "Code: " << doctor.code << endl;
        cout << "Name: " << doctor.name << endl;
        cout << "Specialization: " << doctor.specialization << endl;
        cout << "Available Slots: " << endl;
        for (const TimeSlot& slot : doctor.availableSlots) {
            cout << "Day: " << slot.day << ", Time: " << slot.time << endl;
        }
        cout << endl;
    }
}

void AppointmentManagementSystem::bookAppointment(const User& user) {
    cout << "Enter the code of the doctor you want to book an appointment with: ";
    string doctorCode;
    cin >> doctorCode;

    cout << "Enter your preferred appointment day (e.g., Monday, Tuesday, etc.): ";
    string preferredDay;
    cin >> preferredDay;

    cout << "Enter your preferred appointment time (e.g., 9:00 AM - 5:00 PM): ";
    string preferredTime;
    cin.ignore(); // Ignore newline character in buffer
    getline(cin, preferredTime);

    bool found = false;
    for (Doctor& doctor : doctors) {
        if (doctor.code == doctorCode) {
            for (const TimeSlot& slot : doctor.availableSlots) {
                if (slot.day == preferredDay && slot.time == preferredTime) {
                    found = true;
                    cout << "Booking appointment with Dr. " << doctor.name << " on " << preferredDay << ", " << preferredTime << " successful!" << endl;
                    // Create and store the appointment
                    appointments.push_back(Appointment(doctorCode, user.name, user.roll, preferredDay + ", " + preferredTime));
                    return;
                }
            }
        }
    }

    if (!found) {
        cout << "Invalid doctor code or preferred day/time. Please try again." << endl;
    }
}

void AppointmentManagementSystem::viewBookedAppointments(const User& user) {
    cout << "Booked appointments for " << user.name << " (Roll: " << user.roll << "):" << endl;
    for (const Appointment& appointment : appointments) {
        if (appointment.patientRoll == user.roll) {
            cout << "Doctor Code: " << appointment.doctorCode << endl;
            cout << "Doctor Name: ";
            for (const Doctor& doctor : doctors) {
                if (doctor.code == appointment.doctorCode) {
                    cout << doctor.name << endl;
                    break;
                }
            }
            cout << "Appointment Time: " << appointment.appointmentTime << endl;
            cout << endl;
        }
    }
}

void AppointmentManagementSystem::viewAppointments(const string& doctorCode) {
    cout << "Appointments for Doctor with Code " << doctorCode << ":" << endl;
    for (const Appointment& appointment : appointments) {
        if (appointment.doctorCode == doctorCode) {
            cout << "Patient Name: " << appointment.patientName << endl;
            cout << "Patient Roll: " << appointment.patientRoll << endl;
            cout << "Appointment Time: " << appointment.appointmentTime << endl;
            cout << endl;
        }
    }
}

int main() {
    AppointmentManagementSystem ams;

    while (true) {
        cout << "Welcome to the Appointment Management System" << endl;
        cout << "1. User Login" << endl;
        cout << "2. Admin Login" << endl;
        cout << "3. Sign Up" << endl;
        cout << "4. Exit" << endl;
        cout << "Choose an option: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                ams.userLogin();
                break;
            case 2:
                ams.adminLogin();
                break;
            case 3:
                ams.signUp();
                break;
            case 4:
                cout << "Exiting program..." << endl;
                exit(0); // Terminate the program
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
