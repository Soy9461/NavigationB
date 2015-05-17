#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //QString str;

    //str.append(ui->textEdit->toPlainText());

    //str.append(ui->textEdit_2->toPlainText());

    std::string pathStr;

    std::string origin = ui->lineEdit->text().toStdString();

    std::string destination = ui->lineEdit_2->text().toStdString();


    std::deque<INavigationPoint*>* path = theBuilding.FindPath(origin, destination);

    if(path != 0){

        std::deque<INavigationPoint*>::const_iterator iterator = path->begin(), end = path->end();

        for(; iterator != end; ++iterator){

            pathStr.append((*iterator)->GetName().c_str());

            if(iterator + 1 != end)pathStr.append(" -> ");

        }
    } else {
        pathStr = "Path do not exist.";
    }

    //pathStr = origin + destination;

    QString result = QString::fromStdString(pathStr);

    ui->textEdit->setPlainText(result);
}
