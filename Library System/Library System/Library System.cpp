#include<iostream>
#include<algorithm>
#define MaxBooks 100
#define MaxUsers 10
#define BorrowingLimit 10
using namespace std;

bool FirstRun = true;

struct Book
{
	string Name, Borrower[MaxUsers];
	int TimesBorrowed = 0, ID, Quantity;
};

struct User
{
	string Name;
	int BooksBorrowedID[BorrowingLimit];
	int ID, Counter = 0;
};

bool SmallerName(Book& b1, Book& b2)
{
	return b1.Name < b2.Name;
}

bool SmallerID(Book& b1, Book& b2)
{
	return b1.ID < b2.ID;
}

struct LibrarySystem
{
	Book Books[MaxBooks];
	int LastBook = 0;
	User Users[MaxUsers];
	int LastUser = 0;
	string BN, UN, email, prefix;
	int id, qt;

	void Run()
	{
		while (1)
		{
			int choice = Menu();
			if (choice == 1)
			{
				cout << "Enter Book info: ID, Name and Quantity:" << endl;
				cin >> id >> BN >> qt;
				AddBook(BN, id, qt);
			}
			else if (choice == 2)
			{
				cout << "Enter prefix" << endl;
				cin >> prefix;
				SearchByPrefix(prefix);

			}
			else if (choice == 3)
			{
				cout << "Enter Book Name:" << endl;
				cin >> BN;
				WhoBorrowed(BN);
			}
			else if (choice == 4)
			{
				SortBooksByID();
			}
			else if (choice == 5)
			{
				SortBooksByName();
			}
			else if (choice == 6)
			{
				cout << "Enter User info: Name and ID:" << endl;
				cin >> UN >> id;
				AddUser(id, UN);
			}
			else if (choice == 7)
			{
				cout << "Enter User name and Book name:" << endl;
				cin >> UN >> BN;
				BorrowBook(UN, BN);
			}
			else if (choice == 8)
			{
				cout << "Enter User Name and Book Name" << endl;
				cin >> UN >> BN;
				ReturnBook(UN, BN);
			}
			else if (choice == 9)
			{
				PrintUsers();
			}
			else if (choice == 10)
			{
				cout << "Goodbye!" << endl;
				break;
			}
		}
	}

	int Menu()
	{
		int choice = -1;
		if (FirstRun)
		{
			cout << "Library menu:" << endl;
			cout << "1) Add Book" << endl;
			cout << "2) Search Book by prefix" << endl;
			cout << "3) Print who borrowed Book by Name" << endl;
			cout << "4) Print Library by ID" << endl;
			cout << "5) Print Library by Name" << endl;
			cout << "6) Add User" << endl;
			cout << "7) Borrow a Book" << endl;
			cout << "8) Return a Book" << endl;
			cout << "9) Print Users" << endl;
			cout << "10) Exit" << endl << endl;

			FirstRun = false;
		}
		cout << "Enter your choice" << endl;
		cin >> choice;
		if (choice < 1 || choice >10)
			cout << "Invalid choice " << endl;
		return choice;
	}

	void AddUser(int id, string name)
	{
		if (LastUser == MaxUsers)
		{
			cout << "The Library is at it's full members capacity!" << endl;
			return;
		}
		Users[LastUser].Name = UN;
		Users[LastUser].ID = id;
		LastUser++;
	}

	void AddBook(string name, int id, int quantity)
	{
		if (LastBook == MaxBooks)
		{
			cout << "The Library is at it's full Books capacity!" << endl;
			return;
		}
		Books[LastBook].Name = name;
		Books[LastBook].ID = id;
		Books[LastBook].Quantity = qt;
		LastBook++;
	}

	void SearchByPrefix(string prefix)
	{
		if (LastBook == 0)
		{
			cout << "The Library is Empty right now!" << endl;
			return;
		}
		else
		{
			bool found = false;
			for (int i = 0; i < LastBook; i++)
			{
				string BookName = Books[i].Name;
				for (int j = 0; j < BookName.size(); j++)
				{
					if (BookName[j] != prefix[j])
						break;
					if (j == prefix.size() - 1 && BookName[j] == prefix[j])
					{
						cout << BookName << " ";
						found = true;
					}

				}
			}
			if (!found)
				cout << "There is no Book by such prefix!";
			cout << endl;
		}
	}

