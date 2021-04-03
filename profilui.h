#ifndef PROFILUI_H
#define PROFILUI_H

#include <QMainWindow>

namespace Ui {
class ProfilUI;
}

class ProfilUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProfilUI(QWidget *parent = nullptr);
    ~ProfilUI();

private:
    Ui::ProfilUI *ui;
};

#endif // PROFILUI_H
