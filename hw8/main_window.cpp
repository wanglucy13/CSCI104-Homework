#include "main_window.h"
#include "user.h"
#include "msort.h"
#include "util.h"
#include "heap.h"
#include <string>
#include <sstream>
#include <fstream> 
#include <QMessageBox>
#include <cmath> 
#include <QString>

struct DNode
{
	DNode(User* u, double edge, bool checked){
		u_ = u; 
		edge_ = edge;
		checked_ = checked;
	}
	User* u_;
	double edge_;
	bool checked_;
};

struct dijkstraComp
{
	bool operator() (DNode* x, DNode* y){
		return x -> edge_ < y ->edge_;
	}
};

struct Alphabetical
{
	bool operator() (Product* x, Product* y) {
		return x -> getName() < y -> getName();}
};

struct Rating
{
	Rating(std::map<Product*, std::vector<Review*> > reviewMap){
		std::map<Product*, std::vector<Review*> > r = reviewMap;
	}

	bool operator() (Product* x, Product* y) {
		int ratingTotal = 0;
		double averageX = 0;
		double averageY = 0;

		if (r.find(x) != r.end()) {
			if(r[x].size() == 0){
				return false;
			}
			else{
				std::vector<Review*> reviewsX = r[x]; 
				for(unsigned int i = 0; i < reviewsX.size(); i++){
					ratingTotal += (reviewsX[i] -> rating);
				}
				if(ratingTotal == 0){
					averageX = 0;
				}
				else averageX = ratingTotal/reviewsX.size();
			}
		}
		  
		if (r.find(y) != r.end() ) {
			if(r[y].size() == 0){
				return false;
			}
			else{
				std::vector<Review*> reviewsY = r[y]; 
				for(unsigned int i = 0; i < reviewsY.size(); i++){
					ratingTotal += (reviewsY[i] -> rating);
				}
				if(ratingTotal == 0){
					averageX = 0;
				}
				else averageY = ratingTotal/reviewsY.size();
			}
		}

		return averageX > averageY;
	}

private:
	std::map<Product*, std::vector<Review*> > r;
};

struct Date{
	bool operator() (Review* x, Review* y){
		int dayX, dayY, monthX, monthY, yearX, yearY;

		std::string dateX = x -> date;
		std::stringstream ss1(dateX);
		ss1 >> yearX;
		ss1 >> monthX;
		ss1 >> dayX;

		std::string dateY = y -> date;
		std::stringstream ss2(dateY);
		ss2 >> yearY;
		ss2 >> monthY;
		ss2 >> dayY;

		if(yearX > yearY) return true;
		else return false;
		if(abs(monthX) > abs(monthY)) return true;
		else return false;
		if(abs(dayX) > abs(dayY)) return true;
		else return false;
	}
};

