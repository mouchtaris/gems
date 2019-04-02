current_dir = File.dirname(__FILE__)
log_level                 :info
log_location              STDOUT
node_name                 'crabs'
client_key                "#{current_dir}/crabs.pem"
validation_client_name    'spongers-validator'
validation_key            "#{current_dir}/spongers.pem"
chef_server_url           'https://server.sp.org/organizations/spongers'
cookbook_path             ["#{current_dir}/../cookbooks"]
