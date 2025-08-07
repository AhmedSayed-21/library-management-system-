#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void main_menu();                               
void signup();                       
bool login();           

bool admin_login();        

void user_main_menu();
void admin_main_menu();

void print_available_books();

void print_borrowed_books();

void addBook();
void deleteBook();


void read_data();
void save_data();

void EditInformation();
void ChangeName();
void ChangePassword();

void borrowBook(int code);

///////////////////////////
void editOrder();
///////////////////////////


///////////////////////////
void Edit_booksinfo();

void Changetitle(int code);

void Changeauthor(int code);
void changeedition(int code);

void changecode(int code);

void changecategory(int code);
///////////////////////////

const int MAX_SIZE = 100;
int student_count = 0;

int num_of_books = 0;
int borrowed;

string studentsFilePath = "C:\\Users\\Ahmed\\Downloads\\mugahidProjet\\ConsoleApplication1\\students";
string booksFilePath = "C:\\Users\\Ahmed\\Downloads\\mugahidProjet\\ConsoleApplication1\\books";

// define a struct to represent a book
struct Book {
	int Code;
	int Edition;
	string Name = "\0";
	string Author_name;
	string Category;
	char is_available;

} books[MAX_SIZE];

// Struct to store student data
struct student
{
	string id;
	string name;
	string password;

	int bCount = 0;
	int borredBooks[MAX_SIZE];

};
student students[MAX_SIZE];

student curStudent;

void print_card_info(student stu);
Book getBook(int code) {

	for (int i = 0; i < num_of_books; i++)
	{
		if (books[i].Code == code) 
			{
			
				return books[i];
			}
			
			
	}
	Book checker;
	return checker;
}

void printBook(Book book) {
	
	if(book.Name=="\0"){
			cout << "\033[31m";
			
			cout << "Book is not found!\n";
			cout << "\033[0m";
		}
	else{

			cout << " Code: " << book.Code << endl;
			cout << " Name: " << book.Name << endl;
			cout << " AuthorName: " << book.Author_name << endl;
			cout << " Edition: " << book.Edition << endl;
			cout << " Catagory: " << book.Category << endl
				 << endl;
	}

	
}


int main() {
	read_data();

	main_menu();

	save_data();
	return 0;
}

void read_data() {

	fstream file;
	file.open(studentsFilePath, ios::in | ios::app);

	// read data and put it into students array
	if (file.is_open()) {

		string row;
		int i = 0;

		while (getline(file, row)) {

			stringstream rowdata(row);
			getline(rowdata, students[i].id, ',');

			getline(rowdata, students[i].name, ',');

			getline(rowdata, students[i].password, ',');

			string tempBcount;
			getline(rowdata, tempBcount, ',');

			students[i].bCount = stoi(tempBcount);


			string borredidsStr;
			getline(rowdata, borredidsStr, ',');


			stringstream borredBooksIds(borredidsStr);

			string id;
			for (int j = 0; j < students[i].bCount; j++)
			{
				getline(borredBooksIds, id, '*');
				students[i].borredBooks[j] = stoi(id);
			}

			i++;
			student_count++;
		}

		file.close();
	}


	fstream file2;
	file2.open(booksFilePath, ios::in|ios::app);

	if (file2.is_open()) {

		string str;
		int j = 0;

		while (getline(file2, str)) {
			stringstream ss(str);

			getline(ss, books[j].Name, ',');
			getline(ss, books[j].Author_name, ',');
			getline(ss, books[j].Category, ',');

			string str2;
			getline(ss, str2, ',');
			books[j].Code = stoi(str2);

			string str3;
			getline(ss, str3, ',');

			books[j].Edition = stoi(str3);
			ss >> books[j].is_available;
			j++;
			num_of_books++;
		}
		file.close();
	}
}

