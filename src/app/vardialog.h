#ifndef OWP_APP_VARDIALOG_H_
#define OWP_APP_VARDIALOG_H_

#include <vector>
#include <set>

#include "ui_vardialog.h"

class VarDialog : public QDialog {
  Q_OBJECT
 public:
  VarDialog(std::set<char> &);
  ~VarDialog();

  std::vector<double> result();

 private:
  Ui::VarDialog *ui_ = new Ui::VarDialog;
};

#endif