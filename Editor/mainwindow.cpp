#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "edit.cpp"

#include<QFileDialog>
#include <QPixmap>
#include <QGraphicsScene>

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

void MainWindow::on_pushButton_2_clicked()
{
    QString direccion = QFileDialog::getOpenFileName();
    ui->lineEdit->setText(direccion);

    QGraphicsScene *scene = new QGraphicsScene;
    QPixmap pixmap(ui->lineEdit->text());
    scene->addPixmap(pixmap);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

void MainWindow::on_pushButton_clicked()
{
    string direc = (ui->lineEdit->text()).toStdString();

    string output;
    double valor = ui->doubleSpinBox->value();

    Mat original = imread(direc, CV_LOAD_IMAGE_COLOR);
    Mat original_H = Histograma(original);

    Mat modificada = Suma(direc,valor);
    Mat modificada_H = Histograma(modificada);
    Show(original,original_H,modificada,modificada_H);
}

void MainWindow::on_pushButton_3_clicked()
{
    string direc = (ui->lineEdit->text()).toStdString();
    string output;
    double valor = ui->doubleSpinBox->value();

    Mat original = imread(direc, CV_LOAD_IMAGE_COLOR);
    Mat original_H = Histograma(original);

    Mat modificada = Multiplicacion(direc,valor);
    Mat modificada_H = Histograma(modificada);
    Show(original,original_H,modificada,modificada_H);
}

void MainWindow::on_pushButton_4_clicked()
{
    string direc = (ui->lineEdit->text()).toStdString();
    string output;
    double valor = ui->doubleSpinBox->value();

    Mat original = imread(direc, CV_LOAD_IMAGE_COLOR);
    Mat original_H = Histograma(original);

    Mat modificada = Division(direc,valor);
    Mat modificada_H = Histograma(modificada);
    Show(original,original_H,modificada,modificada_H);
}

void MainWindow::on_pushButton_5_clicked()
{
    string direc = (ui->lineEdit->text()).toStdString();
    string output;

    Mat original = imread(direc, CV_LOAD_IMAGE_COLOR);
    Mat original_H = Histograma(original);

    Mat modificada = to_Gris(direc);
    Mat modificada_H = Histograma_grises(modificada);
    Show(original,original_H,modificada,modificada_H);
}
