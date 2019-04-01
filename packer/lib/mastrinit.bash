#!/usr/bin/env bash
mastoras=/mastoras &&
sudo mkdir -pv "$mastoras" &&
sudo chmod 777 "$mastoras" &&
current=/mastoras/"$1" &&
if test "$current" = "$mastoras/"
then
  echo 'artifact_name not given as $1' 2>&1
  exit 1
else true
fi &&
sudo rm -rfv "$current" &&
mkdir -pv "$current" &&
ln -sv "$current" /mastoras/current &&
true
