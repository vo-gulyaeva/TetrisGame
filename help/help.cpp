// Тетрис, 2022
#include "help.h"
#include "ui_help.h"
#include <QBrush>
#include <QPalette>

Help::Help(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);
    setFixedSize(600,700);
    //фоновое изображение
    QBrush brush(QPixmap(":/img/mainmenu.jpg"));
    QPalette palette;
    palette.setBrush(QPalette::Window, brush);
    this->setPalette(palette);

    connect(ui->phbMenu,&QPushButton::clicked,this,&Help::slotGoToMenu);

    ui->editTextDown->setDisabled(true);
    ui->editTextLeft->setDisabled(true);
    ui->editTextRight->setDisabled(true);
    ui->editTextRotate->setDisabled(true);
    ui->editTextSet->setDisabled(true);
}

Help::~Help()
{
    delete ui;
}

void Help::slotGoToMenu()
{
    this->hide();
    emit goToMenu();
}
