// Тетрис, 2022
#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QPalette>
#include <QBrush>

MainMenu::MainMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    setFixedSize(600,700);

    playingField_ = new PlayingField();
    connect(ui->phbGame, &QPushButton::clicked, this, &MainMenu::toGame);
    connect(ui->phbExit, &QPushButton::clicked, this, &MainMenu::close);
    connect(playingField_, &PlayingField::goToMenu, this, &MainMenu::show);
}

MainMenu::~MainMenu()
{
    delete playingField_;
    delete ui;
}

void MainMenu::toGame()
{
    //устанавливаем полноэкранный режим
    playingField_->showMaximized();
    playingField_->setFixedSize(playingField_->size());
    this->hide();
}

