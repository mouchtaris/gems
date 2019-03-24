# frozen_string_literal: true

# standard lib
require 'pathname'
# appliocation
require 'mastoras/workspace'
require 'mastoras/context'

module Mastoras
  class Facade
    include Args

    def initialize(mastrofile)
      @ctx = Context::Context.new
      @mastrofile = mastrofile
        .tap(&check(:mastrofiile, Pathname))
    end

    def ws
      Workspace.new(@ctx, @mastrofile)
    end

    def list
      ws.scrolls.each do |scroll|
        printf '%20s:  %10s  %s',
               scroll.name,
               scroll.builder_types.join(','),
               "\n"
      end
    end
  end
end
