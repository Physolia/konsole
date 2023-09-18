/*
    SPDX-FileCopyrightText: 2008 Robert Knight <robertknight@gmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

// Own
#include "PtyTest.h"

// Qt
#include <QSize>
#include <QStringList>

// KDE
#include <QTest>

using namespace Konsole;

void PtyTest::init()
{
}

void PtyTest::cleanup()
{
}

void PtyTest::testFlowControl()
{
    Pty pty;
    const bool input = true;
    pty.setFlowControlEnabled(input);
    const bool output = pty.flowControlEnabled();
    QCOMPARE(output, input);
}

void PtyTest::testEraseChar()
{
    Pty pty;
    const char input = 'x';
    pty.setEraseChar(input);
    const char output = pty.eraseChar();
    QCOMPARE(output, input);
}

void PtyTest::testUseUtmp()
{
    Pty pty;
    const bool input = true;
    pty.setUseUtmp(input);
    const bool output = pty.isUseUtmp();
    QCOMPARE(output, input);
}

void PtyTest::testWindowSize()
{
    // Maybe https://bugreports.qt.io/browse/QTBUG-82351 ???
    QSKIP("Skipping on CI suse_tumbelweed_qt64", SkipSingle);
    return;

    Pty pty;
    QSize input(80, 40);
    QSize pxInput(80 * 8, 40 * 16);
    pty.setWindowSize(input.width(), input.height(), pxInput.width(), pxInput.height());
    QSize output = pty.windowSize();
    QCOMPARE(output, input);
    QSize pxOutput = pty.pixelSize();
    QCOMPARE(pxOutput, pxInput);
}

void PtyTest::testRunProgram()
{
    // Maybe https://bugreports.qt.io/browse/QTBUG-82351 ???
    QSKIP("Skipping on CI suse_tumbelweed_qt64", SkipSingle);
    return;

    Pty pty;
    QString program = QStringLiteral("sh");
    QStringList arguments;
    arguments << program;
    QStringList environments;
    const int result = pty.start(program, arguments, environments);

    QCOMPARE(result, 0);
    auto fpg = pty.foregroundProcessGroup();
    auto pid = pty.processId();
    // Try using variables in the QCOMPARE due to random failures on CI
    QCOMPARE(fpg, pid);
    pty.close();
}

QTEST_GUILESS_MAIN(PtyTest)

#include "moc_PtyTest.cpp"
