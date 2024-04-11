#include "dividedialog.h"

DivideDialog::DivideDialog(QString s1, QString s2) {
  ui_->setupUi(this);
  ui_->label->setText(s1);
  ui_->label_3->setText(s2);
}
DivideDialog::~DivideDialog() { delete ui_; }

bool DivideDialog::result() { return ui_->checkBox->isChecked(); }

void DivideDialog::on_checkBox_clicked() {
  QString tmp = ui_->label->text();
  ui_->label->setText(ui_->label_3->text());
  ui_->label_3->setText(tmp);
}