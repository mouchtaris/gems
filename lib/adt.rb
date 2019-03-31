# frozen_string_literal: true

require 'pp'
require 'yaml'
require 'json'

require 'bundler/setup'

require 'args'

ParseError = Class.new(Exception)

module Parsers

  module ClassDecorations
    module InstanceDecorations
      alias_method :orig_methods, :methods
      def methods
        @methods ||= {}
      end

      alias_method :orig_method, :method
      def method(name)
        methods[name] ||= orig_method(name)
      end
    end

    class << self
      def extended(mod)
        mod.include InstanceDecorations
      end
    end
  end

  module State
    module Clazz
      extend ClassDecorations

      CHECK_CHECK = Tap.check(:CHECK, Object)
      DEFAULTS = proc do raise 'Please override' end

      def checks
        @checks ||= {}
      end

      def check_for(name)
        @checks[name] ||= (
          Tap.check(name, self::CHECKS[name].tap(&CHECK_CHECK))
        )
      end

      func def check(name = nil, value = nil)
        check_for(name).call(value)
      end

      func def check_all(attrs = nil)
        attrs.each(&check)
      end

      def new(**attrs)
        @attrs = attrs.tap(&check_all)
      end
    end

    module Instance
      def check_for(name)
        self.class.check_for(name)
      end

      def merge(attrs)
        lambda do |name, old_value|
          new_value = attrs[name]&.tap(&check_for(name))
          next_value = new_value || old_value
          [name, next_value]
        end
      end

      def copy(**attrs)
        next_attrs = @attrs
          .map(&merge(attrs))
          .to_h
        new(**next_attrs)
      end
    end
  end

  class State
  end

  class ParsingState < State
    CHECKS = {
      tokens: Array[Object]
    }
  end

  class State
    TOKENS = Tap.check(:tokens, Array[Object])

    def initialize(
      tokens: []
    )
      @tokens = TOKENS[tokens]
      @tokens_taken
    end

    def copy(
      tokens: nil
    )
      @tokens = tokens&.tap(&TOKENS) || @tokens
    end

    def add_tokens(tokens)
      self.class.copy(tokens: @tokens + tokens)
    end

    def tokens(n)
      @tokens[0..n]
    end
  end

  class Parser
    def generate_conditionally(state)
      tokens = parse(state)
      if tokens
        
      end
    end
  end

  class Namespaces < Parser
    def parse(state)
      token, = state.tokens(1)
      token if token.is_a?(Hash)
    end

    def generate(data)
    end
  end

  class Parser
    include Args

    def initialize(input)
      @input = input.tap(&check(:input, IO))
      @tokens = []
    end

    def tokens(n)
      @tokens[0...n]
    end
  end



  module Namespaces
    module_function

    def ===(parser)

    end
  end

  class Parser
    def initialize(input, fs)
      @input = input
      @fs = fs
    end
    attr_reader :input

    def parse_document
    end
  end

module Adt
  module_function

  def yaml
    YAML.safe_load File.read '/,/moof/interface.yaml'
  end

  def log(*args, lvl: 0)
    msg = format('[%<lvl>3d] %<time>s: ', lvl: lvl, time: Time.now.to_s)
    PP.pp(args, msg)
    STDERR.puts msg
  end

  def parse_line(line)
    log :parse_ling, line.to_s[0..5]
  end

  def parse_doc(doc)
    log :parse_doc
    case doc
    when Hash then doc.map {}
    else raise ParseError, "unhandlable-doc:#{doc.class}"
    end
  end

  def parse!
    @line = 0
    parse_doc yaml
  rescue ParseError => ex
    log "/tmp/lols.rb:#{@line}:#{ex}", lvl: 666
  end
end

Adt.parse! if $PROGRAM_NAME == __FILE__
