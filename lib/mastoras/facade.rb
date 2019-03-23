# frozen_string_literal: true

# standard lib
require 'pathname'
# appliocation
require 'mastoras/mastroroot'

module Mastoras
  ###
  class Facade
    include Args

    def initialize(mastroroot)
      @root = Mastroroot.new(mastroroot)
    end
  end
end
