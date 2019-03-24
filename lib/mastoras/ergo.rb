# frozen_string_literal: true

require 'args'
require 'logger'

module Mastoras
  # :reek:MissingSafeMethod { exclude: [ prepare_site! ] }
  class Ergo
    include Args
    PACKER_JSON = 'packer.json'

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
      @site ||= @ws.bazaar / @name
    end

    def packer_json
      @packer_json ||= site / PACKER_JSON
    end

    def prepare_site!
      return info SKIP: 'site.setup', site: site if site.exist?

      info ACTION: 'site.setup', site: site
      require 'fileutils'
      FileUtils::Verbose.mkdir_p site.dirname
      FileUtils::Verbose.cp_r scroll.dir, site
    end

    def packer_json!
      return info SKIP: 'site.packer_json', packer_json: packer_json \
        if packer_json.exist?

      info ACTION: 'site.packer_json', packer_json: packer_json
      packer_json.open('w') do |fout|
        fout.write(JSON.pretty_generate(scroll.packer))
      end
    end
  end
end
