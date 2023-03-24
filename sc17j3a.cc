#include "globals.h"
#include <string>
#include <QLabel>
#include <set>
#include <QHBoxLayout>
#include <time.h>
#include "gitpp7.h"
#include <stdio.h>  /* defines FILENAME_MAX */
#include <unistd.h>
#define GetCurrentDir getcwd
#include<iostream>

namespace{

class HelloWorldLabel : public QWidget{
public:
	HelloWorldLabel() : QWidget(){

		// make a grid layout
		QGridLayout *h=new QGridLayout;
		setObjectName("label");


		// Make all the labels
		QLabel *repositoryNameLabel =  new QLabel(tr("repository name:    "));
		QLabel *repositoryAgeLabel =   new QLabel(tr("repository age:     "));
		QLabel *firstCommitLabel =     new QLabel(tr("first commit:       "));
		QLabel *numberOfCommitsLabel = new QLabel(tr("number of commits:  "));
		QLabel *numberOfAuthorsLabel = new QLabel(tr("number of authors:   "));
		QLabel *directoryNameLabel =   new QLabel(tr("current working directory:  "));


		// intial varialbes for all the statistics
		int numberOfCommits = 0;
		int numberOfAuthors = 0;
		int repoAgeInDays = 0;
		GITPP::REPO repo;
		std::string repoName;
		std::string firstCommitDate;
		time_t currentTime = time(&currentTime);
		time_t firstCommitTime;
		std::string currentAuthor = "";
		std::set<std::string> allAuthors;


		// go through every commit to gather stats
		for(auto i: repo.commits())
		{
			// find the number of unique authors
			currentAuthor = i.author();
			if(allAuthors.find(currentAuthor) == allAuthors.end())
			{
				allAuthors.insert(currentAuthor);
			}

			// find the time of each commit
			firstCommitDate = i.time();
			firstCommitTime = i.time_seconds();

			// find the total number of commits
			numberOfCommits ++;
		}

		// find the number of authors
		numberOfAuthors = allAuthors.size();

		// compare the seconds to find the number of days
		repoAgeInDays = ((currentTime - firstCommitTime)/(60*60*24));

		// finding the name of the CWD
		char buff[FILENAME_MAX];
  	GetCurrentDir( buff, FILENAME_MAX );
  	std::string current_working_dir(buff);


		// finding just the name of the repo
		auto c = repo.config();
		repoName = c["remote.origin.url"].value();

		// add all the values to the qlabels
		QLabel *repositoryNameValue =  new QLabel(repoName.c_str());
		QLabel *repositoryAgeValue =   new QLabel(tr(std::to_string(repoAgeInDays).c_str()) + " days");
		QLabel *firstCommitValue =     new QLabel(tr(firstCommitDate.c_str()));
		QLabel *numberOfCommitsValue = new QLabel(tr(std::to_string(numberOfCommits).c_str()));
		QLabel *numberOfAuthorsValue = new QLabel(tr(std::to_string(numberOfAuthors).c_str()));
		QLabel *directoryNameValue =   new QLabel(tr(current_working_dir.c_str()));

		// add all the widgets to the page
		h->addWidget(repositoryNameLabel,0,0);
		h->addWidget(repositoryAgeLabel,1,0);
		h->addWidget(firstCommitLabel,2,0);
		h->addWidget(numberOfCommitsLabel,3,0);
		h->addWidget(numberOfAuthorsLabel,4,0);
		h->addWidget(directoryNameLabel,5,0);

		h->addWidget(repositoryNameValue,0,1);
		h->addWidget(repositoryAgeValue,1,1);
		h->addWidget(firstCommitValue,2,1);
		h->addWidget(numberOfCommitsValue,3,1);
		h->addWidget(numberOfAuthorsValue,4,1);
		h->addWidget(directoryNameValue,5,1);


		// set the layout
		setLayout(h);


	}
};

// activate the tab with the correct title
INSTALL_TAB(HelloWorldLabel, "Statistics");

}
