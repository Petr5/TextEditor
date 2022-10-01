#include "mytab.h"
#include "codeeditor.h"
#include <QVBoxLayout>
#include <QLabel>
MyTab::MyTab(QTabWidget *parent)
    : QTabWidget(parent)
{

    QVBoxLayout *mainLayout = new QVBoxLayout;
    CodeEditor* editor = new CodeEditor;
    QLabel *pathLabel = new QLabel(tr("Path:"));
    mainLayout->addWidget(editor);
    mainLayout->addWidget(pathLabel);
    setTabsClosable(true);
//    connect(this->tabBar(), &QTabBar::tabCloseRequested, tabWidget->tabBar(), &QTabBar::removeTab);
}
