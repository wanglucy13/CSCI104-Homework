#include "storage.h"
#include "user.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QFont>
#include <QComboBox>
#include <string>

class NewUserWindow : public QDialog
{
	Q_OBJECT
public:
	NewUserWindow(std::string password, std::string username, Storage* ds);
	~NewUserWindow();

private slots:
	void registerFunction();

private:
	QVBoxLayout* overallLayout;
	QLabel* registrationLabel;
	//QLabel* infoLabel;
	QHBoxLayout* ageLayout;
	QLabel* ageLabel;
	QComboBox* age;

	QHBoxLayout* creditLayout;
	QLabel* creditLabel;
	QLineEdit* creditAmount;

	QHBoxLayout* typeLayout;
	QLabel* typeLabel;
	QComboBox* type;

	QHBoxLayout* buttonLayout;
	QPushButton* registerButton;
	QPushButton* quitButton;

	std::string password_;
	std::string username_;

	Storage* storage;
};