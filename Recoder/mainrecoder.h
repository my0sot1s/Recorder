#ifndef MAINRECODER_H
#define MAINRECODER_H

#include <QMainWindow>
#include "recoders.h"

namespace Ui {
class MainRecoder;
}

class MainRecoder : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainRecoder(QWidget *parent = 0);
    ~MainRecoder();

    recoders rec;

private:
    Ui::MainRecoder *ui;
};

#endif // MAINRECODER_H
