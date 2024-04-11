#ifndef OWP_APP_DIVIDEDIALOG_H_
#define OWP_APP_DIVIDEDIALOG_H_

#include <QString>

#include "ui_dividedialog.h"

class DivideDialog : public QDialog {
  Q_OBJECT
 public:
  DivideDialog(QString, QString);
  ~DivideDialog();
 public slots:
  void on_checkBox_clicked();

  bool result();

 private:
  Ui::DivideDialog *ui_ = new Ui::DivideDialog;
};

#endif  // OWP_APP_DIVIDEDIALOG_H_