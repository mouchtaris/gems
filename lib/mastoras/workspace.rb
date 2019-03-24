# frozen_string_literal: true

require 'pathname'
require 'args'
require 'mastoras/util/f'
require 'mastoras/scroll'

module Mastoras
  class Workspace
    include Args

    CONFIG_DATA_SCHEMA = Hash[
      'mastrorepo_name': String,
      'packer_yaml_name': String,
    ]

    def initialize(ctx, mastrofile)
      @ctx = ctx
      @config = mastrofile
        .tap(&check(:mastrofile, Pathname))
        .open('r', &Util::F::LoadYaml)
        .tap(&check(:mastrofile, CONFIG_DATA_SCHEMA))
        .freeze
      @mastrorepo = (mastrofile.dirname / @config['mastrorepo_name'])
        .freeze
      @packer_yaml_name = @config['packer_yaml_name']
        .freeze
    end

    attr_reader :config
    attr_reader :mastrorepo

    def scroll_of(name)
      Scroll.new(@ctx, @mastrorepo / name / @packer_yaml_name)
    end

    def scrolls
      packer_yaml = @config['packer_yaml_name']
      @scrolls ||= @mastrorepo
        .enum_for(:each_child)
        .lazy
        .map { |child| Scroll.new(@ctx, child / packer_yaml) }
        .freeze
    end
  end
end
