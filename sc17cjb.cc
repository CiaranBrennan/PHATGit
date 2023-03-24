#include "globals.h"
#include "gitpp7.h"

#include <QHBoxLayout>
#include <QString>
#include <QLineEdit>
#include <QApplication>
#include <QDesktopWidget>
#include <QPushButton>
#include <QTableWidget>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <QScrollArea>
#include <QRect>
#include <QGridLayout>

namespace{

class HelloWorldLabel : public QWidget{

public:
	HelloWorldLabel() : QWidget(){
		//Create a new layout
		setObjectName("label");
		QHBoxLayout* h=new QHBoxLayout;
		QGridLayout* layout = new QGridLayout(this);

		QString text;
		QLineEdit* searchBox = new QLineEdit();
		QPushButton* button = new QPushButton("Search");
		QScrollArea* scroll = new QScrollArea(this);
		QScrollArea* scrollSearch = new QScrollArea(this);
		QWidget* qhboxSearch = new QWidget();

		QTableWidget* table = new QTableWidget(this);
		table->setObjectName("table");
		table->setRowCount(100);
		table->setColumnCount(4);
		table->setColumnWidth(0, this->width()/4);
		table->setColumnWidth(1, this->width()/4);
		table->setColumnWidth(2, this->width()/2);
		table->setColumnWidth(3, this->width()/1.5);

		table->setEditTriggers(QAbstractItemView::NoEditTriggers);
		table->setSelectionBehavior(QAbstractItemView::SelectRows);
		table->setSelectionMode(QAbstractItemView::SingleSelection);
		// table->setShowGrid(false);
		table->setStyleSheet("QTableView {selection-background-color: red;}");
		table->setGeometry(QApplication::desktop()->screenGeometry());

		QStringList headerNames;
		headerNames <<"Author"<<"Date"<<"Message"<<"Commit Hash";
		table->setHorizontalHeaderLabels(headerNames);

		QObject::connect(button, &QPushButton::clicked,
										[this, searchBox, table]() {
											searchCommits(searchBox->text().toUtf8().constData(), table);
										});
		h->addWidget(searchBox);
		h->addWidget(button);

		qhboxSearch->setLayout(h);

		layout->setGeometry(QRect(QPoint(0, 0),
												QSize(700, 200)));
		layout->addWidget(qhboxSearch);


		scrollSearch->setGeometry(QRect(QPoint(30, 50),
												QSize(600, 50)));
		scrollSearch->setWidget(qhboxSearch);

		scroll->setGeometry(QRect(QPoint(30, 150),
												QSize(1000, 200)));
		scroll->setWidget(table);

	}

	void searchCommits(std::string searchString, QTableWidget* table){
		GITPP::REPO repo;
		std::string message;
		int row = 0;
		int clearTable = 0;
		std::ostringstream commitHash, commitAuth, commitMess, commitDate;
		std::string StrcommitHash, StrcommitAuth, StrcommitDate;
		QString QcommitHash, QcommitAuth, QcommitMess, QcommitDate;

		while (clearTable < 101) {
			table->setItem(clearTable, 0, new QTableWidgetItem(""));
			table->setItem(clearTable, 1, new QTableWidgetItem(""));
			table->setItem(clearTable, 2, new QTableWidgetItem(""));
			table->setItem(clearTable, 3, new QTableWidgetItem(""));
			clearTable++;
		}

		for (GITPP::COMMIT i : repo.commits()) {
			message = i.message();
			if (row == 100) {
				break;
			}
			if (message.find(searchString) != std::string::npos) {
				commitHash << i;
				StrcommitHash = commitHash.str();
				commitHash.str("");
				commitHash.clear();
				QcommitHash = QString::fromStdString(StrcommitHash);
				commitAuth << i.signature().name();
				StrcommitAuth = commitAuth.str();
				commitAuth.clear();
				commitAuth.str("");
				QcommitAuth = QString::fromStdString(StrcommitAuth);
				QcommitMess= QString::fromStdString(message);
				commitDate << i.time();
				StrcommitDate = commitDate.str();
				QcommitDate = QString::fromStdString(StrcommitDate);
				commitDate.clear(); // clears the ostringstream input
				commitDate.str(""); // so that new values are written from sratch

				table->setItem(row, 0, new QTableWidgetItem(QcommitAuth));
				table->setItem(row, 1, new QTableWidgetItem(QcommitDate));
				table->setItem(row, 2, new QTableWidgetItem(QcommitMess));
				table->setItem(row, 3, new QTableWidgetItem(QcommitHash));
				row = row+1;
			}
		}
	}
};

INSTALL_TAB(HelloWorldLabel, "Keyword Search");

}
