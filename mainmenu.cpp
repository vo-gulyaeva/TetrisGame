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
    connect(playingField_, &PlayingField::goToMenu, this, [&]{this->show(); ui->phbGame->setText("Продолжить");});
    help_ = new Help();
    connect(ui->phbHelp, &QPushButton::clicked, this, &MainMenu::toHelp);
    connect(help_, &Help::goToMenu, this, &MainMenu::show);
    level_ = 2;
    settings_ = new Settings(level_);
    connect(ui->phbSettings, &QPushButton::clicked, this, &MainMenu::toSettings);
    connect(settings_, &Settings::goToMenu, this, &MainMenu::changeLevel);
}

MainMenu::~MainMenu()
{
    delete playingField_;
    delete help_;
    delete settings_;
    delete ui;
}

void MainMenu::toGame()
{
    playingField_->openGame();
    this->hide();
}

void MainMenu::toHelp()
{
    help_->show();
    this->hide();
}

void MainMenu::toSettings()
{
    settings_->show();
    settings_->setLevel(level_);
    this->hide();
}

void MainMenu::changeLevel(int level)
{
    this->show();
    playingField_->changeSpeed(level);
    level_ = level;
}
