#!/usr/bin/env bash

if [ -z "$(which fdfind)" ]; then
  echo "fdfind not found, please install it"
  read -r -p "The script can install it? [y/N] " response
  if [[ "$response" =~ ^([yY][eE][sS]|[yY])+$ ]]; then
    sudo apt install fd-find
  else
    exit 1
  fi
fi

if [ -z "$(which clang-format-19)" ]; then
  echo "clang-format-19 not found, please install it"
  read -r -p "The script can install it? [y/N] " response
  if [[ "$response" =~ ^([yY][eE][sS]|[yY])+$ ]]; then
    local tmp="$(mktemp -d)"
    wget https://apt.llvm.org/llvm.sh -O "$tmp/llvm.sh"
    chmod +x "$tmp/llvm.sh"
    sudo "$tmp/llvm.sh" 19
    sudo apt install clang-format-19 clang-tidy-19 -y
  else
    exit 1
  fi
fi

echo "Running clang-format..."

code="$(fdfind -E "cmake-*/" -i -e cpp -e hpp | xargs clang-format-19 -style=file --verbose --dry-run --Werror)"
if [ "$?" -eq 0 ]; then
  echo "No files to format"
  exit 0
else
  echo "Some files need to be formatted"
  read -r -p "Do you want to format it? [y/N] " response
  if [[ "$response" =~ ^([yY][eE][sS]|[yY])+$ ]]; then
    fdfind -E "cmake-*/" -i -e cpp -e hpp | xargs clang-format-19 -style=file --verbose -i
    exit 0
  else
    exit 1
  fi
fi
