# frozen_string_literal: true

require 'args'
require 'logger'

module Mastoras
  # :reek:MissingSafeMethod { exclude: [ prepare_site! ] }
  class Ergo
    include Args

    def initialize(ctx, ws, name)
      @ctx = ctx.tap(&check(:ctx, ::Mastoras::Context::Check))
      @ws = ws.tap(&check(:ws, ::Mastoras::Workspace))
      @name = name
    end

    # :reek:UncommunicativeVariableName
    def logger
      @logger ||= Logger.new(STDERR)
        .tap { |l| l.progname = "Ergo[#{@name}]" }
    end

    def info(**params)
      require 'json'
      logger.info params.to_json
    end

    def scroll
      @scroll ||= @ws.scroll_of(@name)
    end

    def site
      @ws.bazaar / @name
    end

    def prepare_site!
      if site.exist?
        info SKIP: 'site.setup', site: site
      else
        info ACTION: 'site.setup', site: site
        require 'fileutils'
        FileUtils::Verbose.mkdir_p site.dirname
        FileUtils::Verbose.cp_r scroll.dir, site
      end
    end
  end
end
