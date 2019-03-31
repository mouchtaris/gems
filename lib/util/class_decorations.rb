# frozen_string_literal: true

module Util
  module ClassDecorations
    def func(name)
      implementation = instance_method(name)

      define_method(name) do |*args, &block|
        method = (@methods ||= {})[name] ||= implementation.bind(self)
        if args.to_a.empty?
          method
        else
          method.call(*args, &block)
        end
      end
    end
  end
end
