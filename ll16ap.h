#include "globals.h"
#include "gitpp7.h"
#include <QLabel>
#include <QObject>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QMessageBox>
#include <iostream>
#include <sstream>      // std::ostringstream
#include <QApplication>

class EditConfig : public QObject {

	Q_OBJECT

public:
	EditConfig() : QObject() {};
	~EditConfig() {};

public slots:
};
