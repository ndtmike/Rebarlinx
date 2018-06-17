/****************************************************************************
**
** This software is furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** File Name: mainwindow.cpp
**
** Rebarlinx software
**
** Author: Michael W. Hoag
** Copyright Michael W. Hoag 2018
** Email: mike@ndtjames.com
**
** 6/16/18 Initial Creation
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwindow.h"
#include "console.h"

#include <QMessageBox>
#include <QLabel>

/******************************************************************************

  Function: MainWindow()

  Description:
  ============
  Creator for rebarlinx project

  This project is implemented without Designer in order to integrate the
  QwtPlot library, which conflict with the msvc.

******************************************************************************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    console = new Console;
    console->setEnabled(false);
    setCentralWidget(console);
    serial = new QSerialPort(this);
    status = new QLabel;

    CreateActions();
    CreateMenus();
    CreateStatusBar();
}

MainWindow::~MainWindow()
{

}
/******************************************************************************

  Function: createActions

  Description:
  ============
  Connects Menu's to Actions

******************************************************************************/
void MainWindow::CreateActions()
{
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &MainWindow::MenuActNewFile);

    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::MenuActOpen);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::MenuActSave);

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, &QAction::triggered, this, &QWidget::close);

    copyAct = new QAction(tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    connect(copyAct, &QAction::triggered, this, &MainWindow::MenuActCopy);

    PlotAct = new QAction(tr("&Plot"), this);
    PlotAct->setStatusTip(tr("Plots the data uploaded"));
    connect(PlotAct, &QAction::triggered, this, &MainWindow::MenuActPlot);

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, &QAction::triggered, this, &MainWindow:: MenuActAbout);

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, &QAction::triggered, qApp, &QApplication::aboutQt);

    connect(serial, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &MainWindow::handleError);
    connect(serial, &QSerialPort::readyRead, this, &MainWindow::SerialPortReadData);
    connect(console, &Console::getData, this, &MainWindow::SerialPortWriteData);
}

/******************************************************************************

  Function: createMenus

  Description:
  ============
  Creates the Menu items

******************************************************************************/
void MainWindow::CreateMenus()
{
    FileMenu = menuBar()->addMenu(tr("&File"));
    FileMenu->addAction(newAct);
    FileMenu->addAction(openAct);
    FileMenu->addAction(saveAct);
    FileMenu->addSeparator();
    FileMenu->addAction(exitAct);

    EditMenu = menuBar()->addMenu(tr("&Edit"));
    EditMenu->addAction(copyAct);

    GraphMenu = menuBar()->addMenu(tr("&Graph"));
    GraphMenu->addAction(PlotAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

/******************************************************************************

  Function: CreateStatuBar

  Description:
  ============
  Creates the Menu items

******************************************************************************/
void MainWindow::CreateStatusBar()
{
    status = new QLabel(" Not Connected ");
    status->setAlignment(Qt::AlignHCenter);
    status->setMinimumSize(status->sizeHint());

//    formulaLabel = new QLabel;
//    formulaLabel->setIndent(3);

    statusBar()->addWidget(status);
//    statusBar()->addWidget(formulaLabel, 1);

//    connect(spreadsheet, SIGNAL(currentCellChanged(int, int, int, int)),
//            this, SLOT(updateStatusBar()));
//    connect(spreadsheet, SIGNAL(modified()),
//            this, SLOT(spreadsheetModified()));
//    updateStatusBar();
}
/******************************************************************************

  Function: MenuActAbout

  Description:
  ============
  Creates the Menu items

******************************************************************************/
void MainWindow::MenuActAbout()
{
    const QString about_rebarlinx = tr("The <b>Rebarlinx Sofware</b> is for use with "
                                         "the James Instruments Inc.<br>"
                                         "<a href=\"https://www.ndtjames.com/Rebarscope-Complete-System-p/r-c-4.htm\">Rebarscope</a><br>");
    const QString version =  QString::QString("<br> Software Version <<br> <b>%1.%2.%3</b>").arg(VERSION_MAJOR).arg(VERSION_MINOR).arg(VERSION_PATCH);

    QString show = about_rebarlinx + version;

    QMessageBox::about(this, tr("About Rebarlinx Software"), show);



}

/******************************************************************************

  Function: MenuActCopy

  Description:
  ============

******************************************************************************/
void MainWindow::MenuActCopy()
{

}

/******************************************************************************

  Function: MenuActNewFile

  Description:
  ============
  Executes the menu 'new file' actions

******************************************************************************/
void MainWindow::MenuActNewFile()
{

}

/******************************************************************************

  Function: MenuActOpen

  Description:
  ============


******************************************************************************/
void MainWindow::MenuActOpen()
{

}

/******************************************************************************

  Function: MenuActPlot

  Description:
  ============


******************************************************************************/
void MainWindow::MenuActPlot()
{

}

/******************************************************************************

  Function: MenuActSave

  Description:
  ============


******************************************************************************/
void MainWindow::MenuActSave()
{

}

/******************************************************************************

  Function: SerialPortOpen

  Description:
  ============


******************************************************************************/
void MainWindow::SerialPortOpen()
{
/*    SettingsDialog::Settings p = settings->settings();
    serial->setPortName(p.name);
    serial->setBaudRate(p.baudRate);
    serial->setDataBits(p.dataBits);
    serial->setParity(p.parity);
    serial->setStopBits(p.stopBits);
    serial->setFlowControl(p.flowControl);*/
    if (serial->open(QIODevice::ReadWrite)) {
        console->setEnabled(true);
//        console->setLocalEchoEnabled(p.localEchoEnabled);
//        showStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
//                          .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
//                          .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());

//        showStatusMessage(tr("Open error"));
    }
}

/******************************************************************************

  Function: SerialPortClose

  Description:
  ============


******************************************************************************/
void MainWindow::SerialPortClose()
{
    if (serial->isOpen())
        serial->close();
    console->setEnabled(false);
//    showStatusMessage(tr("Disconnected"));
}

/******************************************************************************

  Function: SerialPortReadData

  Description:
  ============


******************************************************************************/
void MainWindow::SerialPortReadData()
{
    QByteArray data = serial->readAll();
    console->putData(data);
}

/******************************************************************************

  Function: SerialPortWriteData

  Description:
  ============


******************************************************************************/
void MainWindow::SerialPortWriteData(const QByteArray &data)
{
    serial->write(data);
}

/******************************************************************************

  Function: handleError

  Description:
  ============


******************************************************************************/
void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        SerialPortClose();
    }
}
/*
void MainWindow::showStatusMessage(const QString &message)
{
    status->setText(message);
}
*/
