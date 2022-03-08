// Тетрис, 2022
#include "playingfield.h"
#include "ui_playingfield.h"
#include <QScreen>

PlayingField::PlayingField(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayingField)
{
    ui->setupUi(this);
    //фоновое изображение
    QBrush brush(QPixmap(":/img/playingfield.jpeg"));
    QPalette palette;
    palette.setBrush(QPalette::Window, brush);
    this->setPalette(palette);

    ui->gridMain->setColumnStretch(0,1);
    ui->gridMain->setColumnStretch(1,3);
    ui->gridMain->setColumnStretch(2,1);

    ui->gridCentral->setColumnStretch(0,2);
    ui->gridCentral->setColumnStretch(1,1);

    connect(ui->phbHome, &QPushButton::clicked, this, &PlayingField::slotToMenu);
}

PlayingField::~PlayingField()
{
    delete ui;
}

void PlayingField::slotToMenu()
{
    this->close();
    emit goToMenu();
}