MainWindow::MainWindow(Storage& ds, std::string username){
	name = username;
	datastore = &ds;


	setWindowTitle("Amazon");
	overallLayout = new QVBoxLayout();

	//Amazon Label at the top
	AmazonNameLabel = new QLabel("Amazon");
	QFont titleFont;
	titleFont.setBold(true);
	titleFont.setPointSize(14);
	AmazonNameLabel->setFont(titleFont);
	AmazonNameLabel->setAlignment(Qt::AlignCenter);
	overallLayout -> addWidget(AmazonNameLabel);

	recommendLabel = new QLabel("Recommended Product:");
	recommendProduct = new QLabel(QString::fromStdString(recommendedProduct()));
	overallLayout -> addWidget(recommendLabel);
	overallLayout -> addWidget(recommendProduct);



	//Search Section
	searchLayout = new QHBoxLayout();
	overallLayout -> addLayout(searchLayout);
	searchBar = new QLineEdit();
	searchLayout -> addWidget(searchBar);
	searchType = new QComboBox();
	searchType -> insertItem(0, "AND");
	searchType -> insertItem(1, "OR");
	searchLayout -> addWidget(searchType);
	searchButton = new QPushButton("Search");
	connect(searchButton, SIGNAL(clicked()), this, SLOT(searchProducts()));
	searchLayout -> addWidget(searchButton);

	//Product LIst Section
	productListLayout = new QHBoxLayout();
	
	overallLayout -> addLayout(productListLayout);
	productList = new QListWidget();
	connect(productList, SIGNAL(currentRowChanged(int)), this, SLOT(addReviews()));
	productListLayout -> addWidget(productList);

	//Sort Products Section
	sortProductLayout = new QVBoxLayout();	
	sortProductLayout -> addStretch();
	productListLayout -> addLayout(sortProductLayout);
	sortLabel = new QLabel("Sort by:");
	sortProductLayout -> addWidget(sortLabel);
	alpha = new QRadioButton("Alphabetical");
	connect(alpha, SIGNAL(toggled(bool)), this, SLOT(alphaSort()));
	sortProductLayout -> addWidget(alpha);
	rating = new QRadioButton("Rating");
	connect(rating, SIGNAL(toggled(bool)), this, SLOT(ratingSort()));
	sortProductLayout -> addWidget(rating);

	//Users Section
	usersLayout = new QHBoxLayout();
	overallLayout -> addLayout(usersLayout);
	usersList = new QComboBox();
	QString uname = QString::fromStdString(name);
	usersList -> insertItem(0, uname);
	usersLayout -> addWidget(usersList);
	addButton = new QPushButton("Add to Cart");
	connect(addButton, SIGNAL(clicked()), this, SLOT(addProducts()));

	usersLayout -> addWidget(addButton);
	viewUsersButton = new QPushButton("View Cart");
	connect(viewUsersButton, SIGNAL(clicked()), this, SLOT(cartWindow()));
	usersLayout -> addWidget(viewUsersButton);

	//Review Section
	reviewLayout = new QHBoxLayout();
	overallLayout -> addLayout(reviewLayout);
	reviewList = new QListWidget();
	reviewLayout -> addWidget(reviewList);
	buttonLayout = new QHBoxLayout();
	overallLayout -> addLayout(buttonLayout);
	reviewButtonLayout = new QHBoxLayout();
	overallLayout -> addLayout(reviewButtonLayout);
	writeReviewButton = new QPushButton("Write a Review");
	connect(writeReviewButton, SIGNAL(clicked()), this, SLOT(reviewWindow()));
	reviewLayout -> addWidget(writeReviewButton);

	//Save Database Section
	databaseName = new QLabel("Filename:");
	buttonLayout -> addWidget(databaseName);
	saveLineEdit = new QLineEdit();
	buttonLayout -> addWidget(saveLineEdit);
	saveButton = new QPushButton("Save");
	connect(saveButton, SIGNAL(clicked()), this, SLOT(saveData()));
	buttonLayout -> addWidget(saveButton);

	//Exit Button Section
	exitLayout = new QHBoxLayout();
	overallLayout -> addLayout(exitLayout);
	exitButton = new QPushButton("Exit");
	connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));
	overallLayout -> addWidget(exitButton);

	setLayout(overallLayout);
}

MainWindow::~MainWindow(){
	delete AmazonNameLabel;
	delete searchBar;
	delete searchType;
	delete searchButton;
	delete productList;
	delete sortLabel;
	delete alpha;
	delete rating;
	delete addButton;
	delete usersList;
	delete viewUsersButton;
	delete reviewList;
	delete databaseName;
	delete saveLineEdit;
	delete writeReviewButton;
	delete saveButton;
	delete exitButton;
	delete newReviewWindow;
	delete newCartWindow;
	delete searchLayout;
	delete exitLayout;
	delete productListLayout;
	delete sortProductLayout;
	delete usersLayout;
	delete reviewLayout;
	delete buttonLayout;
	delete reviewButtonLayout;
	delete overallLayout;
}

