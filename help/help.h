//////////////////////////////////////////////////////////////////////////
//
//! \file help.h
//! \brief Окно с инструкцией
//
//  Gulyaeva V.
//
//////////////////////////////////////////////////////////////////////////
#ifndef HELP_H
#define HELP_H

#include <QWidget>

namespace Ui {
class Help;
}

class Help : public QWidget
{
    Q_OBJECT
signals:
    void goToMenu();
public:
    explicit Help(QWidget *parent = nullptr);
    ~Help();
private slots:
    void slotGoToMenu();
private:
    Ui::Help *ui;
};

#endif // HELP_H
