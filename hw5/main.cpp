#include "main_window.h"
#include "db_parser.h"
#include "product_parser.h"
#include <QApplication>

using namespace std;

int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Please specify a database file" << endl;
  }

  Storage ds;

  DBParser parser;

  parser.addProductParser(new ProductBookParser);
  parser.addProductParser(new ProductClothingParser);
  parser.addProductParser(new ProductMovieParser);

  if( parser.parse(argv[1], ds) ){
    cerr << "Error parsing!" << endl;
    return 1;
  }

  QApplication app(argc, argv);

  MainWindow mainWindow(ds);

  mainWindow.show();

  return app.exec();
}