void MainWindow::alphaSort(){
	productList->clear();
	std::vector<Product*> prod = datastore -> getProductHits();
	std::string info;
	Alphabetical comp;
	msort(prod, comp);
	for(unsigned int i = 0; i < prod.size(); i++){
		info = prod[i] -> displayString();
		productList -> addItem(new QListWidgetItem(QString::fromStdString(info)));
	}

	datastore -> updateProducts(prod);
}

void MainWindow::ratingHelper(std::map<Product*, std::vector<Review*> > r){
	productList->clear();
	std::vector<Product*> prod = datastore -> getProductHits();
	Rating comp(r);
	msort(prod, comp);
	std::string info;
	for(unsigned int i = 0; i < prod.size(); i++){
		info = prod[i] -> displayString();
		productList -> addItem(new QListWidgetItem(QString::fromStdString(info)));
	}
	datastore -> updateProducts(prod);
}	

void MainWindow::ratingSort(){
	ratingHelper(datastore -> getReview());
}

void MainWindow::searchProducts(){
	productList -> clear();

	if(searchBar->text().isEmpty())
	{
		QMessageBox msgBox;
		msgBox.setText("Please type in search terms");
		msgBox.exec();
		return;
	}
	std::vector<Product*> prodHits;
	//prodHits.clear();

	std::vector<std::string> terms;
	std::string text = (searchBar -> text()).toStdString();
	std::stringstream ss(text);
	std::string word;
	ss >> word;

	while(!ss.fail()){
		terms.push_back(word);
		ss >> word;
	}

	if(alpha -> isChecked() == false && rating -> isChecked() == false){
		QMessageBox msgBox;
		msgBox.setText("Please Check a Sort Method");
		msgBox.exec();
		return;
	}

	else if(searchType -> currentIndex() == 0){
		//prodHits.clear();
		datastore -> updateProducts(prodHits);
		std::string info;
		prodHits = datastore -> search(terms, 0);
		datastore -> updateProducts(prodHits);

		for(unsigned int i = 0; i < prodHits.size(); i++){
			info = prodHits[i] -> displayString();
			productList -> addItem(new QListWidgetItem(QString::fromStdString(info)));
		}
	}

	else if(searchType -> currentIndex() == 1){
		//prodHits.clear();
		datastore -> updateProducts(prodHits);
		std::string info;
		prodHits = datastore -> search(terms, 1);

		for(unsigned int i = 0; i < prodHits.size(); i++){
			info = prodHits[i] -> displayString();
			productList -> addItem(new QListWidgetItem(QString::fromStdString(info)));
		}

	}
	searchBar -> setText("");
}

void MainWindow::addProducts(){
	std::string username = (usersList -> currentText()).toStdString();
	User* u = datastore -> findUser(username);
	std::vector<Product*> temp;

	int index = productList -> currentRow();
	if(productList -> count() != 0 && productList -> currentRow() >= 0){
		if((datastore -> getCart()).find(u) == (datastore -> getCart()).end()){
			//makes sure the product is in the map
			if((datastore -> getProductHits())[index] -> getQty() != 0){
				//if the product is not out of stock then add to the vector
				temp.push_back((datastore -> getProductHits())[index]);
			}
			else return;
		}
		else{
			if((datastore -> getProductHits())[index] -> getQty() != 0){
				temp = (datastore -> getCart())[u];
				temp.push_back((datastore -> getProductHits())[index]);
			}
			else return;
		}
		datastore -> updateCart(u, temp);
	}	
	else{
		QMessageBox msgBox;
		msgBox.setText("Please select a product to add to your cart");
		msgBox.exec();
	}
}

void MainWindow::cartWindow(){
	newCartWindow = new CartWindow(datastore -> getUser()[usersList -> currentIndex()], datastore);
	newCartWindow -> exec();
	productList -> clear();
}

