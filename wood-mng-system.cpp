#include <iostream>
#include <string>
#include <cstdlib> // stands for c standard library, used for system() function
#include <fstream> // for file handling

using namespace std;

//Screen clear commad function that works on Windows, macOS.
void clearScreen() {
    #ifdef _WIN32
        system("cls");     // For Windows
    #else
        system("clear");   // For macOS
    #endif
}

//Global variables to hold data across multiple portals
int orderID[100];
string orderName[100];
string orderStatus[100];
int totalOrders = 0;
int nextID = 1;

// Stock Data (Updated by Supervisor, Checked by Manager)
int pureWoodStock = 20;  //  dummy stock
int sheetWoodStock = 30; //  dummy stock

// Staff Attendance Manager / Supervisor / Chief Foe Admin Portal.
string staffNames[3] = {"Manager", "Chief", "Supervisor"};
bool staffMarked[3] = {false, false, false};

//Decleared so it accessible to Admin Portal to view all portals and their data
void managerPortal();
void supervisorPortal();
void chiefPortal();

//File handling Bsic functions to keep the recorde of data .we have also create a sting variable name as data to store the data in string format and then we will save it in the file.
void logToFile(string filename, string data) {
    ofstream file(filename.c_str(), ios::app); // Open in append mode
    if (file.is_open()) {
        file << data << "\n";
        file.close();
    } else {
        cout << "[Warning: Unable to open file to save record: " << filename << "]\n";
    }
}


// SECURITY FUNCTION

bool checkPassword() {
    int inputPass;
    cout << "\n--------------------------------";
    cout << "\n   SECURE PORTAL ACCESS";
    cout << "\n--------------------------------";
    cout << "\nEnter Passcode: ";
    cin >> inputPass;
    
    if (inputPass == 1234) {
        cout << "Access Granted!\n";
        return true;
    } else {
        cout << "Access Denied! Wrong Password.\n";
        return false;
    }
}

// 1. ADMIN PORTAL (Controls All)

void adminPortal() {
    int choice;
    do {
        cout << "\n========================================" << endl;
        cout << "           ADMIN DASHBOARD              " << endl;
        cout << "========================================" << endl;
        cout << "1. View All Orders (From Manager Portal)" << endl;
        cout << "2. Staff Attendance (Manager/Chief/Supervisor)" << endl;
        cout << "3. View Live Stock Inventory" << endl;
        cout << "4. View Manager Portal" << endl;
        cout << "5. View Supervisor Portal" << endl;
        cout << "6. View Chief Portal" << endl;
        cout << "0. GO BACK TO MAIN MENU" << endl;
        cout << "Enter Choice: ";
        cin >> choice;

        if (choice == 0) break;

        if (choice == 1) {
            cout << "\n--- LIVE ORDER TRACKING ---\n";
            if (totalOrders == 0) cout << "No orders in system.\n";
            for (int i = 0; i < totalOrders; i++) {
                cout << "ID: " << orderID[i] << " | Name: " << orderName[i] << " | Status: " << orderStatus[i] << endl;
            }
        }
        else if (choice == 2) {
            cout << "\n--- STAFF ATTENDANCE ---\n";
            cout << "1. Mark Attendance\n2. View Attendance\n0. GO BACK\nChoice: ";
            int aChoice; cin >> aChoice;
            
            if (aChoice == 1) {
                cout << "Select Staff:\n1. Manager\n2. Chief\n3. Supervisor\nChoice: ";
                int staffChoice; cin >> staffChoice;
                if (staffChoice >= 1 && staffChoice <= 3) {
                    staffMarked[staffChoice - 1] = true;
                    cout << staffNames[staffChoice - 1] << " Marked Present.\n";
                    
                    // SAVE TO FILE
                    logToFile("Records_Attendance.txt", "STAFF PRESENT: " + staffNames[staffChoice - 1]);
                }
            } else if (aChoice == 2) {
                for(int i=0; i<3; i++) {
                    cout << staffNames[i] << ": " << (staffMarked[i] ? "Present" : "Absent") << endl;
                }
            }
        }
        else if (choice == 3) {
            cout << "\n--- LIVE STOCK RECORDS ---\n";
            cout << "Pure Wood Stock: " << pureWoodStock << " units\n";
            cout << "Sheet Wood Stock: " << sheetWoodStock << " units\n";
        }
        else if (choice == 4) {
            managerPortal();
        }
        else if (choice == 5) {
            supervisorPortal();
        }
        else if (choice == 6) {
            chiefPortal();
        }

    } while (true);
}


// 2. MANAGER PORTAL (Orders, Salary, Notifications)

