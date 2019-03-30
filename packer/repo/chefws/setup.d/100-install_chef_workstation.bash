export DEBIAN_FRONTEND=noninteractive &&
curl https://omnitruck.chef.io/install.sh \
| sudo bash -s -- -P chef-workstation -c stable -v 0.2.41 &&
sudo mkdir /mastoras &&
sudo chmod 777 /mastoras &&
true
