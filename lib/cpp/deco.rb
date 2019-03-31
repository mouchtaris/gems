# frozen_string_literal: true

require 'bundler/setup'
require 'args'

module Cpp
  class Deco
    include Args

    module_function def schema
      const_get :SCHEMA
    end

    def initialize(value)
      @value = value.tap(&check(:value, self.class.schema))
    end
  end
end
