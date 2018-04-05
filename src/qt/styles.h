#ifndef IOP_STYLES_H

#define IOP_STYLES_H

    #include <QSettings>

    static const QString s_iopLightBlue = "rgb(108,200,240)";
    static const QString s_iopLightTurqoise = "rgb(12,175,165)";

    static const QString s_iopantratith = "rgb(22,22,22)";
    static const QString s_iopMidGrey = "rgb(53,53,53)";
    static const QString s_iopLightGrey = "rgb(211,211,211)";
    static const QString s_white = "rgb(255,255,255)";

    static const QColor c_iopLightBlue = QColor(108,200,240);
    static const QColor c_iopLightTurqoise = QColor(12,175,165);

    static const QColor c_iopantratith = QColor(22,22,22);
    static const QColor c_iopMidGrey = QColor(53,53,53);
    static const QColor c_iopLightGrey = QColor(211,211,211);
    static const QColor c_white = QColor(255,255,255);

    static const QString styleSheetString =  QString(
            //General
            "QFrame { background-color: " + s_iopantratith + "; border: none;}"
            "QWidget {background: " + s_iopantratith + "; color: " + s_iopLightGrey + ";}"

            //QLineEdit
            "QLineEdit { background: " + s_iopantratith + "; border-style: solid; border-width: 1px;  border-color: " + s_iopMidGrey + ";}"

            //Checkbox
            "QCheckBox {padding: 5px;}"

            //Table view
            "QHeaderView { background: " + s_iopantratith + ";} "
            "QTableView { border: 1px solid " + s_iopMidGrey + "; selection-background-color: " + s_iopMidGrey + "; selection-color: "+ s_iopLightGrey + "; alternate-background: " + s_iopMidGrey + ";}"
            "QTableView::item { border-right: 1px solid " + s_iopMidGrey + "; border-bottom: 1px solid " + s_iopMidGrey + ";}"                    
            //"RecentRequestsTableModel::item { selection-background: " + accentTwo + "; selection-color: "+ fontColor + "; alternate-background: " + accentOne + "; }"

            //Spinbox
            "QAbstractSpinBox { background: " + s_iopantratith + "; border-style: solid; border-width: 1px;  border-color: " + s_iopMidGrey + ";}"
            "QAbstractSpinBox::up-button {min-height: 7px; border: 1px outset " + s_iopMidGrey + "}"
            "QAbstractSpinBox::down-button { min-height: 7px; border: 1px outset " + s_iopMidGrey + "}"
            "QAbstractSpinBox::up-button:off { min-height: 7px; border: 1px outset " + s_iopMidGrey + "}"
            "QAbstractSpinBox::down-button:off {min-height: 7px; border: 1px outset " + s_iopMidGrey + "}"
            "QAbstractSpinBox::up-arrow { image: url(:/icons/up_arrow) 1;}"
            "QAbstractSpinBox::down-arrow { image: url(:/icons/down_arrow) 1;}"                    
            "QAbstractSpinBox::up-arrow:off { image: url(:/icons/up_arrow_off) 1;}"                    
            "QAbstractSpinBox::down-arrow:off { image: url(:/icons/down_arrow_off) 1;}"                   
            

            //Combobox
            "QComboBox { background: " + s_iopantratith + "; border-style: outset; border-width: 1px;  border-color: " + s_iopMidGrey + "; min-width: 45px;}"
            "QComboBox QAbstractItemView { border-style: solid; border-width: 1px;  border-color: " + s_iopMidGrey + "; }"
            "QComboBox::drop-down { border: 1px outset " + s_iopMidGrey + "}"
            "QComboBox::down-arrow { image: url(:/icons/down_arrow) 1;}"

            //Menu
            "QMenu:item:selected { background: " + s_iopMidGrey + ";}"
            "QMenuBar { background-color: " + s_iopantratith + "; border: solid 1px " + s_iopMidGrey + ";}"
            "QMenuBar:item { padding: 5px; spacing: 0px;}"
            "QMenuBar:item:selected { background: " + s_iopMidGrey + ";}"

            //Toolbar
            "#toolbar {background: " + s_iopantratith + "; border-left: none; border-right: 1px solid " + s_iopMidGrey + "; border-top: none; border-bottom: none; padding-top: 0px;}"
            "#toolbar > QToolButton { width: 150px; height: 40px; background: " + s_iopantratith + "; border: none; padding: 6px; padding-left: 9px; padding-right: 9px; margin-bottom: 1px;}"
            "#toolbar > QToolButton:hover { color: " + s_iopLightBlue + "; border: none;}"                    
            "#toolbar > QToolButton:checked { color: " + s_iopLightTurqoise + "; border: none;}"
            
            //Scrollbar
            "QScrollBar:vertical {background: " + s_iopantratith + "; padding-top: 13px; padding-bottom: 13px;}"
            "QScrollBar:horizontal {background: " + s_iopantratith + "; padding-left: 13px; padding-right: 13px;}"

            "QScrollBar::handle { background: " + s_iopMidGrey + "; border: 1px solid " + s_iopMidGrey + "}"

            "QScrollBar::add-line:vertical { background: " + s_iopantratith + "; height: 10px; border: 1px outset " + s_iopMidGrey + "; subcontrol-positon: bottom; subcontrol-origin: margin; }"
            "QScrollBar::sub-line:vertical { background: " + s_iopantratith + "; height: 10px; border: 1px outset " + s_iopMidGrey + "; subcontrol-positon: top; subcontrol-origin: margin;}"
            "QScrollBar::up-arrow:vertical { image: url(:/icons/up_arrow) 1; }"
            "QScrollBar::down-arrow:vertical { image: url(:/icons/down_arrow) 1; }"

            "QScrollBar::add-line:horizontal { background: " + s_iopantratith + "; width: 10px; border: 1px outset " + s_iopMidGrey + "; subcontrol-positon: right; subcontrol-origin: margin;}"
            "QScrollBar::sub-line:horizontal { background: " + s_iopantratith + "; width: 10px; border: 1px outset " + s_iopMidGrey + "; subcontrol-position: left; subcontrol-origin: margin;}"
            "QScrollBar::left-arrow:horizontal { image: url(:/icons/left_arrow) 1; }"
            "QScrollBar::right-arrow:horizontal { image: url(:/icons/right_arrow) 1; }"                     


            //Progress Bar
            "QProgressBar {color: " + s_iopLightGrey + "; background: " + s_iopantratith + ";  border: 1px outset " + s_iopMidGrey + "; border-radius: 0px; padding: 1px; text-align: center;}" 
            "QProgressBar::chunk {color: " + s_iopLightGrey + "; background: qlineargradient(x1:0, y1:0, x2: 0.5, y2: 0, x3: 1, y3: 0, stop: 0 rgb(108,200,239), stop: 1 rgb(102,204,204), stop: 2 rgb(12,175,165)); border-radius: 1px; margin: 0px;}"
            
            //Balance seperator line
            "#lineb, #lineb1, #lineb2, #lineb3, #lineb4, #lineb5 { border-top: none; border-left: none; border-right: none; border-bottom: 1px; border-style: solid; border-color: " + s_iopMidGrey + ";}"
            "#labelBalanceText, #labelPendingText, labelTotalText {color: " + s_iopLightGrey + ";}"
            
            //Buttons (and Icons)
            "QPushButton { background-color: " + s_iopMidGrey + "; color: " + s_iopLightGrey + "; border-color: " + s_iopMidGrey + "; border-width: 1px; padding: 6px; border-style: outset; border-radius: 0px ;}"
            "QPushButton:hover { background-color: " + s_iopLightGrey + ";}"


            //Disturbing borders
            "#labelWalletStatus { border: none; background: transparent}"
            "#labelTransactionsStatus { border: none; background: transparent}"
            "#lineWatchBalance { border: none;}"
            //"#scrollArea {border: none }"
            "#widgetCoinControl { border: none }"
            "#frameFeeSelection { border: none}"
            "#warningIcon { border: none; background: transparent }"

            //Optional Borders
            "#frame { border: none;}"                               //balances frame
            "#frame_2 {border: none;}"                              //recent transactions
            "#SendCoins {border: none;}"                            //sendcoins entries
            "#SendCoinsDialog > #scrollArea {border: 1px solid " + s_iopMidGrey + ";}"  //sendcoins scrollarea
            "#frameFee {border: none;}"                             //sendcoins lower frame
            "#frame2 {border: none;}"                               //receive coins
        );


    class IoPStyles 
    {

     public:

        static bool customThemeIsSet()
        {
            QSettings settings;
            return (settings.value("theme").toString() != "default");
        }
    };

#endif // IOP_STYLES_H