if test "${MASTORAS_SETUP_RUNNING:-x}" = 'x'
then
  exit 0
fi

find /mastoras/setup.d \
  -mindepth 1 \
  -maxdepth 1 \
  -name '*.bash' \
| sort \
| xargs bash -c '
  for arg;
  do
    echo "*** $arg"
    bash "$arg" | sed -r -e "s,^,[$arg] ,"
  done' --
