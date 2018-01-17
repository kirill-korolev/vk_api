#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    vk_api::auth<>("6334044", vk_api::scopes::friends, [this](const std::string& contents) -> std::string {
        this->ui->m_webview->setHtml(QString(contents.c_str()));

        return "";
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}
