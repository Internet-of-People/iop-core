// Copyright (c) 2011-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#if defined(HAVE_CONFIG_H)
#include "config/iop-config.h"
#endif

#include "utilitydialog.h"

#include "ui_helpmessagedialog.h"

#include "iopgui.h"
#include "clientmodel.h"
#include "guiconstants.h"
#include "intro.h"
#include "paymentrequestplus.h"
#include "guiutil.h"

#include "clientversion.h"
#include "init.h"
#include "util.h"

#include <QCloseEvent>
#include <QLabel>
#include <QRect>
#include <QPushButton>
#include <QRegExp>
#include <QTextTable>
#include <QTextCursor>
#include <QVBoxLayout>
#include <QSettings>

#include <iostream>

/** "Help message" or "About" dialog box */
HelpMessageDialog::HelpMessageDialog(QWidget *parent, bool about, bool update, bool available) :
    QDialog(parent),
    ui(new Ui::HelpMessageDialog)
{
    ui->setupUi(this);
    
    ui->okButton->button(QDialogButtonBox::Ok)->setIcon(QIcon());

    QString version = tr(PACKAGE_NAME) + " " + tr("version") + " " + QString::fromStdString(FormatFullVersion());
    /* On x86 add a bit specifier to the version so that users can distinguish between
     * 32 and 64 bit builds. On other architectures, 32/64 bit may be more ambiguous.
     */
#if defined(__x86_64__)
    version += " " + tr("(%1-bit)").arg(64);
#elif defined(__i386__ )
    version += " " + tr("(%1-bit)").arg(32);
#endif
    if(update)
    {
        
        //ui->horizontalSpacerButtons->setVisible(true);
        QString updateInfo;
        QString changelog = QString(" <p>The IoP Blockchain client version <em>6.1.0</em> is now available</p>\n"
"<h1>News</h1>\n"
"<p>This version introduces two new themes for the IoP Core client.  They are accurately called the <em>light</em> and <em>dark</em> theme. When you first start the new version, you are greeted by our new splash screen. After that, you will find the familiar standard wallet interface. To activate one of the new themes, navigate to <em>Preferences</em>-<em>Display</em> and select them from the drop-down menu. After a restart of the client, the wallet will greet you with a sleek, new interface. The default theme will remain the standard until we are completely sure that all interface bugs are weeded out.</p>\n"
"<p>All the newest changes from Bitcoin Core 0.15 have been implemented.</p>\n"
"<h1>Fixes</h1>\n"
"<p>This release adds updated seed servers. This fixes an issue where the client might not see peers on the network after a fresh install.</p>\n"
"<h1>Notice</h1>\n"
"<p>From now on, please consider the Ubuntu packages <em>deprecated</em>. We will still provide them for the next few minor releases, but they are superseded by the tar.gz files produced by gitian. To install these, extract them to a location of your choice, e.g. <code>/usr/local/bin/</code> or your home directory.</p>\n"
"<h1>General Information on 6.x.x</h1>\n"
"<p>This is a new major version release, including new features, various bugfixes<br>\n"
"and performance improvements, as well as updated translations. See below for more information.<br>\n"
"We have decided to drop the <em>IoP HD</em> name in favor of completely replacing the old client.<br>\n"
"This software will from now on be referred to as <strong>IoP Core</strong>.</p>\n"
"<p>While the consensus of the blockchain stays the same, the structure of the data directory <strong>does not</strong>. Therefore, <strong>a full reindex of the blockchain is necessary</strong> (see below for instructions). Additionally, the naming scheme of both executables and data files has been streamlined a bit, as detailed in the next section.</p>\n"
"<p>Removing all previous <em>IoP HD</em> or <code>iop-blockchain</code> packages is recommended to prevent possible confusion, but is not strictly necessary. Please be aware that you cannot use both v5.0.1 and v6.0.0 interchangeably with the same data directory.</p>\n"
"<h1>Naming Scheme</h1>\n"
"<p>The binaries are <code>iopd</code>, <code>iop-cli</code>, <code>iop-tx</code> and <code>iop-qt</code>, while the Windows and macOS executables are <code>iop-qt.exe</code> and <code>IoP-Qt.app</code>, respectively. The configuration file is called <code>iop.conf</code>.</p>\n"
"<p>The default data directory for both the command line and the Qt Wallet is</p>\n"
"<ul>\n"
"<li><code>~/.iop</code> on Linux,</li>\n"
"<li><code>%APPDATA%\\IoP</code> on Windows, and</li>\n"
"<li><code>~/Library/Application Support/IoP</code> on macOS.</li>\n"
"</ul>\n"
"<p>The Qt Wallet (<strong>NOT</strong> the command line utilities) will pick up your previously used data directory.</p>\n"
"<h1>How to update</h1>\n"
"<p>For most users, the relevant packages are the .dmg file (macOS), the .exe file for your CPU architecture (Windows 32-bit and 64-bit), and the .deb packages (Ubuntu 64-bit). Other Linux users should download i686-pc-linux (32-bit) or x86_64-linux (64-bit). The rest of the tar.gz files contain the command line utilities separately or are intended for uncommon architectures (these are untested, feedback is appreciated).</p>\n"
"<h1>Upgrading from <em>v5.0.1</em> or below</h1>\n"
"<p>A full reindex of the blockchain is necessary if you upgrade from <em>v5.0.1</em> or below. The recommended procedure is as follows:</p>\n"
"<ul>\n"
"<li>make a full backup of your data directory and then move it somewhere else.</li>\n"
"<li>create a new directory at the default location for your platform, containing only a copy of the files <code>wallet.dat</code> and (if applicable) <code>iop.conf</code>.</li>\n"
"<li>start the software.</li>\n"
"</ul>\n"
"<h1>How to use the new version for mining</h1>\n"
"<p>The miner is now multi-threaded and supports up to 128 threads. You should never use more threads than your CPU has logical cores. Some CPUs have more logical cores than physical ones, e.g. an Intel i5 dual-core processor has four logical cores. It is recommended to leave one thread free so your computer remains responsive to your input. The configuration file takes the following parameters related to mining :</p>\n"
"<pre><code># mine=1 tells IoP Core to use your CPU to try and find new blocks for the network\n"
"mine=0\n"
"\n"
"# You need to have the private key for a whitelisted address inside your wallet\n"
"# to mine new blocks. If your wallet is encrypted, you need to unlock it for about\n"
"# ten seconds to start mining (see below).\n"
"minewhitelistaddr=YOUR_ADDRESS_HERE\n"
"\n"
"# Optionally, you can also specify a target adress for the block reward associated \n"
"# with finding a new block.\n"
"minetoaddr=TARGET_ADDRESS_HERE\n"
"\n"
"# Specify the number of independent miners. They will all do unique work.\n"
"# When not specified, one thread is used.\n"
"minethreads=X\n"
"</code></pre>\n"
"<p>If you are using iopd for mining, you can unlock the wallet using</p>\n"
"<pre><code>iop-cli -datadir=/specify/non/standard/data/directory walletpassphrase YOUR_PASSPHRASE n\n"
"</code></pre>\n"
"<p>where <code>n</code> indicates the number of seconds you want to unlock (15 is sufficient for the miners to load the private key in the memory).</p>");
        if(available)
        {
            setWindowTitle(tr("Update Available"));
            updateInfo = tr("A new Update is available!");
            updateInfo.append("<br/><br/>\n");
            updateInfo.append(tr("Changelog: "));
            updateInfo.append("<br/>\n");
            updateInfo.append(changelog);
            resize(780,400);
            downloadButton = new QPushButton(tr("download"));
            ui->okButton->addButton(downloadButton, QDialogButtonBox::AcceptRole);
            connect(downloadButton, SIGNAL(clicked()), this, SLOT(on_downloadButton_accepted()));

        } else {
            setWindowTitle(tr("Latest Version"));
            updateInfo = tr("You have the current Version!<br><br>") + version;
        }

        ui->aboutMessage->setTextFormat(Qt::RichText);
        ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        text = updateInfo;
        ui->aboutMessage->setText(updateInfo);
        ui->helpMessage->setVisible(false);
    } else if (about)
    {
        setWindowTitle(tr("About %1").arg(tr(PACKAGE_NAME)));

        /// HTML-format the license message from the core
        QString licenseInfo = QString::fromStdString(LicenseInfo());
        QString licenseInfoHTML = licenseInfo;
        // Make URLs clickable
        QRegExp uri("<(.*)>", Qt::CaseSensitive, QRegExp::RegExp2);
        uri.setMinimal(true); // use non-greedy matching
        licenseInfoHTML.replace(uri, "<a href=\"\\1\">\\1</a>");
        // Replace newlines with HTML breaks
        licenseInfoHTML.replace("\n", "<br>");
        ui->aboutMessage->setTextFormat(Qt::RichText);
        ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        text = version + "\n" + licenseInfo;
        ui->aboutMessage->setText(version + "<br><br>" + licenseInfoHTML);
        ui->aboutMessage->setWordWrap(true);
        ui->helpMessage->setVisible(false);
    } else {
        setWindowTitle(tr("Command-line options"));
        resize(780,400);
        QString header = tr("Usage:") + "\n" +
            "  iop-qt [" + tr("command-line options") + "]                     " + "\n";
        QTextCursor cursor(ui->helpMessage->document());
        cursor.insertText(version);
        cursor.insertBlock();
        cursor.insertText(header);
        cursor.insertBlock();

        std::string strUsage = HelpMessage(HMM_IOP_QT);
        const bool showDebug = gArgs.GetBoolArg("-help-debug", false);
        strUsage += HelpMessageGroup(tr("UI Options:").toStdString());
        if (showDebug) {
            strUsage += HelpMessageOpt("-allowselfsignedrootcertificates", strprintf("Allow self signed root certificates (default: %u)", DEFAULT_SELFSIGNED_ROOTCERTS));
        }
        strUsage += HelpMessageOpt("-choosedatadir", strprintf(tr("Choose data directory on startup (default: %u)").toStdString(), DEFAULT_CHOOSE_DATADIR));
        strUsage += HelpMessageOpt("-lang=<lang>", tr("Set language, for example \"de_DE\" (default: system locale)").toStdString());
        strUsage += HelpMessageOpt("-min", tr("Start minimized").toStdString());
        strUsage += HelpMessageOpt("-rootcertificates=<file>", tr("Set SSL root certificates for payment request (default: -system-)").toStdString());
        strUsage += HelpMessageOpt("-splash", strprintf(tr("Show splash screen on startup (default: %u)").toStdString(), DEFAULT_SPLASHSCREEN));
        strUsage += HelpMessageOpt("-resetguisettings", tr("Reset all settings changed in the GUI").toStdString());
        if (showDebug) {
            strUsage += HelpMessageOpt("-uiplatform", strprintf("Select platform to customize UI for (one of windows, macosx, other; default: %s)", IoPGUI::DEFAULT_UIPLATFORM));
        }
        QString coreOptions = QString::fromStdString(strUsage);
        text = version + "\n" + header + "\n" + coreOptions;

        QTextTableFormat tf;
        tf.setBorderStyle(QTextFrameFormat::BorderStyle_None);
        tf.setCellPadding(2);
        QVector<QTextLength> widths;
        widths << QTextLength(QTextLength::PercentageLength, 35);
        widths << QTextLength(QTextLength::PercentageLength, 65);
        tf.setColumnWidthConstraints(widths);

        QTextCharFormat bold;
        bold.setFontWeight(QFont::Bold);

        for (const QString &line : coreOptions.split("\n")) {
            if (line.startsWith("  -"))
            {
                cursor.currentTable()->appendRows(1);
                cursor.movePosition(QTextCursor::PreviousCell);
                cursor.movePosition(QTextCursor::NextRow);
                cursor.insertText(line.trimmed());
                cursor.movePosition(QTextCursor::NextCell);
            } else if (line.startsWith("   ")) {
                cursor.insertText(line.trimmed()+' ');
            } else if (line.size() > 0) {
                //Title of a group
                if (cursor.currentTable())
                    cursor.currentTable()->appendRows(1);
                cursor.movePosition(QTextCursor::Down);
                cursor.insertText(line.trimmed(), bold);
                cursor.insertTable(1, 2, tf);
            }
        }
        ui->helpMessage->moveCursor(QTextCursor::Start);
        ui->scrollArea->setVisible(false);
        ui->aboutLogo->setVisible(false);
    }
}

