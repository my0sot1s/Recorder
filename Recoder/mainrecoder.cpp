#include "mainrecoder.h"
#include "ui_mainrecoder.h"

MainRecoder::MainRecoder(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainRecoder)
{
    ui->setupUi(this);
}

MainRecoder::~MainRecoder()
{
    delete ui;
}
