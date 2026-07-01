# Wood Workshop Management System (Console-Based)

A comprehensive, multi-portal console application developed in C++ designed to automate and streamline operations in a wood manufacturing workshop. This project focuses on back-end logic, role-based access control, object-oriented concepts, and persistent data storage using C++ File Handling.

## 🚀 Key Features

* **Role-Based Access Control (RBAC):** Integrated security system that requires a master passcode (`1234`) to access management portals.
* **Multi-Portal Architecture:** * **Admin Dashboard:** Central control hub to view all live orders, staff attendance records, stock status, and supervise overall management.
  * **Manager Portal:** Handles client details, dynamic order logging, salary estimations for laborers (including calculations for overtime, active days, and penalties), and critical inventory alerts.
  * **Supervisor Portal:** Manages active production updates, shipment monitoring, wood type segregation, and tracks real-time work statuses of multiple laborers.
  * **Chief Portal (Cost Estimator):** A precise calculator that estimates item creation prices (e.g., Wardrobes, Kitchen setups, Media Walls, Doors) based on dimensions, wood type selection (Pure Wood vs. Sheet), polish, cutting, and labor charges.
* **Inventory & Alerts System:** Live tracking of raw stock levels (Pure Wood vs. Sheet Wood) with automated threshold triggers that flag a low-stock alert when supplies drop below safe levels.
* **Persistent Data Logging:** Leverages C++ File Handling structures to log and append crucial financial transactions, pay slips, attendance reports, and order statuses directly into external text files (e.g., `Records_Orders.txt`, `Records_Attendance.txt`).
* **Cross-Platform Compatibility:** Features built-in smart utility scripts to automatically detect and handle operating system flags (`Windows` vs. `macOS/Linux`) for seamless console screen clearing tasks.

## 🛠️ C++ Concepts Practiced
* Object-Oriented Logic Foundations
* File Handling & Data Persistence (`fstream`, `ofstream::app`)
* Advanced Control Flow (Nested `switch` cases, conditional state loops)
* Array Manipulations & Multi-variable tracking flags
* String formatting & DataType Typecasting (`to_string()`)

## 🖥️ How to Run the Project
1. Clone this repository or download the source `.cpp` file.
2. Open the file in any standard C++ IDE (like Dev-C++, VS Code, or Code::Blocks).
3. Compile and Run the script using a C++11 compliant compiler or higher.
4. Use the master passcode **`1234`** to unlock the admin and management portals.
