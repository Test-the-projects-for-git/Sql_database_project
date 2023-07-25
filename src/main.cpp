#include<iostream>
#include<string>
#include<mysql.h>
using namespace std;

void InputUser(string& newName, string& newEmail, string& newPassword);
void AddUser(MYSQL mysql, string& username, string& email, string& password);
void DeleteUser(MYSQL mysql, string& username);
bool SearchUser(MYSQL mysql, MYSQL_ROW& row, MYSQL_RES(*&res), string& username);
void EditUser(MYSQL mysql, string& othername, string& username, string& email, string& password);
void MainMenu(void);


int main()
{
	MYSQL mysql;
	MYSQL_ROW row;
	MYSQL_RES* res;

	string host = "127.0.0.1";
	string user = "root";
	string passwd = "root";
	string db = "users";
	size_t port = 3306;
	size_t clientFlag = 0;

	string username;
	string email;
	string password;

	string newName;
	string newEmail;
	string newPassword;
	char choose = 'y';


	mysql_init(&mysql);

	if (!mysql_real_connect(&mysql, host.c_str(), user.c_str(), passwd.c_str(), db.c_str(), port, NULL, clientFlag))
	{
		cout << "Error include to database" << endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		while (choose == 'y')
		{
			cout << "connection pass to success" << endl;
			mysql_set_character_set(&mysql, "utf-8");
			MainMenu();
			cin >> choose;
			system("cls");
			if (choose == '1')
			{
				mysql_query(&mysql, "SELECT id_user, name, email, password FROM person");
				if (res = mysql_store_result(&mysql))
				{
					while (row = mysql_fetch_row(res))
					{
						for (size_t i = 0; i < mysql_num_fields(res); i++)
						{
							cout << row[i] << endl;
						}
					}
				}
			}
			else if (choose == '2')
			{
				AddUser(mysql, username, email, password);
			}
			else if (choose == '3')
			{
				DeleteUser(mysql, username);
			}
			else if (choose == '4')
			{
				cout << "Enter name user that want edit: ";
				cin >> username;
				if (SearchUser(mysql, row, res, username))
				{
					InputUser(newName, newEmail, newPassword);
					EditUser(mysql, username, newName, newEmail, newPassword);
				}
				else
				{
					cout << "There is such user" << endl;
				}

			}
			else if (choose == '5')
			{
				cout << "Enter name user that want found: ";
				cin >> username;
				if (!SearchUser(mysql, row, res, username))
				{
					cout << "User with name '" << username << "' not exist" << endl;
				}
				else
				{
					cout << "There is such user" << endl;
				}
			}
			else if (choose == '6')
			{
				mysql_close(&mysql);
				exit(EXIT_SUCCESS);
			}
			else
			{
				cout << "Unknow operation" << endl;
			}
			
			cout << "Repeat programm y/yes - n/not you choose: ";
			cin >> choose;
			system("cls");
		}
		
		

	}

	mysql_close(&mysql);
	return EXIT_SUCCESS;
}

void InputUser(string& newName, string& newEmail, string& newPassword)
{
	cout << "Enter new data" << endl;
	cout << "Enter name user: ";
	cin.ignore();
	std::getline(std::cin, newName);
	cout << "Enter password user: ";
	std::getline(std::cin, newEmail);
	cout << "Enter email user: ";
	std::getline(std::cin, newPassword);
}

void AddUser(MYSQL mysql, string& username, string& email, string& password)
{
	cout << "Enter user name: ";
	cin >> username;
	cout << "Enter email user: ";
	cin >> email;
	cout << "Enter user password: ";
	cin >> password;

	username.insert(username.begin(), '\'');
	username.push_back('\'');

	email.insert(email.begin(), '\'');
	email.push_back('\'');

	password.insert(password.begin(), '\'');
	password.push_back('\'');

	string insertQuery = "INSERT INTO person (name, email, password) VALUES ("
		+ username + ", " + email + ", " + password + ");";

	mysql_query(&mysql, insertQuery.c_str());
}

void DeleteUser(MYSQL mysql, string& username)
{
	cout << "Enter name user that want to delete" << endl;
	cin >> username;
	string deleteQuery = "DELETE FROM person WHERE name = '" + username + "'";
	mysql_query(&mysql, deleteQuery.c_str());
	cout << "User was deleted" << endl;
}

bool SearchUser(MYSQL mysql, MYSQL_ROW& row, MYSQL_RES(*&res), string& username)
{
	string searchQuery = "SELECT * FROM person WHERE name LIKE '%" + username + "%'";
	string editQuery = "";
	(mysql_query(&mysql, searchQuery.c_str()));
	res = mysql_store_result(&mysql);
	return (row = mysql_fetch_row(res)) ? true : false;
}

void EditUser(MYSQL mysql, string& othername, string& newName, string& newEmail, string& newPassword)
{
	string editQuery;

	editQuery = "UPDATE person SET name = '" + newName + "' WHERE name ='" + othername + "'";
	mysql_query(&mysql, editQuery.c_str());

	editQuery = "UPDATE person SET email = '" + newPassword + "'WHERE name = '" + newName + "';";
	mysql_query(&mysql, editQuery.c_str());

	editQuery = "UPDATE person SET password = '" + newEmail + "'WHERE name = '" + newName + "';";
	mysql_query(&mysql, editQuery.c_str());
}

void MainMenu(void)
{
	cout << "You choose" << endl
		<< "1 Show all users" << endl
		<< "2 Add user" << endl
		<< "3 Delete user" << endl
		<< "4 Edit user" << endl
		<< "5 Search user" << endl
		<< "6 leave the app" << endl;
}