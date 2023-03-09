//
// Created by yuchen on 2023/3/7.
//

#include "rqt_virtual_dbus/key_button.h"

KeyboardButton::KeyboardButton(QWidget *parent) : QRadioButton(parent) {
  resize(parent->width(), parent->height());
  this->setText("Use keyboard");
  read_keyboard_ = this->isChecked();

  key_timer_ = new QTimer(this);

  connect(this, &QRadioButton::clicked, this, &KeyboardButton::updateState);
  //  connect(this->key_timer_, &QTimer::timeout, this,
  //          &KeyboardButton::readMouseState);
}

KeyboardButton::~KeyboardButton() {}

void KeyboardButton::updateState() {
  read_keyboard_ = this->isChecked();
  if (read_keyboard_) {
    key_timer_->start(80);
  } else {
    key_timer_->stop();
  }
}

void KeyboardButton::resizeEvent(QResizeEvent *event) {
  resize(this->parentWidget()->width(), this->parentWidget()->height());
}

void KeyboardButton::keyPressEvent(QKeyEvent *ev) {
  if (!slip_state_ || !read_keyboard_)
    return;

  switch (ev->key()) {
  case Qt::Key_W:
    dbus_data_->key_w = true;
    break;
  case Qt::Key_S:
    dbus_data_->key_s = true;
    break;
  case Qt::Key_A:
    dbus_data_->key_a = true;
    break;
  case Qt::Key_D:
    dbus_data_->key_d = true;
    break;
  case Qt::Key_Shift:
    dbus_data_->key_shift = true;
    break;
  case Qt::Key_Control:
    dbus_data_->key_ctrl = true;
    break;
  case Qt::Key_Q:
    dbus_data_->key_q = true;
    break;
  case Qt::Key_E:
    dbus_data_->key_e = true;
    break;
  case Qt::Key_R:
    dbus_data_->key_r = true;
    break;
  case Qt::Key_F:
    dbus_data_->key_f = true;
    break;
  case Qt::Key_G:
    dbus_data_->key_g = true;
    break;
  case Qt::Key_Z:
    dbus_data_->key_z = true;
    break;
  case Qt::Key_X:
    dbus_data_->key_x = true;
    break;
  case Qt::Key_C:
    dbus_data_->key_c = true;
    break;
  case Qt::Key_V:
    dbus_data_->key_v = true;
    break;
  case Qt::Key_B:
    dbus_data_->key_b = true;
    break;
  }
}

void KeyboardButton::keyReleaseEvent(QKeyEvent *ev) {
  if (!slip_state_ || !read_keyboard_)
    return;

  switch (ev->key()) {
  case Qt::Key_W:
    dbus_data_->key_w = false;
    break;
  case Qt::Key_S:
    dbus_data_->key_s = false;
    break;
  case Qt::Key_A:
    dbus_data_->key_a = false;
    break;
  case Qt::Key_D:
    dbus_data_->key_d = false;
    break;
  case Qt::Key_Shift:
    dbus_data_->key_shift = false;
    break;
  case Qt::Key_Control:
    dbus_data_->key_ctrl = false;
    break;
  case Qt::Key_Q:
    dbus_data_->key_q = false;
    break;
  case Qt::Key_E:
    dbus_data_->key_e = false;
    break;
  case Qt::Key_R:
    dbus_data_->key_r = false;
    break;
  case Qt::Key_F:
    dbus_data_->key_f = false;
    break;
  case Qt::Key_G:
    dbus_data_->key_g = false;
    break;
  case Qt::Key_Z:
    dbus_data_->key_z = false;
    break;
  case Qt::Key_X:
    dbus_data_->key_x = false;
    break;
  case Qt::Key_C:
    dbus_data_->key_c = false;
    break;
  case Qt::Key_V:
    dbus_data_->key_v = false;
    break;
  case Qt::Key_B:
    dbus_data_->key_b = false;
    break;
  }
}

void KeyboardButton::readMouseState() {
  int fd, bytes;
  unsigned char data[3];
  const char *pDevice = "/dev/input/mice";

  if (!slip_state_ || !read_keyboard_)
    return;

  // Open Mouse
  fd = open(pDevice, O_RDWR);
  if (fd < 0) {
    printf("ERROR Opening %s, are you run the script {input_authority.bash}?\n",
           pDevice);
    return;
  }
  int left, middle, right;
  signed char x, y;
  if (read_keyboard_) {
    // Read Mouse
    bytes = read(fd, data, sizeof(data));
    if (bytes > 0) {
      //  单击鼠标生成：
      //  x=0, y=0, left=1, middle=0, right=0
      //  x=0, y=0, left=0, middle=0, right=0
      //  并且一个鼠标移动(注意“相对”鼠标移动坐标)：
      //  x=1, y=1, left=0, middle=0, right=0
      left = data[0] & 0x1;
      right = data[0] & 0x2;
      middle = data[0] & 0x4;
      x = data[1];
      y = data[2];

      dbus_data_->m_x = x / 1600.;
      dbus_data_->m_y = y / 1600.;
      /* There is a problem with clicking */
      // dbus_data_->p_l = left;
      // dbus_data_->p_r = right;
    }
  }
  ::close(fd);
}

void KeyboardButton::focusOutEvent(QFocusEvent *event) {
  QRadioButton::focusOutEvent(event);
  if (read_keyboard_) {
    // 保持焦点
    this->setFocus();
    activateWindow();
  }
}