void save_data() {
	fstream file;

	file.open(studentsFilePath, ios::out);

	if (file.is_open()) {
		string borredIDs = " ";

		for (int i = 0; i < student_count; i++) {

			for (int j = 0; j < students[i].bCount; j++) {
				borredIDs += to_string(students[i].borredBooks[j]) + "*";
			}

			file << students[i].id << ',' <<
				students[i].name << ',' <<
				students[i].password << ',' <<
				students[i].bCount << ',' <<
				borredIDs.substr(1) << "\n";

			borredIDs = " ";
		}

		file.close();
	}

	// save data books
	file.open(booksFilePath, ios::out);
	if (file.is_open()) {

		for (int i = 0; i < num_of_books; i++) {

			file <<
				books[i].Name << ',' <<
				books[i].Author_name << ',' <<
				books[i].Category << ',' <<
				books[i].Code << ',' <<
				books[i].Edition << ',' <<
				books[i].is_available << endl;
		}

		file.close();
	}
}

void main_menu() {
	int choice;
	string prombet = "Welcome to the Library system\n"
		"Please choose an option:\n"
		" 1. Sign up\n"
		" 2. Login\n"
		" 3. Admin Login\n"
		" 4. Exit.\n > ";
	do {

		cout << prombet;
		cin >> choice;

		switch (choice) {
			
		case 1:

			signup();
			break;

		case 2:
			if (login()) {
				cout << "\033[1;32m";
				cout << "Login successful!" << endl;
				cout << "\033[0m"; 
				user_main_menu();
			}
			else {
				
				cout << "\033[31mLogin Failed!\033[0m\n";
			}
			break;
		case 3:

			if (admin_login()) {
				 cout << "\033[1;32m";  
				cout << "Login successful!" << endl;
				 cout << "\033[0m";
				 admin_main_menu();
			}
			else {
				
				cout << "\033[31mLogin Failed!\033[0m\n";
			}

			break;

		case 4:
			
			cout << "Exit";

			break;

		default: cout << "INVALIED CHOICE!\n Please Re-enter a valied choice\n";

		}

	} while (choice != 4);

}


void signup() {
	student student;
	cout << "Sign Up\n";
	cout << "Please enter your name: ";

	getline(cin, student.name);
	getline(cin, student.name);
	cout << "Please enter your ID: ";
	cin >> student.id;
	cout << "Please enter your password: ";
	cin >> student.password;
	student.bCount = 0;

	// Add student to array
	students[student_count] = student;
	student_count++;
}

bool login() {
	string entered_id;
	string entered_password;

	cout << "Welcome to the login page!" << endl;
	cout << "Please enter your ID: ";
	cin >> entered_id;
	cout << "Please enter your password: ";
	cin >> entered_password;

	// Check if student is in array
	for (int i = 0; i < student_count; i++) {

		if (entered_id == students[i].id && entered_password == students[i].password)
		{
			curStudent = students[i];
			return true;
		}
	}
	cout << "\033[31m";
	cout << "Username not found or wrong password\n\n";
	
	cout << "Please try again\n\n";
	cout << "\033[0m";
	return false;
}

bool admin_login() {
	string entered_password;
	cout << "Please enter the admin password: ";
	cin >> entered_password;

	if (entered_password == "123") {
		
		return true;
	}
	else {
		return false;
	}
}


void user_main_menu() {

	string prompet = "................................main   menu ......................................\n"
					 " [1] Edit Information\n"
					 " [2] View Books\n"
					 " [3] View Books Information.\n"
					 " [4] Select Book Code to Borrow.\n"
					 " [5] Edit Order\n"
					 " [6] Log Out\n"
					 " [7] view card info\n";

	int choice;
	int code;

	do {
		cout << "\033[34m";
		cout << prompet;
			cout << "\033[0m";
		cin >> choice;

		switch (choice) {

		case 1:
			EditInformation();
			break;

		case 2:
			print_available_books();
			break;

		case 3:
			int code;
			cout << "\nenter code : "; cin >> code;
			printBook(getBook(code));
			break;


		case 4:

			cout << "\nenter book code to borrow : "; cin >> code;
			borrowBook(code);
			break;

		case 5:
			editOrder();

			break;
		case 6:
			system("Color 07");
			for (int i = 0; i < student_count; i++)
			{
				if (curStudent.id == students[i].id) {
					students[i] = curStudent;
				}
			}
			
			break;
		case 7:
		for (int i = 0; i < student_count; i++)
			{
				if (curStudent.id == students[i].id) {
					students[i] = curStudent;
				}
			}
			print_card_info(curStudent);
			break;
		default:
			cout << "Invalid choice\n";
			break;
		}
	} while (choice != 6);
	
}

