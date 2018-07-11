// Copyright (c) 2011-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef IOP_QT_UTILITYDIALOG_H
#define IOP_QT_UTILITYDIALOG_H

#include <QDialog>
#include <QObject>

class IoPGUI;

namespace Ui {
    class HelpMessageDialog;
}

/** "Help message" dialog box */
class HelpMessageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HelpMessageDialog(QWidget *parent, bool about, bool update = false);
    ~HelpMessageDialog();

    void printToConsole();
    void showOrPrint();
    QPushButton* downloadButton;
    void update(bool success, bool latest = true, QString latestVersion = QString(), QString changeLog = QString(), QString tag = QString());

private:
    Ui::HelpMessageDialog *ui;
    QString text;
    QString updateDownloadURL;

private Q_SLOTS:
    void on_okButton_accepted();
    void on_downloadButton_accepted();
};


/** "Shutdown" window */
class ShutdownWindow : public QWidget
{
    Q_OBJECT

public:
    ShutdownWindow(QWidget *parent=0, Qt::WindowFlags f=0);
    static QWidget *showShutdownWindow(IoPGUI *window);

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // IOP_QT_UTILITYDIALOG_H
