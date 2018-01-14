#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>

namespace Ui {
class Notepad;
}

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    explicit Notepad(QWidget *parent = 0);
    ~Notepad();

protected:
    void writeSettings();
    bool maybeSave();
    void closeEvent(QCloseEvent *event) override;
private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionRedo_triggered();

    void on_actionUndo_triggered();

    void on_actionPrint_triggered();

    void on_actionFont_triggered();

    void on_actionColor_triggered();

    void on_actionBackground_Color_triggered();

    void on_actionBackground_Color_Edit_Text_triggered();

private:
    Ui::Notepad *ui;
    QString CurrentFile;//1 biến toàn cục
};

#endif // NOTEPAD_H
