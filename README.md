# Event Management System

A console-based C++ application for managing events, user registrations, and ticket bookings. This project demonstrates proficiency in C++ programming, file handling, and user interface design, developed as part of my academic journey in Artificial Intelligence at Bahria University Karachi Campus.

## Features

- **User Roles:**
  - **Admin:** View events, delete events, view attendee lists, and manage (add/remove) managers and users.
  - **Manager:** Add, modify, delete events, and view attendee lists.
  - **User:** View events, book tickets, view personal bookings, and cancel bookings.
- **Event Management:**
  - Add events with details like ID, name, manager, category, time, date, place, and available seats.
  - Modify event details and delete unbooked events.
  - List all events with formatted output.
- **Booking System:**
  - Book tickets with attendee details (name, phone, banking info, ticket category).
  - View and cancel specific bookings by attendee name and event.
- **Security and Validation:**
  - Prevents deletion of booked events.
  - Validates user inputs (e.g., integer choices, date formats, unique event IDs).
  - Implements login/registration with username/password checks.
- **File Handling:**
  - Stores event and booking data in text files (`Event Information.txt`, `Ticketing Information.txt`).
  - Manages user credentials in separate files (`admin.txt`, `manager.txt`, `user.txt`).

## Technologies Used

- **Language:** C++ (Standard Library)
- **Key Concepts:** File I/O, Structs, Input Validation, Modular Programming
- **Tools:** Any C++ compiler (e.g., g++)

## Installation

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/Talha-Shahid-07/Event-Management-System.git
   cd Event-Management-System
   ```

2. **Compile the Code:**
   Ensure you have a C++ compiler installed (e.g., g++). Compile the source code:
   ```bash
   g++ src/EventManagementSystem.cpp -o EventManagementSystem
   ```

3. **Run the Application:**
   Execute the compiled program:
   ```bash
   ./EventManagementSystem
   ```

## Usage

1. **Start the Program:**
   Run the executable to access the main menu.
2. **Select a Role:**
   - Choose **Admin** (default credentials: `admin password`), **Manager**, or **User**.
   - Register or log in as a Manager or User.
3. **Navigate Dashboards:**
   - **Admin Dashboard:** Manage events and users.
   - **Manager Dashboard:** Add, modify, or delete events; view attendees.
   - **User Dashboard:** Book tickets, view or cancel bookings.
4. **File Outputs:**
   - Events are saved in `Event Information.txt`.
   - Bookings are saved in `Ticketing Information.txt`.
   - User credentials are stored in `manager.txt` and `user.txt`.

## Example

**Sample Event Creation:**
```
Enter Event ID: E001
Enter Manager Name: John Doe
Enter Event Name: Tech Conference
Enter Event Time (24 hr format): 14
Enter Event Category: Technology
Enter Event Date (DD/MM/YYYY, Current Year): 15/12/2024
Enter Event Place: Convention Center
Enter the number of seats available: 100
==========================================
Event added successfully!
```

**Sample Booking:**
```
Enter the ID of the event: E001
Enter your name: Alice Smith
Enter your phone number: 1234567890
Enter your Banking Details: XXXX-XXXX-XXXX-1234
Select the ticket category:
1. Premium
2. Basic
--> 1
==========================================
Ticket booked successfully! Thank you, Alice Smith!
```

## Project Structure

```
Event-Management-System/
├── src/
│   └── EventManagementSystem.cpp  # Main source code
├── Event Information.txt          # Stores event data
├── Ticketing Information.txt   # Stores booking data
├── admin.txt                     # Admin credentials
├── manager.txt                   # Manager credentials
├── user.txt                      # User credentials
├── README.md                     # This file
```

## Contributing

Contributions are welcome! Please fork the repository, make changes, and submit a pull request. Ensure your code follows the existing style and includes appropriate error handling.

## Acknowledgments

Developed as part of an academic project to enhance skills in C++ programming and system design. Special thanks to Bahria University Karachi Campus for fostering a learning environment that encourages practical application development.