void MainWindow::addReviews(){
	reviewList -> clear();
	std::map<Product*, std::vector<Review*> > mapReviews = datastore -> getReview();
	int currIndex = productList -> currentRow();
	Product* prod = (datastore -> getProductHits())[currIndex];
	std::vector<Review*> reviews = (datastore -> getReview())[prod];
	Date comp;
	msort(reviews, comp);

	for(unsigned int i = 0; i < reviews.size(); i++){
		QString name = QString::fromStdString(reviews[i] -> prodName);
		QString rate = QString::number(reviews[i] -> rating);
		QString day = QString::fromStdString(reviews[i] -> date);
		QString rText = QString::fromStdString(reviews[i] -> reviewText);
		QString username = usersList -> currentText();
		QString text = "Product Name: " +name + "\n" + "Rating: " + rate + "\n" + 
			"User: " + username + "\n" + "Date: " + day + "\n" + "Review: " + rText;
		reviewList -> addItem(text);
	}
}

void MainWindow::reviewWindow(){
	if(productList -> currentRow() < 0){
		QMessageBox msgBox;
		msgBox.setText("Please select a product");
		msgBox.exec();
	}
	else{
		std::string username = (usersList -> currentText()).toStdString();
		int currIndex = productList -> currentRow();
		Product* prod = (datastore -> getProductHits())[currIndex];
		newReviewWindow = new ReviewWindow(prod, datastore, username);
		newReviewWindow -> exec();
		addReviews();
	}
}

void MainWindow::saveData(){
	if(saveLineEdit -> text().isEmpty()){
		QMessageBox msgBox;
		msgBox.setText("Enter a filename");
		msgBox.exec();
		return;
	}
	std::string filename = (saveLineEdit -> text()).toStdString();
	ofstream ofile(filename.c_str());
	datastore -> dump(ofile);
	ofile.close();
} 

double MainWindow::basicSimilarity(User* u1, User* u2){
	std::string name1 = u1 -> getName();
	std::string name2 = u2 -> getName();
	std::set<Product*> user1, user2;
	std::map<Product*, std::vector<Review*> > reviews = datastore -> getReview();
	std::map<Product*, std::vector<Review*> >::iterator it;

	for(it = reviews.begin(); it != reviews.end(); ++it){
		std::vector<Review*> rev = (it -> second);
		for(unsigned int i = 0; i < (it -> second).size(); i++){
			if(rev[i] -> user == name1){
				user1.insert(it -> first);
			}
			if(rev[i] -> user == name2){
				user2.insert(it -> first);
			}
		}
	}
	std::set<Product*> intersect = setIntersection(user1, user2);

	double simRating = 10.0;

	if(intersect.empty()){
		simRating = 1.0;
		return simRating;
	}
	else{

		std::set<Product*>::iterator it;
		std::vector<Review*> r;
		std::map<Product*, std::vector<Review*> > mapReviews = datastore -> getReview();
		//double simRating = 10.0;
		for(it = intersect.begin(); it != intersect.end(); ++it){
			double aRating = 0.0;
			double bRating = 0.0;
			r = mapReviews[*it];
			for(unsigned int i = 0; i < r.size(); i++){
				if(r[i] -> user == name1){
					aRating = r[i] -> rating;
				}
				if(r[i] -> user == name2){
					bRating = r[i] -> rating;
				}
			}
			simRating = (double)abs(aRating - bRating)/(double)4.0;
		}
		return simRating;

	}
}

