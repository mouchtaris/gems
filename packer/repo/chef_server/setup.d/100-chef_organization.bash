if [ "$( hostname )" = 'vagrant' ]; then
  exit 0
fi

if [ $(which chef-server-ctl) ]; then
  echo "Creating initial user and organization..." &&

  { test ! -d /local && mkdir -pv /local; } || true &&
  { test -d /local || exit 1; }

  sudo chef-server-ctl \
    user-create \
    crabs \
    Craberman Crabs \
    craberman@crabs.bb \
    crabs12121212 \
    -f /local/crabs.pem \
  &&
  sudo chef-server-ctl \
    org-create spongers \
    'Spongers United FD' \
    --association_user=crabs \
    -f /local/spongers.pem \
  &&

  echo "Waiting for services..." &&
  until (curl -D - http://localhost:8000/_status) | grep "200 OK"; do
    sleep 1s
  done &&
  while (curl http://localhost:8000/_status) | grep "fail"; do
    sleep 1s
  done &&

  echo "My Chef server is ready!" &&
  true
fi
