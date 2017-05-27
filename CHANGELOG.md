27.05.2017 (0.8.1)
* Updated: Version number to be cleanly readed
* Updated: Now translation properly loading on fly
* Updated: Finished French translation
* Updated: code cleanup
* Deleted: Double adding operation hax fix

21.05.2017 (0.8.0.1)
* Code style formatting
* Added: Initial commit for french translation

15 January 2017 (0.7.0.9)

* Fixed: Not correct work of clean database function
* Fixed: Expense command line option now works properly
* Added: Clean Database command line option
* Added: Command line option to get all commandline operations

14 January 2017 (0.7.0.8)

* Added: Key shoercuts for add profit and expence operations
* Added: Console control for testing purpurses

12 January 2017 (0.7.0.7)

* Code Cleanup
* Fixed: small buggs
* Added: Tooltips for main window

11 January 2017 (0.7.0.6)

* Fixed: Settings being not correctly saved in some cases
* Updated: Translations

9 January 2017 (0.7.0.5)

* Fixed: Lockfile being not deleted on exit
* Fixed: Infinite loop of messages in log on settings dialog close
* Added: "Select Folder" button for export file dialog

5 January 2017 (0.7.0.4)
* Fixed: Freezes on valid exit

4 January 2017 (0.7.0.3)

* Added: Select File Button For Import file
* Changed: Now default foulder is "User Documents/ssbm"
* Fixed: Settings select folder button. Now it properly implemented

30 October 2016 (0.7.0.0)

* Fixed: now clearing database not saves old data and really clear database file

1 October 2016 (0.6.1.9)

* Added: Basic console control for autotest using
* Added: Help option
* Added: version information option
* Added: Console output in console mode
9 August 2016 (0.6.1.8)

* Added: Import to database from CSV file
* Fixed: Minor Issues

7 August 2016 (0.6.1.7)

* Added: Export database to CSV File

5 August 2016 (0.6.1.6)

* Fixed: Database was not cleaned after click 'clean' from settings form
* Updated: Readme.md file

5 August 2016 (0.6.1.5)

* Fixed: Lock file deleting on application exit
* Updated: Readme.md file

5 August 2016 (0.6.1.4)

* CleanUp: Simplifying code


5 August 2016 (0.6.1.3)

* Fixed: lock Mechanism to prevent multiple launches

5 August 2016 (0.6.1.2)

* Added: Message to Settings menu to actually notify user that he should restart app after language change

29 June 2016 (0.6.1.1)

* Updated: Translations

24 June 2016 (0.6.1.1)

* Changed: Design to be more material Designy
* Changed: method to submit operations


21 april 2016 (0.6)

* Updated: Translations

08 april 2016 (0.5.8)
* Added: something
* Added: Travis Autobuild settings

07 april 2016 (0.5.7)
* Fixed: Now programm will not run if another instance of programm is already running 

05 april 2016 (0.5.6)

* Fixed: Incorrect checkings for edit entry menu
* Fixed: Incorrect displaying of big numbers, being displayed in scientific form
* Added: When balance is below 0 balance text highlighting with red
* Added: On pressing "Delete" key on keyboard currently selected entry is actually deleting
* Deleted: Code was cleared of qDebug() functions

03 april 2016 (0.5.5)

* Added: Keyboard shortcut for confirm button. Press Return to confirm

02 april 2016 (0.5.5)

* Added: button for reset dateTime

28 of march 2016 (0.5.5)

* Fixed: Table content now is actually stretching to window
* Fixed: Clean database is working now
* Added: Edit entry dialog
* Changed: On confirm old summ has been cleared

26 of march 2016 (0.5.4)

* Fixed: changing size of confirm button in russian translated
* Fixed: size of buttons "settings", "about", "exit" being too big on full
screen application

24 october 2015 (0.5.3)

* Fixed:       SQL manager minor fixes

18 september 2014 (0.5.2):
        Not ready for next release. According plan 14-10 (0.6) will be in october
* Added:        Dynamic translation of main application window
* Added:        Possibility to sort TableView according parameters
* Fixed:        Invalid time adding bug
* Changed:      Columns now fit table perfectly

18 august 2014
        Released version 14-08(0.5) of Snipe Studio Budget Manager
        Changelog:
* Added: 	Multilanguage support
* Fixed: 	Memory leaks due to storing method
* Changed: 	Changed data store to faster way
* Changed: 	Default instalation folder in windows setup

18 april 2014
        Released version 14-04(0.0.3) of Snipe Studio Budget Manager
        Changelog:
* Added:        Menu on top of window
* Added:        Settings Menu
* Added:        Possibility to force save/load data
* Added:        Possibility to separately store different date
* Added:        Possibility to type currency
* Fixed:        Minor fixes

16 March 2014
        Released version 0.0.2 of Snipe Studio Budget Manager
        Change log:
* Added:	Graphical UI
* Fixed: 	Small issues in code
* Changed:	Save on exit

05 February 2014
        Released version 0.0.1 of Snipe Studio Budget Manager
        Change log:
* Fixed:	Bugs in deleting function
* Added:	Checkouts for adding operations
* Added:	Force reload function
* Added:	Force save function
