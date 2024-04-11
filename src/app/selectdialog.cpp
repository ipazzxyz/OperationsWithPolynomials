#include "selectdialog.h"

SelectDialog::SelectDialog(std::set<char>& var) {
  ui_->setupUi(this);
  for (std::set<char>::iterator it = var.begin(); it != var.end(); ++it) {
    ui_->combo->insertItem(0, QChar(*it));
  }
  if (var.size() == 1) {
    ui_->combo->setDisabled(true);
    return;
  }
  return;
}
SelectDialog::~SelectDialog() {
  delete ui_;
  return;
}

std::pair<char, int> SelectDialog::result() {
  return std::make_pair(ui_->combo->currentText().toStdString()[0],
                        ui_->spin->value());
}