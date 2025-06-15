#!/bin/bash
set -e

echo "Определяем дистрибутив Linux..."

if [ -f /etc/os-release ]; then
    . /etc/os-release
    DISTRO=$ID
else
    echo "Не удалось определить дистрибутив."
    exit 1
fi

install_ubuntu() {
    sudo apt update
    sudo apt install -y build-essential libssl-dev
}

install_arch() {
    sudo pacman -Sy --noconfirm base-devel openssl
}

install_fedora() {
    sudo dnf install -y gcc-c++ openssl-devel
}

echo "Проверяем наличие g++..."

if ! command -v g++ &> /dev/null; then
    echo "g++ не найден."
else
    echo "g++ установлен."
fi

case "$DISTRO" in
    ubuntu|debian)
        echo "Дистрибутив: $DISTRO"
        install_ubuntu
        ;;
    arch)
        echo "Дистрибутив: Arch Linux"
        install_arch
        ;;
    fedora)
        echo "Дистрибутив: Fedora"
        install_fedora
        ;;
    *)
        echo "Дистрибутив $DISTRO не поддерживается скриптом автоматически."
        echo "Пожалуйста, установите g++ и библиотеки OpenSSL вручную."
        exit 1
        ;;
esac

echo "Все зависимости установлены или уже были установлены."
echo "Теперь можно собирать проект с помощью 'make'."

