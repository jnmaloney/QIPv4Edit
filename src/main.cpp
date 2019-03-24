#include <QApplication>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QHostAddress>
#include "QIPv4Edit.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QDialog dialog;
    QVBoxLayout layout;

    QLabel labelHeading("IPv4 Address");
    QLabel labelMirror;
    QIPv4Edit ipEdit;
    QPushButton button1("Set to home");
    QPushButton button2("Ping");


    // Check the text input by mirroring in a label widget
    QObject::connect(
      &ipEdit,
      &QLineEdit::textChanged,
      [&labelMirror, &ipEdit] {
        if (ipEdit.hasAcceptableInput())
          labelMirror.setText(ipEdit.text());
        else
          labelMirror.setText(ipEdit.text() + " [Invalid]");
      }
    );

    // Set the IP address programmatically
    QObject::connect(
      &button1,
      &QPushButton::pressed,
      [&ipEdit] {
        qint32 ipv4 =
          (127 << 24) +
          (0   << 16) +
          (0   <<  8) +
          (1   <<  0);
        ipEdit.setAddress(ipv4);
      }
    );

    // Add widgets to layout
    layout.addWidget(&labelHeading);
    layout.addWidget(&ipEdit);
    layout.addWidget(&labelMirror);
    layout.addWidget(&button2);
    layout.addWidget(&button1);

    // Show aapplication window
    dialog.setLayout(&layout);
    dialog.show();
    return app.exec();
}
