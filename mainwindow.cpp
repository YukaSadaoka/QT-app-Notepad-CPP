#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)// create UI class and set ui class member
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// New button
void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}

// Open button
void MainWindow::on_actionOpen_triggered()
{
    // Create a dialog box for to open a file
    QString filename = QFileDialog::getOpenFileName(this, "Open the file");

    // QFile object to read from a file
    QFile file(filename);
    currentFile = filename;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot open file " + file.errorString());
    }
    setWindowTitle(filename);

    // Create an interface to read the file and copy text to QString obj
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

// Save as button
void MainWindow::on_actionSave_as_triggered()
{
    // Open a file dialog to save a file
    QString filename = QFileDialog::getSaveFileName(this, "Save as");

    // Create QFile object to write a file
    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save file " + file.errorString());
        return;
    }
    // Set the currentFile obj memeber with the filename
    currentFile = filename;
    setWindowTitle(filename);

    // Output the text into the file
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

// Print button
void MainWindow::on_actionPrint_triggered()
{
    // Set printer
    QPrinter printer;
    printer.setPrinterName("Printername");

    // Dialog for user to select
    QPrintDialog pDialog(&printer, this);

    // If there is any errors, abort the process and display a message
    if(pDialog.exec() == QDialog::Rejected){
        QMessageBox::warning(this, "Warning", "Cannot Access printer");
        return;
    }
    ui->textEdit->print(&printer);
}

// Exit button
void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

// Copy button
void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

// Paste button
void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

// Cut button
void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

// Undo button
void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

// Redo button
void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}
