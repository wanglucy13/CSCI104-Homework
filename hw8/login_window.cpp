#include "login_window.h"
#include <QSpacerItem>
#include <QMessageBox>
#include <string>
#include <math.h>
#include <iostream> 
#include <sstream>

using namespace std;

LoginWindow::LoginWindow(Storage* ds){
	storage = ds;

	for(unsigned int i = 0; i < storage -> getUser().size(); i++){
		hash[(storage -> getUser())[i] -> getName()] = (storage -> getUser())[i] -> getPassword();
	}

	overallLayout = new QVBoxLayout();
	titleLable = new QLabel("Amazon Login");
	QFont titleFont;
	titleFont.setBold(true);
	titleFont.setPointSize(14);
	titleLable->setFont(titleFont);
	titleLable->setAlignment(Qt::AlignCenter);
	overallLayout -> addWidget(titleLable);

	inputLayout = new QHBoxLayout();
	overallLayout -> addLayout(inputLayout);

	existingUserLayout = new QVBoxLayout();
	inputLayout -> addLayout(existingUserLayout);
	signInLabel = new QLabel("Existing User? Sign In!");
	signInLabel->setAlignment(Qt::AlignCenter);

	existingUserLayout -> addWidget(signInLabel);

	usernameLayout = new QHBoxLayout();
	existingUserLayout -> addLayout(usernameLayout);

	usernameLabel = new QLabel("Username:");
	usernameLayout -> addWidget(usernameLabel);
	username = new QLineEdit();
	usernameLayout -> addWidget(username);

	passwordLayout = new QHBoxLayout();
	existingUserLayout -> addLayout(passwordLayout);

	passwordLabel = new QLabel("Password: ");
	passwordLayout -> addWidget(passwordLabel);
	password = new QLineEdit();
	passwordLayout -> addWidget(password);
	loginButton = new QPushButton("Login");
	existingUserLayout -> addWidget(loginButton);
	connect(loginButton, SIGNAL(clicked()), this, SLOT(login()));

	existingUserLayout -> setContentsMargins(0,0,40,0);                                                               

	newUserLayout = new QVBoxLayout();
	inputLayout -> addLayout(newUserLayout);
	registerLabel = new QLabel("New User? Register!");
	registerLabel->setAlignment(Qt::AlignCenter);

	newUserLayout -> addWidget(registerLabel);

	newUsernameLayout = new QHBoxLayout();
	newUserLayout -> addLayout(newUsernameLayout);

	newUsernameLabel = new QLabel("New Username:");
	newUsernameLayout -> addWidget(newUsernameLabel);
	newUsername = new QLineEdit();
	newUsernameLayout -> addWidget(newUsername);

	newPasswordLayout = new QHBoxLayout();
	newUserLayout -> addLayout(newPasswordLayout);

	newPasswordLabel = new QLabel("New Password: ");
	newPasswordLayout -> addWidget(newPasswordLabel);
	newPassword = new QLineEdit();
	newPasswordLayout -> addWidget(newPassword);
	createButton = new QPushButton("Create user");
	newUserLayout -> addWidget(createButton);
	connect(createButton, SIGNAL(clicked()), this, SLOT(create()));

	quitButton = new QPushButton("Quit");
	overallLayout -> addWidget(quitButton);
	connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

	setLayout(overallLayout);
}

LoginWindow::~LoginWindow(){
	delete titleLable;
	delete signInLabel;
	delete usernameLabel;
	delete username;
	delete passwordLabel;
	delete password;
	delete loginButton;
	delete registerLabel;
	delete newUsernameLabel;
	delete newUsername;
	delete newPasswordLabel;
	delete newPassword;
	delete createButton;
	delete quitButton;
	delete passwordLayout;
	delete usernameLayout;
	delete newPasswordLayout;
	delete newUsernameLayout;
	delete newUserLayout;
	delete existingUserLayout;
	delete inputLayout;
	delete overallLayout;
}

