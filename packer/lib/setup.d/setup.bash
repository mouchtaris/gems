if test "${MASTORAS_SETUP_RUNNING:+x}" = 'x'
then
  exit 0
fi
export MASTORAS_SETUP_RUNNING=yes

find "$MASTORsetup.d \
  -mindepth 1 \
  -maxdepth 1 \
  -regex '[0-9]+-*.bash' \
| sort \
| xargs bash -c '
  for arg;
  do
    echo "*** $arg"
    bash "$arg" | sed -r -e "s,^,[$arg] ,"
  done' --
