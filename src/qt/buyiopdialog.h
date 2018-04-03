// Copyright (c) 2011-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef IOP_QT_BUYIOPDIALOG_H
#define IOP_QT_BUYIOPDIALOG_H

#include "walletmodel.h"


#include <QDialog>
#include <QLineEdit>

class PlatformStyle;

/** Dialog for sending iops */
class BuyIoPDialog : public QDialog {

    Q_OBJECT

public:
    explicit BuyIoPDialog(const PlatformStyle *platformStyle, QWidget *parent = 0);
   
    ~BuyIoPDialog();
    void setModel(WalletModel *model);

public Q_SLOTS:
    void chooseAdress();

public:
    const PlatformStyle *platformStyle;
    WalletModel *model;
    QPushButton *selectAdress;
    QLineEdit *adressLineEdit;
};

#endif // IOP_QT_BUYIOPDIALOG_H
