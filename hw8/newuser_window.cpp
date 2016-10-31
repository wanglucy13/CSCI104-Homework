#include "newuser_window.h"
#include <QRegExpValidator>
#include <sstream>

NewUserWindow::NewUserWindow(std::string password, std::string username, Storage* ds){
	password_ = password;
	username_ = username;
	storage = ds;

	overallLayout = new QVBoxLayout();
	registrationLabel = new QLabel("Register");
	QFont titleFont;
	titleFont.setBold(true);
	titleFont.setPointSize(14);
	registrationLabel->setFont(titleFont);
	registrationLabel->setAlignment(Qt::AlignCenter);
	overallLayout -> addWidget(registrationLabel);

	ageLayout = new QHBoxLayout();
	overallLayout -> addLayout(ageLayout);
	ageLabel = new QLabel("Age:     ");
	ageLayout -> addWidget(ageLabel);
	age = new QComboBox();
	for(int i = 1; i < 149; i++){
		age -> addItem(QString::number(i));
	}
	ageLayout -> addWidget(age);

	creditLayout = new QHBoxLayout();
	overallLayout -> addLayout(creditLayout);
	creditLabel = new QLabel("Credit Amount:       ");
	creditLayout -> addWidget(creditLabel);
	creditAmount = new QLineEdit();
	int num = 999999999;
	creditAmount->setValidator(new QIntValidator(0, num, this) );
	creditLayout -> addWidget(creditAmount);

	typeLayout = new QHBoxLayout();
	overallLayout -> addLayout(typeLayout);
	typeLabel = new QLabel("Type:     ");
	typeLayout -> addWidget(typeLabel);
	type = new QComboBox();
	type -> insertItem(0, "0");
	typeLayout -> addWidget(type);

	buttonLayout = new QHBoxLayout();
	overallLayout -> addLayout(buttonLayout);
	registerButton = new QPushButton("Register");
	connect(registerButton, SIGNAL(clicked()), this, SLOT(registerFunction()));

	buttonLayout -> addWidget(registerButton);
	quitButton = new QPushButton("Quit");
	connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

	buttonLayout -> addWidget(quitButton);

	setLayout(overallLayout);
}

NewUserWindow::~NewUserWindow(){
	delete registrationLabel;
	//QLabel* infoLabel;
	delete ageLabel;
	delete age;
	delete creditLabel;
	delete creditAmount;
	delete typeLabel;
	delete type;
	delete registerButton;
	delete quitButton;
	delete ageLayout;
	delete typeLayout;
	delete creditLayout;
	delete buttonLayout;
	delete overallLayout;
}

void NewUserWindow::registerFunction(){
	int userAge = (age -> currentText()).toInt();
	double userBalance = creditAmount -> text().toInt();
	int userType = 0;

	User* u = new User(username_, userAge, userBalance, userType, password_);
	storage -> addUser(u);
	this -> close();
}
