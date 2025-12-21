/*
** EPITECH PROJECT, 2025
** qt_example_test.cpp
** File description:
** qt_example_test.cpp
*/

#include <qt6/QtTest/QtTest>

class MyFirstTest : public QObject {
    Q_OBJECT

   private:
    bool myCondition() { return true; }

   private slots:
    void initTestCase() { qDebug("Called before everything else."); }

    void myFirstTest() {
        QVERIFY(true);   // check that a condition is satisfied
        QCOMPARE(1, 1);  // compare two values
    }

    void mySecondTest() {
        QVERIFY(myCondition());
        QVERIFY(1 != 2);
    }

    void cleanupTestCase() {
        qDebug("Called after myFirstTest and mySecondTest.");
    }
};

QTEST_GUILESS_MAIN(MyFirstTest)
#include "qt_example_test.moc"