void managerPortal() {
    int choice;
    do {
        cout << "\n========================================" << endl;
        cout << "       MANAGER PORTAL                   " << endl;
        cout << "========================================" << endl;
        cout << "1. Order Management System" << endl;
        cout << "2. Labour Salary Calculator" << endl;
        cout << "3. Shipment & Stock Notifications" << endl;
        cout << "0. GO BACK TO MAIN MENU" << endl;
        cout << "Enter Choice: ";
        cin >> choice;

        if (choice == 0) break;

        if (choice == 1) {
            int orderChoice;
            do {
                cout << "\n--- Order System ---\n1. Add Order\n2. Show Orders\n3. Update Status\n0. GO BACK\nChoice: ";
                cin >> orderChoice;
                
                if (orderChoice == 1) {
                    cin.ignore();
                    orderID[totalOrders] = nextID;
                    nextID++;
                    cout << "Enter Order Name: ";
                    getline(cin, orderName[totalOrders]);
                    orderStatus[totalOrders] = "Pending";
                    
                    // SAVE TO FILE
                    logToFile("Records_Orders.txt", "NEW ORDER - ID: " + to_string(orderID[totalOrders]) + " | Name: " + orderName[totalOrders] + " | Status: Pending");
                    
                    totalOrders++;
                    cout << "Order Added successfully and Saved to File!\n";
                }
                else if (orderChoice == 2) {
                    if (totalOrders == 0) cout << "No Orders available!\n";
                    else {
                        for (int i = 0; i < totalOrders; i++) 
                            cout << "ID: " << orderID[i] << " | Name: " << orderName[i] << " | Status: " << orderStatus[i] << endl;
                    }
                }
                else if (orderChoice == 3) {
                    int id;
                    cout << "Enter ID to Update: "; cin >> id;
                    bool found = false;
                    for (int i = 0; i < totalOrders; i++) {
                        if (orderID[i] == id) {
                            cout << "Select Status: 1. Pending 2. Processing 3. Completed: ";
                            int st; cin >> st;
                            if(st==1) orderStatus[i]="Pending";
                            else if(st==2) orderStatus[i]="Processing";
                            else if(st==3) orderStatus[i]="Completed";
                            
                            // SAVE TO FILE
                            logToFile("Records_Orders.txt", "UPDATED ORDER - ID: " + to_string(id) + " | New Status: " + orderStatus[i]);
                            
                            cout << "Status Updated and Saved to File!\n";
                            found = true; break;
                        }
                    }
                    if(!found) cout << "Order ID Not Found!\n";
                }
            } while (orderChoice != 0);
        }
        else if (choice == 2) {
            string name;
            int days, wage, late, overtime;
            
            cout << "\n--- Labour Salary ---\n";
            cin.ignore();
            cout << "Enter Name: "; getline(cin, name);
            cout << "Enter Daily Wage: "; cin >> wage;
            cout << "Days Worked: "; cin >> days;
            cout << "Late Days: "; cin >> late;
            cout << "Overtime Hours: "; cin >> overtime;

            int basic = days * wage;
            int bonus = overtime * 200;
            int penalty = late * 100;
            int total = basic + bonus - penalty;

            cout << "\n--- PAY SLIP ---\nName: " << name << "\nNet Salary: " << total << " Rs\n";
            
            // SAVE TO FILE
            logToFile("Records_Salary.txt", "PAY SLIP - Name: " + name + " | Basic: " + to_string(basic) + " | Net Salary: " + to_string(total) + " Rs");
            cout << "(Pay slip saved to Records_Salary.txt)\n";
        }
        else if (choice == 3) {
            cout << "\n--- STOCK NOTIFICATIONS ---\n";
            cout << "Pure Wood Current Stock : " << pureWoodStock << " units\n";
            cout << "Sheet Wood Current Stock: " << sheetWoodStock << " units\n\n";
            
            bool needShipment = false;

            if (pureWoodStock < 10) {
                cout << "[ALERT] Pure Wood is less than 10 units! REQUIRED SHIPMENT!\n";
                needShipment = true;
            }
            if (sheetWoodStock < 15) {
                cout << "[ALERT] Sheet Wood is less than 15 units! REQUIRED SHIPMENT!\n";
                needShipment = true;
            }

            if (!needShipment) {
                cout << "[STATUS] Stock is sufficient. No new shipment required at the moment.\n";
            }
        }

    } while (true);
}


// 3. SUPERVISOR PORTAL (Shipment & Attendance)

