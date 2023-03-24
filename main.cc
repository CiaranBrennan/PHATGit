// Window subclassing example - main program
// (NDE, 2016-09-08)

#include "window.h"

#include <QApplication>
#include <iostream>
#include <unistd.h>
#include <QFile>
#include <QTextStream>
#include <QIODevice>

int argc=0;
char* argv[] = {NULL};

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	HelloWindow window;
	window.show();

	QFile file("./stylesheet.qss");
	    file.open(QIODevice::ReadOnly |QIODevice::Text);
	    QTextStream stream(&file);

	    if(!file.exists())
	    {
	        std::cout<< "Problem with finding the file\n";
	    }


	app.setStyleSheet(stream.readAll());
	file.close();
	app.exec();

	// avoid segfault in QtWidget destructors.
	// _exit(0);
}
