#!/bin/sh
# https://learn.chef.io/modules/manage-a-node-chef-server/ubuntu/bring-your-own-system/set-up-your-chef-server#/
chef_server_deb=chef-server-core_12.19.31-1_amd64.deb
chef_server_deb_path=/mastoras/downloads/"$chef_server_deb"
chef_server_deb_dir="$( dirname "$chef_server_deb_path" )"
export DEBIAN_FRONTEND=noninteractive &&
true&&

mkdir -pv "$chef_server_deb_dir" &&

# download the Chef server package
if [ ! -f "$chef_server_deb_path" ]; then
  echo "Downloading the Chef server package..."
  wget -nv -P "$chef_server_deb_dir" \
    https://packages.chef.io/files/stable/chef-server/12.19.31/ubuntu/18.04/"$chef_server_deb"
  # wget -nv -P /downloads https://packages.chef.io/files/stable/chef-server/12.17.33/ubuntu/16.04/chef-server-core_12.17.33-1_amd64.deb
fi

if [ "$( hostname )" = 'vagrant' ]; then
  exit 0
fi

# install Chef server
if [ ! $(which chef-server-ctl) ]; then
  echo "Installing Chef server..." &&
  #dpkg -i /downloads/chef-server-core_12.17.33-1_amd64.deb
  sudo dpkg -i "$chef_server_deb_path" &&

  echo '**************8' &&
  printf 'api_fqdn = %%q{%s}' "$( hostname )" |
    sudo tee -a /etc/opscode/chef-server.rb &&

  sudo chef-server-ctl reconfigure &&

  #chef-server-ctl org-create 4thcoffee "Fourth Coffee, Inc." --association_user chefadmin --filename 4thcoffee-validator.pem
  #chef-server-ctl user-create chefadmin Chef Admin admin@4thcoffee.com insecurepassword --filename /drop/chefadmin.pem
  true
fi &&

echo "My Chef server is ready!" &&

true
