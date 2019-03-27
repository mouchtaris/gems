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

    def module_registry_root_namespace
      @module_registry_root_namespace ||= /^#{name}::/
    end

    def register_module(clazz)
      key = clazz.name.gsub(module_registry_root_namespace, '')

      module_registry_logger.info "  + #{module_registry_root_namespace} :: #{key} -> #{clazz}"
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
