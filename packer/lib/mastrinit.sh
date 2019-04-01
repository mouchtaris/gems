#!/usr/bin/env bash
mastoras="$MASTORAS_BUILD_ROOT" &&
current="$MASTORAS_BUILD_ROOT/$MASTORAS_SCROLL_NAME" &&

sudo mkdir -pv "$mastoras" &&
sudo chmod 777 "$mastoras" &&

sudo rm -rfv "$current" &&
mkdir -pv "$current" &&
ln -sv "$current" /mastoras/current &&

true
