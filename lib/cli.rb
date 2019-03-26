#!/usr/bin/env ruby
require 'optparse'

require 'bundler/setup'

module Cli
  module_function

  class Options
    SetupParser = lambda do |prs|
      prs.instance_exec do
        on '-h', '--help', 'Print this message'
      end
    end

    def initialize(params)
      @params = params.dup.freeze
    end

    def parser
      @parser ||= OptionParser.new.tap(&SetupParser)
    end

    def to_s
      parser.to_s
    end

    def parse
      @parse ||= (
        opts = {}
        args = parser.parse(@params, into: opts)
        [opts, args]
      )
    end

    def opts
      @opts ||= parse[0]
    end

    def args
      @args ||= parse[1]
    end

    def help?
      @help ||= (opts[:help] == true)
    end
  end

  def cli(args)
    opts = Options.new(args)
    return puts opts if opts.help?
  end
end

Cli.cli(ARGV) if __FILE__ == $0
