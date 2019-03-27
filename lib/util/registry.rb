require_relative 'lazy_block'
require_relative 'class_decorations'

module Util
  module Registry
    extend ClassDecorations

    def registry_logger
      @__registry__logger ||= (
        require 'logger'
        Logger.new(STDERR).tap do |logger|
          logger.progname = "Registry[#{name}]"
        end
      )
    end

    def referal=(key)
      registry_logger.debug "Setting referal=#{key}"
      @registry_referal = key
    end

    def register(value)
      key = referal
      update key do |prev|
        raise "overwritting value #{prev.inspect} for #{key} in #{insopect}" if prev
        value
      end
    end
    #make_final :register

    def update(key)
      return LazyBlock.new(method(:update), key) unless block_given?
      registry[key].tap do |previous|
        registry[key] = yield(previous, key)
          .tap { |n| registry_logger.debug "Update [#{key}](#{previous.inspect}) := #{n.inspect}" }
      end
    end

    def [](key)
      registry[key]
        .tap { |r| registry_logger.debug "Accessing #{key} => #{r.inspect}" }
    end

    def each
      return to_enum unless block_given?
      registry.each do |k, v|
        yield k, v
      end
    end

    def registry_keys
      registry.keys
    end

    private

    def registry
      @registry ||= (
        registry_logger.debug 'Creating new'
        {}
      )
    end

    def referal
      @registry_referal || (raise 'Referal not set!')
    end
  end
end
