# frozen_string_literal: true

# standard lib
require 'pathname'
# private gems
require 'args'

module Mastoras
  ###
  class Facade
    include Args

    def initialize(mastoroot)
      @mastoroot = mastoroot
        .tap(&check(:mastoroot, Pathname))
    end
  end
end
