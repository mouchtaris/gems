require_relative 'registry'

module Util
  module ModuleLoader
    extend ClassDecorations
    include Registry

    def module_loader_logger
      @__module_loader__logger ||= (
        require 'logger'
        Logger.new(STDERR).tap do |logger|
          logger.progname = "ModuleLoader[#{self.name}]"
        end
      )
    end

    def module_loader_meta
      self::ModuleLoader
    end

    def module_loader_root
      @__module_loader__root ||= (
        require 'pathname'
        ml = self.module_loader_meta
        (Pathname.new(ml::FILE).dirname / ml::NAME)
          .tap { |r| module_loader_logger.debug "root => #{r}" }
      )
    end

    def load!
      mod_root = module_loader_root
      logger = module_loader_logger
      ml = self.module_loader_meta
      logger.info 'Loading . . .'
      ml::MODULES.each do |mod_name|
        path = mod_root / mod_name
        self.referal = mod_name

        logger.info "  + #{mod_name} (#{path})"
        require path.to_s
      end
      self
    end

    make_safe! :load
  end
end
