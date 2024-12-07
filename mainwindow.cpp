#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Creates the GUI for the current instance
    ui->setupUi(this);

    // Clears the display screen on the calculator
    ui->displayPanel->clear();

    // Changes operator and number boolean variables to false
    checkOperator = false;
    checkNumber = false;

    // Assigns listeners to the number and operator groups for when they're clicked
    ui->numberSet->connect(ui->numberSet,SIGNAL(buttonClicked(QAbstractButton*)),
                           this, SLOT(number_clicked(QAbstractButton*)));
    ui->operatorSet->connect(ui->operatorSet,SIGNAL(buttonClicked(QAbstractButton*)),
                              this, SLOT(operation_clicked(QAbstractButton*)));

    // Fixes window height and width
    this->setFixedSize(QSize(364, 364));
}

// Deconstructor deallocates memory upon application's exit
MainWindow::~MainWindow()
{
    delete ui;
}

// Called when any number is clicked
void MainWindow::number_clicked(QAbstractButton* button)
{
    // Retrieves current string on the display screen
    QString displayLabel = ui->displayPanel->text();

    // If-statement checks if last button clicked was an operator button
    // Updates operator boolean variable and clears display screen
    if (checkOperator) {
        displayLabel.clear();
        checkOperator = false;
    }

    // Displays clicked number if within the digit size limit
    if (displayLabel.length() >= maxDigits) {
        return;
    }
    displayLabel.append(button->text());
    ui->displayPanel->setText(displayLabel);
}

// Called when an operator is clicked
void MainWindow::operation_clicked(QAbstractButton* button)
{
    if (checkOperator) {
        lastOperator = button->text().at(0);
    }
    // Else-statement runs if there was another operator before this
    else {
        // Nested if-statement checks if there is already a number stored in memory
        if (checkNumber) {
            calcResult();
        }
        // Nested else-statement saves the previous number if one is not stored in memory
        else {
            checkNumber = true;
            QString displayLabel = ui->displayPanel->text();
            lastNumber = displayLabel.toDouble();
        }

        // Update the operator boolean variable and store the clicked operator in memory
        checkOperator = true;
        lastOperator = button->text().at(0);
    }
}

// Called when "Del" is clicked
void MainWindow::on_del_clicked()
{
    // Retrieves current string on the display screen
    QString displayLabel = ui->displayPanel->text();

    // If-statement checks if the screen is already empty
    if (displayLabel.length() == 0) {
        return;
    }

    // Deletes digit and displays updated number on screen
    displayLabel.QString::chop(1);
    ui->displayPanel->setText(displayLabel);
}

// Called when "=" is clicked
void MainWindow::on_calc_clicked()
{
    // Retrieves current string on the display screen
    QString displayLabel = ui->displayPanel->text();

    // If-statement that the necessary buttons have been pressed to carry out an operation
    if (!checkNumber || displayLabel.length() < 1 || checkOperator) {
        return;
    }

    // Displays result on screen
    calcResult();
    checkNumber = false;

}

// Called when "." is clicked
void MainWindow::on_decimal_clicked()
{
    // Retrieves current string on the display screen
    QString displayLabel = ui->displayPanel->text();

    // Checks if adding a decimal point will break the digit limit
    if (displayLabel.length() >= (maxDigits - 1) ||
        displayLabel.contains('.', Qt::CaseSensitive)) {
        return;
    }

    // Checks if number is already a decimal before adding the decimal point
    if (displayLabel.length() == 0) {
        displayLabel = "0";
    }
    displayLabel.append('.');

    // Displays number on screen
    ui->displayPanel->setText(displayLabel);
}

// Called when "C" is clicked
void MainWindow::on_clear_clicked()
{
    // Clears anything on display screen
    ui->displayPanel->clear();

    // Resets operator and number boolean variables
    checkOperator = false;
    checkNumber = false;
}

// Called when "%" is clicked
void MainWindow::on_percent_clicked()
{
    // Retrieves current string on the display screen
    QString displayLabel = ui->displayPanel->text();

    // Converts number to a double and makes it a percentage
    double percentage = displayLabel.toDouble();
    percentage *= 0.01;

    // Displays number on screen
    displayLabel = QString::number(percentage,'g', maxDigits);
    ui->displayPanel->setText(displayLabel);
}

// Called when "Abs" is clicked
void MainWindow::on_abs_clicked()
{
    // Retrieves current string on the display screen
    QString displayLabel = ui->displayPanel->text();

    // Converts number to a double and makes absolute
    double num = displayLabel.toDouble();
    num = abs(num);

    // Displays number on screen
    displayLabel = QString::number(num,'g', maxDigits);
    ui->displayPanel->setText(displayLabel);
}

