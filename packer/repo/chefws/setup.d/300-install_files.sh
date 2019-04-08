lib="$CURRENT/setup.d/lib"
chef_d=$HOME/.chef
chef_config=$chef_d/config.rb

mkdir -pv $chef_d &&
  cp -av $lib/config.rb $chef_config &&

sudo mkdir -pv /mloc &&
  sudo chmod 777 /mloc &&
  cp -av $lib/get_pem_keys.sh /mloc &&

cookbooks="$(ruby -- $chef_config <<-'RUBY'
def log_level; end
def log_location; end
def node_name; end
def client_key; end
def validation_client_name; end
def validation_key; end
def chef_server_url; end
def cookbook_path(cbp); @cookbook_path = cbp end
require ARGV[0]
puts @cookbook_path.first
RUBY
)" &&

mkdir -pv "$cookbooks" &&
  cd "$cookbooks" &&
  git clone https://github.com/learn-chef/learn_chef_apache2.git &&

true
