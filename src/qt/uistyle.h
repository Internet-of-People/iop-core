// Copyright (c) 2017 IoP Ventures LLC
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef IOP_STYLES_H
#define IOP_STYLES_H

#include <QApplication>
#include <QColor>
#include <QFont>
#include <QFontDatabase>
#include <QSettings>

namespace UIStyle {
#if QT_VERSION > 0x050100
    const int ratio = ((QGuiApplication*)QCoreApplication::instance())->devicePixelRatio();
#else
    const int ratio = 1;
#endif

    const QSize TOOLBAR_ICONSIZE = QSize(76*ratio,33*ratio);
    const int BUTTON_DEFAULTWIDTH = 75*ratio;
    const QString s_BUTTON_DEFAULTWIDTH = QString::number(BUTTON_DEFAULTWIDTH).append("px");

    const QString s_iopLightBlue = "rgb(108,200,240)";
    const QString s_iopLightTurqoise = "rgb(12,175,165)";

    const QString s_iopantrazith = "rgb(22,22,22)";
    const QString s_iopMidGrey = "rgb(53,53,53)";
    const QString s_iopLightGrey = "rgb(211,211,211)";
    const QString s_white = "rgb(255,255,255)";

    const QString s_highlight_light_anthrazith = "rgba(30,30,30)";
    const QString s_highlight_dark_anthrazith = "rgba(15,15,15)";

    const QString s_highlight_light_midgrey = "rgba(63,63,63)";
    const QString s_highlight_dark_midgrey = "rgba(47,47,47)";
    const QString s_highlight_light_turqoise = "rgb(22,185,175)";
    const QString s_highlight_dark_turqoise = "rgb(2,165,155)";

    const QString s_placeHolderText = "rgba(211,211,211,50%)";

    const QColor c_iopLightBlue = QColor(108,200,240);
    const QColor c_iopLightTurqoise = QColor(12,175,165);

    const QColor c_iopantratith = QColor(22,22,22);
    const QColor c_iopMidGrey = QColor(53,53,53);
    const QColor c_iopLightGrey = QColor(211,211,211);
    const QColor c_white = QColor(255,255,255);

    const QColor c_highlight_light_anthrazith = QColor(30,30,30);

    const QColor c_highlight_light_midgrey = QColor(63,63,63);
    const QColor c_highlight_dark_midgrey = QColor(47,47,47);


    //QString fontfamily = QFontDatabase::applicationFontFamilies(fontid).at(0);
    //QFont monospace(family);

