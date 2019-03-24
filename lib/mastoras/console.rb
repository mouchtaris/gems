# frozen_string_literal: true

require 'pathname'

module Mastoras
  # :reek:MissingSafeMethod { exclude: [ start! ] }
  class Console
    DEFAULT_SCROLL = '_sample/good/mastrofile'

    def initialize(args)
      @args = args.dup.map!(&:freeze)
    end

    def mastrofile
      @mastrofile ||= Pathname.new(
        @args[0] || DEFAULT_SCROLL
      )
    end

    def facade
      require 'mastoras/facade'
      @facade ||= ::Mastoras::Facade.new(mastrofile)
    end

    def start!
      require 'pry'
      facade.tap(&:pry)
    end
  end
end
