#ifndef __QIPV4EDIT__
#define __QIPV4EDIT__


#include <QLineEdit>


class QIPv4Edit : public QLineEdit
{
  Q_OBJECT

public:
  QIPv4Edit(QWidget* parent = nullptr);
  ~QIPv4Edit();

  quint32 getAddress();
  void setAddress(quint32 ipv4);

protected:
};


#endif
