require_relative 'util/module_loader'

module Queries
  extend Util::ModuleLoader

  module ModuleLoader
    FILE = __FILE__
    NAME = 'queries'
    MODULES = %w[
      artifact
    ].freeze
  end
end
