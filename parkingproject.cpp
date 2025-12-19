#include <iostream>
#include <fstream>   // for file handling
#include <cstdlib>   //system("cls");
#include <windows.h> // For Windows color functions
#include <iomanip>   // for setw
using namespace std;
/*Code Color
7 Light Gray (Default)
10 Light Green
11 Light Cyan
12 Light Red
13 Light Magenta
14 Yellow
15 Bright White
🟦 BACKGROUND COLORS
Code Color
0 Black
1 Blue
2 Green
3 Cyan
4 Red
5 Magenta
6 Yellow
7 Light Gray
⭐ READY-MADE COLOR COMBINATIONS (BEST PICKS)
Purpose Text Background Code
Default Gray Black setColor(7,0)
Header / Title Yellow Blue setColor(14,1)
Success Light Green Black setColor(10,0)
Warning Yellow Black setColor(14,0)
Error Light Red Black setColor(12,0)
Info Light Cyan Black setColor(11,0)
Admin Panel White Red setColor(15,4)
Highlight Black Yellow setColor(0,6)
Disabled Gray Gray setColor(7,7)*/
// ============ CONSTANTS ============
int MAX_SLOTS = 20;
int RATE_BIKE = 10;
int RATE_CAR = 20;
int RATE_SUV = 30;
int MONTHLY_PRICE = 2000;
// ============ ARRAYS FOR PARKING SLOTS ============
int slotStatus[99];
string plateNumber[99];
string vehicleType[99];
int startHour[99];
string owner[99];
int count = 0;
int totalRevenue = 0;
// ============ CLEAR SCREEN ============
void clearScreen()
{
    system("cls");
}
void setColor(int text, int background = 0)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, text + background * 16);
}
// ============ DISPLAY HEADERS ============
void showWelcome()
{
    clearScreen();
    cout << "\n";
    setColor(14);
    cout << "============================================================\n";
    cout << " \n";
    cout << " PARKING MANAGEMENT SYSTEM \n";
    cout << " \n";
    cout << " Welcome to Smart Parking! \n";
    cout << " \n";
    cout << "============================================================\n";
    cout << "\n";
    setColor(7);
}
void showHeader(string title)
{
    clearScreen();
    setColor(14);
    cout << "\n";
    cout << "===========================================================\n";
    cout << " " << title << "\n";
    cout << "===========================================================\n\n";
    setColor(7);
}
void pressEnter()
{
    cout << "\nPress Enter to continue...";

    // Clear any leftover input
    cin.sync();

    // Wait for Enter
    cin.get();
}
// ============ INPUT VALIDATION ============
int getInt(string prompt)
{
    int num;
    char extra;
    while (true)
    {
        cout << prompt;
        if (!(cin >> num))
        {
            setColor(12);
            cout << "Invalid input! Please enter a number only.\n";
            setColor(7);
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        // Check if extra characters exist
        if (cin.get(extra) && extra != '\n')
        {
            setColor(12);
            cout << "Invalid input! Extra characters detected.\n";
            setColor(7);
            cin.ignore(10000, '\n');
            continue;
        }
        return num;
    }
}
int getIntInRange(string prompt, int min, int max)
{
    int num;
    while (true)
    {
        num = getInt(prompt);
        if (num >= min && num <= max)
        {
            return num;
        }
        setColor(12);
        cout << "Please enter a number between " << min << " and " << max << ".\n";
        setColor(7);
    }
}
bool isValidEmail(string email)
{
    // Check if email is at least 10 chars (a@b.c minimum)
    if (email.length() < 10)
    {
        return false;
    }

    // Check if email contains '@' and it's not at start or end
    bool hasAt = false;
    for (int i = 1; i < email.length() - 1; i++)
    { // Start from 1, end before last
        if (email[i] == '@')
        {
            hasAt = true;
            break;
        }
    }
    return hasAt;
}
bool hasNoSpaces(string text)
{
    // Check if text has no spaces
    for (int i = 0; i < text.length(); i++)
    {
        if (text[i] == ' ')
        {
            return false;
        }
    }
    return true;
}
bool isValidPassword(string password)
{
    if (password.length() < 7)
    {
        return false;
    }

    bool hasNumber = false;
    for (int i = 0; i < password.length(); i++)
    {
        if (password[i] >= '0' && password[i] <= '9')
        {
            hasNumber = true;
            break;
        }
    }

    return hasNumber;
}
// ============ LOAD/SAVE REVENUE ============
void loadRevenue()
{
    ifstream file("revenue.txt");
    if (file)
    {
        file >> totalRevenue;
        file.close();
    }
}
void saveRevenue()
{
    ofstream file("revenue.txt");
    file << totalRevenue;
    file.close();
}
// ============ LOAD/SAVE PRICES ============
void loadPrices()
{
    ifstream file("prices.txt");
    if (file)
    {
        file >> RATE_BIKE >> RATE_CAR >> RATE_SUV >> MONTHLY_PRICE >> MAX_SLOTS;
        file.close();
    }
}
void savePrices()
{
    ofstream file("prices.txt");
    file << RATE_BIKE << " " << RATE_CAR << " " << RATE_SUV << " " << MONTHLY_PRICE << " " << MAX_SLOTS;
    file.close();
}
// ============ LOAD/SAVE PARKING SLOTS ============
void saveSlots()
{
    ofstream file("slots.txt");
    if (!file)
        return;

    for (int i = 0; i < MAX_SLOTS; i++)
    {
        file << slotStatus[i] << " " << plateNumber[i] << " "
             << vehicleType[i] << " " << startHour[i] << " " << owner[i] << "\n";
    }
    file.close();
}
void loadSlots()
{
    ifstream file("slots.txt");
    if (!file)
        return;

    for (int i = 0; i < MAX_SLOTS; i++)
    {
        if (!(file >> slotStatus[i] >> plateNumber[i] >> vehicleType[i] >> startHour[i] >> owner[i]))
        {
            break;
        }
    }
    file.close();
}
// ============ AUTHENTICATION ============
bool signUp()
{
    while (true)
    {
        showHeader("SIGN UP");

        string email, firstName, password;

        // Email validation loop
        while (true)
        {
            cout << "Enter email (must contain @, min 10 chars) or type 'back' to return: ";
            getline(cin, email);

            if (email == "back" || email == "Back")
            {
                return false;
            }

            if (isValidEmail(email) && hasNoSpaces(email))
            {
                break;
            }
            else
            {
                setColor(12);
                cout << "Invalid email! Must be at least 10 characters and contain '@' (not at start/end) and doesnt have any spaces.\n";
                setColor(7);
            }
        }

        // Check if email already exists
        ifstream checkFile("users.txt");
        string fileE, fileN, fileP;
        bool emailExists = false;
        while (checkFile >> fileE >> fileN >> fileP)
        {
            if (fileE == email)
            {
                emailExists = true;
                break;
            }
        }
        checkFile.close();

        if (emailExists)
        {
            setColor(12);
            cout << "Email already exists! Please use another email.\n";
            setColor(7);
            pressEnter();
            continue;
        }

        // First name validation loop
        // cin.ignore();
        while (true)
        {
            cout << "Enter first name (no spaces, 2-20 chars) or type 'back' to return: ";
            getline(cin, firstName);

            if (firstName == "back" || firstName == "Back")
            {
                return false;
            }

            if (!hasNoSpaces(firstName))
            {
                setColor(12);
                cout << "First name cannot contain spaces!\n";
                setColor(7);
            }
            else if (firstName.length() < 2 || firstName.length() > 20)
            {
                setColor(12);
                cout << "First name must be between 2 and 20 characters!\n";
                setColor(7);
            }
            else
            {
                break;
            }
        }

        // Password validation loop
        while (true)
        {
            cout << "Enter password (min 7 chars, must include a number) or type 'back' to return: ";
            cin >> password;

            if (password == "back")
            {
                return false;
            }

            if (isValidPassword(password))
            {
                break;
            }
            else
            {
                setColor(12);
                cout << "Password must be at least 7 characters and contain a number!\n";
                setColor(7);
            }
        }
        ofstream file("users.txt", ios::app);
        if (!file)
        {
            setColor(12);
            cout << "Error opening file!\n";
            setColor(7);
            pressEnter();
            return false;
        }
        file << email << " " << firstName << " " << password << "\n";
        file.close();

        setColor(10);
        cout << "\n===============================================\n";
        cout << " Signup successful! Welcome " << firstName << "! \n";
        cout << "===============================================\n";
        setColor(7);
        pressEnter();
        return true;
    }
}
bool signIn(string &loggedUser)
{
    while (true)
    {
        showHeader("SIGN IN");

        string email, password, fileE, fileN, fileP;

        cout << "Enter email or type 'back' to return: ";
        cin >> email;

        if (email == "back")
        {
            return false;
        }

        cout << "Enter password: ";
        cin >> password;
        ifstream file("users.txt");
        if (!file)
        {
            setColor(12);
            cout << "No users found! Please sign up first.\n";
            setColor(7);
            pressEnter();
            return false;
        }
        bool found = false;
        while (file >> fileE >> fileN >> fileP)
        {
            if (fileE == email && fileP == password)
            {
                found = true;
                loggedUser = fileN;
                break;
            }
        }
        file.close();

        if (found)
        {
            setColor(10);
            cout << "\n===============================================\n";
            cout << " Login successful! Welcome " << loggedUser << "! \n";
            cout << "===============================================\n";
            setColor(7);
            pressEnter();
            return true;
        }

        setColor(12);
        cout << "\nInvalid email or password! Please try again.\n";
        setColor(7);
        cout << "Press Enter to retry or type 'back' and press Enter to return...";
        cin.ignore();
        string choice;
        getline(cin, choice);

        if (choice == "back")
        {
            return false;
        }
    }
}
bool adminLogin()
{
    while (true)
    {
        showHeader("ADMIN LOGIN");

        string username, password;

        cout << "Enter admin username or type 'back' to return: ";
        cin >> username;

        if (username == "back")
        {
            return false;
        }

        cout << "Enter admin password: ";
        cin >> password;
        if (username == "admin" && password == "admin123")
        {
            setColor(10);
            cout << "\n===============================================\n";
            cout << " Admin login successful! \n";
            cout << "===============================================\n";
            setColor(7);
            pressEnter();
            return true;
        }

        setColor(12);
        cout << "\nInvalid admin username or password! Please try again.\n";
        setColor(7);
        cout << "Press Enter to retry or type 'back' and press Enter to return...";
        cin.ignore();
        string choice;
        getline(cin, choice);

        if (choice == "back")
        {
            return false;
        }
    }
}
// ============ HELPER FUNCTIONS ============
int findEmptySlot()
{
    for (int i = 0; i < MAX_SLOTS; i++)
    {
        if (slotStatus[i] == 0)
            return i;
    }
    return -1;
}
int findSlotByPlate(string plate)
{
    for (int i = 0; i < MAX_SLOTS; i++)
    {
        if ((slotStatus[i] == 1 || slotStatus[i] == 2) && plateNumber[i] == plate)
        {
            return i;
        }
    }
    return -1;
}
int findDedicatedSlot(string username)
{
    for (int i = 0; i < MAX_SLOTS; i++)
    {
        if (slotStatus[i] == 2 && owner[i] == username)
        {
            return i;
        }
    }
    return -1;
}
int getRateForType(string type)
{
    if (type == "bike")
        return RATE_BIKE;
    if (type == "car")
        return RATE_CAR;
    if (type == "suv")
        return RATE_SUV;
    return RATE_CAR;
}
// ============ VIEW PRICES ============
void viewPrices()
{
    showHeader("PARKING PRICES");

    setColor(14); // Yellow for table borders
    cout << "-----------------------------------------\n";
    cout << left << setw(15) << " Vehicle Type" << "| " << setw(10) << "Rate/Hour" << "\n";
    cout << "-----------------------------------------\n";

    setColor(10); // Green
    cout << left << setw(15) << " Bike" << "| Rs. " << setw(10) << RATE_BIKE << " \n";
    setColor(11); // Cyan
    cout << left << setw(15) << " Car" << "| Rs. " << setw(10) << RATE_CAR << " \n";
    setColor(12); // Red
    cout << left << setw(15) << " SUV" << "| Rs. " << setw(10) << RATE_SUV << " \n";

    setColor(14); // Yellow
    cout << "-----------------------------------------\n";
    setColor(13); // Magenta
    cout << left << setw(15) << " Monthly Slot" << "| Rs. " << setw(10) << MONTHLY_PRICE << " \n";
    setColor(14);
    cout << "-----------------------------------------\n";

    setColor(7);
    pressEnter();
}

// ============ VIEW SLOTS ============
void viewSlots()
{
    showHeader("PARKING SLOTS");

    cout << "Total Slots: " << MAX_SLOTS << "\n\n";
    setColor(14); // Yellow borders
    cout << "---------------------------------------------------------------\n";
    cout << left << setw(6) << " Slot" << "| " << setw(10) << "Status" << "| " << setw(10) << "Plate"
         << "| " << setw(8) << "Type" << "| " << setw(15) << "Owner" << "\n";
    cout << "---------------------------------------------------------------\n";

    for (int i = 0; i < MAX_SLOTS; i++)
    {
        string statusStr = "-";
        string plateStr = plateNumber[i].empty() ? "-" : plateNumber[i];
        string typeStr = vehicleType[i].empty() ? "-" : vehicleType[i];
        string ownerStr = owner[i].empty() ? "-" : owner[i];

        if (slotStatus[i] == 0)
        {
            statusStr = "EMPTY";
            setColor(10); // Green for empty
        }
        else if (slotStatus[i] == 1)
        {
            statusStr = "OCCUPIED";
            setColor(12); // Red for occupied
        }
        else
        {
            statusStr = "DEDICATED";
            setColor(11); // Cyan for dedicated
        }

        cout << left << setw(6) << (i + 1) << "| " << setw(10) << statusStr << "| "
             << setw(10) << plateStr << "| " << setw(8) << typeStr << "| " << setw(15) << ownerStr << "\n";
    }

    setColor(14);
    cout << "---------------------------------------------------------------\n";
    setColor(7); // Reset to default
    pressEnter();
}
// ============ PARK CAR ============
void parkCar(string username)
{
    showHeader("PARK CAR");

    int dedicatedSlot = findDedicatedSlot(username);
    int slot = -1;
    if (dedicatedSlot != -1)
    {
        cout << "You have a dedicated slot #" << dedicatedSlot + 1 << "\n";
        int choice = getIntInRange("Use dedicated slot? (1=Yes, 2=No): ", 1, 2);
        if (choice == 1)
        {
            slot = dedicatedSlot;
        }
    }
    if (slot == -1)
    {
        slot = findEmptySlot();
        if (slot == -1)
        {
            setColor(12);
            cout << "No empty slots available!\n";
            setColor(7);
            pressEnter();
            return;
        }
    }
    string plate;
    while (true)
    {
        cout << "Enter plate number (Format: ABC-1234) or type 'back' to return: ";
        cin >> plate;

        if (plate == "back")
        {
            return;
        }

        if (findSlotByPlate(plate) != -1)
        {
            setColor(12);
            cout << "This vehicle is already parked! Please enter plate number.\n";
            setColor(7);
        }
        else
        {
            break;
        }
    }
    while (true)
    {
        cout << "\nVehicle type:\n";
        cout << "1. Bike\n";
        cout << "2. Car\n";
        cout << "3. SUV\n";
        int typeChoice = getIntInRange("Select type (1-3): ", 1, 3);

        if (typeChoice == 1)
        {
            vehicleType[slot] = "bike";
            break;
        }
        else if (typeChoice == 2)
        {
            vehicleType[slot] = "car";
            break;
        }
        else if (typeChoice == 3)
        {
            vehicleType[slot] = "suv";
            break;
        }
    }
    startHour[slot] = getIntInRange("Enter start hour (0-23): ", 0, 23);
    slotStatus[slot] = 1;
    plateNumber[slot] = plate;
    owner[slot] = username;
    setColor(10);
    cout << "\nCar parked successfully at slot #" << slot + 1 << "!\n";
    setColor(7);
    ofstream file("parking.txt", ios::app);
    file << "PARK|" << username << "|" << plate << "|" << vehicleType[slot]
         << "|Slot:" << slot + 1 << "|Hour:" << startHour[slot] << "\n";
    file.close();

    saveSlots();
    pressEnter();
}
// ============ REMOVE CAR ============
void removeCar(string username)
{
    showHeader("REMOVE CAR");

    string plate;
    cout << "Enter plate number: ";
    cin >> plate;
    int slot = findSlotByPlate(plate);
    if (slot == -1)
    {
        setColor(12);
        cout << "Vehicle not found!\n";
        setColor(7);
        pressEnter();
        return;
    }
    int endHour = getIntInRange("Enter end hour (0-23): ", 0, 23);
    int hours = endHour - startHour[slot];
    if (hours < 0)
        hours += 24;
    if (hours == 0)
        hours = 1;
    int rate = getRateForType(vehicleType[slot]);
    int bill = 0;

    if (slotStatus[slot] == 2)
    {
        bill = 0;
        cout << "\n-------------------------------------\n";
        cout << " PARKING BILL \n";
        cout << "-------------------------------------\n";
        cout << left << setw(15) << " Vehicle Type:" << vehicleType[slot] << " \n";
        cout << left << setw(15) << " Hours Parked:" << hours << " \n";
        cout << left << setw(15) << " Rate/Hour:" << "Rs. " << rate << " \n";
        cout << "-------------------------------------\n";
        cout << " DEDICATED SLOT USER \n";
        cout << left << setw(15) << " Total Bill:" << "Rs. 0 (FREE!)" << " \n";
        cout << "-------------------------------------\n";
    }
    else
    {
        bill = rate * hours;
        cout << "\n-------------------------------------\n";
        cout << " PARKING BILL \n";
        cout << "-------------------------------------\n";
        cout << left << setw(15) << " Vehicle Type:" << vehicleType[slot] << " \n";
        cout << left << setw(15) << " Hours Parked:" << hours << " \n";
        cout << left << setw(15) << " Rate/Hour:" << "Rs. " << rate << " \n";
        cout << "-------------------------------------\n";
        cout << left << setw(15) << " Total Bill:" << "Rs. " << bill << " \n";
        cout << "-------------------------------------\n";
        totalRevenue += bill;
        saveRevenue();
    }
    ofstream file("parking.txt", ios::app);
    file << "REMOVE|" << username << "|" << plate << "|" << vehicleType[slot]
         << "|Hours:" << hours << "|Bill:" << bill << "|Revenue:" << totalRevenue << "\n";
    file.close();
    if (slotStatus[slot] == 2)
    {
        plateNumber[slot] = "";
        vehicleType[slot] = "";
        startHour[slot] = 0;
    }
    else
    {
        slotStatus[slot] = 0;
        plateNumber[slot] = "";
        vehicleType[slot] = "";
        owner[slot] = "";
        startHour[slot] = 0;
    }
    setColor(10);
    cout << "\nVehicle removed successfully!\n";
    setColor(7);
    saveSlots();
    pressEnter();
}
// ============ BUY MONTHLY SLOT ============
void buyMonthlySlot(string username)
{
    showHeader("BUY MONTHLY SLOT");
    if (findDedicatedSlot(username) != -1)
    {
        setColor(12);
        cout << "You already have a dedicated slot!\n";
        setColor(7);
        pressEnter();
        return;
    }
    int slot = findEmptySlot();
    if (slot == -1)
    {
        setColor(12);
        cout << "No empty slots available!\n";
        setColor(7);
        pressEnter();
        return;
    }
    cout << "Monthly price: Rs. " << MONTHLY_PRICE << "\n";
    cout << "Benefits: Park FREE anytime in your dedicated slot!\n\n";
    int confirm = getIntInRange("Confirm purchase? (1=Yes, 2=No): ", 1, 2);
    if (confirm != 1)
    {
        setColor(12);
        cout << "Purchase cancelled!\n";
        setColor(7);
        pressEnter();
        return;
    }
    slotStatus[slot] = 2;
    owner[slot] = username;
    totalRevenue += MONTHLY_PRICE;
    saveRevenue();
    setColor(10);
    cout << "\nDedicated slot #" << slot + 1 << " purchased successfully!\n";
    cout << "You can now park FREE in this slot anytime!\n";
    setColor(7);
    ofstream file("parking.txt", ios::app);
    file << "MONTHLY|" << username << "|Slot:" << slot + 1 << "|Price:" << MONTHLY_PRICE << "|Revenue:" << totalRevenue << "\n";
    file.close();

    saveSlots();
    pressEnter();
}
// ============ USER MENU ============
void userMenu(string username)
{
    int choice;
    do
    {
        showHeader("USER MENU");
        cout << "Logged in as: " << username << "\n\n";
        cout << "1. Park Car\n";
        cout << "2. Remove Car\n";
        cout << "3. Buy Monthly Slot\n";
        cout << "4. View Slots\n";
        cout << "5. View Prices\n";
        cout << "6. Logout\n\n";
        choice = getIntInRange("Enter choice: ", 1, 6);
        switch (choice)
        {
        case 1:
            parkCar(username);
            break;
        case 2:
            removeCar(username);
            break;
        case 3:
            buyMonthlySlot(username);
            break;
        case 4:
            viewSlots();
            break;
        case 5:
            viewPrices();
            break;
        case 6:
            cout << "Logging out...\n";
            pressEnter();
            break;
        }
    } while (choice != 6);
}
// ============ ADMIN MENU ============
void viewRecords()
{
    showHeader("PARKING RECORDS");

    ifstream file("parking.txt");
    if (!file)
    {
        setColor(12);
        cout << "No records found!\n";
        setColor(7);
        pressEnter();
        return;
    }
    string line;
    int count = 1;
    while (getline(file, line))
    {
        cout << left << setw(4) << count++ << ". " << line << "\n";
    }
    file.close();

    pressEnter();
}
void updatePrices()
{
    showHeader("UPDATE PRICES");

    cout << "Current Prices:\n\n";
    cout << left << setw(10) << "Bike:" << "Rs. " << RATE_BIKE << " per hour\n";
    cout << left << setw(10) << "Car:" << "Rs. " << RATE_CAR << " per hour\n";
    cout << left << setw(10) << "SUV:" << "Rs. " << RATE_SUV << " per hour\n";
    cout << left << setw(10) << "Monthly:" << "Rs. " << MONTHLY_PRICE << "\n\n";

    cout << "Enter new prices:\n";
    RATE_BIKE = getInt("Bike rate (per hour): ");
    RATE_CAR = getInt("Car rate (per hour): ");
    RATE_SUV = getInt("SUV rate (per hour): ");
    MONTHLY_PRICE = getInt("Monthly slot price: ");

    savePrices();
    setColor(10);
    cout << "\nPrices updated successfully!\n";
    setColor(7);
    pressEnter();
}
void updateSlots()
{
    showHeader("UPDATE TOTAL SLOTS");

    cout << "Current total slots: " << MAX_SLOTS << "\n\n";
    int newSlots = getIntInRange("Enter new total slots (1-99): ", 1, 99);

    if (newSlots < MAX_SLOTS)
    {
        setColor(14);
        cout << "Warning: Reducing slots may affect existing parking!\n";
        setColor(7);
        int confirm = getIntInRange("Confirm? (1=Yes, 2=No): ", 1, 2);
        if (confirm != 1)
        {
            setColor(12);
            cout << "Cancelled!\n";
            setColor(7);
            pressEnter();
            return;
        }
    }

    MAX_SLOTS = newSlots;
    savePrices();
    setColor(10);
    cout << "\nSlots updated to " << MAX_SLOTS << " successfully!\n";
    setColor(7);
    pressEnter();
}
// ============ DELETE OLD RECORDS ============
void deleteOldRecords()
{
    showHeader("DELETE OLD RECORDS");

    int confirm = getIntInRange("Are you sure you want to delete all parking records? (1=Yes, 2=No): ", 1, 2);
    if (confirm == 1)
    {
        ofstream file("parking.txt", ios::trunc);
        file.close();
        setColor(10);
        cout << "All parking records have been deleted.\n";
        setColor(7);
    }
    else
    {
        setColor(12);
        cout << "Operation cancelled.\n";
        setColor(7);
    }
    pressEnter();
}
void adminMenu()
{
    int choice;
    do
    {

        showHeader("ADMIN PANEL");
        cout << "1. View Records\n";
        cout << "2. View Slots\n";
        cout << "3. Revenue Report\n";
        cout << "4. Update Prices\n";
        cout << "5. Update Total Slots\n";
        cout << "6. Delete Old Records\n";
        cout << "7. Exit\n\n";
        choice = getIntInRange("Enter choice: ", 1, 7);
        switch (choice)
        {
        case 1:
            viewRecords();
            break;
        case 2:
            viewSlots();
            break;
        case 3:
            showHeader("REVENUE REPORT");
            cout << "---------------------------------\n";
            cout << " TOTAL REVENUE \n";
            cout << "---------------------------------\n";
            cout << " Rs. " << totalRevenue << " \n";
            cout << "---------------------------------\n";
            pressEnter();
            break;
        case 4:
            updatePrices();
            break;
        case 5:
            updateSlots();
            break;
        case 6:
            deleteOldRecords();
            break;
        case 7:
            cout << "Exiting admin panel...\n";
            pressEnter();
            break;
        }
    } while (choice != 7);
}
// ============ MAIN ============
int main()
{
    loadRevenue();
    loadPrices();

    for (int i = 0; i < MAX_SLOTS; i++)
    {
        slotStatus[i] = 0;
        plateNumber[i] = "";
        vehicleType[i] = "";
        owner[i] = "";
        startHour[i] = 0;
    }

    loadSlots();
    int choice;
    do
    {
        showWelcome();

        cout << "1. Sign Up\n";
        cout << "2. Sign In (User)\n";
        cout << "3. Admin Login\n";
        cout << "4. Exit\n\n";
        choice = getIntInRange("Enter choice: ", 1, 4);
        string username;
        switch (choice)
        {
        case 1:
            signUp();
            break;
        case 2:
            if (signIn(username))
            {
                userMenu(username);
            }
            break;
        case 3:
            if (adminLogin())
            {
                adminMenu();
            }
            break;
        case 4:
            clearScreen();
            cout << "\n";
            cout << "============================================================\n";
            cout << " \n";
            cout << " Thank you for using our system! \n";
            cout << " Drive Safe! \n";
            cout << " \n";
            cout << "============================================================\n\n";
            break;
        }
    } while (choice != 4);

    saveSlots();
    return 0;
}