    const QString styleSheetString =  QString(
            //General
            "QFrame "
            "{ background-color: " + s_iopantrazith + "; border: none; font-family: Encode Sans Expanded; font-size: 14px;}"
            
            "QWidget "
            "{ background: " + s_iopantrazith + "; color: " + s_iopLightGrey + "; font-family: Encode Sans Expanded; font-size: 14px;}"

            "#addressBookButton, #pasteButton, #deleteButton "
            "{ width: 35; height: 35; background-color: " + s_highlight_light_anthrazith + "; color: " + s_iopLightGrey + "; border: 1px outset rgb(33,33,33); padding: 6px; border-radius: 0px;}"
            
            "#addressBookButton:hover, #pasteButton:hover, #deleteButton:hover "
            "{border: 1px solid "+ s_iopLightBlue + "}"

            "#addressBookButton:pressed, #pasteButton:pressed, #deleteButton:pressed "
            "{background-color: " + s_iopantrazith + "; border: 1px solid "+ s_iopLightBlue + "}"

            "QLineEdit "
            "{ background: " + s_iopantrazith + "; border-style: solid; border-color: " + s_iopLightBlue + "; border-width: 1px; border-top: none; border-left: none; border-right: none;}"
            
            "#warningIcon "
            "{ border: none; background: transparent }"

            "#transactions_title, #buy_title "
            "{ color: qlineargradient(x0:0, y0:0, x1: 1, y1: 0, stop: 0 " + s_iopLightTurqoise + ", stop: 0.3 " + s_iopLightBlue + "); font-size: 24px; }"
            
            "QPlainTextEdit "
            "{ background: " + s_highlight_light_anthrazith + "; border: 1px solid " + s_iopLightBlue + "; border-left: none; border-right: none; border-top: none}"
            
            //Table view
            "QHeaderView "
            "{ background: " + s_iopantrazith + ";} "
            
            "QTableView "
            "{ border: none; border-right: 1px solid " + s_iopMidGrey + "; selection-background-color: " + s_highlight_dark_midgrey + "; selection-color: "+ s_iopLightBlue + "; alternate-background-color: " + s_highlight_light_anthrazith + ";}"
            
            "QTableView::item "
            "{ border-right: none; border-bottom: none; }"                    
            
            "#treeWidget"
            "{ border: none; border-right: 1px solid " + s_iopMidGrey + "; selection-background-color: transparent; selection-color: "+ s_iopLightBlue + ";}"
            
            "#treeWidget::item "
            "{ border-right: none; border-bottom: none; }"   

            "#payAmount > QAbstractSpinBox, #payAmount > QComboBox"
            "{ min-height: 48px; font-size: 32px; color: " +  s_iopLightBlue +"; font-weight: light;}"
            "#buy_adressInfo, #buy_amountInfo, #buy_amountVaryInfo "
            "{ color: " + s_placeHolderText + ";}"
            
            //Progress Bar
            "QProgressBar "
            "{ color: transparent; background: " + s_iopantrazith + ";  border: 1px inset " + s_iopMidGrey + ";  padding: 0px; margin-left: 30px; margin-right: 30px;}" 
            "QProgressBar::chunk "
            "{ color: transparent; background: qlineargradient(x1:0, y1:0, x2: 0.5, y2: 0, x3: 1, y3: 0, stop: 0 rgba(108,200,239,100%), stop: 1 rgba(102,204,204,100%), stop: 2 rgba(12,175,165,100%)); border-radius: 1px; margin: 0px;}"
            
            //Balance seperator line
            "#lineb, #lineb1, #lineb2, #lineb3, #lineb4, #lineb5 , #lineb6 , #lineb7 , #lineb8 , #lineb9 ,#w_lineb, #w_lineb1, #w_lineb2, #w_lineb3, #w_lineb4, #w_lineb5, #w_lineb6, #w_lineb7, #w_lineb8, #w_lineb9"
            "{ border-top: none; border-left: none; border-right: none; border-bottom: 1px; border-style: solid; border-color: " + s_iopMidGrey + ";}"
            
            "#labelBalanceText, #labelPendingText, labelTotalText "
            "{ color: " + s_iopLightGrey + ";}"
            
            //Checkbox & RadioButton
            "QCheckBox {spacing: 5px}"
            "QCheckBox::indicator { width: 14px; height: 14px } "
            "QCheckBox::indicator:unchecked { image: url(:icons/checkbox_empty) }"
            "QCheckBox::indicator:checked { image: url(:icons/checkbox_filled) }"
            "QCheckBox::indicator:unchecked:hover {image: url(:icons/checkbox_empty_hover)}"
            "QCheckBox::indicator:checked:hover {image: url(:icons/checkbox_filled_hover)}"


            "QRadioButton::indicator { width: 14px; height: 14px } "
            "QRadioButton::indicator:unchecked { image: url(:icons/radio_empty) }"
            "QRadioButton::indicator:checked { image: url(:icons/radio_filled) }"
            "QRadioButton::indicator:unchecked:hover { image: url(:icons/radio_empty_hover) }"
            "QRadioButton::indicator:checked:hover { image: url(:icons/radio_filled_hover) }"

            //Spinbox
            "QAbstractSpinBox { background: " + s_iopantrazith + "; maximum-width: 500px; color: " +  s_iopLightBlue +"; border-style: solid; border-width: 1px;  border-color: " + s_iopLightBlue + "; border-top: none; border-left: none; border-right: none}"
            "QAbstractSpinBox::up-button {min-height: 7px; border: none; }"
            "QAbstractSpinBox::down-button { min-height: 7px; border: none}"
            "QAbstractSpinBox::up-button:off { min-height: 7px; border: none}"
            "QAbstractSpinBox::down-button:off {min-height: 7px; border: none}"
            "QAbstractSpinBox::up-arrow { image: url(:/icons/up_arrow) 1;}"
            "QAbstractSpinBox::down-arrow { image: url(:/icons/down_arrow) 1;}"                    
            "QAbstractSpinBox::up-arrow:off { image: url(:/icons/up_arrow_off) 1;}"                    
            "QAbstractSpinBox::down-arrow:off { image: url(:/icons/down_arrow_off) 1;}"

            //Combobox
            "QComboBox {color: " + s_placeHolderText + "; background: " + s_iopantrazith + "; border-style: solid; border-width: 1px;  border-color: " + s_iopLightBlue + "; border-top: none; border-left: none; border-right: none; min-width: 45px;}"
            //border-style: outset; border-width: 1px;  border-color: " + s_iopMidGrey + "; }"
            "QComboBox QAbstractItemView { border: 1px outset " + s_iopMidGrey + "; background-color: " + s_highlight_dark_anthrazith + "}"//border-style: outset; border-width: 1px;  border-color: " + s_iopMidGrey + "; }"
            "QComboBox::drop-down { border: none; }"

            "QComboBox::down-arrow { image: url(:/icons/down_arrow) 1; width: 24; height: 24; border: none;}"

            //Menu
            "QMenu:item:selected { background: " + s_iopMidGrey + ";}"
            "QMenuBar { background-color: " + s_iopantrazith + "; border: solid 1px " + s_iopMidGrey + ";}"
            "QMenuBar:item { padding: 5px; spacing: 0px;}"
            "QMenuBar:item:selected { background: " + s_iopMidGrey + ";}"

            //Toolbar
            "#toolbar {background: " + s_iopantrazith + "; border-left: none; border-right: 1px solid " + s_iopMidGrey + "; border-top: none; border-bottom: none; padding-top: 0px;}"
            "#toolbar > QToolButton { width: 150px; height: 40px; background: transparent; border: none; padding: 6px; padding-left: 9px; padding-right: 9px; margin-bottom: 1px;}"
            "#toolbar > QToolButton:hover { color: " + s_iopLightBlue + "; border: none}"                    
            "#toolbar > QToolButton:checked { color: " + s_iopLightBlue + "; border: none;}"
            
            //Scrollbar
            "QScrollBar:vertical {background: " + s_iopantrazith + "; padding-top: 13px; padding-bottom: 13px;}"
            "QScrollBar:horizontal {background: " + s_iopantrazith + "; padding-left: 13px; padding-right: 13px;}"
            "QScrollBar::handle { background: " + s_iopMidGrey + "; border: 1px outset " + s_iopMidGrey + "}"
            "QScrollBar::handle:vertical {min-height: 20px}"
            "QScrollBar::handle:horizontal {min-width: 20px}"
            "QScrollBar::handle:hover { background: " + s_highlight_light_midgrey + "; border: 1px outset " + s_highlight_light_midgrey + "}"
            "QScrollBar::handle:pressed { background: " + s_highlight_dark_midgrey + "; border: 1px outset " + s_iopMidGrey + "}"
            "QScrollBar::add-line:vertical { background: " + s_iopantrazith + "; height: 10px; border: 1px outset " + s_iopMidGrey + "; subcontrol-positon: bottom; subcontrol-origin: margin; }"
            "QScrollBar::sub-line:vertical { background: " + s_iopantrazith + "; height: 10px; border: 1px outset " + s_iopMidGrey + "; subcontrol-positon: top; subcontrol-origin: margin;}"
            "QScrollBar::up-arrow:vertical { image: url(:/icons/up_arrow) 1; }"
            "QScrollBar::down-arrow:vertical { image: url(:/icons/down_arrow) 1; }"
            "QScrollBar::add-line:horizontal { background: " + s_iopantrazith + "; width: 10px; border: 1px outset " + s_iopMidGrey + "; subcontrol-positon: right; subcontrol-origin: margin;}"
            "QScrollBar::sub-line:horizontal { background: " + s_iopantrazith + "; width: 10px; border: 1px outset " + s_iopMidGrey + "; subcontrol-position: left; subcontrol-origin: margin;}"
            "QScrollBar::left-arrow:horizontal { image: url(:/icons/left_arrow) 1; }"
            "QScrollBar::right-arrow:horizontal { image: url(:/icons/right_arrow) 1; }"                     

            //Buttons (and Icons)
            //"#buyButton {background-color: " + s_iopLightTurqoise + "; color: " + s_white + "; border-color: " + s_iopLightTurqoise + "; }"
            //"#buyButton:hover { background-color: " + s_highlight_light_turqoise + "; color: " + s_iopantrazith + ";}"
            //"#buyButton:pressed { background-color: " + s_highlight_dark_turqoise + "; color: " + s_iopantrazith + "; border-style: inset;}"
            "QPushButton "
            "{ background-color: " + s_highlight_light_anthrazith + "; color: " + s_iopLightGrey + "; border: 1px outset rgb(33,33,33); padding: 6px; border-radius: 0px;}"
            "QPushButton:hover {border: 1px solid "+ s_iopLightBlue + "}"
            "QPushButton:pressed {background-color: " + s_iopantrazith + "; border: 1px solid "+ s_iopLightBlue + "}"
            "QPushButton:disabled { color: " + s_iopMidGrey + "}"

            "#payTo, #reqLabel, #reqMessage, #reqAmount, #addAsLabel, #label_Label, #label_amount, #label_message "
            "{ font-size: 14px; font-family: Encode Sans Expanded; font-weight: thin; color: " + s_iopLightGrey + ";}"                   
            
            "#buy_amountIOP, #pay_spinbox "
            "{ min-height: 48px; font-size: 32px; padding-right: 0; color: " +  s_iopLightBlue +"; text-align: left; font-weight: light; border-style: solid; border-color: " + s_iopLightBlue + "; border-width: 1px; border-top: none; border-left: none; border-right: none;}"

            "#buy_IOPLabel, #buy_currency, #payAmount > QValueComboBox"
            "{ min-height: 48px; font-size: 32px; padding-right: 0; padding-top: 0; color: " +  s_placeHolderText +"; text-align: left; font-weight: light; border-style: solid; border-color: " + s_iopLightBlue + "; border-width: 1px; border-top: none; border-left: none; border-right: none;}"
        

            //Disturbing borders
            "#labelWalletStatus { border: none; background: transparent}"
            "#labelTransactionsStatus { border: none; background: transparent}"
            "#lineWatchBalance { border: none;}"
            "#widgetCoinControl { border: none }"
            "#frameFeeSelection { border: none}"

            //Optional Borders
            "#frame { border: none;}"                               //balances frame
            "#frame_2 {border: none;}"                              //recent transactions
            "#SendCoins {border: none;}"                            //sendcoins entries
            //"#SendCoinsDialog > #scrollArea {border: 1px solid " + s_iopMidGrey + ";}"  //sendcoins scrollarea
            "#frameFee {border: none;}"                             //sendcoins lower frame
            "#frame2 {border: none;}"                               //receive coins
            "#scrollArea {border: none; }"

            "QToolTip { background: " + s_iopMidGrey + "; color: "+  s_iopLightGrey + "; border: none }"

        );
}

class IoPStyles 
{

    public:
        static void addFonts()
        {
        QFontDatabase::addApplicationFont(":/fonts/light");
        QFontDatabase::addApplicationFont(":/fonts/regular");
        QFontDatabase::addApplicationFont(":/fonts/medium");
        QFontDatabase::addApplicationFont(":/fonts/bold");
        }

        static bool customThemeIsSet()
        {
            QSettings settings;
            return (settings.value("theme").toString() != "default");
    }
};

#endif // IOP_STYLES_H
