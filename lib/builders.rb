require_relative 'util/module_registry'

module Builders
  extend Util::ModuleRegistry
  Base = base

  class Builder
    extend Base
  end
end

require_relative 'builders/vagrant'