void supervisorPortal() {
    int choice;
    int labIds[5] = {101, 102, 103, 104, 105};
    bool labMark[5] = {false, false, false, false, false};

    do {
        cout << "\n========================================" << endl;
        cout << "       SUPERVISOR PORTAL                " << endl;
        cout << "========================================" << endl;
        cout << "1. Shipment & Storage Management" << endl;
        cout << "2. Labour Attendance" << endl;
        cout << "3. Labour Work Status" << endl;
        cout << "0. GO BACK TO MAIN MENU" << endl;
        cout << "Enter Choice: ";
        cin >> choice;

        if (choice == 0) break;

        if (choice == 1) {
            int sChoice;
            do {
                cout << "\n--- Shipment & Storage ---\n";
                cout << "1. Receive Stock (Add)\n2. Dispatch/Use Stock (Remove)\n3. Check Current Stock\n0. GO BACK\nChoice: ";
                cin >> sChoice;
                
                if (sChoice == 1) {
                    cout << "1. Pure Wood\n2. Sheet Wood\nSelect Material: ";
                    int mat; cin >> mat;
                    cout << "Enter Quantity to Add: ";
                    int qty; cin >> qty;
                    string matName;
                    
                    if (mat == 1) { pureWoodStock += qty; matName = "Pure Wood"; }
                    else if (mat == 2) { sheetWoodStock += qty; matName = "Sheet Wood"; }
                    
                    cout << "Stock Added Successfully!\n";
                    
                    // SAVE TO FILE
                    logToFile("Records_Stock.txt", "STOCK ADDED: " + to_string(qty) + " units of " + matName);
                } 
                else if (sChoice == 2) {
                    cout << "1. Pure Wood\n2. Sheet Wood\nSelect Material to Use: ";
                    int mat; cin >> mat;
                    cout << "Enter Quantity to Use: ";
                    int qty; cin >> qty;
                    string matName;
                    
                    if (mat == 1) {
                        if(pureWoodStock >= qty) { pureWoodStock -= qty; matName = "Pure Wood"; }
                        else { cout << "Not enough Pure Wood in storage!\n"; continue; }
                    } else if (mat == 2) {
                        if(sheetWoodStock >= qty) { sheetWoodStock -= qty; matName = "Sheet Wood"; }
                        else { cout << "Not enough Sheet Wood in storage!\n"; continue; }
                    }
                    cout << "Stock Used Successfully!\n";
                    
                    // SAVE TO FILE
                    logToFile("Records_Stock.txt", "STOCK USED: " + to_string(qty) + " units of " + matName);
                } 
                else if (sChoice == 3) {
                    cout << "Pure Wood Stock: " << pureWoodStock << endl;
                    cout << "Sheet Wood Stock: " << sheetWoodStock << endl;
                }
            } while (sChoice != 0);
        }
        else if (choice == 2) {
            cout << "\n--- Labour Attendance ---\n1. Mark Attendance\n2. View Attendance\n0. GO BACK\nChoice: ";
            int aChoice; cin >> aChoice;
            if(aChoice == 1) {
                cout << "Enter ID (101-105): "; int id; cin >> id;
                bool found = false;
                for(int i=0; i<5; i++) {
                    if(labIds[i] == id) { 
                        labMark[i] = true; 
                        cout << "Attendance Marked!\n"; 
                        // SAVE TO FILE
                        logToFile("Records_Attendance.txt", "LABOUR PRESENT - ID: " + to_string(id));
                        found=true; 
                    }
                }
                if(!found) cout << "Invalid ID!\n";
            } else if(aChoice == 2) {
                for(int i=0; i<5; i++) cout << "Worker " << labIds[i] << " : " << (labMark[i] ? "Present" : "Absent") << endl;
            }
        }
        else if (choice == 3) {
            cout << "\n--- Work Status ---\n1. Mark Worker Busy\n2. Check Available Workers\n0. GO BACK\nChoice: ";
            int wChoice; cin >> wChoice;
            if(wChoice == 1) {
                 cout << "Enter Worker ID to set BUSY: "; int id; cin >> id;
                 cout << "Worker " << id << " is now marked BUSY on a project.\n";
                 // SAVE TO FILE
                 logToFile("Records_WorkStatus.txt", "WORKER BUSY - ID: " + to_string(id));
            } else if (wChoice == 2) {
                cout << "Workers 102, 104, 105 are currently Available.\n"; 
            }
        }

    } while (true);
}

// 4. CHIEF PORTAL (Wood Cost Estimator)