void admin_main_menu() {
	
	string prompet = "................................main menu......................................\n"
		" [1] Add new book\n"
		" [2] Delete book\n"
		" [3] Edit  books\n"
		" [4] Log out\n > ";

	int choice;

	do {
		cout << prompet;
		cin >> choice;

		switch (choice) {
		case 1:

			addBook();
			break;

		case 2:
				
			deleteBook();
			break;

		case 3:

			Edit_booksinfo();
			break;	

		case 4:
			
			break;

		default:
			cout << "INVALID CHOICE\n";
		}


	} while (choice != 4);

}

void EditInformation() {
	bool repeat = true;
	while (repeat)
	{
		int choice;

		cout << " Choose An Option " << endl;
		cout << "   1.Change Name " << endl;
		cout << "   2.Change Password " << endl;
		cout << "   3.Back " << endl;
		cin >> choice;

		switch (choice)
		{
		case 1:
			ChangeName();
			repeat = false;
			break;
		case 2:
			ChangePassword();
			repeat = false;
			break;
		case 3:
			repeat = false;
			break;
		default:
			cout << "Not Valid Choice " << endl;
			repeat = true;
			break;
		}
	}
}

void ChangeName()
{
	string name;
	cout << "Enter A New Name " << endl;
	cin >> name;

	curStudent.name = name;
}

void ChangePassword() {

	string password;
	cout << "Enter A New Password " << endl;
	cin >> password;

	curStudent.password = password;
}

/////////////////

void print_available_books() {
	
	cout << "Available Books are : " << num_of_books << endl;

	for (int i = 0; i < num_of_books; i++) {

		if (books[i].is_available == 'y') {

			printBook(books[i]);

		}
		cout << "//**//\n";
	}
}

void print_borrowed_books() {

	cout << "Borrowed books are : " << borrowed << " " << endl;

	for (int i = 0; i < curStudent.bCount; i++) {

		cout << "Book " << i + 1 << "\n";
		Book book = getBook(curStudent.borredBooks[i]);
		printBook(book);
	}

}

////////////////

void borrowBook(int code) {
	bool failed = true;
	for (int i = 0; i < num_of_books; i++)
	{
		if (books[i].Code == code) {
			books[i].is_available = 'n';
			failed = false;
			break;
		};
	}
	if(!failed)
		curStudent.borredBooks[curStudent.bCount++] = code;
		else{
		cout << "Invalid book code!\n";
		}
}

/////////////////

// curStudent.borredBooks = {0, 2, 3}
// 
// {0, 3}, 3}

void deleteElement(int arr[], int& n, int pos) {

	int i;

	// shift the elements to the left to delete the element
	for (i = pos; i < n - 1; i++) {
		arr[i] = arr[i + 1];
	}

	n--; // reduce the size of the array
}

void editOrder() { 
    cout << "You have borrowed these books:\n"; 
    Book bookToShow; 
    char choice; 
    int bookCodeToDelete; 
 
    for (int i = 0; i < curStudent.bCount; i++) { 
        bookToShow = getBook(curStudent.borredBooks[i]); 
        cout << " [" << bookToShow.Code << "] " << bookToShow.Name << "\n"; 
    } 
 
    cout << "\nDo you want to edit your order? (y/n) > "; 
    cin >> choice; 
 
    bool bookFound = false,havebook=false; 
    int bookIndex = -1; 
 
    switch (choice) { 
        case 'y': 
        case 'Y': 
            cout << "Enter the code of the book you want to delete: "; 
            cin >> bookCodeToDelete; 
            for (int i = 0; i < num_of_books; i++) { 
                if (bookCodeToDelete == books[i].Code) { 
                    books[i].is_available = 'y'; 
                    bookFound = true; 
                    bookIndex = i; 
                    break; 
                } 
            } 
            if (bookFound) { 
                for (int i = 0; i < curStudent.bCount; i++) { 
                    if (bookCodeToDelete == curStudent.borredBooks[i]) {
					havebook = true;
					deleteElement(curStudent.borredBooks, curStudent.bCount, i);
					break; 
                    } 
                } 
				if(havebook){
					 cout << "\033[1;32m";
                cout << "Book deleted successfully.\n"; 
				cout << "\033[0m";
				}else{
				cout << "\033[31m";

				cout << "You dont own that book!\n";
				cout << "\033[0m";
				}
            } else { 
                cout << "Invalid book code.\n"; 
            } 
            break; 
        case 'n': 
        case 'N': 
            cout << "Fine.\n"; 
            break; 
        default: 
            cout << "Invalid choice.\n"; 
            break; 
    }
};