	void BorrowBook(string username, string bookname)
	{
		bool userfound = false;
		bool bookfound = false;
		int i = 0, j = 0;

		if (LastUser == 0)
		{
			cout << "The Library has no users Registered" << endl;
			return;
		}
		else if (LastBook == 0)
		{
			cout << "The Library has no Books" << endl;
			return;
		}
		else
		{
			for (i; i < LastUser; i++)
			{
				if (Users[i].Name == username)
				{
					userfound = true;
					break;
				}
			}
			if (!userfound)
			{
				cout << "There is no User by this name!" << endl;
				return;
			}
			if (Users[i].Counter == BorrowingLimit)
			{
				cout << "Sorry you are at your borrowing limit!" << endl;
				return;
			}
			for (j; j < LastBook; j++)
			{
				if (Books[j].Name == bookname)
				{
					bookfound = true;
					break;
				}
			}
			if (!bookfound)
			{
				cout << "There is no Book by such name" << endl;
				return;
			}
			if (Books[j].TimesBorrowed == Books[j].Quantity)
			{
				cout << "Sorry all the copies of this Books is already borrowed!" << endl;
				return;
			}

			Users[i].BooksBorrowedID[Users[i].Counter] = Books[j].ID;
			Users[i].Counter++;
			Books[j].Borrower[Books[j].TimesBorrowed] = username;
			Books[j].TimesBorrowed++;
		}
	}

	void PrintUsers()
	{
		for (int i = 0; i < LastUser; i++)
		{
			cout << "User " << Users[i].Name << " ID " << Users[i].ID << " borrowd Books ID's: ";
			for (int j = 0; j < Users[i].Counter; j++)
			{
				cout << Users[i].BooksBorrowedID[j] << " ";
			}
			cout << endl;
		}
	}

	void WhoBorrowed(string bookname)
	{
		bool borrowed = false;
		if (LastBook == 0)
		{
			cout << "The Library is Empty!" << endl;
			return;
		}
		for (int i = 0; i < LastBook; i++)
		{
			if (Books[i].Name == bookname)
			{

				for (int j = 0; j < Books[i].TimesBorrowed; j++)
				{
					borrowed = true;
					cout << Books[i].Borrower[j] << endl;
				}
				if (!borrowed)
					cout << "No one borrowed this book" << endl;
				return;
			}
		}
		cout << "There is no Book with such name" << endl;
	}

	void SortBooksByID()
	{
		if (LastBook == 0)
		{
			cout << "The Library has no Books" << endl;
			return;
		}

		sort(Books, Books + LastBook, SmallerID);

		for (int i = 0; i < LastBook; i++)
		{
			cout << "ID = " << Books[i].ID << " Name = " << Books[i].Name << " Total Quantity " << Books[i].Quantity << " Total Borrowed " << Books[i].TimesBorrowed << endl;
		}
	}

	void SortBooksByName()
	{
		if (LastBook == 0)
		{
			cout << "The Library has no Books" << endl;
			return;
		}
		sort(Books, Books + LastBook, SmallerName);
		for (int i = 0; i < LastBook; i++)
		{
			cout << "ID = " << Books[i].ID << " Name = " << Books[i].Name << " Total Quantity " << Books[i].Quantity << " Total Borrowed " << Books[i].TimesBorrowed << endl;
		}
	}

	void ReturnBook(string username, string bookname)
	{
		bool userfound = false;
		bool bookfound = false;
		int i = 0, j = 0;

		if (LastUser == 0)
		{
			cout << "The Library has no users Registered" << endl;
			return;
		}
		else if (LastBook == 0)
		{
			cout << "The Library has no Books" << endl;
			return;
		}
		else
		{
			for (i; i < LastUser; i++)
			{
				if (Users[i].Name == username)
				{
					userfound = true;
					break;
				}
			}
			if (!userfound)
			{
				cout << "There is no User by this name!" << endl;
				return;
			}
			if (Users[i].Counter == 0)
			{
				cout << "You didnt' borrow from us before, this book is not ours!" << endl;
				return;
			}
			for (j; j < LastBook; j++)
			{
				if (Books[j].Name == bookname)
				{
					bookfound = true;
					break;
				}
			}
			if (!bookfound)
			{
				cout << "There is no Book by such name" << endl;
				return;
			}
			if (Books[j].TimesBorrowed == 0)
			{
				cout << "This Books hasn't been borrowed from us before, seems like it's not ours!" << endl;
				return;
			}

			Users[i].BooksBorrowedID[Users[i].Counter] = Books[j].ID;
			for (int x = i; x < Users[i].Counter - 1; x++)
			{
				Users[i].BooksBorrowedID[x] = Users[i].BooksBorrowedID[x + 1];
			}
			Users[i].Counter--;

			Books[j].Borrower[Books[j].TimesBorrowed] = username;
			for (int y = j; y < Books[j].TimesBorrowed - 1; y++)
			{
				Books[j].Borrower[y] = Books[j].Borrower[y + 1];
			}
			Books[j].TimesBorrowed--;
		}
	}
};



int main(void)
{
	LibrarySystem Library;
	Library.Run();

	return 0;
}