// Called when "+/-" is clicked
void MainWindow::on_sign_clicked()
{
    // Retrieves current string on the display screen
    QString displayLabel = ui->displayPanel->text();

    // Initializes double holding variable and changes number's sign
    double number = displayLabel.toDouble();
    number *= -1;

    // Displays number on screen
    displayLabel = QString::number(number,'g', maxDigits);
    ui->displayPanel->setText(displayLabel);
}

/* Calculates result from the last operator, the last number,
 * and the next number entered by the user */
void MainWindow::calcResult() {

    // Retrieves current string on the display screen
    QString displayLabel = ui->displayPanel->text();

    // Removes unnecessary decimal points
    if (displayLabel.endsWith('.',Qt::CaseSensitive)) {
        displayLabel.QString::chop(1);
    }

    // If-statement carries out operation for the operator selected
    // Addition operator
    if (lastOperator == '+') {
        lastNumber += displayLabel.toDouble();
    }
    // Subtraction operator
    else if (lastOperator == '-') {
        lastNumber -= displayLabel.toDouble();
    }
    // Multiplication operator
    else if (lastOperator == 'x') {
        lastNumber *= displayLabel.toDouble();
    }
    // Division operator
    else if (lastOperator == '/') {
        lastNumber /= displayLabel.toDouble();
    }
    // Exponent operator
    else if (lastOperator == '^') {
        double x;
        if (displayLabel.toDouble() > 0) {
            x = lastNumber;
            for (int loop = 1; loop < displayLabel.toDouble(); ++loop){
                x *= lastNumber;
            }
        }
        else {
            x = 1 / lastNumber;
            lastNumber = 1 / lastNumber;
            for(int loop = 1; loop < qAbs(displayLabel.toDouble()); ++loop){
                x *= lastNumber;
            }
        }
        lastNumber = x;
    }
    // Square root operator
    else if (lastOperator == 'R') {
        if (lastNumber > 0){
            lastNumber = qSqrt(displayLabel.toDouble());
        }
    }
    // Modulo operator
    else if(lastOperator == 'M') {
        lastNumber = fmod(lastNumber, displayLabel.toDouble());
    }

    // Displays result
    displayLabel = QString::number(lastNumber,'g', maxDigits);
    ui->displayPanel->setText(displayLabel);
}

// Allows for direct keyboard input to work (in addition to the on-screen buttons)
void MainWindow::keyEvent(QKeyEvent *e) {
    switch (e->key()) {
    // The numbers from 0-9
    case Qt::Key_1:
        number_clicked(ui->num1);
        break;
    case Qt::Key_2:
        number_clicked(ui->num2);
        break;
    case Qt::Key_3:
        number_clicked(ui->num3);
        break;
    case Qt::Key_4:
        number_clicked(ui->num4);
        break;
    case Qt::Key_5:
        number_clicked(ui->num5);
        break;
    case Qt::Key_6:
        number_clicked(ui->num6);
        break;
    case Qt::Key_7:
        number_clicked(ui->num7);
        break;
    case Qt::Key_8:
        number_clicked(ui->num8);
        break;
    case Qt::Key_9:
        number_clicked(ui->num9);
        break;
    case Qt::Key_0:
        number_clicked(ui->num0);
        break;
    // Arithmetic operators
    case Qt::Key_Plus:
        operation_clicked(ui->actionPlus);
        break;
    case Qt::Key_Minus:
        operation_clicked(ui->actionMinus);
        break;
    case Qt::Key_Asterisk:
        operation_clicked(ui->actionMul);
        break;
    case Qt::Key_Slash:
        operation_clicked(ui->actionDiv);
        break;
    // Scientific operators
    case Qt::Key_AsciiCircum:
        operation_clicked(ui->actionExp);
        break;
    case Qt::Key_M:
        operation_clicked(ui->actionModu);
        break;
    case Qt::Key_R:
        operation_clicked(ui->actionRoot);
        break;
    // The period (or decimal) key
    case Qt::Key_Period:
        on_decimal_clicked();
        break;
    // The enter and return keys
    case Qt::Key_Enter:
    case Qt::Key_Return:
        on_calc_clicked();
        break;
    // The delete key
    case Qt::Key_Delete:
        on_del_clicked();
        break;
    // The clear key
    case Qt::Key_Clear:
        on_clear_clicked();
        break;
    // The percent symbol key
    case Qt::Key_Percent:
        on_percent_clicked();
        break;
    }
}
