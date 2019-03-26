require_relative 'util/module_loader'

module Queries
  class << self
    include Util::ModuleLoader
  end

  module ModuleLoader
    NAME = 'queries'
    MODULES = %w[
      artifact
    ].freeze
  end
end
