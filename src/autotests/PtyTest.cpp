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
    Pty pty;
    QString program = QStringLiteral("sh");
    QStringList arguments;
    arguments << program;
    QStringList environments;
    const int result = pty.start(program, arguments, environments);

    QCOMPARE(result, 0);
    auto fpg = pty.foregroundProcessGroup();
    auto pid = pty.processId();
    // FIXME: This often fails on FreeBSD CI
    //  Actual   (fpg): 100000; Expected (pid): 28534
#if defined(Q_OS_FREEBSD)
    QSKIP("This often fails on CI FreeBSD CI", SkipSingle);
#else
    QCOMPARE(fpg, pid);
#endif
    pty.close();
}

QTEST_GUILESS_MAIN(PtyTest)

#include "moc_PtyTest.cpp"
