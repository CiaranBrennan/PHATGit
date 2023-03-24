/*                                 *
 * 25/11/2018 version 0.01 ALPHA   *
 *                                 *
 *  Jonathan Alderson              */

#include <QtWidgets>




class Ui_TabWidget
{
public:
    QWidget* welcome_tab;
    QWidget* branch_navigation_tab;
    QWidget* display_commits_tab;
    QWidget* show_edit_settings_tab;
    QWidget* statistics_tab;
    QWidget* keyword_search_tab;
    QLabel* label;

    void setupUi(QTabWidget* TabWidget)
    {

        if (TabWidget->objectName().isEmpty())
        { TabWidget->setObjectName(QStringLiteral("TabWidget")); }

        TabWidget->resize(780, 680); // resize the window
        // The following block adds all menu buttons:
        // welcome_tab ( the logo ):
            // create QWidget object
            welcome_tab = new QWidget();
            // set the object's name (if we want to use QObject.find() later)
            welcome_tab->setObjectName(QStringLiteral("welcome_tab"));
            // add some welcoming and loving text:
            label = new QLabel(welcome_tab);
            label->setObjectName(QString("label"));
            label->setGeometry(QRect(170, 40, 600, 201));
            QFont font;
            font.setPointSize(48);
            font.setBold(true);
            font.setWeight(75);
            label->setFont(font);
            // the text itself is added down there in the void fillOutWidget(QTabWidget *TabWidget)
        // adds the created tab to our TabWidget and its object name
        TabWidget->addTab(welcome_tab, QString());
        // the next lines follow the same pattern...
            branch_navigation_tab = new QWidget();
            branch_navigation_tab->setObjectName(QStringLiteral("branch_navigation_tab"));
        TabWidget->addTab(branch_navigation_tab, QString());
        // display_commits_tab:
            display_commits_tab = new QWidget();
            display_commits_tab->setObjectName(QStringLiteral("display_commits_tab"));
        TabWidget->addTab(display_commits_tab, QString());
        // show_edit_settings_tab:
            show_edit_settings_tab = new QWidget();
            show_edit_settings_tab->setObjectName(QStringLiteral("show_edit_settings_tab"));
        TabWidget->addTab(show_edit_settings_tab, QString());
        // statistics_tab:
            statistics_tab = new QWidget();
            statistics_tab->setObjectName(QStringLiteral("statistics_tab"));
        TabWidget->addTab(statistics_tab, QString());
        // keyword_search_tab:
            keyword_search_tab = new QWidget();
            keyword_search_tab->setObjectName(QStringLiteral("keyword_search_tab"));
        TabWidget->addTab(keyword_search_tab, QString());

        fillOutWidget(TabWidget); // set widget tab titles (function defined below)

        TabWidget->setCurrentIndex(0); // set which tab is dislpayed at launch (0 = first)
        // allowing the objects to comminicate when their state is changed (like callbacks):
        QMetaObject::connectSlotsByName(TabWidget);

    } // END OF void setupUi(QTabWidget *TabWidget)

    // set button titles, pictures, label texts, fills in the wireframe model provided by setupUi:
    void fillOutWidget(QTabWidget *TabWidget)
    {
        // change displayed name of application:
           TabWidget->setWindowTitle(QApplication::translate("TabWidget", "PHATgit", 0));

        // set the picture of welcome tab to be the logo:
           //QString welcome_tab="QTabBar::tab:first { height: 65px; width: 60px;border-image: url(PHATgit.png);}";
           label->setText(QApplication::translate("TabWidget", "WELCOME TO\n    PHATgit\n     ( ͡° ͜ʖ ͡°)", 0));
           //TabWidget->setStyleSheet(welcome_tab);

        // set descriptive text of each tab:
          TabWidget->setTabText(TabWidget->indexOf(welcome_tab),
             QApplication::translate("TabWidget", "Home", 0));

           TabWidget->setTabText(TabWidget->indexOf(branch_navigation_tab),
              QApplication::translate("TabWidget", "Branch Navigation", 0));

           TabWidget->setTabText(TabWidget->indexOf(display_commits_tab),
              QApplication::translate("TabWidget", "Display Commits", 0));

           TabWidget->setTabText(TabWidget->indexOf(show_edit_settings_tab),
              QApplication::translate("TabWidget", "Show/Edit Settings", 0));

           TabWidget->setTabText(TabWidget->indexOf(statistics_tab),
              QApplication::translate("TabWidget", "Statistics", 0));

           TabWidget->setTabText(TabWidget->indexOf(keyword_search_tab),
              QApplication::translate("TabWidget", "Keyword Search", 0));

    } // END OF void fillOutWidget(QTabWidget *TabWidget)

};

namespace Ui {
    class TabWidget: public Ui_TabWidget {};
} // END OF namespace Ui


int main(int argc, char* argv[])
{
  using namespace Ui; // using the namespace above to have access to TabWidget

  QApplication app(argc, argv); // define the application


  // This is the big that I have done
  QString mainStyleSheet= "QWidget { background-color: black; }";
  QFile File("stylesheet.qss");
  File.open(QFile::ReadOnly);
  QString StyleSheet = QLatin1String(File.readAll());
  qApp->setStyleSheet(StyleSheet);
  // this bit

  QTabWidget* widget = new QTabWidget(); // QTabWidget object (from QT library)
  TabWidget* layout =  new TabWidget(); // create new empty TabWidget (defined above)

  layout->setupUi(widget); // adds buttons to the QTabWidget (function setupUi in class Ui_TabWidget)

  widget->show();
  return app.exec(); // launches the application
} // END OF main
