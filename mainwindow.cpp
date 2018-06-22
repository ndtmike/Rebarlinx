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
    SerialConsole = new Console;
    SerialConsole->setEnabled(false);
    setCentralWidget(SerialConsole);
    Serial = new QSerialPort(this);
    Plot = new QwtPlot;

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

    connect(Serial, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &MainWindow::SerialPortHandleError);
    connect(Serial, &QSerialPort::readyRead, this, &MainWindow::SerialPortReadData);
    connect(SerialConsole, &Console::getData, this, &MainWindow::SerialPortWriteData);
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
    Status = new QLabel(" Not Connected ");
    Status->setAlignment(Qt::AlignHCenter);
    Status->setMinimumSize(Status->sizeHint());
    statusBar()->addWidget(Status);
}
/******************************************************************************

  Function: MenuActAbout

  Description:
  ============
  Creates the Menu items

******************************************************************************/
void MainWindow::MenuActAbout()
{
    const QString about_rebarlinx = tr("The <b>Rebarlinx Sofware</b> is for use with <br>"
                                       "the James Instruments Inc.<br>"
                                       "<a href=\"https://www.ndtjames.com/Rebarscope-Complete-System-p/r-c-4.htm\">Rebarscope</a><br>"
                                       "USA: +1773.4636565<br>"
                                       "Europe: +31.548.659032<br>"
                                       "Email: <a href=\"mailto:info@ndtjames.com?Subject=Rebarlinx\" target=\"_top\">info@ndtjames.com</a><br>"
                                       "Copyright 2017<br>");
    const QString version =  QString::QString("<br> Software Version <<br> <b>%1.%2.%3</b>").arg(VERSION_MAJOR).arg(VERSION_MINOR).arg(VERSION_PATCH);
    QString show = about_rebarlinx + version;
    QMessageBox::about(this, tr("About Rebarlinx Software"), show);
    ShowStatusMessage( "About Rebarlinx" );
}

/******************************************************************************

  Function: MenuActCopy

  Description:
  ============

******************************************************************************/
void MainWindow::MenuActCopy()
{
    ShowStatusMessage( "Copy Data" );
}

/******************************************************************************

  Function: MenuActNewFile

  Description:
  ============
  Executes the menu 'new file' actions

******************************************************************************/
void MainWindow::MenuActNewFile()
{
    ShowStatusMessage( "New File" );
}

/******************************************************************************

  Function: MenuActOpen

  Description:
  ============


******************************************************************************/
void MainWindow::MenuActOpen()
{
    ShowStatusMessage( "Open File" );
}

/******************************************************************************

  Function: MenuActPlot

  Description:
  ============


******************************************************************************/
void MainWindow::MenuActPlot()
{
    Plot->setTitle( "Plot Demo" );
    Plot->setCanvasBackground( Qt::white );

    Plot->insertLegend( new QwtLegend() );

    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->attach( Plot );

    QwtPlotCurve *curve = new QwtPlotCurve();
    curve->setTitle( "Some Points" );
    curve->setPen( Qt::blue, 4 ),
    curve->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Ellipse,
        QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
    curve->setSymbol( symbol );

    QPolygonF points;
    points << QPointF( 0.0, 4.4 ) << QPointF( 1.0, 3.3 )
        << QPointF( 2.0, 4.5 ) << QPointF( 3.0, 6.8 )
        << QPointF( 4.0, 7.9 ) << QPointF( 5.0, 7.1 );
    curve->setSamples( points );

    curve->attach( Plot );

    Plot->replot();

    Plot->resize(600, 400);
    Plot->show();

    ShowStatusMessage( "Plot" );
}

/******************************************************************************

  Function: MenuActSave

  Description:
  ============


******************************************************************************/
void MainWindow::MenuActSave()
{
    ShowStatusMessage( "Save" );
}

/******************************************************************************

  Function: SerialCheckPort()

  Description:
  ============
  Checks that an instrument is connected to the PC

******************************************************************************/
void MainWindow::SerialCheckPort()
{
    QString description;
    QString manufacturer;
    QString portname;

    const QString portmanufacturer = "FTDI";
    const QString noport = tr("No Available Ports") + '\n'
                              + tr("Check instrument is plugged in") + '\n'
                              + tr("or serial port installed properly") + '\n'
                              + tr("then restart Rebarlinx");
    const QString messageTitle = tr("Check Serial Port");
    const QString connected = tr("Connected to ");
    QList <QSerialPortInfo> availablePorts;
    bool r = false;
    availablePorts = QSerialPortInfo::availablePorts();

    if(!availablePorts.isEmpty()){
        foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        {
            portname = info.portName();
            description = info.description();
            manufacturer = info.manufacturer();
            if(manufacturer == portmanufacturer){
                Serial->setPortName(portname);
                r = true;
            }
        if( r == true ) break;
        }
    }
    if(r == false){
        QMessageBox::information(this,messageTitle,noport);
    }else{
        QMessageBox::information(this ,messageTitle , connected + portname );
        ShowStatusMessage( "Serial Port Found" );
        SerialPortOpen(); // Found the instrument open the port
    }
}

/******************************************************************************

  Function: SerialPortOpen

  Description:
  ============


******************************************************************************/
void MainWindow::SerialPortOpen()
{
    Serial->setBaudRate(9600);
    Serial->setDataBits(QSerialPort::Data8);
    Serial->setParity(QSerialPort::NoParity);
    Serial->setStopBits(QSerialPort::OneStop);
    Serial->setFlowControl(QSerialPort::NoFlowControl);
    if (Serial->open(QIODevice::ReadWrite)) {
        SerialConsole->setEnabled(true);
        SerialConsole->setLocalEchoEnabled(true);
        ShowStatusMessage(tr("Connected"));
    } else {
        QMessageBox::critical(this, tr("Error"), Serial->errorString());

        ShowStatusMessage(tr("Open error"));
    }
}

/******************************************************************************

  Function: SerialPortClose

  Description:
  ============


******************************************************************************/
void MainWindow::SerialPortClose()
{
    if (Serial->isOpen())
        Serial->close();
    SerialConsole->setEnabled(false);

    ShowStatusMessage(tr("Serial Port Closed"));
}

/******************************************************************************

  Function: SerialPortReadData

  Description:
  ============


******************************************************************************/
void MainWindow::SerialPortReadData()
{
    QByteArray data = Serial->readAll();
    SerialConsole->putData(data);
}

/******************************************************************************

  Function: SerialPortWriteData

  Description:
  ============


******************************************************************************/
void MainWindow::SerialPortWriteData(const QByteArray &data)
{
    Serial->write(data);
}

/******************************************************************************

  Function: handleError

  Description:
  ============


******************************************************************************/
void MainWindow::SerialPortHandleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), Serial->errorString());
        SerialPortClose();
    }
}

/******************************************************************************

  Function: ShowStatusMessage

  Description:
  ============


******************************************************************************/
void MainWindow::ShowStatusMessage(QString message)
{
    Status->setText( message );
}
