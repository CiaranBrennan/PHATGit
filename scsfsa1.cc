#include "globals.h"

#include <QLabel>
#include <QHBoxLayout>

namespace{

class HelloWorldLabel : public QWidget{
public:
	HelloWorldLabel() : QWidget(){
		QVBoxLayout* editConfigTab = new QVBoxLayout;

		QLabel *nameLabel = new QLabel(tr("name:"));
		QLabel *nameLabelEdit = new QLabel(tr("name info"));
		nameLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
		// nameLabel->setFrameWidth(2);

		QLabel *emailLabel = new QLabel(tr("email:"));
		QLabel *emailLabelEdit = new QLabel(tr("email info"));
		emailLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);


		editConfigTab->addWidget(nameLabel);
		editConfigTab->addWidget(nameLabelEdit);
		editConfigTab->addWidget(emailLabel);
		editConfigTab->addWidget(emailLabelEdit);
		setLayout(editConfigTab);

	}
};

// INSTALL_TAB(HelloWorldLabel, __FILE__);

}
