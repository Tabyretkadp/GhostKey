<div align = center>

<img src="/core/visual/LOGO.png" alt="Logo" width="200"/>

<br>

<h1>GhostKey v1.0</h1>

</div>

**GhostKey** is a local application for secure storage and management of passwords and seed phrases for cryptocurrency wallets.  
The program ensures private data concealment and encrypts information, protecting your digital assets from unauthorized access.

# Screen

<img src="/screen/1.jpg" alt="Screen" width="500"/>

## What GhostKey Does

- Hashes passwords and provides them for use — a convenient and reliable password manager  
- Stores passwords and wallet seed phrases locally  
- Hides data so that access is only possible with root privileges  
- Does not send any data over the internet; all operations are local — maximum privacy and security

## Summary

- Local data storage and processing without servers  
- Uses cryptographic algorithms (OpenSSL) to protect information  
- User-friendly interface with visual elements for managing passwords and seed phrases  
- Simple and clear build process using Makefile

---

## Installation

- Supported package managers: apt (Debian/Ubuntu), pacman (Arch/Manjaro), dnf (Fedora)

Clone the repository and build the project:

```bash
git clone https://github.com/Tabyretkadp/GhostKey
cd ghostkey
sudo chmod +x install.sh
./install.sh

