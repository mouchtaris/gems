if [ "$( hostname )" = 'vagrant' ]; then
  exit 0
fi

if [ $(which chef-server-ctl) ]; then
  echo "Creating initial user and organization..." &&

  if test ! -d /local
  then
    sudo mkdir -pv /local &&
    sudo chmod 777 /local &&
    true
  fi &&

  # Reconfigure with the correct hostname
  # (for SSL certificates)
  sudo chef-server-ctl \
    reconfigure \
  &&

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
