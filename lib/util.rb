require 'pathname'
require_relative 'funcs'
module Util
  module_function

  def load_yaml(source)
    case source
    when ::Pathname
      source.open('r', &Funcs.load_yaml)
    when ::String
      File.open('r', source, &Funcs.load_yaml)
    when ::IO
      Funcs.load_yaml.call(source)
    else
      raise ArgumentError, "Cannot handle #{
        source.inspect} as a YAML source"
    end
  end
end