double MainWindow::refineSimilarity(User* u1, User* u2){
	dijkstraComp comp;
	Heap<DNode*, dijkstraComp> heap(2, comp);
	DNode* start = new DNode(u1, 0.0, true);
	heap.push(start);
	DNode* min;
	double refined = 10.0;

	vector<DNode*> neighbors;

	for(unsigned int i = 0; i < datastore -> getUser().size(); i++){
		if(datastore -> getUser()[i] != u1){
			DNode* n = new DNode(datastore -> getUser()[i], 10.0, false);
			heap.push(n);
			neighbors.push_back(n);
		}
	}

	while(!heap.empty()){
		min = heap.top();
		min -> checked_ = true;
		heap.pop();
		for(unsigned int i = 0; i < neighbors.size(); i++){
			double sim = basicSimilarity(min -> u_, neighbors[i] -> u_);
			if(neighbors[i] -> checked_ == false){
				if(min -> edge_ + sim < neighbors[i] -> edge_){
					neighbors[i] -> edge_ = min -> edge_ + sim;
				}
			}
			while(!heap.empty()){
				heap.pop();
			}
			for(unsigned int i = 0; i < neighbors.size(); i++){
				if(neighbors[i] -> checked_ == false){
					heap.push(neighbors[i]);
				}
			}
		}
	}

	for(unsigned int i = 0; i < neighbors.size(); i++){
		if(neighbors[i] -> u_ == u2){
			refined = neighbors[i] -> edge_;
		}
	}
	return refined;
}

std::string MainWindow::recommendedProduct(){
	set<User*> ratedUsers;
	Product* recommended = NULL;
	User* u = datastore -> findUser(name);
	std::map<User*, std::vector<Product*> > reviewedProducts = datastore -> getReviewedProducts();
	vector<Product*> mainUserReviewed = reviewedProducts.find(u) -> second;
	vector<Product*> possibleProds;
	std::map<User*, std::vector<Product*> >::iterator it;
	double interestingness = -5.0;

	if(mainUserReviewed.size() == datastore -> getProduct().size()){
		std::string s1 = "No more products to recommend";
		return s1;
	}

	for(unsigned int i = 0; i < datastore -> getProduct().size(); i++){
		bool exists = false;
		for(unsigned int j = 0; j < mainUserReviewed.size(); j++){
			if(datastore -> getProduct()[i] == mainUserReviewed[j]){
				exists = true;
			}
		}
		if(!exists){ 
			//all products that the user has not reviewed
			possibleProds.push_back(datastore -> getProduct()[i]);
		}
	}


	for(unsigned int i = 0; i < possibleProds.size(); i++){
		//pReviews is the reviews from all the products that the user has not reviewed
		std::map<Product*, std::vector<Review*> > tempReview = datastore -> getReview();
		std::map<Product*, std::vector<Review*> >::iterator it1;

		Product* p = possibleProds[i];
		std::vector<Review*> pReviews;
		if(tempReview.find(p) != tempReview.end()){
			pReviews = tempReview.find(p) -> second;
			//finds all the reviews from the possible products
			for(unsigned int j = 0; j < pReviews.size(); j++){
				//add all users who reviews the product into the set
				if(datastore -> findUser(pReviews[j] -> user) != u){
					ratedUsers.insert(datastore -> findUser(pReviews[j] -> user));
				}
			}
			set<User*>::iterator it;
			double rp = 0.0;
			double w = 0.0;

			//iterate through the user's set for all the users in the set
			for(it = ratedUsers.begin(); it != ratedUsers.end(); ++it){
				//prod is the products that this specific user has reviewed
				std::vector<Product*> prod = reviewedProducts.find(*it) -> second;
				int rating = 0;
				for(unsigned int j = 0; j < prod.size(); j++){
					for(unsigned int k = 0; k < pReviews.size(); k++){
						std::string username1 = pReviews[k] -> user;
						User* user1 = datastore -> findUser(username1);
						if(user1 == *it){
							rating = pReviews[k] -> rating;
						}
					}
				}	
				double similarity = refineSimilarity(u, *it);
				rp += (1.0 - similarity) * rating;
				w += 1.0 - similarity;
			}

			double temp = (double)rp/w;
			if(w == 0){
				if(interestingness < 0.0){
					recommended = possibleProds[i];
					interestingness = 0.0;
				}
			}
			else if(temp > interestingness){
				interestingness = temp;
				recommended = possibleProds[i];
			}
		}
	}
	std::string s2 = recommended -> getName();
	return s2;
}