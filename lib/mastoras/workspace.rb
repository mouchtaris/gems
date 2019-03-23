# frozen_string_literal: true

require 'args'

module Mastoras
  class Workspace
    include Args

    def initialize(mastroroot)
      @mastroroot = mastroroot
        .tap(&check(:mastroroot, Pathname))
    end

    def mastrofile
      @mastroroot / 'mastrofile'
    end
  end
end
