# frozen_string_literal: true

require 'pathname'
require 'args'
require 'mastoras/util/f'
require 'mastoras/scroll'

module Mastoras
  class Workspace
    include Args

    MASTROREPO_PATH = 'mastrorepo_path'
    PACKER_YAML_NAME = 'packer_yaml_name'

    CONFIG_DATA_SCHEMA = Hash[
      MASTROREPO_PATH => String,
      PACKER_YAML_NAME => String,
    ]

    def initialize(ctx, mastrofile)
      @ctx = ctx
      @config = mastrofile
        .tap(&check(:mastrofile, Pathname))
        .open('r', &Util::F::LoadYaml)
        .tap(&check(mastrofile.to_s, CONFIG_DATA_SCHEMA))
        .freeze
      @mastrorepo = (mastrofile.dirname / @config[MASTROREPO_PATH])
        .freeze
      @packer_yaml_name = @config[PACKER_YAML_NAME]
        .freeze
    end

    attr_reader :config
    attr_reader :mastrorepo

    def scroll_of(name)
      Scroll.new(@ctx, @mastrorepo / name / @packer_yaml_name)
    end

    def scrolls
      @scrolls ||= @mastrorepo
        .enum_for(:each_child)
        .lazy
        .map { |child| Scroll.new(@ctx, child / @packer_yaml_name) }
        .freeze
    end
  end
end
