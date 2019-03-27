require_relative 'registry'

module Util
  module ModuleRegistry
    include Registry

    def module_registry_logger
      @__module_registry__logger ||= (
        require 'logger'
        Logger.new(STDERR).tap do |logger|
          logger.progname = "ModuleRegistry[#{name}]"
        end
      )
    end

    def root_namespace=(ns)
      raise ArgumentError, :ns unless ns.is_a?(String) && !ns.empty?
      @root_namespace = /^#{ns}::/
    end

    def root_namespace
      @root_namespace || (
        raise "root_namespace not set for #{self.name} module loader"
      )
    end

    def register_module(clazz)
      module_registry_logger.info "  + #{clazz}"
      key = clazz.name.gsub(root_namespace, '')
      self.referal = key
      self.register clazz
    end

    alias_method :module_keys, :registry_keys

    def base
      module_registry = self
      @base ||= Module.new.tap do |baze|
        baze.define_singleton_method :extended do |mod|
          module_registry.module_registry_logger.debug "A new base in town: #{mod}"
        end
        baze.define_method :inherited do |clazz|
          module_registry.register_module(clazz)
        end
      end
    end
  end
end
