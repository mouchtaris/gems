require_relative 'util/module_registry'

module Actions
  extend Util::ModuleRegistry
  self.root_namespace = Actions
  Base = base

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

require_relative 'actions/packer'
