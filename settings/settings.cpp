// Тетрис, 2022
#include "settings.h"
#include "ui_settings.h"

Settings::Settings(int level, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    setFixedSize(600,700);
    //фоновое изображение
    QBrush brush(QPixmap(":/img/mainmenu.jpg"));
    QPalette palette;
    palette.setBrush(QPalette::Window, brush);
    this->setPalette(palette);
    ui->textEdit->setDisabled(true);

    setLevel(level);
    connect(ui->rbBeginner, &QRadioButton::toggled, this, &Settings::slotChangeLevel);
    connect(ui->rbPro, &QRadioButton::toggled, this, &Settings::slotChangeLevel);
    connect(ui->rbFan, &QRadioButton::toggled, this, &Settings::slotChangeLevel);

    connect(ui->phbHome, &QPushButton::clicked, this, &Settings::slotToMenu);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::slotToMenu()
{
    this->hide();
    emit goToMenu(level_);
}

void Settings::setLevel(int level)
{
    level_ = level;

    if(level_ == 1)
            ui->rbBeginner->setChecked(true);
        else
            if(level_ == 2)
                ui->rbFan->setChecked(true);
        else
                ui->rbPro->setChecked(true);
}

void Settings::slotChangeLevel(bool tr)
{
    if(!tr)
        return;
    if(ui->rbBeginner->isChecked())
        level_ = 1;
    else
        if(ui->rbFan->isChecked())
            level_ = 2;
    else
            level_ = 3;
}
