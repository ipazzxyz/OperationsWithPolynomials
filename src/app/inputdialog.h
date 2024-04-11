#ifndef OWP_APP_INPUTDIALOG_H_
#define OWP_APP_INPUTDIALOG_H_

#include <QDialog>

#include "ui_inputdialog.h"

class InputDialog : public QDialog {
  Q_OBJECT
 public:
  InputDialog();
  ~InputDialog();

  QString result();

 private:
  Ui::InputDialog *ui_ = new Ui::InputDialog;
};

#endif  // OWP_APP_INPUTDIALOG_H_