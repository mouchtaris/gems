require_relative '../util/module_registry'

module Cli
  module Actions
    extend Util::ModuleRegistry
    Base = base # ModuleRegistry

    class Action
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
require_relative 'actions/recode'
