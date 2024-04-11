#ifndef OWP_APP_MAINWINDOW_H_
#define OWP_APP_MAINWINDOW_H_

#include <QErrorMessage>
#include <QMainWindow>

#include "ui_mainwindow.h"

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  MainWindow();
  ~MainWindow();

 public slots:
  void on_enter_clicked();
  void on_remove_clicked();
  void on_compareForEquality_clicked();
  void on_summarize_clicked();
  void on_multiply_clicked();
  void on_divide_clicked();
  void on_calculateValue_clicked();
  void on_calculateDerivative_clicked();
  void on_findIntRoots_clicked();
  void on_save_clicked();
  void on_load_clicked();

 private:
  Ui::MainWindow *ui_ = new Ui::MainWindow;
  QErrorMessage *error_message_ = new QErrorMessage;

  void add_polynomial_to_base(const QString &);
  void show_result(const QString &);
  void show_result_and_add(const QString &);
  void show_result_and_add(const QString &, const QString &);
  void show_error_message(const QString &);
};

#endif  // OWP_APP_MAINWINDOW_H_