// Тетрис, 2022
#include "game/playingfield.h"
#include "ui_playingfield.h"
#include <QScreen>
#include <QRandomGenerator>

PlayingField::PlayingField(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayingField), score_(-15)
{
    ui->setupUi(this);
    //фоновое изображение
    QBrush brush(QPixmap(":/img/game/playingfield.jpeg"));
    QPalette palette;
    palette.setBrush(QPalette::Window, brush);
    this->setPalette(palette);

    ui->gridMain->setColumnStretch(0,1);
    ui->gridMain->setColumnStretch(1,3);
    ui->gridMain->setColumnStretch(2,1);

    ui->gridCentral->setColumnStretch(0,2);
    ui->gridCentral->setColumnStretch(1,1);

    connect(ui->phbHome, &QPushButton::clicked, this, &PlayingField::slotToMenu);

    gameScene_ = new GameScene();
    connect(gameScene_, &GameScene::signalPressMouse, this, &PlayingField::slotPauseOrPlayGame);

    ui->graphicsView->setScene(gameScene_);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // фигуры J, I, O, L, Z, T, S
    typeForm = {{{1,1}, {0,1}, {0,1}},
                {{1}, {1}, {1}, {1}},
                {{1,1}, {1,1}},
                {{1,1}, {1,0}, {1,0}},
                {{0,1,1}, {1,1,0}},
                {{1,1,1},{0,1,0}},
                {{1,1,0},{0,1,1}}};
    //инициализируем массив последних фигур 4 случайными значениями номера фигуры
    //(выбрала их не случайно - с них не удобно начинать игру - особенно Z и S)
    prevElem_ = {0,3,4,6};
    nextElem_ = generalNumElem();
    //настройка времени
    timerGame_ = new QTimer(this);
    connect(timerGame_, &QTimer::timeout, this, &PlayingField::slotUpdateTime);
    timerGame_->setInterval(1000);
    connect(ui->phbPauseAndPlay,&QPushButton::clicked, this, &PlayingField::slotPauseOrPlayGame);
    connect(ui->phbReset,&QPushButton::clicked, this, &PlayingField::slotGameReset);
    level_ = 2;
}

PlayingField::~PlayingField()
{
    delete ui;
}

void PlayingField::openGame()
{
    //устанавливаем полноэкранный режим
    this->showMaximized();
    //продолжаем только если открытие игры происходит впервые
    if(field_ && activElem_ && textGameOver_)
        return;
    this->setFixedSize(this->size());
    //настраиваем сцену
    QSize sizeView = ui->graphicsView->frameSize();
    gameScene_->setSceneRect(0,0,sizeView.width(),sizeView.height());
    width_ = sizeView.width();
    height_ = sizeView.height();
    //добавляем игровые элементы на сцену
    addGameElemToScene();
    //начинаем игру
    startGame();
}

void PlayingField::addGameElemToScene()
{
    if(field_ && activElem_ && textGameOver_)
        return;
    //добавляем на сцену поле для фиксированных элементов
    int widhtSquare = (int)width_/15;
    int strField = (int)height_/widhtSquare;
    int stbField = (int)width_/widhtSquare;
    field_ = new FixedShape(strField,stbField, widhtSquare, height_% widhtSquare);
    gameScene_->addItem(field_);
    //добавляем на сцену активный элемент
    activElem_ = new ActivShape(width_, height_, widhtSquare, field_->getField());
    gameScene_->addItem(activElem_);
    activElem_->setSpeed(speedActivElem(level_));
    statusGame_ = true;
    connect(gameScene_, &GameScene::signalPressControlKeys, activElem_, &ActivShape::slotMoveShape);
    connect(activElem_, &ActivShape::signalFell, this, &PlayingField::slotUpdateFieldAndPosElem);

    textGameOver_ = new QGraphicsSimpleTextItem("Конец игры");
    QFont font("Times", 70, QFont::Cursive);
    textGameOver_->setFont(font);
    textGameOver_->setBrush(QBrush(QColor(253,217,181,185)));
}

