require_relative 'util/module_registry'
module Queries
  extend Util::ModuleRegistry
  self.root_namespace = Queries.name
  Base = base

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

require_relative 'queries/artifact'
