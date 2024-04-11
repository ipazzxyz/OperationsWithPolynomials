#include <polynomial.h>

#include <QApplication>
#include <iostream>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication application(argc, argv);
  MainWindow window;
  window.show();
  return application.exec();
}