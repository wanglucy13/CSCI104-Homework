#include "storage.h"
#include "review_window.h"
#include "cart_window.h"
#include "review.h"
#include <QWidget>
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

class MainWindow : public QWidget
{
	Q_OBJECT
public: 
	MainWindow(Storage& ds, std::string username);
	~MainWindow();

private slots:
	void addProducts();
	void addReviews();
	void reviewWindow();
	void cartWindow();
	void searchProducts();
	void saveData();
	void alphaSort();
	void ratingHelper(std::map<Product*, std::vector<Review*> > r);
	void ratingSort();
	double basicSimilarity(User* u1, User *u2);
	double refineSimilarity(User* u1, User* u2);
	std::string recommendedProduct();

private:
	QVBoxLayout* overallLayout;
	QLabel* AmazonNameLabel;
	QLabel* recommendLabel;
	QLabel* recommendProduct;

	// Displayed quote
	QHBoxLayout* searchLayout;
	QLineEdit* searchBar;
	QComboBox* searchType;
	QPushButton* searchButton;

	QHBoxLayout* productListLayout;
	QLabel* recommendation;
	QLabel* productRec;
	QListWidget* productList;
	QVBoxLayout* sortProductLayout;
	QLabel* sortLabel;
	QRadioButton* alpha;
	QRadioButton* rating;
	QPushButton* addButton;

	QHBoxLayout* usersLayout;
	QComboBox* usersList;
	QPushButton* viewUsersButton;

	QHBoxLayout* reviewLayout;
	QListWidget* reviewList;
	QHBoxLayout* buttonLayout;
	QLabel* databaseName;
	QLineEdit* saveLineEdit;
	QHBoxLayout* reviewButtonLayout;
	QPushButton* writeReviewButton;
	QPushButton* saveButton;
	QHBoxLayout* exitLayout;
	QPushButton* exitButton;

	ReviewWindow* newReviewWindow;
	CartWindow* newCartWindow;

	std::string name;
	Storage* datastore;
};