HelpMessageDialog::~HelpMessageDialog()
{
    delete ui;
}

void HelpMessageDialog::printToConsole()
{
    // On other operating systems, the expected action is to print the message to the console.
    fprintf(stdout, "%s\n", qPrintable(text));
}

void HelpMessageDialog::showOrPrint()
{
#if defined(WIN32)
    // On Windows, show a message box, as there is no stderr/stdout in windowed applications
    exec();
#else
    // On other operating systems, print help text to console
    printToConsole();
#endif
}

void HelpMessageDialog::on_okButton_accepted()
{
    close();
}

void HelpMessageDialog::on_downloadButton_accepted()
{
    QDesktopServices::openUrl(QUrl("https://github.com/Internet-of-People/iop-core/releases",QUrl::TolerantMode)); 
}

/** "Shutdown" window */
ShutdownWindow::ShutdownWindow(QWidget *parent, Qt::WindowFlags f):
    QWidget(parent, f)
{
    QSettings settings; 
    if(settings.value("theme").toString() == "dark") 
    {   
        QString fontGray = "rgb(204,204,204)";
        QString medGray = "rgb(45,45,45)";
        setStyleSheet("QWidget {background: " + medGray + "; color: " + fontGray + ";}"); 
    } 
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel(
        tr("%1 is shutting down...").arg(tr(PACKAGE_NAME)) + "<br /><br />" +
        tr("Do not shut down the computer until this window disappears.")));
    setLayout(layout);
}

QWidget *ShutdownWindow::showShutdownWindow(IoPGUI *window)
{
    if (!window)
        return nullptr;

    // Show a simple window indicating shutdown status
    QWidget *shutdownWindow = new ShutdownWindow();
    shutdownWindow->setWindowTitle(window->windowTitle());

    // Center shutdown window at where main window was
    const QPoint global = window->mapToGlobal(window->rect().center());
    shutdownWindow->move(global.x() - shutdownWindow->width() / 2, global.y() - shutdownWindow->height() / 2);
    shutdownWindow->show();
    return shutdownWindow;
}

void ShutdownWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
}
