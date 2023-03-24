
#include "tabs.h"
#include "globals.h"

#include <QTabWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <iostream>


TabDialog::TabDialog(QWidget *parent)
    : QDialog(parent)
{

    _tabWidget = new QTabWidget;

	 // addTab passes ownership
	 for(WidgetDispatcher::const_iterator i=myTabs.begin(); i!=myTabs.end(); ++i){
		 _tabWidget->addTab(i->second->clone_instance(), tr(i->first.c_str()));
	 }

	 QVBoxLayout *mainLayout = new QVBoxLayout;
   mainLayout->addWidget(_tabWidget);
   QString welcome_tab="QTabBar::tab:first { height: 65px; width: 60px;border-image: url(PHATgit.png); }";
   _tabWidget->setStyleSheet(welcome_tab);
   _tabWidget->setCurrentIndex(0); // sets whih tab is opened first


	 // transfers ownership
    setLayout(mainLayout);
}
