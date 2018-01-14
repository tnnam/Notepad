#include "notepad.h"
#include "ui_notepad.h"
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include <QFontDialog>
#include <QFont>
#include <QColorDialog>
#include <QColor>
#include <QCloseEvent>
#include <QApplication>
#include <QSettings>
#include <QPrinter>
#include <QPrintDialog>

Notepad::Notepad(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Notepad)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

Notepad::~Notepad()
{
    delete ui;
}

/*_______________Tạo 1 file mới__________________*/
void Notepad::on_actionNew_triggered()
{
        CurrentFile = "";
        ui->textEdit->setText("");
}

/*__________________Mở file__________________*/
void Notepad::on_actionOpen_triggered()
{
        //Chọn file bạn muốn mở khi cửa sổ mở ra
        QString filter = "All File (*.*) ;; Text File (*.txt) ;; XML File (*.xml)";
        QString fileName = QFileDialog::getOpenFileName(this, "Open the file", QDir::homePath(), filter);
        QFile file(fileName);//Chọn tên file cần mở
        CurrentFile = fileName;
        if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            QMessageBox::warning(this,"..","File not opened.");
            return;
        }
        QTextStream in(&file);
        QString text = in.readAll();
        ui->textEdit->setText(text);
        file.close();
}

/*________________Lưu file__________________*/
void Notepad::on_actionSave_triggered()
{
        QFile file(CurrentFile);
        if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this,"..","No file opened. Use Save As");
            return;
        }
        QTextStream out(&file);
        QString text = ui->textEdit->toPlainText();
        out << text;
        file.flush();
        file.close();
}

/*_________________Lưu tất cả________________*/
void Notepad::on_actionSave_as_triggered()
{
       QString filter = "All File (*.*) ;; Text File (*.txt) ;; XML File(*.xml)";
       QString fileName = QFileDialog::getSaveFileName(this, "Save as", QDir::homePath(), filter);
       QFile file(fileName);
       CurrentFile = fileName;
       if (!file.open(QFile::WriteOnly | QFile::Text)) {
           QMessageBox::warning(this,"..","File not opened.");
           return;
       }
       QTextStream out(&file);
       QString text = ui->textEdit->toPlainText();
       out << text;
       file.flush();
       file.close();
}

/*___________Các thao tác đã được Qt hỗ trợ sẵn__________*/
void Notepad::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void Notepad::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void Notepad::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void Notepad::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void Notepad::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

/*________________Máy in___________________*/
void Notepad::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("desierd printer name");
    QPrintDialog dialog(&printer, this);
    if(dialog.exec() == QDialog::Rejected) return;
    ui->textEdit->print(&printer);
}

/*________________Font__________________*/
void Notepad::on_actionFont_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if(ok){
        ui->textEdit->setFont(font);
    }
    else return;
}

/*__________________Color________________*/
void Notepad::on_actionColor_triggered()
{
    QColor color  = QColorDialog::getColor(Qt::white, this, "Chose Color");
    if(color.isValid()){
        ui->textEdit->setTextColor(color);
    }
}

void Notepad::on_actionBackground_Color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose Color");
    if(color.isValid()){
        ui->textEdit->setTextBackgroundColor(color);
    }
}

void Notepad::on_actionBackground_Color_Edit_Text_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose Color");
    if(color.isValid()){
        ui->textEdit->setPalette(QPalette(color));
    }
}

void Notepad::writeSettings()
  {
      QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
      settings.setValue("geometry", saveGeometry());
  }

/*_______________Xét điều kiện để lưu file____________*/
bool Notepad::maybeSave(){
    if (!ui->textEdit->document()->isModified())
             return true;
         const QMessageBox::StandardButton ret
             = QMessageBox::warning(this, tr("Application"),
                                    tr("The document has been modified.\n"
                                       "Do you want to save your changes?"),
                                    QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
         switch (ret) {
         case QMessageBox::Save:{
             QFile file(CurrentFile);
             if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
                 QMessageBox::warning(this,"..","No file opened. Use Save As");
                 return 0;
             }
             QTextStream out(&file);
             QString text = ui->textEdit->toPlainText();
             out << text;
             file.flush();
             file.close();
             return true;
         }
         case QMessageBox::Cancel:
             return false;
         default:
             break;
         }
         return true;
}

void Notepad::closeEvent(QCloseEvent *event)//Khi bạn bấm tắt, xét nếu file có sự thay đổi thì mới hiện lên cửa sổ
//thông báo bạn có muốn lưu file hay không
  {
      if (maybeSave()) {
          writeSettings();
          event->accept();
      } else {
          event->ignore();
      }
  }


