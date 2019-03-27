require_relative 'util/module_registry'
require_relative 'util/lazy_block'

module Builders
  extend Util::ModuleRegistry
  Base = base

  class << self
    def injection(scroll, meth, builder_def = nil)
      return Util::LazyBlock.new(method(:injection), scroll, meth) if builder_def.nil?
      each.reduce(builder_def) do |bdef, builder_pair|
        _, builder = builder_pair
        if builder.handle? builder: bdef
          binst = builder.new(scroll)
          binst.public_method(meth).call(bdef)
        else
          bdef # unchanged
        end
      end
    end
  end
end

require_relative 'builders/builder'
require_relative 'builders/vagrant'
