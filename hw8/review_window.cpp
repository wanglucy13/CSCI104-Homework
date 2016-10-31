#include "review_window.h"
#include <QMessageBox>
#include <sstream>  

ReviewWindow::ReviewWindow(Product* p, Storage* ds, std::string name)
{
	product = p;
	storage = ds;
	username = name;

	overallLayout = new QVBoxLayout();

	reviewLabel = new QLabel("Write a Review");
	QFont titleFont;
	titleFont.setBold(true);
	titleFont.setPointSize(14);
	reviewLabel->setFont(titleFont);
	reviewLabel->setAlignment(Qt::AlignCenter);
	overallLayout -> addWidget(reviewLabel);
	
	//writing reviews
	writeReview = new QTextEdit();
	overallLayout -> addWidget(writeReview);

	//ratings
	ratingLayout = new QHBoxLayout();
	overallLayout -> addLayout(ratingLayout);
	ratingLabel = new QLabel("Rating:");
	ratingLayout -> addWidget(ratingLabel);
	rb1 = new QRadioButton();
	rb2 = new QRadioButton();
	rb3 = new QRadioButton();
	rb4 = new QRadioButton();
	rb5 = new QRadioButton();
	l1 = new QLabel("1");
	l2 = new QLabel("2");
	l3 = new QLabel("3");
	l4 = new QLabel("4");
	l5 = new QLabel("5");
	ratingLayout -> addWidget(rb1);
	ratingLayout -> addWidget(l1);
	ratingLayout -> addWidget(rb2);
	ratingLayout -> addWidget(l2);
	ratingLayout -> addWidget(rb3);
	ratingLayout -> addWidget(l3);
	ratingLayout -> addWidget(rb4);
	ratingLayout -> addWidget(l4);
	ratingLayout -> addWidget(rb5);
	ratingLayout -> addWidget(l5);

	//date
	dateLayout = new QHBoxLayout();
	overallLayout -> addLayout(dateLayout);
	dateLabel = new QLabel("Date:");
	dateLayout -> addWidget(dateLabel);
	actualDateLabel = new QHBoxLayout();
	dateLayout -> addLayout(actualDateLabel);

	year = new QComboBox();
	for(int i = 2015; i >= 1800; i--){
		year -> addItem(QString::number(i));
	}
	actualDateLabel -> addWidget(year);
	month = new QComboBox();
	for(int i = 1; i <= 12; i++){
		month -> addItem(QString::number(i));
	}
	actualDateLabel -> addWidget(month);
	day = new QComboBox();	
	for(int i = 1; i <= 31; i++){
		day -> addItem(QString::number(i));
	}
	actualDateLabel -> addWidget(day);

	buttonLayout = new QHBoxLayout();
	overallLayout -> addLayout(buttonLayout);
	submitButton = new QPushButton("Submit");
	connect(submitButton, SIGNAL(clicked()), this, SLOT(writeReviewFunct()));

	buttonLayout -> addWidget(submitButton);

	exitButton = new QPushButton("Exit");
	connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));
	buttonLayout -> addWidget(exitButton);

	setLayout(overallLayout);
}

ReviewWindow::~ReviewWindow(){
	delete reviewLabel;
	delete writeReview;
	delete ratingLabel;
	delete dateLabel;
	delete actualDateLabel; 
	delete year;
	delete month;
	delete day;
	delete rb1;
	delete rb2;
	delete rb3;
	delete rb4;
	delete rb5;
	delete l1;
	delete l2;
	delete l3;
	delete l4;
	delete l5;
	delete submitButton;
	delete exitButton;
	delete ratingLayout;
	delete dateLayout;
	delete buttonLayout;
	delete overallLayout;
}

void ReviewWindow::writeReviewFunct(){
	if(rb1 -> isChecked() == true) ratingText = 1;
	if(rb2 -> isChecked() == true) ratingText = 2;
	if(rb3 -> isChecked() == true) ratingText = 3;
	if(rb4 -> isChecked() == true) ratingText = 4;
	if(rb5 -> isChecked() == true) ratingText = 5;

	if(writeReview -> toPlainText().isEmpty()){
		QMessageBox msgBox;
		msgBox.setText("Please write a review");
		msgBox.exec();
		return;
	}

	if(rb1 -> isChecked() == false && rb2 -> isChecked() == false && rb3 -> isChecked() == false 
		&& rb4 -> isChecked() == false && rb5 -> isChecked() == false){
		QMessageBox msgBox;
		msgBox.setText("Please select a rating");
		msgBox.exec();
		return;
	}

	// User* u = storage -> findUser(username);
	textReview = (writeReview -> toPlainText()).toStdString();
	std::string yearText = (year -> currentText()).toStdString();
	std::string monthText = (month -> currentText()).toStdString();
	std::string dayText = (day -> currentText()).toStdString();
 	dateText = yearText + '-' + monthText + '-' + dayText;
 	name = product -> getName();
 	review = new Review(name, ratingText, username, dateText, textReview);
 	storage -> updateReviews(product, review);
 	this -> close();
}