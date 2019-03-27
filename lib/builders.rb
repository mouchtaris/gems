require_relative 'util/module_registry'

module Builders
  extend Util::ModuleRegistry
  Base = base
end

require_relative 'builders/builder'
require_relative 'builders/injector'
require_relative 'builders/vagrant'