/////////////////

void addBook() {


	string Name; 
	string Author_name;
	string Category;
	int Code; 
	int Edition;

	cout << "Add new Book:\n";
 
	cout << " Code		 : "; cin >> Code;
 
	cout << " Name		 : "; cin.ignore(); getline(cin, Name);
 
	cout << " Author Name: "; getline(cin,Author_name);
 
	cout << " Category   : "; getline(cin,Category);
 
	cout << " Edition    : "; cin >> Edition;
	// create a new book and add it to the array
	Book newBook = Book{ Code, Edition, Name, Author_name, Category, 'y' };

	books[ num_of_books ] = newBook;

	num_of_books++;
	cout << "\033[1;32m";
	cout << "Book added successfully!\n";
	cout << "\033[0m";
}

void deleteBook() {

	int code;

	cout << "Enter Book's Code : "; cin >> code;

	// find the book in the array and remove it
	for (int i = 0; i < num_of_books; i++) {

		if (books[i].Code == code) {

			for (int j = i; j < num_of_books - 1; j++) {
				books[j] = books[j + 1];
			}

			num_of_books--;
			 cout << "\033[1;32m"; 
			cout << "Book deleted successfully!\n";
			 cout << "\033[0m";
			return;
		}
	}

	cout << "\033[31mBook not found!\033[0m\n";
}

//////////////////

void Edit_booksinfo()
{
	int code;
	cout << "Enter code of book : "; cin >> code;

	string prompt = "Choose An Option "
					" 1.Chane name "
					" 2.Change author "
					" 3.change Edition  "
					" 4.change code "
					" 5.change category "
					" 6.Back ";

	int choice;


	do{
		cout << prompt;
		cin >> choice;

		switch (choice)
		{
		case 1:
			Changetitle(code);

			break;
		case 2:
			Changeauthor(code);

			break;
		case 3:
			changeedition(code);

			break;
		case 4:
			changecode(code);

			break;
		case 5:
			changecategory(code);
			break;
		default:
			if(choice!=6)
			cout << "Not Valid Choice " << endl;
			break;
		}


	} while (choice != 6);
}

void Changetitle(int code)
{
    string newName;
    cout << "Enter A New Title : "; cin.ignore(); getline(cin, newName);

    for (int i = 0; i < num_of_books; i++)
    {
        if (books[i].Code == code)
        {
            books[i].Name = newName;
        }
    }

}

void Changeauthor(int code) {
    string author;
    cout << "Enter A new Author : ";
    cin.ignore();
    getline(cin, author);

    for (int i = 0; i < num_of_books; i++)
    {
        if (books[i].Code == code)
        {
            books[i].Author_name = author;
        }
    }

}

void changeedition(int code) {
    int Edition;
    cout << " Enter edition year : "; cin >> Edition;

    for (int i = 0; i < num_of_books; i++)
    {
        if (books[i].Code == code)
        {
            books[i].Edition = Edition;
        }
    }
}

void changecode(int code) {
    int newCode;
    cout << "Enter A New Code : "; cin >> newCode;

    for (int i = 0; i < num_of_books; i++)
    {
        if (books[i].Code == code)
        {
            books[i].Code = newCode;
        }
    }

}

void changecategory(int code) {
    string newCategory;
    cout << "Enter A New Category ";
    cin.ignore();
    getline(cin, newCategory);

    for (int i = 0; i < num_of_books; i++)
    {
        if (books[i].Code == code)
        {
            books[i].Category = newCategory;
        }
    }
}
void print_card_info(student curStudent){
cout << "\033[31m";
			cout << "---------\n";
			cout << "ID: " << curStudent.id << endl;
			cout << "Name: " << curStudent.name << endl;
			cout << "Password: " << curStudent.password << endl;
			cout << "---------\n\n";
			cout << "\033[0m";
}