#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    player = new QMediaPlayer(this);
    vw = new QVideoWidget(this);
    this->setCentralWidget(vw);
    player->setVideoOutput(vw);
    slider = new QSlider(this);
    slider->setOrientation(Qt::Horizontal);
    ui->statusbar->addPermanentWidget(slider);
    connect(player, &QMediaPlayer::durationChanged, slider, &QSlider::setMaximum);
    connect(player, &QMediaPlayer::positionChanged, slider, &QSlider::setValue);
    connect(slider, &QSlider::sliderMoved, player, &QMediaPlayer::setPosition);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_actionFile_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open a file");
    on_actionPause_triggered();
    player->setMedia(QUrl::fromLocalFile(filename));
    on_actionPlay_triggered();

}

void MainWindow::on_actionPlay_triggered()
{
    player->play();
}

void MainWindow::on_actionPause_triggered()
{
    player->pause();
}


