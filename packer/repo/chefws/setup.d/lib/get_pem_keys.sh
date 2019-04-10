#!/bin/sh
[ ! -d "$HOME/.chef" ] && mkdir -pv "$HOME/.chef"
scp 
  -o PasswordAuthentication=no                \
  -o StrictHostKeyChecking=no                 \
  -o UserKnownHostsFile=/dev/null             \
  server.sp.org:/mloc/crabs.pem "$HOME/.chef"

scp 
  -o PasswordAuthentication=no                \
  -o StrictHostKeyChecking=no                 \
  -o UserKnownHostsFile=/dev/null             \
  server.sp.org:/mloc/spongers.pem "$HOME/.chef"
