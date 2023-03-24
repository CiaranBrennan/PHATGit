// Window subclassing example - class implementation
// (NDE, 2016-09-08)

#include "window.h"
#include "tabs.h"

//#include <QtWidgets> // qt5 only?
#include <QHBoxLayout>
#include <QStatusBar>
#include <QMenuBar>
#include <QApplication>
#include <QScrollArea>
#include <QFile>



 // File.open(QFile::ReadOnly);
 // QString StyleSheet = QLatin1String(File.readAll());


HelloWindow::HelloWindow()
{
	createWindowContent();
	createMenuAndStatusBar();
}


void HelloWindow::createWindowContent()
{
	// Create layout

	TabDialog* tabs=new TabDialog();

	QHBoxLayout* layout=new QHBoxLayout();
	 QFile File("stylesheet.qss");
// layout->addStretch();

	// transfer ownership?
	layout->addWidget(tabs);
// layout->addStretch(1);

	// Put layout in the middle of the window



	_mainWidget = new QWidget();
	_mainWidget->setLayout(layout);
	// _mainWidget->setStyleSheet(stylesheet);
	// _mainWidget->setStyleSheet("QWidget {background-color: #A9FDAC;}");

	setCentralWidget(_mainWidget);
}


void HelloWindow::createMenuAndStatusBar()
{
	statusBar()->showMessage("This is the status bar");

	QMenu* fileMenu = menuBar()->addMenu("&File");

	QAction* open = fileMenu->addAction("&Open");
	open->setShortcuts(QKeySequence::Open);
	open->setStatusTip("Open an existing file");

	QAction* quit = fileMenu->addAction("Quit");
	quit->setShortcuts(QKeySequence::Quit);
	quit->setStatusTip("Quit the application");

	connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));
}
