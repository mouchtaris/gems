#!/usr/bin/env bash
set -x

test "${MASTORAS_BUILD_ROOT:-x}" = 'x' && exit 1
test "${MASTORAS_SCROLL_NAME:-x}" = 'x' && exit 1

mastoras="$MASTORAS_BUILD_ROOT"
current="$MASTORAS_BUILD_ROOT/$MASTORAS_SCROLL_NAME"



if test "${_MASTORAS_RESET+x}" = 'x'
then
  cd / && sudo rm -rfv "$mastoras"
fi &&


sudo mkdir -pv "$mastoras" &&
sudo chmod 777 "$mastoras" &&


sudo rm -rfv "$current" &&
mkdir -pv "$current" &&
rm -f "$MASTORAS_BUILD_ROOT/current" &&
ln -sv "$current" "$MASTORAS_BUILD_ROOT/current" &&


true
