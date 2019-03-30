find /mastoras/setup.d \
  -mindepth 1 \
  -maxdepth 1 \
  -name '*.bash' \
| sort \
| xargs bash -c '
  for arg;
  do
    if [ test "$arg" != "setup.bash" ]
    then
      echo "*** $arg"
      bash "$arg" | sed -r -e "s,^,[$arg] ,"
    fi
  done' --
