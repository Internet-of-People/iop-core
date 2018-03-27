// Copyright (c) 2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef IOP_QT_PLATFORMSTYLE_H
#define IOP_QT_PLATFORMSTYLE_H

#include <QIcon>
#include <QPixmap>
#include <QString>

static const QString sPrimaryLightblue = "rgb(108,200,240)";
static const QString sPrimaryMint = "rgb(12,175,165)";

static const QString sSecondaryAnthrazit = "rgb(22,22,22)";
static const QString sSecondaryGray = "rgb(53,53,53)";
static const QString sSecondaryLightGray = "rgb(211,211,211)";
static const QString sSecondaryWhite = "rgb(255,255,255)";

static const QColor cPrimaryLightblue = QColor(108,200,240);
static const QColor cPrimaryMint = QColor(12,175,165);

static const QColor cSecondaryAnthrazit = QColor(22,22,22);
static const QColor cSecondaryGray = QColor(53,53,53);
static const QColor cSecondaryLightGray = QColor(211,211,211);
static const QColor cSecondaryWhite = QColor(255,255,255);

/* Coin network-specific GUI style information */
class PlatformStyle
{
public:
    /** Get style associated with provided platform name, or 0 if not known */
    static const PlatformStyle *instantiate(const QString &platformId);

    const QString &getName() const { return name; }

    bool getImagesOnButtons() const { return imagesOnButtons; }
    bool getUseExtraSpacing() const { return useExtraSpacing; }

    QColor TextColor() const { return textColor; }
    QColor SingleColor() const { return singleColor; }

    /** Colorize an image (given filename) with the icon color */
    QImage SingleColorImage(const QString& filename) const;

    /** Colorize an icon (given filename) with the icon color */
    QIcon SingleColorIcon(const QString& filename) const;

    /** Colorize an icon (given object) with the icon color */
    QIcon SingleColorIcon(const QIcon& icon) const;

    /** Colorize an icon (given filename) with the text color */
    QIcon TextColorIcon(const QString& filename) const;

    /** Colorize an icon (given object) with the text color */
    QIcon TextColorIcon(const QIcon& icon) const;

private:
    PlatformStyle(const QString &name, bool imagesOnButtons, bool colorizeIcons, bool useExtraSpacing);

    QString name;
    bool imagesOnButtons;
    bool colorizeIcons;
    bool useExtraSpacing;
    QColor singleColor;
    QColor textColor;
    /* ... more to come later */
};

#endif // IOP_QT_PLATFORMSTYLE_H

