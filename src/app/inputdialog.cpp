#include "inputdialog.h"

InputDialog::InputDialog() {
  ui_->setupUi(this);
  ui_->input->setFocus();
  return;
}
InputDialog::~InputDialog() {
  delete ui_;
  return;
}

QString InputDialog::result() { return ui_->input->text(); }