/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>

#include "mainwindow.h"
#include "mytab.h"
//! [0]
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupFileMenu();
    setupHelpMenu();
    setupEditor();

    tab = new MyTab;
    for (int j = 0; j < 3; ++j){
        tab->addTab(vec_editor[j], "tab" + QString::number(j));
    }

    setCentralWidget(tab);
    setWindowTitle(tr("Text Editor"));

//    connect(tab->tabBar(), &QTabBar::tabBarClicked, tab->tabBar(), &QTabBar::tabCloseRequested);
    connect(tab->tabBar(), &QTabBar::tabCloseRequested, tab->tabBar(), &QTabBar::removeTab);
}
//! [0]

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Text Editor"),
                tr("<p>The <b>Text Editor</b> is simple editor" \
                   "with highlighting c++ syntax " \
                   " " \
                   "highlighting rules using regular expressions.</p>"));
}

void MainWindow::newFile()
{
        QString filename = "NewFile.txt";
        QFile file(filename);
        if(!file.open(QIODevice::ReadWrite)) {
            QMessageBox::information(0, "error", file.errorString());
        }
        vec_editor.push_back(new CodeEditor);
        int last_ind = vec_editor.size() - 1;
        highlighter = new Highlighter(vec_editor[last_ind]->document());
        tab->addTab(vec_editor[last_ind], "tab" + QString::number(last_ind));
}

void MainWindow::openFile(const QString &path)
{
    QString fileName = path;

    if (fileName.isNull())
        fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", "C++ Files (*.cpp *.h)");
    vec_editor.push_back(new CodeEditor);
    int last_ind = vec_editor.size() - 1;
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly | QFile::Text))
            vec_editor[last_ind]->setPlainText(file.readAll());
        highlighter = new Highlighter(vec_editor[last_ind]->document());
        tab->addTab(vec_editor[last_ind], "tab" + QString::number(last_ind));
    }
}

//! [1]
void MainWindow::setupEditor()
{
    for (int g = 0; g < 3; ++g){
        qInfo() << "Started loop";
        vec_editor.push_back( new CodeEditor);
        highlighter = new Highlighter(vec_editor[g]->document());
    }
//    QVBoxLayout *layout = new QVBoxLayout;


    QFile file("mainwindow.h");
    if (file.open(QFile::ReadOnly | QFile::Text))
        for (int g = 0; g < 3; ++g)
        vec_editor[g]->setPlainText(file.readAll());




}

void MainWindow::SaveFile(){
    int index = tab->currentIndex();
    QString str = vec_editor[index]->toPlainText();
    QFile file(tab->tabText(index));
//    qInfo() << "title is " << tab->tabText(index);

    if(!file.open(QIODevice::ReadWrite)) {
        QMessageBox::information(0, "error", file.errorString());
    }
    QTextStream stream(&file);
            stream << str;
}

void MainWindow::SaveFileAs(){
    int index = tab->currentIndex();
    QString str = vec_editor[index]->toPlainText();

    qInfo() << "SaveFileAs STARTED" << Qt::endl;
    QString fileName = QFileDialog::getSaveFileName(this);
    QFile file(fileName);
     if(!file.open(QIODevice::ReadWrite)) {
         QMessageBox::information(0, "error", file.errorString());
     }
    QTextStream stream(&file);
            stream << str;
}

void MainWindow::setupFileMenu()
{
    QMenu *fileMenu = new QMenu(tr("&File"), this);
    menuBar()->addMenu(fileMenu);

    fileMenu->addAction(tr("&New"), this, SLOT(newFile()), QKeySequence::New);
    fileMenu->addAction(tr("&Open..."), this, SLOT(openFile()), QKeySequence::Open);
    fileMenu->addAction(tr("&Save"), this, SLOT(SaveFile()), QKeySequence::Save);
    fileMenu->addAction(tr("&SaveAs"), this, SLOT(SaveFileAs()), QKeySequence::SaveAs);
    fileMenu->addAction(tr("E&xit"), qApp, SLOT(quit()), QKeySequence::Quit);
}

void MainWindow::setupHelpMenu()
{
    QMenu *helpMenu = new QMenu(tr("&Help"), this);
    menuBar()->addMenu(helpMenu);

    helpMenu->addAction(tr("&About"), this, SLOT(about()));
    helpMenu->addAction(tr("About &Qt"), qApp, SLOT(aboutQt()));
}

