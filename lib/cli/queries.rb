require_relative '../util/module_registry'

module Cli
  module Queries
    extend Util::ModuleRegistry
    Base = self.base # ModuleRegistry

    class Query
      extend Base

      def initialize(workspace)
        @workspace = workspace
      end

      def perform(opts)
        raise 'Not implemented'
      end
    end
  end
end
require_relative 'queries/artifact'
