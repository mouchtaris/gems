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

    def initialize(mastrofile)
      @config = mastrofile
        .tap(&check(:mastrofile, Pathname))
        .open('r', &Util::F::LoadYaml)
        .tap(&check(:mastrofile, CONFIG_DATA_SCHEMA))
        .freeze
      @mastrorepo = (mastrofile.dirname / @config['mastrorepo_name'])
        .freeze
    end

    attr_reader :config
    attr_reader :mastrorepo

    def scrolls
      packer_yaml = @config['packer_yaml_name']
      @scrolls ||= @mastrorepo
        .enum_for(:each_child)
        .lazy
        .map { |child| child / packer_yaml }
        .map(&Scroll::F.create)
        .freeze
    end
  end
end
