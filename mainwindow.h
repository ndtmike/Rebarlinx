/* ---------------------------------------------------------------------------
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
** 3/23/18 Initial Creation
** -------------------------------------------------------------------------*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:
    void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;

private slots:
    void aboutQt();
    void MenuActAbout();
    void MenuActCopy();
    void MenuActNewFile();
    void MenuActOpen();
    void MenuActPlot();
    void MenuActSave();

private:
    void createActions();
    void createMenus();

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

    QLabel *infoLabel;
};

#endif
