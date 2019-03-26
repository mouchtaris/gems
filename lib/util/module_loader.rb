require_relative 'registry'

module Util
  module ModuleLoader
    extend ClassDecorations
    include Registry

    def module_loader_root
      @__module_loader__root ||= (
        Pathname.new(self::ModuleLoader::NAME)
      )
    end

    def load!
      require 'pathname'
      mod_root = module_loader_root
      self::ModuleLoader::MODULES.each do |mod_name|
        self.referal = mod_name
        require_relative (mod_root / mod_name).to_s
      end
    end

    make_safe! :load
  end
end
