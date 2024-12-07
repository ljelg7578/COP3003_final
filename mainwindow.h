// Defines header if it has not already been defined
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Includes class for building the application's main window
#include <QMainWindow>
// Includes abstract base class for implementing clickable buttons
#include <QAbstractButton>
// Includes class for handling key events / receiving keyboard inputs
#include <QKeyEvent>

// Declares the scope identifier for initializing class objects
namespace Ui {
class MainWindow;
}

/* Defines derived class from QMainWindow to manage the members
 * and methods used by the application window */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    // Class constructor with parameter initializing new child widget
    explicit MainWindow(QWidget *parent = 0);
    /* Class deconstructor deletes object after the application ends
     * to deallocate memory */
    ~MainWindow();

    /* Defines slot functions to be called when the widget receives
 * a signal (when a certain button is pressed on the calculator) */
private slots:
    /* Called when any number / operation is pressed and points
     * to the group of number / operation buttons */
    void number_clicked(QAbstractButton*);
    void operation_clicked(QAbstractButton*);
    // Called when "C" is pressed
    void on_clear_clicked();
    // Called when "Del" is pressed
    void on_del_clicked();
    // Called when "%" is pressed
    void on_percent_clicked();
    // Called when "Abs" is pressed
    void on_abs_clicked();
    // Called when "." is pressed
    void on_decimal_clicked();
    // Called when "+/-" is pressed
    void on_sign_clicked();
    // Called when "=" is pressed
    void on_calc_clicked();

protected:
    // Method to handle incoming key events
    void keyEvent(QKeyEvent *e);

private:
    // Initializes user interface object
    Ui::MainWindow *ui;
    /* Initializes constant integer variable to set the digit
     * for numbers at 16 digits */
    const int maxDigits = 16;
    /* Boolean variable to register true if an operator was
     * the last button clicked by the user */
    bool checkNumber;
    /* Initializes double variable to retrieve the
     * last number that was stored in memory */
    double lastNumber;
    /* Calculates results given the last operator for the last
     * number and the second number clicked by the user*/
    bool checkOperator;
    /* Initializes object of QChar class to retrieve the
     * last operator that was stored in memory */
    QChar lastOperator;
    /* Boolean variable to register true if a number was
     * the last button clicked by the user */
    void calcResult();
};

#endif // MAINWINDOW_H
