require 'args'

module Mastoras
  module Builders
    class Vagrant < Builder
      VAGRANT = 'vagrant'

      class << self
        def can_build?(scroll)
          scroll
            .tap(&Args.check(:scroll, Scroll))
            .build_types
            .include?(VAGRANT)
        end

        alias_method :===, :can_build?
      end

      def build!
        raise 'unimplemented'
      end
    end
  end
end
