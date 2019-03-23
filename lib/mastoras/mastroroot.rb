# frozen_string_literal: true

require 'args'

module Mastoras
  class Mastroroot
    include Args

    MASTROFILE_NAME = 'mastrofile'

    def initialize(mastroroot)
      @root = mastroroot
        .tap(&check(:mastroroot, Pathname))
    end

    def mastrofile
      @root / MASTROFILE_NAME
    end
  end
end
