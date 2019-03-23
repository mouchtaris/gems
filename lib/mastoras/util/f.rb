# frozen_string_literal: true

require 'yaml'

module Mastoras
  module Util
    # This module has an :reek:UncommunicativeModuleName
    module F
      module_function

      LoadYaml = YAML.method(:safe_load)

      def class_functions(clazz)
        Module.new do
          extend self
          define_method :create do
            @create_f ||= clazz.method(:new)
          end
        end
      end

      class << self
        def included(clazz)
          clazz.const_set :F, F.class_functions(clazz)
        end
      end
    end
  end
end
