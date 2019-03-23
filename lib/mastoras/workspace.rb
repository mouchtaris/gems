# frozen_string_literal: true

require 'pathname'
require 'args'
require 'mastoras/mastroroot'

module Mastoras
  class Workspace
    include Args

    def initialize(root)
      @root = root
        .tap(&check(:root, Pathname))
    end

    CONFIG_DATA_SCHEMA = Hash[
      'mastrorepo_name': String
    ]

    def mastroroot
      Mastroroot.new(@root)
    end

    def config_data
      @config_data ||= mastroroot
        .mastrofile
        .open('r', &YAML.method(:safe_load))
    end

    def config
      config_data
        .tap(&check(:config_data, CONFIG_DATA_SCHEMA))
    end

    def mastrorepo_name
      config_data['mastrorepo_name']
    end

    def mastrorepo
      @root / mastrorepo_name
    end
  end
end
