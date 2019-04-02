#!/bin/sh
[ ! -d "$HOME/.chef" ] && mkdir -pv "$HOME/.chef"
scp server.sp.org:crabs.pem "$HOME/.chef"
scp server.sp.org:spongers.pem "$HOME/.chef"
