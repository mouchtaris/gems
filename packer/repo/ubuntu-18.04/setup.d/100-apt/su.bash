export DEBIAN_FRONTEND=noninteractive &&
apt-get update &&
apt-get upgrade --yes </dev/null | tee /dev/null &&
apt-get install --yes \
  curl \
  docker-ce \
  fish \
  python-pip \
  tmux \
  vim \
  </dev/null \
| tee /dev/null &&
true
