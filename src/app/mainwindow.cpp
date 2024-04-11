#include "mainwindow.h"

#include <polynomial.h>
#include <validator.h>

#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <utility>

#include "dividedialog.h"
#include "inputdialog.h"
#include "selectdialog.h"
#include "vardialog.h"

MainWindow::MainWindow() {
  ui_->setupUi(this);
  return;
}
MainWindow::~MainWindow() {
  delete ui_, error_message_;
  return;
}

void MainWindow::on_enter_clicked() {
  InputDialog inputDialog = InputDialog();
  if (inputDialog.exec()) {
    add_polynomial_to_base(inputDialog.result());
  }
  return;
}
void MainWindow::on_compareForEquality_clicked() {
  QList selected = ui_->list->selectedItems();
  if (selected.size() != 1 && selected.size() != 2) {
    show_error_message("Выбрано " + QString::number(selected.size()) +
                       " требуется 1 или 2");
    return;
  }
  if (selected.size() == 1 ||
      selected[0]->text().toStdString() == selected[1]->text().toStdString()) {
    show_result("равны");
  } else {
    show_result("не равны");
  }
  return;
}
void MainWindow::on_remove_clicked() {
  foreach (QListWidgetItem *item, ui_->list->selectedItems()) {
    delete ui_->list->takeItem(ui_->list->row(item));
  }
  return;
}
void MainWindow::on_summarize_clicked() {
  QList selected = ui_->list->selectedItems();
  if (selected.size() != 1 && selected.size() != 2) {
    show_error_message("Выбрано " + QString::number(selected.size()) +
                       " требуется 1 или 2");
    return;
  }
  show_result_and_add(QString::fromStdString(
      (Polynomial(selected[0]->text().toStdString()) +
       Polynomial(selected[selected.size() == 1 ? 0 : 1]->text().toStdString()))
          .toString()));
  return;
}
void MainWindow::on_multiply_clicked() {
  QList selected = ui_->list->selectedItems();
  if (selected.size() != 1 && selected.size() != 2) {
    show_error_message("Выбрано " + QString::number(selected.size()) +
                       " требуется 1 или 2");
    return;
  }
  show_result_and_add(QString::fromStdString(
      (Polynomial(selected[0]->text().toStdString()) *
       Polynomial(selected[selected.size() == 1 ? 0 : 1]->text().toStdString()))
          .toString()));
  return;
}
void MainWindow::on_divide_clicked() {
  QList selected = ui_->list->selectedItems();
  if (selected.size() != 1 && selected.size() != 2) {
    show_error_message("Выбрано " + QString::number(selected.size()) +
                       " требуется 1 или 2");
    return;
  }
  if (selected.size() == 1) {
    show_result_and_add("1", "0");
    return;
  }
  std::pair<Polynomial, Polynomial> result;
  DivideDialog dialog(
      QString::fromStdString(
          Polynomial(selected[0]->text().toStdString()).toString()),
      QString::fromStdString(
          Polynomial(selected[1]->text().toStdString()).toString()));
  if (dialog.exec()) {
    if (dialog.result()) {
      result = Polynomial(selected[1]->text().toStdString()) /
               Polynomial(selected[0]->text().toStdString());
    } else {
      result = Polynomial(selected[0]->text().toStdString()) /
               Polynomial(selected[1]->text().toStdString());
    }
    try {
      show_result_and_add(QString::fromStdString(result.first.toString()),
                          QString::fromStdString(result.second.toString()));
    } catch (const Polynomial::CannotApplyFunction &e) {
      show_error_message(QString::fromStdString(e.message()));
    }
  }
  return;
}
void MainWindow::on_calculateValue_clicked() {
  QList selected = ui_->list->selectedItems();
  if (selected.size() != 1) {
    show_error_message("Выбрано " + QString::number(selected.size()) +
                       " требуется 1");
    return;
  }
  Polynomial polynomial = Polynomial(selected[0]->text().toStdString());
  std::set<char> varList = polynomial.var();
  VarDialog varDialog = VarDialog(varList);
  if (varDialog.exec()) {
    show_result(QString::number(Polynomial(selected[0]->text().toStdString())
                                    .calculate_value(varDialog.result())));
  }
  return;
}
void MainWindow::on_calculateDerivative_clicked() {
  QList selected = ui_->list->selectedItems();
  if (selected.size() != 1) {
    show_error_message("Выбрано " + QString::number(selected.size()) +
                       " требуется 1");
    return;
  }
  Polynomial polynomial = Polynomial(selected[0]->text().toStdString());
  std::set<char> s = polynomial.var();
  if (s.size() == 0) {
    show_result_and_add("0");
    return;
  }
  SelectDialog dialog(s);
  if (dialog.exec()) {
    std::pair<char, int> p = dialog.result();
    show_result_and_add(QString::fromStdString(
        polynomial.derivative(p.first, p.second).toString()));
  }
  return;
}
void MainWindow::on_findIntRoots_clicked() {
  QList selected = ui_->list->selectedItems();
  if (selected.size() != 1) {
    show_error_message("Выбрано " + QString::number(selected.size()) +
                       " требуется 1");
    return;
  }
  Polynomial polynomial = Polynomial(selected[0]->text().toStdString());
  std::set<char> varList = polynomial.var();
  try {
    std::set<int> set =
        Polynomial(selected[0]->text().toStdString()).int_roots();
    if (!set.size()) {
      show_result("нет решений");
      return;
    }
    if (set.size() == 20001) {
      show_result("бесконечность решений");
      return;
    }
    QString s;
    for (std::set<int>::iterator it = set.begin(); it != set.end(); ++it) {
      s += QString::number(*it) + ", ";
    }
    s.chop(2);
    show_result(s);
  } catch (const Polynomial::CannotApplyFunction &e) {
    show_error_message(QString::fromStdString(e.message()));
  }
  return;
}
void MainWindow::on_save_clicked() {
  QFile file = QFileDialog::getOpenFileName();
  file.open(QIODevice::WriteOnly);
  QList selected = ui_->list->selectedItems();
  QTextStream out(&file);
  if (!selected.size()) {
    for (int i = 0; i < ui_->list->count(); ++i) {
      out << ui_->list->item(i)->text() << Qt::endl;
    }
  } else {
    for (QListWidgetItem *item : selected) {
      out << item->text() << Qt::endl;
    }
  }
  file.close();
  return;
}
void MainWindow::on_load_clicked() {
  QFile file = QFileDialog::getOpenFileName();
  file.open(QIODevice::ReadOnly);
  QTextStream in(&file);
  while (!in.atEnd()) {
    add_polynomial_to_base(in.readLine());
  }
  file.close();
  return;
}

