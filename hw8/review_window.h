#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget>
#include <QRadioButton>
#include <QFont>
#include <QComboBox>
#include <QString>
#include <string>
#include "review.h"
#include "product.h"
#include "storage.h"

class ReviewWindow : public QDialog
{
	Q_OBJECT
public:
	ReviewWindow(Product* p, Storage* ds, std::string name);
	~ReviewWindow();

private slots:
	void writeReviewFunct();

private:
	QVBoxLayout* overallLayout;
	QLabel* reviewLabel;

	QTextEdit* writeReview;
	QHBoxLayout* ratingLayout;
	QLabel* ratingLabel;

	QHBoxLayout* dateLayout;
	QLabel* dateLabel;
	QHBoxLayout* actualDateLabel; 
	QComboBox* year;
	QComboBox* month;
	QComboBox* day;

	QRadioButton* rb1;
	QRadioButton* rb2;
	QRadioButton* rb3;
	QRadioButton* rb4;
	QRadioButton* rb5;

	QLabel* l1;
	QLabel* l2;
	QLabel* l3;
	QLabel* l4;
	QLabel* l5;

	QHBoxLayout* buttonLayout;
	QPushButton* submitButton;
	QPushButton* exitButton;

	int ratingText;
	std::string dateText;
	std::string username;
	Product* product;
	std::string name;
	//std::vector<Review*> reviews;
	Review* review;
	std::string textReview;
	Storage* storage;

};