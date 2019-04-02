test "${MASTORAS_BUILD_ROOT:-x}" = 'x' && exit 1
test "${MASTORAS_SCROLL_NAME:-x}" = 'x' && exit 1

export CURRENT="$MASTORAS_BUILD_ROOT/current"

mkdir -pv "$CURRENT/setup.d" &&
tar \
  --directory="$CURRENT/setup.d" \
  --extract \
  "$CURRENT/setup.d.tar" &&

find "$CURRENT/setup.d" \
  -mindepth 1 \
  -maxdepth 1 \
  -regextype posix-extended \
  -regex '.*[0-9]{3}-[a-zA-Z_]+\.sh$' \
| sort \
| xargs bash -x -c '
  for arg;
  do
    bash "$arg" | sed -r -e "s,^,[$arg] ,"
  done' --
