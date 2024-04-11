#include "vardialog.h"

#include <QDoubleSpinBox>

VarDialog::VarDialog(std::set<char>& var) {
  ui_->setupUi(this);
  ui_->table->setRowCount(var.size());
  int i = 0;
  for (std::set<char>::iterator it = var.begin(); it != var.end(); ++it, ++i) {
    ui_->table->setVerticalHeaderItem(i, new QTableWidgetItem(QChar(*it)));
    QTableWidgetItem* item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, .0);
    ui_->table->setItem(i, 0, item);
  }
  return;
}
VarDialog::~VarDialog() {
  delete ui_;
  return;
}

std::vector<double> VarDialog::result() {
  std::vector<double> result(26);
  for (int i = 0; i < ui_->table->rowCount(); ++i) {
    result[ui_->table->verticalHeaderItem(i)->text().toStdString()[0] - 'a'] =
        ui_->table->item(i, 0)->text().toDouble();
  }
  return result;
}