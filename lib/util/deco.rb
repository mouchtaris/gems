# frozen_string_literal: true

require 'bundler/setup'
require 'util/args'

module Util
  class Deco
    include Args

    class << self
      def schema
        const_get :SCHEMA
      end
    end

    def initialize(value)
      @value = value.tap(&check(:value, self.class.schema))
    end
  end
end
