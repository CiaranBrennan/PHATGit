#include "globals.h"
#include "gitpp7.h"
// sc17dd
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

namespace{

class WelcomeLabel : public QLabel{
public:
	WelcomeLabel() : QLabel(){

		setObjectName("welcomepage");
		setText("Welcome to PHATgit");
		QFont font;
		font.setPointSize(48);
		font.setBold(true);
		font.setWeight(75);
		setFont(font);


	}
};

class RepositoryStatusLabel : public QLabel{
public:
	RepositoryStatusLabel() : QLabel(){

		QFont font;
		setObjectName("label");
		font.setPointSize(16);
		font.setWeight(75);
		setFont(font);
		try
		{ // try to open repository in working directory
			GITPP::REPO repo;
			setText("Repository found in the working directory. You are all set-up!");
		}
		catch(const GITPP::EXCEPTION_CANT_FIND e)
		{ // if the repository is not found, then open the initialization menu
			QPushButton create_repo;
			setText("Repository not found in the working directory.");
			// Create the button, make "this" the parent
			QPushButton *m_button;
			m_button = new QPushButton("Create Repository", this);
			// set size and location of the button
			m_button->setGeometry(QRect(QPoint(100, 100),

			QSize(200, 50)));

			// return git_init_ui.exec();
		}

	}
};

class WelcomeTabWidget : public QWidget{
public:
	WelcomeTabWidget() : QWidget(){
		QVBoxLayout* vertical_element=new QVBoxLayout;

		setObjectName("label");
		vertical_element->addWidget(new WelcomeLabel());
		vertical_element->addWidget(new RepositoryStatusLabel());
		setLayout(vertical_element);

	}
};


//
// };
//


INSTALL_TAB(WelcomeTabWidget,  "");

}
