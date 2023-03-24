
#include "globals.h"
#include "gitpp7.h"

#include <QLabel>
#include <QHBoxLayout>
#include <iostream>
#include <sstream>      // std::ostringstream

#include <QTableWidget> // for the table layout
#include <QDesktopWidget>
#include <QApplication>
#include <QScrollArea> // will have a scrollable table

namespace{


class HelloWorldLabel : public QWidget{
public:
	HelloWorldLabel() : QWidget(){
		setObjectName("label");
		GITPP::REPO repo; // open current directory repository

		// ------------- variables for parsing data branch data: ------------
		std::ostringstream commits_stream_code;
		std::ostringstream commits_stream_name;
		std::ostringstream commits_stream_message;
		std::ostringstream commits_stream_date;

		std::string branches;
		std::string commits_code;
		std::string commits_name;
		std::string commits_message;
		std::string commits_date;
		std::string commits;
		// ------------------------------------------------------------------

		// ----------------------------- QT variables:
		QVBoxLayout* vertical_element=new QVBoxLayout;
		QTableWidget* table;
		QStringList m_TableHeader;
		QScrollArea* scroll = new QScrollArea(this);
		// ------------------------------------------

		int number_of_commits = 0;

		for(auto i : repo.commits())
		{ // get the number of commits (how many rows are needed)
			number_of_commits++;
			(void)i; // get rid of the unused variable warning
		}
		table = new QTableWidget(this);
		table->setObjectName("table");
		table->setRowCount(number_of_commits);
		table->setColumnCount(4);
		m_TableHeader<<"Author"<<"Date"<<"Message"<<"Commit Hash";
		table->setHorizontalHeaderLabels(m_TableHeader);
		// set the widths
		table->setColumnWidth(0, this->width()/4);
		table->setColumnWidth(1, this->width()/4);
		table->setColumnWidth(2, this->width()/1.6);
		table->setColumnWidth(3, this->width()/1.5);
// comment
		table->setEditTriggers(QAbstractItemView::NoEditTriggers);
		table->setSelectionBehavior(QAbstractItemView::SelectRows);
		table->setSelectionMode(QAbstractItemView::SingleSelection);
		table->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
		// entry is red onclick
		table->setStyleSheet("QTableView {selection-background-color: red;}");
		table->setGeometry(QApplication::desktop()->screenGeometry());

		int iterator = 0;
		// for each commit:
		for(GITPP::COMMIT i : repo.commits())
		{
			// stream variables to ostringstream variables 
			commits_stream_code << i;
			commits_stream_name << i.signature().name();
			commits_stream_message << i.message();
			commits_stream_date << i.time();

			// converting ostringstream to string and then to Qstring for the table
			// because table takes QString variables as item parameters
			commits_code = commits_stream_code.str();
			QString qstring_commits_stream_code = QString::fromStdString(commits_code);
			commits_name = commits_stream_name.str();
			QString qstring_commits_name = QString::fromStdString(commits_name);
			commits_message = commits_stream_message.str();
			QString qstring_commits_message = QString::fromStdString(commits_message);
			commits_date = commits_stream_date.str();
			QString qstring_commits_date = QString::fromStdString(commits_date);

			// set tables entries
			table->setItem(iterator, 0, new QTableWidgetItem(qstring_commits_name));
			table->setItem(iterator, 1, new QTableWidgetItem(qstring_commits_date));
			table->setItem(iterator, 2, new QTableWidgetItem(qstring_commits_message));
			table->setItem(iterator, 3, new QTableWidgetItem(qstring_commits_stream_code));

			// clear ostringstream variables so that new ones can be written to them
			// (equivalent of initializing a variable to NULL or 0)
			commits_stream_code.str("");
			commits_stream_code.clear();
			commits_stream_name.str("");
			commits_stream_name.clear();
			commits_stream_date.str("");
			commits_stream_date.clear();
			commits_stream_message.str("");
			commits_stream_message.clear();

			iterator++; // increment row iterator
		}

		scroll->setGeometry(QRect(QPoint(30, 15),
		QSize(1000, 350))); // set the size of the scroll widget (with table inside)
		scroll->setWidget(table); // put the table inside a scroll widget
		setLayout(vertical_element);

	}
};


INSTALL_TAB(HelloWorldLabel, "Display Commits");

}
