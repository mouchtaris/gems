# frozen_string_literal: true

# standard lib
require 'pathname'
# appliocation
require 'mastoras/workspace'

module Mastoras
  class Facade
    include Args

    attr_reader :ws

    def initialize(mastroroot)
      @ws = Workspace.new(mastroroot)
    end

    def list
      @ws.scrolls.each do |scroll|
        printf '%20s:  %10s  %s',
               scroll.name,
               scroll.builder_types.join(','),
               "\n"
      end
    end
  end
end
