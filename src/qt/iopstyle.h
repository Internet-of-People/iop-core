// Copyright (c) 2017 IoP Ventures LLC
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef IOP_STYLE_H
#define IOP_STYLE_H

#include <QApplication>
#include <QColor>
#include <QFont>
#include <QFontDatabase>
#include <QSettings>

class IoPStyle
{
    public:

    static float getDevicePixelRatio();
    static QSize getToolbarIconSize(); 

    static void addFonts();
    static bool customThemeIsSet();

    static const QString s_iopLightBlue;
    static const QString s_iopLightTurqoise;

    static const QString s_iopantrazith;
    static const QString s_iopMidGrey;
    static const QString s_iopLightGrey;
    static const QString s_white;

    static const QString s_highlight_light_anthrazith;
    static const QString s_highlight_dark_anthrazith;

    static const QString s_highlight_light_midgrey;
    static const QString s_highlight_dark_midgrey;
    static const QString s_highlight_light_turqoise;
    static const QString s_highlight_dark_turqoise;

    static const QString s_placeHolderText;

    static const QColor c_iopLightBlue;
    static const QColor c_iopLightTurqoise;

    static const QColor c_iopantrazith;
    static const QColor c_iopMidGrey;
    static const QColor c_iopLightGrey;
    static const QColor c_white;

    static const QColor c_highlight_light_anthrazith;

    static const QColor c_highlight_light_midgrey;
    static const QColor c_highlight_dark_midgrey;

    static const QString styleSheetString;
};

#endif // IOP_STYLES_H
