#include "user.h"
#include "storage.h"
#include "product.h"
#include <vector>
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

class CartWindow : public QDialog
{
	Q_OBJECT
public:
	CartWindow(User* u, Storage* ds);
	~CartWindow();

private slots:
	void removeItem();
	void buyCart();

private:
	QVBoxLayout* overallLayout;
	QLabel* cartLabel;
	QListWidget* cartList;

	QPushButton* addButton;
	QPushButton* removeButton;
	QPushButton* exitButton;

	User* user_;
	std::map<User*, std::vector<Product*> > cart_;
	std::vector<Product*> products;
	Storage* storage;
};
