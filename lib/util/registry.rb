require_relative 'lazy_block'
require_relative 'class_decorations'

module Util
  module Registry
    extend ClassDecorations

    def referal=(key)
      @registry_referal = key
    end

    def register(value)
      if method(:register).unbind != ::Util::Registry.instance_method(:register)
        raise '#register() is final -- cannot be overriden'
      end
      key = referal
      update key do |prev|
        raise "overwritting value #{prev.inspect} for #{key} in #{insopect}" if prev
        value
      end
    end
    make_final :register

    def update(key)
      return LazyBlock.new(method(:update), key) unless block_given?
      registry[key] = yield registry[key], key
    end

    def [](key)
      registry[key]
    end

    private

    def registry
      @registry ||= {}
    end

    def referal
      @registry_referal || (raise 'Referal not set!')
    end
  end
end
