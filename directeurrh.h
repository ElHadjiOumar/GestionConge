#ifndef DIRECTEURRH_H
#define DIRECTEURRH_H

#include <QMainWindow>

namespace Ui {
class DirecteurRH;
}

class DirecteurRH : public QMainWindow
{
    Q_OBJECT

public:
    explicit DirecteurRH(QWidget *parent = nullptr);
    ~DirecteurRH();

private:
    Ui::DirecteurRH *ui;
};

#endif // DIRECTEURRH_H