void PlayingField::slotToMenu()
{
    pauseGame();
    this->close();
    emit goToMenu();
}

void PlayingField::changeSpeed(int level)
{
    if(field_ && activElem_ && textGameOver_)
        activElem_->setSpeed(speedActivElem(level));
    level_ = level;
}

int PlayingField::speedActivElem(int level) const
{
    return 600 * 1.5/level;
}

int PlayingField::generalNumElem()
{
    int num = QRandomGenerator::global()->bounded(0, 7);
    while(prevElem_.contains(num))
        num = QRandomGenerator::global()->bounded(0, 7);
    prevElem_.pop_front();
    prevElem_.push_back(num);
    return num;
}

void PlayingField::startGame()
{
    timeGame_ = QTime(0,0);
    timerGame_->start();
    updatePosActiveElem();
}

void PlayingField::slotUpdateFieldAndPosElem(const FixField &field, int minFixStr)
{
    field_->setField(field);
    if(field_->setMinFixStr(minFixStr))
        gameOver();
    else
        updatePosActiveElem();
}

void PlayingField::updatePosActiveElem()
{
    int widhtSquare = (int)width_/15;           //ширина и длина одного квадратика фигуры
    activElem_->setTypeShape(typeForm[nextElem_]);
    int widthShape = typeForm[nextElem_].at(0).size()*widhtSquare; //ширина элемента - нужно учитывать, чтобы не выйти за границы сцены
    int yPos = (height_% widhtSquare) - widhtSquare;    //чтобы позиция у была четна ширине квадрата
    int xPos = QRandomGenerator::global()->bounded(0, width_ - widthShape);
    xPos-=xPos%widhtSquare;   //учитываем размер сетки
    activElem_->setPos(xPos,yPos);
    nextElem_ = generalNumElem();
    ui->nextElem->setShape(typeForm[nextElem_]);
    //обновляем счет
    score_+=15;
    ui->scoreEdit->setValue(score_);
}

void PlayingField::slotUpdateTime()
{
    timeGame_ = timeGame_.addSecs(1);
    ui->timeEdit->setTime(timeGame_);
}

void PlayingField::gameOver()
{
    pauseGame();
    ui->phbPauseAndPlay->setEnabled(false);
    timerGame_->stop();
    gameScene_->addItem(textGameOver_);
    textGameOver_->setPos(gameScene_->width()/2 - 200, gameScene_->height()/3);
}

void PlayingField::slotGameReset()
{
    //очищаем поле
    field_->clearField();
    activElem_->clearField();
    gameScene_->removeItem(textGameOver_);
    ui->phbPauseAndPlay->setEnabled(true);
    timeGame_ = QTime(0,0);
    ui->timeEdit->setTime(timeGame_);
    score_ = -15;
    if(!statusGame_)
        playGame();
    startGame();
}

void PlayingField::slotPauseOrPlayGame()
{
    if(!activElem_)
        return;
    if(statusGame_)
        pauseGame();
    else
        playGame();
}

void PlayingField::pauseGame()
{
    activElem_->setPause();
    ui->phbPauseAndPlay->setStyleSheet("QPushButton {background: rgba(0,0,0,0); background-image: url(:/img/game/phbPlay.png); border:2px "
                                       "solid rgba(0,0,0,0); } QPushButton:hover {border:2px solid #000000; border-radius: 16px;}");
    timerGame_->stop();
    statusGame_ = false;
}
void PlayingField::playGame()
{
    activElem_->setPlay();
    ui->phbPauseAndPlay->setStyleSheet("QPushButton {background: rgba(0,0,0,0); background-image: url(:/img/game/phbPause.png); border:2px "
                                       "solid rgba(0,0,0,0); } QPushButton:hover {border:2px solid #000000; border-radius: 16px; }");
    timerGame_->start();
    statusGame_ = true;
}
