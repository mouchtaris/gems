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

    def initialize(ctx, packer_yaml)
      @ctx = ctx
      @packer_yaml = packer_yaml.freeze
    end

    def dir
      @packer_yaml.dirname
    end

    def name
      @name ||= dir.basename.to_s.freeze
    end

    def packer
      @packer ||= @packer_yaml
        .open('r', &Util::F::LoadYaml)
        .tap(&check(@packer_yaml.to_s, PACKER_YAML_SCHEMA))
    end

    def builders
      packer['builders']
    end

    def builder_types
      builders.map { |bldr| bldr['type'] }
    end
  end
end
