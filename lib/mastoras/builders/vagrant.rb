# frozen_string_literal: true

require 'json'
require 'args'

module Mastoras
  module Builders
    # :reek:MissingSafeMethod { exclude: [ bravo!, build! ] }
    class Vagrant < Builder
      VAGRANT = 'vagrant'

      def build!(scroll)
        return unless super
          .builder_types
          .include?(VAGRANT)

        exec '/usr/bin/env', 'packer', 'packer.json'
      end
    end
  end
end
