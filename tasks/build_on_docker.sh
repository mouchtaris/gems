true &&
source ./agent.sh &&
ssh -l nikos -p 22020 localhost 'make -C $HOME/op/ms/m2' |
  sed -e 's/^\/home\/nikos/\/Users\/nikolaos\/homes\/ws/'