void MainWindow::add_polynomial_to_base(const QString &s) {
  try {
    ui_->list->addItem(
        QString::fromStdString(Polynomial(s.toStdString()).toString()));
  } catch (Validator::BadFormat &e) {
    show_error_message(QString::fromStdString(e.what()));
  }
  return;
}
void MainWindow::show_result(const QString &s) {
  QMessageBox message;
  message.setText("Результат: " + s);
  message.exec();
  return;
}
void MainWindow::show_result_and_add(const QString &s) {
  QMessageBox message;
  message.setText("Результат: " + s);
  message.setInformativeText("Сохранить в базу?");
  message.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
  message.setDefaultButton(QMessageBox::Save);
  if (message.exec() == QMessageBox::Save) {
    add_polynomial_to_base(s);
  }
  return;
}
void MainWindow::show_result_and_add(const QString &s1, const QString &s2) {
  QMessageBox message;
  message.setText("Результат:\n" + s1 + '\n' + s2);
  message.setInformativeText("Сохранить в базу?");
  message.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
  message.setDefaultButton(QMessageBox::Save);
  if (message.exec() == QMessageBox::Save) {
    add_polynomial_to_base(s1);
    add_polynomial_to_base(s2);
  }
  return;
}
void MainWindow::show_error_message(const QString &s) {
  error_message_->showMessage(s);
  std::cerr << s.toStdString() << std::endl;
  return;
}