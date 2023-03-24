add qt to the current folder:
1. open the folder where layout.cc is
2. in terminal enter 'module add qt/5.3.1'

if any changes to the project are made
(added new header .h or c++ .cc files )
1. in terminal enter 'qmake -project'  // generates phatgit.pro
2. in terminal enter 'qmake phatgit.pro'  // generates the Makefile

Use of application:
The application  is designed for the user to
explore a Git repository, providing a way to
change the branch, see all commits, search
commits by keyword, look up statitics and 
configure user settings.

==========================================
compile by typing 'make' in the terminal
run with ./phatgit
==========================================
