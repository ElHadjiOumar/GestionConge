#ifndef DRHUI_H
#define DRHUI_H

#include <QMainWindow>

namespace Ui {
class DrhUI;
}

class DrhUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit DrhUI(QWidget *parent = nullptr);
    ~DrhUI();

private:
    Ui::DrhUI *ui;
};

#endif // DRHUI_H
