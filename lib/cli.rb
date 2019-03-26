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
        on '-q[QUERY_NAME]', 'Perform a query; no query-name lists queries.'
        on '--scroll=NAME', 'Specify scroll name.'
        on '--root=PATH', '(mastoric) repository root; where mastoras.yaml is.'
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

    def inspect
      ##<Cli::Options:0x0000565029445ca8
      # @opts={:q=>"artifact", :scroll=>"ubuntu-18.04"},
      #  @params=["-qartifact", "--scroll=ubuntu-18.04"],
      #   @parse=[{:q=>"artifact", :scroll=>"ubuntu-18.04"}, []],
      #
      "#<#{self.class.name}:#{object_id} @opts=#{opts.inspect} @args=#{args.inspect}>"
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
      opts.has_key?(:q) && !opts[:q]
    end

    def query
      opts[:q]
    end

    def scroll_name
      opts[:scroll]
    end

    def root
      opts[:root]
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

  def workspace
    @workspace ||= (
      require_relative 'workspace'
      root = Pathname.new(@opts.root || (raise '--root required'))
      Workspace.new(root)
    )
  end

  def queries
    @queries ||= (
      require_relative 'queries'
      Queries.load!
    )
  end

  def list_queries!
    output(queries.names.to_a)
  end

  def perform_query!
    q = queries[@opts.query] || (raise "Query not found: #{@opts.query}; try -q to list")
    q.new(workspace).perform(@opts)
  end

  def execute!
    return help! if @opts.help?
    return list_queries! if @opts.list_queries?
    return perform_query! if @opts.query
    puts '???'
    pp @opts
  rescue RuntimeError => e
    pp e
    pp @opts
  end
end

Cli.new(ARGV).execute! if __FILE__ == $0