string LoginWindow::loginHashFunction(){
	string pw = (password -> text()).toStdString();
	int passwordLength = password -> text().toStdString().length();
	long long sigDigit = 0;
	for(int i = 0; i < passwordLength; i++){
		sigDigit += (long long)pow(128, i) * (long long)pw[passwordLength - i - 1];
	}
	unsigned int array[4];
	array[3] = sigDigit % 65521;
	sigDigit /= (long long)65521;
	array[2] = sigDigit % 65521;
	sigDigit /= (long long)65521;
	array[1] = sigDigit % 65521;
	sigDigit /= (long long)65521;
	array[0] = sigDigit % 65521;

	int encrypt = (45912 * array[0] + 35511 * array[1] + 
		65169 * array[2] + 4625 * array[3]) % 65521;

	std::stringstream ss;
	ss << encrypt;
	std::string e = ss.str();
	return e;
}

string LoginWindow::registerHashFunction(){
	string pw = (newPassword -> text()).toStdString();
	int passwordLength = newPassword -> text().toStdString().length();
	long long sigDigit = 0;
	for(int i = 0; i < passwordLength; i++){
		sigDigit += (long long)pow(128, i) * (long long)pw[passwordLength - i - 1];
	}
	unsigned int array[4];
	array[3] = sigDigit % 65521;
	sigDigit /= (long long)65521;
	array[2] = sigDigit % 65521;
	sigDigit /= (long long)65521;
	array[1] = sigDigit % 65521;
	sigDigit /= (long long)65521;
	array[0] = sigDigit % 65521;
	int encrypt = (45912 * array[0] + 35511 * array[1] + 
		65169 * array[2] + 4625 * array[3]) % 65521;

	std::stringstream ss;
	ss << encrypt;
	std::string e = ss.str();
	return e;
}

void LoginWindow::login(){

	if(password -> text().isEmpty() && username -> text().isEmpty()){
		QMessageBox msgBox;
		msgBox.setText("Please type in a username and password");
		msgBox.exec();
		return;
	}
	else if(username -> text().isEmpty()){
		QMessageBox msgBox;
		msgBox.setText("Please type in a username");
		msgBox.exec();
		return;
	}
	else if(password -> text().isEmpty()){
		QMessageBox msgBox;
		msgBox.setText("Please type in a password");
		msgBox.exec();
		return;
	}
	else{
		bool userExists = false;
		bool passwordCorrect = false;

		for(unsigned int i = 0; i < storage -> getUser().size(); i++){
			string name = (storage -> getUser())[i] -> getName();
			string pw;
			string encrypt = loginHashFunction();
			if(name == (username -> text().toStdString())){
				userExists = true;
				pw = (storage -> getUser())[i] -> getPassword();
			}
			if(userExists){
				if(encrypt.compare(pw) == 0){
					passwordCorrect = true;
				}
			}
		}
		if(!userExists || !passwordCorrect){
			QMessageBox msgBox;
			msgBox.setText("Invalid username or password");
			msgBox.exec();
			return;
		}
		else{  

			mainWindow = new MainWindow(*storage, (username -> text().toStdString()));
			mainWindow -> show();
			this -> close();
		}
	}
}

void LoginWindow::create(){
	if(newPassword -> text().isEmpty() && newUsername -> text().isEmpty()){
		QMessageBox msgBox;
		msgBox.setText("Please type in a username and password");
		msgBox.exec();
		return;
	}
	else if(newUsername -> text().isEmpty()){
		QMessageBox msgBox;
		msgBox.setText("Please type in a username");
		msgBox.exec();
		return;
	}
	else if(newPassword -> text().isEmpty()){
		QMessageBox msgBox;
		msgBox.setText("Please type in a password");
		msgBox.exec();
		return;
	}
	else{
		for(unsigned int i = 0; i < storage -> getUser().size(); i++){
			string name = (storage -> getUser()[i]) -> getName();
			if(name == (newUsername -> text()).toStdString()){
				QMessageBox msgBox;
				msgBox.setText("This username is already taken");
				msgBox.exec();
				return;
			}
		}
		for(unsigned int i = 0; i < newPassword -> text().toStdString().length(); i++){
			if(newPassword -> text().toStdString()[i] == ' '){
				QMessageBox msgBox;
				msgBox.setText("Password cannot contain whitespace");
				msgBox.exec();
				return;
			}
		}
		if(newPassword -> text().toStdString().length() > 8){
			QMessageBox msgBox;
			msgBox.setText("Password is too long. Maximum of 8 characters!");
			msgBox.exec();
			return;
		}
		else{
			string encrypt = registerHashFunction();
			string user = (newUsername -> text()).toStdString();

			newuserWindow = new NewUserWindow(encrypt, user, storage);
			newuserWindow -> exec();
		}
	}
}

