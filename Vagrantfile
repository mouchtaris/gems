# -*- mode: ruby -*-
# vi: set ft=ruby :
# frozen-string-literal: true

Vagrant.require_version '>= 2.2.4'

INSTALL_CHEF_SERVER_PATH = '/tmp/install-chef-server.bash'

DOMAIN = 'sp.org'

class Machine
  attr_reader :name

  def initialize(name, n)
    @name = name.to_s.dup.freeze
    @n = n
  end

  def ip
    sprintf('172.28.128.%d', 20 + @n)
  end

  def hostname
    "#{@name}.#{DOMAIN}"
  end

  def inspect
    "Μασίνι[#{@name},#{ip}]"
  end
end

Machines = %w[tower server node0 node1]
  .each_with_index
  .map(&Machine.method(:new))
  .tap do |this|
    class << this
      def hosts
        self
          .map { |m| "#{m.ip} #{m.name}" }
          .join("\n")
      end

      def provision_hosts
        self
          .map { |m| %Q,printf '%s %s\\n' '#{m.ip}' '#{m.name}.sp.org' | sudo tee -a /etc/hosts, }
          .join("\n")
      end
    end
  end

# All Vagrant configuration is done below. The "2" in Vagrant.configure
# configures the configuration version (we support older styles for
# backwards compatibility). Please don't change it unless you know what
# you're doing.
Vagrant.configure("2") do |config|
  # The most common configuration options are documented and commented below.
  # For a complete reference, please see the online documentation at
  # https://docs.vagrantup.com.

  # Every Vagrant development environment requires a box. You can search for
  # boxes at https://vagrantcloud.com/search.

  Machines.each do |machine_def|
    config.vm.define machine_def.name do |machine|
      config.vm.box = 
        case machine_def.name
        when 'server' then 'mastoras/chef_server'
        else 'mastoras/chefws'
        end
      machine.vm.hostname = machine_def.hostname
      machine.vm.network 'private_network', ip: machine_def.ip
      machine.vm.provision 'shell', inline: Machines.provision_hosts
      machine.vm.provision 'shell',
        inline: %Q,sudo hostnamectl set-hostname '#{machine_def.hostname}',
    end
  end

  #config.vm.define 'tower' do |tower|
  #  tower.vm.hostname = 'tower'
  #  tower.vm.network 'private_network', ip: '172.28.128.11'
  #  tower.vm.provision 'shell', inline: <<-'SHELL'
  #    printf '
  #  SHELL
  #end

  #config.vm.define 'server' do |server|
  #  server.vm.hostname = 'server'
  #  server.vm.network 'private_network', ip: '172.28.128.12'
  #end

  #config.vm.define 'node0' do |node0|
  #  node0.vm.hostname = 'node0'
  #  node0.vm.network 'private_network', ip: '172.28.128.13'
  #end

  #config.vm.define 'node1' do |node1|
  #  node1.vm.hostname = 'node1'
  #  node1.vm.network 'private_network', ip: '172.28.128.14'
  #end

  #%w[
  #  tower
  #  server
  #  node0
  #  node1
  #].each do |name|
  #  config.vm.define name do |subconfig|
  #    subconfig.vm.hostname = name
  #    puts "#{name} IP: #{ipman.to_s}"
  #    subconfig.vm.network 'private_network', ip: ipman.to_s
  #    ipman.next!
  #  end
  #end

  # Disable automatic box update checking. If you disable this, then
  # boxes will only be checked for updates when the user runs
  # `vagrant box outdated`. This is not recommended.
  # config.vm.box_check_update = false

  # Create a forwarded port mapping which allows access to a specific port
  # within the machine from a port on the host machine. In the example below,
  # accessing "localhost:8080" will access port 80 on the guest machine.
  # NOTE: This will enable public access to the opened port
  # config.vm.network "forwarded_port", guest: 80, host: 8080

  # Create a forwarded port mapping which allows access to a specific port
  # within the machine from a port on the host machine and only allow access
  # via 127.0.0.1 to disable public access
  # config.vm.network "forwarded_port", guest: 80, host: 8080, host_ip: "127.0.0.1"

  # Create a private network, which allows host-only access to the machine
  # using a specific IP.
  # config.vm.network "private_network", ip: "192.168.33.10"

  # Create a public network, which generally matched to bridged network.
  # Bridged networks make the machine appear as another physical device on
  # your network.
  # config.vm.network "public_network"

  # Share an additional folder to the guest VM. The first argument is
  # the path on the host to the actual folder. The second argument is
  # the path on the guest to mount the folder. And the optional third
  # argument is a set of non-required options.
  # config.vm.synced_folder "../data", "/vagrant_data"

  # Provider-specific configuration so you can fine-tune various
  # backing providers for Vagrant. These expose provider-specific options.
  # Example for VirtualBox:
  #
  # config.vm.provider "virtualbox" do |vb|
  #   # Display the VirtualBox GUI when booting the machine
  #   vb.gui = true
  #
  #   # Customize the amount of memory on the VM:
  #   vb.memory = "1024"
  # end
  #
  # View the documentation for the provider you are using for more
  # information on available options.

  # Enable provisioning with a shell script. Additional provisioners such as
  # Puppet, Chef, Ansible, Salt, and Docker are also available. Please see the
  # documentation for more information about their specific syntax and use.
  # config.vm.provision "shell", inline: <<-SHELL
  #   apt-get update
  #   apt-get install -y apache2
  # SHELL
end
