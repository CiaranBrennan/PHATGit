#include "globals.h"
#include "gitpp7.h"
#include "ll16ap.h"
#include <QLabel>
#include <QObject>
#include <QSignalMapper>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QMessageBox>
#include <iostream>
#include <sstream>      // std::ostringstream
#include <QApplication>


namespace{

class HelloWorldLabel : public QWidget{
public:

	HelloWorldLabel() : QWidget(){
		// connect to repo in current directory
		GITPP::REPO repo;

		setObjectName("label");

		std::ostringstream name_stream;
		std::ostringstream email_stream;

		std::string name;
		std::string email;


		name_stream << repo.config()["user.name"];
		email_stream << repo.config()["user.email"];
		// edit string to only show needed values
		name = name_stream.str();
		name = name.erase(0, 12);
		email = email_stream.str();
		email = email.erase(0, 13);
		QString qstring_name = QString::fromStdString(name);
		QString qstring_email = QString::fromStdString(email);


		// set up text boxes on page
		QLabel *nameLabel = new QLabel(tr("Current name:"));
		QLabel *nameLabelString = new QLabel(qstring_name);
		QLabel *nameEditLabel = new QLabel(tr("New name:    "));

		QLabel *emailLabel = new QLabel(tr("Current email:"));
		QLabel *emailLabelString = new QLabel(qstring_email);
		QLabel *emailEditLabel = new QLabel(tr("New email:    "));
		// user input
		QLineEdit *nameEditInput = new QLineEdit();
		QLineEdit *emailEditInput = new QLineEdit();
		// button creation
		QPushButton *nameButton = new QPushButton("save name",this);
		QPushButton *emailButton = new QPushButton("save email",this);

		// connect buttons to functions using lamda, uses input from user to
		// update the config file

		QObject::connect(nameButton, &QPushButton::clicked, [this, nameEditInput](){
																																									setName(nameEditInput->text().toUtf8().constData());
																																								});
		// connect button click to the dialog pop up
		QObject::connect(nameButton, &QPushButton::clicked, [this](){
																																	showMessage();
																																});

		QObject::connect(emailButton, &QPushButton::clicked, [this, emailEditInput](){
																																									setEmail(emailEditInput->text().toUtf8().constData());
																																								});
		QObject::connect(emailButton, &QPushButton::clicked, [this](){
																																	showMessage();
																																});

		// populate page with fields

		QGridLayout* editConfigTab = new QGridLayout;
		editConfigTab->addWidget(nameLabel, 0, 0, 1, 1);
		editConfigTab->addWidget(nameLabelString, 0, 1, 1, 1);
		editConfigTab->addWidget(nameEditLabel, 1, 0, 1, 1);
		editConfigTab->addWidget(nameEditInput, 1, 1, 1, 2);
		editConfigTab->addWidget(nameButton, 1, 4, 1, 1);

		editConfigTab->addWidget(emailLabel, 2, 0, 1, 1);
		editConfigTab->addWidget(emailLabelString, 2, 1, 1, 1);
		editConfigTab->addWidget(emailEditLabel, 3, 0, 1, 1);
		editConfigTab->addWidget(emailEditInput, 3, 1, 1, 2);
		editConfigTab->addWidget(emailButton, 3, 4, 1, 1);


		setLayout(editConfigTab);

	}
	// update the user.name in the git config file
	void setName(std::string name){
		GITPP::REPO repo;
		repo.config()["user.name"] = name;

	}
	// update the user.email in the git config file

	void setEmail(std::string email){
		GITPP::REPO repo;
		repo.config()["user.email"] = email;
	}
    // display pop up dialog to the user
	void showMessage(){
		QMessageBox *message = new QMessageBox();
		message->setText("Config updated\nChanges will be shown next time the program is loaded");
		message->exec();
	}



};

INSTALL_TAB(HelloWorldLabel, "Edit Config");

}
