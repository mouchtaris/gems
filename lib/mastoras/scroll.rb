# frozen_string_literal: true

require 'pathname'
require 'args'
require 'mastoras/util/f'

module Mastoras
  class Scroll
    include Args
    include Util::F

    PACKER_YAML_SCHEMA = Hash[
      'builders': Array[
        Hash[
          'type': String,
        ]
      ],
    ]

    def initialize(packer_yaml)
      @packer_yaml = packer_yaml.freeze
      @name = packer_yaml.basename.to_s.freeze
      @packer = packer_yaml
        .open('r', &Util::F::LoadYaml)
        .tap(&check(@packer_yaml.to_s, PACKER_YAML_SCHEMA))
    end

    attr_reader :name
    attr_reader :packer

    def builder_types
      @packer
        .dig('builders')
        .map { |builder| builder['type'] }
    end
  end
end
