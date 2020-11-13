/*
    SPDX-FileCopyrightText: 2007-2008 Robert Knight <robertknight@gmail.com>
    SPDX-FileCopyrightText: 2020 Tomaz Canabrava <tcanabrava@gmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef FILE_FILTER
#define FILE_FILTER

#include <QPointer>
#include <QString>
#include <QSet>

#include "RegExpFilter.h"

namespace Konsole {
class Session;
class HotSpot;

/**
 * A filter which matches files according to POSIX Portable Filename Character Set
 * https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap03.html#tag_03_267
 */

class FileFilter : public RegExpFilter
{
public:
    explicit FileFilter(Session *session);

    void process() override;

protected:
    QSharedPointer<HotSpot> newHotSpot(int, int, int, int, const QStringList &) override;

private:
    QPointer<Session> _session;
    QString _dirPath;
    QSet<QString> _currentDirContents;
};

}
#endif
