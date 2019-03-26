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

    def module_loader_root
      @__module_loader__root ||= (
        ml = self::ModuleLoader
        (Pathname.new(ml::FILE).dirname / ml::NAME)
          .tap { |r| module_loader_logger.debug "root => #{r}" }
      )
    end

    def load!
      require 'pathname'
      mod_root = module_loader_root
      logger = module_loader_logger
      logger.info 'Loading . . .'
      self::ModuleLoader::MODULES.each do |mod_name|
        logger.info "  + #{mod_name}"
        self.referal = mod_name
        require_relative (mod_root / mod_name).to_s
      end
      self
    end

    make_safe! :load
  end
end
