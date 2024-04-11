#ifndef OWP_APP_SELECTDIALOG_H_
#define OWP_APP_SELECTDIALOG_H_

#include <QDialog>
#include <set>
#include <utility>

#include "ui_selectdialog.h"

class SelectDialog : public QDialog {
  Q_OBJECT
 public:
  SelectDialog(std::set<char> &);
  ~SelectDialog();

  std::pair<char, int> result();

 private:
  Ui::SelectDialog *ui_ = new Ui::SelectDialog;
};

#endif