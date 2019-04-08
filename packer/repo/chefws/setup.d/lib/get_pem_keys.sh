#!/bin/sh
[ ! -d "$HOME/.chef" ] && mkdir -pv "$HOME/.chef"
scp server.sp.org:/mloc/crabs.pem "$HOME/.chef"
scp server.sp.org:/mloc/spongers.pem "$HOME/.chef"
