# -*- mode: ruby -*-
# vi: set ft=ruby :
# frozen-string-literal: true
require_relative 'strip'
ENV['VAGRANT_NO_PARALLEL'] = 'yes'

Vagrant.require_version '>= 2.2.4'

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

  config.vm.define 'test' do |test|
    test.vm.box = 'bento/ubuntu-18.04'
  end

  machines.each do |machine_def|
    config.vm.define machine_def.name do |machine|
      config.vm.box = 
        case machine_def.name
        when 'server' then 'mastoras/chef_server'
        else 'mastoras/chefws'
        end
      machine.vm.hostname = machine_def.hostname
      machine.vm.network 'private_network', ip: machine_def.ip
      machine.vm.provision 'shell', inline: machines.provision_hosts
      machine.vm.provision 'shell',
        inline: %Q,sudo hostnamectl set-hostname '#{machine_def.hostname}',
      case machine_def.name
      when 'tower' then
      else
        #|   --server-url 'https://server.sp.org/organizations/spongers'
        #knife bootstrap --sudo --ssh-user vagrant --node-name node0 --run-list 'recipe[learn_chef_apache2]' node0.sp.org --server-url 'https://server.sp.org/organizations/spongers'
        machine.ssh.forward_agent = true
        machine.vm.provision 'shell', inline: <<-NO_SERVER
        NO_SERVER
      end
    end
  end

  # Disable automatic box update checking. If you disable this, then
  # boxes will only be checked for updates when the user runs
  # `vagrant box outdated`. This is not recommended.
  #config.vm.box_check_update = false

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
end


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

Machines = %w[node1 node0 server tower]
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

def machines
  Machines
end
