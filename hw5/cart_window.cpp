#include "cart_window.h"
#include <QMessageBox>

CartWindow::CartWindow(User* u, Storage* ds){
	storage = ds;
	user_ = u;
	overallLayout = new QVBoxLayout();

	cartLabel = new QLabel("Shopping Cart");
	QFont titleFont;
	titleFont.setBold(true);
	titleFont.setPointSize(14);
	cartLabel->setFont(titleFont);
	cartLabel->setAlignment(Qt::AlignCenter);
	overallLayout -> addWidget(cartLabel);
	cartList = new QListWidget();

	cart_ = storage -> getCart();
	products = cart_[user_];
	std::string info;
	for(unsigned int i = 0; i < products.size(); i++){
		info = products[i] -> displayString();
		cartList -> addItem(QString::fromStdString(info));
	}
	overallLayout -> addWidget(cartList);

	addButton = new QPushButton("Checkout Cart");
	connect(addButton, SIGNAL(clicked()), this, SLOT(buyCart()));
	overallLayout -> addWidget(addButton);

	removeButton = new QPushButton("Remove Item");
	connect(removeButton, SIGNAL(clicked()), this, SLOT(removeItem()));
	overallLayout -> addWidget(removeButton);

	exitButton = new QPushButton("Exit");
	connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));
	overallLayout -> addWidget(exitButton);

	setLayout(overallLayout);
}
 
CartWindow::~CartWindow(){
	delete overallLayout;
	delete cartLabel;
	delete cartList;
	delete addButton;
	delete removeButton;
	delete exitButton;
} 

void CartWindow::removeItem(){
	cartList -> clear();

	std::string info;
	int index = cartList -> currentRow() + 1;
	if(index < 0){
		QMessageBox msgBox;
		msgBox.setText("Please select a product to remove");
		msgBox.exec();
		return;
	}
	products.erase(products.begin() + index);
	cart_[user_] = products;

	if(products.size() == 0){
		QMessageBox msgBox;
		msgBox.setText("There's nothing in your cart!");
		msgBox.exec();
		return;
	}
	else{
		for(unsigned int i = 0; i < products.size(); i++){
			info = products[i] -> displayString();
			cartList -> addItem(QString::fromStdString(info));
		}
	}	

	storage -> updateCart(user_, products);
}

void CartWindow::buyCart(){
	std::vector<Product*> temp = cart_[user_];
	if(temp.size() == 0){
		QMessageBox msgBox;
		msgBox.setText("There are no items in the cart");
		msgBox.exec();
		return;
	}
	for(unsigned int i = 0; i < temp.size(); i++){
		double money = user_ -> getBalance();
		double price = temp[i] -> getPrice();
		int quanity = temp[i] -> getQty();
		if(money >= price && quanity > 0){
			//if user has enough money and the item is in stock
			//subtract one from the quantity and deduct the user's balance
			temp[i] -> subtractQty(1);
			user_ -> deductAmount(price);
		}
	}
	temp.clear();
	cartList -> clear();
	cart_[user_] = temp;
	storage -> updateCart(user_, temp);
	QMessageBox msgBox;
	msgBox.setText("You have successfully bought the cart");
	msgBox.exec();
}
