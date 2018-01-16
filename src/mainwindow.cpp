#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    vk_api::auth("6334044", vk_api::scopes::friends, [](const std::string& c) -> std::string{
        return "";
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
