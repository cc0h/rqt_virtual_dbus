sudo usermod -a -G input $USER

if groups $USER| grep -qw "input"; then
  echo "The user is enter the input group."
  echo "Sign in again for changes to take effect."
else
  echo "The user fail to enter the input group."
fi

