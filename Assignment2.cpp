#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

class Book//Represents a book with attributes such as title, author, ISBN, and availability.
{
private: 
	string title, author, ISBN;
	bool available; 
public:
	//constructor fort title, author, isbn, and avail
	Book(string t, string a, string i) : title(t), author(a), ISBN(i), available(true) {} 
	
	string getTitle() const
	{
		return title;
	}
	 
	string getISBN() const
	{
		return ISBN;
	}

	void borrowBook()
	{
		if (!available)
		{
			throw runtime_error("Book is unavailable");
		}
		available = false;
	}
	void returnBook()
	{
		if (available)
		{
			throw runtime_error("Book is unavailable");
		}
		available = true;
	}
};

class User//Represents a user with attributes such as name, userID, and a list of borrowed books. (note: UserID can be automatically generated).
{
protected: 
	string name;
	int userID;
	vector<string>borrowedBooks;//declare vector string borrowed books

public: 
	User(string n, int uID) :name(n), userID(uID){}
	
	string getName() const
	{
		return name; 
	}

	int getUserID() const
	{
		return userID;
	}

	void borrowBook(string isbn)//adds book to isbn to vector borrowdbooks
	{
		borrowedBooks.push_back(isbn);
	}

	void returnBook(string isbn)
	{
		for (size_t i = 0; i < borrowedBooks.size(); i++)//size t for maximum size rather than array
		{
			if (borrowedBooks[i] == isbn) //access book and erase once found, restart the indecesfor more books if needed
			{
				borrowedBooks.erase(borrowedBooks.begin() + i);
				return;
			}
		}
		throw runtime_error("This book has not been borrowed by user");
	}
};

class Student : public User//inherits user class for student
{
public: 
	Student(string n, int uID):User(n, uID){}
};

class Faculty : public User//inherits user class to build profile faculty
{
public: 
	Faculty(string n, int uID):User(n, uID){}
};

class Library //Manages books, users, and transactions.
{
private: 
	vector<Book> books;
	vector<User*> users;
	static Library* instance; //singleton method

	Library(){}//private construct

public: 
	static Library* getInstance()
	{
		if (!instance) 
		{
			instance = new Library();
		}
		return instance;
	}

	void addBook(string title, string author, string ISBN)
	{
		books.push_back(Book(title, author, ISBN));
		cout << "Book added: " << title << " by " << author << endl;

	}
	void registerUser(string name, int userID, bool isFaculty)
	{
		if (isFaculty)
		{
			users.push_back(new Faculty(name, userID));
		}
		else
		{
			users.push_back(new Student(name, userID));
		}
		cout << "User registered: " << name << " ID: " << userID; 
	}

	Book* findBook(const string& isbn)
	{
		for (Book& book : books)
		{
			if (book.getISBN() == isbn)
			{
				return &book;
			}
		}
		return nullptr; //not found book
		
	}

	User* findUser(int userID)
	{
		for (User* user : users)//loop pointers
		{
			if (user->getUserID() == userID)//access user members
			{
				return user; //return specific pointer
			}
		}
		return nullptr; //user not found
	}
	
	void borrowBook(int userID, string isbn)
	{
		User* user = findUser(userID);
		Book* book = findBook(isbn);

		if (!user)
		{
			cout << "User not found";
			return;
		}

		if (!book)
		{
			cout << "Book not found";
			return;
		}

		book->borrowBook();
		user->borrowBook(isbn);
		cout << "book borrowed successfully! \n";
	}

	void returnBook(int userID, string isbn)
	{
		User* user = findUser(userID);
		Book* book = findBook(isbn);

		if (!user)
		{
			cout << "User not found";
			return;
		}

		if (!book)
		{
			cout << "Book not found";
			return;
		}

		book->returnBook();
		user->returnBook(isbn); 
		cout << "Book has been returned succecssfully" << endl;
	}

	void searchBooksByTitle(string title)
	{
		for (Book& book :books)
		{
			if (book.getTitle()==title)
			{
				cout << "Found book! " << book.getTitle() << "ISBN: " << book.getISBN() << endl;
			}
		}
	}
};

void Menu()
{
	cout << "\nWelcome to the Library:\n";
	cout << "1. Manage Books\n";
	cout << "2. Manage Users\n";
	cout << "3. Manage Transactions\n";
	cout << "4. Exit\n";;
	cout << "Choose an option: ";
}
void manageBooks()
{
	cout << "\nManage Books:\n";
	cout << "1. Add Book\n";
	cout << "2. Search by Title\n";
	cout << "3. Go Back\n";
	cout << "Choose an option: ";
}
void manageUsers()
{
	cout << "\nManage Users:\n";
	cout << "1. Register User\n";
	cout << "2. Go Back\n";
	cout << "Choose an option: ";
}
void manageTransactions()
{
	cout << "\nManage Transactions:\n";
	cout << "1. Borrow Book\n";
	cout << "2. Return Book\n";
	cout << "3. Go Back\n";
	cout << "Choose an option: ";
}

Library* Library::instance = nullptr;//singleton

int main() 
{
	Library* lib = Library::getInstance();

	while (true) 
	{
		Menu();
		int choice;
		cin >> choice;
		cin.ignore();

		switch (choice) 
		{
		case 1: //books
		{ 
			manageBooks();
			int bookChoice;
			cin >> bookChoice;
			cin.ignore();

			switch (bookChoice) 
			{
			case 1: 
			{
				string title, author, isbn;
				cout << "Enter title: ";
				getline(cin, title);
				cout << "Enter author: ";
				getline(cin, author);
				cout << "Enter ISBN: ";
				getline(cin, isbn);
				lib->addBook(title, author, isbn);
				break;
			}
			case 2: 
			{
				string title;
				cout << "Enter title: ";
				cin.ignore();
				getline(cin, title);
				lib->searchBooksByTitle(title);
				break;
			}

			case 3:
				break;
			default:
				cout << "Invalid option. Try again.\n";
			}
			break;
		}
		case 2: //users
		{ 
			manageUsers();
			int userChoice;
			cin >> userChoice;
			cin.ignore();

			switch (userChoice) 
			{
			case 1: {
				string name;
				int id, uType;
				cout << "Enter name: ";
				getline(cin, name);
				cout << "Enter User ID: ";
				cin >> id;
				cout << "Enter 1 For Student, 2 for Faculty ";
				cin >> uType;

				bool isFaculty = (uType == 2);

				lib->registerUser(name, id, uType);
				break;
			}
			case 2:
				break;
			default:
				cout << "Invalid option. Try again.\n";
			}
			break;
		}
		case 3: //transactions
		{
			manageTransactions();
			int transactionChoice;
			cin >> transactionChoice;
			cin.ignore();

			switch (transactionChoice) 
			{
			case 1: 
			{
				int id;
				string isbn;
				cout << "Enter User ID: ";
				cin >> id;
				cout << "Enter ISBN: ";
				cin >> isbn;
				lib->borrowBook(id, isbn);
				break;
			}
			case 2: 
			{
				int id;
				string isbn;
				cout << "Enter User ID: ";
				cin >> id;
				cout << "Enter ISBN: ";
				cin >> isbn;
				lib->returnBook(id, isbn);
				break;
			}
			case 3:
				break;
			default:
				cout << "Invalid option. Try again.\n";
			}
			break;
		}
		case 4: //exit
			return 0;
		default:
			cout << "Invalid option. Try again.\n";
		}
	}
	return 0;
}