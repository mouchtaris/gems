# frozen_string_literal: true

require 'rubygems'
require 'pathname'
require 'args'
require 'mastoras/util/f'
require 'mastoras/scroll'

module Mastoras
  class Workspace
    include Args

    LIBRARY_PATH = 'library'
    BAZAAR_PATH = 'bazaar'
    PACKER_YAML_NAME = 'packer_yaml_name'

    CONFIG_DATA_SCHEMA = Hash[
      LIBRARY_PATH => String,
      BAZAAR_PATH => String,
      PACKER_YAML_NAME => String,
    ]

    def initialize(ctx, mastrofile)
      @ctx = ctx
      @mastrofile = mastrofile.tap(&check(:mastrofile, Pathname))
    end

    def mastroroot
      @mastroroot ||= @mastrofile.dirname
    end

    def config
      @config ||= @mastrofile
        .open('r', &Util::F::LoadYaml)
        .tap(&check(@mastrofile.to_s, CONFIG_DATA_SCHEMA))
        .freeze
    end

    def library
      @library ||= mastroroot / config[LIBRARY_PATH]
    end
    alias mastrorepo library
    extend Gem::Deprecate
    deprecate :mastrorepo, :library, 2019, 3

    def bazaar
      @bazaar ||= mastroroot / config[BAZAAR_PATH]
    end

    def packer_yaml_name
      @packer_yaml_name ||= config[PACKER_YAML_NAME].freeze
    end

    def scroll_of(name)
      Scroll.new(@ctx, library / name / packer_yaml_name)
    end

    def scrolls
      @scrolls ||= library
        .enum_for(:each_child)
        .lazy
        .map { |child| Scroll.new(@ctx, child / packer_yaml_name) }
        .freeze
    end
  end
end