void chiefPortal() {
    int mainOption, subOption, materialType;
    float length, width, area, totalCost;
    
    float rate_wood = 800.0, rate_sheet = 200.0;
    float rate_cutting_wood = 40.0, rate_cutting_sheet = 25.0;
    float rate_polish = 250.0, rate_tapping = 60.0;       
    float rate_labor = 200.0;       

    while (true) {
        totalCost = 0;
        area = 0;

        cout << "\n========================================" << endl;
        cout << "      CHIEF PORTAL: COST ESTIMATION     " << endl;
        cout << "========================================" << endl;
        cout << "1. Full Furniture Estimation" << endl;
        cout << "2. Only Services (Cutting/Finishing)" << endl;
        cout << "0. GO BACK TO MAIN MENU" << endl;
        cout << "Enter Choice: ";
        cin >> mainOption;

        if (mainOption == 0) break; 

        if (mainOption == 1) {
            cout << "\n--- Select Item ---" << endl;
            cout << "1. Wardrobe / Cabinet\n2. Italian Kitchen\n3. Media Wall\n4. Bed\n5. Wood Flooring\n6. Door\n0. GO BACK\nChoice: ";
            cin >> subOption;
            if (subOption == 0) continue; 

            cout << "Enter Length/Height (ft): "; cin >> length;
            cout << "Enter Width (ft): "; cin >> width;
            area = length * width;

            cout << "\nSelect Material:\n1. Pure Wood\n2. Laminated Sheet\nChoice: ";
            cin >> materialType;

            float materialPrice = 0, finishPrice = 0, cuttingPrice = 0;

            if (materialType == 1) { 
                materialPrice = area * rate_wood;
                finishPrice = area * rate_polish;
                cuttingPrice = area * rate_cutting_wood;
            } else { 
                materialPrice = area * rate_sheet;
                finishPrice = area * rate_tapping;
                cuttingPrice = area * rate_cutting_sheet;
            }
            float laborPrice = area * rate_labor;
            totalCost = materialPrice + finishPrice + cuttingPrice + laborPrice;

            cout << "\n--- ESTIMATED BILL ---\nTOTAL COST: " << totalCost << " Rs\n";
            
            // SAVE TO FILE
            logToFile("Records_Estimations.txt", "FULL FURNITURE ESTIMATE - Area: " + to_string(area) + " sq.ft | Total Cost: " + to_string(totalCost) + " Rs");
            cout << "(Estimate saved to Records_Estimations.txt)\n";
        }
        else if (mainOption == 2) {
            cout << "\n--- Select Service ---\n1. Only Cutting\n2. Only Finishing\n0. GO BACK\nChoice: ";
            cin >> subOption;
            if (subOption == 0) continue;

            cout << "Enter Length (ft): "; cin >> length;
            cout << "Enter Width (ft): "; cin >> width;
            area = length * width;

            cout << "Select Material:\n1. Pure Wood\n2. Sheet\nChoice: "; cin >> materialType;

            if (subOption == 1) { 
                if (materialType == 1) totalCost = area * rate_cutting_wood;
                else totalCost = area * rate_cutting_sheet;
            } else if (subOption == 2) { 
                if (materialType == 1) totalCost = area * rate_polish;
                else totalCost = area * rate_tapping;
            }
            cout << "\nTotal Service Cost: " << totalCost << " Rs\n";
            
            // SAVE TO FILE
            logToFile("Records_Estimations.txt", "SERVICE ESTIMATE - Area: " + to_string(area) + " sq.ft | Cost: " + to_string(totalCost) + " Rs");
            cout << "(Estimate saved to Records_Estimations.txt)\n";
        }
    }
}


// MAIN FUNCTION (Start Page)

int main() {
    int role;

    while (true) {
        clearScreen(); // OS-independent screen clear
        
        cout << "\n=============================================" << endl;
        cout << "      WOOD WORK SHOP MANAGEMENT SYSTEM       " << endl;
        cout << "=============================================" << endl;
        cout << "1. Admin Portal" << endl;
        cout << "2. Manager Portal" << endl;
        cout << "3. Supervisor Portal" << endl;
        cout << "4. Chief Portal" << endl;
        cout << "5. Exit System" << endl;
        cout << "=============================================" << endl;
        cout << "Enter your choice: ";
        cin >> role;

        if (role == 5) {
            cout << "\nShutting Down System... Goodbye!\n";
            break;
        }

        // Apply Password Check before letting anyone into a portal
        if (role >= 1 && role <= 4) {
            if (checkPassword()) {
                switch (role) {
                    case 1:
                        adminPortal();
                        break;
                    case 2:
                        managerPortal();
                        break;
                    case 3:
                        supervisorPortal();
                        break;
                    case 4:
                        chiefPortal();
                        break;
                }
            } else {
                cout << "Returning to Main Menu...\n";
            }
        } else {
            cout << "\nInvalid Selection! Please choose an option between 1 and 5.\n";
        }
        
        cout << "\nPress Enter to Continue...";
        cin.ignore();
        cin.get();
    }

    return 0;
}