# frozen_string_literal: true

# standard lib
require 'pathname'
# appliocation
require 'mastoras/mastroroot'
require 'mastoras/workspace'

module Mastoras
  ###
  class Facade
    include Args

    attr_reader :ws

    def initialize(mastroroot)
      @ws = Workspace.new(mastroroot)
    end
  end
end
