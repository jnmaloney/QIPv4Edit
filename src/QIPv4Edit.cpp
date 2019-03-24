#include "QIPv4Edit.h"
#include <QValidator>
#include <QHostAddress>


class MyValidator : public QValidator
{
public:
  QValidator::State	validate(QString &input, int &pos) const
  {
    bool tokensOutOfRange = false;
    bool leadingZero = false;

    QStringList stringTokens = input.split(".");

    if (stringTokens.size() > 4)
      return QValidator::Invalid;

    for (const auto& i : stringTokens)
    {
      int x = i.toInt();
      if (x < 0 || x > 255)
        tokensOutOfRange = true;
      if (i.length() > 1 && i.front() == '0')
        leadingZero = true;
    }

    if (tokensOutOfRange)
      return QValidator::Invalid;

    if (leadingZero)
      return QValidator::Intermediate;

    if (stringTokens.size() < 4)
      return QValidator::Intermediate;

    return QValidator::Acceptable;
  }


  void fixup(QString &input) const
  {
    QStringList stringTokens = input.split(".");
    while (stringTokens.size() < 4) stringTokens.append("0");
    input = QString("%1.%2.%3.%4")
      .arg(stringTokens[0].toInt())
      .arg(stringTokens[1].toInt())
      .arg(stringTokens[2].toInt())
      .arg(stringTokens[3].toInt());
  }
};


QIPv4Edit::QIPv4Edit(QWidget* parent) : QLineEdit(parent)
{
  setText("0.0.0.0");
  setValidator(new MyValidator);
}


QIPv4Edit::~QIPv4Edit()
{

}


quint32 QIPv4Edit::getAddress()
{
  return QHostAddress(text()).toIPv4Address();
}


void QIPv4Edit::setAddress(quint32 ipv4)
{
  setText(QHostAddress(ipv4).toString());
}
