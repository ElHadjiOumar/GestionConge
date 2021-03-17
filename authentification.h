#ifndef AUTHENTIFICATION_H
#define AUTHENTIFICATION_H

#include <QMainWindow>
#include "user.h"


namespace Ui {
class Authentification;
}

class Authentification : public QMainWindow
{
    Q_OBJECT

public:
    explicit Authentification(QWidget *parent = nullptr);
    explicit Authentification(QObject *controller);

    bool validate();
    bool closeConfirmation();
    User getUser() {return user ;}
    void setUser (User obj) { user = obj; }

    ~Authentification();

private:
    Ui::Authentification *ui;
    User user;
};

#endif // AUTHENTIFICATION_H
