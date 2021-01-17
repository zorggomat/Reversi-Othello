#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    p1 = nullptr;
    p2 = nullptr;

    //Connect buttons to click handlers
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::startButtonClicked);
    connect(ui->restartButton, &QPushButton::clicked, this, &MainWindow::startButtonClicked);
    connect(ui->backButton, &QPushButton::clicked, this, &MainWindow::backButtonClicked);

    //Load images from resources
    fieldPixmap.load(":/img/field.png");
    whitePixmap.load(":/img/white.png");
    blackPixmap.load(":/img/black.png");

    //Init graphicsView
    scene = new GraphicsScene();
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete scene;
    delete ui;
}

void MainWindow::Draw(const Match &f)
{
    for(char i  = 1; i <= 8; ++i)
        for(int j = 1; j <= 8; ++j)
        {
            CellState state = f.get(Position(j, i));
            if (state == empty) continue;
            QPixmap &pixmap = (state == white ? whitePixmap : blackPixmap);
            scene->addPixmap(pixmap)->setOffset((j-1)*68+4, (i-1)*68+4);
        }
}

void MainWindow::backButtonClicked()
{
    //stop game
    disconnect(p1, SIGNAL(turnFinished(Player*, Position)), this, SLOT(processTurn(Player*, Position)));
    disconnect(p2, SIGNAL(turnFinished(Player*, Position)), this, SLOT(processTurn(Player*, Position)));
    ui->tabWidget->setCurrentIndex(0); //switch to menu tab
}

void MainWindow::startButtonClicked()
{
    //Players cleanup
    if(p1 != nullptr) delete p1;
    if(p2 != nullptr) delete p2;

    //Clear scene and field
    f = Match();
    scene->clear();
    scene->addPixmap(fieldPixmap);

    //Create player1
    if(ui->p1HumanRB->isChecked())
        p1 = new Human(scene);
    else if(ui->p1SimpleBotRB->isChecked())
        p1 = new SimpleBot();
    else p1 = new AdvancedBot();

    //Create player 2
    if(ui->p2HumanRB->isChecked())
        p2 = new Human(scene);
    else if(ui->p2SimpleBotRB->isChecked())
        p2 = new SimpleBot();
    else p2 = new AdvancedBot();

    //Changeto: setcolor
    p1->setColor(black);
    p2->setColor(white);

    //Connect player's signal to mainwindow's slot
    connect(p1, SIGNAL(turnFinished(Player*, Position)), this, SLOT(processTurn(Player*, Position)));
    connect(p2, SIGNAL(turnFinished(Player*, Position)), this, SLOT(processTurn(Player*, Position)));

    //Ui
    Draw(f);
    ui->statusLabel->setText(p1->name() + "'s (black) turn");
    ui->blackLabel->setText("Black: 2");
    ui->whiteLabel->setText("White: 2");
    ui->tabWidget->setCurrentIndex(1);

    p1->turnStart(f);
}

void MainWindow::processTurn(Player *currentPlayer, Position p)
{
    Player *nextPlayer = (currentPlayer == p1 ? p2 : p1);

    if(f.makeTurn(p, currentPlayer->getColor()) == false)
    {
        //If move is incorrect
        currentPlayer->turnStart(f);
        return;
    }

    //Ui
    Draw(f);
    ui->statusLabel->setText(nextPlayer->name() + "'s (" + (nextPlayer->getColor() == white ? "white" : "black") + ") turn");
    int p1count = f.count(black);
    int p2count = f.count(white);
    ui->blackLabel->setText("Black: " + QString::number(p1count));
    ui->whiteLabel->setText("White: " + QString::number(p2count));

    //Turn transfer
    if(f.turnsAvailable(nextPlayer->getColor()))
        nextPlayer->turnStart(f);   //Another player's turn
    else if(f.turnsAvailable(currentPlayer->getColor()))
        currentPlayer->turnStart(f); //No available turns for another player; current player's turn
    else //No available turns for both players; game over
    {
        if(p1count == p2count)
            ui->statusLabel->setText("Tie");
        else if (p1count > p2count)
            ui->statusLabel->setText(p1->name() + " (black) won!");
        else ui->statusLabel->setText(p2->name() + " (white) won!");
    }
}
