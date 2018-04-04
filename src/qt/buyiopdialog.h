// Copyright (c) 2011-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef IOP_QT_BUYIOPDIALOG_H
#define IOP_QT_BUYIOPDIALOG_H

#include "walletmodel.h"
#include "iopamountfield.h"


#include <QDialog>
#include <QLineEdit>
#include <QDoubleSpinBox>


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
    void updatePhysical();
    void updateIoP(double i);

public:
    const PlatformStyle *platformStyle;
    WalletModel *model;
    QPushButton *selectAdress;
    QLineEdit *adressLineEdit;
    QDoubleSpinBox* paySpinBox;
    IoPAmountField* amountIoP;

private:
    bool slotblock;
};

#endif // IOP_QT_BUYIOPDIALOG_H
