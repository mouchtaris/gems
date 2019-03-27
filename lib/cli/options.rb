module Cli
  class Options
    OUT = :out
    OUTS = %i[txt json yaml]
    SCROLL = :scroll
    ROOT = :root
    QUERY_KEY = :q
    ACTION_KEY = :a
    BUILDER_KEY = :b

    SetupParser = lambda do |prs|
      prs.instance_exec do
        on '-h', '--help', 'Print this message.'
        on "--#{OUT}=[TYPE]", "Set output type. (#{OUTS.map(&:to_s).join(', ')})", OUTS
        on "--#{SCROLL}=NAME", 'Specify scroll name.'
        on "--#{ROOT}=PATH", '(mastoric) repository root; where mastoras.yaml is.'
        on "-#{QUERY_KEY}[QUERY_NAME]", 'Perform a query; no query-name lists queries.'
        on "-#{ACTION_KEY}[ACTION_NAME]", 'Perform an action: no action-name lists actions.'
        on "-#{BUILDER_KEY}[BUILDER}", 'Do not provider BUILDER -- list available builder support.'
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

    def out
      opts[:out] || :yaml
    end

    def scroll
      opts[SCROLL]
    end

    def root
      opts[ROOT]
    end

    list_or_take = lambda do |names, name, key|
      define_method :"list_#{names}?" do
        opts.has_key?(key) && !opts[key]
      end

      define_method :"#{name}" do
        opts[key]
      end
    end

    list_or_take.call :queries, :query, QUERY_KEY
    list_or_take.call :actions, :action, ACTION_KEY
    list_or_take.call :builders, :builder, BUILDER_KEY
  end
end
