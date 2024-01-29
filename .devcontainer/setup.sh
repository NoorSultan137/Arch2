#!/bin/sh

echo "Setting Up CAAL241 Development"

sudo apt-get update
sudo dpkg --add-architecture i386
sudo apt-get update
sudo apt-get install -y gcc-multilib libc6-dbg:i386 valgrind lib32readline-dev libreadline-dev
