#!/usr/bin/env bash

trap 'exit' ERR

cd /yuvPatterer

premake4 gmake

cd build/

make

echo "Provision (user) completed."
