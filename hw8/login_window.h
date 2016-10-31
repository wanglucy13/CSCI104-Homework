#include "newuser_window.h"
#include "storage.h"
#include "main_window.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFont>
#include <map>

using namespace std; 

class LoginWindow : public QWidget
{
	Q_OBJECT
public:
	LoginWindow(Storage* ds);
	~LoginWindow();
	string registerHashFunction();
	string loginHashFunction();

private slots:
	void login();
	void create();

private:
	QVBoxLayout* overallLayout;
	QLabel* titleLable;
	
	QHBoxLayout* inputLayout;

	QVBoxLayout* existingUserLayout;
	QLabel* signInLabel;
	QHBoxLayout* usernameLayout;
	QLabel* usernameLabel;
	QLineEdit* username;
	QHBoxLayout* passwordLayout;
	QLabel*	passwordLabel;
	QLineEdit* password;
	QPushButton* loginButton;

	QVBoxLayout* newUserLayout;
	QLabel* registerLabel;
	QHBoxLayout* newUsernameLayout;
	QLabel* newUsernameLabel;
	QLineEdit* newUsername;
	QHBoxLayout* newPasswordLayout;
	QLabel*	newPasswordLabel;
	QLineEdit* newPassword;
	QPushButton* createButton;

	QPushButton* quitButton;

	MainWindow* mainWindow;
	NewUserWindow* newuserWindow;

	std::map<std::string, std::string> hash;

	Storage* storage;
};