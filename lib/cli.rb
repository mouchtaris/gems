#!/usr/bin/env ruby
require 'optparse'

require 'bundler/setup'

class Cli
  class Options
    OUT = %i[txt json yaml]

    SetupParser = lambda do |prs|
      prs.instance_exec do
        on '-h', '--help', 'Print this message.'
        on '--out=[TYPE]', "Set output type. (#{OUT.map(&:to_s).join(', ')})", OUT
        on '-q[QUERY_NAME]', 'Perform a query. No query-name lists queries'
      end
    end

    def initialize(params)
      @params = params.dup.freeze
    end

    def parser
      @parser ||= OptionParser.new(&SetupParser)
    end

    def to_s
      parser.to_s
    end

    def parse
      @parse ||= (
        opts = {}
        args = parser.parse(@params, into: opts)
        [
          opts.freeze,
          args.freeze,
        ].freeze
      )
    end

    def opts
      @opts ||= parse[0]
    end

    def args
      @args ||= parse[1]
    end

    def help?
      opts[:help] == true
    end

    def list?
      opts[:list] == true
    end

    def out
      opts[:out] || :yaml
    end

    def list_queries?
      opts.has_key?(:q)
    end
  end

  def initialize(args)
    @opts = Options.new(args)
  end

  def output(result)
    case @opts.out
    when :txt
      result.each(&method(:puts))
    when :json
      require 'json'
      puts JSON.pretty_generate(result)
    when :yaml
      require 'yaml'
      YAML.dump(result, STDOUT)
    end
  end

  def help!
    puts @opts
  end

  def list_queries!
    require_relative 'queries'
    output(Queries.load!.names.to_a)
  end

  def execute!
    return help! if @opts.help?
    return list_queries! if @opts.list_queries?
    puts '???'
    pp @opts
  end
end

Cli.new(ARGV).execute! if __FILE__ == $0
