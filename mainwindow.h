/****************************************************************************
**
** This software is furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** File Name: mainwindow.h
**
** mainwindow.cpp Rebarlinx software
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore/QtGlobal>
#include <QtSerialPort/QSerialPort>
#include <QSerialPortInfo>
#include <QtWidgets>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QDialog;
class QLabel;
class QMenu;
class QSerialPort;
class QSerialPortInfo;
QT_END_NAMESPACE

class Console;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void MenuActAbout();
    void MenuActCopy();
    void MenuActNewFile();
    void MenuActOpen();
    void MenuActPlot();
    void MenuActSave();

    void SerialPortClose();
    void SerialPortHandleError(QSerialPort::SerialPortError error);
    void SerialPortOpen();
    void SerialPortReadData();
    void SerialPortWriteData(const QByteArray &data);

private:
    QByteArray Data;

    struct SerialSettings {
        QString name;
        qint32 baudRate;
        QString stringBaudRate;
        QSerialPort::DataBits dataBits;
        QString stringDataBits;
        QSerialPort::Parity parity;
        QString stringParity;
        QSerialPort::StopBits stopBits;
        QString stringStopBits;
        QSerialPort::FlowControl flowControl;
        QString stringFlowControl;
        bool localEchoEnabled;
    };

    void CreateActions();
    void CreateMenus();
    void CreateStatusBar();

    SerialSettings CurrentSerialSettings;

    void SerialCheckPort();
    void ShowStatusMessage( QString message );

    QMenu *FileMenu;
    QMenu *EditMenu;
    QMenu *GraphMenu;
    QMenu *helpMenu;

    QAction *aboutAct;
    QAction *aboutQtAct;
    QAction *copyAct;
    QAction *exitAct;

    QAction *newAct;
    QAction *openAct;
    QAction *PlotAct;
    QAction *saveAct;

    QwtPlot *Plot;
    QSerialPort *Serial;
    Console *SerialConsole;
    QLabel *Status;
};

#endif // MAINWINDOW_H
