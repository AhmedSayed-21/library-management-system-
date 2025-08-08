📚 Library Management System — C++
Overview
This is a console-based Library Management System implemented in C++ that allows both students and administrators to manage library operations such as book borrowing, returning, editing, and account management.
It supports data persistence using text files, ensuring library records are saved and loaded automatically.

✨ Features
👨‍🎓 For Students
Sign up & login with a unique ID and password.

Edit personal information (name or password).

View available books in the library.

Search books by code and view details.

Borrow books by entering their code.

Edit borrowed books list (return a book).

View personal library card information.

🛠 For Administrators
Login as admin (default password: 123).

Add new books to the library.

Delete existing books.

Edit book information:

Change title

Change author

Change edition

Change code

Change category

📂 Data Persistence
All student data and book records are stored in external files.

Data is loaded at program start and saved automatically when exiting.

🗂 File Structure
bash
Copy
Edit
/LibraryManagement
 ├── students              # Student data file
 ├── books                 # Books data file
 ├── main.cpp              # Main source code
⚙️ Requirements
C++11 or higher compiler (g++ recommended).

Works on Windows, Linux, or MacOS (adjust file paths if needed).

🖥 Compilation
Open a terminal in the project directory and run:

bash
Copy
Edit
g++ -std=c++11 -o library main.cpp
▶️ Usage
Run the program:

bash
Copy
Edit
./library
Main Menu Options:

Sign Up — Create a new student account.

Login — Access student features.

Admin Login — Access admin features.

Exit — Save all data and close the program.

📌 Data Format
Students file:
php-template
Copy
Edit
<id>,<name>,<password>,<borrowed_count>,<book_code1>*<book_code2>*
Books file:
php-template
Copy
Edit
<name>,<author>,<category>,<code>,<edition>,<is_available>
is_available = y (yes) or n (no)

🔒 Admin Credentials
Password: 123 (default — can be changed in code).

🚀 Future Improvements
Implement search by author/title.

Add due dates and overdue fines.

Improve security with encrypted passwords.

Add graphical interface.
