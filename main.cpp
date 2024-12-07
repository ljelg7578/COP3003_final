#include "mainwindow.h"
// Includes class to manage main GUI settings
#include <QApplication>

/* Main function passes argument count and argument vector parameters
 * from the command line to start the application */
int main(int argc, char *argv[])
{
    // Initializes the program's window system
    QApplication a(argc, argv);

    // Declares new object to construct the program's main window
    MainWindow w;

    // Displays the calculator window on screen
    w.show();

    /* Main function returns exec() to start event handling, staying in
     * the main event loop until it receives a call to exit the program */
    return a.exec();
}
