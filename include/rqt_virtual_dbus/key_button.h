//
// Created by yuchen on 2023/3/7.
//

#pragma

#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QRadioButton>
#include <QThread>
#include <QTimer>
#include <QWidget>
#include <fcntl.h>
#include <ros/ros.h>
#include <unistd.h>

#include "rm_msgs/DbusData.h"

class KeyboardButton : public QRadioButton {
  Q_OBJECT

public:
  explicit KeyboardButton(QWidget *parent = nullptr);
  ~KeyboardButton();

  void setDbusData(rm_msgs::DbusData *data) { dbus_data_ = data; }
  void updateSlip(bool state) { slip_state_ = state; }
  void updateState();

protected:
  void keyPressEvent(QKeyEvent *ev) override;
  void keyReleaseEvent(QKeyEvent *ev) override;
  void resizeEvent(QResizeEvent *ev) override;
  void focusOutEvent(QFocusEvent *ev) override;
  // 需要root用户执行 input_authority.bash 脚本以获取读取文件的权限
  // 这个方法不太好用
  void readMouseState();

private:
  bool slip_state_, read_keyboard_ = false;
  rm_msgs::DbusData *dbus_data_;
  QTimer *key_timer_;
};
