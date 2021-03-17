#ifndef MANAGERUI_H
#define MANAGERUI_H

#include <QMainWindow>

namespace Ui {
class ManagerUI;
}

class ManagerUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit ManagerUI(QWidget *parent = nullptr);
    ~ManagerUI();

private:
    Ui::ManagerUI *ui;
};

#endif // MANAGERUI_H
