# frozen_string_literal: true

require 'bundler/setup'
require 'args'

module Util
  module Tap
    module_function

    def new
      raise LocalJumpError unless block_given?

      ->(obj) { obj.tap { yield obj } }
    end

    def check(name, check)
      new do
        Args.check(name, check)
      end
    end
  end
end
